#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
    int TareaId;       //
    char *Descripcion; //
    int Duracion;      // Entre 10 - 100
} Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *siguiente;
} Nodo;
