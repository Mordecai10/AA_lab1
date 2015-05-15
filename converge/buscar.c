void buscar(int largo,struct Nodo *lista,int inicioCoorDX,int inicioCoorDY, int finCoorDX, int finCoorDY,int pasos)
{
	//####################################################################
	printf("-------------------------------------COMBINACION SIN CEROS, INICIO Y FINAL\n");

	
	int elementoCombinacion,elementoCombinacionAux;
	while(pasos>0){
		printf("pasos: %i\n",pasos);
		int ciclo;
		printf("INICIO: (%i,%i)\n",inicioCoorDY,inicioCoorDX );


		for (i = 0; i < largo; ++i){
			//------------------ACCEDIENDO A LOS ELEMENTOS------------------------
			int avanceX,avanceY;
			int ciclo=0;
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
			if (inicial->dato==2)
			{
				inicial=encuentra(elementoCombinacion,lista,1);
			}
			//------------------ACCEDIENDO A LOS ELEMENTOS------------------------
			printf("SOY:-------%i MIS COORDENADAS SON:(%i,%i)\n",inicial->dato,inicial->columna,inicial->fila );

			avanceX=(inicioCoorDX-inicial->columna);
			avanceY=(inicioCoorDY-inicial->fila);

			if (avanceX==-1 && avanceY==0 && inicial->revisado==0)
			{
				printf("------------------------->[Derecha]\n");
				inicioCoorDX=inicial->columna;
				inicial=encuentra(elementoCombinacion,lista,1);
				pasos--;
				buscar(largo,lista,inicioCoorDX,inicioCoorDY,finCoorDX,finCoorDY,pasos);
			}
			else if (avanceX==1 && avanceY==0 && inicial->revisado==0)
			{
				printf("------------------------->[Izquierda]\n");
				inicioCoorDX=inicial->columna;
				inicial=encuentra(elementoCombinacion,lista,1);
				pasos--;
				buscar(largo,lista,inicioCoorDX,inicioCoorDY,finCoorDX,finCoorDY,pasos);
			}
			else if (avanceX==0 && avanceY==-1 && inicial->revisado==0)
			{
				printf("------------------------->[Abajo]\n");
				inicioCoorDY=inicial->fila;
				inicial=encuentra(elementoCombinacion,lista,1);
				pasos--;
				buscar(largo,lista,inicioCoorDX,inicioCoorDY,finCoorDX,finCoorDY,pasos);
			}
			else if (avanceX==0 && avanceY==1 && inicial->revisado==0)
			{
				printf("------------------------->[Arriba]\n");
				inicioCoorDY=inicial->fila;
				inicial=encuentra(elementoCombinacion,lista,1);
				pasos--;
				buscar(largo,lista,inicioCoorDX,inicioCoorDY,finCoorDX,finCoorDY,pasos);
			}
			else{
				printf("ESTOY LEJOS DEL INICIO\n");
			}



		}
	}
}