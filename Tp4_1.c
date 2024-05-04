#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define NUM 100
#define MAX 30

typedef struct Tarea Tarea;
typedef struct Nodo Nodo;


 struct Tarea {
    int tareaId; //empieza en 1000
    char *descripcion;
    int duracion; //entre 10 - 100
} ;

 struct Nodo {
    Tarea tarea; //dato
    Nodo *sig; //puntero al siguiente
};

Nodo *crearNodo(int *ID, char *descripcion, int duracion);
Nodo *crearListaVacia();
void insertarNodo(Nodo **start, Nodo *NNodo);
Nodo buscarNodo(Nodo **start, int buscarID);
void mostarTareas(Nodo **start);
void eliminarNodo(Nodo **start, int id);
void buscarTareaPorId(Nodo **list1, Nodo **list2, int id);
void buscarTareaPorPalabra(Nodo **list1, Nodo **list2, char * palabra);


int main(){
    int ID = 1000, solicitud = 0, duracion = 1, caso = 0, cambiar = 0;
    char descripcion[NUM];
    Nodo *startPendiente = crearListaVacia();
    Nodo *startRealizado = crearListaVacia();


    do
    {   
        puts("------------------------------------");
        puts("1 para agregar tarea");
        puts("------------------------------------");
        puts("2 para poner una tarea pentiente en realizada");
        puts("------------------------------------");
        puts("3 para mostrar tareas pendientes");
        puts("------------------------------------");
        puts("4 para mostrar tareas realizadas");
        puts("------------------------------------");
        puts("5 para buscar tarea por id");
        puts("------------------------------------");
        puts("6 para buscar tarea por palabra clave");
        puts("------------------------------------");
        puts("7 para salir");
        puts("------------------------------------");
        scanf("%d", &caso);
        switch (caso)
        {
        case 1:
            do
            {
                printf("-----------CARGAR TAREA-----------\n");
                printf("Duracion de la tarea: \n");
                scanf("%d", &duracion);
                fflush(stdin);
                printf("Descripcion de la tarea\n");
                gets(descripcion);
                fflush(stdin);
                insertarNodo(&startPendiente, crearNodo(&ID, descripcion, duracion));
                puts("Si cargara mas datos preionar 1, en lo contrario presionar 0");
                fflush(stdin);
                scanf("%d", &solicitud);
            } while (solicitud != 0);
            break;
        case 2:
            puts("Ingresar el ID de la tarea que cambiara");
            scanf("%d", &cambiar);
            fflush(stdin);
            Nodo tareaCambiar = buscarNodo(&startPendiente, cambiar);
            insertarNodo(&startRealizado, &tareaCambiar);
            eliminarNodo(&startPendiente, cambiar);
            puts("Tarea intercambiada con exito");

            break;
        case 3:
            if (startPendiente == NULL)
            {
                puts("La lista esta vacia");
            }else{
                mostarTareas(&startPendiente);
            }
            break;
        case 4:
            if (startRealizado == NULL)
            {
                puts("La lista esta vacia");
            }else{
                mostarTareas(&startRealizado);
            }
            break;
        case 5:
            puts("Ingresar el ID de la tarea que cambiara");
            fflush(stdin);
            scanf("%d", &cambiar);
            fflush(stdin);
            buscarTareaPorId(&startPendiente, &startRealizado, cambiar);
            break;
        case 6:
            puts("Ingresar la palabra clave a buscar");
            char *buscar = (char*)malloc(sizeof(char)*MAX);
            fflush(stdin);
            gets(buscar);
            buscarTareaPorPalabra(&startPendiente, &startRealizado, buscar);
            free(buscar);
            break;
        }
    } while (caso != 7);
    
    // Paso la direccion de memotia de id (&id)

    return 0;
}

Nodo *crearNodo(int * ID, char *descripcion, int duracion){
    Nodo * NNodo = (Nodo *) malloc(sizeof(Nodo));
    NNodo->tarea.tareaId = *ID;
    (*ID)++;
    NNodo->tarea.descripcion = (char*) malloc(sizeof(char)*NUM);
    strcpy(NNodo->tarea.descripcion, descripcion);
    NNodo->tarea.duracion = duracion;
    NNodo->sig = NULL;
    return NNodo; 
}

Nodo *crearListaVacia(){
    return NULL;
}


