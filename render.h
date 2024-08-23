#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

struct un_jugador;
struct un_equipo;

void colorSegunFloat(int*, int*, int*, float);

void inicioDeSistema(int*);
void mostrarPlantillaCarga(int, int, int);
void jugadorFueElegido(int, int, int);

void mostrarJugador(struct un_jugador, int, int*);
void mostrarListadoJugadores(struct un_jugador*, const int, const int, int, int*);
void mostrarTablaDeEstadisticas(struct un_jugador *, const int, int, int *);

void mostrarEquipos(struct un_equipo*, int, int, int);

#endif // RENDER_H_INCLUDED