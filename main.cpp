#include <iostream>
#include "Tui.h"
#include "Game.h"

int main()
{
	Tui t;
	
	Game g;
	
	t.set_model(&g);
	
	t.draw();
	t.run();
	
	return 0;
}