#include <stdio.h>

#define libexp __declspec(dllexport)

libexp void testDll()
{
   printf ("Hello DLL.\n");
}

