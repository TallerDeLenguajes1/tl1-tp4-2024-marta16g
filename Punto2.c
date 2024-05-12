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

int main()
{
    Nodo *TareasPendientes = listaVacia();
    Nodo *TareasRealizadas = listaVacia();

    int ID = 1000;
    int eleccion = 1;
    int seguir;

    do
    {
        puts("---BIENVENIDO---");
        puts("1) Agregar tarea pendiente");
        puts("2) Listar tareas pendientes");
        puts("3) Marcar tarea pendiente como realizada");
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
            // char titulo[] = "TAREAS PENDIENTES";
            mostrarLista(&TareasPendientes, "TAREAS PENDIENTES");
            break;
        default : break;
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
    Nodo **aux = cabeza;
    if (aux != NULL)
    {
        puts(titulo);
        while ((*aux))
        {
            fflush(stdin);
            printf("ID--> %d\n", (*aux)->T.TareaID);
            printf("DESCRIPCION--> %s",(*aux)->T.Descripcion);
            printf("DURACION--> %d\n", (*aux)->T.Duracion);
            printf("\n");
            (*aux) = (*aux)->Siguiente;
        }
    }else{
        puts("La lista está vacía");
    }
}