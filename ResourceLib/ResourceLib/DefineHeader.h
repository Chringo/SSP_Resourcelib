#pragma once
#define DLLEXPORT


#ifdef DLLEXPORT
#define DLL_OPERATION __declspec(dllexport)
#else
#define DLL_OPERATION __declspec(dllimport)
#endif


#include <iostream>

