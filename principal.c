#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UN_JUGADOR      1
#define DOS_JUGADORES   2
#define ESTADISTICAS    3
#define SALIR           4
#define N 22            5



/* Estructuras */
struct Pregunta {
	int numero_pregunta;
	char pregunta[256];
	char respuesta_posible[4][64];
	int respuesta_correcta;
};

struct Jugador {
	char nombre[64];
	int puntuacion;
	int tiempo_parcial[3];
	int tiempo_final;
};

struct Puntuaciones {
	struct Jugador top10_jugadores_single[10];
	struct Jugador top10_jugadores_dobles[2][10];
};

/* Declaracion de Funciones auxiliares */
int Banner(void);
int Banner_Salir(void);
struct Pregunta LeerPreguntaCSV(int dificultad);
int EscribirPuntuacionJugadoresCSV(struct Jugador jug[2], int num_jugadores);
struct Puntuaciones LeerPuntuacionJugadoresCSV(int num_jugadores);
int ComenzarJuego(int num_jugadores);
int LeerEstadisticas(void);
int Salir(void);

/* Funcion principal */
int main()
{

    int inicio_eleccion = 0;
    int inicio_correcto = 0;
    int ver_menu = 1;

    /* Lanzar banner con titulo y luego breves instrucciones */

    do
    {
        if (ver_menu)
        {
            /* Menu principal con formato y color */
            printf("%cQu%c quieres hacer ahora? (Introduce una de las 4 opciones):\n\n", 168, 130); // Numeros ASCII para é y ?
            printf("1 - Comenzar a Jugar -- 1 jugador\n");
            printf("2 - Comenzar a Jugar -- 2 jugadores\n");
            printf("3 - Ver tabla de las mejores puntuaciones\n");
            printf("4 - Salir del juego\n");
            scanf("%d", &inicio_eleccion);
            fflush(stdin);
            ver_menu = 0;
        }

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
                LeerEstadisticas();
                ver_menu = 1;
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

static unsigned int ContadorLineas(int dificultad)
{
    int contador_lineas = 0;
    int caracter;

    /* Abrimos el archivo en modo lectura */
    FILE *fichero_preguntas;
    fichero_preguntas = fopen("preguntas.txt","r");
    if (fichero_preguntas == NULL)
    {
        printf("Error en la lectura del fichero preguntas.txt. Fin del programa\n");
        return 0;
    }

    /* Contamos cuantas preguntas son de la dificultad seleccionada */
    do
    {
        caracter = fgetc(fichero_preguntas);
        if (dificultad == 1)
        {
            if (caracter == 35) /* 35 es el caracter # en ASCII */
            {
                contador_lineas++;
            }
        }
        else
        {
            if (caracter == 36) /* 36 es el $ en ASCII */
            {
                contador_lineas++;
            }
        }
    }
    while (caracter != EOF);

    /* Cerramos el fichero */
    fclose(fichero_preguntas);

    return contador_lineas;
}

static struct Pregunta LeerPregunta(int dificultad, int num_aleatorio)
{
    int pregunta_detectada = 0, contador_preguntas = 0, contador_separador = 0, i = 0, j = 0, k = 0, l = 0, m = 0, n = 0;
    int caracter;
    struct Pregunta pregunta_seleccionada;

    /* Abrimos el archivo en modo lectura */
    FILE *fichero_preguntas;
    fichero_preguntas = fopen("preguntas.txt","r");
    if (fichero_preguntas == NULL) {
        printf("Error en la lectura del fichero preguntas.txt. Fin del programa\n");
        return pregunta_seleccionada;
    }

    /* Nos situamos en la pregunta aleatoria seleccionada */
    while (pregunta_detectada == 0)
    {
        caracter = fgetc(fichero_preguntas);
        if (dificultad == 1)
        {
            if (caracter == 35) /* 35 es el caracter # en ASCII */
            {
                contador_preguntas++;
                if (contador_preguntas == num_aleatorio)
                {
                    pregunta_detectada = 1;
                }
            }
        }
        else
        {
            if (caracter == 36) /* 36 es el $ en ASCII */
            {
                contador_preguntas++;
                if (contador_preguntas == num_aleatorio)
                {
                    pregunta_detectada = 1;
                }
            }
        }
    }

    /* Leemos los datos de la pregunta */
    while (1)
    {
        caracter = fgetc(fichero_preguntas);
        if (caracter == ';')
        {
            contador_separador++;
            caracter = fgetc(fichero_preguntas);
        }

        if (caracter == 10) /* 10 es el caracter '\n' en ASCII */
        {
            break;
        }

        switch (contador_separador)
        {
            case 0:
            {
                break;
            }
            case 1:
            {
                pregunta_seleccionada.pregunta[i] = caracter;
                i++;
                break;
            }
            case 2:
            {
                if (j == 0)
                {
                    pregunta_seleccionada.pregunta[i] = '\0';
                }
                pregunta_seleccionada.respuesta_posible[0][j] = caracter;
                j++;
                break;
            }
            case 3:
            {
                if (k == 0)
                {
                    pregunta_seleccionada.respuesta_posible[0][j] = '\0';
                }
                pregunta_seleccionada.respuesta_posible[1][k] = caracter;
                k++;
                break;
            }
            case 4:
            {
                if (l == 0)
                {
                    pregunta_seleccionada.respuesta_posible[1][k] = '\0';
                }
                pregunta_seleccionada.respuesta_posible[2][l] = caracter;
                l++;
                break;
            }
            case 5:
            {
                if (m == 0)
                {
                    pregunta_seleccionada.respuesta_posible[2][l] = '\0';
                }
                pregunta_seleccionada.respuesta_posible[3][m] = caracter;
                m++;
                break;
            }
            case 6:
            {
                if (n == 0)
                {
                    pregunta_seleccionada.respuesta_posible[3][m] = '\0';
                }
                pregunta_seleccionada.respuesta_correcta = caracter - 48; /* conversion ASCII a numero */
                n++;
                break;
            }
        }
    }
    /* Cerramos el fichero */
    fclose(fichero_preguntas);

    return pregunta_seleccionada;
}

struct Pregunta LeerPreguntaCSV(int dificultad)
{
    struct Pregunta pregunta_seleccionada;
    unsigned int num_lineas = 0, numero_aleatorio;

    /* Calculamos el numero de preguntas de la misma dificultad */
    num_lineas = ContadorLineas(dificultad);

    /* Seleccionamos una pregunta de manera aletoria */
    srand(time(NULL)); /* generamos la semilla aleatoria */
    numero_aleatorio = (rand() % num_lineas) + 1; /* obtenemos un valor aleatorio entre 1 y num_lineas */

    /* Leemos la pregunta seleccionada */
    pregunta_seleccionada = LeerPregunta(dificultad, numero_aleatorio);

    return pregunta_seleccionada;
}

int EscribirPuntuacionJugadoresCSV(struct Jugador jug[2], int num_jugadores)
{
    /* buffer para convertir enteros a cadena de caracteres */
    char buffer[128];

    /* Abrimos el archivo en modo escritura, posicionandonos al final del archivo */
    FILE *fichero_puntuaciones;
    fichero_puntuaciones = fopen("puntuaciones.txt", "a+");
    if (fichero_puntuaciones == NULL)
    {
        return 0;
    }

    if (num_jugadores == 2 && (jug[1].puntuacion > jug[0].puntuacion))
    {
        fputs("$ ", fichero_puntuaciones);
        fputs(jug[1].nombre, fichero_puntuaciones);
        fputs(" ", fichero_puntuaciones);
        sprintf(buffer, "%d", jug[1].puntuacion);
        fputs(buffer, fichero_puntuaciones);
        fputs(" ", fichero_puntuaciones);
        sprintf(buffer, "%d", jug[1].tiempo_final);
        fputs(buffer, fichero_puntuaciones);
    }

    if (num_jugadores == 1)
    {
        fputs("# ", fichero_puntuaciones);
    }
    else if(num_jugadores == 2 && (jug[0].puntuacion >= jug[1].puntuacion))
    {
        fputs("$ ", fichero_puntuaciones);
    }

    fputs(jug[0].nombre, fichero_puntuaciones);
    fputs(" ", fichero_puntuaciones);
    sprintf(buffer, "%d", jug[0].puntuacion);
    fputs(buffer, fichero_puntuaciones);
    fputs(" ", fichero_puntuaciones);
    sprintf(buffer, "%d", jug[0].tiempo_final);
    fputs(buffer, fichero_puntuaciones);


    if (num_jugadores == 2 && (jug[0].puntuacion >= jug[1].puntuacion))
    {
        fputs(" ", fichero_puntuaciones);
        fputs(jug[1].nombre, fichero_puntuaciones);
        fputs(" ", fichero_puntuaciones);
        sprintf(buffer, "%d", jug[1].puntuacion);
        fputs(buffer, fichero_puntuaciones);
        fputs(" ", fichero_puntuaciones);
        sprintf(buffer, "%d", jug[1].tiempo_final);
        fputs(buffer, fichero_puntuaciones);
    }

    fputs("\n", fichero_puntuaciones);
    fclose(fichero_puntuaciones);

    return 1;
}

struct Puntuaciones LeerPuntuacionJugadoresCSV(int num_jugadores)
{
    int i,k;
    char single_doble;
    struct Jugador jug[2];
    struct Puntuaciones puntuaciones_jugadores;

    FILE *fichero_puntuaciones = fopen("puntuaciones.txt","r");

    if(fichero_puntuaciones == NULL){
        printf("Error en la apertura de ficheros\n");
        return puntuaciones_jugadores;
    }

    for (k=0;k<10;k++)
    {
        puntuaciones_jugadores.top10_jugadores_single[k].nombre[0] = '\0';
        puntuaciones_jugadores.top10_jugadores_dobles[0][k].nombre[0] = '\0';
        puntuaciones_jugadores.top10_jugadores_dobles[1][k].nombre[0] = '\0';
        puntuaciones_jugadores.top10_jugadores_single[k].puntuacion = 0;
        puntuaciones_jugadores.top10_jugadores_dobles[0][k].puntuacion = 0;
        puntuaciones_jugadores.top10_jugadores_dobles[1][k].puntuacion = 0;
        puntuaciones_jugadores.top10_jugadores_single[k].tiempo_final = 0;
        puntuaciones_jugadores.top10_jugadores_dobles[0][k].tiempo_final = 0;
        puntuaciones_jugadores.top10_jugadores_dobles[1][k].tiempo_final = 0;
    }

    while(fscanf(fichero_puntuaciones,"%c %s %d %d ", &single_doble, jug[0].nombre, &jug[0].puntuacion, &jug[0].tiempo_final) != EOF)
    {
        if (single_doble == '$')
        {
            fscanf(fichero_puntuaciones,"%s %d %d ", jug[1].nombre, &jug[1].puntuacion, &jug[1].tiempo_final);
            for (i=0;i<10;i++)
            {
                if (jug[0].puntuacion > puntuaciones_jugadores.top10_jugadores_dobles[0][i].puntuacion)
                {
                    int j;
                    for (j = 9; j > i; j--)
                    {
                        puntuaciones_jugadores.top10_jugadores_dobles[0][j] = puntuaciones_jugadores.top10_jugadores_dobles[0][j-1];
                    }
                    puntuaciones_jugadores.top10_jugadores_dobles[0][i] = jug[0];
                    puntuaciones_jugadores.top10_jugadores_dobles[1][i] = jug[1];
                    break;
                 }
            }
        }
        else if (single_doble == '#')
        {
            for (i=0;i<10;i++)
            {
                if (jug[0].puntuacion > puntuaciones_jugadores.top10_jugadores_single[i].puntuacion)
                {
                    int j;
                    for (j = 9; j > i; j--)
                    {
                        puntuaciones_jugadores.top10_jugadores_single[j] = puntuaciones_jugadores.top10_jugadores_single[j-1];
                    }
                    puntuaciones_jugadores.top10_jugadores_single[i] = jug[0];
                    break;
                 }
            }
        }
    }

    fclose(fichero_puntuaciones);

    return puntuaciones_jugadores;
}

int ComenzarJuego(int num_jugadores)
{
	
}

int LeerEstadisticas(void)
{
    int i;
    time_t tiempo_inicial;
    struct Puntuaciones estadisticas = LeerPuntuacionJugadoresCSV(2);

    /* Inicializamos el tiempo para mostrar las estadisticas */
    tiempo_inicial = time(NULL);

    /* Limpiamos la consola */
    system("cls");

    /* Imprimimos el TOP 10 single */
    printf("El TOP 10 de los mejores jugadores en solitario es el siguiente:\n\n");
    for (i=0; i<10; i++)
    {
        if (i == 9)
        {
            printf("%d%s%s - %d puntos - %d minutos y %d segundos\n", i+1, ". ", estadisticas.top10_jugadores_single[i].nombre, estadisticas.top10_jugadores_single[i].puntuacion, estadisticas.top10_jugadores_single[i].tiempo_final / 60, estadisticas.top10_jugadores_single[i].tiempo_final % 60);
        }
        else
        {
            printf("%d%s%s - %d puntos - %d minutos y %d segundos\n", i+1, ".  ", estadisticas.top10_jugadores_single[i].nombre, estadisticas.top10_jugadores_single[i].puntuacion, estadisticas.top10_jugadores_single[i].tiempo_final / 60, estadisticas.top10_jugadores_single[i].tiempo_final % 60);
        }
    }

    /* temporizador */
    while((time(NULL) - tiempo_inicial) < 15)
    {
        /* esperamos 15 sec */
    }

    /* Inicializamos el tiempo de nuevo para mostrar las estadisticas de dobles*/
    tiempo_inicial = time(NULL);

    /* Limpiamos la consola de nuevo */
    system("cls");

    /* Imprimimos el TOP 10 dobles */
    printf("El TOP 10 de los mejores jugadores en dobles es el siguiente:\n\n");
    for (i=0; i<10; i++)
    {
        if (i == 9)
        {
            printf("%d%s%s - %d pts - %d min y %d seg vs %s - %d pts\n", i+1, ". ", estadisticas.top10_jugadores_dobles[0][i].nombre, estadisticas.top10_jugadores_dobles[0][i].puntuacion, estadisticas.top10_jugadores_dobles[0][i].tiempo_final / 60, estadisticas.top10_jugadores_dobles[0][i].tiempo_final % 60,
                                                                                    estadisticas.top10_jugadores_dobles[1][i].nombre, estadisticas.top10_jugadores_dobles[1][i].puntuacion);
        }
        else
        {
            printf("%d%s%s - %d pts - %d min y %d seg vs %s - %d pts\n", i+1, ".  ", estadisticas.top10_jugadores_dobles[0][i].nombre, estadisticas.top10_jugadores_dobles[0][i].puntuacion, estadisticas.top10_jugadores_dobles[0][i].tiempo_final / 60, estadisticas.top10_jugadores_dobles[0][i].tiempo_final % 60,
                                                                                     estadisticas.top10_jugadores_dobles[1][i].nombre, estadisticas.top10_jugadores_dobles[1][i].puntuacion);
        }
    }

    /* temporizador */
    while((time(NULL) - tiempo_inicial) < 15)
    {
        /* esperamos 15 sec */
    }

    /* Limpiamos la consola antes de volver */
    system("cls");

    return 1;
}

int Salir(void)
{
	
}
