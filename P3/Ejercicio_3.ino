void setup() {
  // Pin de salida del led
  pinMode(13, OUTPUT);
  // Pin de entrada del sensor de movimiento PIR
  pinMode(7, INPUT);

}
void loop() {
  // Para cada iteración, comprobamos el estado del pin 7. Si es HIGH, pita y enciende un led
  if (digitalRead(7) == HIGH){
    //Encendemos el led. También pita
    digitalWrite(13, HIGH);
  // Si no, se apagada el led
  }else{
    digitalWrite(13, LOW);
  }
}
