#include <fstream>
#include "View.h"
#include "Tui.h"
#include "Game.h"
#include "Control.h"

static std::ofstream fout("log.txt");

View * View::inst;

View * View::get()
{
	if(inst)
		return inst;
	inst = new Tui;
	return inst;
}

View::~View()
{
	fout << "started func view dtor" << std::endl;
	fout << "ended func view dtor" << std::endl;
}