#ifndef _BASE_COM_H
#define _BASE_COM_H

#include <Windows.h>

class BaseCom {
public:
	virtual bool Open(const char* name) = 0;
	virtual void Close(void) = 0;
	virtual bool Send(PBYTE buf, int size) = 0;
	virtual bool Recv(PBYTE buf, int size) = 0;
};

#endif