#include <LiquidCrystal.h>  
#include <DS3232RTC.h>    
#include <TimeLib.h>         
#include <Wire.h>      
      
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  
  
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
