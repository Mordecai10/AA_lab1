#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "combinacion.h"
#define MAXCOL 25
struct Nodo{
	int dato;
	int columna;
	int fila;
	int revisado;

	struct Nodo * siguiente;
};
//##########################################
void AgregarFinal(struct Nodo *lista,int dato,int columna,int fila){
	struct Nodo *aux,*aux2;
	int contador=0,i;
	aux2=lista;
	
	for (aux=lista; aux!=NULL; aux=aux->siguiente)
		contador++;
	for (i = 0; i < contador-1; ++i)
		aux2=aux2->siguiente;

	struct Nodo *nuevoNodo;
	nuevoNodo=malloc(sizeof(struct Nodo));
	aux2->siguiente=nuevoNodo;
	nuevoNodo->dato=dato;
	nuevoNodo->columna=columna;
	nuevoNodo->fila=fila;
	nuevoNodo->revisado=0;
	nuevoNodo->siguiente=NULL;
}
//##############################################
void formatear(struct Nodo *lista){
	struct Nodo *formateo;
	for (formateo=lista; formateo!=NULL; formateo=formateo->siguiente)
		formateo->revisado=0;
}
//##############################################
void generarCombinaciones(int filas,int columnas){

	int i,NUMELEMENTOS=filas*columnas;
	for (i = 0; i < NUMELEMENTOS; ++i)
		combinacion(NUMELEMENTOS,i+1);
}
//##############################################
struct Nodo* encuentra(int encontrar,struct Nodo *lista){
	struct Nodo *buscador;
		buscador=lista;
		int aux=encontrar;
		while(encontrar>1){
			buscador=buscador->siguiente;
			encontrar--;
		}
		//printf("Nodo %i, encontrado tine los siguientes elementos: %d,coordenadas (%i,%i)\n",aux,buscador->dato,buscador->columna,buscador->fila);	
		return buscador;
}
//##############################################
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
		int convertir1;
		while(!feof(archivo)){
			fgets(linea,MAXCOL,archivo);
			largo=strlen(linea);
			for (i = 0; i < largo; ++i){
				if(linea[i]=='1'|| linea[i]=='2'|| linea[i]=='3'|| linea[i]=='0'){
					aux++;	
					printf("dato %c en posicion(%d,%d)\n",linea[i],filas,aux-1 );
					convertir1=(int)(linea[i]-48);
					AgregarFinal(lista,convertir1,filas,aux-1);
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


	int elemenetoCombinacion, elementoDato,numeroCombinacion,numeroNoCero;
	lista=lista->siguiente;
	FILE * combinaciones;
	combinaciones= fopen("combinaciones.txt","w");
	fclose(combinaciones);
	generarCombinaciones(filas,columnas);
	combinaciones=fopen("combinaciones.txt","r");
	struct Nodo *inicial;
	if (archivo!=NULL){
		int ncombi=1,j;
		while(!feof(archivo)){
			fgets(linea,MAXCOL,combinaciones);
			largo=strlen(linea);
			numeroCombinacion=0;
			numeroNoCero=0;
			//printf("EL LARGO DE LA LINEA ES : %i\n",largo);
			printf("COMBINACION %i   ##############\n",ncombi );
			for (i= 0; i < largo; ++i){
				elemenetoCombinacion=(int)(linea[i]-48);
				if (elemenetoCombinacion>0){
					numeroCombinacion++;
				}
				inicial=encuentra(elemenetoCombinacion,lista);
				if((inicial->dato)>0){
					numeroNoCero++;
				}
			}
			if (numeroCombinacion==numeroNoCero){
				printf("LA COMBINACION %i ES CANDIDATA!!!!!!!\n",ncombi );
				printf("CON %i ELEMENTOS\n",numeroNoCero);
				for (i = 0; i < largo; ++i){

					elemenetoCombinacion=(int)(linea[i]-48);
					inicial=encuentra(elemenetoCombinacion,lista);
					elementoDato=inicial->dato;
					if (elementoDato==2){
						int coordenadaI,coordenadaJ;
						int restantes;

						printf("COMBINACION CON UN DOS! %i\n",ncombi );
						printf("CUYOS DATOS SON DATO: %i COLUMNA: %i FILA: %i REVISADO: %i\n",inicial->dato,inicial->columna,inicial->fila,inicial->revisado );
						


					}
				}
			}

			ncombi++;
		}
	}


	struct Nodo *lector;
	int numNodo=0;
	for (lector=lista; lector!=NULL; lector=lector->siguiente){
		printf("Nodo %i, tine los siguientes elementos: %d,coordenadas (%i,%i)\n",numNodo+1,lector->dato,lector->columna,lector->fila);
		numNodo++;
	}



//###########################################
	return 0;
}

