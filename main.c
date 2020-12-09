#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"
#include <string.h>
#include "list.h"

typedef struct App{
    int count;
    HashMap * tareas;
    HashMap * realizadas;
} App;
typedef struct Tarea{
  char nombre[50];
  char complejidad[10];
  int dia;
  int mes;
  int anio;
  char hora[50];
  char descripcion[201];
  char clasificacion[100];
  char ID[5];
} Tarea;

const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}


void agregarTarea(App * general);
void buscarNombre(App * general);
void buscarCat(App * general);
void buscarCom(App * general);
void mostrarTodo(App * general);
void editarTarea(App * general);
void eliminarTarea(App * general);
void marcarTarea(App * general);
void cargarCSV(App * general);

Tarea * editordeTarea(Tarea * mod);

int main(void) {
  App * general = (App *)malloc(sizeof(App));
  general->count = 0;
  general->tareas = createMap(100); //key -> id - funciona como archivador de las tareas sin realizar
  general->realizadas = createMap(100);//key -> id - funciona como archivador de tareas realizadas

  int op = 0; //menú principal del programa
        while(op != 10)
        {
        printf("1.- Insertar tarea nueva\n");
        printf("2.- Buscar por nombre\n");
        printf("3.- Buscar por categoria\n");
        printf("4.- Buscar por complejidad\n");
        printf("5.- Mostrar todas las tareas\n");
        printf("6.- Editar tarea\n");
        printf("7.- Eliminar tarea\n");
        printf("8.- Marcar tarea como realizada\n");
        printf("9.- Mostrar Demo\n");
        printf("10.- Cerrar la aplicacion\n\n"); //cualquier número de 10 en adelante sirve para cerrar el programa
        printf("Indica la opcion: ");
        scanf("%d", &op);
        printf("\n");
        fflush(stdin);

        switch(op)
        {
            case 1:
                agregarTarea(general);
                break;

            case 2:
                buscarNombre(general);
                break;

            case 3:
                buscarCat(general);
                break;

            case 4:
                buscarCom(general);
                break;

            case 5:
                mostrarTodo(general);
                break;

            case 6:
                editarTarea(general);
                break;

            case 7:
                eliminarTarea(general);
                break;

            case 8:
                marcarTarea(general);
                break;

            case 9:
                cargarCSV(general);
                break;

            case 10: //cualquier número de 10 en adelante sirve para cerrar el programa
                break;
        }
    }
    return 0;
}

void agregarTarea(App * general) {
    char titulo[50]; //variables usadas para que el usuario ingrese los datos de las tareas
    char descripcion[201];
    char complejidad[10];
    int dia;
    int mes;
    int anio;
    char hora[50];
    char categoria[50];
    long id;
    char auxid[10];
    Tarea * nueva = (Tarea *)malloc(sizeof(Tarea)); //arreglo dinámico usado para crear una tarea nueva

    printf("Ingresa el titulo(1 palabra):\n"); //se ingresan los datos de las tareas
    gets(titulo);
    printf("Ingresa la descripcion(200 caracteres maximo):\n");
    gets(descripcion);
    printf("Ingresa la fecha:\nDia(1-31):\n");
    scanf("%d",&dia);
    printf("Ingresa el mes(1-12):\n");
    scanf("%d",&mes);
    printf("Ingresa el anio: \n");
    scanf("%d",&anio);
    printf("Ingresa la hora(formato 24:00 hrs):\n");
    fflush(stdin);
    gets(hora);
    printf("Ingresa la categoria:\n");
    fflush(stdin);
    gets(categoria);
    printf("Ingresa la dificultad de la tarea(1-10 | mayor numero indica mayor dificultad): \n");
    gets(complejidad);
    fflush(stdin);


    nueva->anio = anio; //se introducen los datos ingresados en el arreglo dinámico
    strcpy(nueva->complejidad, complejidad);
    nueva->dia = dia;
    nueva->mes = mes;
    nueva->anio = anio;
    strcpy(nueva->nombre, titulo);
    strcpy(nueva->descripcion, descripcion);
    strcpy(nueva->clasificacion, categoria);
    id = general->count + 1; //se crea la ID de la tarea nueva
    general->count += 1;
    strcpy(nueva->hora, hora);
    itoa(id, auxid,10);
    strcpy(nueva->ID, auxid);

    insertMap(general->tareas, nueva->ID, nueva); //se inserta la tarea nueva con su ID en el mapa de tareas

    return;


}

