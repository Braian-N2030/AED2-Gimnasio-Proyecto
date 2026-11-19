#ifndef persistencia_h
#define persistencia_h

#include "socio.h"

/* Declaracion de prototipos */
void guardarDatos(tListaSocios * pLista);
void cargarDatos(tListaSocios ** pLista, tArbolSocios ** pArbol);
void guardarPilaRecursiva(tPilaRutinas * pPila, FILE * pArchivo);


/* Guardamos la pila desde el fondo hacia la cima para que cuando cargue se quede en el mismo orden */
void guardarPilaRecursiva(tPilaRutinas * pPila, FILE * pArchivo) {
    if (pPila != NULL) {
        guardarPilaRecursiva(pPila->siguiente, pArchivo);
        fwrite(&(pPila->datos), sizeof(tRutina), 1, pArchivo);
    }
}

void guardarDatos(tListaSocios * pLista) {
    FILE * archSocios = fopen("socios.dat", "wb");
    FILE * archRutinas = fopen("rutinas.dat", "wb");
    
    if (archSocios == NULL || archRutinas == NULL) {
        printf("\nNo se puedo abrir.\n");
        if (archSocios != NULL) fclose(archSocios);
        if (archRutinas != NULL) fclose(archRutinas);
        return;
    }
    
    tListaSocios * aux = pLista;
    int cantSocios = 0;
    
    while (aux != NULL) {
        /* 1. Guardamos datos del socio en socios.dat */
        fwrite(&(aux->socio->info), sizeof(tDatosSocio), 1, archSocios);
        
        /* 2. Guardamos el historial de ejercicios del socio en rutinas.dat */
        guardarPilaRecursiva(aux->socio->historial, archRutinas);
        
        cantSocios++;
        aux = aux->siguiente;
    }
    
    fclose(archSocios);
    fclose(archRutinas);
    
    printf("\nDatos guardados correctamente.\n", cantSocios);
}

void cargarDatos(tListaSocios ** pLista, tArbolSocios ** pArbol) {
    FILE * archSocios = fopen("socios.dat", "rb");
    
    if (archSocios == NULL) {
        printf("\nNo se encontro socios.\n");
        return;
    }
    
    tDatosSocio regSocio;
    int cantCargados = 0;

    fread(&regSocio, sizeof(tDatosSocio), 1, archSocios);
    while (!feof(archSocios)) {
        registrarSocio(pLista, pArbol, regSocio);
        cantCargados++;
        fread(&regSocio, sizeof(tDatosSocio), 1, archSocios);
    }
    fclose(archSocios);
    
    FILE * archRutinas = fopen("rutinas.dat", "rb");
    if (archRutinas != NULL) {
        tRutina regRutina;
        tSocio * socioEncontrado;
        
        fread(&regRutina, sizeof(tRutina), 1, archRutinas);
        while (!feof(archRutinas)) {
            socioEncontrado = buscarSocioABB(*pArbol, regRutina.dniSocio);
            if (socioEncontrado != NULL) {
                apilarRutina(&(socioEncontrado->historial), regRutina);
            }
            fread(&regRutina, sizeof(tRutina), 1, archRutinas);
        }
        fclose(archRutinas);
    }
    return;
}

#endif
