
void EEPROMWriteByte(int Adresse, byte Wert){
  EEPROM.write(Adresse, Wert);   
  EEPROM.commit();
}
void EEPROMWriteUInt(int Adresse, unsigned int  Wert){
  EEPROM.write(Adresse, Wert/256);     // Hi
  EEPROM.write(Adresse+1, Wert%256);   // Lo
  EEPROM.commit();
}
byte EEPROMReadByte(int Adresse){
  return EEPROM.read(Adresse);   
}
unsigned int EEPROMReadUInt(int Adresse){
  unsigned int Wert = 0;
  Wert = EEPROM.read(Adresse) * 256;     // Hi
  Wert+= EEPROM.read(Adresse+1);         // lo
  return Wert;   
}

void ReadConfigFromEEPROM(){
  InverterType =     EEPROMReadUInt(1); // EEPROM Adr 1+2 
  InverterZahl =     EEPROMReadUInt(3); // EEPROM Adr 3+4
  MaxWattInverter =  EEPROMReadUInt(5); // EEPROM Adr 5+6
  WattsCorr =        EEPROMReadUInt(7); // EEPROM Adr 7+8
  InverterInterval = EEPROMReadUInt(9); // EEPROM Adr 9+10
  InverterAdress =   EEPROMReadUInt(11);// EEPROM Adr 11+12
  MinNetInput =      EEPROMReadUInt(13);// EEPROM Adr 13+14    
  LastWechselDelay=  EEPROMReadUInt(15);// EEPROM Adr 15+16    
}

void WriteConfigToEEPROM(){
  // wenn keine Werte im EEPROM vorhanden sind, wird mit diesen Werten initialiert und gespeichert
  Serial.println("Konfiguration wird auf EEPRPOM geschrieben");
  EEPROMWriteByte( 0,EEPROM_ConfigMarker);// EEPROM Adr 0; 27 ist Marker, dass es schon eine Initialisierung des EEProm mit Werten gegeben hat   
  EEPROMWriteUInt( 1,InverterType);       // EEPROM Adr 1+2 
  EEPROMWriteUInt( 3,InverterZahl);       // EEPROM Adr 3+4
  EEPROMWriteUInt( 5,MaxWattInverter);    // EEPROM Adr 5+6
  EEPROMWriteUInt( 7,WattsCorr);          // EEPROM Adr 7+8
  EEPROMWriteUInt( 9,InverterInterval);   // EEPROM Adr 9+10
  EEPROMWriteUInt(11,InverterAdress);     // EEPROM Adr 11+12
  EEPROMWriteUInt(13,MinNetInput);        // EEPROM Adr 13+14 
  EEPROMWriteUInt(15,LastWechselDelay);   // EEPROM Adr 15+16 

}

bool islocalClient(){   // True, wenn IP locale Adresse, sonst falsde
  bool Loc =false;
  int i=ClientIP.toString().indexOf("192.168.");
  if(i==0) Loc=true;
  return Loc;
}


void S2C(String InStrg){  // Schreibt String Dateinamen in Array ChrDatName
  //InStrg+="\0";
  int ssid_len = InStrg.length() + 1;      
  InStrg.toCharArray(ChrDatName, ssid_len);  
}
