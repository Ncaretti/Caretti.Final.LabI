/*
 * Parser.c
 *
 *  Created on: Nov 23, 2021
 *      Author: Seether
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Parser.h"
#include "log.h"

int parser_log(FILE* pFile, LinkedList* this)
{
    int ret = 0;
    char date[11];
    char time[6];
    char serviceName[65];
    char gravedad[128];
    char msg[65];
    S_LogEntry* pLog;

    if(pFile != NULL && this != NULL)
    {
        fscanf(pFile,"%s\n",msg);
         while(!feof(pFile))
        {
           if(fscanf(pFile,"%[^;];%[^;];%[^;];%[^;];%[^\n] \n",date,time,serviceName,gravedad, msg) == 5)
           {
        	   pLog = log_newParametrosStr(date, time, serviceName, gravedad, msg);
               ll_add(this,pLog);
           }
           else
           {
        	   printf("Error\n");
               break;
           }
        }
        ret = 1;
    }

    return ret;
}
