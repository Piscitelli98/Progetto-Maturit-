#include <LiquidCrystal.h>
#include <Keyboard.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int contrastPin = 9;

int conta=0;
char myInts[5];
char psw[] = {'2', '4', '8', '3', '6'};


void setup() {
  pinMode(contrastPin, OUTPUT);
  analogWrite(contrastPin, 88);

  lcd.begin(16, 2);
  lcd.println("Pronto");
  delay(5000);
  lcd.clear();
  Serial.begin(9600);
}

void loop() {

  while (Serial.available() > 0) {
    do{
    char inChar =  Serial.read();
    lcd.print(inChar);
    myInts[conta]=inChar;
    conta++;
    Serial.print(inChar + " " + conta);
    }while(conta>6);


if(myInts[0]==psw[0])
  lcd.print("corretto");
 else
  lcd.print("errato");

    
   /* if (inChar == '7') {
      lcd.clear();
      lcd.print("Ciao Pin 7");
      delay(2000);
    }
    
    if (inChar == '8') {
      lcd.clear();
      lcd.print("Ciao Pin 8");
      delay(2000);
    }*/
  }

}



