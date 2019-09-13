#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FUNC_H
#define FUNC_H

#define nameLength 20
#define MaxRooms 100
#define EmailLength 70

typedef struct {
    char name[nameLength + 1];
    char lastname[nameLength + 1];
    char email[EmailLength + 1];
    int age;
    int dni;
    int days;
}Client;

typedef struct {
    int roomID;
    bool available;
    Client client;
}Room;

#ifdef __cplusplus
extern "C" {
#endif
    
/*crea el archivo y marca las habitaciones como disponibles*/
void InitializeRooms(); 
/*reserva una habitacion*/
void RoomReservation(FILE *rooms);
/*libera una habitacion*/
void FreeRoom (FILE *rooms);
/*Imprime el listado de habitaciones*/
void PrintList (FILE *rooms); 
/*pone todos los caracteres de la cadena en mayuscula*/
void stringUpper(char *str);

#ifdef __cplusplus
}
#endif

#endif /* FUNC_H */

