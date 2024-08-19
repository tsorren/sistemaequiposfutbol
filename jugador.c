#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "jugador.h"
// Función para calcular el puntaje
float calcularPuntaje(struct un_jugador *jugador)
{
    float w_R  = 0.1034;  // Resistencia
    float w_V  = 0.06897; // Velocidad
    float w_C  = 0.1379;  // Control del balón
    float w_D  = 0.1034;  // Defensa
    float w_AT = 0.1379;  // Ataque
    float w_G  = 0.06897; // Gambeta
    float w_CU = 0.06897; // Cuerpo
    float w_P  = 0.06897; // Porteria
    float w_VJ = 0.1379;  // Visión de juego
    float w_JE = 0.1034;  // Juego en equipo

    //  Suma de los pesos
    float suma_pesos = 0;
    suma_pesos += w_R;
    suma_pesos += w_V;
    suma_pesos += w_C;
    suma_pesos += w_D;
    suma_pesos += w_AT;
    suma_pesos += w_G;
    suma_pesos += w_CU;
    suma_pesos += w_VJ;
    suma_pesos += w_JE;

    // Cálculo del puntaje ponderado
    float puntaje = 0;
    puntaje += w_R * jugador->resistencia;
    puntaje += w_V * jugador->velocidad;
    puntaje += w_C * jugador->control;
    puntaje += w_D * jugador->defensa;
    puntaje += w_AT * jugador->ataque;
    puntaje += w_G * jugador->gambeta;
    puntaje += w_CU * jugador->cuerpo;
    puntaje += w_P * jugador->porteria;
    puntaje += w_VJ * jugador->vision;
    puntaje += w_JE * jugador->juego_equipo;
    // puntaje /= suma_pesos;

    return puntaje;
}

float calcularPromedio(struct un_jugador **equipo, int tam_equipo)
{
    float suma = 0;
    for (int i = 0; i < tam_equipo; i++)
    {
        suma += equipo[i]->puntaje_general;
    }
    return suma / tam_equipo;
}

float calcularVarianza(struct un_jugador **equipo, int tam_equipo, int promedio)
{
    float suma = 0.0;
    for (int i = 0; i < tam_equipo; i++)
    {
        suma += pow(equipo[i]->puntaje_general - promedio, 2);
    }
    return suma / tam_equipo;
}

float calcularDispersion(struct un_jugador **equipo, int tam_equipo)
{
    return equipo[tam_equipo - 1]->puntaje_general - equipo[0]->puntaje_general;
}

float phi(float x)
{
    const float M_SQRT1_2 = 0.70710678118;
    float proba = 0.5 * erfc(x * M_SQRT1_2);
    return proba;
}

void calcularProbabilidadDeGanar(struct un_equipo *eq1, struct un_equipo *eq2, int tam_equipo)
{
    eq1->promedio = calcularPromedio(eq1->jugadores, tam_equipo);
    eq2->promedio = calcularPromedio(eq2->jugadores, tam_equipo);

    const float modificador = 5;
    //float esperanza = (eq1->promedio + sqrt(eq1->varianza) - (eq2->promedio + sqrt(eq2->varianza))) * modificador;
    float esperanza = eq1->promedio - eq2->promedio;
    esperanza *= modificador;

    eq1->varianza = calcularVarianza(eq1->jugadores, tam_equipo, eq1->promedio);
    eq2->varianza  = calcularVarianza(eq2->jugadores, tam_equipo, eq2->promedio);
    float varianza = ((tam_equipo - 1) * eq1->varianza + (tam_equipo - 1) * eq2->varianza) / (2 * tam_equipo - 2);
    varianza =  varianza * sqrt(2.0 / tam_equipo);
    //varianza *= modificador;

    eq1->probabilidadGanar = 1 - phi((esperanza - 0) / varianza);
    eq2->probabilidadGanar = 1 - eq1->probabilidadGanar;
}

void ordenarListaDeJugadores(struct un_jugador **jugadores, const int tam)
{
    int i, j;
    struct un_jugador aux;
    for (i = 1; i < tam; i++)
    {
        for (j = 1; j <= tam - i; j++)
        {
            if ((*jugadores)[j - 1].puntaje_general > (*jugadores)[j].puntaje_general)
            {
                aux = (*jugadores)[j - 1];
                (*jugadores)[j - 1] = (*jugadores)[j];
                (*jugadores)[j] = aux;
            }
        }
    }
}

// EQUIPOS

void ordenarEquipo(struct un_equipo *equipo, const int tam)
{
    int i, j;
    struct un_jugador *aux;
    for (i = 1; i < tam; i++)
    {
        for (j = 1; j <= tam - i; j++)
        {
            if (equipo->jugadores[j - 1]->puntaje_general > equipo->jugadores[j]->puntaje_general)
            {
                aux = equipo->jugadores[j - 1];
                equipo->jugadores[j - 1] = equipo->jugadores[j];
                equipo->jugadores[j] = aux;
            }
        }
    }
}

