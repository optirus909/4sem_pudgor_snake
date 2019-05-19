OBJ = View.o Game.o Tui.o Control.o main.o
PROG = main
HDR = View.h Game.h Tui.h Control.h
CXXFLAGS += -Wall -Wextra -std=c++17

all: $(PROG)

$(PROG): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	$(RM) $(OBJ) $(PROG)
