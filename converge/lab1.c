#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "combinacion.h"
#define MAXCOL 60
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
	nuevoNodo->columna=fila;
	nuevoNodo->fila=columna;
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
struct Nodo* encuentra(int encontrar,struct Nodo *lista,int revisado){
	struct Nodo *buscador;
		buscador=lista;
		int aux=encontrar;
		while(encontrar>1){
			buscador=buscador->siguiente;
			encontrar--;
		}
		if (revisado<2)
		{
			buscador->revisado=revisado;
		}
		
		//printf("Nodo %i, encontrado tine los siguientes elementos: %d,coordenadas (%i,%i)\n",aux,buscador->dato,buscador->columna,buscador->fila);	
		return buscador;
}
//##############################################
int main(int argc, char const *argv[]){
	
	int filas=0,columnas,aux=0,largo,nCombinacionesSinCero=0,i;
	char linea[MAXCOL];
	struct Nodo *lista;
	lista=malloc(sizeof(struct Nodo));
	lista->siguiente=NULL;

	FILE *archivo;


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



	int elementoCombinacion,elementoCombinacionAux,nDatoCombinacion,nDatoNoCero;
	int tiene2,tiene3,tiene1,pasos;
	int inicioCoorDX, inicioCoorDY;
	int finCoorDX, finCoorDY;
	lista=lista->siguiente;
	FILE * combinaciones;
	combinaciones= fopen("combinaciones.txt","w");
	fclose(combinaciones);
	generarCombinaciones(filas,columnas);
	combinaciones=fopen("combinaciones.txt","r");
	struct Nodo *inicial;
	int soluciones=0,Numerodecombinacion;
	int largoCombinacion=99999;

	if (combinaciones!=NULL){
		int ncombi=1,j;
		while(!feof(archivo)){
			formatear(lista);
			fgets(linea,MAXCOL,combinaciones);
			largo=strlen(linea);
			nDatoCombinacion=0;
			nDatoNoCero=0;
			tiene2=0;
			tiene3=0;
			tiene1=0;
			//DETERMINAR SI LA COMBINACION ES VALIDA--------------------------------
			printf("COMBINACION %i   ##############\n",ncombi );
			printf("{ ");
			for (i= 0; i < largo; ++i){
				elementoCombinacion=(int)(linea[i]-48);
				elementoCombinacionAux=(int)(linea[i+1]-48);
				if (elementoCombinacion>=0 && elementoCombinacionAux>=0)
				{
					elementoCombinacion=(((int)(linea[i]-48))*10+((int)(linea[i+1]-48)));
					i++;
					printf("%i ",elementoCombinacion);
					nDatoCombinacion++;
					inicial=encuentra(elementoCombinacion,lista,0);
					if((inicial->dato)>0){
						nDatoNoCero++;
					}
					if (inicial->dato==3)
					{
						tiene3=1;
						finCoorDX=inicial->columna;
						finCoorDY=inicial->fila;
					}
					if (inicial->dato==2)
					{
						tiene2=1;
						inicioCoorDX=inicial->columna;
						inicioCoorDY=inicial->fila;
					}
					if (inicial->dato==1)
					{
						tiene1++;
					}
				}
				else if (elementoCombinacion>=0 && elementoCombinacionAux<0)
				{
					elementoCombinacion=(int)(linea[i]-48);
					nDatoCombinacion++;
					inicial=encuentra(elementoCombinacion,lista,0);
					printf("%i ",elementoCombinacion);
					if((inicial->dato)>0){
						nDatoNoCero++;
					}
					if (inicial->dato==3)
					{
						tiene3=1;
						finCoorDX=inicial->columna;
						finCoorDY=inicial->fila;
					}
					if (inicial->dato==2)
					{
						tiene2=1;
						inicioCoorDX=inicial->columna;
						inicioCoorDY=inicial->fila;
						inicial=encuentra(elementoCombinacion,lista,1);
					}
					if (inicial->dato==1)
					{
						tiene1++;
					}
					
				}

			}
			printf("}\n");
			printf("tiene %i unos\n",tiene1 );
			pasos=tiene1+3;
			//FIN DETERMINAR--------------------------------------------------------
			//--SI ES VALIDA ENTONCES ANALIZAR--------------------------------------
			if (nDatoNoCero==nDatoCombinacion && tiene2 ==1 && tiene3==1 && tiene1>0){

				
				nCombinacionesSinCero++;
				
				//####################################################################
				printf("--------------------------COMBINACION SIN CEROS, INICIO Y FINAL\n");

				
				
				while(pasos>0){
					printf("pasos: %i\n",pasos);
					int ciclo;
					printf("INICIO: (%i,%i)\n",inicioCoorDY,inicioCoorDX );


					for (i = 0; i < largo; ++i){
						//------------------ACCEDIENDO A LOS ELEMENTOS------------------------
						int avanceX,avanceY;
						ciclo=0;
						while(ciclo==0){
							elementoCombinacion=(int)(linea[i]-48);
							elementoCombinacionAux=(int)(linea[i+1]-48);
							if (elementoCombinacion>=0 && elementoCombinacionAux>=0){
								elementoCombinacion=(((int)(linea[i]-48))*10+((int)(linea[i+1]-48)));
								i++;
								printf("%i ",elementoCombinacion);
							}
							else if (elementoCombinacion>=0 && elementoCombinacionAux<0)
							{
								elementoCombinacion=(int)(linea[i]-48);
								printf("%i ",elementoCombinacion);
							}
							ciclo=1;
						}

						inicial=encuentra(elementoCombinacion,lista,3);
						printf("DATO[%i]\n",inicial->dato );
						if (inicial->dato > 0)
						{
							/* code */
							avanceX=((inicial->columna)-inicioCoorDX);
							avanceY=((inicial->fila)-inicioCoorDY);

							if (avanceX==-1 && avanceY==0 && inicial->revisado==0)
							{
								printf("SOY:-------%i MIS COORDENADAS SON:(%i,%i) REVISADO?[%i]\n",inicial->dato,inicial->columna,inicial->fila,inicial->revisado );
								printf("------------------------->[Izquierda]\n");
								inicioCoorDX=inicial->columna;
								inicial=encuentra(elementoCombinacion,lista,1);
								pasos--;
								if (inicial->dato==3 && pasos==0)
								{
									printf("------------------------->------------------------->SOY EL ULTIMO Y TERMINE!!!!!\n");
									
									
									if (largoCombinacion<ncombi)
									{
										largoCombinacion=ncombi;
										Numerodecombinacion=ncombi;
										soluciones++;
									}
								}
							}
							else if (avanceX==1 && avanceY==0 && inicial->revisado==0)
							{
								printf("SOY:-------%i MIS COORDENADAS SON:(%i,%i) REVISADO?[%i]\n",inicial->dato,inicial->columna,inicial->fila,inicial->revisado );
								printf("------------------------->[Derecha]\n");
								inicioCoorDX=inicial->columna;
								inicial=encuentra(elementoCombinacion,lista,1);
								pasos--;
								if (inicial->dato==3 && pasos==0)
								{
									printf("------------------------->------------------------->SOY EL ULTIMO Y TERMINE!!!!!\n");
									if (largoCombinacion<ncombi)
									{
										largoCombinacion=ncombi;
										Numerodecombinacion=ncombi;
										soluciones++;
									}
								}
							}
							else if (avanceX==0 && avanceY==-1 && inicial->revisado==0)
							{
								printf("SOY:-------%i MIS COORDENADAS SON:(%i,%i) REVISADO?[%i]\n",inicial->dato,inicial->columna,inicial->fila,inicial->revisado );
								printf("------------------------->[Arriba]\n");
								inicioCoorDY=inicial->fila;
								inicial=encuentra(elementoCombinacion,lista,1);
								pasos--;
								if (inicial->dato==3 && pasos==0)
								{
									printf("------------------------->------------------------->SOY EL ULTIMO Y TERMINE!!!!!\n");
									if (largoCombinacion<ncombi)
									{
										largoCombinacion=ncombi;
										Numerodecombinacion=ncombi;
										soluciones++;
									}
								}
							}
							else if (avanceX==0 && avanceY==1 && inicial->revisado==0)
							{
								printf("SOY:-------%i MIS COORDENADAS SON:(%i,%i) REVISADO?[%i]\n",inicial->dato,inicial->columna,inicial->fila,inicial->revisado );
								printf("------------------------->[Abajo]\n");
								inicioCoorDY=inicial->fila;
								inicial=encuentra(elementoCombinacion,lista,1);
								pasos--;
								if (inicial->dato==3 && pasos==0)
								{
									printf("------------------------->------------------------->SOY EL ULTIMO Y TERMINE!!!!!\n");
									if (largoCombinacion<ncombi)
									{
										largoCombinacion=ncombi;
										Numerodecombinacion=ncombi;
										soluciones++;
									}
								}
							}
							else{
								//printf("ESTOY LEJOS DEL INICIO\n");
							}
						}

						//------------------ACCEDIENDO A LOS ELEMENTOS------------------------
						//printf("SOY:-------%i MIS COORDENADAS SON:(%i,%i) REVISADO?[%i]\n",inicial->dato,inicial->columna,inicial->fila,inicial->revisado );




					}
					pasos--;
				}
				
				

			}
			//--FIN SI ES VALIDA---------------------------------------------------

		ncombi++;
		printf("FIN ANALISIS COMBINACION----------------------\n");
		}
	}


	struct Nodo *lector;
	formatear(lista);
	int numNodo=0;
	for (lector=lista; lector!=NULL; lector=lector->siguiente){

		printf("Nodo %i, tine los siguientes elementos: %d,coordenadas (%i,%i) REVISADO: %i\n",numNodo+1,lector->dato,lector->columna,lector->fila,lector->revisado);
		numNodo++;
	}
	printf("LA CANTIDAD DE NODOS ES:%i\n",numNodo);
	printf("LA CANTIDAD DE COMBINACIONES VALIDAS SON : %i\n",nCombinacionesSinCero );
	printf("LA CANTIDAD DE SOLUCIONES ES: %i\n",soluciones );
	printf("EL NUMERO DA LA COMBINACION SOLUCION ES: %i\n",Numerodecombinacion );



//###########################################
	return 0;
}

