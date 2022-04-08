# Periféricos y dispositivos de interfaz humana (PDIH)
# Práctica 1: Entrada/Salida utilizando interrupciones con lenguaje C
### Pre-Requisitos 📋
- _DosBox_
### Funciones implementadas 🔧
- _gotoxy()_
- _setcursortype()_
- _setvideomode()_
- _getvideomode()_
- _textcolor()_
- _textbackground()_
- _clrscr()_
- _cputchar()_
- _getche()_
## Autores ✒️

* **Álvaro Marín Pérez** 
* **Francisco Lara Marín**



# Fichero main.c
```c
#include<dos.h>
#include<stdio.h>
#include<string.h>
#include "funcs.h"

int main(void){
  int tipo_cursor, color, modo_video;
  
  printf("Ejecutando gotoxy\n");
  gotoxy(0x05,0x05);
  printf("Fin gotoxy. Pulsa una tecla para continuar\n");
  mi_pausa();
  printf("Prueba de setcursortype. Escribe 0 para INVISIBLE, 1 para NORMAL, 2 para GRUESO.");
  scanf("%d", &tipo_cursor);
  setcursortype(tipo_cursor);
  printf("Fin setcursortype. Pulsa una tecla para continuar\n");
  mi_pausa();
  printf("Cambiando color de fuente a azul...\n");
  color = 1;
  textcolor_pr1(color);
  printf("Color cambiado.\n");
  mi_pausa();
  color = 2;
  printf("Cambiando color de fondo a verde...\n");
  textbackground_pr1(color);
  printf("Color cambiado.\n");
  mi_pausa();
  printf("Prueba de los anteriores pintando la letra con fondo y fuente previamente cambiado: \n");
  cputchar('A');
  printf("\nFin de prueba.Pulse tecla para continuar \n");
  mi_pausa();
  printf("Cambiando modo de video...\n");
  mi_pausa();
  setvideomode(1);
  mi_pausa();
  printf("Obteniendo el modo de video...\n");
  modo_video = getvideomode();
  printf("El modo actual es el %d\n", modo_video);
  mi_pausa();
  printf("Pulsa para volver a la normalidad :)\n");
  mi_pausa();
  setvideomode(3);
  printf("Escribriendo para comprobar el funcionamiento de la funcion clrscr-----------------------\n");
  mi_pausa();
  clrscr_pr1();
  printf("Escribe un caracter por teclado:");
	getche();

  
	return 0;
}
```
# Fichero funcs.h (funciones utilizadas en main.c)
```c
#include<dos.h>
#define BYTE unsigned char
// Como predeterminado colocamos el gris claro
BYTE COLOR_FUENTE = 7;
// Como predeterminado colocamos el negro
BYTE COLOR_FONDO = 0;


/*
    Función: Produce una interrupción hasta pulsar una tecla
*/
void mi_pausa(void){
   union REGS inregs, outregs;
	 inregs.h.ah = 8;
	 int86(0x21, &inregs, &outregs);
}

/*
    Función: Devuelve la posición y del cursor (DL)
*/
int get_y(void){
  union REGS inregs,outregs;
  // Colocamos la subrutina 0x03, que corresponde con la función 3 con la que obtenemos el tamaño y posición del cursor
  inregs.h.ah=0x03;
  inregs.h.bh=0x00; //Debe ser 0
  int86(0x10,&inregs,&outregs);
  return outregs.h.dl;    // DH --> número de columna

}

/*
    Función: Devuelve la posición x del cursor (DH)
*/
int get_x(void){
  union REGS inregs,outregs;
  // Colocamos la subrutina 0x03, que corresponde con la función 3 con la que obtenemos el tamaño y posición del cursor
  inregs.h.ah=0x03;
  inregs.h.bh=0x00;
  int86(0x10,&inregs,&outregs);
  return outregs.h.dh;    // DL --> número de fila
}

/*
    Función:    Coloca el cursor en una posición determinada
    Parámetros: 
                x:  DH(Número de fila)
                y:  DL(Número de columna)
*/

// EJERCICIO 1. Coloca el cursor en una posición determinada
void gotoxy(int x, int y){
  // En inregs se almacenan los parámetros de la interrupción y en outregs los datos devueltos de la salida
  union REGS inregs,outregs;
  inregs.h.dh=x;    // DH --> número de columna
  inregs.h.dl=y;    // DL --> número de fila
  
  inregs.h.ah=0x02;   // Función 2 que se corresponde con colocar el cursor en una posición determinada
  inregs.h.bh=0x00;   // Debe ser 0

  // La interrución 0x10 se asocia con la tarjeta de vídeo
  int86(0x10,&inregs,&outregs);
}

/*
    Función:    Fija aspecto del cursor
    Parámetros: 
                tipo_cursor: Puede tomar 3 valores: INVISIBLE, NORMAL y GRUESO
*/
// EJERCICIO 2. Fijar el aspecto del cursor, debe admitir 3 valores: INVISIBLE, NORMAL y GRUESO 
void setcursortype(int tipo_cursor){
  union REGS inregs,outregs;
  // La rutina 0x01 se corresponde con la función de obtener tamaño y posición del cursor
  inregs.h.ah = 0x01;
  switch (tipo_cursor){
      // INVISIBLE
      case 0:
          inregs.h.ch=010;
          inregs.h.cl=000;
          break;
      // NORMAL
      case 1:
          inregs.h.ch=010;
          inregs.h.cl=010;
          break;
      // GRUESO
      case 2:
          inregs.h.ch=000;
          inregs.h.cl=010;
          break;
      // CUALQUIER OTRO
      default:
          printf("Has introducido un valor no valido");
          return;
      }
  int86(0x10, &inregs, &outregs);
}


/*
    Función:    Fija el modo de vídeo deseado
    Parámetros: 
                modo --> se pueden introducir varios modos con diversas resoluciones. Nosotros introduciremos el modo 1
*/
// EJERCICIO 3. Fija el modo de vídeo deseado
void setvideomode(BYTE modo){
  union REGS inregs, outregs;
  inregs.h.ah = 0x00;   // Se corresponde con la función 0, que es seleccionar modo de video
  inregs.h.al = modo;

  int86(0x10,&inregs,&outregs);

}


/*
    Función:    Obtiene el modo de vídeo actual
*/
// EJERCICIO 4. Obtiene el modo de vídeo actual
int getvideomode(void){
  union REGS inregs, outregs;
  int modo;   //Modo de vídeo actual
  // Averiguar el modo de vídeo actual
  inregs.h.ah = 0x0F;   // Se corresponde con la función Fh que corresponde con averiguar el modo de vídeo actual
  int86(0x10,&inregs,&outregs);
  // Salida del modo actual
  modo=outregs.h.al;

  return modo;
}


/*
    Función:    Modifica el color de primer plano con el que se mostrarán los caracteres al llamar a cputchar
    Parámetros: color_texto_pass --> nuevo color
               
*/
// EJERCICIO 5. Modifica el color de primer plano con que se mostrarán los caracteres
void textcolor_pr1(int color_texto_pass){
  COLOR_FUENTE = color_texto_pass;
}


/*
    Función:    Modifica el color de fondo con que se mostrarán los caracteres al llamar a cputchar
    Parámetros: color_findo_pass --> nuevo color
               
*/
// EJERCICIO 6. Modifica el color de fondo con que se mostrarán los caracteres
void textbackground_pr1(int color_fondo_pass){
  COLOR_FONDO = color_fondo_pass;
}


/*
    Función: Borra toda la pantalla
*/
// EJERCICIO 7. Borra toda la pantalla
void clrscr_pr1(void){
  union REGS inregs, outregs;
  inregs.h.ah = 0x06;   // Se corresponde con la función desplazar zona de pantalla hacia arriba
  inregs.h.bh = 15;    // Color para los espacios en blanco. Lo colocamos en blanco
  // Línea de la esquina superior izquierda
  inregs.h.ch = 0x00;
  // Columna de la esquna superior izquierda
  inregs.h.cl = 0x00;
  inregs.h.al = 0x00;
  // Número de fila
  inregs.h.dh = get_x()-1;
  // Número de columna
  inregs.h.dl = get_y()-1;

  int86(0x10,&inregs,&outregs);

  gotoxy(0x00,0x00);

}

/*
    Función:    Escribe un carácter en pantalla con el color indicado actualmente
    Parámetros: carácter --> carácter que vamos a pintar
               
*/
// EJERCICIO 8. Escribe un carácter en pantalla con el color indicado actualmente
void cputchar(char caracter){
  union REGS inregs, outregs;
  // Para poder cambiar el color de la fuente y el fondo debemos "combinar" ambos para conseguir el código concreto con los operadores
  // << 4 y | 
  BYTE resultado = (COLOR_FONDO << 4) | COLOR_FUENTE;

  // La rutina 0x09 se corresponde con la función de escribir un carácter en pantalla
  inregs.h.ah = 0x09;
  
  //parametros
  inregs.h.al = caracter;   // código ascii del carácter
  inregs.h.bl = resultado;  //color 
  inregs.h.bh = 0x00;       //0
  inregs.x.cx = 1;          // Número de repeticiones
  
  int86(0x10, &inregs, &outregs);
  
}

// EJERCICIO 9. Obtiene un carácter de teclado y lo muestra por pantalla
void getche(void){
  union REGS inregs, outregs;
  int caracter;
  // Subfunción que permite leer un carácter desde el teclado
  inregs.h.ah = 0x00;   //0
  // Gestión del teclado
  int86(0x16, &inregs, &outregs);
  caracter = outregs.h.al;    //Salida de la tecla pulsada
    
  cputchar(caracter);

}



```
