#ifndef ADMIN_OPS
#define ADMIN_OPS

#include "comFunc.h"

bool adminHandler(int connFD);

bool adminHandler(int connFD) {
	logHandler(true, connFD, NULL);
}

#endif
