#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#include "render.h"
#include "utils.h"
#include "jugador.h"

void inicioDeSistema(int *input)
{
    clearScreen();

    printf("\n\n");
    
    printf("                                                      +-------------------------------------------------------------+\n");
    printf("                                                      |   ____ ___ ____ _____ _____ __  __    _       ____  _____   |\n");
    printf("                                                      |  / ___|_ _/ ___|_   _| ____|  \\/  |  / \\     |  _ \\| ____|  |\n");
    printf("                                                      |  \\___ \\| |\\___ \\ | | |  _| | |\\/| | / _ \\    | | | |  _|    |\n");
    printf("                                                      |   ___) | | ___) || | | |___| |  | |/ ___ \\   | |_| | |___   |\n");
    printf("                                                      |  |____/___|____/ |_| |_____|_|  |_/_/   \\_\\  |____/|_____|  |\n");
    printf("                                                      |     ____ _____ ____ _____ ___ ___  _   _    ____  _____     |\n");
    printf("                                                      |    / ___| ____/ ___|_   _|_ _/ _ \\| \\ | |  |  _ \\| ____|    |\n");
    printf("                                                      |   | |  _|  _| \\___ \\ | |  | | | | |  \\| |  | | | |  _|      |\n");
    printf("                                                      |   | |_| | |___ ___) || |  | | |_| | |\\  |  | |_| | |___     |\n");
    printf("                                                      |    \\____|_____|____/ |_| |___\\___/|_| \\_|  |____/|_____|    |\n");
    printf("                                                      |           _____ ___  _   _ ___ ____   ___  ____             |\n");
    printf("                                                      |          | ____/ _ \\| | | |_ _|  _ \\ / _ \\/ ___|            |\n");
    printf("                                                      |          |  _|| | | | | | || || |_) | | | \\___ \\            |\n");
    printf("                                                      |          | |__| |_| | |_| || ||  __/| |_| |___) |           |\n");
    printf("                                                      |          |_____\\__\\_\\\\___/|___|_|    \\___/|____/            |\n");
    printf("                                                      |                                                             |\n");
    printf("                                                      +-------------------------------------------------------------+\n");
    printf("                                                      |                                                             |\n");
    printf("                                                      |         ___  ____   ____ ___ ___  _   _ _____ ____          |\n");
    printf("                                                      |        / _ \\|  _ \\ / ___|_ _/ _ \\| \\ | | ____/ ___|         |\n");
    printf("                                                      |       | | | | |_) | |    | | | | |  \\| |  _| \\___ \\         |\n");
    printf("                                                      |       | |_| |  __/| |___ | | |_| | |\\  | |___ ___) |        |\n");
    printf("                                                      |        \\___/|_|    \\____|___\\___/|_| \\_|_____|____/         |\n");
    printf("                                                      |                                                             |\n");
    printf("                                                      |                                                             |\n");
    printf("                                                      |  +-------+-----------------------------------------------+  |\n");
    printf("                                                      |  |   1   |       Generar  Equipos  Balanceadamente       |  |\n");
    printf("                                                      |  +-------+-----------------------------------------------+  |\n");
    printf("                                                      |  |   2   |         Evaluar  Balance  de  Equipos         |  |\n");
    printf("                                                      |  +-------+-----------------------------------------------+  |\n");
    printf("                                                      |  |   3   |           Añadir  Nuevos  Jugadores           |  |\n");
    printf("                                                      |  +-------+-----------------------------------------------+  |\n");
    printf("                                                      |  |   4   |             Modificar  Jugadores              |  |\n");
    printf("                                                      |  +-------+-----------------------------------------------+  |\n");
    printf("                                                      |                                                             |\n");
    printf("                                                      |  +-------+-----------------------------------------------+  |\n");
    printf("                                                      |  |   0   |                   S A L I R                   |  |\n");
    printf("                                                      |  +-------+-----------------------------------------------+  |\n");
    printf("                                                      |                                                             |\n");
    printf("                                                      +-------------------------------------------------------------+\n");


    *input = getch() - 48;
}
void mostrarPlantillaCarga(int p_X, int y, int cant_j)
{
    moveTo(p_X, y);
    printf("+---------------------------------+");
    moveTo(p_X, ++y);
    printf("| C A R G A N D O   J U G A D O R |");    
    moveTo(p_X, ++y);
    printf("+-----------------+---------------+");
    moveTo(p_X, ++y);
    printf("| Nombre          |               |");
    moveTo(p_X, ++y);
    printf("| Resistencia     |               |");
    moveTo(p_X, ++y);
    printf("| Velocidad       |               |");
    moveTo(p_X, ++y);
    printf("| Control         |               |");
    moveTo(p_X, ++y);
    printf("| Defensa         |               |");
    moveTo(p_X, ++y);
    printf("| Ataque          |               |");
    moveTo(p_X, ++y);
    printf("| Gambeta         |               |");
    moveTo(p_X, ++y);
    printf("| Cuerpo          |               |");
    moveTo(p_X, ++y);
    printf("| Porteria        |               |");
    moveTo(p_X, ++y);
    printf("| Vision de Juego |               |");
    moveTo(p_X, ++y);
    printf("| Juego en Equipo |               |");
    moveTo(p_X, ++y);
    printf("+-----------------+---------------+");
    moveTo(p_X, ++y);
    printf("| Puntaje         |               |");
    moveTo(p_X, ++y);
    printf("+-----------------+---------------+");

}

