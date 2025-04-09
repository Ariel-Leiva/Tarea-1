#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
  char id[10]; 
  char descripcion[101];
  char prioridad[6];
  int hora;
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
void registrar_tickets(List *tickets) {
  registro* usuario = (registro *) malloc(sizeof(registro));

  printf("Registrar nuevo Ticket\n");

  printf("Ingrese ID del usuario:\n");
  scanf(" %9[^\n]", &usuario->id);
  printf("Ingrese descripcion del problema:\n");
  scanf(" %100[^\n]", &usuario->descripcion);
  
  strcpy(usuario->prioridad,"Bajo"); //prioridad baja
  usuario->hora = 0;
  list_pushBack(tickets, usuario);
}

//OPCION 2
void modificar_prioridad(List *tickets){
  char identificador[10];
  char nuevaPrioridad[6];
  printf("Ingrese ID del Usuario:\n");
  scanf(" %9[^\n]", identificador);
  printf("Ingrese la prioridad Alta, Media o Baja:\n");
  scanf(" %5[^\n]", nuevaPrioridad);

  registro *actual = list_first(tickets);
  while(actual != NULL){
    if(strcmp(actual->id, identificador) == 0) break;
    actual = list_next(tickets);
  }

  if(actual != NULL){
    strcpy(actual->prioridad,nuevaPrioridad);
    printf("La prioridad del Usuario se ha actualizado correctamente\n");
  }
  else printf("El ID del Usuario no se ha encontrado\n");  
}

//OPCION 3
void mostrar_lista_tickets(List *tickets) {
  
  printf("tickets en espera: \n");
  registro *actual = list_first(tickets);
  while(actual != NULL){
    printf("ID: %s\n", actual->id);
    printf("descripción: %s\n", actual->descripcion);
    printf("Prioridad: %s\n", actual->prioridad);
    printf("Hora de Registro: %d\n\n", actual->hora);
    actual = list_next(tickets);
  }
}

//OPCION 4
void procesar_sig_ticket(List *tickets){ //ID, descripción, prioridad y hora de registro
  registro *actual = list_first(tickets);
  if(actual == NULL) {
    printf("No hay tickets pendientes\n\n");
    return;
  }

  list_popFront(tickets);
  printf("ID: %s\n", actual->id);
  printf("Descripción: %s\n", actual->descripcion);
  printf("Prioridad: %s\n", actual->prioridad);
  printf("Hora de Registro: %d\n\n", actual->hora);
}

//OPCION 5
void mostrar_ticket_id(List *tickets){
  char identificador[10];
  printf("Ingrese ID del Usuario:\n");
  scanf(" %9[^\n]", identificador);

  registro *actual = list_first(tickets);
  while(actual != NULL){
    if(strcmp(actual->id, identificador) == 0) break;
    actual = list_next(tickets);
  }

  if(actual != NULL){
    printf("Descripción: %s\n",actual->descripcion);
    printf("Prioridad: %s\n",actual->prioridad);
    printf("Hora De Registro: %d\n\n",actual->hora);
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
      mostrar_lista_tickets(tickets); //FALTA MOSTRARLOS POR PRIORIDAD !
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
