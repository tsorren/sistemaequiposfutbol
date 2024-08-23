#include <stdlib.h>
#include <string.h>

#include "files.h"
#include "jugador.h"
#include "render.h"
#include "utils.h"


void moverPunteroA(FILE *archivo, int linea)
{
    fseek(archivo, linea * sizeof(struct un_jugador), SEEK_SET);
}

int calcularCantidadDeJugadores(char *dir_archivo)
{
    FILE *archivo = fopen(dir_archivo, "rb+");
    struct un_jugador aux;
    int cantidad = 0;

    while (fread(&aux, sizeof(struct un_jugador), 1, archivo))
    {
        cantidad++;
    }
    // moveTo(3, 1);
    // printf("Cantidad de jugadores disponibles: %d", cantidad);

    fclose(archivo);
    return cantidad;
}

void ingresarNuevosJugadores(char *dir_archivo, int *cant_j, int padding_x, int *pos_y)
{
    FILE* archivo = fopen(dir_archivo, "rt+");
    int p_X = padding_x + 2;
    int x;

    struct un_jugador jugador;
    int continuar = 1;
    while(continuar != 0)
    {
        x = p_X;
        *pos_y = 2;
        jugador.id = *cant_j;
        mostrarPlantillaCarga(x, *pos_y, *cant_j);

        *pos_y += 2;

        x = p_X + 20;
        moveTo(x, ++(*pos_y));
        scanf("%s", jugador.nombre);
        moveTo(x, ++(*pos_y));
        scanf("%f", &jugador.resistencia);
        moveTo(x, ++(*pos_y));
        scanf("%f", &jugador.velocidad);
        moveTo(x, ++(*pos_y));
        scanf("%f", &jugador.control);
        moveTo(x, ++(*pos_y));
        scanf("%f", &jugador.defensa);
        moveTo(x, ++(*pos_y));
        scanf("%f", &jugador.ataque);
        moveTo(x, ++(*pos_y));
        scanf("%f", &jugador.gambeta);
        moveTo(x, ++(*pos_y));
        scanf("%f", &jugador.cuerpo);
        moveTo(x, ++(*pos_y));
        scanf("%f", &jugador.porteria);
        moveTo(x, ++(*pos_y));
        scanf("%f", &jugador.vision);
        moveTo(x, ++(*pos_y));
        scanf("%f", &jugador.juego_equipo);
        jugador.puntaje_general = calcularPuntaje(jugador);

        *pos_y += 2;
        moveTo(x, *pos_y);
        printf("%.2f", jugador.puntaje_general);

        cargarNuevoJugadorEnArchivo(archivo, jugador, *cant_j);

        (*cant_j)++;

        (*pos_y) += 2;
        moveTo(p_X, *pos_y);
        printf("Continuar carga? (0/1): ");
        scanf("%d", &continuar);
    }
    (*pos_y) += 2;
    fclose(archivo);
}

void cargarNuevoJugadorEnArchivo(FILE *archivo, struct un_jugador j, int cant_j)
{
    moverPunteroA(archivo, cant_j);

    fwrite(&j, sizeof(struct un_jugador), 1, archivo);
    fflush(archivo);
}

void ordenarArchivoJugadores(char *dir_archivo, struct un_jugador** jugadores, int cantidad_jugadores)
{

    ordenarListaDeJugadores(jugadores, cantidad_jugadores);
    
    FILE *archivo = fopen(dir_archivo, "rb+");

    for (int i = 0; i < cantidad_jugadores; i++)
    {
        cargarNuevoJugadorEnArchivo(archivo, (*jugadores)[i], i);
    }
    fclose(archivo);
}

void cargarListaDeJugadores(char *dir_archivo, struct un_jugador *jugadores)
{
    FILE* archivo = fopen(dir_archivo, "rb");

    int contador = 0;
    const int size = sizeof(struct un_jugador);

    while (fread(&jugadores[contador], size, 1, archivo))
    {
        jugadores[contador].puntaje_general = calcularPuntaje(jugadores[contador]);
        contador++;
    }
    fclose(archivo);
}

