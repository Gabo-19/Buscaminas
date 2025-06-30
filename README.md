Proyecto

Buscaminas

-Gabriel Villalobos Araya C4K961
-Juan Pablo Martinez Rua  C4G932

_Descripcion del proyecto:_

Este proyecto es una implementacion del clasico juego Buscaminas en lenguaje C, utilizando la biblioteca gráfica Raylib para su interfaz visual

El juego contiene:

-Iniciar partidas nuevas desde un menu principal.

-Interactuar con un tablero  de tamano 12x12 casillas.

-Marcar banderas, revelar casillas, y perder o ganar según se revelen las casillas.

-Activar/desactivar música y efectos de sonido desde un menú de opciones.


_Dependencias e Instalacion:_

-Si no tiene Ubuntu instalado, puede hacerlo por medio de este tutorial haciendo click en este link: https://www.youtube.com/watch?v=qH9JuCjCKow&ab_channel=RedesPlus

-Una vez que se instale Ubuntu, abrir la terminal con las teclas "Ctrl" + "Alt" + "T" a la vez.

-Ahora escribir estos comandos uno por uno en la terminal y presionar enter cuando este list@:

sudo apt update (Presionar Enter)
[Esto actualiza la lista de programas disponibles.]

sudo apt install build-essential (Presionar Enter)
[Esto instala GCC (el traductor del código) y Make (el automatizador).]

sudo apt install libraylib-dev (Presionar Enter)
[Esto instala la biblioteca Raylib, que permite mostrar gráficos y sonidos.]

sudo apt install libasound2-dev libopenal-dev (Presionar Enter)
[Esto instala las bibliotecas de sonido necesarias.]

**Nota: Cuando le pida su contraseña, escribala y presione Enter aunque no vea nada.**

_Clonar el repositorio del proyecto desde  GitHub:_

git clone https://github.com/Gabo-19/Buscaminas.git
[Esto va a crear una carpeta llamada Buscaminas.]

cd Buscaminas
[Entra en la carpeta Buscaminas del repositorio]

make
[Compila el juego]

./buscaminas
[Inicia el juego]

**Listo, que disfrute!**

 