void jugadorFueElegido(int id, int padding_x, int padding_y)
{
    // const int paddingX = 7;
    // const int paddingY = 10;
    int x = floor(id % 5) * 23 + padding_x;
    int y = (id / 5) * 4 + padding_y;
    moveTo(x + 8, y);
    setColor(FGRN, BBLK);
    printf("X");
    setColor(FWHT, BBLK);
}

void mostrarJugador(struct un_jugador jugador, int x, int *pos_y)
{
    x += 3 + (jugador.id % 5) * 23 ;
    int y = *pos_y + floor(jugador.id / 5) * 4;
    moveTo(x, y);
    printf("ID: %d", jugador.id);
    moveTo(x, ++y);
    printf("Nombre:  %s", jugador.nombre);

    moveTo(x, ++y);
    printf("PUNTAJE: ");
    int r, g, b;
    colorSegunFloat(&r, &g, &b, jugador.puntaje_general);
    setColorRGB(r, g, b);
    printf("%.2f", jugador.puntaje_general);
    setColor(FWHT, BBLK);
}

void mostrarListadoJugadores(struct un_jugador *jugadores, const int cantidad_jugadores, const int tam_equipo, int x, int *pos_y)
{
    const int padding_y = *pos_y;
    int last_y = *pos_y;
    moveTo(x, *pos_y);
    printf("+-------------------------------------------------------------------------------------------------------------------+");
    moveTo(x + 25, ++(*pos_y));
    printf("          _ _   _  ____    _    ____   ___  ____  _____ ____       ");
    moveTo(x + 25, ++(*pos_y));
    printf("         | | | | |/ ___|  / \\  |  _ \\ / _ \\|  _ \\| ____/ ___|      ");
    moveTo(x + 25, ++(*pos_y));
    printf("      _  | | | | | |  _  / _ \\ | | | | | | | |_) |  _| \\___ \\      ");
    moveTo(x + 25, ++(*pos_y));
    printf("     | |_| | |_| | |_| |/ ___ \\| |_| | |_| |  _ <| |___ ___) |     ");
    moveTo(x + 25, ++(*pos_y));
    printf("      \\___/ \\___/ \\____/_/   \\_\\____/ \\___/|_| \\_\\_____|____/      ");
    moveTo(x + 25, ++(*pos_y));
    printf("                                                                   ");
    moveTo(x, ++(*pos_y));
    printf("+-------------------------------------------------------------------------------------------------------------------+");

    (*pos_y) = padding_y + 1;

    for(int j = 0; j < 6; j++)
    {
        moveTo(x, *pos_y);
        printf("|");
        moveTo(x + 116, *pos_y);
        printf("|");
        (*pos_y)++;
    }

    (*pos_y)++;

    for (int j = 0; j < (ceil(cantidad_jugadores / 5.0)) * 4 + 1; j++)
    {
        moveTo(x, *pos_y);
        printf("|");
        moveTo(x + 116, *pos_y);
        printf("|");
        (*pos_y)++;
    }
    

    moveTo(x, *pos_y);
    printf("+-------------------------------------------------------------------------------------------------------------------+");

    last_y = *pos_y + 2;
    (*pos_y) = padding_y + 9;

    for (int i = 0; i < cantidad_jugadores; i++)
    {
        jugadores[i].id = i;
        mostrarJugador(jugadores[i], x,  pos_y);
    }
    (*pos_y) = last_y;
}

