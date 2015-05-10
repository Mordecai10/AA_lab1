#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCOL 50

struct Nodo{
	char dato;
	int columna;
	int fila;

	struct Nodo * siguiente;
};

void AgregarFinal(struct Nodo *lista,char dato,int columna,int fila){
	//##########################################
	struct Nodo *aux,*aux2;
	int contador=0,i;
	aux2=lista;
	
	for (aux=lista; aux!=NULL; aux=aux->siguiente){
		contador++;
	}	
	for (i = 0; i < contador-1; ++i){
		aux2=aux2->siguiente;
	}
	//##########################################
	struct Nodo *nuevoNodo;
	nuevoNodo=malloc(sizeof(struct Nodo));
	aux2->siguiente=nuevoNodo;
	nuevoNodo->dato=dato;
	nuevoNodo->columna=columna;
	nuevoNodo->fila=fila;
	nuevoNodo->siguiente=NULL;
}

int main(int argc, char const *argv[]){
	struct Nodo *lista;
	lista=malloc(sizeof(struct Nodo));
	lista->siguiente=NULL;

//###########################################
	char linea[MAXCOL];
	FILE *archivo;
	int filas=0;
	int largo;
	int i;
	int columnas=0;

	archivo=fopen("entrada.txt","r");
	if (archivo!=NULL){
		
		while(!feof(archivo)){
			fgets(linea,MAXCOL,archivo);
			largo=strlen(linea);
			for (i = 0; i < largo; ++i)
			{
				if(linea[i]=='1'|| linea[i]=='2'|| linea[i]=='3'|| linea[i]=='0'){
					columnas++;	
					printf("dato %c en posicion(%d,%d)\n",linea[i],filas,columnas-1 );
					AgregarFinal(lista,linea[i],filas,columnas-1);
				}	
			}
			printf("las columnas son%d\n",columnas );
			columnas=0;
			filas++;
		}
		fclose(archivo);
	}

	printf("la cantidad de filas es: %d\n",filas);
	printf("%d\n",largo );
//###########################################
	lista=lista->siguiente;
	struct Nodo *lector;
	int numNodo=0;
	for (lector=lista; lector!=NULL; lector=lector->siguiente){
		printf("Nodo %i, tine los siguientes elementos: %c,coordenadas (%i,%i)\n",numNodo+1,lector->dato,lector->columna,lector->fila);
		numNodo++;
	}

	struct Nodo *encontrador;
	int encontrar=22;
		encontrador=lista;
		while(encontrar>1){
			encontrador=encontrador->siguiente;
			encontrar--;
		}
	printf("Nodo %i, tine los siguientes elementos: %c,coordenadas (%i,%i)\n",encontrar+1,encontrador->dato,encontrador->columna,encontrador->fila);	
//###########################################
	return 0;
}

