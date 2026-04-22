#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

#define DHTTYPE DHT11   // DHT 11

/*Ağ adınızı ve Şifrenizi Giriniz*/
const char* ssid = "WifiName";  // Ağ adınızı girin
const char* password = "Password";  //Ağ şifrenizi girin

ESP8266WebServer server(80); //80 portunu kullanarak bir webserver nesnesi oluşturduk


uint8_t DHTPin = D4;

uint8_t LED2pin = D6;
bool LED2status = LOW;

DHT dht(DHTPin, DHTTYPE);                

float Temperature;
float Humidity;


//Timer tanımları
unsigned long previousMillis = 0;
const unsigned long interval = 1000; // Timer süresi (ms)
unsigned long timerCount = 0;


void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(DHTPin, INPUT);
  pinMode(LED2pin, OUTPUT);

dht.begin();  
  
  Serial.println(ssid);
  Serial.println(" Ağına Bağlanılıyor");

  //yerel ağınıza bağlanmanız için gerekli komut
  WiFi.begin(ssid, password);

  //bağlantının gerçekleştiğini kontrol ediyoruz
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print("."); //gerçekleşene kadar loading gibi işaret yaptırıyoruz
  }
  Serial.println("");
  Serial.println("Ağ Bağlantısı Sağlandı..!");
  Serial.print("IP Adresiniz: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);


  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP Sunucusu Başlatıldı");
}
void loop() {
  
unsigned long currentMillis = millis();

  server.handleClient();
   
  if(LED2status)
  {digitalWrite(LED2pin, HIGH);}
  else
  {digitalWrite(LED2pin, LOW);}



  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Timer süresi dolunca yapılması gereken işlemler buraya yazılır
    timerCount++;
    //Serial.print("Timer: ");
    //Serial.println(timerCount);
  Temperature = dht.readTemperature(); // 
  Humidity = dht.readHumidity(); // 
 server.send(200, "text/html", SendHTML(Temperature,Humidity,LED2status)); 
  }






}

void handle_OnConnect() {
  //LED1status = LOW;
  //LED2status = LOW;
  Temperature = dht.readTemperature(); // 
  Humidity = dht.readHumidity(); // 
  //Serial.println("GPIO7 Durumu: OFF | GPIO6 Durumu: OFF");
  //server.send(200, "text/html", SendHTML(LED1status,LED2status)); 
  server.send(200, "text/html", SendHTML(Temperature,Humidity,LED2status)); 
}


void handle_led2on() {
  LED2status = HIGH;
  //Serial.println("GPIO6 Durumu: ON");
  //server.send(200, "text/html", SendHTML(LED1status,true)); 
   server.send(200, "text/html", SendHTML(Temperature,Humidity,true)); 
}

void handle_led2off() {
  LED2status = LOW;
  //Serial.println("GPIO6 Durumu: OFF");
 // server.send(200, "text/html", SendHTML(LED1status,false)); 
   server.send(200, "text/html", SendHTML(Temperature,Humidity,false)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Sayfa Bulunamadı");
}


/*
String SendHTML(uint8_t led1stat,uint8_t led2stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<meta http-equiv=\"Content-Type\" content=\"text/html;charset=UTF-8\">";
  ptr +="<title>LED ve Röle Kontrol</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 Web Server Uygulaması</h1>\n";
    ptr +="<h3>ESP Station(STA) Modunda Kullanılıyor</h3>\n";
  
   if(led1stat)
  {ptr +="<p>LED1 Durum: AÇIK</p><a class=\"button button-off\" href=\"/led1off\">KAPAT</a>\n";}
  else
  {ptr +="<p>LED1 Durum: KAPALI</p><a class=\"button button-on\" href=\"/led1on\">AÇ</a>\n";}

  if(led2stat)
  {ptr +="<p>LED2 Durum: AÇIK</p><a class=\"button button-off\" href=\"/led2off\">KAPAT</a>\n";}
  else
  {ptr +="<p>LED2 Durum: KAPALI</p><a class=\"button button-on\" href=\"/led2on\">AÇ</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}*/


String SendHTML(float Temperaturestat,float Humiditystat,uint8_t led2stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<meta http-equiv='refresh' content='4'/>";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
   ptr +="<link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.7.2/css/all.css' integrity='sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr' crossorigin='anonymous'>";
  ptr +="<title>Hidayet Ailesinin Evi</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c ;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #0095c7;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body bgcolor= white style=color:white>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>Hidayet Ailesinin Evi</h1>\n";
  
 
  ptr +="<p><i class='fas fa-thermometer-half' style='color:#ca3517;'></i>";
  ptr +="<span class='dht-labels'>Temperature: </span>";
    ptr +=(float)Temperaturestat;
  ptr +=" C</p>";
 

  ptr +="<p><i class='fas fa-tint' style='color:#00add6;'></i>";
  ptr +="<span class='dht-labels'>NEM: </span>";
  ptr +=(int)Humiditystat;
  ptr +="%</p>";

  if(led2stat)
  {ptr +="<p>Lamba: ACIK</p><a class=\"button button-off\" href=\"/led2off\">KAPAT</a>\n";}
  else
  {ptr +="<p>Lamba: KAPALI</p><a class=\"button button-on\" href=\"/led2on\">AC</a>\n";}

 
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}


