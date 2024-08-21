#include <stdlib.h>
#include <string.h>

#include "files.h"
#include "jugador.h"
#include "render.h"
#include "utils.h"

void moverPunteroA(FILE*, int);
int calcularCantidadDeJugadores(FILE*);
void ingresarNuevosJugadores(FILE *, char*, int*);
void cargarNuevoJugadorEnArchivo(FILE *, int, struct un_jugador);
int siguienteComa(char*, int);
float conseguirSiguienteFloat(char*, int*, int*);
void cargarListaDeJugadores(FILE*, struct un_jugador*);

void moverPunteroA(FILE *archivo, int linea)
{
    const int MAX_LENGTH = 150;
    char buffer[MAX_LENGTH];

    fseek(archivo, 0, SEEK_SET);
    for (int i = 0; i < linea; i++)
    {
        fgets(buffer, MAX_LENGTH, archivo);
        fseek(archivo, 0, SEEK_CUR);
    }
}

int calcularCantidadDeJugadores(FILE *archivo)
{
    const int MAX_LENGTH = 150;
    char buffer[MAX_LENGTH];
    int cantidad = 0;

    moverPunteroA(archivo, 1);

    while (fgets(buffer, MAX_LENGTH, archivo))
    {
        cantidad++;
    }
    // moveTo(3, 1);
    // printf("Cantidad de jugadores disponibles: %d", cantidad);

    return cantidad;
}

void ingresarNuevosJugadores(FILE *arch, char *dir_archivo, int *cant_j)
{
    arch = fopen(dir_archivo, "rt+");
    int p_X = 8;
    int x;
    int y;

    struct un_jugador jugador;
    int continuar = 1;
    while(continuar != 0)
    {
        x = p_X;
        y = 3;
        jugador.id = *cant_j;
        mostrarPlantillaCarga(x, y);

        x = p_X + 22;
        moveTo(x, ++y);
        scanf("%s", jugador.nombre);
        moveTo(x, ++y);
        scanf("%f", &jugador.resistencia);
        moveTo(x, ++y);
        scanf("%f", &jugador.velocidad);
        moveTo(x, ++y);
        scanf("%f", &jugador.control);
        moveTo(x, ++y);
        scanf("%f", &jugador.defensa);
        moveTo(x, ++y);
        scanf("%f", &jugador.ataque);
        moveTo(x, ++y);
        scanf("%f", &jugador.gambeta);
        moveTo(x, ++y);
        scanf("%f", &jugador.cuerpo);
        moveTo(x, ++y);
        scanf("%f", &jugador.porteria);
        moveTo(x, ++y);
        scanf("%f", &jugador.vision);
        moveTo(x, ++y);
        scanf("%f", &jugador.juego_equipo);
        jugador.puntaje_general = calcularPuntaje(&jugador);

        moveTo(p_X + 3, ++y);
        printf("Puntaje: ");
        moveTo(x, y);
        printf("%.2f", jugador.puntaje_general);

        cargarNuevoJugadorEnArchivo(arch, *cant_j, jugador);

        (*cant_j)++;

        y += 2;
        moveTo(p_X, y);
        printf("Continuar carga? (0/1): ");
        scanf("%d", &continuar);
    }
    fclose(arch);
}

void cargarNuevoJugadorEnArchivo(FILE *arch, int cant_j, struct un_jugador j)
{
    moverPunteroA(arch, cant_j + 1);
    
    fflush(arch);

    fprintf(arch, "%s,%05.2f,%05.2f,%05.2f,%05.2f,%05.2f,%05.2f,%05.2f,%05.2f,%05.2f,%05.2f,%05.2f\n",
        j.nombre, j.resistencia, j.velocidad, j.control, j.defensa, j.ataque, j.gambeta, j.cuerpo, j.porteria, j.vision, j.juego_equipo, j.puntaje_general);

    fflush(arch);}

int siguienteComa(char *buffer, int inicio)
{
    while (buffer[inicio] != ',')
    {
        inicio++;
    }

    return inicio;
}

float conseguirSiguienteFloat(char *buffer, int *inicio, int *fin)
{
    const int MAX_LENGTH = 150;
    char word[MAX_LENGTH];

    *fin = siguienteComa(buffer, *inicio);
    strncpy(word, &buffer[*inicio], *fin - *inicio);
    word[*fin] = '\0';
    *inicio = *fin + 1;
    float aux = atof(word);
    return aux;
}

