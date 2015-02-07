#ifndef __SIMPLE_COM_OBJ
#define __SIMPLE_COM_OBJ
#include "base.h"
#include <Unknwn.h>
interface IX : public IUnknown
{	
	virtual void Fx1() = 0;
};

void CreateIXComInterface(IX** ppIx);



#endif