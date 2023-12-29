#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <FirebaseESP8266.h>

// Firebase information
#define FIREBASE_HOST "smart-cold-storage-cbae1-default-rtdb.firebaseio.com" 
#define FIREBASE_AUTH "PsU83cA4O1nCHoIyxDEm7cSL2srracmtdTV8wx7O"
//----------------------------------------

// Declare the Firebase Data object in the global scope
FirebaseData firebaseData;
//----------------------------------------

// Necessary variables
// Recieved data from Arduino
char data;
String message="";
// Sensor values
String temperature, humidity, lpg, co2;
// separation index
int tempIndex, huIndex, lpgIndex, coIndex;
//----------------------------------------


// WiFi info
const char* ssid = "Notification";
const char* password = "sabbir62";
//----------------------------------------

//Host & httpsPort
const char* host = "script.google.com";
const int httpsPort = 443;
//----------------------------------------

//Create a WiFiClientSecure object.
WiFiClientSecure client;
//----------------------------------------

//Spread Sheet script ID
String GAS_ID = "AKfycbx1CQeMj8yysapJGdHysMWTijnYt7jSYtfebm8FuWukLozM0PQ7GD0B9GHQwa5jVYh8UA";
//----------------------------------------

//--------------------------------------------------------------Set up-----------------------------------------------------------------//
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Connect to your WiFi router
  WiFi.begin(ssid, password);
    
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting");
    delay(1000);
  }
  //----------------------------------------

  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------

  // connect to firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  client.setInsecure();
  //----------------------------------------
  
}

//-------------------------------------------------------------- Loop -----------------------------------------------------------------//

void loop() {
  Serial.println("Tried");
  while(Serial.available() > 0) {
    data = Serial.read();
    
    if(data == 'C') {
      message += data;
      break;
    }
    else {
      message += data;
    }
  }
  Serial.println(message);

  if(data == 'C') {
    parse_data();
    if(Firebase.setString(firebaseData, "/temperature", temperature) && Firebase.setString(firebaseData, "/humidity", humidity) && Firebase.setString(firebaseData, "/lpg", lpg) && Firebase.setString(firebaseData, "/co2", co2)) {
      Serial.println("Value Uploaded Successfully");
    }
    else {
      Serial.print("Wrong data");
      Serial.println(firebaseData.errorReason());
    }
  }
  
  // Calls the sendData Subroutine
  sendData(temperature, humidity, lpg, co2);
  //----------------------------------------
  
  delay(3000);
  message = "";
}

//------------------------------------------------------------ Sending data to Google sheet -------------------------------------------------------------//
// Subroutine for sending data to Google Sheets
void sendData(String temperature, String humidity, String lpg, String co2) {
  
  //Connect to Google host
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/macros/s/" + GAS_ID + "/exec?temperature=" + temperature + "&humidity=" + humidity + "&LPG=" + lpg + "&CO2=" + co2;

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");

  //Checking whether the data was sent successfully or not
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"Success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  //----------------------------------------
}

//------------------------------------------------------------ Separating collected data -------------------------------------------------------------//
void parse_data() {
  tempIndex = message.indexOf("T");
  huIndex = message.indexOf("H");
  lpgIndex = message.indexOf("L");
  coIndex = message.indexOf("C");
  
  temperature = message.substring(0, tempIndex);
  humidity = message.substring(tempIndex + 1, huIndex);
  lpg = message.substring(huIndex + 1, lpgIndex);
  co2 = message.substring(lpgIndex + 1, coIndex);
}
