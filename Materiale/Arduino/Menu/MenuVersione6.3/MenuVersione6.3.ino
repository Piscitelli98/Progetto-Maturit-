#include <Keypad.h>
#include <LiquidCrystal.h>  
#include <DS3232RTC.h>   
#include <TimeLib.h>         
#include <Wire.h>  
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Fingerprint.h>

//test
String pswTest="1998";

//estensione memoria SD
File myFile;
int id = 1;

//imprinte digitali
//collegamenti rosso->5v | nero->gnd | verde->d2 | bianco-d3
int getFingerprintIDez();
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);
boolean esitoLettura=false;
int idLettura=-1;
String message="";
String logIn="login_request;BeppeL;c7cc6a1fd6d6b5f4817025cb532b52fa;%";
boolean fineMSGPERC=false;


//lcd, configurazione e collegamenti
//VSS->gnd | VDD->vcc | V0->potenziometro | RS->7 | RW->gnd | E->6 | D4->5 | D5->4 | D6->3 | D7->2 | A->vcc330Hom | K->gnd
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
//LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
int stato=0;
String lettura="";
boolean chiuso=true;

//pin motorini serratura
int m0=32, m1=33, m2=34, m3=35;//50,51,52,53
long secondiStop=0;
int minutiCambioOra=0;
int tempoApertChius=5;


const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {22, 23, 24, 25}; //connect to the row pinouts of the keypad 2-7-6-4 || 4-5-6-7
byte colPins[COLS] = {26, 27, 28}; //connect to the column pinouts of the keypad 3-1-5 || 1-2-3

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  Serial1.begin (9600);//clock
  Serial3.begin(9600);
   lcd.begin(16, 2);  
   lcd.setCursor(0, 0); 
   lcd.print("Ins. codice...");
   lcd.setCursor(0, 1); 
   lcd.print("Ins:");
   lcd.setCursor(4, 1);    

   //pin motorino setup
   pinMode(m0, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);

//imposto le uscite a livello logico basso
  digitalWrite(m0, LOW);
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);

//rtc
    setSyncProvider(RTC.get);   // the function to get the time from the RTC
    if(timeStatus() != timeSet) 
        Serial.println("Unable to sync with the RTC");
    else
        Serial.println("RTC has set the system time"); 

//sensore impronte digitali
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    //while (1);
  }
//memoria SD

Serial.print("Inizializzazione Card: ");
  if (!SD.begin(53)) //il Pin 53 è collegato a CS
  {
    Serial.println("FALLITA!");
  }
  else{
    Serial.println("ESEGUITO!");
    }
  


        stampaData(); 
        minutiCambioOra=minute();
}


//--metodi
void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    Serial.print(':');
    if(digits < 10)
        Serial.print('0');
    Serial.print(digits);
}

