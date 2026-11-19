#include "persistencia.h"

/* Guarda datos de socio nuevo */
void leerDatosSocio(tDatosSocio * pDatos) {
    char opcion;
    printf("\n--- NUEVO SOCIO ---\n");
    printf("DNI: ");
    scanf("%d", &pDatos->dni);
    printf("Nombre y apellido: ");
    scanf(" %[^\n]", pDatos->nombre);
    printf("Edad: ");
    scanf("%d", &pDatos->edad);
    printf("Peso (kg): ");
    scanf("%f", &pDatos->peso);
    printf("Altura (m): ");
    scanf("%f", &pDatos->altura);
    printf("Objetivo: ");
    scanf(" %[^\n]", pDatos->objetivo);
    printf("Cuota al dia? (s/n): ");
    scanf(" %c", &opcion);
    pDatos->cuotaAlDia = (opcion == 's' || opcion == 'S');
}
/* Guarda rutina de un socio */
void leerRutina(tRutina * pRutina, int pDni) {
    printf("\n--- NUEVA RUTINA ---\n");
    pRutina->dniSocio = pDni;
    printf("Nombre del ejercicio: ");
    scanf(" %[^\n]", pRutina->nombreEjercicio);
    printf("Grupo muscular: ");
    scanf(" %[^\n]", pRutina->grupoMuscular);
    printf("Series: ");
    scanf("%d", &pRutina->series);
    printf("Repeticiones: ");
    scanf("%d", &pRutina->repeticiones);
}
/* Busca rutina de un socio */
void mostrarRutina(const tRutina * pRutina) {
    if (pRutina->dniSocio == 0) {
        printf("\nEl socio no tiene rutinas registradas.\n");
    } else {
        printf("\nEjercicio: %s | Grupo: %s | %d x %d\n",
               pRutina->nombreEjercicio,
               pRutina->grupoMuscular,
               pRutina->series,
               pRutina->repeticiones);
    }
}
/* Busca a un socio */
tSocio * pedirSocio(tArbolSocios * pArbol) {
    int dni;
    tSocio * socio;
    printf("\nDNI del socio: ");
    scanf("%d", &dni);
    socio = buscarSocioABB(pArbol, dni);
    if (socio == NULL) {
        printf("\nNo existe un socio con DNI %d\n", dni);
    }
    return socio;
}
/* Muestra el menu en pantalla */
void mostrarMenu(void) {
    printf("\n=====================================\n");
    printf("   SISTEMA DE REGISTRO DE GIMNASIO\n");
    printf("=====================================\n");
    printf(" 1. Registrar socio\n\n");
    printf(" 2. Listar todos los socios\n\n");
    printf(" 3. Listar socios ordenados por nombre\n\n");
    printf(" 4. Buscar socio por DNI\n\n");
    printf(" 5. Dar de baja socio\n\n");
    printf(" 6. Agregar rutina a un socio\n\n");
    printf(" 7. Ver historial de rutinas de un socio\n\n");
    printf(" 8. Ver ultima rutina de un socio\n\n");
    printf(" 9. Eliminar ultima rutina de un socio\n\n");
    printf("10. Guardar datos en disco\n\n");
    printf(" 0. Salir\n");
    printf("-------------------------------------\n");
    printf("Opcion: ");
}


/* MENU PRINCIPAL */
int main(void) {
    tListaSocios * lista;
    tArbolSocios * arbol;
    int opcion = -1;
    inicializarLista(&lista);
    crearArbol(&arbol);
    /* Carga automaticamente los datos desde disco */
    cargarDatos(&lista, &arbol);
    while (opcion != 0) {
        mostrarMenu();
        scanf("%d", &opcion);
        switch (opcion) {

            case 1: {
                tDatosSocio datos;
                leerDatosSocio(&datos);
                if (registrarSocio(&lista, &arbol, datos)) {
                    printf("\nSocio registrado correctamente.\n");
                    /* Guarda automaticamente el nuevo socio */
                    guardarDatos(lista);
                } else {
                    printf("\nNo se pudo registrar: DNI duplicado o sin memoria.\n");
                }
                break;
            }

            case 2:
                listarSocios(lista);
                break;

            case 3:
                listarSociosOrdenadosPorNombre(lista);
                break;

            case 4: {
                tSocio * socio;
                socio = pedirSocio(arbol);
                if (socio != NULL) {
                    mostrarUnSocio(socio);
                }
                break;
            }

            case 5: {
                int dni;
                printf("\nDNI a dar de baja: ");
                scanf("%d", &dni);
                if (darDeBajaSocio(&lista, &arbol, dni)) {
                	eliminarDeLista(&lista, dni);
                	guardarDatos(lista);
                    printf("\nSocio dado de baja correctamente.\n");
                } else {
                    printf("\nNo se encontro el socio.\n");
                }
                break;
            }

            case 6: {
                tSocio * socio;
                socio = pedirSocio(arbol);
                if (socio != NULL) {
                    tRutina rutina;
                    leerRutina(&rutina, socio->info.dni);
                    apilarRutina(&(socio->historial), rutina);
                    /* Guarda automaticamente la nueva rutina */
                    guardarDatos(lista);
                    printf("\nRutina agregada al historial.\n");
                }
                break;
            }

            case 7: {
                tSocio * socio;
                socio = pedirSocio(arbol);
                if (socio != NULL) {
                    mostrarUnSocio(socio);
                    mostrarHistorialRutinas(socio->historial);
                }
                break;
            }

            case 8: {
                tSocio * socio;
                socio = pedirSocio(arbol);
                if (socio != NULL) {
                    tRutina ultima;
                    ultima = verUltimaRutina(socio->historial);
                    mostrarRutina(&ultima);
                }
                break;
            }

            case 9: {
                tSocio * socio;
                socio = pedirSocio(arbol);
                if (socio != NULL) {
                    desapilarRutina(&(socio->historial));
                    guardarDatos(lista);
                }
                break;
            }

            case 10:
                guardarDatos(lista);
                printf("\nDatos guardados correctamente.\n");
                break;

            case 0:
                printf("\nCerrando el sistema...\n");
                break;

            default:
                printf("\nOpcion invalida. Intente nuevamente.\n");
        }
    }

    liberarEstructuras(&lista, &arbol);

    return 0;
}