void insertarNodo(Nodo **start, Nodo *NNodo){
    NNodo->sig = *start;
    *start = NNodo;
}
Nodo buscarNodo(Nodo **start, int buscarID){
    Nodo *Aux = *start;
    while (Aux && Aux->tarea.tareaId != buscarID)
    {
        Aux = Aux->sig;
    }
    return *Aux;
}


void mostarTareas(Nodo **start){
    Nodo * aux = *start; 
    while (aux != NULL)
    {   
        puts("-------------------TAREAS-------------------");
        printf("Id de la tarea: %d \n", aux->tarea.tareaId);
        puts("Descripcion de la tarea:");
        puts(aux->tarea.descripcion);
        printf("Duracion de la tarea: %d\n", aux->tarea.duracion);

        aux = aux->sig;
    }
}



void eliminarNodo(Nodo **start, int id){
    Nodo **aux = start;

    while (*aux != NULL && (*aux)->tarea.tareaId != id)
    {
        aux = &(*aux)->sig;
    }
    
    if (*aux)
    {
        Nodo *temp = *aux;
        *aux = (*aux)->sig;

        free(temp);
    }
    
}

void buscarTareaPorId(Nodo **list1, Nodo **list2, int id){
    int bandera = 0;
    Nodo **aux1 = list1;
    Nodo **aux2 = list2;

    if (*aux1 == NULL && *aux2 == NULL)
    {
        puts("Las listas estan vacias");
    }else{
        while (*aux1 != NULL && bandera == 0)
        {
            if ((*aux1)->tarea.tareaId == id)
            {
                puts("-------------------TAREA ENCONTRADA-------------------");
                printf("Id de la tarea: %d \n", (*aux1)->tarea.tareaId);
                puts("Descripcion de la tarea:");
                puts((*aux1)->tarea.descripcion);
                printf("Duracion de la tarea: %d\n", (*aux1)->tarea.duracion);
                puts("Tarea encontrada en pendientes");
                bandera = 1;
            }
            *aux1 = (*aux1)->sig;
        }
        
    }

    if (bandera == 0)
    {
        while (*aux2 != NULL && bandera == 0)
        {
            if ((*aux2)->tarea.tareaId == id)
            {
                puts("-------------------TAREA ENCONTRADA-------------------");
            printf("Id de la tarea: %d \n", (*aux2)->tarea.tareaId);
            puts("Descripcion de la tarea:");
            puts((*aux2)->tarea.descripcion);
            printf("Duracion de la tarea: %d\n", (*aux2)->tarea.duracion);
            puts("Tarea encontrada en realizadas");
            }
            *aux2 = (*aux2)->sig;
        }
    } else{
        puts("No hay tareas con ese id");
    }
    

}

void buscarTareaPorPalabra(Nodo **list1, Nodo **list2, char * palabra){
    int bandera = 0;
    Nodo **aux1 = list1;
    Nodo **aux2 = list2;

    if (*aux1 == NULL && *aux2 == NULL)
    {
        puts("Las listas estan vacias");
    }else{
        while (*aux1 != NULL && bandera == 0)
        {
            if (strstr((*aux1)->tarea.descripcion, palabra))
            {
                puts("-------------------TAREA ENCONTRADA-------------------");
                printf("Id de la tarea: %d \n", (*aux1)->tarea.tareaId);
                puts("Descripcion de la tarea:");
                puts((*aux1)->tarea.descripcion);
                printf("Duracion de la tarea: %d\n", (*aux1)->tarea.duracion);
                puts("Tarea encontrada en pendientes");
                bandera = 1;
            }
            *aux1 = (*aux1)->sig;
        }
        
    }

    if (bandera == 0)
    {
        while (*aux2 != NULL && bandera == 0)
        {
            if (strstr((*aux2)->tarea.descripcion, palabra))
            {
                puts("-------------------TAREA ENCONTRADA-------------------");
            printf("Id de la tarea: %d \n", (*aux2)->tarea.tareaId);
            puts("Descripcion de la tarea:");
            puts((*aux2)->tarea.descripcion);
            printf("Duracion de la tarea: %d\n", (*aux2)->tarea.duracion);
            puts("Tarea encontrada en realizadas");
            }
            *aux2 = (*aux2)->sig;
        }
    } 
    
    if(bandera == 0){
        puts("No hay tareas con esa palabra");
    }
    

}