OBJ = Game.o Tui.o Control.o main.o
PROG = main
HDR = Game.h Tui.h View.h Control.h
CXXFLAGS += -Wall -Wextra -std=c++17

all: $(PROG)

$(PROG): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	$(RM) $(OBJ) $(PROG)
