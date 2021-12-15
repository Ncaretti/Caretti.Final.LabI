/*
 ============================================================================
 Name        : FINAL.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LinkedList.h"
#include "log.h"
#include "Parser.h"
#include "Controller.h"

int main(void)
{

	setbuf(stdout, NULL);
    int opcion = 0;
    int flagAlta = 0;

    LinkedList* this = ll_newLinkedList();

    do{
        printf("Menu:\n"
       		 "1. Leer log\n"
       		 "2. Procesar informacion\n"
       		 "3. Mostrar estadisticas\n"
       		 "4. Salir\n");
        scanf("%d", &opcion);

        switch(opcion)
        {
        	case 1:
        		if(controller_loadFromText("log.txt", this))
        		{
        			flagAlta = 1;
        			controller_listLog(this);
        			printf("\nArchivo cargado con exito.\n");
        		}
        		system("pause");
        	break;

        	case 2:
        		if(flagAlta)
        		{
					if(controller_filtrarPorErrores(this, -1))
					{
						printf("\nLa informacion ha sido procesada con exito, acceda a la opcion 3 del menu para ver los nuevos informes con los errores.\n");
					}
					else
					{
						printf("Error al crear los informes.\n");
					}
        		}
        		else
        		{
        			printf("Error, primero cargue el archivo de la opcion 1.\n");
        		}
        		system("pause");
        	break;

        	case 3:
        		if(flagAlta)
        		{
        			controller_menuFiltros(this);
        		}
        		else
        		{
        			printf("Error, primero cargue el archivo de la opcion 1.\n");
        		}
        		system("pause");
        	break;

        	case 4:
        		printf("Ha salido con exito.\n");
        	break;
        }
    }while(opcion != 4);
}
