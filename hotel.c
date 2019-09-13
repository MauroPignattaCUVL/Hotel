#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  //toupper
#include "hotel.h"

void stringUpper(char *str)
{
    while(*str)
    {
        *str=toupper(*str);
        str++;
    }
}

void GetClientData(Room * room)
{
    printf("\nNombre y Apellido: ");
    scanf("%s %s",room->client.name,room->client.lastname);
    room->client.name[strlen(room->client.name)] = '\0';
    printf("DNI: ");
    scanf("%d",&room->client.dni);
    printf("Edad: ");
    scanf("%d",&room->client.age);
    printf("email: ");
    scanf("%s",room->client.email);
    printf("Cuantos dias va a hospedarse? ");
    scanf("%d",&room->client.days);
}

void InitializeRooms()
{
    FILE * file = fopen("hotel","wb");
    Room room;
    room.available = true;
    for (int i = 1; i < MaxRooms + 1; i++ )
    {
        room.roomID = i;
        fwrite(&room, sizeof(Room), 1, file);
    }
    fclose(file);
    return;
}

void ReserveRoom(FILE *rooms)
{
    int i=0;
    Room room;
    char option;
    printf("\nDesea alguna habitacion en especifico? Y/N \n");
    scanf(" %c",&option);
    int nRoom = -1;
    option = toupper(option); // pasa el caracter a mayuscula
    if(option == 'Y')
    {
        do
        {
            if(nRoom == -1)
                printf("\nTenemos 100 habitaciones, cual desea? ");
            else
            {
                printf("\nEsa habitacion se encuentra ocupada o no existe, elija otra ");
            }
            scanf("%d",&nRoom);
            fseek(rooms,(sizeof(Room)*(nRoom - 1)) , SEEK_SET);
            fread(&room, sizeof(Room), 1, rooms);
        }while(!(nRoom > 0 && nRoom < 101 && room.available));
    }
    else
    {
        do
        {
            fread(&room,sizeof(Room),1,rooms);
            i++;
        }while(!(room.available && i<100));
    }
    if (i < 100)
    {
        fseek(rooms, sizeof(Room)*(-1), SEEK_CUR);
        room.available = false;
        GetClientData(&room);
        fwrite(&room,sizeof(Room),1,rooms);
        printf("\nCliente registrado\n");
    }
    else
    {
        printf("\nNo hay habitaciones disponibles\n");
    }
    fseek(rooms, 0,SEEK_SET);
}

void FreeRoom (FILE *rooms)
{
    int nRoom = 0;
    Room room;
    puts("\nIngrese numero de la habitacion a liberar");
    scanf("%d", &nRoom);
    fseek(rooms,(sizeof(Room)*(nRoom - 1)) , SEEK_SET);
    fread(&room, sizeof(Room), 1, rooms);
    fseek(rooms, sizeof(Room)*(-1), SEEK_CUR);
    if (!room.available)
    {
        room.available=true;
        fwrite(&room,sizeof(Room),1,rooms);
        printf("\nSe libero la habitacion %d\n",room.roomID);
    }
    else
    {
        printf("\nYa esta desocupada o no existe\n");
    }
    fseek(rooms, 0,SEEK_SET);
}

void PrintList (FILE *rooms)
{
    Room room;
    int i = 0;
    while (i <100)
    {
        fread(&room, sizeof(Room), 1, rooms);
        printf("Habitacion %d ", room.roomID);
        if (room.available)
            printf("esta disponible. \n");
        else 
        {
            printf("esta ocupada.   ");
            printf("Cliente - Nombre: %s %s Edad: %d DNI: %d Dias: %d Email: %s\n",
                    room.client.name,room.client.lastname,
                    room.client.age, room.client.dni,
                    room.client.days,room.client.email);
        }
        i++;
    }
    fseek(rooms, 0,SEEK_SET);
}

