vpath %.h	include
vpath %.cpp	src

OBJDIR = bin
OBJ = $(addprefix $(OBJDIR)/, main.o token.o)

all: lox-cpp

debug: CXXFLAGS += -DDEBUG -g
debug: lox-cpp

lox-cpp: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/$@ $^

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(OBJDIR)/lox-cpp
	find . -type f -name '*.o' -exec rm {} +
