void finfIdUser(String username){
  int riga=0;
  String l_line = "";
  myFile = SD.open("utenti.txt");
  if (myFile) {
//open the file here
while (myFile.available() != 0) {  
    
    //A inconsistent line length may lead to heap memory fragmentation        
    l_line = myFile.readStringUntil('\n');  
    int trovPerc = l_line.indexOf('%'); 
    int PuntoVirgola = l_line.indexOf(';');
    String id=l_line.substring(0, PuntoVirgola);     
    l_line=l_line.substring(primoPuntoVirgola+1, trovPerc+1);
    trovPerc = l_line.indexOf('%'); 
    PuntoVirgola = l_line.indexOf(';');
    String username_locale=l_line.substring(0, PuntoVirgola);
    if(username == username_locale){
      return id;
      }else{
        return "-1";
        }
    l_line=l_line.substring(primoPuntoVirgola+1, trovPerc+1);
    trovPerc = l_line.indexOf('%'); 
    PuntoVirgola = l_line.indexOf(';');
    String password=l_line.substring(0, PuntoVirgola);
    
    //no blank lines are anticipated        
     return id;  
  }

void verificaUtente(String username)
 {
  int a = finfIdUser(username);
  if (a!="-1"){
    return "true";
  }
  else if(a=="-1"){
    return "false";
    }
  }
  }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening utenti.txt");
  }

    
    return id;
  }

  void registraUserPass (int id,String username,String password){
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("utenti.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to utenti.txt...");
    myFile.print(id);
    myFile.print(";");
    myFile.print(username);
    myFile.print(";");
    myFile.print(password);
    myFile.println(";");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void findCredenzialiUser(String username, String password){
  String l_line = "";
  myFile = SD.open("utenti.txt");
  if (myFile) {
//open the file here
while (myFile.available() != 0) {  
    
    //A inconsistent line length may lead to heap memory fragmentation        
    l_line = myFile.readStringUntil('\n');  
    int trovPerc = l_line.indexOf('%'); 
    int PuntoVirgola = l_line.indexOf(';');
    String id=l_line.substring(0, PuntoVirgola);     
    l_line=l_line.substring(primoPuntoVirgola+1, trovPerc+1);
    trovPerc = l_line.indexOf('%'); 
    PuntoVirgola = l_line.indexOf(';');
    String username_locale=l_line.substring(0, PuntoVirgola);
    l_line=l_line.substring(primoPuntoVirgola+1, trovPerc+1);
    trovPerc = l_line.indexOf('%'); 
    PuntoVirgola = l_line.indexOf(';');
    String password_locale=l_line.substring(0, PuntoVirgola);
    if (password == password_locale && username == username_locale){
      String login = "true";
      return login;
      }else{
        String login = "false";
        return login;
        }
          //no blank lines are anticipated        
     return id;  
  }
 
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening utenti.txt");
  }

    
    return id;
  }

  void setlog(int id,int giorno, int mese, int anno, int ora, int minuti, int secondi){
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open(giorno+"_"+mese+"_"+anno+".txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to"+myFile+".txt...");
    myFile.print(id);
    myFile.print(";");
    myFile.print(giorno);
    myFile.print(";");
    myFile.print(mese);
    myFile.print(";");
    myFile.print(anno);
    myFile.print(";");
    myFile.print(ora);
    myFile.print(";");
    myFile.print(minuti);
    myFile.print(";");
    myFile.print(secondi);
    myFile.println(";");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

 
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening utenti.txt");
  }
  }
void loop() {
  // put your main code here, to run repeatedly:

}
