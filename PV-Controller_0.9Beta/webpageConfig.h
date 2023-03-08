void webPageConfig() { 
  String cStr[4];cStr[1]=" ";cStr[2]=" ";cStr[3]=" "; // Platzhalter für Radiobutton Checked String
  cStr[InverterType]=" checked";
  //Serial.println("Webseite ausgeben");
  CP("HTTP/1.1 200 OK");
  CP("Content-type:text/html");
  CP("Connection: close");
  CPL();
  // Hier wird nun die HTML Seite angezeigt:
  CP("<!DOCTYPE html><html>");
  CP("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  CP("<link rel=\"icon\" href=\"data:\">");
  
  CP("<body> <h1>Konfiguration</h1> ");
  CP("<p><b> Inverter Typ:</b></p>");
  CP(" <form action=\"/get\" method =\"GET\">");
  CP("<p> <label><input type=radio id=Inv1 name=InvType value=1 " + cStr[1]+ "> Soyosource GTN 1000/1200</label></p>");
  /* CP("<p> <label><input type=radio id=Inv2 name=InvType value=2 " + cStr[2]+ "> GoodWe 3048/5048D - ES</label> </p>");
  CP("<p> <label><input type=radio id=Inv3 name=InvType value=3 " + cStr[3]+ "> Growatt SPH </label>");
  */
  CP(" <p><label><b>Inverter Adresse:&nbsp</b><input type=text id=input0 name=Adress style='width:40px; text-align:right' value=" +String(InverterAdress)+"> dezimal</p></label>");
  CP(" <p><label><b>Anzahl Inverter: &nbsp</b><input type=text id=input1 name=InverterZahl style='width:40px;text-align:right'; value=" +String(InverterZahl)+"></P></label>");
  CP(" <p><label><b>Gesamtleistung: &nbsp&nbsp</b><input type=text id=input2 name=InverterLeistung style='width:40px; text-align:right'; value=" +String(MaxWattInverter)+"> Watt maximal</p></label>");
  CP(" <p><label><b>Ansteuerung mit:&nbsp</b><input type=text id=input3 name=InverterFaktor style='width:40px; text-align:right'; value=" +String(WattsCorr)+"> &#8240 </p></label>");
  CP(" <p><label><b>Ansteuerung alle: </b><input type=text id=input4 name=SendInterval style='width:40px; text-align:right' value=" +String(InverterInterval)+"> msec</p></label>");
  CP(" <p><label><b>Verz&oumlgerg. Lastw.: </b><input type=text id=input5 name=LastWechselDelay style='width:40px; text-align:right' value=" +String(LastWechselDelay)+"> msec/kW</p></label>");
  CP(" <p><label><b>Regelung auf:&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp</b><input type=text id=input5 name=MinWert style='width:40px; text-align:right' value=" +String(MinNetInput)+"> Watt Netzbezug</p></label>");
  CP(" &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp<input type=submit value=\"Speichern\"style='width:150px; text-align:center'>");

  CP("</form>  </body>  </html>");
  }
