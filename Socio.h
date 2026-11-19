#ifndef SOCIO_H
#define SOCIO_H

#include "rutina.h"

/* Datos del socio */
typedef struct {
    int dni;
    tString nombre;
    int edad;
    float peso;
    float altura;
    tString objetivo;
    bool cuotaAlDia;
} tDatosSocio;


typedef struct {
    tDatosSocio info;
    tPilaRutinas * historial;
} tSocio;


typedef struct nodoLista {
    tSocio * socio;
    struct nodoLista * siguiente;
} tListaSocios;


typedef struct nodoArbol {
    tSocio * socio;
    struct nodoArbol * hijoIzq;
    struct nodoArbol * hijoDer;
} tArbolSocios;



/* Inicializacion  */
void inicializarLista(tListaSocios ** pLista);
bool listaVacia(tListaSocios * pLista);
void crearArbol(tArbolSocios ** pArbol);
bool arbolVacio(tArbolSocios * pArbol);


tSocio * crearSocioEnMemoria(tDatosSocio pDatos);
void insertarEnLista(tListaSocios ** pLista, tSocio * pSocio);
void insertarEnArbol(tArbolSocios ** pArbol, tSocio * pSocio);
bool registrarSocio(tListaSocios ** pLista, tArbolSocios ** pArbol, tDatosSocio pDatos);

/* Busqueda  por el dni */
tSocio * buscarSocioABB(tArbolSocios * pArbol, int pDni);

/* Elimino al Socio y despues libero la memoria) */
tArbolSocios * minimoElemento(tArbolSocios * pArbol);
void eliminarDeArbol(tArbolSocios ** pArbol, int pDni);
void eliminarDeLista(tListaSocios ** pLista, int pDni);
bool darDeBajaSocio(tListaSocios ** pLista, tArbolSocios ** pArbol, int pDni);

/* Ordenamos por insercion directa */
int contarSocios(tListaSocios * pLista);
void insercionDirecta(tSocio * pVector[], int pCant);
void listarSociosOrdenadosPorNombre(tListaSocios * pLista);

/* Visualizamos al socio y despues libero la memoria*/
void mostrarUnSocio(tSocio * pSocio);
void listarSocios(tListaSocios * pLista);
void liberarEstructuras(tListaSocios ** pLista, tArbolSocios ** pArbol);

/* Implementacion de de la funciones */

void inicializarLista(tListaSocios ** pLista) {
    *pLista = NULL;
}

bool listaVacia(tListaSocios * pLista) {
    return (pLista == NULL);
}

void crearArbol(tArbolSocios ** pArbol) {
    *pArbol = NULL;
}

bool arbolVacio(tArbolSocios * pArbol) {
    return (pArbol == NULL);
}

tSocio * crearSocioEnMemoria(tDatosSocio pDatos) {
    tSocio * nuevoSocio = (tSocio *) malloc(sizeof(tSocio));
    if (nuevoSocio != NULL) {
        nuevoSocio->info = pDatos;
        inicializarPila(&(nuevoSocio->historial));
    }
    return nuevoSocio;
}

void insertarEnLista(tListaSocios ** pLista, tSocio * pSocio) {
    tListaSocios * nuevoNodo;
    nuevoNodo = (tListaSocios *) malloc(sizeof(tListaSocios));
    
    if (nuevoNodo != NULL) {
        nuevoNodo->socio = pSocio;
        nuevoNodo->siguiente = *pLista;
    
        *pLista = nuevoNodo;
    }
}

void insertarEnArbol(tArbolSocios ** pArbol, tSocio * pSocio) {
    
	if (arbolVacio(*pArbol)) {
        *pArbol = (tArbolSocios *) malloc(sizeof(tArbolSocios));
        
	if (*pArbol != NULL) {
            (*pArbol)->socio = pSocio;
            (*pArbol)->hijoIzq = NULL;
            (*pArbol)->hijoDer = NULL;
        }
    }
	
	else if (pSocio->info.dni < (*pArbol)->socio->info.dni) {
            insertarEnArbol(&((*pArbol)->hijoIzq), pSocio);
        }
		
		else if (pSocio->info.dni > (*pArbol)->socio->info.dni) {
                insertarEnArbol(&((*pArbol)->hijoDer), pSocio);
            }  
}

bool registrarSocio(tListaSocios ** pLista, tArbolSocios ** pArbol, tDatosSocio pDatos) {
    /* aca vamos  verificamos  si el DNi  del socio ya existe para evitar duplicados */
    if (buscarSocioABB(*pArbol, pDatos.dni) != NULL) {
        return false;
    }
    
    tSocio * nuevoSocio = crearSocioEnMemoria(pDatos);
    if (nuevoSocio == NULL) {
        return false;
    }

    insertarEnLista(pLista, nuevoSocio);
    insertarEnArbol(pArbol, nuevoSocio);
    
    return true;
}

tSocio * buscarSocioABB(tArbolSocios * pArbol, int pDni) {
   
    if (arbolVacio(pArbol)) {
        return NULL;
    } 
	
		else if (pDni < pArbol->socio->info.dni) {
            return buscarSocioABB(pArbol->hijoIzq, pDni);
        } 
		
		else if (pDni > pArbol->socio->info.dni) {
                return buscarSocioABB(pArbol->hijoDer, pDni);
            } 
			
			else {
                return pArbol->socio;
            }  
}

tArbolSocios * minimoElemento(tArbolSocios * pArbol) {
    if (arbolVacio(pArbol)) {
        return NULL;
        
    } else if (pArbol->hijoIzq != NULL) {
            return minimoElemento(pArbol->hijoIzq);
        } else {
            return pArbol;
        }
    
}