void buscarNombre(App * general) {
    char name[50]; //variable usada para ingresar el nombre de la tarea

    printf("Ingresa el nombre de la tarea: \n");
    //
    gets(name); //se introduce el nombre de la tarea
    Tarea * recorrido = firstMap(general->tareas); //variable de recorrido para iterar las tareas y mostrar sus datos
    if(recorrido == NULL)return; //se devuelve al menú principal cuando se termina de iterar o se ingresa un nombre que no existe en el mapa
        while(recorrido != NULL){ //mientras el recorrido sea distinto de NULL, se iteran las tareas y se muestran sus datos
            if(strcmp(recorrido->nombre,name)==0){ //se compara el nombre de las tareas con el nombre ingresado
                printf("\n---------------------------\n");//barra espaciadora, se comienza a mostrar los datos de las tareas
                printf("Nombre: %s\n",recorrido->nombre);
                printf("Descripcion: %s\n", recorrido->descripcion);
                printf("Fecha y hora: %d - %d - %d | %s\n",recorrido->dia,recorrido->mes,recorrido->anio,recorrido->hora);
                printf("Clasificacion: %s\n",recorrido->clasificacion);
                printf("Dificultad: %s\n",recorrido->complejidad);
                printf("|ID: %s|",recorrido->ID);
                printf("\n---------------------------\n"); //barra espaciadora
            }
            recorrido = nextMap(general->tareas); //se continua con la tarea siguiente si el recorrido es distinto de NULL
        }


}

void buscarCat(App * general) {
    char categoria[50]; //variable usada para ingresar la categoría buscada

    printf("Ingresa la categoria: \n");
    gets(categoria); //se ingresa la categoría

    Tarea * recorrido = firstMap(general->tareas); //variable de recorrido para iterar las tareas y mostrar sus datos
    if(recorrido == NULL) return; //se devuelve al menú principal cuando se termina de iterar o se ingresa una categoría que no existe en el mapa
        while(recorrido != NULL){ //mientras el recorrido sea distinto de NULL, se iteran las tareas y se muestran sus datos
                if(strcmp(recorrido->clasificacion, categoria) == 0){ //se compara la categoría de las tareas con la categoría ingresada
                    printf("\n---------------------------\n");//barra espaciadora, se comienza a mostrar los datos de las tareas
                    printf("Nombre: %s\n",recorrido->nombre);
                    printf("Descripcion: %s\n", recorrido->descripcion);
                    printf("Fecha y hora: %d - %d - %d | %s\n",recorrido->dia,recorrido->mes,recorrido->anio,recorrido->hora);
                    printf("Clasificacion: %s\n",recorrido->clasificacion);
                    printf("Dificultad: %s\n",recorrido->complejidad);
                    printf("|ID: %s|\n",recorrido->ID);
                    printf("\n---------------------------\n"); //barra espaciadora
                }
                recorrido = nextMap(general->tareas); //se continua con la tarea siguiente si el recorrido es distinto de NULL
        }
}

void buscarCom(App * general) {
    char complejidad[10]; //variable usada para ingresar la complejidad deseada

    printf("Ingresa la dificultad(1-10): \n");

    gets(complejidad); //se ingresa la complejidad
    Tarea * recorrido = firstMap(general->tareas); //variable de recorrido para iterar las tareas y mostrar sus datos
    if(recorrido == NULL) return; //se devuelve al menú principal cuando se termina de iterar o se ingresa un nombre que no existe en el mapa
    while(recorrido != NULL){ //mientras el recorrido sea distinto de NULL, se iteran las tareas y se muestran sus datos
            if(strcmp(recorrido->complejidad, complejidad) == 0){ //se compara la complejidad de las tareas con la complejidad ingresada
                printf("\n---------------------------\n");//barra espaciadora, se comienza a mostrar los datos de las tareas
                printf("Nombre: %s\n",recorrido->nombre);
                printf("Descripcion: %s\n", recorrido->descripcion);
                printf("Fecha y hora: %d - %d - %d | %s\n",recorrido->dia,recorrido->mes,recorrido->anio,recorrido->hora);
                printf("Clasificacion: %s\n",recorrido->clasificacion);
                printf("Dificultad: %s\n",recorrido->complejidad);
                printf("|ID: %s|\n",recorrido->ID);
                printf("\n---------------------------\n"); //barra espaciadora
            }
            recorrido = nextMap(general->tareas); //se continua con la tarea siguiente si el recorrido es distinto de NULL
    }

}

