#include <Keypad.h>
#include <LiquidCrystal.h>  

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

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
   lcd.begin(16, 2);  
   lcd.setCursor(0, 0); 
   lcd.print("Ins. codice...");
   lcd.setCursor(0, 1); 
   lcd.print("Ins:");
   lcd.setCursor(4, 1);    
}
  
void loop(){
  char key;

switch(stato){
  case 0:{
    //Serial.println("Inizio case 0");
    key = keypad.getKey();
    if (key != NO_KEY){
    if(key=='*'){
      stato=1;
      Serial.print("Cambiato stato");
      }
    lcd.print(key);
    lettura+=key;
    Serial.print("key: ");
    Serial.println(key);
    Serial.print("Stato: ");
    Serial.println(stato);
    }
    
     //Serial.println("Fine case 0");
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
  break;
}

 //Serial.println(stato);
}
