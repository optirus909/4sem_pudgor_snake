#include <iostream>
#include <fstream>
#include "View.h"
#include "AI.h"
#include "Game.h"
#include "Tui.h"
#include "Control.h"

static std::ofstream fout("log.txt");


int main()
{
	View * v = View::get();
	
	Game g;
	
	v->set_model(&g);
	
	Snake s;
	Human h(&s);
	
	Snake * s2 = new Snake;
	AI ai(s2);
	
	g.add(&s);
	g.add(s2);
	
	v->draw();
	v->run();
	v->~View();
	return 0;
}