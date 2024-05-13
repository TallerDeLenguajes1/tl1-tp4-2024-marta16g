#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LONG 100

struct
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} typedef Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

Nodo *listaVacia();
Nodo *crearNodo(int *ID);
void agregarNodo(Nodo *nuevoNodo, Nodo **cabeza);
void mostrarLista(Nodo **cabeza, char *titulo);
void pasajeListas(Nodo **cabeza, Nodo **nuevaCabeza, int idTarea);
void buscarPorID(Nodo **cabeza1, Nodo **cabeza2, int idTarea);

int main()
{
    Nodo *TareasPendientes = listaVacia();
    Nodo *TareasRealizadas = listaVacia();

    int ID = 1000;
    int eleccion = 1;
    int seguir, idTarea;

    do
    {
        puts("---BIENVENIDO---");
        puts("1) Agregar tarea pendiente");
        puts("2) Listar tareas pendientes");
        puts("3) Marcar tarea pendiente como realizada");
        puts("4) Listar tareas realizadas");
        puts("5) Buscar tarea por ID");
        puts("0 para salir del programa");

        scanf("%d", &eleccion);

        switch (eleccion)
        {
        case 1:
            do
            {
                agregarNodo(crearNodo(&ID), &TareasPendientes);
                puts("¿Desea agregar otra tarea?");
                puts("Escriba 1 para seguir y 0 para salir");
                scanf("%d", &seguir);
            } while (seguir == 1);
            break;
        case 2:
            mostrarLista(&TareasPendientes, "TAREAS PENDIENTES");
            break;
        case 3:
            puts("Ingrese ID de la tarea para transferirla a lista realizada");
            scanf("%d", &idTarea);
            pasajeListas(&TareasPendientes, &TareasRealizadas, idTarea);
            break;
        case 4:
            mostrarLista(&TareasRealizadas, "TAREAS REALIZADAS");
            break;
        case 5:
            puts("Ingrese ID de la tarea a buscar");
            scanf("%d", &idTarea);
            buscarPorID(&TareasPendientes, &TareasRealizadas, idTarea);
            break;
        default: puts("Numero ingresado incorrecto");
            break;
        }

    } while (eleccion != 0);

    puts("¡Nos vemos!");

    return 0;
}

Nodo *listaVacia()
{
    return NULL;
}

Nodo *crearNodo(int *ID)
{
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));

    int duracion;

    nuevo->T.TareaID = (*ID);
    (*ID)++;

    nuevo->T.Descripcion = (char *)malloc(MAX_LONG * sizeof(char));
    puts("Ingrese la descripción de la tarea");
    fflush(stdin);
    fgets(nuevo->T.Descripcion, MAX_LONG, stdin);

    puts("Ingrese la duracion la tarea (10 a 100 minutos)");
    scanf("%d", &duracion);
    while (duracion < 10 || duracion > 100)
    {
        puts("Por favor ingrese un numero valido entre 10 y 100");
        scanf("%d", &duracion);
    }

    nuevo->T.Duracion = duracion;

    nuevo->Siguiente = NULL;

    return nuevo;
}

void agregarNodo(Nodo *nuevoNodo, Nodo **cabeza)
{
    nuevoNodo->Siguiente = *cabeza;
    *cabeza = nuevoNodo;
}

void mostrarLista(Nodo **cabeza, char *titulo)
{
    Nodo *aux = *cabeza;
    if (aux != NULL)
    {
        puts(titulo);
        while (aux)
        {
            fflush(stdin);
            printf("ID--> %d\n", aux->T.TareaID);
            printf("DESCRIPCION--> %s", aux->T.Descripcion);
            printf("DURACION--> %d\n", aux->T.Duracion);
            printf("\n");
            aux = aux->Siguiente;
        }
    }
    else
    {
        puts("\n");
        puts("La lista está vacía");
        puts("\n");
    }
}

void pasajeListas(Nodo **cabeza, Nodo **nuevaCabeza, int idTarea)
{
    Nodo *aux = *cabeza;
    Nodo *anterior = NULL;

    if (aux != NULL)
    {
        while (aux != NULL && aux->T.TareaID != idTarea)
        {
            anterior = aux;
            aux = aux->Siguiente;
        }

        if (aux)
        {
            if (anterior == NULL)
            {
                *cabeza = aux->Siguiente;
            }
            else
            {
                anterior->Siguiente = aux->Siguiente;
            }

            aux->Siguiente = NULL;
            agregarNodo(aux, nuevaCabeza);
            printf("Tarea de id %d marcada como realizada \n", idTarea);
        }
        else
        {
            puts("No se encontro la tarea con el id solicitado");
        }
    }
    else
    {
        puts("La lista de tareas pendientes esta vacia, no hay nada que mover");
    }
}

void buscarPorID(Nodo **cabeza1, Nodo **cabeza2, int idTarea)
{
    Nodo *aux1 = *cabeza1;
    Nodo *aux2 = *cabeza2;

    if (aux1 != NULL)
    {
        while (aux1 != NULL && aux1->T.TareaID != idTarea)
        {
            aux1 = aux1->Siguiente;
        }

        if (aux1)
        {
            printf("Se encontró la tarea de id %d en la lista de PENDIENTES \n", idTarea);
            puts("--Mostrando tarea--");
            printf("ID: %d \n", aux1->T.TareaID);
            printf("DESCRIPCION: %s", aux1->T.Descripcion);
            printf("DURACION %d \n", aux1->T.Duracion);
        }
        else
        {
            while (aux2 != NULL && aux2->T.TareaID != idTarea)
            {
                aux2 = aux2->Siguiente;
            }

            if (aux2)
            {
                printf("Se encontró la tarea de id %d en la lista de REALIZADOS \n", idTarea);
                puts("--Mostrando tarea--");
                printf("ID: %d \n", aux2->T.TareaID);
                printf("DESCRIPCION: %s", aux2->T.Descripcion);
                printf("DURACION %d \n", aux2->T.Duracion);
            }
            else
            {
                puts("No se encontro tarea alguna con el id proporcionado");
            }
        }
    }
    else
    {
        puts("La lista de tareas pendientes esta vacia, no hay nada que mover");
    }
}