void modificarArchivoJugadores(char *dir_archivo, struct un_jugador *jugadores, int cantidad_jugadores, int padding_x, int *pos_y)
{
    FILE *archivo = fopen(dir_archivo, "rb+");
    int grabar = 1;
    int continuar = 1;
    int continuar_campos = 1;

    char campo[2] = "";
    int id;
    float *campo_reemplazar;
    char *nombre_reemplazar = NULL;

    while(continuar != 0)
    {
        clearScreen();
        mostrarTablaDeEstadisticas(jugadores, cantidad_jugadores, padding_x, pos_y);
        moveTo(padding_x + 1, *pos_y);
        printf("Ingresar ID: ");
        scanf("%d", &id);
        moveTo(padding_x + 1, *pos_y);
        printf("                                                                ");

        continuar_campos = 1;
        grabar = 1;

        while(continuar_campos != 0)
        {
            nombre_reemplazar = NULL;
            moveTo(padding_x + 1, *pos_y);
            printf("Ingresar campo (N / R / V / C / D / A / G / CU / P / VJ / JE): ");
            scanf("%s", campo);
            moveTo(padding_x + 1, *pos_y);
            printf("                                                                                    ");
            
            if     (!strcmp(campo, "n") || !strcmp(campo, "N")) nombre_reemplazar = jugadores[id].nombre;    
            else if(!strcmp(campo, "r") || !strcmp(campo, "R")) campo_reemplazar = &jugadores[id].resistencia;            
            else if(!strcmp(campo, "v") || !strcmp(campo, "V")) campo_reemplazar = &jugadores[id].velocidad;            
            else if(!strcmp(campo, "c") || !strcmp(campo, "C")) campo_reemplazar = &jugadores[id].control;            
            else if(!strcmp(campo, "d") || !strcmp(campo, "D")) campo_reemplazar = &jugadores[id].defensa;            
            else if(!strcmp(campo, "a") || !strcmp(campo, "A")) campo_reemplazar = &jugadores[id].ataque;            
            else if(!strcmp(campo, "g") || !strcmp(campo, "G")) campo_reemplazar = &jugadores[id].gambeta;            
            else if(!strcmp(campo, "cu") || !strcmp(campo, "CU")) campo_reemplazar = &jugadores[id].cuerpo;            
            else if(!strcmp(campo, "p") || !strcmp(campo, "P")) campo_reemplazar = &jugadores[id].porteria;            
            else if(!strcmp(campo, "vj") || !strcmp(campo, "VJ")) campo_reemplazar = &jugadores[id].vision;            
            else if(!strcmp(campo, "je") || !strcmp(campo, "JE")) campo_reemplazar = &jugadores[id].juego_equipo;
            
            moveTo(padding_x + 1, *pos_y);

            if(nombre_reemplazar != NULL)
            {
                printf("Reemplazar %s por: ", nombre_reemplazar);
                scanf("%s", nombre_reemplazar);
            }
            else
            {
                printf("Reemplazar %.2f por: ", *campo_reemplazar);
                scanf("%f", campo_reemplazar);
            }
            moveTo(padding_x + 1, *pos_y);
            printf("                                                                ");

            jugadores[id].puntaje_general = calcularPuntaje(jugadores[id]);

            moveTo(padding_x + 1, *pos_y);
            printf("Continuar modificando campos? (0 / 1): ");
            scanf("%d", &continuar_campos);
            moveTo(padding_x + 1, *pos_y);
            printf("                                                                ");
            
        }
        moveTo(padding_x + 1, *pos_y);
        printf("Guardar en archivo? (0 / 1): ");
        scanf("%d", &grabar);
        moveTo(padding_x + 1, *pos_y);
        printf("                                                                ");

        if(grabar == 1)
        {
            cargarNuevoJugadorEnArchivo(archivo, jugadores[id], id);
            ordenarArchivoJugadores(dir_archivo, &jugadores, cantidad_jugadores);
        }

        moveTo(padding_x + 1, *pos_y);
        printf("Continuar? (0 / 1): ");
        scanf("%d", &continuar);
        moveTo(padding_x + 1, *pos_y);
        printf("                                                                ");
    }
    fclose(archivo);
}