OBJ = Tui.o main.o
PROG = main
HDR = Tui.h View.h
CXXFLAGS += -Wall -Wextra

all: $(PROG)

$(PROG): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	$(RM) $(OBJ) $(PROG)
