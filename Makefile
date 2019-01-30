vpath %.h	include
vpath %.cpp	src

OBJDIR = bin
OBJ = $(addprefix $(OBJDIR)/, token.o)
CXXFLAGS = -std=c++17 -Wall -pedantic

all: lox-cpp test

run: lox-cpp
	./bin/lox-cpp

debug: CXXFLAGS += -DDEBUG -g
debug: lox-cpp

test: run-test
	./bin/run-test

run-test: $(OBJDIR)/test.o $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/$@ $^

lox-cpp: $(OBJDIR)/main.o $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/$@ $^

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(OBJDIR)/lox-cpp
	find . -type f -name '*.o' -exec rm {} +
