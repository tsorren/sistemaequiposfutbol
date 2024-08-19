#include <stdio.h>
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
    const int paddingX = 5;
    const int paddingY = 11;
    int x = floor(id % 5) * 23 + paddingX;
    int y = (id / 5) * 4 + paddingY;
    moveTo(x + 8, y);
    setColor(FGRN, BBLK);
    printf("ELEGIDO");
    setColor(FWHT, BBLK);
}

void mostrarJugador(struct un_jugador jugador)
{
    const int padding_x = 5;
    const int padding_y = 11;
    int x = padding_x + (jugador.id % 5) * 23 ;
    int y = padding_y + floor(jugador.id / 5) * 4;
    moveTo(x, y);
    printf("ID: %d", jugador.id);
    moveTo(x, ++y);
    printf("    Nombre: %s", jugador.nombre);

    moveTo(x, ++y);
    printf("    PUNTAJE: %.2f", jugador.puntaje_general);
}

void mostrarListadoJugadores(struct un_jugador *jugadores, const int cantidad_jugadores, const int tam_equipo, int* pos_y)
{
    const int padding_y = 2;
    *pos_y = padding_y;
    moveTo(3, *pos_y);
    printf(" -------------------------------------------------------------------------------------------------------------------");
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
    moveTo(28, ++(*pos_y));
    printf("                                                                   ");
    moveTo(3, ++(*pos_y));
    printf(" -------------------------------------------------------------------------------------------------------------------");

    (*pos_y) = padding_y + 1;
    int j = 0;
    while (j < (ceil(cantidad_jugadores / 5) + 1) * 4 + 7 + 1)
    {
        moveTo(3, (*pos_y) + j);
        printf("|");
        moveTo(119, (*pos_y) + j);
        printf("|");
        j++;
    }

    (*pos_y) += j;
    moveTo(3, *pos_y);
    printf(" -------------------------------------------------------------------------------------------------------------------");

    for (int i = 0; i < cantidad_jugadores; i++)
    {
        jugadores[i].id = i;
        mostrarJugador(jugadores[i]);
    }
    (*pos_y) += 2;
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

        moveTo(x, ++y);
        printf("Ataque:");
        moveTo(x + 14, y);
        printf("%.2f", ataque);

        moveTo(x, ++y);
        float defensa = calcularDefensaDeEquipo(equipos[num], tam);
        printf("Defensa:");
        moveTo(x + 14, y);
        printf("%.2f", defensa);

        y++;
        moveTo(x, ++y);
        printf("Habilidad:");
        moveTo(x + 14, y);
        printf("%.2f", equipos[num].promedio);

        moveTo(x, ++y);
        printf("Varianza:");
        moveTo(x + 14, y);
        printf("%.2f", equipos[num].varianza);
        
        moveTo(x, ++y);
        //printf("Dispersión: %.2f", dispersion);
        printf("Predicción:");
        moveTo(x + 14, y);
        printf("%.2f%%", equipos[num].probabilidadGanar * 100);
    }
}