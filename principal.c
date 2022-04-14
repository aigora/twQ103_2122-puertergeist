#include <stdio.h>


int main()
{

    int inicio_eleccion = 0;
    int inicio_correcto = 0;

	/* Lanzar banner con titulo y luego breves instrucciones */

	/* Menu principal con formato y color */
	printf("%cQu%c quieres hacer ahora? (Introduce una de las 3 opciones):\n\n", 168, 130); // Numeros ASCII para é y ?
	printf("1 - Comenzar a Jugar -- 1 jugador\n");
	printf("2 - Comenzar a Jugar -- 2 jugadores\n");
	printf("3 - Ver tabla de mejores puntuaciones\n");
	scanf("%d", &inicio_eleccion);
	fflush(stdin);

	do
	{
        if (inicio_eleccion == 1)
        {
            printf ("\nBien!!! Has elegido jugar solo. Vamos all%c!!!\n", 160); // Numero ASCII para á
            inicio_correcto = 1;
            /* Llamar a funcion de un solo jugador */
        }
        else if (inicio_eleccion == 2)
        {
            printf ("\nVaya!. Veo que quieres competencia. Que gane el mejor!!!!\n");
            inicio_correcto = 1;
            /* Llamar a funcion multijugador */
        }
        else if (inicio_eleccion == 3)
        {
            printf ("\nEsta es la tabla de los mejores puntuaciones\n");
            inicio_correcto = 1;
            /* Llamar a funcion de mostrar estadisticas del juego (tiempo, puntos, veces jugadas, etc) */
        }
        else
        {
            printf ("\nOpci%cn erronea. Por favor, introduce 1, 2 o 3:\n", 162); // Numero ASCII para ó
            scanf("%d", &inicio_eleccion);
            fflush(stdin);
        }
	}
	while(inicio_correcto != 1);

	return 0;
}
