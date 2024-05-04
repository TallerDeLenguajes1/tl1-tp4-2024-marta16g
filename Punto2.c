#include <stdio.h>
#include <stdlib.h>


struct{
    int TareaID;
    char *Descripcion;
    int Duracion;
} typedef Tarea;

struct{
    Tarea T;
    Nodo *Siguiente;
}typedef Nodo;

Nodo* crearNodo(Nodo *cabeza);

int main()
{
    Nodo *cabeza;
    cabeza = NULL;
    return 0;
}

Nodo* crearNodo(Nodo *cabeza)
{
    int cantDesc;
    int cantDur;
    Nodo* PNodo = (Nodo*)malloc(sizeof(Nodo));

    puts("Ingrese cantidad aproximada de caracteres de la descripción");
    scanf("%d", &cantDesc);

    puts("Ingrese duracion de la tarea");
    scanf("%d", &cantDur);

    PNodo->T.Descripcion =  (char*)malloc(sizeof(char)*cantDesc);
    PNodo->T.Duracion = cantDur;

    puts("Ingrese descripcion");
    gets(PNodo->T.Descripcion);

    

}