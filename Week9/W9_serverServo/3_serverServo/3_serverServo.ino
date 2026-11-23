/*
  DM3014 Interactive Devices, Teh Wern Jenn
  Week 9 - Remote Interfaces
  ESP32-C3 Server Servo Control
  Move a 180° servo motor over web server.
  Additional Components: Servo Motor

  Comments:
  Editing design elements of the screen and creating a more fun design to interact with.
  (note for myself) to access web page IP adress to be found in Serial monitor

  Edits:
  - Changed wifi name and password to my name so that can recognise the ESP32
  - Editted Head title and angle description title, of page to make it more fun!
  - Changed the colour of the buttons and size bigger and giving it a border
  - Adding gradient background (shown in video but is closed in this code)
  - Created colour change when pressing button on screen.
  - Adding addtional angles in between 0,90,180. 
  - add more angles by copying a line and changing both numbers of the servo and the button ,  servo to tell the motor to turn to that angle, button is what the vieer sees 


*/

// ====== Reference Libraries ======
#include <WiFi.h>
#include <ESP32Servo.h>

// ====== Network Credentials ======
const char* ssid     = "ESP32-Access-Jenn"; // edited my ESP32 name here
const char* password = "87654321";         // created a password

// ====== Network Settings ======
WiFiServer server(80);
String header;        // variable stores HTTP request
int servo_angle = 90; // variable stores current servo angle (0-180)

// ====== Assign Servo Pin ======
#define SERVO_PIN 7
Servo myServo;

// //====== Webpage ====== 
//*** edit the page here, written exactly like a normal HTML file
// %ANGLE% is a placeholder: it gets swapped for the current servo angle,
// <h1>ESP32 Web Server</h1>  //can change servo angle but need to keep %ANGLE%&deg
// <p>Servo Angle - %ANGLE%&deg;</p>   // changed label

   
const char webpage[] = R"HTML(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html { font-family: Trebuchet MS; text-align: center; } /*search online html font family ot find other fonts than, Helvetica is the previous font*/
    .button { /*Changed the colours and added borders to make the button different, did use Ai to help guide how to make a class in html code for the button*/
      background-color: #e3f4ff; 
      color: Black;
      border: 2px solid #057df5;
      border-radius: 800px;
      padding: 16px 40px;
      font-size: 20px;
      margin: 2px 20px; /*changing the margin so that the angle buttons stack*/
      cursor: pointer;
    }
    .button:hover {
  background-color: #fffd70;
  }
  body { /*with some guidance of ai to figure out what specific code i need to create gradients*/
  min-height: 100vh;
  margin: 0;
  background: linear-gradient(135deg, #e3f4ff, #c2e9fb, #a1c4fd); //added gradient to the bg
}
  </style>
</head>
<body>

   <h1>Control the Hand! :)</h1>  

   <p> ~ Angle of Hand ~ - %ANGLE%&deg;</p>   
 
  <!-- Added a variety of angles to explore  --> 
  <p>
    <a href="/servo/ 0 "><button class="button">0&deg;</button></a>
    <a href="/servo/ 20 "><button class="button">20&deg;</button></a>
    <a href="/servo/ 50 "><button class="button">50&deg;</button></a>
    <a href="/servo/ 90 "><button class="button">90&deg;</button></a>
    <a href="/servo/ 150 "><button class="button">150&deg;</button></a>
    <a href="/servo/ 180 "><button class="button">180&deg;</button></a>
  </p>
</body>
</html>
)HTML";

void setup() {
  // ====== Setup Serial Monitor ======
  Serial.begin(115200);

  // ====== Setup Servo ======
  myServo.setPeriodHertz(50);           // standard servos expect 50 Hz
  myServo.attach(SERVO_PIN, 500, 2400); // pulse width range in microseconds
  myServo.write(servo_angle);           // move to start position

  // ====== Setup ESP as Access Point ======
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("IP Address: ");
  Serial.println(IP);
  server.begin();
}

void loop(){
  WiFiClient client = server.available(); // listen for incoming clients
  if (client) {                           // if a new client connects
    Serial.println("New Client");   
    String currentLine = "";
    unsigned long startTime = millis();   // note when client connected (for timeout)
    while (client.connected() && millis() - startTime < 2000) { // set a 2s timeout
      if (client.available()) {           // if there's bytes to read from the client
        char c = client.read();           // read a byte
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            // ====== Setup Webpage ======
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // ====== Move Servo ======
            int pos = header.indexOf("GET /servo/");
            if (pos >= 0) {
              servo_angle = constrain(header.substring(pos + 11).toInt(), 0, 180); // read the number after /servo/
              Serial.println("servo to " + String(servo_angle));
              myServo.write(servo_angle);
            } 
            
            // ====== Display HTML Webpage ======
            String page = webpage;                        // copy webpage from top of the sketch
            page.replace("%ANGLE%", String(servo_angle)); // fill in the current angle
            client.print(page);                           // send it to the browser
            client.println();                             // HTTP response ends with another blank line
            break;                                        // break out of the while loop
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";   // clear the header variable
    client.stop(); // close the connection
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}