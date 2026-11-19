#ifndef RUTINA_H
#define RUTINA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Declaracion de datos personalizados */
typedef char tString[80];

typedef struct {
    int dniSocio;
    tString nombreEjercicio;
    tString grupoMuscular;
    int series;
    int repeticiones;
} tRutina;


typedef struct nodoRutina {
    tRutina datos;
    struct nodoRutina * siguiente;
} tPilaRutinas;

/* Declaracion de los  prototiposs */
void inicializarPila(tPilaRutinas ** pPila);
bool pilaVacia(tPilaRutinas * pPila);
void apilarRutina(tPilaRutinas ** pPila, tRutina pRutina);
void desapilarRutina(tPilaRutinas ** pPila);
void mostrarHistorialRutinas(tPilaRutinas * pPila);
tRutina verUltimaRutina(tPilaRutinas * pPila);
void liberarPila(tPilaRutinas ** pPila);

/* Implementacion de las funciones */
void inicializarPila(tPilaRutinas ** pPila) {
    *pPila = NULL;
}

bool pilaVacia(tPilaRutinas * pPila) {
    return (pPila == NULL);
}

void apilarRutina(tPilaRutinas ** pPila, tRutina pRutina) {
	
    tPilaRutinas * nuevoNodo;
	nuevoNodo = (tPilaRutinas *) malloc(sizeof(tPilaRutinas));
	
	
    nuevoNodo->datos = pRutina;
     nuevoNodo->siguiente = *pPila;
	*pPila = nuevoNodo;
}

void desapilarRutina(tPilaRutinas ** pPila) {
    if (!pilaVacia(*pPila)) {

        tPilaRutinas * suprimirNodo;
        suprimirNodo = *pPila;

        *pPila = (*pPila)->siguiente;
        printf("Se elimino el ejercicio %s.\n", 
               suprimirNodo->datos.nombreEjercicio, 
               suprimirNodo->datos.grupoMuscular);
        free(suprimirNodo);
        suprimirNodo = NULL;
    } 
	else {
        printf("El historial de ejercicios esta vacío.\n");
    }
}

void mostrarHistorialRutinas(tPilaRutinas * pPila) {
    if (pilaVacia(pPila)) {
        printf("El socio no tiene ejercicios cargados.\n");
    } else {
        tPilaRutinas * aux = pPila;
        printf("\n*** Historial de ejercicios ***\n");
        printf("Ejercicio | Grupo muscular | Series y Repeticiones\n");
        printf("------------------------------------------------------\n");
        while (aux != NULL) {
            printf("%s | %s | %d x %d\n", 
                   aux->datos.nombreEjercicio, 
                   aux->datos.grupoMuscular, 
                   aux->datos.series, 
                   aux->datos.repeticiones);
            aux = aux->siguiente; 
        }
    }
}

tRutina verUltimaRutina(tPilaRutinas * pPila) {
    tRutina rutinaVacia;
    rutinaVacia.dniSocio = 0;
    strcpy(rutinaVacia.nombreEjercicio, " ");
    strcpy(rutinaVacia.grupoMuscular, " ");
    rutinaVacia.series = 0;
    rutinaVacia.repeticiones = 0;

    if (pilaVacia(pPila)) {
        return rutinaVacia;
    } else {
        return pPila->datos;
    }
}

void liberarPila(tPilaRutinas ** pPila) {
    tPilaRutinas * aux;
    while (*pPila != NULL) {
        aux = *pPila;
        *pPila = (*pPila)->siguiente;
        free(aux);
        aux = NULL;
    }
}

#endif
