void setup() {
  //Pin para el led rojo
  pinMode(13,OUTPUT);
  //Pin para el led verde
  pinMode(12,OUTPUT);
  //Pin para el led amarillo
  pinMode(11,OUTPUT);

}

void loop() {
  // Para cada iteración, enciende los 3 leds
  int i = 11;
  for (i;i<14;i++){
    digitalWrite(i, HIGH);
  }
  // Espera un segundo y medio
  delay(1500);
  // Apaga los 3 leds
  i = 11;
  for (i;i<14;i++){
    digitalWrite(i, LOW);
  }
  delay(1500);
  
}
