#define BLYNK_TEMPLATE_ID "TMPL3ZWmBl0Hf"
#define BLYNK_TEMPLATE_NAME "ESP32"
#define BLYNK_AUTH_TOKEN "noetB5XdpQpGjlrpANt7OQRRhAXIwg37"

#define BLYNK_PRINT Serial

#include<WiFi.h>
#include<HTTPClient.h>
#include<ESP32Servo.h>
#include<BlynkSimpleEsp32.h>

Servo motor1;
Servo motor2;

const char* ssid="OPPO";
const char* password="maggi9804";

const char* api="http://192.168.175.122:2000/status";

HTTPClient http;

int trig=12;
int echo=14;
int gate1=23;
int gate2=22;

void setup() {
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

  motor1.attach(gate1);
  motor2.attach(gate2);

  motor1.write(0);
  motor2.write(0);
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);

  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(400);
  }
  Blynk.begin(BLYNK_AUTH_TOKEN,ssid,password);
  Serial.println("WIFI CONNECTED");
}

void loop() {
  Blynk.run();
  http.begin(api);
  int code=http.GET();
  if(code>0){
    String response=http.getString();
    Serial.println(response);
    if(response=="alert"){
      int d=readDistance();
      int d1=map(d,180,0,0,100);
      Blynk.virtualWrite(V0,d1);
      if(d>50 && d<100){
        Serial.println("Gate1 Open");
        motor1.write(90);
        motor2.write(0);
      } else if(d>10 && d<50){
        Blynk.logEvent("flood_alert","Flood Alert, Vacate Immediately");
        Serial.println("Both Gates Open");
        motor1.write(90);
        motor2.write(90);
      } else {
        Serial.println("Both Gates Closed");
        motor1.write(0);
        motor2.write(0);
      }
    }
    http.end();
  }
  delay(2000);
}

int readDistance(){
  digitalWrite(trig,0);
  delayMicroseconds(2);

  digitalWrite(trig,1);
  delayMicroseconds(10);
  digitalWrite(trig,0);

  float duration=pulseIn(echo,1);
  duration=duration/2;

  int distance=(0.034)*duration;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}