void eliminarDeArbol(tArbolSocios ** pArbol, int pDni) {
    
	tArbolSocios * aux;
    
    if (!arbolVacio(*pArbol)) {
        if (pDni < (*pArbol)->socio->info.dni) {
            eliminarDeArbol(&((*pArbol)->hijoIzq), pDni);
            
        } 
		
		else if (pDni > (*pArbol)->socio->info.dni) {
                eliminarDeArbol(&((*pArbol)->hijoDer), pDni);
        
		} 
		
		else if ((*pArbol)->hijoIzq == NULL) {
                    aux = *pArbol;
                    *pArbol = (*pArbol)->hijoDer;
                    free(aux);
    	
		}
		
		else if ((*pArbol)->hijoDer == NULL) {
                        aux = *pArbol;
                        *pArbol = (*pArbol)->hijoIzq;
                        free(aux);
        } 
					
		else {
            aux = minimoElemento((*pArbol)->hijoDer);
            (*pArbol)->socio = aux->socio;
            eliminarDeArbol(&((*pArbol)->hijoDer), (*pArbol)->socio->info.dni);
        }
    }
}

void eliminarDeLista(tListaSocios ** pLista, int pDni) {
    tListaSocios * actual = *pLista;
    tListaSocios * anterior = NULL;
    
    while (actual != NULL && actual->socio->info.dni != pDni) {
        anterior = actual;
        actual = actual->siguiente;
    }
    
    
    if (actual != NULL) {
        if (anterior == NULL) {
          
            *pLista = actual->siguiente;
        } else {
            anterior->siguiente = actual->siguiente;
        }
        free(actual);
    }
}

bool darDeBajaSocio(tListaSocios ** pLista, tArbolSocios ** pArbol, int pDni) {
    tSocio * socioEliminar = buscarSocioABB(*pArbol, pDni);
    
    if (socioEliminar == NULL) {
        return false;
    }
    

    eliminarDeArbol(pArbol, pDni);
    eliminarDeLista(pLista, pDni);
    
    liberarPila(&(socioEliminar->historial));
    free(socioEliminar);
    
    return true;
}

int contarSocios(tListaSocios * pLista) {
    int contador = 0;
    tListaSocios * aux = pLista;
    
    while (aux != NULL) {
        contador++;
        aux = aux->siguiente;
    }
    return contador;
}

void insercionDirecta(tSocio * pVector[], int pCant) {
    int i, j;
    tSocio * aux;
    
    for (i = 1; i < pCant; i++) {
        aux = pVector[i];
        j = i - 1;
        
        while ((j >= 0) && (strcmp(pVector[j]->info.nombre, aux->info.nombre) > 0)) {
            pVector[j + 1] = pVector[j];
            j = j - 1;
        }
        
        pVector[j + 1] = aux;
    }
}

void listarSociosOrdenadosPorNombre(tListaSocios * pLista) {
    int cant = contarSocios(pLista);
    
    if (cant == 0) {
        printf("\nNo hay socios registrados.\n");
        return;
    }
    
    tSocio ** vectorAux = (tSocio **) malloc(cant * sizeof(tSocio *));
    if (vectorAux == NULL) {
        printf("\nError no se puedo asignar la memoria para ordenar.\n");
        return;
    }
    
    tListaSocios * aux = pLista;
    int i = 0;
    while (aux != NULL) {
        vectorAux[i] = aux->socio;
        aux = aux->siguiente;
        i++;
    }
    
    insercionDirecta(vectorAux, cant);
    
    printf("\n*** SOCIOS ORDENADOS ALFABETICAMENTE ***\n");
    for (i = 0; i < cant; i++) {
        mostrarUnSocio(vectorAux[i]);
    }
    free(vectorAux);
}

void mostrarUnSocio(tSocio * pSocio) {
    if (pSocio != NULL) {
        printf("DNI: %d | Nombre: %s | Edad: %d | Peso: %.1f kg | Altura: %.2f m | Objetivo: %s | Cuota: %s\n",
               pSocio->info.dni,
               pSocio->info.nombre,
               pSocio->info.edad,
               pSocio->info.peso,
               pSocio->info.altura,
               pSocio->info.objetivo,
               pSocio->info.cuotaAlDia ? "Al dia" : "Adeuda");
    }
}

void listarSocios(tListaSocios * pLista) {
    if (listaVacia(pLista)) {
        printf("\nNo hay socios cargados \n");
    } else {
        tListaSocios * aux = pLista;
        printf("\n*** LISTA GENERAL DE SOCIOS ***\n");
        while (aux != NULL) {
            mostrarUnSocio(aux->socio);
            aux = aux->siguiente;
        }
    }
}

void liberarArbolSoloNodos(tArbolSocios ** pArbol) {
    if (!arbolVacio(*pArbol)) {
        liberarArbolSoloNodos(&((*pArbol)->hijoIzq));
        liberarArbolSoloNodos(&((*pArbol)->hijoDer));
        free(*pArbol);
        *pArbol = NULL;
    }
}

void liberarEstructuras(tListaSocios ** pLista, tArbolSocios ** pArbol) {

    liberarArbolSoloNodos(pArbol);
    
    tListaSocios * aux;
    while (*pLista != NULL) {
        aux = *pLista;
        *pLista = (*pLista)->siguiente;
        
        liberarPila(&(aux->socio->historial));
        free(aux->socio);
        free(aux);
    }
}

#endif
