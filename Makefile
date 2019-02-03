vpath %.h	include
vpath %.cpp	src

OBJDIR = bin
OBJ = $(addprefix $(OBJDIR)/, token.o)
CXXFLAGS = -std=c++17 -Wall -pedantic

.PHONY: run coverage clean

run:
	$(MAKE) build
	./$(OBJDIR)/lox

debug: CXXFLAGS += -DDEBUG -g
debug: build

build: src/main.o $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/lox $^

test: CXXFLAGS += -fprofile-arcs -ftest-coverage
test: $(OBJDIR)/test.o $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/$@ $^
	./$(OBJDIR)/$@
	$(MAKE) coverage

coverage:
	mkdir -p coverage
	mv $(OBJDIR)/*.gcda src/
	mv $(OBJDIR)/*.gcno src/
	gcov src/test.cpp src/token.cpp
	mv *.gcov coverage/

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJDIR)/*
	rm -f coverage/*
	find . -type f -name '*.gcda' -exec rm {} +
	find . -type f -name '*.gcno' -exec rm {} +
