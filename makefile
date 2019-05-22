OBJ = View.o Game.o Tui.o Control.o main.o AI.o
PROG = main
HDR = View.h Game.h Tui.h Control.h AI.h
CXXFLAGS += -Wall -Wextra -std=c++17

all: $(PROG)

$(PROG): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	$(RM) $(OBJ) $(PROG)
