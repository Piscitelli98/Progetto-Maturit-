#include <Keypad.h>
#include <LiquidCrystal.h>  
#include <DS3232RTC.h>   
#include <TimeLib.h>         
#include <Wire.h>  

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
//LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
int ledPin=13;//led test
int stato=0;
String lettura="";

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {22, 23, 24, 25}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {26, 27, 28}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  Serial1.begin (9600);
   lcd.begin(16, 2);  
   lcd.setCursor(0, 0); 
   lcd.print("Ins. codice...");
   lcd.setCursor(0, 1); 
   lcd.print("Ins:");
   lcd.setCursor(4, 1);    

   pinMode(ledPin, OUTPUT);
   digitalWrite(ledPin, LOW);

    setSyncProvider(RTC.get);   // the function to get the time from the RTC
    if(timeStatus() != timeSet) 
        Serial.println("Unable to sync with the RTC");
    else
        Serial.println("RTC has set the system time"); 
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
    else { stato=-1; Serial.println("----------dentro if tp -----------stato -1 ERRORE");}
  }//fine if controllo
  else{//se è una password controllo su database
    Serial.println("controllo psw");
    lettura="";
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

//---------


  
void loop(){
   char key; 


switch (stato){
  case 0:
  {
     digitalClockDisplay();  
     key = keypad.getKey();
          if (key != NO_KEY){
                  if(key=='#'){
                        Serial.print("Lettura");
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
    Serial.print("Stato dentro stato 2: ");
              Serial.println(stato);
              
   Serial.println("caso2");
   pulisciLCD();
   lettura="";
    stato=0;
    }break;

  case 3:
  {
    digitalWrite(ledPin, HIGH);
     pulisciLCD();
   lettura="";
    stato=0;
    }break;

  case 4:
  {
    digitalWrite(ledPin, LOW);
     pulisciLCD();
   lettura="";
    stato=0;
    }break;

  case 5:
  {}break;

  case 6:
  {}break;

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

/*if(stato==0){
   key = keypad.getKey();
          if (key != NO_KEY){
                  if(key=='#'){
                        Serial.print("Lettura");
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
          }
} else if(stato==1){
              Serial.print("Stato dentro stato 1: ");
              Serial.println(stato);  
  
    Serial.println("caso1");
    Serial.println("cambio lo stato a 0");
    delay(2000);
    pulisciLCD();
    lettura="";
    stato=0;
} else if(stato==2){
  Serial.print("Stato dentro stato 2: ");
              Serial.println(stato);
              
   Serial.println("caso2");
   pulisciLCD();
   lettura="";
    stato=0;
} else{
  Serial.println("errore");
}*/

 



/*
switch(stato){
  case 0:
    {  
          key = keypad.getKey();
          if (key != NO_KEY){
          if(key=='#'){
            stato=gestisciInsert(lettura);
            Serial.print("Cambiato stato");
            }
          lcd.print("*");
          lettura+=key;
          
          //codice di controllo
          Serial.print("key: ");
          Serial.println(key);
          Serial.print("Stato: ");
          Serial.println(stato);     
          }
    }
    break;
 
  case 5:
    {
     Serial.println("Inizio case 1");
   lcd.setCursor(4, 1); 
    lcd.print("            ");
    delay(2000);
     lcd.setCursor(4, 1); 
    lcd.print(lettura);
     Serial.println("Fine case 1");
    }
   break;
  case 3:
    {
    Serial.println("dentro 3");
    delay(1000);
    stato=0;
    //if (Serial1.available() > 0) {//attende fino a che seriale non riceve qualcosa
    //char msg=Serial1.read();//mette la ricezione in un char
    //Serial.print(msg);//la tsampa
  //}
    }
  break;

  default: Serial.println("ERRORE");
    break;
}*/

 
}



