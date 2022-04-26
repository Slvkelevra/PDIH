
# Práctica 3: Experimentación con Arduino
## Pre-Requisitos📋
- Arduino
## Objetivos
- Instalar las herramientas de trabajo con Arduino.
- Configurar el dispositivo Arduino para hacer programas básicos
- Hacer programas sencillos de entrada/salida con Arduino.
# Instalación
Inicialmente disponíamos de un Arduino MEGA. Tras descargar el software necesario conectamos Arduino y en la barra de herramientas seleccionamos nuestra placa y modelo de nuestro Arduino
![
](https://github.com/Phyrov/PDIH/blob/main/P3/img/config_arduino.png?raw=true)

# Proyectos
## Parpadeo de LED
Programa que enciende y apaga alternativamente 3 LEDs conectados a las salidas digitales 11, 12 y 13 a un intervalo de 1.5 segundos.
### Componentes :electric_plug:
- LEDs rojo, verde y amarillo.
- Resistencias de 1 Kohm.
- Cableado (en verde).
-  Placa madre de pruebas.
### Ejecución 
![enter image description here](https://github.com/Phyrov/PDIH/blob/main/P3/img/Ejercicio%201.gif?raw=true)
### Código
```c++
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
```

## Modificación parpadeo de LED
A partir del programa anterior, se realiza una modificación para que se encienda solo el LED rojo cuando se pulse un interruptor conectado a la entrada digital 7, y en ese momento se apaguen tanto el amarillo como el verde.
### Componentes :electric_plug:
- LEDs rojo, verde y amarillo.
- Resistencias de 1 Kohm.
- Cableado (en verde).
-  Placa madre de pruebas.
- Placa Arduino
- Botón (pulsador). Las patillas de un mismo lado no están conectadas entre sí. Las opuestas si que lo están.
- Resistencia de 10 K.
### Ejecución 
![enter image description here](https://github.com/Phyrov/PDIH/blob/main/P3/img/Ejercicio%202.gif?raw=true)

### Código
```c++
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
```
## Alarma por detección de presencia
### Componentes :electric_plug:
- LED amarillo.
- Resistencia de 1 K.
- Buzzer o zumbador. No es necesaria resistencia para su funcionamiento en este caso.
- Cableado (verde).
- Placa Arduino.
- Placa madre de pruebas.
- Sensor PIR o de movimiento pasivo: sensor que se enciende (HIGH) cuando detecta movimiento. Funciona mediante infrarrojos.
### Ejecución 
![
](https://github.com/Phyrov/PDIH/blob/main/P3/img/Ejercicio%203.gif?raw=true)
### Código
```c++
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
```

# Autores ✒️

* **Álvaro Marín Pérez**
* **Francisco Lara Marín**

