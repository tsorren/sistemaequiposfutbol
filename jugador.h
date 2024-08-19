#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

struct un_jugador
{
    int id;
    char nombre[10 + 1];

    float resistencia;
    float velocidad;
    float control;
    float defensa;
    float ataque;
    float gambeta;
    float cuerpo;
    float porteria;
    float vision;
    float juego_equipo;

    float puntaje_general;
};

struct un_equipo
{
    int num;
    struct un_jugador **jugadores;
    float promedio;
    float varianza;
    float probabilidadGanar;
};

struct FILE;

float calcularPuntaje(struct un_jugador*);
void calcularProbabilidadDeGanar(struct un_equipo*, struct un_equipo*, int);
float calcularAtaqueDeEquipo(struct un_equipo eq, int tam);
float calcularDefensaDeEquipo(struct un_equipo eq, int tam);
void ordenarListaDeJugadores(struct un_jugador**, const int);
void generarEquiposBalanceadamente(struct un_jugador**, struct un_equipo*, struct un_equipo*, int);

#endif // JUGADOR_H