float calcularAtaqueDeEquipo(struct un_equipo eq, int tam)
{
    float ataqueTotal = 0;

    float atkPeso = 0.45;
    float gamPeso = 0.15;
    float velPeso = 0.05;
    float resPeso = 0.10;
    float conPeso = 0.05;
    float visPeso = 0.15;

    float atkProm = 0;
    float gamProm = 0;
    float velProm = 0;
    float resProm = 0;
    float conProm = 0;
    float visProm = 0;    
    for (int i = 0; i < tam; i++)
    {
        atkProm += eq.jugadores[i]->ataque;
        gamProm += eq.jugadores[i]->gambeta;
        velProm += eq.jugadores[i]->velocidad;
        resProm += eq.jugadores[i]->resistencia;
        conProm += eq.jugadores[i]->control;
        visProm += eq.jugadores[i]->vision;
    }
    atkProm /= tam;
    gamProm /= tam;
    velProm /= tam;
    resProm /= tam;
    conProm /= tam;
    visProm /= tam;

    ataqueTotal += atkProm * atkPeso;
    ataqueTotal += gamProm * gamPeso;
    ataqueTotal += velProm * velPeso;
    ataqueTotal += resProm * resPeso;
    ataqueTotal += conProm * conPeso;
    ataqueTotal += visProm * visPeso;

    return ataqueTotal;
}

float calcularDefensaDeEquipo(struct un_equipo eq, int tam)
{
    float defensaTotal = 0;

    float defPeso = 0.50;
    float velPeso = 0.15;
    float resPeso = 0.10;
    float cuePeso = 0.10;
    float porPeso = 0.10;
    float juePeso = 0.05;

    float defProm = 0;
    float velProm = 0;
    float resProm = 0;
    float cueProm = 0;
    float porProm = 0;
    float jueProm = 0;    
    for (int i = 0; i < tam; i++)
    {
        defProm += eq.jugadores[i]->defensa;
        velProm += eq.jugadores[i]->velocidad;
        resProm += eq.jugadores[i]->resistencia;
        cueProm += eq.jugadores[i]->cuerpo;
        porProm += eq.jugadores[i]->porteria;
        jueProm += eq.jugadores[i]->juego_equipo;
    }
    defProm /= tam;
    velProm /= tam;
    resProm /= tam;
    cueProm /= tam;
    porProm /= tam;
    jueProm /= tam;

    defensaTotal += defProm * defPeso;
    defensaTotal += velProm * velPeso;
    defensaTotal += resProm * resPeso;
    defensaTotal += cueProm * cuePeso;
    defensaTotal += porProm * porPeso;
    defensaTotal += jueProm * juePeso;
    return defensaTotal;
    
}

void generarEquiposBalanceadamente(struct un_jugador **j_disp, struct un_equipo *eq1, struct un_equipo *eq2, int tam)
{
    int tam_equipo = tam / 2;
    int total_combinaciones = 1 << tam; // 2^tam combinaciones posibles
    int count;

    const float CONST_E = 2.718281828459045;
    float probabilidadDeGanar;
    float mejor_balance = 99999999;
    float balance;

    struct un_equipo temp_eq1;
    temp_eq1.jugadores = malloc(tam_equipo * sizeof(struct un_jugador *));

    struct un_equipo temp_eq2;
    temp_eq2.jugadores = malloc(tam_equipo * sizeof(struct un_jugador *));

    temp_eq1.num = 0;
    temp_eq2.num = 1;

    for (int mask = 0; mask < total_combinaciones; mask++)
    {
        count = 0;
        // Verificar si la combinación tiene exactamente tam_equipo elementos en cada equipo
        for (int i = 0; i < tam; i++)
        {
            if (mask & (1 << i))
            {
                count++;
            }
        }
        if (count != tam_equipo)
            continue;

        // Dividir los jugadores en dos equipos según la máscara

        int idx1 = 0, idx2 = 0;
        for (int i = 0; i < tam; i++)
        {
            if (mask & (1 << i))
            {
                temp_eq1.jugadores[idx1++] = j_disp[i];
            }
            else
            {
                temp_eq2.jugadores[idx2++] = j_disp[i];
            }
        }

        ordenarEquipo(&temp_eq1, tam_equipo);
        ordenarEquipo(&temp_eq2, tam_equipo);

        // Calcular la diferencia de promedios

        calcularProbabilidadDeGanar(&temp_eq1, &temp_eq2, tam_equipo);

        balance = fabs(temp_eq1.probabilidadGanar - 0.5);

        // Si la diferencia es menor, actualizamos los equipos
        if (balance < mejor_balance)
        {
            mejor_balance = balance;
            for (int i = 0; i < tam_equipo; i++)
            {
                eq1->jugadores[i] = temp_eq1.jugadores[i];
                eq2->jugadores[i] = temp_eq2.jugadores[i];
            }
            eq1->num = 0;
            eq2->num = 1;
            calcularProbabilidadDeGanar(eq1, eq2, tam_equipo);
        }
    }
    free(temp_eq1.jugadores);
    free(temp_eq2.jugadores);
    return;
}
