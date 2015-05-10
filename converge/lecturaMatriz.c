#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "combinacion.h"
#define MAXCOL 50

struct Nodo{
	char dato;
	int columna;
	int fila;

	struct Nodo * siguiente;
};

//##########################################
void AgregarFinal(struct Nodo *lista,char dato,int columna,int fila){
	struct Nodo *aux,*aux2;
	int contador=0,i;
	aux2=lista;
	
	for (aux=lista; aux!=NULL; aux=aux->siguiente){
		contador++;
	}	
	for (i = 0; i < contador-1; ++i){
		aux2=aux2->siguiente;
	}

	struct Nodo *nuevoNodo;
	nuevoNodo=malloc(sizeof(struct Nodo));
	aux2->siguiente=nuevoNodo;
	nuevoNodo->dato=dato;
	nuevoNodo->columna=columna;
	nuevoNodo->fila=fila;
	nuevoNodo->siguiente=NULL;
}
//##########################################
void generarCombinaciones(int filas,int columnas){

	int i,NUMELEMENTOS=filas*columnas;
	for (i = 0; i < NUMELEMENTOS; ++i)
		combinacion(NUMELEMENTOS,i+1);
}

int main(int argc, char const *argv[]){
	
	struct Nodo *lista;
	lista=malloc(sizeof(struct Nodo));
	lista->siguiente=NULL;

	char linea[MAXCOL];
	FILE *archivo;
	int filas=0,columnas,aux=0,largo,i;

//###########################################
	archivo=fopen("entrada.txt","r");
	if (archivo!=NULL){
		
		while(!feof(archivo)){
			fgets(linea,MAXCOL,archivo);
			largo=strlen(linea);
			for (i = 0; i < largo; ++i){
				if(linea[i]=='1'|| linea[i]=='2'|| linea[i]=='3'|| linea[i]=='0'){
					aux++;	
					printf("dato %c en posicion(%d,%d)\n",linea[i],filas,aux-1 );
					AgregarFinal(lista,linea[i],filas,aux-1);
				}	
			}
			filas++;
			if (filas==1){
				columnas=aux;
			}
			aux=0;
		}
		fclose(archivo);
	}

	printf("la cantidad de filas es: %d\n",filas);
	printf("la cantidad de columnas es: %d\n",columnas);
//###########################################
	FILE * combinaciones;
	combinaciones= fopen("combinaciones.txt","w");
	fclose(combinaciones);
	generarCombinaciones(filas,columnas);


	lista=lista->siguiente;
	struct Nodo *lector;
	int numNodo=0;
	for (lector=lista; lector!=NULL; lector=lector->siguiente){
		printf("Nodo %i, tine los siguientes elementos: %c,coordenadas (%i,%i)\n",numNodo+1,lector->dato,lector->columna,lector->fila);
		numNodo++;
	}

	struct Nodo *encontrador;
	int encontrar=2;
		encontrador=lista;
		while(encontrar>1){
			encontrador=encontrador->siguiente;
			encontrar--;
		}
	printf("Nodo %i, encontrado tine los siguientes elementos: %c,coordenadas (%i,%i)\n",encontrar+1,encontrador->dato,encontrador->columna,encontrador->fila);	
//###########################################
	return 0;
}

