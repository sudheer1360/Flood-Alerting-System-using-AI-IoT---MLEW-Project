int rainfall=34;
int nthreshold=1000;
int hthreshold=500;

String state;
String action;

void setup() {
  Serial.begin(115200);
  pinMode(rainfall,INPUT);
}

void loop() {
  int rValue=getRainfallReading();

  if(rValue>hthreshold && rValue<nthreshold){
    action="alert";
  } else if (rValue<hthreshold) {
    action="alert";
  } else {
    action="normal";
  }

  Serial.print("#");
  Serial.print(",");
  Serial.print(rValue);
  Serial.print(",");
  Serial.print(action);
  Serial.print(",");
  Serial.println("~");
  delay(1000);
}

int getRainfallReading(){
  return (analogRead(rainfall));
}
