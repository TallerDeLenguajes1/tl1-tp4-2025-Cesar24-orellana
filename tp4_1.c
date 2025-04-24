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

        // Apartir de aqui todo el codigo lo hice en clases, no pude hacer los commit pues
        // Hay problemas de conexion en el lab. fomec 

        Nodo *CrearListaVacia();
        Nodo *CargarTarea(char descripcion[], int time, int id);
        void InsertarNodo(Nodo **star, Nodo *nodo);
        Nodo *BuscarTarea(Nodo *star, int idBusacar);
        Nodo *QuitarNodo(Nodo *star, int dato);
        
        void MostrarDatos(Nodo *nodo);

        int main()
        {
            char descripcion[30];
            int time, id = 1000, i = 0;
            int continuar = 1;
            Nodo *tareasRealizadas, *tareasPendientes, *star;
            tareasRealizadas = CrearListaVacia();
            tareasPendientes = CrearListaVacia();
            star = CrearListaVacia(); // Creo un nodo vasio
            do
            {
                printf("Ingrese Los siguientes Datos:\n"); // Pido datos de entrada
                fflush(stdin);
                printf("Descripcion de la tarea: ");
                gets(descripcion);
                printf("Duracion de la tarea, entre 10 a 100: ");
                scanf("%d", &time);
                printf("\n");
                
                star = CargarTarea(descripcion, time, id); // Cargo los datos a un nodo vasio
                InsertarNodo(&tareasPendientes, star);     // Inserto la nueva tarea a la lista
        
                printf("Desea ingresar una nueva tarea?\n 1. Si  0. No \n");
                scanf("%d", &continuar);
                id++;
            } while (continuar != 0);
        
            MostrarDatos(tareasPendientes);
        
            int realizada;
            printf("Ingrese el ID de la tarea realizada: ");
            scanf("%d", &realizada);
            Nodo *aux = BuscarTarea(tareasPendientes, realizada);
            InsertarNodo(&tareasRealizadas, aux);
            tareasPendientes = QuitarNodo(tareasPendientes, realizada);
        
            MostrarDatos(tareasRealizadas);
            return 0;
        }
        
        Nodo *CrearListaVacia() // Crear Lista vacia
        {
            return NULL;
        }
        
        Nodo *CargarTarea(char descripcion[], int time, int id) // Cargar Tareas
        {
            Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
            nodo->T.Duracion = time;
            nodo->T.Descripcion = (char *)malloc(strlen(descripcion) * sizeof(char) + 1);
            strcpy(nodo->T.Descripcion, descripcion);
            nodo->T.TareaId = id;
            nodo->siguiente = NULL;
            return nodo;
        }
        
        void InsertarNodo(Nodo **star, Nodo *nodo) // Insertar nodos a la lista
        {
            nodo->siguiente = *star;
            *star = nodo;
        }
        
        Nodo *BuscarTarea(Nodo *star, int idBusacar){
            Nodo *Aux = star;
            while (Aux && Aux->T.TareaId != idBusacar)
            {
                Aux = Aux->siguiente;
            }
            return Aux;
        } 
        
        Nodo *QuitarNodo(Nodo *star, int dato){
            Nodo **anterior = star;
            while (anterior != NULL && (*anterior)->T.TareaId != dato)
            {
                anterior = &(*anterior)->siguiente;
            }
            if (*anterior)
            {
                Nodo *temp = *anterior;
                *anterior = (*anterior)->siguiente;
                temp->siguiente = NULL;
                return temp;
            }
            else
            {
                return NULL;
            }
            
            
        }
        
        void MostrarDatos(Nodo *nodo){
            Nodo *data = nodo;
            while (data != NULL)
            {
                printf("Id de tarea: %d\n", data->T.TareaId);
                printf("Tarea: %s\n", data->T.Descripcion);
                printf("Duracion: %d\n", data->T.Duracion);
                data = data->siguiente;
            }
            
        }        