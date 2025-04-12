# Sistema de Soporte Técnico

## 🧾 Descripción

Este sistema permite gestionar solicitudes de soporte técnico a través de **tickets**. 
Los usuarios pueden registrar tickets, asignar prioridades, visualizar la lista de espera ordenada, 
revisar tickets específicos por ID y procesar a los usuarios según el nivel de urgencia.
Está diseñado para optimizar la atención y priorización de problemas técnicos reportados por los usuarios.

---

## ⚙️ Cómo compilar y ejecutar

### Requisitos previos
- [Visual Studio Code](https://code.visualstudio.com/)
- Extensión **C/C++** de Microsoft
- Compilador C como `gcc`  
  - En Windows puedes usar [MinGW](https://www.mingw-w64.org/) o [WSL](https://learn.microsoft.com/en-us/windows/wsl/)

### Pasos para compilar

1. Clonar este repositorio o descarga los archivos.
2. Asegúrate de tener los archivos `tarea1.c` y las dependencias en la carpeta `tdas/`.
3. Abre la carpeta del proyecto en VS Code.
4. Abre una terminal (`Terminal > Nueva terminal`) y compila con:
   
     ```bash
   gcc -o tarea1 tarea1.c tdas/list.c tdas/extra.c

5. Ejecuta el programa con:

      ```bash
   ./tarea1

6. Si quieres que se vean las tildes usa:

     ```bash
   $OutputEncoding = [Console]::OutputEncoding = [Text.UTF8Encoding]::new()

  ## ✅ Funcionalidades:

  +Registrar nuevos tickets con ID, descripción y prioridad por defecto "Bajo".

  +Asignar prioridad ("Alta", "Media", "Baja") a tickets existentes.

  +Mostrar la lista de espera ordenada por prioridad y tiempo de ingreso.

  +Atender al siguiente ticket (el de mayor prioridad y más antiguo).

  +Consultar tickets por ID.


  ## ⚠️ Problemas conocidos:

  -No hay persistencia: los datos se pierden al cerrar el programa.

  -No hay validación para entradas incorrectas (como prioridad inválida).


  ## 🛠️ Mejoras futuras:

  ->Soporte para guardar y cargar tickets desde archivos CSV o binarios.

  ->Validación robusta de entradas.

  ->Interfaz gráfica. 

  ## 🧪 Ejemplo de uso:

  Opción seleccionada: 1) Registrar Ticket
      
    Ingrese ID del usuario: 111111111
    Ingrese descripcion del problema: Mi pc no prende

  El sistema registra el ID '111111111' y su descripción, ademas ingresa con una prioridad inicial "Baja" 
  y guarda la hora actual de registro. La prioridad inicial puede ser ajustada más tarde. 
      
  Opción seleccionada: 2) Asignar prioridad a Ticket

    Ingrese ID del Usuario: 111111111
    Ingrese la prioridad Alta, Media o Baja: Alta
  El sistema actualiza la prioridad de '111111111' a 'Alta', asegurando que será uno de las próximos usuarios en ser atendido.
  
  Opción seleccionada: 3) Mostrar lista de espera tickets

    Tickets en espera:
    ID: 111111111
    descripción: Mi pc no prende
    Prioridad: Media
    Fecha de Registro: Fri Apr 11 23:34:20 2025

    ...
  Se muestra al ID '111111111', en la primera posición, gracias a su prioriad 'Alta'.
  
  Opción seleccionada: 4) Atender al siguiente Usuario

    Siguiente usuario a procesar:
    ID: 111111111
    descripción: Mi pc no prende
    Prioridad: Media
    Fecha de Registro: Fri Apr 11 23:34:20 2025
  Se muestra que el usuario esta siendo atendido y se elimina de la lista.
  
  Opción seleccionada: 5) Mostrar Tickets por ID

    Ingrese ID del Usuario: 111111111
    Descripción: Mi pc no prende
    Prioridad: Media
    Fecha De Registro: Fri Apr 11 23:34:20 2025
  El usuario podra ver su ticket ingresando su ID y el programa le mostrará su descripción, prioridad, Hora de Registro.
