#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct{
  char id[10]; 
  char descripcion[101];
  char prioridad[6];
  time_t fecha;
} registro;

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Soporte Técnico");
  puts("========================================");

  puts("1) Registrar Ticket");
  puts("2) Asignar prioridad a Ticket");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente Usuario");
  puts("5) Mostrar Tickets por ID");
  puts("6) Salir");
}

//OPCION 1
void registrar_tickets(List *tickets) {//El usuario registra el ticket con su respectivo problema
  registro* usuario = (registro *) malloc(sizeof(registro));

  printf("\nRegistrar nuevo Ticket\n");

  printf("Ingrese ID del usuario: ");
  scanf(" %9[^\n]", &usuario->id);
  printf("Ingrese descripción del problema: ");
  scanf(" %100[^\n]", &usuario->descripcion);
  strcpy(usuario->prioridad,"Bajo"); 
  
  time(&usuario->fecha);
  list_pushBack(tickets, usuario);
  printf("Se ha registrado correctamente\n\n");
}

//Funcion ordena por prioridad y fecha (OPCION 2), le da valores a las prioridades y luego las compara
int lower_than_prioridad(void *data1, void *data2) {
  registro *a = (registro *)data1;
  registro *b = (registro *)data2;

  int valor_a = 2, valor_b = 2;

  if (strcmp(a->prioridad, "Alta") == 0) valor_a = 0;
  else if (strcmp(a->prioridad, "Media") == 0) valor_a = 1;

  if (strcmp(b->prioridad, "Alta") == 0) valor_b = 0;
  else if (strcmp(b->prioridad, "Media") == 0) valor_b = 1;

  if (valor_a != valor_b) return valor_a < valor_b;
  return a->fecha < b->fecha;
}

//OPCION 2
void modificar_prioridad(List *tickets){ //El usuario modifica su prioridad del ticket
  char identificador[10];
  char nuevaPrioridad[6];
  printf("\nIngrese ID del Usuario: ");
  scanf(" %9[^\n]", identificador);
  printf("Ingrese la prioridad Alta, Media o Baja: ");
  scanf(" %5[^\n]", nuevaPrioridad);

  registro *actual = list_first(tickets);
  while(actual != NULL){
    if(strcmp(actual->id, identificador) == 0)break;
    actual = list_next(tickets);
  }

  if(actual != NULL){ //Se modifica la prioridad y luego se inserta a la lista en su posicion correspondiente
    registro *temp = actual;
    list_popCurrent(tickets);
    strcpy(temp->prioridad, nuevaPrioridad);
    
    list_sortedInsert(tickets, temp, lower_than_prioridad);
    printf("La prioridad del Usuario se ha actualizado correctamente\n");
  }
  else printf("El ID del Usuario no se ha encontrado\n");  
}

//OPCION 3
void mostrar_lista_tickets(List *tickets) { //Muestra la lista ordenada por Prioridad
  
  printf("\nTickets en espera: \n\n");
  registro *actual = list_first(tickets);
  while(actual != NULL){
    printf("ID: %s\n", actual->id);
    printf("descripción: %s\n", actual->descripcion);
    printf("Prioridad: %s\n", actual->prioridad);
    printf("Fecha de Registro: %s\n\n", ctime(&actual->fecha));
    actual = list_next(tickets);
  }
}

//OPCION 4
void procesar_sig_ticket(List *tickets){ //muestra el siguiente ticket a procesar: ID, descripción, prioridad y Fecha de registro
  registro *actual = list_first(tickets);
  if(actual == NULL) {
    printf("\nNo hay tickets pendientes\n\n");
    return;
  }

  list_popFront(tickets);
  printf("\nSiguiente usuario a procesar: \n");
  printf("ID: %s\n", actual->id);
  printf("Descripción: %s\n", actual->descripcion);
  printf("Prioridad: %s\n", actual->prioridad);
  printf("Fecha de Registro: %s\n\n", ctime(&actual->fecha));
}

//OPCION 5
void mostrar_ticket_id(List *tickets){ //El usuario escribe su ID y puede ver su ticket
  char identificador[10];
  printf("\nIngrese ID del Usuario: ");
  scanf(" %9[^\n]", identificador);

  registro *actual = list_first(tickets);
  while(actual != NULL){
    if(strcmp(actual->id, identificador) == 0) break;
    actual = list_next(tickets);
  }

  if(actual != NULL){
    printf("Descripción: %s\n",actual->descripcion);
    printf("Prioridad: %s\n",actual->prioridad);
    printf("Fecha De Registro: %s\n\n", ctime(&actual->fecha));
  }
  else printf("El ID del Usuario no se ha encontrado\n\n");
}


int main() {

  char opcion;
  List *tickets = list_create();

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_tickets(tickets);
      break;
    case '2':
      modificar_prioridad(tickets);
      break;
    case '3':
      mostrar_lista_tickets(tickets); 
      break;
    case '4':
      procesar_sig_ticket(tickets);
      break;
    case '5':
      mostrar_ticket_id(tickets);
      break;
    case '6':
      puts("Saliendo del sistema del servicio técnico...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  list_clean(tickets);

  return 0;
}
