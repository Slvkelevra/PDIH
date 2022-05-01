#include <String.h>
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Dirección MAC que hemos asignado
byte ip[] = { 192, 168, 1, 200}; // ip en la red.
EthernetServer server(8080); //server port
//Será la cadena para leer la petición http
String readString = "" ;

int PIN = 9;    // PIN para led
boolean login;  // Para saber si estamos logeados o no
String Estado_Pin = String(8);



void setup(){
  
Ethernet.begin(mac, ip);
Serial.begin(9600);
pinMode(PIN, OUTPUT);
digitalWrite(PIN, LOW);
Estado_Pin = "ENCENDER";
login=false;
server.begin();
}

void loop(){
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
    
          //Reseteamos el string 
          readString="";
          //Paramos el cliente para la siguiente lectura
          client.stop();
            
    
          }
      } 
    } 
  } 
}