void mostrarTodo(App * general) {

    int opcion; //variable usada para que el usuario indique la opción que desea seleccionar
    Tarea * recorrido = firstMap(general->tareas); //arreglo dinámico usado para las tareas sin realizar
    Tarea * listas = firstMap(general->realizadas); //usado para las tareas ya realizadas

    printf("Elige una opcion: \n 1,- Mostrar tareas\n 2.- Mostrar tareas realizadas\n 3.- Mostrar todas\n 4.- Volver al menu\n");
    scanf("%d",&opcion); //se le pregunta al usuario la opción que desea elegir

    switch(opcion){
        case 1:
            while(recorrido != NULL){ //se muestran todas las tareas sin realizar
                printf("\n---------------------------\n");//barra espaciadora, se comienza a mostrar los datos de las tareas
                printf("Nombre: %s\n",recorrido->nombre);
                printf("Descripcion: %s\n", recorrido->descripcion);
                printf("Fecha y hora: %d/%d/%d |%s|\n",recorrido->dia,recorrido->mes,recorrido->anio,recorrido->hora);
                printf("Clasificacion: %s\n",recorrido->clasificacion);
                printf("Dificultad: %s\n",recorrido->complejidad);
                printf("|ID: %s|\n",recorrido->ID);
                printf("\n---------------------------\n"); //barra espaciadora
                recorrido = nextMap(general->tareas); //se continua con la siguiente tarea
            }
            break;
        case 2:
            while(listas != NULL){ //se muestran las tareas ya realizadas
                printf("\n---------------------------\n");//barra espaciadora, se comienza a mostrar los datos de las tareas
                printf("Nombre: %s\n", listas->nombre);
                printf("Descripcion: %s\n", listas->descripcion);
                printf("Fecha y hora: %d/%d/%d |%s|\n",listas->dia,listas->mes,listas->anio, listas->hora);
                printf("Clasificacion: %s\n",listas->clasificacion);
                printf("Dificultad: %s\n",listas->complejidad);
                printf("|ID: %s|\n",listas->ID);
                printf("\n---------------------------\n"); //barra espaciadora
                listas = nextMap(general->realizadas); //se continua con la siguiente tarea
            }
            break;
        case 3:
             while(recorrido != NULL){ //primero se muestran las tareas sin realizar
                printf("\n---------------------------\n");//barra espaciadora, se comienza a mostrar los datos de las tareas
                printf("Nombre: %s\n",recorrido->nombre);
                printf("Descripcion: %s\n", recorrido->descripcion);
                printf("Fecha y hora: %d/%d/%d |%s|\n",recorrido->dia,recorrido->mes,recorrido->anio,recorrido->hora);
                printf("Clasificacion: %s\n",recorrido->clasificacion);
                printf("Dificultad: %s\n",recorrido->complejidad);
                printf("|ID: %s|\n",recorrido->ID);
                printf("\n---------------------------\n"); //barra espaciadora
                recorrido = nextMap(general->tareas); //se continua con la siguiente tarea
            }
            while(listas != NULL){ //después se muestran las tareas ya hechas
                printf("\n---------------------------\n");//barra espaciadora, se comienza a mostrar los datos de las tareas
                printf("Nombre: %s\n", listas->nombre);
                printf("Descripcion: %s\n", listas->descripcion);
                printf("Fecha y hora: %d/%d/%d |%s|\n",listas->dia,listas->mes,listas->anio, listas->hora);
                printf("Clasificacion: %s\n",listas->clasificacion);
                printf("Dificultad: %s\n",listas->complejidad);
                printf("|ID: %s|\n",listas->ID);
                printf("\n---------------------------\n"); //barra espaciadora
                listas = nextMap(general->realizadas);//se continua con la siguiente tarea
            }
            break;
        case 4:
            break; //se cierra el submenú y se devuelve al menú principal, se puede elegir cualquier número desde 4 hacia arriba para que funcione
    }

}