void digitalClockDisplay(void)
{
    // digital clock display of the time
    Serial.print(hour());
    printDigits(minute());
    printDigits(second());
    Serial.print(' ');
    Serial.print(day());
    Serial.print(' ');
    Serial.print(month());
    Serial.print(' ');
    Serial.print(year()); 
    Serial.println(); 
}

  //gestisce la lettura del tastierino elaborandola
 void gestisciInsert(String lettura){

  //leggo il primo carattere per sapere se è una password di accesso o un comando
  String tp=lettura.substring(0,1);  
  Serial.print("Lettura prima di entrare nel controllo: ");
  Serial.println(lettura);
  if(tp=="*"){//se il primo carattere è un *, allora è un comando
   /* Serial.println("----------dentro if tp");
    Serial.print("----------LEttura lettura: ");
     Serial.println(lettura);
    Serial.print("----------Lettura tp: ");
    Serial.println(tp);*/
    if(lettura=="*1"){ stato=1; Serial.println("----------dentro if tp -----------stato 1");}
    else if(lettura=="*2"){ stato=2; Serial.println("----------dentro if tp -----------stato 2");}
    else if(lettura=="*3"){ stato=3; Serial.println("----------dentro if tp -----------stato 3");}
    else if(lettura=="*4"){ stato=4; Serial.println("----------dentro if tp -----------stato 4");}
    else if(lettura=="*5"){ stato=5; Serial.println("----------dentro if tp -----------stato 5");}
    else if(lettura=="*6"){ stato=6; Serial.println("----------dentro if tp -----------stato 6");}
    else if(lettura=="*7"){ stato=7; Serial.println("----------dentro if tp -----------stato 7");}
    else if(lettura=="*1234567890"){ stato=1234567890; Serial.println("----------dentro if tp -----------stato 1234567890");}
    else { stato=-1; Serial.println("----------dentro if tp -----------stato -1 ERRORE");}
  }//fine if controllo
  else{//se è una password controllo su database
    Serial.print("Lettura prima di entrare nel controllo DELLA PASSWORD : ");
  Serial.println(lettura);
    Serial.println("controllo psw");
    if(pswTest==lettura){
        stato=2;
        Serial.println("--******--dentro if controllo PASSWORD --******-- stato 2");
      }    
     else if(lettura==""){
      Serial.println("Chiudo Cassaforte");
      //chiudi();
      stato=4;
      lettura="";
      pulisciLCD();
      }
      else{
        stato=-1;
        }

    lettura="";
   
    pulisciLCD();
   // valore=1;
  }
  
  //return valore;
 }

 
void pulisciLCD(){
  lcd.setCursor(4, 1); 
    lcd.print("            ");
    delay(100);
     lcd.setCursor(4, 1);   
}

  //metodi motorino
void  fase1(){
   //FASE 1
    //Alimento solo la prima bobina
    digitalWrite(m0, HIGH);
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    delay(10);
  }
  
 void fase2(){
  //FASE 2
    //Alimento solo la seconda bobina
    digitalWrite(m0, LOW);
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    delay(10);
  }
  
void  fase3(){
  //FASE 3
    //Alimento solo la terza bobina
    digitalWrite(m0, LOW);
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    delay(10);
  }
  
void  fase4(){
  //fase 4
    //Alimento solo la quarta bobina
    digitalWrite(m0, LOW);
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    delay(10);
  }


 void avanti(){
    fase1();
    fase2();
    fase3();
    fase4();
  }

void  indietro(){
    fase4();
    fase3();
    fase2();
    fase1();
  }

 //metodo per portare tutte le bobine del motorino a LOW 
void tuttoSpento(){
      digitalWrite(m0, LOW);
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
  }
//problema riscontrato: calcolo basato sui secondi da problemi a cavallo tra un minuto e un altro
void apri(){
 if(chiuso){ //se chiuso è uguale a true, quindi se è chiuso apri
  lcd.setCursor(4,1);
  lcd.print("Apertura...");
  secondiStop=now()+tempoApertChius;
 
    while(now()<secondiStop){
    indietro();
    }
    tuttoSpento();
    secondiStop=0;
    chiuso=false;
 }
}
void chiudi(){
if(!chiuso){// se chiuso è a false quindi è aperto
   lcd.setCursor(4,1);
  lcd.print("Chiusura...");
secondiStop=now()+tempoApertChius;
    
    while(now()<secondiStop){
    avanti();
    }
    tuttoSpento();
     secondiStop=0;
     chiuso=true;
     esitoLettura=false;
  }
}

void stampaData(){
 lcd.setCursor(0, 0); 
   lcd.print(day()); 
   lcd.print("/");
    lcd.print(month()); 
   lcd.print("/");
    lcd.print(year()); 
   lcd.print(" ");
    lcd.print(hour()); 
   lcd.print(":");
    if(minute() < 10)
        lcd.print('0');
    lcd.print(minute());

    lcd.setCursor(4,1);
 }

 //metodi lettore impronte digitali

 
uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
}

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
   esitoLettura=true;
   idLettura=finger.fingerID;
}
boolean leggiImpronta(){
      //metodo per la lettura del sensore di impronte digitali
   getFingerprintIDez();
  delay(50);

  return esitoLettura;
  }

