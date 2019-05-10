#include <View.h>

View * View::inst;

View * View::get()
{
	if(inst)
		return inst;
	inst = new Tui;
	return inst;
}