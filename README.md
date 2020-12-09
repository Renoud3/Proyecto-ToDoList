# Proyecto-ToDoList
---------- Readme del proyecto ----------

Integrantes del equipo:

Pablo Julio
Fernando Melillan
Sebastian Yañez

-----------------------------------------

Opciones que funcionan correctamente:

1.- Insertar tarea nueva
2.- Buscar por nombre
3.- Buscar por categoría
4.- Buscar por complejidad
5.- Mostrar todas las tareas
6.- Editar tareas
8.- Marcar como realizada
9.- Mostrar Demo
10.- Cerrar aplicación

Opciones que funcionan no correctamente:

7.- Eliminar tarea


Modo de uso:

Es necesario seleccionar la opción 9 antes de comenzar a probar, puesto que esta opción carga el archivo de prueba.
Al seleccionar esta opción, lo llevará al submenú de la opción 5, y deberá seleccionar la primera opción.
Una vez hecho esto, puede comenzar su uso.


Datos adicionales:

No logramos hacer que se guarden los cambios hechos a la lista cuando se cierra la aplicación.

Al seleccionar la opción 4, no se imprimen todas las tareas con la categoría "universidad", pero la opción si funciona correctamente con todas las demás categorías. Sospechamos que simplemente es un error de nuestra parte al confeccionar el archivo de demostración.


Problemas de la aplicación:

La función de eliminar tarea no borra correctamente la mayoría de las tareas del archivo. Puede borrar la primera tarea, pero no puede borrar las tareas 10, 11, y las añadidas por el usuario.

Este problema también se extiende a la opción de marcar tareas como realizadas, ya que no se borran las tareas correctamente del mapa de tareas sin hacer, aunque si se añaden bien al mapa de tareas realizadas.


Diferencias con el informe:

Añadimos un nuevo tipo de dato llamado App que indica las tareas sin hacer, las tareas ya realizadas, y un contador de estas.

No pudimos implementar los mapas mapClass, mapName y mapDif, por lo que las funciones que originalmente hacen uso de estos mapas (opciones 3, 2 y 4 respectivamente) funcionan de manera distinta a la indicada en el informe.

El nombre de los mapas tareas y realizadas es diferente.  
