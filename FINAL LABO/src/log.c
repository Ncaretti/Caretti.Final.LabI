#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"

S_LogEntry* log_new()
{
	S_LogEntry* nuevoLog;

	nuevoLog = (S_LogEntry*) malloc(sizeof(S_LogEntry));

	if(nuevoLog != NULL)
	{
		strcpy(nuevoLog->date, "NN");
		strcpy(nuevoLog->time, "NN");
		strcpy(nuevoLog->serviceName, "NN");
		nuevoLog->gravedad = 0;
		strcpy(nuevoLog->msg, "NN");
	}

	return nuevoLog;
}

S_LogEntry* log_newParametrosStr(char* date,char* time,char* serviceName, char* gravedad, char* msg)
{
	S_LogEntry* nuevoLogStr = log_new();

	if(nuevoLogStr != NULL)
	{
		if(!(log_setDate(nuevoLogStr, date)
			&& log_setTime(nuevoLogStr, time)
			&& log_setServiceName(nuevoLogStr, serviceName)
			&& log_setGravedad(nuevoLogStr, atoi(gravedad))
			&& log_setMsg(nuevoLogStr, msg)))
		{
			printf("Hubo un error.\n");
			free(nuevoLogStr);
			nuevoLogStr = NULL;
		}
	}
	return nuevoLogStr;
}

//--------------SETTERS------------//

int log_setDate(S_LogEntry* this,char* date)
{
	int ret = 0;

	if(this != NULL)
	{
		strcpy(this->date, date);
		ret = 1;
	}

	return ret;
}

int log_setTime(S_LogEntry* this,char* time)
{
	int ret = 0;

	if(this != NULL)
	{
		strcpy(this->time, time);
		ret = 1;
	}

	return ret;
}

int log_setServiceName(S_LogEntry* this,char* serviceName)
{
	int ret = 0;

	if(this != NULL)
	{
		strcpy(this->serviceName, serviceName);
		ret = 1;
	}

	return ret;
}

int log_setGravedad(S_LogEntry* this,int gravedad)
{
	int ret = 0;

	if(this != NULL)
	{
		this->gravedad = gravedad;
		ret = 1;
	}

	return ret;
}

int log_setMsg(S_LogEntry* this,char* msg)
{
	int ret = 0;

	if(this != NULL)
	{
		strcpy(this->msg, msg);
		ret = 1;
	}

	return ret;
}

//----------GETTERS----------//

int log_getDate(S_LogEntry* this,char* date)
{
	int ret = 0;

	if(this != NULL)
	{
		strcpy(date, this->date);
		ret = 1;
	}

	return ret;
}

int log_getTime(S_LogEntry* this,char* time)
{
	int ret = 0;

	if(this != NULL)
	{
		strcpy(time, this->time);
		ret = 1;
	}

	return ret;
}

int log_getServiceName(S_LogEntry* this,char* serviceName)
{
	int ret = 0;

	if(this != NULL)
	{
		strcpy(serviceName, this->serviceName);
		ret = 1;
	}

	return ret;
}

int log_getGravedad(S_LogEntry* this,int* gravedad)
{
	int ret = 0;

	if(this != NULL)
	{
		*gravedad = this->gravedad;
		ret = 1;
	}

	return ret;
}

int log_getMsg(S_LogEntry* this,char* msg)
{
	int ret = 0;

	if(this != NULL)
	{
		strcpy(msg, this->msg);
		ret = 1;
	}

	return ret;
}

//-------------FILTROS-----------//

int log_filtroGravedadMenosTres(void* log)
{
	int ret = 0;
	S_LogEntry* auxLog = NULL;

	if(log != NULL)
	{
		auxLog = (S_LogEntry*) log;

		if(auxLog->gravedad < 3)
		{
			ret = 1;
		}
	}

	return ret;
}
int log_filtroGravedadIgualTres(void* log)
{
	int ret = 0;
	S_LogEntry* auxLog = NULL;

	if(log != NULL)
	{
		auxLog = (S_LogEntry*) log;

		if(auxLog->gravedad == 3)
		{
			ret = 1;
		}
	}

	return ret;
}

int log_filtroGravedadEntreCuatroYSiete(void* log)
{
	int ret = 0;
	S_LogEntry* auxLog = NULL;

	if(log != NULL)
	{
		auxLog = (S_LogEntry*) log;

		if(auxLog->gravedad >=4 && auxLog->gravedad <= 7)
		{
			ret = 1;
		}
	}

	return ret;
}

int log_filtroGravedadMayorASiete(void* log)
{
	int ret = 0;
	S_LogEntry* auxLog = NULL;

	if(log != NULL)
	{
		auxLog = (S_LogEntry*) log;

		if(auxLog->gravedad > 7)
		{
			ret = 1;
		}

	}

	return ret;
}