void mostrarSeparadorEquipos(const int x, int *y)
{
    moveTo(x, (*y)++);
    printf("+--------------+-----------+------------+");
}

void mostrarSeparadorDeColEquipos(const int x, int y)
{
    moveTo(x, y);
    printf("|");
    moveTo(x + 15, y);
    printf("|");
    moveTo(x + 27, y);
    printf("|");
    moveTo(x + 40, y);
    printf("|");
}
void mostrarPlantillaEquipos(int x, int y, const int tam_equipos)
{
    const int start_x = x, start_y = y;
    setColor(FWHT, BBLK);
    mostrarSeparadorEquipos(x, &y);
    mostrarSeparadorDeColEquipos(start_x, y++);
    mostrarSeparadorEquipos(start_x, &y);

    moveTo(x + 3, y);
    printf("Jugadores");
    for (int i = 0; i < tam_equipos; i++)
    {
        mostrarSeparadorDeColEquipos(start_x, y++);
    }
    mostrarSeparadorEquipos(start_x, &y);

    mostrarSeparadorDeColEquipos(start_x, y);
    moveTo(x + 3, y++);
    printf("Ataque");    
    mostrarSeparadorDeColEquipos(start_x, y);
    moveTo(x + 3, y++);
    printf("Defensa");

    mostrarSeparadorEquipos(start_x, &y);

    mostrarSeparadorDeColEquipos(start_x, y);
    moveTo(x + 3, y++);
    printf("Puntaje");
    mostrarSeparadorDeColEquipos(start_x, y);
    moveTo(x + 3, y++);
    printf("Varianza");
    mostrarSeparadorDeColEquipos(start_x, y);
    moveTo(x + 3, y++);
    printf("Prediccion");
    
    mostrarSeparadorEquipos(start_x, &y);
}

void mostrarEquipos(struct un_equipo *equipos, int tam, int padding_x, int padding_y)
{
    int x = padding_x + 120;
    int y = padding_y;

    int r, g, b;
    float diferencia;

    mostrarPlantillaEquipos(x, y, tam);

    x += 17;
    for (int num = 0; num < 2; num++)
    {
        y = 3;
        x += 13 * num;
        moveTo(x, y);
        setColor(num == 0 ? FCYA : FYEL, BBLK);

        printf("EQUIPO %d", num + 1);
        setColor(FWHT, BBLK);

        y += 2;

        for (int i = 0; i < tam; i++)
        {
            diferencia = equipos[num].jugadores[i]->puntaje_general - equipos[!num].jugadores[i]->puntaje_general;
            
            if(fabs(diferencia) > 0.5)
            {
                colorSegunFloat(&r, &g, &b, 5 + diferencia);
                setColorRGB(r, g, b);
            }
            moveTo(x, y++);
            printf("%s ", equipos[num].jugadores[i]->nombre);
            setColor(FWHT, BBLK);
        }

        float ataque = calcularAtaqueDeEquipo(equipos[num], tam);
        float defensa = calcularDefensaDeEquipo(equipos[num], tam);
        int r, g, b;

        moveTo(x, ++y);
        diferencia = ataque - calcularAtaqueDeEquipo(equipos[!num], tam);
        if (fabs(diferencia) > 0.5)
        {
            colorSegunFloat(&r, &g, &b, 5 + diferencia * 2);
            setColorRGB(r, g, b);
        }
        printf("%.2f", ataque);
        setColor(FWHT, BBLK);

        moveTo(x, ++y);
        diferencia = defensa - calcularDefensaDeEquipo(equipos[!num], tam);
        if (fabs(diferencia) > 0.5)
        {
            colorSegunFloat(&r, &g, &b, 5 + diferencia * 2);
            setColorRGB(r, g, b);
        }
        setColorRGB(r, g, b);
        printf("%.2f", defensa);
        setColor(FWHT, BBLK);

        y++;

        moveTo(x, ++y);
        diferencia = equipos[num].promedio - equipos[!num].promedio;
        if (fabs(diferencia) > 0.75)
        {
            colorSegunFloat(&r, &g, &b, 5 + diferencia * 2);
            setColorRGB(r, g, b);
        }
        printf("%.2f", equipos[num].promedio);
        setColor(FWHT, BBLK);

        moveTo(x, ++y);
        colorSegunFloat(&r, &g, &b, 10 - equipos[num].varianza);
        setColorRGB(r, g, b);
        printf("%.2f", equipos[num].varianza);
        setColor(FWHT, BBLK);
        
        moveTo(x, ++y);
        diferencia = (equipos[num].probabilidadGanar - equipos[!num].probabilidadGanar) * 100;
        if (fabs(diferencia) > 10)
        {
            colorSegunFloat(&r, &g, &b, 5 + diferencia / 5);
            setColorRGB(r, g, b);
        }
        printf("%.2f%%", equipos[num].probabilidadGanar * 100);
        setColor(FWHT, BBLK);
    }
}
void mostrarSeparadorEstadisticas(const int x, int *y)
{
    moveTo(x, (*y)++);
    printf("+-----+------------+-------------+-----------+-----------+-----------+----------+-----------+----------+------------+-----------------+-----------------+-----------+");
}

