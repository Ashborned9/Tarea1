# Tarea1

En este programa realizado en C , tiene la función de gestionar tickets de soporte, en el cual permite registrar nuevos tickets , asignar y modificar sus prioridades, además de mostrar una lista de tickets pendientes los cuales se ordendan por prioridades y tiempo de llegada.

Adicionalmente permite procesar el ticket, eliminarlo de los datos y pasar al siguiente ticket en cola, tambien se puede buscar la informacion de un ticket especifico por su ID.

Este programa utiliza una estructura de datos dinamica (array) para manejar las listas de tickets segun su prioridad (Alta, Media, Baja), cabe destacar que la implementacion de arraylist se realiza mediante el TDA "List" , mejorando la modularidad del código. EL funcionamiento de proceso de datos se maneja con el orden FIFO(First In First Out).

Para acceder a este Programa se debe ingresar al Repositorio de GitHUB.



El codigo tiene las siguientes Funcionalidades:

Ejemplo de uso:

1.- Registar Nuevos Tickes:
* El usuario ingresa el ID
* El usuario ingresa su Nombre.
* El usuario ingresa una Desacripcion del Problema
* Se asigna automaticamente en priodad baja.

2.-Asignar Prioridad:
* Se ingresa el ID del ticket
* Se selecciona una Prioridad (1 = Alta, 2 = Media, 3 = Baja)
* Si existe se actualiza, si no mostrará un mensaje de error.

3.- Mostrar Lista de Tickets:
* Se muestran los tickets ordenados por prioridad (se muestra explicitamente)
* Se muestran ordenados dentro de la prioridad por orden de Llegada (FIFO).

4.- Procesar Siguiente Ticket:
* Al seleccionarse , el ticket con más prioridad y con más antiguedad es procesado.
* Se eliminan los datos del ticket procesado y se muestran sus datos.
* En caso de que no queden Tickest se notifica.

5.- Buscar Ticket por ID :
* Accede a la información del ticket mediante su ID.
* Muestra la infomación
* Si no existe, mostrará un mensaje.

Complejidades o Malfuncionamiento de Funciones:

Registro ID: Idealmente no se debe escribir un mismo ID 2 veces, para comprobrar si exite revisar la lista de Tickets, en caso de repetir el ID existiran 2 tickets con el mismo ID. Pero no presenta un problema a la hora de programar porque presenta el Ordenamiento FIFO. Sin embargo solo muestra el primer ID ingresado en la función de Buscar Ticket por ID.

Además el Registro permite escribir con numeros en nombre y descripción, que podría llegar a ser confuso.

Mostrar Tickets: Si está vacia, mostrara las listas vacías, no presenta un problema pero si de estética.

