#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

struct un_jugador;
struct un_equipo;

void inicioDeSistema(int*);
void mostrarPlantillaCarga(int, int);
void jugadorFueElegido(int);

void mostrarJugador(struct un_jugador);
void mostrarListadoJugadores(struct un_jugador*, const int, const int, int*);

void mostrarEquipos(struct un_equipo*, int);

#endif // RENDER_H_INCLUDED