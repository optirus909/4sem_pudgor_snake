#include "View.h"
#include "Tui.h"
#include "Game.h"
#include "Control.h"

View * View::inst;

View * View::get()
{
	if(inst)
		return inst;
	inst = new Tui;
	return inst;
}