#include<dos.h>
#include "funcs.h"

// Como predeterminado colocamos el gri claro
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
  // Colocamos la subrutina 0x03, que corresponde con la funcion 3 con la que obtenemos el tamaño y posicion del cursor
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
  // Colocamos la subrutina 0x03, que corresponde con la funcion 3 con la que obtenemos el tamaño y posicion del cursor
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

  //int pos_x = get_x();    // Obtenemos la posición actual de x
  //int pos_y = get_y();    // Obtenemos la posición actual de y
  // Se establece la posición del cursor (fila y columna) sumando x e y
  inregs.h.dh=x;    // DH --> número de columna
  inregs.h.dl=y;    // DL --> número de fila
  
  inregs.h.ah=0x02;   // Función 2 que se corresponde con colocar el cursor en una posición determinada
  inregs.h.bh=0x00;   // Debe ser 0

  // Función no estándar definida en dos.h
  // La interrución 0x10 se asocia con la tarjeta de video
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
  // La rutina 0x01 se corresponde con la funcion de obtener tamaño y posicion del cursor
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
// EJERCICIO 3. Fija el modo de video deseado
void setvideomode(BYTE modo){
  union REGS inregs, outregs;
  inregs.h.ah = 0x00;   // Se corresponde con la función 0, que es seleccionar modo de video
  inregs.h.al = modo;

  int86(0x10,&inregs,&outregs);

}


/*
    Función:    Obtiene el modo de video actual
*/
// EJERCICIO 4. Obtiene el modo de video actual
int getvideomode(void){
  union REGS inregs, outregs;
  int modo;   //Modo de video actual
  // Averiguar el modo de vídeo actual
  inregs.h.ah = 0x0F;   // Se corresponde con la funcion Fh que corresponde con averiguar el modo de video actual
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
void clrscr_pr1(void){
  union REGS inregs, outregs;
  inregs.h.ah = 0x06;   // Se corresponde con la funcion desplazar zona de pantalla hacia arriba
  inregs.h.bh = 15;    // Color para los espacios en blanco. Lo colocamos en blanco
  // Línea de la esquina superior izquierda
  inregs.h.ch = 0x00;
  // Columna de la esquna superior izquierda
  inregs.h.cl = 0x00;
  inregs.h.al = 0x00;
  // Numero de fila
  inregs.h.dh = get_x()-1;
  // Numero de columna
  inregs.h.dl = get_y()-1;

  int86(0x10,&inregs,&outregs);

  gotoxy(0x00,0x00);

}

/*
    Función:    Escribe un carácter en pantalla con el color indicado actualmente
    Parámetros: caracter --> caracter que vamos a pintar
               
*/

void cputchar(char caracter){
  union REGS inregs, outregs;
  // Para poder cambiar el color de la fuente y el fondo debemos "combinar" ambos para conseguir el código concreto con los operadores
  // << 4 y | 
  BYTE resultado = (COLOR_FONDO << 4) | COLOR_FUENTE;

  // La rutina 0x09 se corresponde con la funcion de escribir un caracter en pantalla
  inregs.h.ah = 0x09;
  
  //parametros
  inregs.h.al = caracter;   // codigo ascii del caracter
  inregs.h.bl = resultado;  //color 
  inregs.h.bh = 0x00;       //0
  inregs.x.cx = 1;          // Número de repeticiones
  
  int86(0x10, &inregs, &outregs);
  
}

void getche(void){
  union REGS inregs, outregs;
  int caracter;
  // Subfunción que permite leer un caracter desde el teclado
  inregs.h.ah = 0x00;   //0
  // Gestión del teclado
  int86(0x16, &inregs, &outregs);
  caracter = outregs.h.al;    //Salida de la tecla pulsada
    
  cputchar(caracter);

}

