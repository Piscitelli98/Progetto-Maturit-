#include <Keypad.h>
#include <LiquidCrystal.h>  

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
//LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

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
  stato=0;
  Serial.begin(9600);
  Serial1.begin (9600);
   lcd.begin(16, 2);  
   lcd.setCursor(0, 0); 
   lcd.print("Ins. codice...");
   lcd.setCursor(0, 1); 
   lcd.print("Ins:");
   lcd.setCursor(4, 1);    
}


//----------
//Metodi

  //gestisce la lettura del tastierino elaborandola
 int gestisciInsert(String lettura){

  int valore=-1;
  //leggo il primo carattere per sapere se è una password di accesso o un comando
  String tp=lettura.substring(0,1);
  
  if(tp=='*'){//se il primo carattere è un *, allora è un comando
    /*switch(lettura){
      case "*3"{
        valore=-3;
      }
      break;
    }*/
    if(lettura="*3"){ valore=-3;}
    
  }//fine if controllo
  else{//se è una password controllo su database
    Serial.println("controllo psw");
    valore=1;
  }
  
  return valore;
 }

 
  //legge tastierino
 int leggiTastierino(){
    char key;
    int valore=-1;
    key = keypad.getKey();
    if (key != NO_KEY){
    if(key=='#'){
      valore=gestisciInsert(lettura);
      Serial.print("Cambiato stato");
      }
    lcd.print("*");
    lettura+=key;
    
    //codice di controllo
    Serial.print("key: ");
    Serial.println(key);
    Serial.print("Stato: ");
    Serial.println(stato);
    return valore;
    }
  }

//---------


  
void loop(){
  

switch(stato){
  case 0:{
    Serial.println("dentroTastierino");
    stato=leggiTastierino();
    Serial.println("fuoriTastierino");
    }
    break;
 
  case 1:{
     Serial.println("Inizio case 1");
   lcd.setCursor(4, 1); 
    lcd.print("            ");
    delay(2000);
     lcd.setCursor(4, 1); 
    lcd.print(lettura);
     Serial.println("Fine case 1");
  }
  case -3:{
     if (Serial1.available() > 0) {//attende fino a che seriale non riceve qualcosa
    char msg=Serial1.read();//mette la ricezione in un char
    Serial.print(msg);//la tsampa
  }
    }
  break;
}

 
}