void editarTarea(App * general) {
    Tarea * recorrido = firstMap(general->tareas); //variable usada para iterar las tareas
    char id[50]; //variable usada para que el usuario indique la ID de la tarea que desea editar
    while(recorrido != NULL){ //se muestran todas las tareas sin realizar hasta que el recorrido llegue a NULL
            printf("\n---------------------------\n");//barra espaciadora
            printf("Nombre: %s\n",recorrido->nombre);
            printf("Descripcion: %s\n", recorrido->descripcion);
            printf("Fecha y hora: %d/%d/%d |%s|\n",recorrido->dia,recorrido->mes,recorrido->anio,recorrido->hora);
            printf("Clasificacion: %s\n",recorrido->clasificacion);
            printf("Dificultad: %s\n",recorrido->complejidad);
            printf("|ID: %s|\n",recorrido->ID);
            printf("\n---------------------------\n");
            recorrido = nextMap(general->tareas);
    }
    printf("Ingresa la ID de la tarea que quieres editar:\n");
    gets(id); //se le pregunta al usuario la ID de la tarea que desea editar
    Tarea * mod = searchMap(general->tareas, id); //se busca la tarea en el mapa con una variable auxiliar
    if(mod == NULL){ //si no se encuentra, se imprime el siguiete mensaje
      printf("No se encuentra la ID de la tarea ingresada\n");
      return;
    }
    editordeTarea(mod); //si se encuentra, la tarea se lleva a la función editordeTarea

}

void eliminarTarea(App * general){
    char id[10];//variable usada para que el usuario indique la tarea que desea eliminar
    Tarea * recorrido = firstMap(general->tareas); //variable usada para iterar las tareas
    while(recorrido!=NULL) { //se muestran todas las tareas sin realizar hasta que el recorrido llegue a NULL
        printf("\n---------------------------\n");//barra espaciadora
        printf("Nombre: %s\n",recorrido->nombre);
        printf("Descripcion: %s\n", recorrido->descripcion);
        printf("Fecha y hora: %d/%d/%d |%s|\n",recorrido->dia,recorrido->mes,recorrido->anio,recorrido->hora);
        printf("Clasificacion: %s\n",recorrido->clasificacion);
        printf("Dificultad: %s\n",recorrido->complejidad);
        printf("|ID: %s|\n",recorrido->ID);
        printf("\n---------------------------\n");
        recorrido = nextMap(general->tareas);
    }
    printf("Ingresa la id de la tarea que quieres eliminar: \n");
    gets(id); //se le pregunta al usuario la ID de la tarea que desea editar
    Tarea * mod = searchMap(general->tareas, id); //se busca la tarea en el mapa con una variable auxiliar
    if(mod == NULL){ //si no se encuentra, se imprime el siguiete mensaje
      printf("No se encuentra la ID de la tarea ingresada\n");
      return;
    }
    eraseMap(general->tareas, id); //si se encuentra, se elimina la tarea con la función eraseMap
    return;
}

void marcarTarea (App * general){
    Tarea * recorrido = firstMap(general->tareas); //variable usada para iterar las tareas
    char id[10]; //variable usada para que el usuario indique la tarea que desea eliminar

    while(recorrido != NULL){ //se muestran todas las tareas sin realizar hasta que el recorrido llegue a NULL
            printf("\n---------------------------\n");//barra espaciadora
            printf("Nombre: %s\n",recorrido->nombre);
            printf("Descripcion: %s\n", recorrido->descripcion);
            printf("Fecha y hora: %d/%d/%d |%s|\n",recorrido->dia,recorrido->mes,recorrido->anio,recorrido->hora);
            printf("Clasificacion: %s\n",recorrido->clasificacion);
            printf("Dificultad: %s\n",recorrido->complejidad);
            printf("|ID: %s|\n",recorrido->ID);
            printf("\n---------------------------\n");
            recorrido = nextMap(general->tareas);
    }

    printf("Ingresa la id de la tarea que quieres marcar como realizada:\n");
    gets(id); //se le pregunta al usuario la ID de la tarea que desea editar
    Tarea * auxtarea = searchMap(general->tareas, id); //se busca la tarea en el mapa con una variable auxiliar
    if(auxtarea == NULL){ //si no se encuentra, se imprime el siguiete mensaje
      printf("No se encuentra la ID de la tarea ingresada\n");
      return;
    }
    insertMap(general->realizadas, id, auxtarea); //si se encuentra, se inserta la tarea en el mapa de tareas realizadas
    eraseMap(general->tareas, id); //se elimina la tarea del mapa de tareas sin realizar
    return;

}

