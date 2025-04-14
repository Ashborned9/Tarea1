#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include "arraylist.h"

typedef struct {
    int id;
    char nombre[50];
    char descripcion[200];
    char fecha[20];
    int prioridad; // 1: Alta, 2: Media, 3: Baja
} stTicket;

// Limpia la Pantalla, para Windows y Linux
void limpiarPantalla()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}
//Transforma el string a un numero, si no es un numero devuelve false
// Si es un numero devuelve true
bool isNum(const char *str) {
    if (str == NULL || *str == '\0')
        return false;
    
    bool tieneAlgoDistintoDeCero = false;
    for (const char *p = str; *p; p++) {
        if (!isdigit((unsigned char)*p))
            return false;
        if (*p != '0')
            tieneAlgoDistintoDeCero = true;
    }
    return tieneAlgoDistintoDeCero;
}
void mostrarMenuPrincipal()
{
  puts("========================================");
  puts("     Sistema de Gestion ticket");
  puts("========================================");

  puts("1) Registrar ticket");
  puts("2) Asignar prioridad a un ticket");
  puts("3) Mostrar lista de ticket pendientes");
  puts("4) Procesar y pasar al siguiente ticket");
  puts("5) Buscar ticket por ID ");
  puts("6) Salir");
}

// Asigna la fecha y hora actual al ticket
// Se implementa usando la libreria time.h
void FechaAsignada(stTicket *ticket)
{
  time_t t;
  time(&t);
  strftime(ticket->fecha, sizeof(ticket->fecha), "%d/%m/%Y %H:%M:%S", localtime(&t));
}
/// Busca un ticket por ID y lo elimina de la lista
/// Devuelve el ticket eliminado o NULL si no se encuentra
stTicket* Buscar_Remover(List *lista, int id){
    stTicket *ticket = (stTicket *)first(lista);
    while (ticket != NULL)
    {
        if (ticket->id == id)
        {
        popCurrent(lista);
        return ticket;
        }
        ticket = next(lista);
    }
    return NULL;
}
// Registra un nuevo ticket en la lista de tickets de baja prioridad
// Se asigna la fecha y hora actual al ticket
void registrar_ticket(List *ticket_Baja)
{
    stTicket *nuevoTicket = (stTicket *)malloc(sizeof(stTicket));
    if (nuevoTicket == NULL)
    {
        printf("Error al asignar memoria para el nuevo ticket.\n");
        return;
    }

    char idInput[20];
    int valid = 0;
    do {
        printf("Ingrese el ID del ticket: ");
        scanf("%s", idInput);  

        if (isNum(idInput))
        {
            nuevoTicket->id = atoi(idInput);  
            valid = 1;
        }
        else
        {
            printf("El valor ingresado no es un numero valido. Intente nuevamente.\n");
        }
    } while(!valid);

    
    printf("Ingrese el nombre del cliente: ");
    scanf(" %[^\n]", nuevoTicket->nombre);
    printf("Ingrese la descripcion del ticket: ");
    scanf(" %[^\n]", nuevoTicket->descripcion);
  
    FechaAsignada(nuevoTicket);
    nuevoTicket->prioridad = 3; 
    pushBack(ticket_Baja, nuevoTicket);
}
// Definir la prioridad de un ticket existente
// Busca el ticket por ID en las listas de alta, media y baja prioridad
// Si lo encuentra, lo elimina de la lista actual y inserta a la nueva asignada.
void definir_prio(List *ticket_Alta, List *ticket_Media, List *ticket_Baja)
{
  int id;
  printf("Ingrese el ID del ticket a modificar: ");
  scanf("%d", &id);

  stTicket *ticket = NULL;
  // Buscamos y eliminamos el ticket en cada lista
  ticket = Buscar_Remover(ticket_Alta, id);
  if (!ticket) {
      ticket = Buscar_Remover(ticket_Media, id);
  }
  if (!ticket) {
      ticket = Buscar_Remover(ticket_Baja, id);
  }
  
  if (!ticket)
  {
    printf("No se encontro ticket con ID %d.\n", id);
    return;
  }
  
  int nuevaPrioridad;
  printf("Seleccione la nueva prioridad (1: Alta, 2: Media, 3: Baja): ");
  scanf("%d", &nuevaPrioridad);
  ticket->prioridad = nuevaPrioridad;
  
  // Reinserción usando pushBack para preservar el orden FIFO.
  switch(nuevaPrioridad)
  {
    case 1:
      pushBack(ticket_Alta, ticket);
      break;
    case 2:
      pushBack(ticket_Media, ticket);
      break;
    case 3:
      pushBack(ticket_Baja, ticket);
      break;
    default:
      printf("Prioridad no valida. Se asignará la prioridad baja por defecto.\n");
      ticket->prioridad = 3;
      pushBack(ticket_Baja, ticket);
      break;
  }
}
// Muestra los tickets pendientes en cada lista
// Ademas de la fecha y hora de creacion, de acuerdo a la prioridad
void TicketsPendientes(List *ticket_Alta, List *ticket_Media, List *ticket_Baja)
{
  printf("Tickets pendientes:\n");
  printf("Prioridad Alta:\n");
  stTicket *ticket = (stTicket *)first(ticket_Alta);
  while (ticket != NULL)
  {
    printf("ID: %d, Nombre: %s, Descripcion: %s, Fecha: %s\n", ticket->id, ticket->nombre, ticket->descripcion, ticket->fecha);
    ticket = next(ticket_Alta);
  }
  printf("Prioridad Media:\n");
  ticket = (stTicket *)first(ticket_Media);
  while (ticket != NULL)
  {
    printf("ID: %d, Nombre: %s, Descripcion: %s, Fecha: %s\n", ticket->id, ticket->nombre, ticket->descripcion, ticket->fecha);
    ticket = next(ticket_Media);
  }
  printf("Prioridad Baja:\n");
  ticket = (stTicket *)first(ticket_Baja);
  while (ticket != NULL)
  {
    printf("ID: %d, Nombre: %s, Descripcion: %s, Fecha: %s\n", ticket->id, ticket->nombre, ticket->descripcion, ticket->fecha);
    ticket = next(ticket_Baja);
  }
}
// Procesa el siguiente ticket de acuerdo a la prioridad
// Se recorre la lista de alta, media y baja prioridad
// Si se encuentra un ticket, se muestra y se elimina de la lista
void Siguiente_Ticket(List *ticket_Alta, List *ticket_Media, List *ticket_Baja)
{
  stTicket *ticket = (stTicket *)first(ticket_Alta);
  if (ticket != NULL)
  {
    printf("Procesando ticket de alta prioridad:\n");
    printf("ID: %d, Nombre: %s, Descripcion: %s, Fecha: %s\n", ticket->id, ticket->nombre, ticket->descripcion, ticket->fecha);
    popFront(ticket_Alta);
    free(ticket);
  }
  else
  {
    ticket = (stTicket *)first(ticket_Media);
    if (ticket != NULL)
    {
      printf("Procesando ticket de media prioridad:\n");
      printf("ID: %d, Nombre: %s, Descripcion: %s, Fecha: %s\n", ticket->id, ticket->nombre, ticket->descripcion, ticket->fecha);
      popFront(ticket_Media);
      free(ticket);
    }
    else
    {
      ticket = (stTicket *)first(ticket_Baja);
      if (ticket != NULL)
      {
        printf("Procesando ticket de baja prioridad:\n");
        printf("ID: %d, Nombre: %s, Descripcion: %s, Fecha: %s\n", ticket->id, ticket->nombre, ticket->descripcion, ticket->fecha);
        popFront(ticket_Baja);
        free(ticket);
      }
      else
      {
        printf("No hay tickets pendientes.\n");
      }
    }
  }
}
// Busca un ticket por ID en las listas de alta, media y baja prioridad
// Si lo encuentra, muestra los detalles del ticket
void Buscar_Ticket(List *ticket_Alta, List *ticket_Media, List *ticket_Baja)
{
  int id;
  printf("Ingrese el ID del ticket a buscar: ");
  scanf("%d", &id);
  stTicket *ticket = (stTicket *)first(ticket_Alta);
  while (ticket != NULL)
  {
    if (ticket->id == id)
    {
      printf("Ticket encontrado en alta prioridad:\n");
      printf("ID: %d, Nombre: %s, Descripcion: %s, Fecha: %s\n", ticket->id, ticket->nombre, ticket->descripcion, ticket->fecha);
      return;
    }
    ticket = next(ticket_Alta);
  }
  ticket = (stTicket *)first(ticket_Media);
  while (ticket != NULL)
  {
    if (ticket->id == id)
    {
      printf("Ticket encontrado en media prioridad:\n");
      printf("ID: %d, Nombre: %s, Descripcion: %s, Fecha: %s\n", ticket->id, ticket->nombre, ticket->descripcion, ticket->fecha);
      return;
    }
    ticket = next(ticket_Media);
  }
  ticket = (stTicket *)first(ticket_Baja);
  while (ticket != NULL)
  {
    if (ticket->id == id)
    {
      printf("Ticket encontrado en baja prioridad:\n");
      printf("ID: %d, Nombre: %s, Descripcion: %s, Fecha: %s\n", ticket->id, ticket->nombre, ticket->descripcion, ticket->fecha);
      return;
    }
    ticket = next(ticket_Baja);
  }
  printf("Ticket no encontrado.\n");
}
//Funcion auxiliar para que el usuario tenga tiempo de ver los resultados en pantalla.
void Pausa()
{
  printf("Presione Enter para continuar...\n");
  while (getchar() != '\n');
    getchar(); 
}
int main()
{
  List *ticket_Alta = create_list();
  List *ticket_Media = create_list();
  List *ticket_Baja = create_list();
  printf("============================================\n");
  printf("Bienvenido al sistema de gestion de tickets.\n");
  printf("============================================\n\n");
  int opcion;
  do
  {
    Pausa();
    limpiarPantalla();

    mostrarMenuPrincipal();
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:
      limpiarPantalla();
      registrar_ticket(ticket_Baja);
      break;
    case 2:
      limpiarPantalla();
      definir_prio(ticket_Alta, ticket_Media, ticket_Baja);
      break;
    case 3:
      limpiarPantalla();
      TicketsPendientes(ticket_Alta, ticket_Media, ticket_Baja);
      break;

    case 4:
      limpiarPantalla();
      Siguiente_Ticket(ticket_Alta, ticket_Media, ticket_Baja);
      break;
    case 5:
      limpiarPantalla();
      Buscar_Ticket(ticket_Alta, ticket_Media, ticket_Baja);
      break;
    case 6:
      printf("Saliendo del programa...\n");
      break;

    default:
      printf("Opcion no valida. Intente nuevamente.\n");
      break;
    }
  } while (opcion != 6);
  return 0;
}

