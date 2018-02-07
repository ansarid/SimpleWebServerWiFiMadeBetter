#ifndef __CC3200R1M1RGC__
// Do not include SPI for CC3200 LaunchPad
#include <SPI.h>
#endif
#include <WiFi.h>
#include <Wire.h>
#include <BMA222.h>
#include <Adafruit_TMP006.h>

// your network name also called SSID
char ssid[] = "MyWiFiSSID";
// your network password
char password[] = "supersecretpassword";
// your network key Index number (needed only for WEP)
int keyIndex = 0;

WiFiServer server(80);

int RESET = 16;

int objt = 0;
int diet = 0;

int objt_css = 100;
int diet_css = 100;

//int data_x = 0;
//int data_y = 0;

int data_x_css = 0;
int data_y_css = 0;

char* thermometer_scale[] = {"#0000FF", "#1C00E2", "#3800C6", "#5500AA", "#71008D", "#8DOO71", "#AA0055", "#C60038", "#E2001C", "#FF0000"};

bool sensor_mode = FALSE;
bool LED_mode = FALSE;

int diet_thermometer_color = 0;
int objt_thermometer_color = 0;

const int button1 = PUSH1;
const int button2= PUSH2;

int button1State = 0;
int button2State = 0;

Adafruit_TMP006 tmp006(0x41);
BMA222 accelerometer;

void setup() {
  Serial.begin(115200);      // initialize serial communication

  pinMode(RESET, OUTPUT);
  digitalWrite(RESET, LOW);

  // The code causing the page to stop responding for some reason?
  Serial.println("Starting Adafruit TMP006.");
  tmp006.begin();  //  <--- More specifically this line!
  Serial.println("Done.");

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

  accelerometer.begin();
  uint8_t chipID = accelerometer.chipID();
  Serial.print("chipID: ");
  Serial.println(chipID);

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid);
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");

  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nIP Address obtained");

  // you're connected now, so print out the status
  printWifiStatus();

  Serial.println("Starting webserver on port 80");
  server.begin();                           // start the web server on port 80
  Serial.println("Webserver started!");
}

