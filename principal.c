#include <stdio.h>

#define UN_JUGADOR      1
#define DOS_JUGADORES   2
#define ESTADISTICAS    3
#define SALIR           4


/* Estructuras */
struct Pregunta {
	int dificultad;
	char pregunta[256];
	char respuesta_posible[4][64];
	int respuesta_correcta;
};

struct Jugador {
	char nombre[64];
	int puntuacion;
	int tiempo_parcial[3];
	int tiempo_final;
}

struct Puntuaciones {
	Jugador top10_jugadores_single[10];
	Jugador top10_jugadores_dobles[2][10];
}

/* Declaracion de Funciones auxiliares */
int Banner(void);
int Banner_Salir(void);
Pregunta LeerPreguntaCSV(int dificultad);
int EscribirPuntuacionJugadoresCSV(Jugador jug[2], int num_jugadores);
Puntuaciones LeerPuntuacionJugadoresCSV(int num_jugadores);
int ComenzarJuego(int num_jugadores);
int LeerEstadisticas(void);
int Salir(void);

/* Funcion principal */
int main()
{

    int inicio_eleccion = 0;
    int inicio_correcto = 0;

    /* Lanzar banner con titulo y luego breves instrucciones */

    /* Menu principal con formato y color */
    printf("%cQu%c quieres hacer ahora? (Introduce una de las 3 opciones):\n\n", 168, 130); // Numeros ASCII para é y ?
    printf("1 - Comenzar a Jugar -- 1 jugador\n");
    printf("2 - Comenzar a Jugar -- 2 jugadores\n");
    printf("3 - Ver tabla de las mejores puntuaciones\n");
    printf("4 - Salir del juego\n");
    scanf("%d", &inicio_eleccion);
    fflush(stdin);

    do
    {
        switch (inicio_eleccion)
        {
            case UN_JUGADOR:
            {
                printf("\nBien!!! Has elegido jugar solo. Vamos all%c!!!\n", 160); // Numero ASCII para á
                inicio_correcto = 1;
                /* Llamar a funcion de un solo jugador */
                break;
            }
            case DOS_JUGADORES:
            {
                printf("\nVaya!. Veo que quieres competencia. Que gane el mejor!!!!\n");
                inicio_correcto = 1;
                /* Llamar a funcion multijugador */
                break;
            }
            case ESTADISTICAS:
            {
                printf("\nEsta es la tabla de las mejores puntuaciones\n");
                inicio_correcto = 1;
                /* Llamar a funcion de mostrar estadisticas del juego (tiempo, puntos, veces jugadas, etc) */
                break;
            }
            case SALIR:
            {
                printf("\nBueno, pues nos vemos dentro de poco. P%csalo bien ah%c fuera!!!\n", 160, 214); // Numeros ASCII para á e í
                inicio_correcto = 1;
                break;
            }
            default:
            {
                printf("\nOpci%cn erronea. Por favor, introduce 1, 2, 3 o 4:\n", 162); // Numero ASCII para ó
                scanf("%d", &inicio_eleccion);
                fflush(stdin);
            }
        }
    }
    while(inicio_correcto != 1);

    return 0;
}

/* Definicion de funciones auxiliares */
int Banner(void)
{
	
}

int Banner_Salir(void)
{
	
}

Pregunta LeerPreguntaCSV(int dificultad)
{
	
}

int EscribirPuntuacionJugadoresCSV(Jugador jug[2], int num_jugadores)
{
	
}

Puntuaciones LeerPuntuacionJugadoresCSV(int num_jugadores)
{
	
}

int ComenzarJuego(int num_jugadores)
{
	
}

int LeerEstadisticas(void)
{
	
}

int Salir(void)
{
	
}
