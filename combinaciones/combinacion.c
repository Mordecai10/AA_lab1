#include "combinacion.h"
#include <stdio.h>

//DECLARACIÓN DE CONSTANTES
#define TRUE 1
#define FALSE 0
typedef unsigned char Boolean;


// DECLARACIÓN DE FUNCIONES
void imprimirCombinacion(unsigned char *conjuntoInicial, unsigned char cantidadElementos);
unsigned char incrementarCombinacion(unsigned char *conjuntoInicial,
                                     unsigned char posicionActual,
                                     unsigned char cantidadElementos,
                                     unsigned char conjuntoR,
                                     Boolean salir);


int combinacion(int numeroElementos,int numeroR)
{
  unsigned char conjuntoInicial[numeroElementos];     /* Vector de elementos a ordenar */
  unsigned char aux;                                  /* Contador para los bucles      */
  unsigned char cantidadElementos;                    /* Número total de elementos     */
  unsigned char conjuntoR;                            /* Elementos por combinación     */
  Boolean salir;                                      /* Indica si se sale del bucle   */

  /* Inicialización de variables                                              */
  cantidadElementos = numeroElementos;
  conjuntoR = numeroR;
  salir = FALSE;

  /* Relleno de los elementos iniciales del vector.                           */
  for(aux = 0; aux < cantidadElementos; aux++)
  {
    conjuntoInicial[aux] = aux;
  }

  /* Impresión de los elementos iniciales del vector                          */
  imprimirCombinacion(conjuntoInicial, conjuntoR);

  /* Se repite mientras no se indique que se debe salir del bucle             */
  while(salir == FALSE)
  {
    /* Paso a la siguiente combinación. El valor de la variable salir no se  */
    /* tiene en cuenta ya que siempre será True.                              */
    salir = incrementarCombinacion(conjuntoInicial, conjuntoR - 1, cantidadElementos,
                                    conjuntoR, 0);

    /* Si el primer elemento se ha salido del rango del vector, la            */
    /* combinación ya no es válida. Por lo que se ha recorrido la lista de    */
    /* combinaciones al completo.                                             */
    if(conjuntoInicial[0] > (cantidadElementos - conjuntoR))
    {
      salir = TRUE;
    }
    /* En caso contrario se muestra la combinación actual por pantalla        */
    else
    {
      imprimirCombinacion(conjuntoInicial, conjuntoR);
      salir = FALSE;
    }
  }

  return 0;
}

//IMPRIMIRCOMBINACION
void imprimirCombinacion(unsigned char *conjuntoInicial, unsigned char cantidadElementos)
{
  unsigned char aux;                            /* Contador para el bucle for */

  printf("Combinacion: { ");

  /* Impresión de todos los elementos necesarios del vector de combinación    */
  for(aux = 0; aux < cantidadElementos; aux++)
  {
    printf("%i ", conjuntoInicial[aux]+1);
  }

  printf("}\n");
}


/*INCREMENTARCOMBINACION
 * Parámetros:
 *   - conjuntoInicial:    vector de elementos de la combinación actual.
 *   - posicionActual:    posición del elemento actual a incrementar.
 *   - cantidadElementos: número de elementos a combinar.
 *   - conjuntoR: número de elementos por combinación.
 *   - salir:     finaliza el recorrido por los elementos.
 ******************************************************************************/
unsigned char incrementarCombinacion(unsigned char *conjuntoInicial,
                                     unsigned char posicionActual,
                                     unsigned char cantidadElementos,
                                     unsigned char conjuntoR,
                                     Boolean salir)
{
  /* Si no se debe salir del recorrido                                        */
  if(salir == FALSE)
  {
    /* Incremento del valor de la posición actual.                            */
    conjuntoInicial[posicionActual] = conjuntoInicial[posicionActual] + 1;

    /* Si no estamos en la posición inicial                                   */
    if(posicionActual > 0)
    {
      /* Si el elemento actual ha superado su máximo.                         */
      if(conjuntoInicial[posicionActual] > cantidadElementos - (conjuntoR - posicionActual))
      {
        /* Incremento del elemento anterior.                                  */
        salir = incrementarCombinacion(conjuntoInicial, posicionActual - 1, cantidadElementos,
                                         conjuntoR, 0);

        /* Actualización del valor del elemento actual.                       */
        conjuntoInicial[posicionActual] = conjuntoInicial[posicionActual - 1] + 1;
      }
      /* Si no se ha superado el límite sale de la recursividad.              */
      else
      {
        salir = 1;
      }
    }
    /* Si el elemento es el inicial, sale de la recursividad.                 */
    else
    {
      salir = 1;
    }
  }

  return salir;
}

.
