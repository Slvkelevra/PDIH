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