void msgBT(){
   while(Serial3.available() > 0) {//attende fino a che seriale non riceve qualcosa
 //gestiscoIlmessaggio
    char lettoCh=Serial3.read();
    message+=lettoCh;
    if(lettoCh=='%'){
      fineMSGPERC=true;
      }
   }
   if(message!=""){
    Serial.print("messaggio: ");
  Serial.println(message);
    }
  
if(fineMSGPERC){
  //faccio lo substring della prima parte per capire che tipo di messaggio sto ricevendo
   int primoPuntoVirgola = message.indexOf(';');
   String tipoMSG = message.substring(0, primoPuntoVirgola+1);
 Serial.print("messaggio tipo: ");
  Serial.println(tipoMSG);

   if(tipoMSG=="login_request;"){
     Serial.println("Dentro loginrequest");
     int trovPerc = message.indexOf('%');
    message=message.substring(primoPuntoVirgola+1, trovPerc+1);
     Serial.print("messaggio per user: ");
  Serial.println(message);
    int secondoPuntoVirgola = message.indexOf(';');
    String username=message.substring(0, secondoPuntoVirgola);
    trovPerc = message.indexOf('%');
    message=message.substring(secondoPuntoVirgola+1, trovPerc+1);
    int terzoPuntoVirgola = message.indexOf(';');
    Serial.print("messaggio per pass: ");
  Serial.println(message);
    String password=message.substring(0, terzoPuntoVirgola);
    Serial.print("Username: ");
    Serial.println(username);
     Serial.print("Password: ");
    Serial.println(password);

  //!!!^^^!!! DA IMPLEMENTARE
/*String messRitorno=getCredenzialiLogin(username, password);
      String msgResponse="login_response;"+messRitorno+";%";
      Serial3.write(msgResponse);
  */
    
    fineMSGPERC=false;
    message="";
    stato=2;
  }

  else if(tipoMSG=="get_datiLog_request;"){
    //prendo i valori del messaggio
    Serial.println("Dentro getDatiLog");
     int trovPerc = message.indexOf('%');
    message=message.substring(primoPuntoVirgola+1, trovPerc+1);
     Serial.print("messaggio per user: ");
  Serial.println(message);
    int secondoPuntoVirgola = message.indexOf(';');
    String username=message.substring(0, secondoPuntoVirgola);
    trovPerc = message.indexOf('%');
    message=message.substring(secondoPuntoVirgola+1, trovPerc+1);
    int terzoPuntoVirgola = message.indexOf(';');
    Serial.print("messaggio per pass: ");
  Serial.println(message);
    String data=message.substring(0, terzoPuntoVirgola);
    Serial.print("Username: ");
    Serial.println(username);
     Serial.print("data: ");
    Serial.println(data);
    
    //richiamo il metodo per trovare nella memoria i dati di log, prima però devo verificare le credenziali dell'username
    //quindi gli passerò username e la data dei log che devo visualizzare
                //!!!^^^!!!! METODO DA IMPLEMENTARE
    /*String messRitorno=getDatiLog(username, data);
        if(messRitorno.length()<3){
          String msgResponse="get_datiLog_response;"+messRitorno+";%";
          Serial3.write(msgResponse);
          }
         else{
          String msgResponse="get_datiLog_response;0;%";
          }
    Serial3.write(messRitorno);
    Serial3.write("get_datiLog_end;%");*/
    fineMSGPERC=false;
    message="";
    
    }
   else if(tipoMSG=="close_request;"){
    Serial.println("Dentro closerequest");
    stato=4;
    if(chiuso){
      Serial3.write("close_response;-1;%");
      }
     else if(!chiuso){
      Serial3.write("close_response;0;%");
      }
    
     fineMSGPERC=false;
    message="";
    }
   else if(tipoMSG==";"){
    
    }
     else if(tipoMSG==";"){
    
    }
   
 
    }
  /* if(message==logIn){stato=2; Serial.println("dentro if login==message, stato = 2");}
   else{
     //Serial.println("cancello messaggio");
    //message="";
    }*/
}
 void lettura_sd_utenti(){
  myFile = SD.open("utenti.txt");
  if (myFile) {
    Serial.println("utenti.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening utenti.txt");
  }
} 
//---------!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!___________


  
void loop(){
   char key; 


switch (stato){
  case 0:
  {
     //digitalClockDisplay();  
     if(minutiCambioOra!=minute()){
      stampaData();
      minutiCambioOra=minute();
      }
     key = keypad.getKey();
     msgBT();
          if (key != NO_KEY){
                  if(key=='#'){
                        Serial.print("Lettura: ");
                        Serial.println(lettura);
                        gestisciInsert(lettura);
                        //stato=gestisciInsert(lettura);
                        Serial.println("Cambiato stato");
                        Serial.println(stato);  
                       
                    }
              
              lcd.print("*");
              lettura+=key;
              
              //codice di controllo
              Serial.print("key: ");
              Serial.println(key);
              Serial.print("Stato: ");
              Serial.println(stato);    
    }break;

  case 1:
  {
    Serial.print("Stato dentro stato 1: ");
              Serial.println(stato);  
  digitalClockDisplay();  
  delay(1000);
  digitalClockDisplay();

    Serial.println("caso1");
    Serial.println("cambio lo stato a 0");
    delay(2000);
    pulisciLCD();
    lettura="";
    stato=0;
    }break;
  }

  case 2:
  {
    Serial.print("Stato dentro stato 2: "); Serial.println(stato);                            
   Serial.println("caso lettura impronte digitali");
    secondiStop=now()+10;
    
     //codice per la visualizzazione su lcd
   lcd.setCursor(0, 1); 
   lcd.print("ins. Impronta...");
   lcd.setCursor(4, 1); 
   
    do{
    esitoLettura = leggiImpronta();
    }while(esitoLettura==false && now()<secondiStop);
      
   //codice per la visualizzazione su lcd
  lcd.setCursor(0, 1); 
   lcd.print("Ins:");
   lcd.setCursor(4, 1);
   pulisciLCD();
   
    if(esitoLettura){
      apri();
    }
    else
    {
      Serial.println("Errore Impronta");
      }
   pulisciLCD();
   lettura="";
   message="";
   
    stato=0;
    }break;

  case 3:
  {
    Serial.println("Caso 3| test apertura");
   apri();
     pulisciLCD();
   lettura="";
    stato=0;
    }break;

  case 4:
  {
     Serial.println("Caso 4| test chiusura");
    chiudi();
     pulisciLCD();
   lettura="";
    stato=0;
    }break;

  case 5:
  {
    pulisciLCD();
   lettura="";
    stato=0;
    }break;

  case 6:
  {
    pulisciLCD();
   lettura="";
    stato=0;
    }break;

 case 7:
  {
    pulisciLCD();
    lettura_sd_utenti();
   lettura="";
    stato=0;
    }break;
case 1234567890:
  {
    Serial.println("Stampo tutte le variabili...");
    delay(300);
    Serial.print("pswTest: "); Serial.println(pswTest);
    Serial.print("EsitoLettura: "); Serial.println(esitoLettura);
    Serial.print("idLettura: "); Serial.println(idLettura);
    Serial.print("stato: "); Serial.println(stato);
    Serial.print("lettura: "); Serial.println(lettura);
    Serial.print("chiuso: "); Serial.println(chiuso);
    Serial.print("tempo Apertura e chiusura: "); Serial.println(tempoApertChius);
    
    pulisciLCD();
   lettura="";
    stato=0;
    }break;
  case -1:
  {
    Serial.println("errore, codice menue inesistente");
    pulisciLCD();
    lcd.print("Err. menu");
    delay(1000);
    pulisciLCD();
   lettura="";
    stato=0;
    }break;

  default:
  {
    Serial.println("errore");
    }break;
  
  
  }
 
}