void cargarListaDeJugadores(FILE *archivo, struct un_jugador *jugadores)
{
    moverPunteroA(archivo, 1);
    struct un_jugador jugador;

    int contador = 0;
    const int MAX_LENGTH = 150;
    char buffer[MAX_LENGTH];
    int inicio = 0;
    int fin;
    int len;

    while (fgets(buffer, MAX_LENGTH, archivo))
    {
        inicio = 0;
        fin = siguienteComa(buffer, inicio);
        len = fin - inicio;
        strncpy(jugador.nombre, &buffer[inicio], len);
        jugador.nombre[fin] = '\0';
        inicio = fin + 1;

        jugador.id = contador;
        jugador.resistencia = conseguirSiguienteFloat(buffer, &inicio, &fin);
        jugador.velocidad = conseguirSiguienteFloat(buffer, &inicio, &fin);
        jugador.control = conseguirSiguienteFloat(buffer, &inicio, &fin);
        jugador.defensa = conseguirSiguienteFloat(buffer, &inicio, &fin);
        jugador.ataque = conseguirSiguienteFloat(buffer, &inicio, &fin);
        jugador.gambeta = conseguirSiguienteFloat(buffer, &inicio, &fin);
        jugador.cuerpo = conseguirSiguienteFloat(buffer, &inicio, &fin);
        jugador.porteria = conseguirSiguienteFloat(buffer, &inicio, &fin);
        jugador.vision = conseguirSiguienteFloat(buffer, &inicio, &fin);
        jugador.juego_equipo = conseguirSiguienteFloat(buffer, &inicio, &fin);
        jugador.puntaje_general = calcularPuntaje(&jugador);

        jugadores[contador] = jugador;
        contador++;
    }
}

void modificarArchivoJugadores(FILE *archivo, struct un_jugador *jugadores, int cantidad_jugadores, int padding_x, int *pos_y)
{
    int grabar = 1;
    int continuar = 1;
    int continuar_campos = 1;

    char campo[2] = "";
    float val;
    int id;

    while(continuar != 0)
    {
        mostrarTablaDeEstadisticas(jugadores, cantidad_jugadores, padding_x, pos_y);
        moveTo(padding_x + 1, *pos_y);
        printf("Ingresar ID: ");
        scanf("%d", &id);
        moveTo(padding_x + 1, *pos_y);
        printf("                                                                ");

        continuar_campos = 1;
        grabar = 1;
        float *campo_reemplazar;
        while(continuar_campos != 0)
        {
            moveTo(padding_x + 1, *pos_y);
            printf("Ingresar campo (R / V / C / D / A / G / CU / P / V / JE): ");
            scanf("%s", campo);
            moveTo(padding_x + 1, *pos_y);
            printf("                                                                ");
            
            if(!strcmp(campo, "r") || !strcmp(campo, "R")) campo_reemplazar = &jugadores[id].resistencia;            
            else if(!strcmp(campo, "v") || !strcmp(campo, "V")) campo_reemplazar = &jugadores[id].velocidad;            
            else if(!strcmp(campo, "c") || !strcmp(campo, "C")) campo_reemplazar = &jugadores[id].control;            
            else if(!strcmp(campo, "d") || !strcmp(campo, "D")) campo_reemplazar = &jugadores[id].defensa;            
            else if(!strcmp(campo, "a") || !strcmp(campo, "A")) campo_reemplazar = &jugadores[id].ataque;            
            else if(!strcmp(campo, "g") || !strcmp(campo, "G")) campo_reemplazar = &jugadores[id].gambeta;            
            else if(!strcmp(campo, "cu") || !strcmp(campo, "CU")) campo_reemplazar = &jugadores[id].cuerpo;            
            else if(!strcmp(campo, "p") || !strcmp(campo, "P")) campo_reemplazar = &jugadores[id].porteria;            
            else if(!strcmp(campo, "v") || !strcmp(campo, "V")) campo_reemplazar = &jugadores[id].vision;            
            else if(!strcmp(campo, "je") || !strcmp(campo, "JE")) campo_reemplazar = &jugadores[id].juego_equipo;
            
            moveTo(padding_x + 1, *pos_y);
            printf("Reemplazar %.2f por: ", *campo_reemplazar);
            scanf("%f", &val);
            moveTo(padding_x + 1, *pos_y);
            printf("                                                                ");

            *campo_reemplazar = val;

            jugadores[id].puntaje_general = calcularPuntaje(&jugadores[id]);

            moveTo(padding_x + 1, *pos_y);
            printf("Continuar modificando campos? (0 / 1): ");
            scanf("%d", &continuar_campos);
            moveTo(padding_x + 1, *pos_y);
            printf("                                                                ");
            
        }
        moveTo(padding_x + 1, *pos_y);
        printf("Guardar en archivo? (0 / 1): ");
        scanf("%d", &grabar);
        moveTo(padding_x + 1, *pos_y);
        printf("                                                                ");

        if(grabar == 1)
        {
            cargarNuevoJugadorEnArchivo(archivo, id, jugadores[id]);
        }

        moveTo(padding_x + 1, *pos_y);
        printf("Continuar? (0 / 1): ");
        scanf("%d", &continuar);
        moveTo(padding_x + 1, *pos_y);
        printf("                                                                ");
    }
}