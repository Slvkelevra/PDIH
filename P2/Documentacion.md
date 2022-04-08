
# Práctica 2: Uso de bibliotecas de programación de interfaces de usuario en modo texto
## Pre-Requisitos 📋
- Linux OS
- Ncurses library (sudo apt-get install libncurses5-dev libncursesw5-dev for Ubuntu)
## Objetivos
- Instalar la librería ncurses en Linux.
- Crear programas sencillos basados en ncurses.
# Instalación
> Resultado tras la instalación:

![enter image description here](https://github.com/Phyrov/PDIH/blob/main/P2/img/Setup-ncurses.png?raw=true)
![enter image description here](https://github.com/Phyrov/PDIH/blob/main/P2/img/Setup-ncurses-finish.png?raw=true)
# Programas de ejemplo
## Mostrar una ventana en el terminal

> Compilar con 
> gcc ventana.c -o ventana -lncurses
```c
#include <stdlib.h>
#include <ncurses.h>
int main(void) {
	int rows, cols;
	
	initscr();
	
	if (has_colors() == FALSE) {
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_GREEN);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(3,COLOR_WHITE,COLOR_BLUE);
	clear();
	
	refresh();
	getmaxyx(stdscr, rows, cols);
	
	WINDOW *window = newwin(rows,cols,0,0);
	wbkgd(window, COLOR_PAIR(3));
	box(window, '|', '-');
	
	mvwprintw(window, 10, 10, "una cadena");
	wrefresh(window);  
	
	getch();
	endwin();
	return  0;
}
```
### Ejemplo de ejecución
>Compilación

![enter image description here](https://github.com/Phyrov/PDIH/blob/main/P2/img/compile-ventana.png?raw=true)
> Ejecución

![enter image description here](https://github.com/Phyrov/PDIH/blob/main/P2/img/execute-ventana.png?raw=true)
## Mover una "pelotita" en pantalla 
```c
#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000

int main(int argc, char *argv[]) {
	int x = 0, y = 0;
	int max_y = 20, max_x = 20;
	int next_x = 0;
	int direction = 1;
	
	initscr();
	noecho();
	curs_set(FALSE);
	
	while(1) {
		clear();
		mvprintw(y, x, "o");
		refresh();
		usleep(DELAY);
		next_x = x + direction;  
		if (next_x >= max_x || next_x < 0) {
			direction*= -1;
		} else {
			x+= direction;
		}
	}
	endwin();
}
```
> Compilación

![enter image description here](https://github.com/Phyrov/PDIH/blob/main/P2/img/compile-pelotita.png?raw=true)
> Ejecución

![enter image description here](https://github.com/Phyrov/PDIH/blob/main/P2/img/execute-pelotita.png?raw=true)

## Juego Ping Pong terminal  🔧

```c
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>



void dibujar_paletas(int fila_jug1,int fila_jug2, int cols){
    // Para el jugador 1. Lo colocamos en la columna 0
	mvprintw(fila_jug1, 0, "|");
	mvprintw(fila_jug1+1, 0, "|");
	mvprintw(fila_jug1+2, 0, "|");
	mvprintw(fila_jug1+3, 0, "|");
    // Para el jugador 2. Lo colocamos a la derecha -1 para no solaparse
	mvprintw(fila_jug2, cols, "|");
	mvprintw(fila_jug2+1, cols, "|");
	mvprintw(fila_jug2+2, cols, "|");
	mvprintw(fila_jug2+3, cols, "|");
}

int mover_pelota(int eje,int direccion_pelota){ return eje+direccion_pelota;}


int main(int argc, char *argv[]){


//===================       Cuadro de presentación de controles     =============================

    int rows, cols;
    int x = 0, y = 0;

    // Inicializamos el entorno. La necesitamos para poder ejecutar ncurses
    
    initscr();
    if (has_colors() == FALSE) {
            endwin();
            printf("Your terminal does not support color\n");
            exit(1);
	}   
    // Quitamos el cursor
    curs_set(FALSE);
    // Inicializamos el soporte de colores
    start_color();
    init_pair(3,COLOR_WHITE,COLOR_BLUE);
    clear();

    // Recargamos lo ejecutado
    refresh();
    // Calculamos el tamaño del terminal (filas y columnas) para saber los maximos donde rebotará 
    getmaxyx(stdscr, rows, cols);

    // Creamos una nueva ventana del tamaño anterior obtenido
    WINDOW *window = newwin(rows, cols, 0, 0);
    wbkgd(window, COLOR_PAIR(3));
    // Dibujamos los marcos de la ventana
    box(window, '|', '-');
    // Mostramos la bienvenida
    mvwprintw(window, 5,28, "Bienvenido al juego");  
    mvwprintw(window, 10, 28, "Para jugador 1:");
    mvwprintw(window, 12, 28, "q -> Arriba,  a - Abajo");
    mvwprintw(window, 14, 28, "Para jugador 2:");
    mvwprintw(window, 16, 28, "p -> Arriba  l - Abajo");
    mvwprintw(window, 20, 28, "Pulsa una tecla para iniciar");
    wrefresh(window);

    // Obtiene una entrada por teclado
    getch();
    // COn esto limpiamos el terminal para poder inicial el juego
    endwin();
//=============================================================================================



//============================       ELECCIÓN DE NIVEL     ====================================
    initscr();
    
    clear();
    refresh();
    int nivel;
    mvwprintw(window, 5,26, "¿Qué nivel de dificultad quieres?");
    mvwprintw(window, 6,cols/2-11, "1 -> nivel PRINCIPIANTE");
    mvwprintw(window, 7,cols/2-11, "2 -> nivel MEDIO");
    mvwprintw(window, 8,cols/2-11, "3 -> nivel DIOS");
    mvwprintw(window, 9,cols/2-11, "4 -> nivel NO ERES CAPAZ");
    wrefresh(window);
    scanf("%d", &nivel);
    while(nivel != 1 && nivel != 2 && nivel != 3 && nivel != 4){
        clear();
        refresh();
        mvwprintw(window, 6,cols/2-11, "Introduce un nivel valido");
        wrefresh(window);
        scanf("%d", &nivel);
    }

//=============================================================================================


//==============================       COMENZANDO...     ======================================

    clear();
    refresh();
    
    mvwprintw(window, rows/2,cols/2-6, "Empenzando en");
    wrefresh(window);
    usleep(1000000); 
    clear();
    refresh();
    mvwprintw(window, rows/2,cols/2, "3");
    wrefresh(window);
    usleep(1000000); 

    mvwprintw(window, rows/2,cols/2, "2");
    wrefresh(window);
    usleep(1000000); 

    mvwprintw(window, rows/2,cols/2, "1");
    wrefresh(window);
    usleep(1000000); 

    endwin();


//=============================================================================================

//==================================      INICIAMOS EL JUEGO ==================================

    // Declaramos el tope en la derecha,izquierda,arriba y abajo
    int max_y = rows;
    int max_x = cols;

    // Colocamos la posicion de la pelota (en el centro)
    int next_x = max_x/2, next_y = max_y/2;
    // Damos los mismos valores a X e Y respectivamente
    x = max_x/2;
    y = max_y/2;


    //posicion del jugador 1
    int pos_jug1_x = 0, pos_jug1_y = 0;
    //posicion del jugador 2
    int pos_jug2_x = max_x - 1, pos_jug2_y = 0 ;
    //direccion de la pelota hacia la derecha inicialmente
    int direccion_pelota_x = 1, direccion_pelota_y = 1;

    // Para saber quien ha ganado
    int quien_gana;
    // Para controlar si queremos parar el juego o seguir tras reinicio
    int parar;

    initscr();
    // https://linux.die.net/man/3/noecho
    noecho();
    

    // Seleccion de nivel
    switch(nivel){

        case 1:
            timeout(100);
            break;
        case 2:
            timeout(75);
            break;
        case 3:
            timeout(40);
            break;
        case 4:
            timeout(20);
            break;
    }
    

    while (1){

        // Limpiamos la pantalla y volvermos a pintar
        clear();
        
        // Pintamos la separación de los campos y los jugadores
        int i=0;
        for (i; i < rows; i++){
            mvprintw(i, cols/2, "+");
        }
        mvprintw(rows-1, cols/2+2, "Jugador 2");
        mvprintw(rows-1, cols/2-10, "Jugador 1");


        //Dibujamos la pelota
        mvprintw(next_y, next_x, "O");
        // Dibujamos las palas en el tablero
        dibujar_paletas(pos_jug1_y, pos_jug2_y,cols-1);

        //Refrescamos el tablero con las nuevas posiciones
        refresh();
        
        // Movemos la pelota siempre
        next_x = mover_pelota(x,direccion_pelota_x);
        next_y = mover_pelota(y,direccion_pelota_y);
    
        
        // Comprobamos si cambia de direccion en el eje Y si llega arriba o abajo
        // Si no, aumentamos o restamos en uno para la siguiente iteración
        if(next_y >= max_y || next_y <= 0){
            direccion_pelota_y *= -1;
        }else{
            y += direccion_pelota_y;
        }

        // Comprobamos si cuando llega a los lados, la posicion del jugador (la barra) se encuntra en el camino
        // Entonces, si llegamos a la columna del jugador y el jugador se encuentra, rebota
        if(next_x == pos_jug2_x && (next_y <= pos_jug2_y + 4 && next_y >= pos_jug2_y)){
            direccion_pelota_x *= -1;       // Si lo está, cambiamos de direccion para el jugador 2
        }else if(next_x == pos_jug1_x && (next_y <= pos_jug1_y + 4 && next_y >= pos_jug1_y)){
                direccion_pelota_x *= -1;   // Si lo está, cambiamos de direccion para el jugador 1
            }else{
                if(next_x == pos_jug2_x && (next_y > pos_jug2_y + 4 || next_y < pos_jug2_y)){       // Preguntamos si reiniciar o finalizar
                    
                    // Decimos quien ha ganado
                    if(next_x == pos_jug2_x){
                        quien_gana = 1;
                    }else{
                        quien_gana = 2;
                    }
                    mvwprintw(window, 5,25, "Fin de la partida. Gana el jugador %d", quien_gana);
                    wrefresh(window);
                    usleep(2000000); 
                    mvwprintw(window, 6,5, "Pulsa 1 y pulsa enter para continuar. Pulsa cualquier otra y enter para salir");
                    wrefresh(window);

                    int paro = scanf(" %d", &parar);
                    if((paro == EOF || paro == -1 || paro == 0)){
                        clear();
                        endwin();
                        return 0;
                    }
                    if(parar != 1){
                        clear();
                        endwin();
                        return 0;
                    }
                    // Reiniciamos todas las variables necesarias
                    
                    // Colocamos la posicion de la pelota (en el centro)
                    int next_x = max_x/2, next_y = max_y/2;
                    // Damos los mismos valores a X e Y respectivamente
                    x = max_x/2;
                    y = max_y/2;
                    //posicion del jugador 1
                    int pos_jug1_x = 0, pos_jug1_y = 0;
                    //posicion del jugador 2
                    int pos_jug2_x = max_x - 1, pos_jug2_y = 0 ;
                    //direccion de la pelota hacia la derecha inicialmente
                    int direccion_pelota_x = 1, direccion_pelota_y = 1;
                    continue;

                }else{
                    if(next_x == pos_jug1_x && (next_y > pos_jug1_y + 4 || next_y < pos_jug1_y)){
                        // Decimos quien ha ganado
                        if(next_x == pos_jug2_x){
                            quien_gana = 1;
                        }else{
                            quien_gana = 2;
                        }
                        mvwprintw(window, 5,25, "Fin de la partida. Gana el jugador %d", quien_gana);
                        wrefresh(window);
                        usleep(2000000); 
                        mvwprintw(window, 6,5, "Pulsa 1 y pulsa enter para continuar. Pulsa cualquier otra y enter para salir");
                        wrefresh(window);

                        int paro = scanf(" %d", &parar);
                        if((paro == EOF || paro == -1 || paro == 0)){
                            clear();
                            endwin();
                            return 0;
                        }
                        if(parar != 1){
                            clear();
                            endwin();
                            return 0;
                        }
                        // Reiniciamos todas las variables necesarias
                        
                        // Colocamos la posicion de la pelota (en el centro)
                        int next_x = max_x/2, next_y = max_y/2;
                        // Damos los mismos valores a X e Y respectivamente
                        x = max_x/2;
                        y = max_y/2;
                        //posicion del jugador 1
                        int pos_jug1_x = 0, pos_jug1_y = 0;
                        //posicion del jugador 2
                        int pos_jug2_x = max_x - 1, pos_jug2_y = 0 ;
                        //direccion de la pelota hacia la derecha inicialmente
                        int direccion_pelota_x = 1, direccion_pelota_y = 1;
                        continue;
                    }else{
                        x += direccion_pelota_x;    // En caso contrario, dejamos que continue
                    }
                }
            }
        switch (getch()){
            // Teclas para el 1
            case 'q':
                // Esta es la posicion más abajo de la paleta
                if(pos_jug1_y > 0){
                    pos_jug1_y -= 1;
                }
                break;

            case 'a':
                // Esta es la posicion más arriba de la paleta
                if (pos_jug1_y + 3 < max_y - 1)
                    pos_jug1_y += 1;
                break;

            //Teclas para el 2
            case 'p':
                if(pos_jug2_y > 0){
                    pos_jug2_y -= 1;
                }
                break;

            case 'l':
                if (pos_jug2_y + 3 < max_y - 1){
                    pos_jug2_y += 1;
                }
                break;

            default:
                break;
        }
        

    }
    
    endwin();




}
```


Se trata de un pequeño juego en terminal basado en el clásico Ping-Pong. Primero mostramos una pantalla de carga.

![enter image description here](https://github.com/Phyrov/PDIH/blob/main/P2/img/Instruction-pingpong.png?raw=true)

Seleccionamos el nivel de dificultad.

![enter image description here](https://github.com/Phyrov/PDIH/blob/main/P2/img/Level-selection.png?raw=true)

Tras acabar la partida se muestra la pantalla final y el ganador.

![enter image description here](https://github.com/Phyrov/PDIH/blob/main/P2/img/Playing-game.png?raw=true)

