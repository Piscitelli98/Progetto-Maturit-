/*

Sketch da caricare ad Arduino Mega collegato con il modulo bluetooth slave.

Effettua una lettura di un fooresistore e la invia elaborata in un range da 0 a 100

al bluetooth master.

*/

//short ph = A0; //Assegnamo al fotoresistore il pin A0

void setup() {
Serial.begin(9600);
Serial1.begin (9600); //Inizializziamo l’interfaccia seriale del bluetooth con baud rate 9600

}

void loop() {

  if (Serial1.available() > 0) {//attende fino a che seriale non riceve qualcosa
    char msg=Serial1.read();//mette la ricezione in un char
    Serial.print(msg);//la tsampa
    Serial1.print("okokok");
  }
  else{
    delay (1500); //Attesa di un secondo e mezzo per sincronizzare i dati che arrivano all’altro bluetooth
  }
}
