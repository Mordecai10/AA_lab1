#include "combinacion.h"
#include <stdio.h>

/******************************************************************************
 * DECLARACIÓN DE CONSTANTES
 ******************************************************************************/
#define TRUE           1             /* Valor que indica verdadero            */
#define FALSE          0             /* Valor que indica falso                */

/******************************************************************************
 * DECLARACIÓN DE TIPOS
 ******************************************************************************/
typedef unsigned char Boolean;


/******************************************************************************
 * DECLARACIÓN DE FUNCIONES
 ******************************************************************************/
void imprimirCombinacion(unsigned char *ucVector, unsigned char ucElementos);
unsigned char incrementarCombinacion(unsigned char *ucVector,
                                     unsigned char ucActual,
                                     unsigned char ucElementos,
                                     unsigned char ucElemCombi,
                                     Boolean ucSalir);


/******************************************************************************
 * MAIN
 ******************************************************************************/
int combinacion(int MAX_ELEMENTOS,int ELEM_X_COMBI)
{
  unsigned char ucVector[MAX_ELEMENTOS];     /* Vector de elementos a ordenar */
  unsigned char ucI;                         /* Contador para los bucles      */
  unsigned char ucElementos;                 /* Número total de elementos     */
  unsigned char ucElemCombi;                 /* Elementos por combinación     */
  Boolean bSalir;                            /* Indica si se sale del bucle   */

  /* Inicialización de variables                                              */
  ucElementos = MAX_ELEMENTOS;
  ucElemCombi = ELEM_X_COMBI;
  bSalir = FALSE;

  /* Relleno de los elementos iniciales del vector.                           */
  for(ucI = 0; ucI < ucElementos; ucI++)
  {
    ucVector[ucI] = ucI;
  }

  /* Impresión de los elementos iniciales del vector                          */
  imprimirCombinacion(ucVector, ucElemCombi);

  /* Se repite mientras no se indique que se debe salir del bucle             */
  while(bSalir == FALSE)
  {
    /* Paso a la siguiente combinación. El valor de la variable bSalir no se  */
    /* tiene en cuenta ya que siempre será True.                              */
    bSalir = incrementarCombinacion(ucVector, ucElemCombi - 1, ucElementos,
                                    ucElemCombi, 0);

    /* Si el primer elemento se ha salido del rango del vector, la            */
    /* combinación ya no es válida. Por lo que se ha recorrido la lista de    */
    /* combinaciones al completo.                                             */
    if(ucVector[0] > (ucElementos - ucElemCombi))
    {
      bSalir = TRUE;
    }
    /* En caso contrario se muestra la combinación actual por pantalla        */
    else
    {
      imprimirCombinacion(ucVector, ucElemCombi);
      bSalir = FALSE;
    }
  }

  return 0;
}


/******************************************************************************
 * IMPRIMIRCOMBINACION
 ******************************************************************************/
void imprimirCombinacion(unsigned char *ucVector, unsigned char ucElementos)
{
  unsigned char ucI;                            /* Contador para el bucle for */

  printf("Combinacion: { ");

  /* Impresión de todos los elementos necesarios del vector de combinación    */
  for(ucI = 0; ucI < ucElementos; ucI++)
  {
    printf("%i ", ucVector[ucI]+1);
  }

  printf("}\n");
}


/******************************************************************************
 * INCREMENTARCOMBINACION
 *
 * Parámetros:
 *   - ucVector:    vector de elementos de la combinación actual.
 *   - ucActual:    posición del elemento actual a incrementar.
 *   - ucElementos: número de elementos a combinar.
 *   - ucElemCombi: número de elementos por combinación.
 *   - ucSalir:     finaliza el recorrido por los elementos.
 ******************************************************************************/
unsigned char incrementarCombinacion(unsigned char *ucVector,
                                     unsigned char ucActual,
                                     unsigned char ucElementos,
                                     unsigned char ucElemCombi,
                                     Boolean bSalir)
{
  /* Si no se debe salir del recorrido                                        */
  if(bSalir == FALSE)
  {
    /* Incremento del valor de la posición actual.                            */
    ucVector[ucActual] = ucVector[ucActual] + 1;

    /* Si no estamos en la posición inicial                                   */
    if(ucActual > 0)
    {
      /* Si el elemento actual ha superado su máximo.                         */
      if(ucVector[ucActual] > ucElementos - (ucElemCombi - ucActual))
      {
        /* Incremento del elemento anterior.                                  */
        bSalir = incrementarCombinacion(ucVector, ucActual - 1, ucElementos,
                                         ucElemCombi, 0);

        /* Actualización del valor del elemento actual.                       */
        ucVector[ucActual] = ucVector[ucActual - 1] + 1;
      }
      /* Si no se ha superado el límite sale de la recursividad.              */
      else
      {
        bSalir = 1;
      }
    }
    /* Si el elemento es el inicial, sale de la recursividad.                 */
    else
    {
      bSalir = 1;
    }
  }

  return bSalir;
}