void mostrarSeparadoresDeColEstadisticas(const int x, const int y)
{
    int pos_x[14] = {0, 6, 19, 33, 45, 57, 69, 80, 92, 103, 116, 134, 152, 164};
    for (int i = 0; i < 14; i++)
    {
        moveTo(x + pos_x[i], y);
        printf("|");
    }
}

void colorSegunFloat(int *r, int *g, int *b, float valor)
{
    int cant_colores = 64;
    float rango_inicial = 1.0; // Transición de rojo a amarillo
    float rango_transicion = 6.5; // Transición de rojo a amarillo
    float rango_final = 10; // Transición de amarillo a verde (8 a 10)

    if(valor < rango_inicial)
    {        
        *r = 255;
        *g = 0;
    }
    else if (valor <= rango_transicion) 
    {
        // Transición de rojo a amarillo
        *r = 255;
        *g = (int)(255 * fmax(0, (valor - rango_inicial)) / rango_transicion);
    } 
    else if (valor <= rango_final) 
    {
        // Transición de amarillo a verde
        *r = (int)(255 * (10 - valor) / (10 - rango_transicion));
        *g = 255;
    } 
    else {
        // Verde
        *r = 0;
        *g = 255;
    }
    *b = 0;
}
/*

void colorSegunFloat(int *r, int *g, int *b, float valor)
{
    int cant_colores = 10; 
    int codigo = (int)floor(valor / (10.0 / cant_colores));

    int r_inicial = 255, g_inicial = 0, b_inicial = 0;
    int r_medio = 255, g_medio = 255, b_medio = 0;
    int r_final = 0, g_final = 255, b_final = 0;

    int segmento = cant_colores - 3; 

    if (codigo < segmento)
    {
        float factor = (float)codigo / segmento;
        *r = r_inicial * (1 - factor) + r_medio * factor;
        *g = g_inicial * (1 - factor) + g_medio * factor;
        *b = b_inicial * (1 - factor) + b_medio * factor;
    }
    else if (codigo < cant_colores)
    {
        float factor = (float)(codigo - segmento) / (cant_colores - segmento);
        *r = r_medio * (1 - factor) + r_final * factor;
        *g = g_medio * (1 - factor) + g_final * factor;
        *b = b_medio * (1 - factor) + b_final * factor;
    }
    else
    {
        *r = r_final;
        *g = g_final;
        *b = b_final;
    }
}
*/

void mostrarInfoColumnasEstadisticas(const int x, int *y)
{    
    int pos_x[13] = {2, 8, 21, 35, 48, 60, 72, 83, 95, 106, 118, 136, 155};

    mostrarSeparadoresDeColEstadisticas(x, *y);

    char info[13][17] = {
        "ID", "Nombre", "Resistencia", "Velocidad", "Control", "Defensa", "Ataque",
        "Gambeta", "Cuerpo", "Portería", "Visión de Juego", "Juego en Equipo", "Puntaje"};

    for (int i = 0; i < 13; i++)
    {
        moveTo(x + pos_x[i], *y);
        printf("%s", info[i]);
    }
    (*y)++;
}

