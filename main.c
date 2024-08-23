#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "utils.h"
#include "render.h"
#include "files.h"
#include "jugador.h"

void elegirJugadores(struct un_jugador***, struct un_jugador*, const int, int, int, int*);
void elegirEquiposManualmente(struct un_equipo*, struct un_equipo*, int,  struct un_jugador**);

int main(void)
{
    const char dir_archivo[] = "jugadores.dat";
    int cantidad_jugadores;
    struct un_jugador *jugadores;
    struct un_jugador **jugadores_disponibles;
    struct un_equipo equipo1, equipo2;

    int input = -1;
    int tam_equipo = 0;
    int pos_y;
    int padding_x = 10;
    int padding_y = 2;
    // old padding = 3;

    setupTerminal();
    inicioDeSistema(&input);
    _sleep(500);
    clearScreen();
    showCursor();
    while(input != 0)
    {
        clearScreen();
        pos_y = padding_y;
        cantidad_jugadores = calcularCantidadDeJugadores(dir_archivo);
        jugadores = malloc(cantidad_jugadores * sizeof(struct un_jugador));
        if(cantidad_jugadores > 0)
        {
            cargarListaDeJugadores(dir_archivo, jugadores);
            ordenarArchivoJugadores(dir_archivo, &jugadores, cantidad_jugadores);
        }

        if(input == 1 || input == 2)
        {
            // moveTo(padding_x + 2, 3);
            // printf("Cant: %d", cantidad_jugadores);
            
            mostrarListadoJugadores(jugadores, cantidad_jugadores, tam_equipo, padding_x, &pos_y);

            moveTo(padding_x + 1, pos_y);
            printf("Ingrese el tamaño de los equipos: ");
            scanf("%d", &tam_equipo);
            moveTo(padding_x, pos_y);
            printf("                                      ");

            jugadores_disponibles = malloc(tam_equipo * 2 * sizeof(struct un_jugador *));

            elegirJugadores(&jugadores_disponibles, jugadores, tam_equipo * 2, padding_x, padding_y, &pos_y);

            equipo1.num = 0;
            equipo1.probabilidadGanar = 0;
            equipo1.promedio = 0;
            equipo1.varianza = 0;

            equipo2.num = 0;
            equipo2.probabilidadGanar = 0;
            equipo2.promedio = 0;
            equipo2.varianza = 0;

            equipo1.jugadores = malloc(tam_equipo * sizeof(struct un_jugador*));
            equipo2.jugadores = malloc(tam_equipo * sizeof(struct un_jugador*));


            if (input == 1)
            {
                generarEquiposBalanceadamente(jugadores_disponibles, &equipo1, &equipo2, tam_equipo * 2);
            }
            else if (input == 2)
            {
                elegirEquiposManualmente(&equipo1, &equipo2, tam_equipo, jugadores_disponibles);
                calcularProbabilidadDeGanar(&equipo1, &equipo2, tam_equipo);
            }
            struct un_equipo equipos[2] = {equipo1, equipo2};

            //float probabilidadDeGanar = 
            mostrarEquipos(equipos, tam_equipo, padding_x, padding_y);
            free(jugadores);
            free(jugadores_disponibles);
            free(equipo1.jugadores);
            free(equipo2.jugadores);
        }
        else if(input == 3)
        {
            ingresarNuevosJugadores(dir_archivo, &cantidad_jugadores, padding_x, &pos_y);

            free(jugadores);
            jugadores = malloc(cantidad_jugadores * sizeof(struct un_jugador));

            // archivo_jugadores = fopen(dir_archivo, "rt");
            // cargarListaDeJugadores(archivo_jugadores, jugadores);
            // ordenarListaDeJugadores(&jugadores, cantidad_jugadores);
            // fclose(archivo_jugadores);
        }
        else if(input == 4)
        {
            clearScreen();
            modificarArchivoJugadores(dir_archivo, jugadores, cantidad_jugadores, padding_x, &pos_y);
        }

        moveTo(padding_x + 1, pos_y);
        _sleep(500);
        printf("Volver al menú...");
        _sleep(500);
        getch();

        inicioDeSistema(&input);
    }
    clearScreen();
    return 0;
}

void elegirJugadores(struct un_jugador ***jugadores_disponibles, struct un_jugador *jugadores, const int cant_jugadores, int padding_x, int padding_y, int* pos_y)
{
    int indice_jugador = 0;
    int contador = 0;

    moveTo(padding_x + 1, *pos_y);
    printf("Elija ");
    setColor(FGRN, BBLK);
    printf("%d", cant_jugadores - contador);
    setColor(FWHT, BBLK);
    printf(" jugadores: ");
    scanf("%d", &indice_jugador);
    while (contador < cant_jugadores && indice_jugador > -1)
    {
        (*jugadores_disponibles)[contador] = &jugadores[indice_jugador];
        jugadorFueElegido(indice_jugador, padding_x + 4, padding_y + 9);
        moveTo(padding_x, *pos_y);
        printf("                        ");
        contador++;
        if (contador < cant_jugadores)
        {
            moveTo(padding_x, *pos_y);
            printf("Elija ");
            setColor(FGRN, BBLK);
            printf("%d", cant_jugadores - contador);
            setColor(FWHT, BBLK);
            printf(" jugadores: ");
            scanf("%d", &indice_jugador);
        }
    }
    printf("\n");
}

void elegirEquiposManualmente(struct un_equipo *eq1, struct un_equipo *eq2, int tam, struct un_jugador **j_disp)
{    
    for (int i = 0; i < tam; i++)
    {
        eq1->jugadores[i] = j_disp[i];
        eq2->jugadores[i] = j_disp[i + tam];
        
        eq1->num = 0;
        eq2->num = 1;
    }
}