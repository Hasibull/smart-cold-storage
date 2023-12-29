#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#define FIREBASE_HOST "smart-cold-storage-cbae1-default-rtdb.firebaseio.com/" 
#define FIREBASE_AUTH "GnDAI4mXLLJD76sMLaJQK71qdMCCZsfAhfpDc4PB"

#define WIFI_SSID "Sabbir 2.4G"
#define WIFI_PASSWORD "$sabbir62$"

// Initializing software-serial
SoftwareSerial receiving(D5, D6);

// Declare the Firebase Data object in the global scope
FirebaseData firebaseData;

// Declare global variable to store value
int val=0;

// Sensor values
String temperature, humidity, lpg, co2;
// separation index
int tempIndex, huIndex, lpgIndex, coIndex;
char endText;
String dataSeq;

void setup() {

  Serial.begin(9600);
  receiving.begin(9600);

  Serial.println("Serial communication started\n\n");  
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  delay(1000);
}

void loop() { 

  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(receiving);

  if(root == JsonObject::invalid()) {
    Serial.print("Wrong");
  }

  float val1 = root["temperature"];
  float val2 = root["humidity"];
  Serial.print(val1);
  Serial.print(val2);

//  if(sending.available() > 0) {
//    root.printTo(sending);
//  }
  

//  while(receiving.available() > 0) {
//    endText = receiving.read();
//
//    if(endText == '\n') {
//      break;
//    }
//    else {
//      dataSeq += endText;
//    }
//  }
//
//  if(endText == '\n') {
//    parse_data();
//    if(Firebase.setInt(firebaseData, "/temperature", temperature) && Firebase.setInt(firebaseData, "/humidity", humidity) && Firebase.setInt(firebaseData, "/lpg", lpg) && Firebase.setInt(firebaseData, "/co2", co2)) {
//      Serial.println("Value Uploaded Successfully");
//      
//      val++;
//      delay(1000);
//    }
//    else {        
//      Serial.println(firebaseData.errorReason());
//    }
//    
//    // Reseting variables for further values
//    endText = 0;
//    dataSeq = "";
//  }
}


//void parse_data() {
//  lpgIndex = dataSeq.indexOf("l");
//  coIndex = dataSeq.indexOf("a");
//  huIndex = dataSeq.indexOf("h");
//  tempIndex = dataSeq.indexOf("t");
//
//  lpg = dataSeq.substring(0, lpgIndex);
//  co2 = dataSeq.substring(lpgIndex + 1, coIndex);
//  humidity = dataSeq.substring(coIndex + 1, huIndex);
//  temperature = dataSeq.substring(huIndex + 1, tempIndex);
//}
