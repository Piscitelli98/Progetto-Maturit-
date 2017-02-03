#include <LiquidCrystal.h>  
#include <DS3232RTC.h>    
#include <TimeLib.h>         
#include <Wire.h>      
      
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

//pin per mottore StepToStep
int Pin1n1=6, Pin1n2=7, Pin1n3=8, Pin1n4=9;
  
void setup() {  
   //impostiamo il numero di colonne ed il numero di righe di lcd  

  lcd.begin(16, 2);  
  // Visualizzo il messaggio sul display  
   Serial.begin(9600);
    setSyncProvider(RTC.get);   // the function to get the time from the RTC
    if(timeStatus() != timeSet) 
        Serial.println("Unable to sync with the RTC");
    else
        Serial.println("RTC has set the system time"); 
  lcd.print("Salve mondo!");  

    //configurati come uscite
  pinMode(Pin1n1, OUTPUT);
  pinMode(Pin1n2, OUTPUT);
  pinMode(Pin1n3, OUTPUT);
  pinMode(Pin1n4, OUTPUT);
 
  //forzo le uscite a livello logico basso
  digitalWrite(Pin1n1, LOW);
  digitalWrite(Pin1n2, LOW);
  digitalWrite(Pin1n3, LOW);
  digitalWrite(Pin1n4, LOW);
}  
  
void loop() {  
  // posiziona il cursore in colonna 0 e linea 1  
  // (nota: la linea 1 e la seconda linea, poichè si conta incominciando da 0):  
  lcd.setCursor(0, 1);  
  // stampa il numero di secondi dall'ultimo reset  
  digitalClockDisplay();  
    delay(1000); 
}  
void digitalClockDisplay(void)
{
    // digital clock display of the time
    lcd.print(hour());
    printDigits(minute());
    printDigits(second());
    lcd.print(' ');
    lcd.print(day());
    lcd.print(' ');
    lcd.print(month());
    lcd.print(' ');
    lcd.print(year()); 
    lcd.println(); 

    

   
    
}

void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    lcd.print(':');
    if(digits < 10)
        lcd.print('0');
    lcd.print(digits);
}

//per motore step to step
void  fase1(){
   //FASE 1
    //Alimento solo la prima bobina
    digitalWrite(Pin1n1, HIGH);
    digitalWrite(Pin1n2, LOW);
    digitalWrite(Pin1n3, LOW);
    digitalWrite(Pin1n4, LOW);
    delay(10);
  }
  
 void fase2(){
  //FASE 2
    //Alimento solo la seconda bobina
    digitalWrite(Pin1n1, LOW);
    digitalWrite(Pin1n2, HIGH);
    digitalWrite(Pin1n3, LOW);
    digitalWrite(Pin1n4, LOW);
    delay(10);
  }
  
void  fase3(){
  //FASE 3
    //Alimento solo la terza bobina
    digitalWrite(Pin1n1, LOW);
    digitalWrite(Pin1n2, LOW);
    digitalWrite(Pin1n3, HIGH);
    digitalWrite(Pin1n4, LOW);
    delay(10);
  }
  
void  fase4(){
  //fase 4
    //Alimento solo la quarta bobina
    digitalWrite(Pin1n1, LOW);
    digitalWrite(Pin1n2, LOW);
    digitalWrite(Pin1n3, LOW);
    digitalWrite(Pin1n4, HIGH);
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
void apri(int attendi){
  //setto i secondi di adesso
  
    int sec=second();
    int attesa=attendi;
    do{
     Serial.println("Dentro primo ciclo");
    avanti();
      
    }while(second()<(sec+attesa));//aspetto fino a che i secondi di adesso non sono aumentati di 20 secondi
}
void chiudi(int attendi){
  
    int sec=second();
    int attesa=attendi;
    do{
        Serial.println("Dentro secondo ciclo");
    indietro();
      
    }while(second()<(sec+attesa));
}
}

