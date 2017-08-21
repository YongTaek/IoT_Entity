#include <ArduinoJson.h>
#include <SoftwareSerial.h>

int bluetoothTx = 5;
int bluetoothRx = 6;

const int button1Pin = 10; 
const int ledPin =  13;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
char request[] =  "{\"resource\":\"car1\",\"time\":1351824120,\"name\":\"fred\",\"assist\":\"monica\"}";

void setup()
{
  Serial.begin(9600);//시리얼 통신 초기화
  bluetooth.begin(9600);//블루투스 통신 초기화
  pinMode(button1Pin, INPUT);
  pinMode(ledPin, OUTPUT);  
}
 
 
void loop()
{ 
  int button1State;     
  // 버튼이 눌렸는 지 아닌지 버튼의 상태를 읽어와서 앞에 선언한 변수에 저장
  button1State = digitalRead(button1Pin);    
  
  if(button1State == LOW){         
    bluetooth.print(request);
    bluetooth.print("\n");
    handle();
  }
}

void handle(){
  char response[128]={'\0'};
  int i = 0;
  while(!bluetooth.available());
  while(bluetooth.available()){
    delay(10);
    response[i] = bluetooth.read();
    i++;
  }
  Serial.println(response);
  String result(response);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(result);
  boolean isSuccess = root["result"];
  if (isSuccess) {
    digitalWrite (ledPin, HIGH);
    delay(1000);
    digitalWrite (ledPin, LOW);
  }
}

