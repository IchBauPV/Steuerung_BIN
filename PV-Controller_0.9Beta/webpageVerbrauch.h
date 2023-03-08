void webpageVerbrauch(){

  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println();
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<meta http-equiv='refresh' content='5'>");
  client.println("<link rel=\"icon\" href=\"data:\">");
  
  client.print("<body><style type=text/css>.background {box-sizing: border-box; width: 380px; height: 750px; padding: 5px;");
  //client.print("background-image: url(https://www.elektrotechnik-matt.de/wp-content/uploads/2020/07/Photovoltaik-Anlage-3_370x450_web.jpg);");
  client.print("background-color:DarkBlue;"); 
  client.print("border: 4px solid black; background-size: 100% 100%; }");
  client.print("h1 {color: white; font-size: 2.2em; line-height: 0.0; margin-top: 1.0; margin-bottom: 0;} ");
  client.print("p {color: white; font-size: 1.1em; line-height: 1.0;  margin-top: 0;  margin-bottom: 0;}");
  client.print("h2 {color: white; font-size: 1.3em; line-height: 1.0; margin-top: 0; margin-bottom: 0;}  </style>");
  
  client.print("<div class=background> <h1 align=center>STROMVERBRAUCH</h1>");
  client.print("<table>");
  int InvPowerAnzeige;
  if(Batterie_empty) InvPowerAnzeige=0; else InvPowerAnzeige = InverterPowerOld;  //InverterPower; ggf (InverterPowerOld+InverterPower)/2 probieren, um besseren Match aus Einspeisungsvorgabe und aktuellem Netzbezug zu erreichen
  
  // *** Beginn Block aktuelle Werte ***
  DPRINT("Gesamtverbrauch :");
  DPRINTLN(String(NetPowerAct + InvPowerAnzeige));
  client.print("<tr><td><b><h2>AKTUELL: </td>");          
  //client.print("<tr><td><b><p>Gesamtverbrauch: </p></b></td>");
  client.print("<td align=right><b><p>" + String(NetPowerAct_Display + InvPowerAnzeige) + " W</h2></b></p></td></tr>");//eigentlich NetPowerAct, aber InverterPowerOld ergibt aufgrund der Regelverzögerung einen besseren Gesamtwert, der nicht so stark springt

  DPRINT("Netzbezug: ");
  DPRINTLN((NetPowerAct));
  client.print("<tr><td><p>Netzbezug: </p></td>");
  client.print("<td align=right><p>" + String(NetPowerAct_Display) + " W</p></td></tr>");

  DPRINT("Einspeisung:");
  DPRINTLN((InverterPower));
  client.print("<tr><td><p>Einspeisung: </p></td>");
  client.print("<td align=right><p>" +String(InvPowerAnzeige)+ " W</p></td></tr>");
  client.print("<tr><td><hr></td><td><hr></td></tr>"); // Absatz einfügeb

  DPRINT("Zaehlerstand:");
  DPRINTLN((ConsmptTot));
  client.print("<tr><td><p>Z&aumlhlerstand: </p></td><td align=right><p>");
  if(ConsmptTot >= 1000)    client.print(String(ConsmptTot / 1000) + ","); 
  if(ConsmptTot % 1000<100) client.print("0"); 
  if(ConsmptTot % 1000<10)  client.print("0"); 
  client.print(String(ConsmptTot % 1000) + " kWh</p></td></tr>");
  client.print("<tr><td><hr></td><td><hr></td></tr>"); // Absatz einfügen 
  //****** ENDE Block Aktuelle Werte *********

  // *** Beginn Block Heute ***
  long Ensp=(Einspeisung_day+_max(EinspeisungWattSek/(3600),0));
  client.print("<tr><td><b><h2>HEUTE GESAMT: </b></h2></td>");                    
  client.print("<td align=right><b><p>"+String(ConsmptTot-ConsmptTot_lastday+Ensp) +" Wh</p></b></td>");
  client.print("<tr><td><p>Netzbezug: </p></td>");
  client.println("<td align=right><p>" + String((ConsmptTot-ConsmptTot_lastday)) + "  Wh</p></td></tr>");

  DPRINT("Einspeisung Inverter :");
  DPRINTLN((InverterPower));
  client.print("<tr><td><p>Einspeisung: </p></td>");
  client.println("<td align=right><p>" +String(Ensp)+ "  Wh</p></td></tr>");
  client.print("<tr><td><hr></td><td><hr></td></tr>"); // Absatz einfügen
  // *** Ende Block Heute ***

  // *** Beginn Block Gestern *** 
//      if(Consmpt_lastday!=0) { // Werte vom Vortag liegen vor
  if(true) { // Werte vom Vortag liegen vor
    client.print("<tr><td><b><h2>GESTERN GESAMT: </b></h2></td>");          
    client.print("<td align=right><b><p>"+ String(Consmpt_lastday+Einspeisung_lastday) +" Wh</p></b></td>");
    client.print("<tr><td><p>Netzbezug: </p></td>");
    client.println("<td align=right><p>" + String(Consmpt_lastday) + " Wh</p></td></tr>");
    client.print("<tr><td><p>Einspeisung: </p></td>");
    client.println("<td align=right><p>" + String(Einspeisung_lastday) + " Wh</p></td></tr>");
    client.print("<tr><td><hr></td><td><hr></td></tr>"); // Absatz einfügeb
  }
  // *** Ende Block Gestern ***           
  
  client.println("<br><hr>  ");
  
  client.print("<tr><td><b><p>Batterie: </p></td><td align=right><b><p>");
  if(Batterie_empty) client.println("LEER</p></td></tr>"); else client.println("GELADEN</p></td></tr>");
  client.print("<tr><td><hr></td><td><hr></td></tr>"); // Absatz einfügen
  client.print("</b><hr><br>");
  client.print("</table>");
  //client.print("<br>");
  
  // Daten abrufen           
  client.print("<p>Daten abrufen</p>");          
  CP(" <form action=\"/get\" method =\"GET\">");
  //client.print("<form>"); 
  client.println("<button name=\"ShowDataPage\" value=1>Heute</button>");
  client.println("<button name=\"ShowDataPage\" value=2>Monat</button>");
  client.println("<button name=\"ShowDataPage\" value=3>Jahr</button>");
  client.println("<button name=\"ShowDataPage\" value=4>Vorjahr</button>");
  client.print("</form>");        
  client.print("<hr>");
  //client.println("<br><br>");     

  // Zeit und Datum ausgeben  
  client.print("<p>Uhrzeit: " + String(hour_) + ":");
  if (minute_ < 10) client.print("0");
  client.print(String(minute_) + ":");
  if (second_ < 10) client.print("0");
  client.print(String(second_));
  client.println("</p> ");
  client.println("<p>Datum : " + String(DatumString));
  client.println("</p><br> ");             //delay(100);
  client.println(Systemstartzeit);
  client.println("<br>Client IP:");
  client.println(client.remoteIP()); 
  if(islocalClient()) client.println(" lokale Adresse"); else client.println(" Internet-Adresse");  

  // Konfigurations Button
  if(islocalClient()){ 
    client.println("<br>");          
    client.print("<hr>");
//    client.print("<form>"); 
    CP(" <form action=\"/get\" method =\"GET\">");
    client.println("<button name=\"ConfigPage\" value=1>Konfiguration</button>");
    client.print("</form>");        
    client.print("<hr>");
  }
  
  client.println("</div></body></html>");
}
