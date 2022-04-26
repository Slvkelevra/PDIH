void setup() {
  // Pin de salida del led rojo
  pinMode(13,OUTPUT);
  // Pin de salida del led verde
  pinMode(12,OUTPUT);
  // Pin de salida del led amarillo
  pinMode(11,OUTPUT);
  // Este será el pin para el boton, que es entrada
  pinMode(7,INPUT);
}
// En esta variable leeremos si el pin 7 está activado (boton pulsado)
int valor_interruptor = 0;

void loop() {
  // Leemos y alamcenamos el valor en la variable
  valor_interruptor = digitalRead(7);
  // Si está pulsado, encendemos el rojo y apagamos el resto (si está activado será HIGH y LOW en caso contrario)
  digitalWrite(13, !valor_interruptor);
  digitalWrite(12, valor_interruptor);
  digitalWrite(11, valor_interruptor);
  
}
