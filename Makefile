vpath %.h	include
vpath %.cpp	src

OBJDIR = bin
OBJ = $(addprefix $(OBJDIR)/, token.o)
CXXFLAGS = -std=c++17 -Wall -pedantic

.PHONE run:
	$(MAKE) build
	./$(OBJDIR)/lox

debug: CXXFLAGS += -DDEBUG -g
debug: build

build: $(OBJDIR)/main.o $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/lox $^

test: CXXFLAGS += -fprofile-arcs -ftest-coverage
test: $(OBJDIR)/test.o $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/$@ $^
	./$(OBJDIR)/$@ -r junit > report.xml

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY clean:
	rm -f $(OBJDIR)/*
