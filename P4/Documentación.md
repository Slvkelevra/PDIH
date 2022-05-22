# Práctica 4: El lenguaje Postscript
## Objetivos
- Conocer la sintaxis básica del lenguaje Postscript. 
- Crear varios archivos y probar el funcionamiento con un visor Postscript.
- Transformar los ejemplos creados a otros formatos de archivo, como PDF.


## Casa
```ps
%!PS
%%************* PARTE DE ABAJO DE LA CASUCHA
newpath

150 300 moveto % move pointer to (x,y)=(10,200)
300 0 rlineto %% Linea de abajo
0 250 rlineto %% La lateral derecha
-300 0 rlineto %% la de abajo
0 -250 rlineto %% La lateral izquierda

closepath

5 setlinewidth
stroke

%%************* TEJADO DE LA CASUCHA
newpath

100 550 moveto %% Nos colocamos en la izquierda de la base del tejado
400 0 rlineto %% Linea de abajo del tejado. 400 hacia la derecha
-200 200 rlineto %% 200 para arriba y 200 para la izquierda
-200 -200 rlineto %% 200 para abajo y 200 para la izquierda
0.7 0.1 0.0 setrgbcolor
fill

closepath
5 setlinewidth
stroke

%%************* VENTANA IZQUIERDA
newpath

200 500 moveto
50 0 rlineto
0 -50 rlineto
-50 0 rlineto
0 50 rlineto
0.5 0.2 0.0 setrgbcolor

fill

closepath

5 setlinewidth
stroke

%%************* VENTANA DERECHA

newpath

350 500 moveto

50 0 rlineto

0 -50 rlineto

-50 0 rlineto

0 50 rlineto

0.5 0.2 0.0 setrgbcolor

fill

closepath

5 setlinewidth

stroke

%%************ LA PUERTA
newpath

275 300 moveto
0 75 rlineto
50 0 rlineto
0 -75 rlineto
0.5 0.2 0.0 setrgbcolor
fill

closepath
5 setlinewidth
stroke

%%************ TEXTO
/Times-Roman findfont % La fuente

20 scalefont % Escalar 20 puntos la fuente
setfont
newpath
200 400 moveto
(Mi casucha!) show
stroke
showpage % We're done
```
![enter image description here](https://github.com/Phyrov/PDIH/blob/main/P4/img/casa.png?raw=true)
## Tarjeta
```ps
%!PS

%%************* RECTÁNGULO DE LA TARJETA

newpath

75 350 moveto % move pointer to (x,y)=(10,200)
450 0 rlineto %% Linea de abajo
0 300 rlineto %% La lateral derecha
-450 0 rlineto %% la de abajo
0 -300 rlineto %% La lateral izquierda
0.90 0.90 0.90 setrgbcolor

fill

5 setlinewidth
closepath
stroke

%% CIRCULO IZQUIERDO EXTERIOR

newpath

160 560 60 0 360 arc
0 0 0 setrgbcolor fill

%% CIRCULO INTERIOR

160 560 56 0 360 arc closepath
0 0.7 0 setrgbcolor fill

%% CIRCULO INTERIOR

160 560 50 0 360 arc closepath
0 0 0 setrgbcolor fill

%%************** TEXTO

/Times-Roman findfont % La fuente
40 scalefont % Escalar 20 puntos la fuente
setfont
newpath
350 560 moveto
(PDIH) show
stroke

%%************** TEXTO

/Times-Roman findfont % La fuente
20 scalefont % Escalar 20 puntos la fuente
setfont
newpath
280 530 moveto
(Amante de los perifericos) show
stroke

%%************** TEXTO FRANCISCO

/Times-Roman findfont % La fuente
20 scalefont % Escalar 20 puntos la fuente
setfont
newpath
320 470 moveto
(Francisco Lara Marin) show
stroke

%%************** TEXTO ALVARO

/Times-Roman findfont % La fuente
20 scalefont % Escalar 20 puntos la fuente
setfont
newpath
325 450 moveto
(Alvaro Marin Perez) show
stroke
showpage
```
![enter image description here](https://github.com/Phyrov/PDIH/blob/main/P4/img/tarjeta.png?raw=true)

## Extra: Corazón
```ps
%!PS

%% CIRCULO IZQUIERDO CORAZON
newpath
165 560 60 0 360 arc
1 0 0 setrgbcolor fill
closepath
stroke

%% CIRCULO DERECHO CORAZON
newpath
275 560 60 0 360 arc
1 0 0 setrgbcolor fill
closepath
stroke

%% TRIANGULO
newpath
332 539 moveto
-224 0 rlineto
120 -200 rlineto
1 0 0 setrgbcolor fill
closepath
stroke

%%************** TEXTO

/Times-Roman findfont % La fuente
12 scalefont
setfont
newpath
380 500 moveto
0.8 0.8 0.8 setrgbcolor
(La belleza no es nada, no permanece) show
stroke

%%************** TEXTO

/Times-Roman findfont % La fuente
12 scalefont % Escalar 20 puntos la fuente
setfont
newpath
380 480 moveto
0.5 0.5 0.5 setrgbcolor
(No sabes la suerte que tienes sin belleza.) show
stroke

%%************** TEXTO

/Times-Roman findfont % La fuente
12 scalefont % Escalar 20 puntos la fuente
setfont
newpath
380 460 moveto
0.2 0.2 0.2 setrgbcolor
(Porque si le gustas a alguien,) show
stroke

%%************** TEXTO

/Times-Roman findfont % La fuente
12 scalefont % Escalar 20 puntos la fuente
setfont
newpath
380 440 moveto
0 0 0 setrgbcolor
(sabes que es por otra cosa.) show
stroke

showpage
```
![enter image description here](https://github.com/Phyrov/PDIH/blob/main/P4/img/corazon.png?raw=true)
# Autores ✒️

* **Francisco Lara Marín**
* **Álvaro Marín Pérez**
