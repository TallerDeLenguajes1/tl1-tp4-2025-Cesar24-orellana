#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
int validarTiempo();
void InsertarNodo(Nodo **star, Nodo *nodo);
Nodo *BuscarTarea(Nodo **star, int idBusacar);
Nodo *QuitarNodo(Nodo **star, int dato);
void consultarTarea(Nodo *pendiente, Nodo *Realizada);
void MostrarDatos(Nodo *nodo);
Nodo *BuscarTareaDescripcion(Nodo **star, char description[]);
Nodo *BuscarTareaId(Nodo **star, int id);
void EliminarNodo(Nodo *Eliminar);

int main()
{
    char descripcion[30];
    int time, id = 1000;
    int continuar = 1;
    Nodo *tareasRealizadas, *tareasPendientes, *star;
    tareasRealizadas = CrearListaVacia();
    tareasPendientes = CrearListaVacia();
    star = CrearListaVacia(); // Creo un nodo vasio
    do                        // Pedir datos e iterar hasta que ya no sea necesario
    {
        printf("Ingrese Los siguientes Datos:\n"); // Pido datos de entrada
        fflush(stdin);
        printf("Descripcion de la tarea: ");
        gets(descripcion);
        time = validarTiempo();                 // Validar tiempo entre 10 a 100
        
        star = CargarTarea(descripcion, time, id); // Cargo los datos a un nodo vasio
        InsertarNodo(&tareasPendientes, star);     // Inserto la nueva tarea a la lista

        printf("Desea ingresar una nueva tarea?\n 1. Si  0. No \n");
        scanf("%d", &continuar);
        id++;
    } while (continuar != 0);

    MostrarDatos(tareasPendientes); // Mostrar la lista de tareasPendientes
    Nodo *aux = CrearListaVacia();
    continuar = 1;
    do
    {

        int realizada;
        printf("Ingrese el ID de la tarea realizada: ");
        scanf("%d", &realizada);
        aux = BuscarTarea(tareasPendientes, realizada);       // Buscar la tarea ya realizada
        InsertarNodo(&tareasRealizadas, aux);                       // Agregar la tarea realizada a la lista tareaRealizadas
        Nodo *NodoQuitar = QuitarNodo(&tareasPendientes, realizada); // Quitar la tarea realizada de la lista tareasPendientes
        EliminarNodo(NodoQuitar);

        printf("\nDesea elegir otra tarea como concluida?\n 1. Si  0. No \n");
        scanf("%d", &continuar);
    } while (continuar != 0);

    MostrarDatos(tareasRealizadas); // Mostrar la lista de tareasRealizas

    consultarTarea(tareasPendientes, tareasRealizadas);
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

int validarTiempo(){
    int tiempo;
    do
    {
        printf("Duracion de la tarea, entre 10 a 100: ");
        scanf("%d", &tiempo);
        printf("\n");
    } while (tiempo<0 || tiempo>100);   //Verifica que el tiempo sea entre 10 a 100
    return tiempo;
}

void InsertarNodo(Nodo **star, Nodo *nodo) // Insertar nodos a la lista
{
    nodo->siguiente = *star;
    *star = nodo;
}

Nodo *BuscarTarea(Nodo **star, int idBusacar)
{
    Nodo *Aux = star;
    while (Aux && Aux->T.TareaId != idBusacar)
    {
        Aux = Aux->siguiente;
    }
    return Aux;
}

Nodo *QuitarNodo(Nodo **star, int dato)
{
    Nodo **anterior = star;
    while (*anterior != NULL && (*anterior)->T.TareaId != dato)
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

void MostrarDatos(Nodo *nodo)
{
    Nodo *data = nodo;
    while (data != NULL)
    {
        printf("Sus datos son\n");
        printf("Id de tarea: %d\n", data->T.TareaId);
        printf("Tarea: %s\n", data->T.Descripcion);
        printf("Duracion: %d\n", data->T.Duracion);
        data = data->siguiente;
    }
}

void consultarTarea(Nodo *pendiente, Nodo *Realizada){
    int consulta, id;
    char description[20];
    Nodo *tarea;
    printf("\nDesea buscar la tarea por su Id o por su Descripcion?\n");
    printf("0_ ID \n1_ Descripcion\n");
    scanf("%d", &consulta);
    if (consulta == 0)
    {
        tarea = BuscarTareaId(pendiente, id);
        if (tarea == NULL)
        {
            tarea = BuscarTareaId(Realizada, id);
            printf("Su tarea ya fue realizada\n");
        } else
        {
            printf("Su tarea sigue pendiente\n");
        }
        
    } else
    {
        tarea = BuscarTareaDescripcion(&pendiente, description);
        if (tarea == NULL)
        {
            tarea = BuscarTareaDescripcion(Realizada, description);
            printf("Su tarea ya fue realizada\n");
        } else
        {
            printf("Su tarea sigue pendiente\n");
        }
        
    }
    MostrarDatos(tarea);
    
}

Nodo *BuscarTareaDescripcion(Nodo **star, char description[]){
    Nodo *Aux = *star;
    while (Aux && Aux->T.Descripcion != description)
    {
        Aux = Aux->siguiente;
    }
    if (Aux)
    {
        return Aux;
    }
    else
    {
        return NULL;
        
    }
    
}

Nodo *BuscarTareaId(Nodo **star, int id){
    Nodo *Aux = star;
    while (Aux && Aux->T.TareaId != id)
    {
        Aux = Aux->siguiente;
    }
    if (Aux)
    {
        return Aux;
    }
    else
    {
        return NULL;
        
    }
}

void EliminarNodo(Nodo *Eliminar){
    free(Eliminar->T.Descripcion);
    free(Eliminar);
}