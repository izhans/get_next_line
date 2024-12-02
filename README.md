# get_next_line
Leer una línea de un fd es demasiado aburrido

Resumen: El objetivo de este proyecto es simple: programar una función que devuelva una línea leída de un file descriptor.

## Parte obligatoria
| Nombre de función | get_next_line |
|-|-|
| Prototipo | char *get_next_line(int fd); |
| Archivos a entregar | get_next_line.c, get_next_line_utils.c, get_next_line.h |
| Parámetros | fd: File descriptor del que leer |
| Valor devuelto | Si todo va bien: la línea leída<br>En caso de fallo o si la lectura termina: NULL |
| Funciones autorizadas | read, malloc, free |
| Descripción | Escribe una función que devuelva la línea leída de un file descriptor

Consideraciones generales:
- Llamar a tu función get_next_line de manera repetida (por ejemplo, usando un bucle)
te permitirá leer el contenido del archivo hacia el que apunta el file descriptor,
línea a línea, hasta el final.

- Tu función deberá devolver la línea que se acaba de leer.
Si no hay nada más que leer o si ha ocurrido un error, deberá devolver NULL.

- Asegúrate de que tu función se comporta adecuadamente cuando lea de un archivo
y cuando lea de stdin.

- Ten en cuenta que la línea devuelta debe terminar con el caracter \n, excepto
si se ha llegado al final del archivo y esté no termina con un caracter \n.

- En el header get_next_line.h deberás tener como mínimo el prototipo de la función get_next_line.

- Añade todas las funciones de ayuda que necesites en el archivo get_next_line_utils.c

Consideraciones sobre la compilación:
- Tu programa debe compilar con el flag -D BUFFER_SIZE=xx.
Este flag se utilizará para determinar el tamaño del buffer de las lecturas de tu get_next_line().
Este parámetro será modificado por tus evaluadores y por Moulinette para probar tu programa.

- Debemos ser capaces de compilar este proyecto con y sin el flag -D
BUFFER_SIZE, junto a los flags habituales. Puedes elegir el valor por
defecto que prefieras.

- El programa se compilará de la siguiente forma (se utiliza como ejemplo un tamaño
de buffer de 42): cc -Wall -Werror -Wextra -D BUFFER_SIZE=42 <archivos>.c.

Comportamientos indeterminados:
- Se considera que get_next_line() tiene un comportamiento indeterminado si el
archivo al que apunta el fd ha cambiado desde la última vez que se llamó, siempre
que read() no haya llegado al final del archivo.

- Se considera que get_next_line() tiene un comportamiento indeterminado cuando
lo que se lee es un archivo binario. Sin embargo, puedes implementar alguna manera
lógica de sortear este problema, si quieres