#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "log.h"
#include "Parser.h"
#include "validaciones.h"

int controller_loadFromText(char* path , LinkedList* this)
{
	int ret = 0;

	FILE* pFile = fopen (path,"r");

	if(path != NULL && this != NULL)
	{
		if(pFile != NULL)
		{
			if(parser_log(pFile, this))
			{
				ret = 1;
			}
		}
		fclose(pFile);
	}

    return ret;
}

int controller_elegirArchivo(LinkedList* this)
{
	int ret = 0;
	char archivo[20];

	if(getString(archivo, 20, 3, "Ingrese el nombre del archivo: ", "Error, ingrese un nombre valido.\n"))
	{
		ll_clear(this);
	}

	if(controller_loadFromText(archivo, this))
	{
		printf("El archivo se ha cargado con exito.\n");
		ret = 1;
	}
	else
	{
		printf("Error, el archivo no existe o hubo un error en la carga.\n");
	}

	return ret;
}

int controller_listLog(LinkedList* this)
{
    int contLog = 0;
    int ret = 0;
    int tam;
    int i;
    S_LogEntry* pLog;

    if(ll_isEmpty(this) == 0)
    {

    	tam = ll_len(this);

        printf("DATE           TIME       SERVICE_NAME          GRAVEDAD       MSG\n");

        for(i=1; i<tam; i++)
        {
        	pLog = (S_LogEntry*) ll_get(this, i);

            printf("%-12s   %-6s %-25s  %d           %-65s\n", pLog->date, pLog->time, pLog->serviceName, pLog->gravedad, pLog->msg);
            contLog++;
        }
        if(contLog == tam)
        {
        	ret = 1;
        }
    }
    return ret;
}

int controller_saveAsText(char* path , LinkedList* this)
{
    int ret = 0;
    int tam;
    int i;
    char date[20];
    char time[20];
    char serviceName[65];
    int gravedad;
    char msg[65];
    FILE* pFile;
    S_LogEntry* auxLog = NULL;

    if(this != NULL && path != NULL)
    {
        pFile = fopen(path, "w");
        tam = ll_len(this);

        if(pFile != NULL)
        {
            fprintf(pFile, "Fecha;Hora;Nombre_Servicio;Gravedad;Msg_Error\n");
            for(i=0; i<tam; i++)
            {
            	auxLog = (S_LogEntry*) ll_get(this, i);

                log_getDate(auxLog, date);
                log_getTime(auxLog, time);
                log_getServiceName(auxLog, serviceName);
                log_getGravedad(auxLog, &gravedad);
                log_getMsg(auxLog, msg);

                fprintf(pFile, "%s;%s;%s;%d;%s\n", date, time, serviceName, gravedad, msg);
            }
        }
        fclose(pFile);
        ret = 1;
    }
    return ret;
}

int controller_filtrarPorErrores(LinkedList* this, int opcion)
{
	int ret = 0;
	int tam;
	int i;
	S_LogEntry* auxLog = NULL;
	LinkedList* auxLogMenosTres = ll_newLinkedList();
	LinkedList* auxLogTres = ll_newLinkedList();
	LinkedList* auxLogCuatroSiete = ll_newLinkedList();
	LinkedList* auxLogSiete = ll_newLinkedList();
	tam = ll_len(this);

	if(this != NULL)
	{
		for(i=1;i<tam;i++)
		{
			auxLog = ll_get(this, i);

			if(auxLog->gravedad < 3)
			{
				auxLogMenosTres = ll_filter(this, log_filtroGravedadMenosTres);
			}
			if(auxLog->gravedad == 3)
			{
				auxLogTres = ll_filter(this, log_filtroGravedadIgualTres);
				ret = 1;
			}

			if(auxLog->gravedad >= 4 &&  auxLog->gravedad <= 7)
			{
				auxLogCuatroSiete = ll_filter(this, log_filtroGravedadEntreCuatroYSiete);
				ret = 1;
			}

			if(auxLog->gravedad > 7)
			{
				auxLogSiete = ll_filter(this, log_filtroGravedadMayorASiete);
				ret = 1;
			}
		}

		controller_saveAsText("warnings.txt", auxLogTres);
		controller_saveAsText("errors.txt", auxLogSiete);

		if(opcion == 1)
		{
			controller_listLog(auxLogMenosTres);
		}
		else if(opcion == 2)
		{
			controller_listLog(auxLogTres);
		}
		else if(opcion == 3)
		{
			controller_listLog(auxLogCuatroSiete);
		}
		else if(opcion == 4)
		{
			controller_listLog(auxLogSiete);
		}
		else if(opcion == -1)
		{
			printf("IMPRIMIENDO ERRORES ENTRE 4 Y 7:\n");
			controller_listLog(auxLogCuatroSiete);
		}
	}



	return ret;
}

int controller_menuFiltros(LinkedList* this)
{
	int ret = 0;
	int opcion;

	printf("MENU ESTADISTICAS:\n"
		   "1- Menores a 3\n"
		   "2- 3\n"
		   "3- 4 y 7 (inclusive)\n"
		   "4- Mayores a 7\n"
		   "5- SALIR\n");
	printf("Ingrese la opcion deseada: ");
	validarEntero(&opcion, 1, 5);

	switch(opcion)
	{
		case 1:
			controller_filtrarPorErrores(this, 1);
		break;

		case 2:
			controller_filtrarPorErrores(this, 2);
		break;

		case 3:
			controller_filtrarPorErrores(this, 3);
		break;

		case 4:
			controller_filtrarPorErrores(this, 4);
		break;

		case 5:
			printf("Ha salido con exito.\n");
		break;

		default:
			printf("Error, ingrese una opcion valida.\n");
		break;
	}

	return ret;
}
