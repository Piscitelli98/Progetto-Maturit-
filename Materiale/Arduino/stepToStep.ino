void setup()
{
  //i pin 2-3-4-5 sono collegati a 1n1, 2n2, 3n3, 4n4
  //configurati come uscite
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
 
  //forzo le uscite a livello logico basso
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}
 
void loop()
{
 
 indietro();
}

void  fase1(){
   //FASE 1
    //Alimento solo la prima bobina
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(10);
  }
  
 void fase2(){
  //FASE 2
    //Alimento solo la seconda bobina
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(10);
  }
  
void  fase3(){
  //FASE 3
    //Alimento solo la terza bobina
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    delay(10);
  }
  
void  fase4(){
  //fase 4
    //Alimento solo la quarta bobina
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
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


