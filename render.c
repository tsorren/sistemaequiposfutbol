#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "render.h"
#include "utils.h"
#include "jugador.h"

void inicioDeSistema(int *input)
{
    clearScreen();
    printf("\n");
    printf("                    S I S T E M A\n");
    printf("                         D E\n");
    printf("         G E S T I Ó N   D E   E Q U I P O S\n\n");
    printf("         Opciones:\n");
    printf("            1:  Generar equipos balanceadamente\n");
    printf("            2:  Evaluar balance de equipos\n");
    printf("            3:  Añadir nuevo jugador\n");
    printf("            4:  Modificar jugadores existentes\n");
    printf("            99: Salir\n");

    setColor(FGRN, BBLK);
    printf("\n         Elija una opción: ");
    setColor(FWHT, BBLK);
    scanf("%d", input);
}
void mostrarPlantillaCarga(int p_X, int y)
{
    for (int i = 0; i < 20; i++)
    {
        moveTo(0, i);
        printf("                                               ");
    }

    moveTo(p_X, y);
    printf("CARGA DE JUGADOR:");
        
    moveTo(p_X + 3, ++y);
    printf("Nombre: ");
    
    moveTo(p_X + 5, ++y);
    printf("Resistencia: ");
    
    moveTo(p_X + 5, ++y);
    printf("Velocidad: ");
    
    moveTo(p_X + 5, ++y);
    printf("Control: ");
    
    moveTo(p_X + 5, ++y);
    printf("Defensa: ");
    
    moveTo(p_X + 5, ++y);
    printf("Ataque: ");
    
    moveTo(p_X + 5, ++y);
    printf("Gambeta: ");
    
    moveTo(p_X + 5, ++y);
    printf("Cuerpo: ");
    
    moveTo(p_X + 5, ++y);
    printf("Porteria: ");
    
    moveTo(p_X + 5, ++y);
    printf("Vision: ");
    
    moveTo(p_X + 5, ++y);
    printf("Juego en Equipo: ");
}

void jugadorFueElegido(int id)
{
    const int paddingX = 7;
    const int paddingY = 10;
    int x = floor(id % 5) * 23 + paddingX;
    int y = (id / 5) * 4 + paddingY;
    moveTo(x + 8, y);
    setColor(FGRN, BBLK);
    printf("ELEGIDO");
    setColor(FWHT, BBLK);
}

void mostrarJugador(struct un_jugador jugador, int *pos_y)
{
    const int padding_x = 6;
    int x = padding_x + (jugador.id % 5) * 23 ;
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

void mostrarListadoJugadores(struct un_jugador *jugadores, const int cantidad_jugadores, const int tam_equipo, int *pos_y)
{
    const int padding_y = 2;
    int last_y;
    *pos_y = padding_y;
    moveTo(3, *pos_y);
    printf("+-------------------------------------------------------------------------------------------------------------------+");
    moveTo(28, ++(*pos_y));
    printf("          _ _   _  ____    _    ____   ___  ____  _____ ____       ");
    moveTo(28, ++(*pos_y));
    printf("         | | | | |/ ___|  / \\  |  _ \\ / _ \\|  _ \\| ____/ ___|      ");
    moveTo(28, ++(*pos_y));
    printf("      _  | | | | | |  _  / _ \\ | | | | | | | |_) |  _| \\___ \\      ");
    moveTo(28, ++(*pos_y));
    printf("     | |_| | |_| | |_| |/ ___ \\| |_| | |_| |  _ <| |___ ___) |     ");
    moveTo(28, ++(*pos_y));
    printf("      \\___/ \\___/ \\____/_/   \\_\\____/ \\___/|_| \\_\\_____|____/      ");
    //moveTo(28, ++(*pos_y));
    //printf("                                                                   ");
    moveTo(3, ++(*pos_y));
    printf("+-------------------------------------------------------------------------------------------------------------------+");

    (*pos_y) = padding_y + 1;

    for(int j = 0; j < 5; j++)
    {
        moveTo(3, *pos_y);
        printf("|");
        moveTo(119, *pos_y);
        printf("|");
        (*pos_y)++;
    }
    moveTo(3, *pos_y);
    printf("+");
    moveTo(119, *pos_y);
    printf("+");
    (*pos_y)++;

    for (int j = 0; j < (ceil(cantidad_jugadores / 5.0)) * 4 + 1; j++)
    {
        moveTo(3, *pos_y);
        printf("|");
        moveTo(119, *pos_y);
        printf("|");
        (*pos_y)++;
    }
    

    moveTo(3, *pos_y);
    printf("+-------------------------------------------------------------------------------------------------------------------+");

    last_y = *pos_y + 2;
    (*pos_y) = padding_y + 8;

    for (int i = 0; i < cantidad_jugadores; i++)
    {
        jugadores[i].id = i;
        mostrarJugador(jugadores[i], pos_y);
    }
    (*pos_y) = last_y;
}

void mostrarEquipos(struct un_equipo *equipos, int tam)
{
    int x = 125;
    int y = 3;
    for (int num = 0; num < 2; num++)
    {
        y = 3;
        x += 36 * num;
        moveTo(x, y);

        if (num == 1)
            setColor(FCYA, BBLK);
        else
            setColor(FYEL, BBLK);

        printf("E Q U I P O  %d:", num + 1);
        setColor(FWHT, BBLK);

        y++;

        moveTo(x, ++y);
        printf("Jugadores:");
        for (int i = 0; i < tam; i++)
        {
            moveTo(x + 14, y++);
            printf("%s ", equipos[num].jugadores[i]->nombre);
        }


        moveTo(x, ++y);
        printf("ESTADISTICAS:");

        float ataque = calcularAtaqueDeEquipo(equipos[num], tam);
        int r, g, b;

        moveTo(x, ++y);
        printf("Ataque:");
        moveTo(x + 14, y);
        colorSegunFloat(&r, &g, &b, ataque);
        setColorRGB(r, g, b);
        printf("%.2f", ataque);
        setColor(FWHT, BBLK);

        moveTo(x, ++y);
        float defensa = calcularDefensaDeEquipo(equipos[num], tam);
        printf("Defensa:");
        moveTo(x + 14, y);
        colorSegunFloat(&r, &g, &b, defensa);
        setColorRGB(r, g, b);
        printf("%.2f", defensa);
        setColor(FWHT, BBLK);

        y++;
        moveTo(x, ++y);
        printf("Puntaje:");
        moveTo(x + 14, y);
        colorSegunFloat(&r, &g, &b, equipos[num].promedio);
        setColorRGB(r, g, b);
        printf("%.2f", equipos[num].promedio);
        setColor(FWHT, BBLK);

        moveTo(x, ++y);
        printf("Varianza:");
        moveTo(x + 14, y);
        colorSegunFloat(&r, &g, &b, 10 - equipos[num].varianza * 2);
        setColorRGB(r, g, b);
        printf("%.2f", equipos[num].varianza);
        setColor(FWHT, BBLK);
        
        moveTo(x, ++y);
        //printf("Dispersión: %.2f", dispersion);
        printf("Predicción:");
        moveTo(x + 14, y);
        colorSegunFloat(&r, &g, &b, equipos[num].probabilidadGanar * 10);
        setColorRGB(r, g, b);
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
    int cant_colores = 16;
    float rango_inicial = 1.5; // Transición de rojo a amarillo
    float rango_transicion = 6.0; // Transición de rojo a amarillo
    float rango_final = 7.5; // Transición de amarillo a verde (8 a 10)

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