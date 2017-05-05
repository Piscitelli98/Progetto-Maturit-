#include <SoftwareSerial.h>

//NOTA IMPORTANTE, il piedino rx e tx del modulo HC-06 vano collegati rispettivamente al tx e rx di arduino(rx va con tx e tx con rc, si invertono)
const int rxpin = 2;  //Andiamo ad assegnare al pin 2 l’indirizzo di ricezione dati (e lo colleghiamo al pin TXD del modulo)
const int txpin = 3;  //Assegnamo invece al pin 3 l’indirizzo di trasmissione dati (collegandolo al pin RXD del nostro componente
SoftwareSerial bluetooth(rxpin, txpin);  //Assegnamo ad un nome (bluetooth) i suoi pin di ricezione e trasmissione, per facilitarci la scrittura del codice
String message;
String logIn="login_request;BeppeL;c7cc6a1fd6d6b5f4817025cb532b52fa";
String request="registration_request;BeppeL;c7cc6a1fd6d6b5f4817025cb532b52fa"; /*;81dc9bdb52d04dc20036dbd8313ed055*/
String requestOpen="open_request;BeppeL;c7cc6a1fd6d6b5f4817025cb532b52fa"; 
String requestClose="close_request;BeppeL;c7cc6a1fd6d6b5f4817025cb532b52fa"; 

String requestCheckPin="open_request;81dc9bdb52d04dc20036dbd8313ed055"; /*;81dc9bdb52d04dc20036dbd8313ed055*/
String newRegistration="";
void setup(){
   pinMode(13, OUTPUT);
    
    Serial.begin(9600);  //Inizializziamo l’interfaccia seriale al baud rate dell’AT-mode
    bluetooth.begin(9600);  //Inizializziamo l’interfaccia del modulo bluetooth sempre al baud rate riferito alla modalità AT
  }
  
  void loop(){
    while(bluetooth.available()){
        message+=char(bluetooth.read());
  }
  if(!bluetooth.available())
  {
    Serial.println(message);
    if(message==logIn){//se arrivano informazioni
      delay(200);
      bluetooth.write("TTRUEE");
      Serial.println("Inviato ");
      message=""; //pulisci il messaggio
    }
   
    if(message==request){//se arrivano informazioni
      delay(200);
      newRegistration=message;//registrato
      bluetooth.write("TTRUEE");//invio conferma
      Serial.println("Inviato ");
      message=""; //pulisci il messaggio
    }
    if(message==requestCheckPin){
      delay(200);
      bluetooth.write("TTRUEE");
      Serial.println("Inviato ");
      message=""; //pulisci il messaggio
    }
    if(message==requestClose){
      delay(200);
      Serial.println("Chiusura cassaforte");
      message=""; //pulisci il messaggio
    }
    if( message == requestOpen){
      delay(200);
      Serial.println("Apertura cassaforte");
      message=""; //pulisci il messaggio
    }
     if(message!=logIn && message!="" && message!=request){
      delay(200);
      bluetooth.write("FFALSE");
      Serial.println("Else Inviato ");
      message=""; //pulisci il messaggio
    }
    

  }
  delay(500); //attendi


  }
