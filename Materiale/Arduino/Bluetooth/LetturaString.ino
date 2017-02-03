#include <SoftwareSerial.h>
 
int rxPin = 2;
int txPin = 3;
SoftwareSerial bluetooth(rxPin, txPin);

//stringa che memorizza il messaggio in arrivo 
String message;
 
void setup()
{
  Serial.begin(9600); //set baud rate
  bluetooth.begin(9600); //set baud rate
}
 
void loop()
{
  while(bluetooth.available()){
    message+=char(bluetooth.read());
  }
  if(!bluetooth.available())
  {
    if(message!="")
    {//se arrivano informazioni
      Serial.println(message); //stampa il messaggio
      message=""; //pulisci il messaggio
    }
  }
  delay(5000); //attendi
}











