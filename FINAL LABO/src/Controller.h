/*
 * Controller.h
 *
 *  Created on: 15 dic. 2021
 *      Author: Seether
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

int controller_loadFromText(char* path , LinkedList* this);
int controller_elegirArchivo(LinkedList* this);
int controller_listLog(LinkedList* this);
int controller_filtrarPorErrores(LinkedList* this, int opcion);
int controller_menuFiltros(LinkedList* this);


#endif /* CONTROLLER_H_ */
