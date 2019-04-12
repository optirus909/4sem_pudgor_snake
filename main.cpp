#include <iostream>
#include "Tui.h"
#include "Game.h"
#include "Control.h"

int main()
{
	Tui t;
	
	Game g;
	
	t.set_model(&g);
	
	Snake s;
	Human h(&s);
	
	g.add(&s);
	
	t.draw();
	t.run();
	
	return 0;
}