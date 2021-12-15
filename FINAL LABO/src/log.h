/*
 * log.h
 *
 *  Created on: 15 dic. 2021
 *      Author: Seether
 */

#ifndef LOG_H_
#define LOG_H_
typedef struct
{
	char date[11];
	char time[6];
	char serviceName[65];
	int gravedad;
	char msg[65];
}S_LogEntry;

S_LogEntry* log_new();
S_LogEntry* log_newParametrosStr(char* date,char* time,char* serviceName, char* gravedad, char* msg);

int log_setDate(S_LogEntry* this,char* date);
int log_setTime(S_LogEntry* this,char* time);
int log_setServiceName(S_LogEntry* this,char* serviceName);
int log_setGravedad(S_LogEntry* this,int gravedad);
int log_setMsg(S_LogEntry* this,char* msg);

int log_getDate(S_LogEntry* this,char* date);
int log_getTime(S_LogEntry* this,char* time);
int log_getServiceName(S_LogEntry* this,char* serviceName);
int log_getGravedad(S_LogEntry* this,int* gravedad);
int log_getMsg(S_LogEntry* this,char* msg);

int log_filtroGravedadMenosTres(void* log);
int log_filtroGravedadIgualTres(void* log);
int log_filtroGravedadEntreCuatroYSiete(void* log);
int log_filtroGravedadMayorASiete(void* log);

#endif /* LOG_H_ */