Tarea * editordeTarea(Tarea * mod){

     int op = 10; //variable usada para que el usuario indique su opción

     //menu

     while(op!=0){
          //mostrar en pantalla que quiere modificar
     printf("Escoge una opcion: \n");
     printf("1.- Modificar titulo\n2.- Modificar descripcion\n3.- Modificar fecha\n4.- Modificar categoria\n5.- Modificar prioridad\n6.- Salir\n");
     scanf("%d",&op); //se le pregunta al usuario que desea elegir y el usuario indica su elección
          //0=salir
          switch(op){
              case 1: //modificar titulo
                  memset(mod->nombre, 0, 50);
                  printf("Ingresa el nuevo nombre de la tarea:\n");
                  fflush(stdin);
                  gets(mod->nombre); //se modifica el nombre de la tarea
                  break;
              case 2: //modificar descripcion
                  memset(mod->descripcion, 0, 200);
                  printf("Ingresa la nueva descripcion:\n");
                  fflush(stdin);
                  gets(mod->descripcion); //se modifica la descripción de la tarea
                  break;
              case 3: //modificar fecha
                  mod->dia = NULL; //se incializa la fecha de la tarea en NULL
                  mod->mes = NULL;
                  mod->anio = NULL;
                  printf("Ingresa la nueva fecha\n");
                  printf("Dia:\n");
                  scanf("%d",&mod->dia); //se le indica la nueva fecha a la tarea
                  printf("Mes:\n");
                  scanf("%d",&mod->mes);
                  printf("Anio:\n");
                  scanf("%d",&mod->anio);
                  break;
              case 4: //mod categoria
                  memset(mod->clasificacion, 0, 100);
                  printf("Ingresa la nueva clasificacion:\n");
                  fflush(stdin);
                  gets(mod->clasificacion); //se modifica la categoría de la tarea
                  break;
              case 5: //mod complejidad
                  memset(mod->complejidad, 0, 10);
                  printf("Ingresa la nueva complejidad:\n");
                  fflush(stdin);
                  gets(mod->complejidad); //se modifica la complejidad de la tarea

                  break;
              case 6: //se debe elegir el número 6 para que funcione correctamente, de lo contrario volverá a este submenú
                  printf("\n"); //salto de linea por motivos estéticos
                  return mod; //se retorna la tarea ya modificada, y se devuelve al menú
          }
      }
      return mod;
}

void cargarCSV(App * general){

    FILE * fp = fopen("demo.csv", "r"); //función usada para la carga del archivo de prueba
    char * linea  = (char*)malloc(1024*sizeof(char));
    int id;
    char auxid[10];


     while (fgets (linea, 1023, fp) != NULL) { //se consiguen los datos de las tareas del archivo de prueba
        Tarea * nuevo = (Tarea *)malloc(sizeof(Tarea));
        strcpy(nuevo->nombre, get_csv_field(linea, 0));
        strcpy(nuevo->complejidad, get_csv_field(linea, 1));
        nuevo->dia = atoi(get_csv_field(linea, 2));
        nuevo->mes = atoi(get_csv_field(linea, 3));
        nuevo->anio = atoi(get_csv_field(linea, 4));
        strcpy(nuevo->hora, get_csv_field(linea, 5));
        strcpy(nuevo->descripcion, get_csv_field(linea, 6));
        strcpy(nuevo->clasificacion, get_csv_field(linea, 7));
        int aux = strlen(nuevo->clasificacion);
        printf("largo cadena %d",aux);
        id = general->count + 1;
        itoa(id, auxid, 10);
        strcpy(nuevo->ID, auxid);
        general->count += 1;
        insertMap(general->tareas, nuevo->ID, nuevo); //se insertan en el mapa de tareas sin realizar
        printf("Tarea almacenada...\n\n");
        linea  = (char*)malloc(1024*sizeof(char));
     }
     mostrarTodo(general); //se incializa la opción 5 del menú para mostrar las tareas
}
