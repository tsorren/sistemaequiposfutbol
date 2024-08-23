#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

#include <stdio.h>

struct un_jugador;

void moverPunteroA(FILE*, int);
int calcularCantidadDeJugadores(char*);
void ordenarArchivoJugadores(char*, struct un_jugador**, int);
void ingresarNuevosJugadores(char*, int*, int, int*);
void cargarNuevoJugadorEnArchivo(FILE*, struct un_jugador, int);
int siguienteComa(char*, int);
float conseguirSiguienteFloat(char*, int*, int*);
void cargarListaDeJugadores(char*, struct un_jugador*);
void modificarArchivoJugadores(char *, struct un_jugador *, int, int, int*);

#endif // FILES_H_INCLUDED