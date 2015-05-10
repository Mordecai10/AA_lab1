#include <stdio.h>
#include <stdlib.h>
#include "combinacion.h"
#define NUMELEMENTOS 4
int main(int argc, char const *argv[])
{
	FILE * combinaciones;
	combinaciones= fopen("combinaciones.txt","w");
	fclose(combinaciones);	
	int i;
	for (i = 0; i < NUMELEMENTOS; ++i)
	{
		combinacion(NUMELEMENTOS,i+1);
	}
	return 0;
}