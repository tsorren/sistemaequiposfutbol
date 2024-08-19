#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "utils.h"
#include "render.h"
#include "files.h"
#include "jugador.h"

void elegirJugadores(struct un_jugador***, struct un_jugador*, const int, int*);
void elegirEquiposManualmente(struct un_equipo*, struct un_equipo*, int,  struct un_jugador**);

int main(void)
{
    const char dir_archivo[] = "jugadores.csv";
    FILE *archivo_jugadores;
    int cantidad_jugadores;
    struct un_jugador *jugadores;
    struct un_jugador **jugadores_disponibles;
    struct un_equipo equipo1, equipo2;

    int input = 0;
    int tam_equipo = 0;
    int pos_y;

    setupTerminal();
    inicioDeSistema(&input);
    while(input != 99)
    {
        pos_y = 0;
        archivo_jugadores = fopen(dir_archivo, "rt");
        cantidad_jugadores = calcularCantidadDeJugadores(archivo_jugadores);
        jugadores = malloc(cantidad_jugadores * sizeof(struct un_jugador));
        cargarListaDeJugadores(archivo_jugadores, jugadores);
        ordenarListaDeJugadores(&jugadores, cantidad_jugadores);
        fclose(archivo_jugadores);

        if(input == 3)
        {
            ingresarNuevosJugadores(archivo_jugadores, dir_archivo, &cantidad_jugadores);

            free(jugadores);
            jugadores = malloc(cantidad_jugadores * sizeof(struct un_jugador));

            archivo_jugadores = fopen(dir_archivo, "rt");
            cargarListaDeJugadores(archivo_jugadores, jugadores);
            ordenarListaDeJugadores(&jugadores, cantidad_jugadores);
            fclose(archivo_jugadores);
        }

        _sleep(1000);
        clearScreen();

        mostrarListadoJugadores(jugadores, cantidad_jugadores, tam_equipo, &pos_y);

        moveTo(3, pos_y);
        printf("Ingrese el tamaño de los equipos: ");
        scanf("%d", &tam_equipo);
        moveTo(3, pos_y);
        printf("                                      ");

        jugadores_disponibles = malloc(tam_equipo * 2 * sizeof(struct un_jugador *));

        elegirJugadores(&jugadores_disponibles, jugadores, tam_equipo * 2, &pos_y);

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
        mostrarEquipos(equipos, tam_equipo);
        moveTo(3, pos_y);

        free(jugadores);
        free(jugadores_disponibles);
        free(equipo1.jugadores);
        free(equipo2.jugadores);
        _sleep(1500);
        _getch();
        inicioDeSistema(&input);
    }
    clearScreen();
    return 0;
}
void elegirJugadores(struct un_jugador ***jugadores_disponibles, struct un_jugador *jugadores, const int cant_jugadores, int* pos_y)
{
    int indice_jugador = 0;
    int contador = 0;

    moveTo(3, *pos_y);
    printf("Elija ");
    setColor(FGRN, BBLK);
    printf("%d", cant_jugadores - contador);
    setColor(FWHT, BBLK);
    printf(" jugadores: ");
    scanf("%d", &indice_jugador);
    while (contador < cant_jugadores && indice_jugador > -1)
    {
        (*jugadores_disponibles)[contador] = &jugadores[indice_jugador];
        jugadorFueElegido(indice_jugador);
        moveTo(3, *pos_y);
        printf("                        ");
        contador++;
        if (contador < cant_jugadores)
        {
            moveTo(3, *pos_y);
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