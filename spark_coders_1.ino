#include<WiFi.h>
#include<HTTPClient.h>

const char* ssid="OPPO";
const char* password="maggi9804";

HTTPClient http;
int rainfall=34;

const char* api="http://192.168.175.122:2000/predict?rainfall=";


void setup() {
  Serial.begin(115200);
  pinMode(rainfall,INPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(400);
  }

  Serial.println("WIFI CONNECTED");
}

void loop() {
  int rValue=getRainfallReading();
  Serial.println(rValue);
  http.begin(api+String(rValue));
  int code=http.GET();
  if(code>0){
    String response = http.getString();
    Serial.println(response);
    http.end();
  }
  delay(1000);
}

int getRainfallReading(){
  return (analogRead(rainfall));
}
