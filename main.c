#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "utils.h"

struct un_jugador
{
    int id;
    char nombre[16 + 1];

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

float calcularPuntaje(struct un_jugador*);
void moverPunteroADatos(FILE*);
int calcularCantidadDeJugadores(FILE*);
int siguienteComa(char*, int);
float conseguirSiguienteFloat(char*, int*, int*);
void cargarListaDeJugadores(FILE*, struct un_jugador*);
void mostrarJugador(struct un_jugador);
void jugadorFueElegido(int);
void elegirJugadores(struct un_jugador***, struct un_jugador*, const int);
void ordenarListaDeJugadores(struct un_jugador**, const int);
void mostrarListadoJugadores(struct un_jugador*, const int, const int);
void ordenarEquipo(struct un_equipo*, const int);
float calcularPromedio(struct un_jugador**, int);
float calcularVarianza(struct un_jugador **, int, int);
float calcularDispersion(struct un_jugador**, int);
void calcularProbabilidadDeGanar(struct un_equipo*, struct un_equipo*, int);
void generarEquiposBalanceadamente(struct un_jugador**, struct un_equipo*, struct un_equipo*, int);
void mostrarEquipos(struct un_equipo*, int);

int main(void)
{
    FILE *archivo_jugadores = fopen("jugadores.csv", "rt");
    const int cantidad_jugadores = calcularCantidadDeJugadores(archivo_jugadores);
    struct un_jugador *jugadores = malloc(cantidad_jugadores * sizeof(struct un_jugador));
    int input;
    int tam_equipo = 0;

    cargarListaDeJugadores(archivo_jugadores, jugadores);
    ordenarListaDeJugadores(&jugadores, cantidad_jugadores);
    fclose(archivo_jugadores);

    enableANSI();
    clearScreen();
    printf("   S I S T E M A    D E    G E S T I Ó N    D E    E Q U I P O S\n");
    printf("   1: Generar equipos balanceadamente\n");
    printf("   2: Evaluar balance de equipos\n");

    setColor(FGRN, BBLK);
    printf("   Elija una opción: ");
    scanf("%d", &input);
    setColor(FWHT, BBLK);

    _sleep(1000);
    clearScreen();

    mostrarListadoJugadores(jugadores, cantidad_jugadores, tam_equipo);

    moveTo(3, 37);
    printf("Ingrese el tamaño de los equipos: ");
    scanf("%d", &tam_equipo);
    moveTo(3, 37);
    printf("                                      ");


    struct un_jugador **jugadores_disponibles = malloc(tam_equipo * 2 * sizeof(struct un_jugador *));

    elegirJugadores(&jugadores_disponibles, jugadores, tam_equipo * 2);

    struct un_equipo equipo1;
    equipo1.jugadores = malloc(tam_equipo * sizeof(struct un_jugador *));

    struct un_equipo equipo2;
    equipo2.jugadores = malloc(tam_equipo * sizeof(struct un_jugador *));


    if (input == 1)
    {
        generarEquiposBalanceadamente(jugadores_disponibles, &equipo1, &equipo2, tam_equipo * 2);
    }
    else if (input == 2)
    {
        for (int i = 0; i < tam_equipo; i++)
        {
            equipo1.jugadores[i] = jugadores_disponibles[i];
            equipo2.jugadores[i] = jugadores_disponibles[i + tam_equipo];
            
            equipo1.num = 0;
            equipo2.num = 1;
        }
        calcularProbabilidadDeGanar(&equipo1, &equipo2, tam_equipo);
    }
    struct un_equipo equipos[2] = {equipo1, equipo2};

    //float probabilidadDeGanar = 
    mostrarEquipos(equipos, tam_equipo);

    moveTo(2, 42);

    free(jugadores);
    free(equipo1.jugadores);
    free(equipo2.jugadores);

    return 0;
}



// Función para calcular el puntaje
float calcularPuntaje(struct un_jugador *jugador)
{
    // Pesos para cada habilidad
    float w_R = 0.75; // Resistencia
    float w_V = 0.5;  // Velocidad
    float w_C = 1.0;  // Control del balón
    float w_D = 0.75; // Defensa
    float w_AT = 1.0; // Ataque
    float w_G = 0.5;  // Gambeta
    float w_CU = 0.5; // Cuerpo
    float w_P = 0.5;   // Porteria
    float w_VJ = 1.0;  // Visión de juego
    float w_JE = 0.75; // Juego en equipo

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
    puntaje /= suma_pesos;

    return puntaje;
}

void moverPunteroADatos(FILE *archivo)
{

    const int MAX_LENGTH = 150;
    char buffer[MAX_LENGTH];

    const int cant = 1;
    fseek(archivo, 0, SEEK_SET);
    for (int i = 0; i < cant; i++)
    {
        fgets(buffer, MAX_LENGTH, archivo);
    }
}

int calcularCantidadDeJugadores(FILE *archivo)
{
    const int MAX_LENGTH = 150;
    char buffer[MAX_LENGTH];

    moverPunteroADatos(archivo);

    int cantidad = 0;
    while (fgets(buffer, MAX_LENGTH, archivo))
    {
        cantidad++;
    }
    // moveTo(3, 1);
    // printf("Cantidad de jugadores disponibles: %d", cantidad);

    return cantidad;
}

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
    moverPunteroADatos(archivo);
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

void mostrarJugador(struct un_jugador jugador)
{
    const int paddingX = 5;
    const int paddingY = 11;
    int x = floor(jugador.id / 5) * 30 + paddingX;
    int y = (jugador.id % 5) * 5 + paddingY;
    moveTo(x, y);
    printf("ID: %d\n", jugador.id);
    moveTo(x, ++y);
    printf("    Nombre: %s\n", jugador.nombre);

    /*
    printf("Resistencia: %.2f\n", jugador.resistencia);
    printf("Velocidad: %.2f\n", jugador.velocidad);
    printf("Control: %.2f\n", jugador.control);
    printf("Defensa: %.2f\n", jugador.defensa);
    printf("Ataque:%.2f\n", jugador.ataque);
    printf("Vision: %.2f\n", jugador.vision);
    printf("Juego en equipo: %.2f\n", jugador.juego_equipo);
    */
    moveTo(x, ++y);
    printf("    PUNTAJE : %.2f\n", jugador.puntaje_general);
}

void jugadorFueElegido(int id)
{
    const int paddingX = 5;
    const int paddingY = 11;
    int x = floor(id / 5) * 30 + paddingX;
    int y = (id % 5) * 5 + paddingY;
    moveTo(x + 8, y);
    setColor(FGRN, BBLK);
    printf("ELEGIDO");
    setColor(FWHT, BBLK);
}

void elegirJugadores(struct un_jugador ***jugadores_disponibles, struct un_jugador *jugadores, const int cant_jugadores)
{
    int indice_jugador = 0;
    int contador = 0;

    moveTo(3, 37);
    printf("Elija ");
    setColor(FGRN, BBLK);
    printf("%d", cant_jugadores - contador);
    setColor(FWHT, BBLK);
    printf(" jugadores: ");
    scanf("%d", &indice_jugador);
    while (contador < cant_jugadores && indice_jugador > -1)
    {
        (*jugadores_disponibles)[contador] = &jugadores[indice_jugador];
        jugadorFueElegido(indice_jugador);
        moveTo(3, 37);
        printf("                        ");
        contador++;
        if (contador < cant_jugadores)
        {
            moveTo(3, 37);
            printf("Elija ");
            setColor(FGRN, BBLK);
            printf("%d", cant_jugadores - contador);
            setColor(FWHT, BBLK);
            printf(" jugadores: ");
            scanf("%d", &indice_jugador);
        }
    }
    printf("\n");
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

void mostrarListadoJugadores(struct un_jugador *jugadores, const int cantidad_jugadores, const int tam_equipo)
{
    const int yStart = 2;
    int y = yStart;
    moveTo(3, y);
    printf(" -------------------------------------------------------------------------------------------------------------------");
    moveTo(28, ++y);
    printf("          _ _   _  ____    _    ____   ___  ____  _____ ____       ");
    moveTo(28, ++y);
    printf("         | | | | |/ ___|  / \\  |  _ \\ / _ \\|  _ \\| ____/ ___|      ");
    moveTo(28, ++y);
    printf("      _  | | | | | |  _  / _ \\ | | | | | | | |_) |  _| \\___ \\      ");
    moveTo(28, ++y);
    printf("     | |_| | |_| | |_| |/ ___ \\| |_| | |_| |  _ <| |___ ___) |     ");
    moveTo(28, ++y);
    printf("      \\___/ \\___/ \\____/_/   \\_\\____/ \\___/|_| \\_\\_____|____/      ");
    moveTo(28, ++y);
    printf("                                                                   ");
    moveTo(3, ++y);
    printf(" -------------------------------------------------------------------------------------------------------------------");

    y = yStart + 1;
    int j = 0;
    while (j < 5 * 5 + 7)
    {
        moveTo(3, y + j);
        printf("|");
        moveTo(119, y + j);
        printf("|");
        j++;
    }
    moveTo(3, y + j);
    printf(" -------------------------------------------------------------------------------------------------------------------");

    for (int i = 0; i < cantidad_jugadores; i++)
    {
        jugadores[i].id = i;
        mostrarJugador(jugadores[i]);
    }
}

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
    float proba = 0.5 * erfc(-x * M_SQRT1_2);
    return proba;
}

void calcularProbabilidadDeGanar(struct un_equipo *eq1, struct un_equipo *eq2, int tam_equipo)
{

    eq1->promedio = calcularPromedio(eq1->jugadores, tam_equipo);
    eq2->promedio = calcularPromedio(eq2->jugadores, tam_equipo);

    const float modificador = 1;
    //float esperanza = (eq1->promedio + sqrt(eq1->varianza) - (eq2->promedio + sqrt(eq2->varianza))) * modificador;
    float esperanza = eq1->promedio - eq2->promedio;
    //esperanza *= modificador;

    eq1->varianza = calcularVarianza(eq1->jugadores, tam_equipo, eq1->promedio);
    eq2->varianza  = calcularVarianza(eq2->jugadores, tam_equipo, eq2->promedio);
    float varianza = eq1->varianza + eq2->varianza;
    //varianza *= modificador;

    eq1->probabilidadGanar = 1 - phi((0 - esperanza / sqrt(varianza)) * 2);
    eq2->probabilidadGanar = 1 - eq1->probabilidadGanar;
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