void mostrarEstadisticasJugador(struct un_jugador jugador, int padding_x, int *pos_y)
{
    int x;
    int pos_x[13] = {2, 8, 21, 35, 48, 60, 72, 83, 95, 106, 118, 136, 155};
    int separacion[13] = {0, 0, 3, 2, 1, 1, 1, 1, 1, 2, 5, 5, 1};
    //int separacion[13] = {0, 0, 2, 1, 0, 0, 0, 0, 0, 2, 4, 4, 1};

    mostrarSeparadoresDeColEstadisticas(padding_x, *pos_y);

    int i = 0;    
    x = padding_x + pos_x[i] + separacion[i];
    moveTo(x, *pos_y);
    printf("%03d", jugador.id);
    i++;
    
    x = padding_x + pos_x[i] + separacion[i];
    moveTo(x, *pos_y);
    printf("%s", jugador.nombre);
    i++;

    float *estadisticas = malloc(11 * sizeof(float));

    generarArrayEstadisticasDeJugador(jugador, estadisticas);
    int r, g, b;
    while (i < 13)
    {
        x = padding_x + pos_x[i] + separacion[i];
        moveTo(x, *pos_y);
        // setColor(colorSegunFloat(estadisticas[i - 2]), BBLK);
        colorSegunFloat(&r, &g, &b, estadisticas[i - 2]);
        setColorRGB(r, g, b);
        printf("%.2f", estadisticas[i - 2]);
        setColor(FWHT, BBLK);
        i++;
    }
    (*pos_y)++;
}

void mostrarTablaDeEstadisticas(struct un_jugador *jugadores, const int cantidad_jugadores, int padding_x, int *pos_y)
{
    const int padding_y = 2;
    int x = padding_x;
    *pos_y = padding_y;
    moveTo(padding_x, *pos_y);
    moveTo(x, (*pos_y)++);
    printf("+-------------------------------------------------------------------------------------------------------------------------------------------------------------------+");
    moveTo(x, (*pos_y)++);
    printf("|                       _____     _            _ __    _   _                     _            _                       _                                             |\n");
    moveTo(x, (*pos_y)++);
    printf("|                      | ____|___| |_ __ _  __| /_/___| |_(_) ___ __ _ ___    __| | ___      | |_   _  __ _  __ _  __| | ___  _ __ ___  ___                         |\n");
    moveTo(x, (*pos_y)++);
    printf("|                      |  _| / __| __/ _` |/ _` | / __| __| |/ __/ _` / __|  / _` |/ _ \\  _  | | | | |/ _` |/ _` |/ _` |/ _ \\| '__/ _ \\/ __|                        |\n");
    moveTo(x, (*pos_y)++);
    printf("|                      | |___\\__ \\ || (_| | (_| | \\__ \\ |_| | (_| (_| \\__ \\ | (_| |  __/ | |_| | |_| | (_| | (_| | (_| | (_) | | |  __/\\__ \\                        |\n");
    moveTo(x, (*pos_y)++);
    printf("|                      |_____|___/\\__\\__,_|\\__,_|_|___/\\__|_|\\___\\__,_|___/  \\__,_|\\___|  \\___/ \\__,_|\\__, |\\__,_|\\__,_|\\___/|_|  \\___||___/                        |\n");
    moveTo(x, (*pos_y)++);
    printf("|                                                                                                     |___/                                                         |\n");
    moveTo(x, (*pos_y)++);
    printf("|                                                                                                                                                                   |\n");

    mostrarSeparadorEstadisticas(x, pos_y);
    mostrarInfoColumnasEstadisticas(x, pos_y);
    mostrarSeparadorEstadisticas(x, pos_y);
    for (int i = 0; i < cantidad_jugadores; i++)
    {
        mostrarEstadisticasJugador(jugadores[i], x, pos_y);
    }
    mostrarSeparadorEstadisticas(x, pos_y);
    (*pos_y)++;
}