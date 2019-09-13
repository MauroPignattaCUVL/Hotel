#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //strcmp
#include "hotel.h"

int main(int argc, char** argv) {

    char option[11];
    printf("Inicializar habitaciones? Y/N: ");
    scanf("%s",option);
    stringUpper(option);  // convierte cadena a mayuscula
    
    if(!strcmp(option,"Y"))
    {
        InitializeRooms(); // crea e inicializa el archivo
        printf("\nArchivo de habitaciones inicializado con exito.\n");
    }
    
    FILE * rooms = fopen("hotel","r+b");
    // comprueba que el archivo se haya abierto correctamente
    if (!rooms)
    {
        printf ("No se pudo abrir el archivo");
        exit(EXIT_FAILURE);       
    }
    
    while(1)
    {
        printf("\nQue desea hacer?\n");
        printf ("Reservar    Liberar \nListado     Salir\n");
        scanf("%s",option);
        stringUpper(option);  // convierte cadena a mayusculas
        if(!strcmp(option,"RESERVAR" ))
        {
            ReserveRoom(rooms);
        }
        if(!strcmp(option, "LIBERAR"))
        {
            FreeRoom(rooms);
        }
        if(!strcmp(option, "LISTADO"))
        {
            PrintList(rooms);
        }
        if(!strcmp(option, "SALIR"))
        {
            exit(EXIT_SUCCESS);
        }
    }
    return (EXIT_SUCCESS);
}

