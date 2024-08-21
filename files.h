#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

#include <stdio.h>

struct un_jugador;

void moverPunteroA(FILE*, int);
int calcularCantidadDeJugadores(FILE*);
void ingresarNuevosJugadores(FILE*, char*, int*);
void cargarNuevoJugadorEnArchivo(FILE *, int, struct un_jugador);
int siguienteComa(char*, int);
float conseguirSiguienteFloat(char*, int*, int*);
void cargarListaDeJugadores(FILE*, struct un_jugador*);
void modificarArchivoJugadores(FILE *, struct un_jugador *, int, int, int*);

#endif // FILES_H_INCLUDED