void loop() {
  int i = 0;
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    char buffer[150] = {0};                 // make a buffer to hold incoming data
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (strlen(buffer) == 0) {

//            if (sensor_mode == TRUE) {

              //Get data from temp and accelerometer

              button1State = digitalRead(button1);
              button2State = digitalRead(button2);
              
              float objt = tmp006.readObjTempC();
              float diet = tmp006.readDieTempC();
              
              float objt_css = objt * 2;
              float diet_css = diet * 2;
              
              int8_t data_x = accelerometer.readXData();
              int8_t data_y = accelerometer.readYData();
              
              data_x_css = (data_x + 60) * 2;
              data_y_css = (243 - ((data_y + 60) * 2)) - 135;

              if (objt < 0) {
                objt = 0;
              }
              else if (objt > 200) {
                objt = 200;
              }

              if (diet < 0) {
                diet = 0;
              }
              else if (diet > 200) {
                diet = 200;
              }

              if (objt <= 10) {
                objt_thermometer_color = 0;
              }
              else if (objt <= 20 && objt > 10) {
                objt_thermometer_color = 1;
              }
              else if (objt <= 30 && objt > 20) {
                objt_thermometer_color = 2;
              }
              else if (objt <= 40 && objt > 30) {
                objt_thermometer_color = 3;
              }
              else if (objt <= 50 && objt > 40) {
                objt_thermometer_color = 4;
              }
              else if (objt <= 60 && objt > 50) {
                objt_thermometer_color = 5;
              }
              else if (objt <= 70 && objt > 60) {
                objt_thermometer_color = 6;
              }
              else if (objt <= 80 && objt > 70) {
                objt_thermometer_color = 7;
              }
              else if (objt <= 90 && objt > 80) {
                objt_thermometer_color = 8;
              }
              else if (objt <= 100 && objt > 90) {
                objt_thermometer_color = 9;
              }
              else if (objt < 100) {
                objt_thermometer_color = 9;
              }


              if (diet <= 10) {
                diet_thermometer_color = 0;
              }
              else if (diet <= 20 && diet > 10) {
                diet_thermometer_color = 1;
              }
              else if (diet <= 30 && diet > 20) {
                diet_thermometer_color = 2;
              }
              else if (diet <= 40 && diet > 30) {
                diet_thermometer_color = 3;
              }
              else if (diet <= 50 && diet > 40) {
                diet_thermometer_color = 4;
              }
              else if (diet <= 60 && diet > 50) {
                diet_thermometer_color = 5;
              }
              else if (diet <= 70 && diet > 60) {
                diet_thermometer_color = 6;
              }
              else if (diet <= 80 && diet > 70) {
                diet_thermometer_color = 7;
              }
              else if (diet <= 90 && diet > 80) {
                diet_thermometer_color = 8;
              }
              else if (diet <= 100 && diet > 90) {
                diet_thermometer_color = 9;
              }
              else if (diet < 100) {
                diet_thermometer_color = 9;
              }

//            }



            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("");

            // the content of the HTTP response follows the header

            client.println("");
            client.println("<html>");
            client.println("    <head>");
            client.println("        <meta http-equiv=\"refresh\" content=\"2\">");
            client.println("        <title>Energia CC3200 WiFi Web Server but Better</title>");
            client.println("        <style>");
            client.println("            table {");
            client.println("                width: 275px;");
            client.println("                margin-top: 20px;");
            client.println("                margin-left: auto;");
            client.println("                margin-right: auto;");
            client.println("            }");
            client.println("            .sensors {");
            client.println("                width: 900px;");
            client.println("                height: 300px;");
            client.println("                margin-left: auto;");
            client.println("                margin-right: auto;");
            client.println("            }");
            client.println("            .graph {");
            client.println("                height: 261px;");
            client.println("                width: 261px;");
            client.println("                float: left;");
            client.println("                margin-left: 200px;");
            client.println("                margin-right: auto;");
            client.println("                max-height: 261px;");
            client.println("                max-width: 261px;");
            client.println("                display: inline-block;");
            client.println("                background-size: 10px 10px;");
            client.println("                background-image: linear-gradient(to right, lightgrey 1px, transparent 1px), linear-gradient(to bottom, lightgrey 1px, transparent 1px);");
            client.println("            }");
            client.println("            .point {");
            client.println("                width:10px;");
            client.println("                height: 10px;");
            client.print("                margin-left: ");
            client.print(data_x_css);
            client.println("px;");
            client.print("                margin-top: ");
            client.print(data_y_css);
            client.println("px;");
            client.println("                border-radius: 100%;");
            client.println("                background-color: #ffd335;");
            client.println("                border-color: black;");
            client.println("                border-width: 1px;");
            client.println("                border-style: solid;");
            client.println("            }");
            client.println("            .point_home {");
            client.println("                width:10px;");
            client.println("                height: 10px;");
            client.println("               margin-top: -136px;");
            client.println("               margin-left: 125px;");
            client.println("                border-radius: 100%;");
            client.println("                border-color: black;");
            client.println("                border-width: 1px;");
            client.println("                border-style: solid;");
            client.println("            }");
            client.println("          .point-bounds {");
            client.println("              height: 259px;");
            client.println("              width: 259px;");
            client.println("              margin-top: -261px;");
            client.println("              border-color: grey;");
            client.println("              border-style: dashed;");
            client.println("              border-width: 1px;");
            client.println("              border-radius: 100%;");
            client.println("           }");
            client.println("          .x-axis {");
            client.println("              height: 2px;");
            client.println("              width: 261px;");
            client.println("              margin-top: 130px;");
            client.println("              background-color: black;");
            client.println("           }");
            client.println("          .y-axis {");
            client.println("              height: 261px;");
            client.println("              width: 2px;");
            client.println("              margin-left: 130px;");
            client.println("               margin-top: -132px;");
            client.println("              background-color: black;");
            client.println("            }");
            client.println("            .thermometer{");
            client.println("                height: 232px;");
            client.println("                width: 44px;");
            client.println("                float: left;");
            client.println("                margin-left: 200px;");
            client.println("                margin-top: 30px;");
            client.println("                margin-left: 50px;");
            client.println("                margin-right: 50px;");
            client.println("                position: relative;");
            client.println("                display: inline-block;");
            client.println("            }");
            client.println("            .label{");
            client.println("                width: 80px;");
            client.println("                height: 10px;");
            client.println("                margin-top: -40px;");
            client.println("                margin-left: -20px;");
            client.println("             }");
            client.println("            .name_label{");
            client.println("                margin-top: 250px;");
            client.println("             }");
            client.println("            .column-obj{");
            client.print("                height:");
            client.print(objt_css);
            client.println("px;");
            client.println("                width: 20px;");
            client.println("                bottom: 20px;");
            client.println("                position: absolute;");
            client.print("                background-color: ");
            client.print(thermometer_scale[objt_thermometer_color]);
            client.println(";");
            client.println("            }");
            client.println("            .column-die{");
            client.print("                height:");
            client.print(diet_css);
            client.println("px;");
            client.println("                width: 20px;");
            client.println("                bottom: 20px;");
            client.println("                position: absolute;");
            client.print("                background-color: ");
            client.print(thermometer_scale[diet_thermometer_color]);
            client.println(";");
            client.println("            }");
            client.println("            .tube{");
            client.println("                height: 200px;");
            client.println("                width: 20px;");
            client.println("                margin: 0 auto;");
            client.println("                margin-top: -190px;");
            client.println("                background-color: LightCyan;");
            client.println("                border-width: 1px;");
            client.println("                border-color: black;");
            client.println("                border-radius: 20px;");
            client.println("                border-style: solid;");
            client.println("                margin-bottom: 90px;");
            client.println("            }");
            client.println("            .bulb-die{");
            client.println("                height: 40px;");
            client.println("                width: 40px;");
            client.println("                bottom:0px;");
            client.println("                position: absolute;");
            client.println("                margin: 0 auto;");
            client.println("                border-width: 1px;");
            client.println("                border-color: black;");
            client.println("                border-radius: 50%;");
            client.println("                border-style: solid;");
            client.println("            }");
            client.println("            .bulb-obj{");
            client.println("                height: 40px;");
            client.println("                width: 40px;");
            client.println("                bottom:0px;");
            client.println("                position: absolute;");
            client.println("                margin: 0 auto;");
            client.println("                border-width: 1px;");
            client.println("                border-color: black;");
            client.println("                border-radius: 50%;");
            client.println("                border-style: solid;");
            client.println("            }");
            client.println("            .bulb-color-obj{");
            client.println("                height:40px;");
            client.println("                width: 40px;");
            client.println("                position: absolute;");
            client.print("                background-color: ");
            client.print(thermometer_scale[objt_thermometer_color]);
            client.println(";");
            client.println("                border-radius: 50%;");
            client.println("                margin: 0 auto;");
            client.println("            }");
            client.println("            .bulb-color-die{");
            client.println("                height:40px;");
            client.println("                width: 40px;");
            client.println("                position: absolute;");
            client.print("                background-color: ");
            client.print(thermometer_scale[diet_thermometer_color]);
            client.println(";");
            client.println("                border-radius: 50%;");
            client.println("                margin: 0 auto;");
            client.println("            }");
/*

            if(button1State == HIGH){
              client.println("<p>ON</p>");
            }
            else if (button1State == LOW){
              client.println("<p>OFF</p>");              
            }
              client.println("");

            client.println("Button 2 (SW2) Mode:");
            
            if(button2State == HIGH){
              client.println("<p>ON</p>");
            }
            else if (button2State == LOW){
              client.println("<p>OFF</p>");
            }

*/
 
            client.println("            .buttons {");
            client.println("              height: 100%;");
            client.println("              width: 350px;");
            client.println("              margin-left: -300px;");
            client.println("              margin-right: auto;");
            client.println("              margin: auto;");
            client.println("                background-color: green;");
            client.println("            }");
            
            client.println("            .button1 {");
            client.println("              height: 60px;");
            client.println("              width: 60px;");
            client.println("              margin-top: 30px;");
            client.println("              display: inline-block;");
            client.println("              border-radius: 50%;");
            client.print("              background-color: ");
            
            if(button1State == HIGH){
              client.print("red");
            }

            else if (button1State == LOW){
              client.print("#b7b7b7");              
            }
            
            client.println(";");
            client.println("              float: left;");
            client.println("            }");
            client.println("            .button2 {");
            client.println("              height: 60px;");
            client.println("              width: 60px;");
            client.println("              margin-top: 30px;");
            client.println("              display: inline-block;");
            client.println("              border-radius: 50%;");
            client.print("              background-color:");

            if(button2State == HIGH){
              client.print("red");
            }

            else if (button2State == LOW){
              client.print("#b7b7b7");              
            }
            
            client.println(";");
            client.println("              float: right;");
            client.println("            }");
            client.println("            .button1_inner {");
            client.println("              height: 45px;");
            client.println("              width: 45px;");
            client.println("              margin-top: 7px;");
            client.println("              margin-right: 8px;");
            client.println("              display: inline-block;");
            client.println("              border-radius: 50%;");
            client.print("              background-color:");

            if(button1State == HIGH){
              client.print("#f47741");
            }

            else if (button1State == LOW){
              client.print("lightgrey");              
            }
            
            client.println(";");
            client.println("              float: right;");
            client.println("            }");
            client.println("            .button2_inner {");
            client.println("              height: 45px;");
            client.println("              width: 45px;");
            client.println("              margin-top: 7px;");
            client.println("              margin-right: 8px;");
            client.println("              display: inline-block;");
            client.println("              border-radius: 50%;");
            client.print("              background-color:");

            if(button2State == HIGH){
              client.print("#f47741");
            }

            else if (button2State == LOW){
              client.print("lightgrey");              
            }
            
            client.println(";");
            client.println("              float: right;");
            client.println("            }");
            client.println("            .button_label {");
            client.println("              height: 60px;");
            client.println("              width: 100px;");
            client.println("              margin-top: 15px;");
            client.println("              margin-right: -20px;");
            client.println("              display: inline-block;");
            client.println("              float: right;");
            client.println("            }");
            client.println("            .reset_button {");
            client.println("              height: 60px;");
            client.println("              width: 60px;");
            client.println("              color: white;");
            client.println("              font-weight: bold;");
            client.println("              background-color: red;");
            client.println("              border-radius: 100%;");
            client.println("            }");
            client.println("            </style>");
            client.println("    </head>");
            client.println("    <body align=center>");
            client.println("        <h1 align=center>");
            client.println("            <font color=\"red\">Welcome to the CC3200 WiFi Web Server Made Like Wayyyyy Better</font>");
            client.println("        </h1>");
            client.println("            Mode: <button onclick=\"location.href='/LEDS'\">");
            client.println("                LED");
            client.println("            </button>");
            client.println("            <button onclick=\"location.href='/SENSORS'\">");
            client.println("                Sensor");
            client.println("            </button>");
            client.println("        <table>");
            client.println("          <tr>");
            client.println("            <td>RED LED (D7)</td>");
            client.println("            <td><button onclick=\"location.href='/LED/RH'\">HIGH</button></td>");
            client.println("            <td>");
            client.println("            <button onclick=\"location.href='/LED/RH'\">LOW</button></td>");
            client.println("          </tr>");
            client.println("  <tr>");
            client.println("    <td>YELLOW LED (D6)</td>");
            client.println("    <td><button onclick=\"location.href='/LED/YH'\">HIGH</button></td>");
            client.println("  <td>");
            client.println("  <button onclick=\"location.href='/LED/YH'\">LOW</button></td>");
            client.println("  </tr>");
            client.println("  <tr>");
            client.println("    <td>GREEN LED (D5)</td>");
            client.println("    <td><button onclick=\"location.href='/LED/GH'\">HIGH</button></td>");
            client.println("  <td>");
            client.println("  <button onclick=\"location.href='/LED/GH'\">LOW</button></td>");
            client.println("  </tr>");
            client.println("</table>");
            client.println("        <br>");
            client.println("        <div class=\"sensors\">");
            client.println("            <div class=\"graph\">");
            client.println("                <div class=\"x-axis\"></div>");
            client.println("                <div class=\"y-axis\"></div>");
            client.println("                <div class=\"point-bounds\"></div>");
            client.println("                <div class=\"point_home\"></div>");
            client.println("                <div class=\"point\"></div>");
            client.println("            </div>");
            client.println("            <div class=\"thermometer\">");
            client.println("              <div class=\"label\"><p>");
            client.println(objt);
            client.println(" *C</p></div>");
            client.println("                <div class=\"bulb-obj\">");
            client.println("                    <div class=\"bulb-color-obj\"></div>");
            client.println("                    <div class=\"tube\">");
            client.println("                        <div class=\"column-obj\"></div>");
            client.println("                    </div>");
            client.println("                </div>");
            client.println("              <div class=\"name_label\">Object</div>");
            client.println("            </div>");
            client.println("            <div class=\"thermometer\">");
            client.println("              <div class=\"label\"><p>");
            client.println(diet) ;
            client.println(" *C</p></div>");
            client.println("                <div class=\"bulb-die\">");
            client.println("                    <div class=\"bulb-color-die\"></div>");
            client.println("                    <div class=\"tube\">");
            client.println("                        <div class=\"column-die\"></div>");
            client.println("                    </div>");
            client.println("                </div>");
            client.println("              <div class=\"name_label\">Die</div>");

/*

            client.println("              <div class=\"buttons\">");
            client.println("                <div class=\"button1\">");
            client.println("                  <div class=\"button1_inner\"></div>");
            client.println("                    <div class=\"button_label\">");
            client.println("                      PUSH2 (SW2)");
            client.println("                    </div>");
            client.println("                  </div>");
            client.println("                  <div class=\"button2\">");
            client.println("                    <div class=\"button2_inner\"></div>");
            client.println("                      <div class=\"button_label\">");
            client.println("                        PUSH3 (SW3)");
            client.println("                      </div>");
            client.println("                    </div>");
            client.println("                  </div>");
            client.println("                </div>");
            client.println("              </div>");
*/

/*
            client.println("Button1 Mode:");
            
            if(button1 == HIGH){
              client.println("ON");
            }
            else if (button1 == LOW){
              client.println("OFF");              
            }
              client.println("");

            client.println("Button2 Mode:");
            
            if(button2 == HIGH){
              client.println("ON");
            }
            else if (button2 == LOW){
              client.println("OFF");
            }
            client.println("        </div>");
            client.println("<button class=\"reset_button\" onclick=\"location.href='/RESET'\">RESET</button>");
*/
            client.println("    </body>");
            client.println("</html>");
            
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear the buffer:
            memset(buffer, 0, 150);
            i = 0;
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          buffer[i++] = c;      // add it to the end of the currentLine
        }

        if (endsWith(buffer, "GET /LEDS")) {

          sensor_mode = FALSE;
          LED_mode = TRUE;
          
//          pinMode(RED_LED, OUTPUT);
//          pinMode(GREEN_LED, OUTPUT);
//          pinMode(YELLOW_LED, OUTPUT);

//          digitalWrite(RED_LED, LOW);
//          digitalWrite(YELLOW_LED, LOW);
//          digitalWrite(GREEN_LED, LOW);

        }

        if (endsWith(buffer, "GET /SENSORS")) {

          sensor_mode = TRUE;
          LED_mode = FALSE;
//          digitalWrite(RESET, HIGH);

        }

        if (endsWith(buffer, "GET /RESET")) {

          //RESET

        }

        else if (endsWith(buffer, "GET /LED/RH")) {
          digitalWrite(RED_LED, HIGH);
          Serial.println("RED_LED ON");
        }

        else if (endsWith(buffer, "GET /LED/RL")) {
          digitalWrite(RED_LED, LOW);
          Serial.println("RED_LED OFF");
        }

        else if (endsWith(buffer, "GET /LED/YH")) {
          digitalWrite(YELLOW_LED, HIGH);
          Serial.println("YELLOW_LED ON");
        }

        else if (endsWith(buffer, "GET /LED/YL")) {
          digitalWrite(YELLOW_LED, LOW);
          Serial.println("YELLOW_LED OFF");
        }

        else if (endsWith(buffer, "GET /LED/GH")) {
          digitalWrite(GREEN_LED, HIGH);
          Serial.println("GREEN_LED ON");
        }

        else if (endsWith(buffer, "GET /LED/GL")) {
          digitalWrite(GREEN_LED, LOW);
          Serial.println("GREEN_LED OFF");
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}


// a way to check if one array ends with another array

boolean endsWith(char* inString, char* compString) {
  int compLength = strlen(compString);
  int strLength = strlen(inString);

  //compare the last "compLength" values of the inString
  int i;
  for (i = 0; i < compLength; i++) {
    char a = inString[(strLength - 1) - i];
    char b = compString[(compLength - 1) - i];
    if (a != b) {
      return false;
    }
  }
  return true;
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
