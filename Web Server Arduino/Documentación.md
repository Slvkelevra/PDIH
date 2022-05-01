
# Web Server con Arduino
## Introducción
**Arduino es una plataforma de creación de electrónica de código abierto**, la cual está basada en hardware y software libre, flexible y fácil de utilizar para los creadores y desarrolladores. Esta plataforma permite crear diferentes tipos de microordenadores de una sola placa a los que la comunidad de creadores puede darles diferentes tipos de uso. [[1]](https://www.xataka.com/basics/que-arduino-como-funciona-que-puedes-hacer-uno)

## Herramientas 🔧
- Arduino MEGA
- Shield Ethernet: permite conectar nuestro Arduino UNO o Arduino MEGA a una red mediante un **cable  _ethernet_**

## Objetivo
Controlar nuestra placa Arduino MEGA a través de una página web gracias al módulo Shield Ethernet.
## Web 
Creamos una web sencilla que nos permite controlar una LED de nuestro Arduino. Previamente será necesario un login en dicha web.
![enter image description here](https://github.com/Phyrov/PDIH/blob/main/Web%20Server%20Arduino/img/Login.jpg?raw=true)

![enter image description here](https://github.com/Phyrov/PDIH/blob/main/Web%20Server%20Arduino/img/Logged.jpg?raw=true)

### Problema ⚠️
Cuando conectamos Arduino a internet, el servidor DHCP asigna una IP a nuestro dispositivo. El problema es que si esa IP cambia, dejará de funcionar.

Necesitamos:
-  Configurar el router para que no cambie la IP de nuestro Arduino.
- Abrir puertos del router para conectar con Arduino.
- Conseguir que no cambie la IP pública.

## Asignar IP y MAC
A pesar de que cada router tiene una configuración distinta, el método es el mismo. Es necesario indicarle al servidor DHCP que asigne una IP a una MAC (identificación del dispositivo dentro de la red). 

![enter image description here](https://github.com/Phyrov/PDIH/blob/main/Web%20Server%20Arduino/img/Asignar%20IP%20y%20MAC%20a%20arduino.png?raw=true)

![enter image description here](https://github.com/Phyrov/PDIH/blob/main/Web%20Server%20Arduino/img/Asignar%20IP%20y%20MAC%20a%20arduino%202.png?raw=true)
![enter image description here](https://github.com/Phyrov/PDIH/blob/main/Web%20Server%20Arduino/img/Asignar%20IP%20y%20MAC%20a%20arduino%203.png?raw=true)

## Configuración de puertos
Para que Arduino pueda compartir y recibir información con el exterior, será necesario abrir un puerto.  Para ello, nos guiaremos por las palabras NAT,Virtual Server ó Port Forwarding.
![enter image description here](https://github.com/Phyrov/PDIH/blob/main/Web%20Server%20Arduino/img/Abrir%20puertos%201.jpg?raw=true)

![enter image description here](https://github.com/Phyrov/PDIH/blob/main/Web%20Server%20Arduino/img/Abrir%20puertos%202.jpg?raw=true)

![enter image description here](https://github.com/Phyrov/PDIH/blob/main/Web%20Server%20Arduino/img/Abrir%20puertos%203.jpg?raw=true)

## Conexión de Arduino con Shield Ethernet
La conexión del módulo Shield Ethernet depende del tipo de Arduino. Un ejemplo de conexión con el modelo UNO es la siguiente:
![enter image description here](https://github.com/Phyrov/PDIH/blob/main/Web%20Server%20Arduino/img/conexion.jpg?raw=true)

En nuestro caso la conexión al completo quedaría de la siguiente manera:
![enter image description here](https://github.com/Phyrov/PDIH/blob/main/Web%20Server%20Arduino/img/Completo.jpg?raw=true)
### Código
```c++
#include  <String.h>
#include  <SPI.h>
#include  <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Dirección MAC que hemos asignado
byte ip[] = { 192, 168, 1, 200}; // ip en la red.
EthernetServer  server(8080); //server port

//Será la cadena para leer la petición http
String readString = "" ;
int PIN = 9; // PIN para led
boolean login; // Para saber si estamos logeados o no
String Estado_Pin = String(8);

  
void  setup(){
	thernet.begin(mac, ip);
	Serial.begin(9600);
	pinMode(PIN, OUTPUT);
	digitalWrite(PIN, LOW);
	Estado_Pin = "ENCENDER";
	login=false;
	server.begin();
}

void  loop(){
	EthernetClient client = server.available();

	//Buscamos constantemente si tenemos clientes
	//Si tenemos cliente
	if (client) {
		boolean currentLineIsBlank = true;
		while (client.connected()) {
	
			//Si tenemos datos para leer
			if (client.available()) {
				//Leemos la petición letra por letra

				char c = client.read();

				//Unimos el string con la petición.Ahora tenemos la petición en formato String

				readString.concat(c);

				//Cuando ya no hay para leer,el servidor está listo para mandar la respuesta

				if (c == '\n' && currentLineIsBlank) {
				//Si el usuario y la contraseña son correctos(Mayor que 0)

				if(readString.indexOf("User=pdih&Pass=pdih") > 0) {

				login=true;

				}

				//Si nos hemos logueado y existe un Logout, nos salimos

				if(login==true){

				if(readString.indexOf("Logout") > 0) {

				login=false;

				}

				}

				// Si el cliente no se ha logeado, le mostramos el login

				if (login == false) {

					client.println("HTTP/1.1 200 OK");
					client.println("Content-Type: text/html");
					client.println();
					client.print("<html>");
					client.println("<meta http-equiv=\"refresh\" content=\"60\">");
					client.println(" <head><title>WebServer Arduino. PDIH</title><center></head><body> ");
					client.println("<h1>Bienvenido</h1>");
					client.println("<h1>Ingrese su usuario y contrasenia</h1>");
					client.print("<form action='/'>");
					client.print("Usuario: <input name='User' value=''>");
					client.print("Contrasenia: <input type='Password' name='Pass' value=''>");
					client.print("<input type='submit' value=' Entrar '>");

				}else{

				//Comprobamos si se ha encendido alguna vez. Si es asi,se comprueba su estado

				int Dato = readString.indexOf("PIN");

				if (readString.substring(Dato, Dato + 5) == "PIN=S"){

					if (Estado_Pin == "ENCENDER") {

						digitalWrite(PIN, HIGH);

						Estado_Pin = "APAGAR";

						}

						else{

						digitalWrite(PIN, LOW);

						Estado_Pin = "ENCENDER";

					}

				}
				client.println("HTTP/1.1 200 OK");
				client.println("Content-Type: text/html");
				client.println();
				client.println("<!DOCTYPE html>");
				client.println("<html>");
				client.println("<br>""</br>");
				client.println("<br>""</br>");
				client.println("<br>""</br>");
				client.println("<head>");
				client.println(" <head><title>WebServer Arduino. PDIH</title><center></head><body> ");
				client.println("</head>");

				//Color de fondo
				client.println("<body style=background-color:#00ffff>");

				//cliente.println("<body width=100% height=100%>");
				client.println("<center>");
				client.println("<strong><font size=300>WebServer Arduino. PDIH</font></strong>");

				//Valor del led.ENCENDIDO o APAGADO
				client.print("<input type=submit value=");
				client.print(Estado_Pin);

				//Definimos el tamaño del boton. Cuando lo pulsamos, añadimos en la URL PIN=S
				client.print(" style=width:200px;height:75px onClick=location.href='./?PIN=S\'>");
				client.print("</center>");
				client.print("</body>");
				client.println("<center>");
				client.print("<h2><a href='/?Logout'>Logout</a>");
				client.print("</center>");
				client.print("</html>");

				}

				//clearing string for next read
				readString="";

				//stopping client
				client.stop();
				}
			}
		}
	}
}
```
### Resultado final
![enter image description here](https://github.com/Phyrov/PDIH/blob/main/Web%20Server%20Arduino/img/VID_20220429_191544.gif?raw=true)

## Bibliografía  📚

[[1] Xataka,  Qué es Arduino, cómo funciona y qué puedes hacer con uno](https://www.xataka.com/basics/que-arduino-como-funciona-que-puedes-hacer-uno)


# Autores ✒️

* **Francisco Lara Marín**
* **Álvaro Marín Pérez**
