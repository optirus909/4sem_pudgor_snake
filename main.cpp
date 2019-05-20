#include <iostream>
#include "View.h"
#include "Game.h"
#include "Tui.h"
#include "Control.h"

int main()
{
	View * v = View::get();
	
	Game g;
	
	v->set_model(&g);
	
	Snake s;
	Human h(&s);
	
	g.add(&s);
	
	v->draw();
	v->run();
	
	v->~View();
	return 0;
}