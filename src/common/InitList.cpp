
// this is a combination of some C++ and preprocessor magic which allows a
// group of initialization functions to be declared across many different
// source files and then at the appropriate time all can be called at once.
// The "trick" is that it automatically works for all modules linked to the
// program so you don't have to keep a handmade list anywhere of the names
// of the initialization functions. This is used by the AI functions to initialize
// all the function pointers etc for the various creatures.
#include "InitList.h"
#include "stat.h"

void InitList::AddFunction(void (*func)(void))
{
	AddFunction((void *)func);
}

void InitList::AddFunction(bool (*func)(void))
{
	AddFunction((void *)func);
}

void InitList::AddFunction(void *func)
{
	//stat("AddFunction (void)%08x [%d]", func, fCount);
	if (fCount >= MAX_INIT_RECORDS)
		return;
	
	fFunctions[fCount++] = (void *)func;
}

/*
void c------------------------------() {}
*/

bool InitList::CallFunctions()
{
int i;

	if (fCount >= MAX_INIT_RECORDS)
	{
		stat("InitList::CallFunctions(%08x): too many initializers", this);
		return 1;
	}
	
	stat("InitList::CallFunctions(%08x): executing %d functions...", this, fCount);
	
	for(i=0;i<fCount;i++)
	{
		void (*func)(void) = (void (*)())fFunctions[i];
		(*func)();
	}
	
	return 0;
}






