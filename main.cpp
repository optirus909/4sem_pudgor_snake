#include <iostream>
#include <fstream>
#include "View.h"
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
	
	g.add(&s);
	
	v->draw();
	v->run();
	fout << "main started view dtor" << std::endl;
	v->~View();
	fout << "main ended view dtor" << std::endl;
	return 0;
}