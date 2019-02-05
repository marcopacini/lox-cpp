vpath %.h	include
vpath %.cpp	src

OBJDIR = bin
OBJ = $(addprefix $(OBJDIR)/, token.o scanner.o)
CXXFLAGS = -std=c++17 -Wall -pedantic

.PHONY: run coverage clean

run:
	$(MAKE) build
	./$(OBJDIR)/lox

debug: CXXFLAGS += -D DEBUG -g
debug: build

build: src/main.o $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/lox $^

# -lgcov -fprofile-arcs -ftest-coverage
test: CXXFLAGS += --coverage
test: $(OBJDIR)/test.o $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/$@ $^
	./$(OBJDIR)/$@

coverage:
	mv $(OBJDIR)/*.gcda src/
	mv $(OBJDIR)/*.gcno src/
	gcov src/test.cpp src/token.cpp src/scanner.cpp > /dev/null

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJDIR)/*
	find . -type f -name '*.gcda' -exec rm {} +
	find . -type f -name '*.gcno' -exec rm {} +
	find . -type f -name '*.gcov' -exec rm {} +
