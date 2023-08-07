
// #UlinProject22

#define int_pin 12 //D6

#include <ESP8266WiFi.h>
#include <max30102.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <PubSubClient.h>
#include <ESP8266WebServer.h>
#include <algorithmRF.h>

#define idX_WARNING 2
#define idX_BPM 3
#define idX_SP02 1
#define mqttServer "10.42.0.1"
#define mqttPort 1883
#define mqttUser ""
#define mqttPassword ""
#define mqttin "domoticz/in"

#define LOGO_HEIGHT   64
#define LOGO_WIDTH    64
static const unsigned char PROGMEM logo_bmp[] ={ 
// 'free-icon-pulse-143010', 64x64px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xbc, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x07, 0xbc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x0f, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x1e, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x3e, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x3c, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x78, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0xf0, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x10, 
0x01, 0xf0, 0x01, 0xe0, 0x00, 0x00, 0x00, 0xfc, 0x01, 0xe0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xfe, 
0xff, 0xe0, 0x00, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0xf8, 0x00, 0x1f, 0xff, 0xff, 
0xff, 0xc0, 0x00, 0x78, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x78, 0x00, 0x1f, 0xff, 0xff, 
0x00, 0x00, 0x00, 0x3c, 0x00, 0x3c, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x3c, 0x00, 0xfc, 
0x00, 0x00, 0x00, 0x3c, 0x00, 0x3c, 0x00, 0x10, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x78, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x1e, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0xf8, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x0f, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0xf0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x07, 0x81, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0xe0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x07, 0x81, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc3, 0xc0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x03, 0xc3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe7, 0xc0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x01, 0xe7, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe7, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
 };

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
ESP8266WebServer server(80);
Adafruit_SSD1306 display(128, 64, &Wire, -1);

#define MAX_INVALID_CONNECTS 6 *2 // 12s
#define SSID "RPI4"
#define PASSWORD "999999999"
#define HOSTNAME "PULSEUSER_001"

uint8_t anim_warning;
bool is_update_warning;
bool is_warning;
bool is_update_warning_ignore_mqtt;
WiFiClient espClient;
PubSubClient client(espClient);
IPAddress ip(10,42,0,2);
IPAddress gateway(10,42,0,1);
IPAddress subnet(255,255,255,0);

#define MSG_BUFFER_SIZE  (60)
char mqttmsg[MSG_BUFFER_SIZE];

long samplesTaken = 0; //Counter for calculating the Hz or read rate
//
uint32_t aun_ir_buffer[BUFFER_SIZE]; //infrared LED sensor data
uint32_t aun_red_buffer[BUFFER_SIZE];  //red LED sensor data
float old_n_spo2;  // Previous SPO2 value
uint8_t uch_dummy,k;
uint32_t old_update_bmpsp02_time;

void update_scale_min_max(uint8_t del_width, String maxHum, String minHum, String averageHum);
void flush_all_display();

//
void millis_to_hours(uint32_t ms, char* hr_str) {
  char istr[6];
  uint32_t secs,mins,hrs;
  secs=ms/1000; // time in seconds
  mins=secs/60; // time in minutes
  secs-=60*mins; // leftover seconds
  hrs=mins/60; // time in hours
  mins-=60*hrs; // leftover minutes
  itoa(hrs,hr_str,10);
  strcat(hr_str,":");
  itoa(mins,istr,10);
  strcat(hr_str,istr);
  strcat(hr_str,":");
  itoa(secs,istr,10);
  strcat(hr_str,istr);
}

bool inline auto_mqtt_reconnect() {
  if (client.connected()) {
    return true;
  }
  client.connect(HOSTNAME, mqttUser, mqttPassword);
  yield();
  return client.connected();
}

bool mqtt_update_sp02(int value) {
  if (auto_mqtt_reconnect()) {
    yield();
    
    snprintf(mqttmsg, MSG_BUFFER_SIZE, "{\"idx\":%d,\"svalue\":\"%d\"}", idX_SP02, value);
    if (!client.publish(mqttin, mqttmsg)) {
      return false;
    }
    return true;
  }
  return false;
}

bool mqtt_update_bpm(int value) {
  if (auto_mqtt_reconnect()) {
    yield();
    
    snprintf(mqttmsg, MSG_BUFFER_SIZE, "{\"idx\":%d,\"svalue\":\"%d\"}", idX_BPM, value);
    if (!client.publish(mqttin, mqttmsg)) {
      return false;
    }
    return true;
  }
  return false;
}

bool mqtt_update_warning(bool value) {
  if(is_update_warning_ignore_mqtt) {
    is_update_warning_ignore_mqtt = false;
    return true;
  }
  if (auto_mqtt_reconnect()) {
    yield();

    if(value) {
      snprintf(mqttmsg, MSG_BUFFER_SIZE, "{\"idx\":%d,\"nvalue\":1}", idX_WARNING);
    }else {
      snprintf(mqttmsg, MSG_BUFFER_SIZE, "{\"idx\":%d,\"nvalue\":0}", idX_WARNING);
    }
    
    if (!client.publish(mqttin, mqttmsg)) {
      return false;
    }
    return true;
  }
  return false;
}

uint32_t humidity[100];
int count = 0;

const uint32_t min(uint32_t& a, uint32_t&b) {
  if ((int)b < a) {
    return (uint32_t)b;
  }
  return a;
}
const uint32_t max(uint32_t& a, uint32_t b) {
  if ((int)b > a) {
    return (uint32_t)b;
  }
  return a;
}

float old_sp02;
uint32_t old_ubmp;

void setup(){
  is_update_warning_ignore_mqtt = false;
  is_warning = false;
  is_update_warning = false;
  anim_warning = 0;
  old_update_bmpsp02_time = millis();

  uint8_t i = 0;
  while (i < 100) {
    humidity[i] = 0;
    i += 1;
  }
  
  Wire.begin();
  pinMode(int_pin, INPUT);

  WiFi.persistent(false);
  WiFi.hostname(HOSTNAME);
  WiFi.setAutoReconnect(true);
  WiFi.begin(SSID, PASSWORD);
  WiFi.config(ip, gateway, subnet);
  
  Wire.setClock(400000L); // 800000
  Wire.setClockStretchLimit(1500);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();

  display.cp437(true);
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text

  display.setCursor(0, 0);
  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  
  maxim_max30102_reset();
  delay(2000);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("UWait...");
  display.display();
    
  if (!maxim_max30102_init()){
    display.setCursor(0, 10);
    display.print("MAX30105 was not found");
    display.display();
    while (true) {
      yield();
    }
  }

  
  display.setCursor(0, 10);
  uint8_t uch_dummy = 0;
  maxim_max30102_read_reg(REG_REV_ID, &uch_dummy);
  display.print("PULSE: [ID" + (String)uch_dummy + "]");
  display.display();

  display.setCursor(0, 30);
  display.print("NAME: [" + (String)HOSTNAME + "]");

  display.setCursor(0, 40);
  display.print("WIFI: [" + (String)SSID + "] >>>");
  display.display();
  while(WiFi.status() != WL_CONNECTED) {
    yield();
    delay(500);

    display.setCursor(0, 40);
    display.setTextColor(SSD1306_BLACK);        // Draw white text
    display.print("WIFI: [" + (String)SSID + "]");
    
    display.display();
    delay(500);
    
    display.setCursor(0, 40);
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.print("WIFI: [" + (String)SSID + "]");
    display.display();
  }
  
  

  client.setServer(mqttServer, mqttPort);
  if(!auto_mqtt_reconnect()) {
    display.setCursor(0, 50);
    display.print("MQTT: [INVALID_CONNECT]");
    display.display();
  }else {
    display.setCursor(0, 50);
    display.print("MQTT: [OK]");
    display.display();
  }

  server.on("/", []() {
    server.send(200, "text/plain", "");
  });
  server.on("/warn_on", []() {
    is_update_warning_ignore_mqtt = true;
    if(!is_warning) {
      is_warning = true;
      is_update_warning = true;
    
      server.send(200, "text/plain", "1");
    }else {
      server.send(200, "text/plain", "0");
    }
  });
  server.on("/warn_off", []() {
    is_update_warning_ignore_mqtt = true;
    if(is_warning) {
      is_warning = false;
      is_update_warning = true;
      
      server.send(200, "text/plain", "1");
    }else {
      server.send(200, "text/plain", "0");
    }
  });
  server.begin();
  
  yield();
  delay(1000);
  
  display.clearDisplay();
  display.setCursor(0, 0);
  update_sp02_bmp("_", "_");
  update_scale_min_max(25, "MAX", "MIN", "AVERAGE");
  update_all_borders();
  display.display();
  delay(2000);

  old_n_spo2=0.0;
  
  //startTime = millis();
  old_sp02 = 0.0;
  old_ubmp = 0.0;
}

void flush_all_display() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.display();
  
  
  yield();
}

void update_all_borders() {
  display.drawLine(0, 18, 127, 18, SSD1306_WHITE);
  display.drawLine(0, 18, 0, 63, SSD1306_WHITE);
  display.drawLine(127, 18, 127, 63, SSD1306_WHITE);
  display.drawLine(0, 63, 127, 63, SSD1306_WHITE);
}

String old_scale_maxhum = "";
String old_scale_minhum = "";
String old_scale_averagehum = "";
uint8_t old_width = 0;
void update_scale_min_max(const uint8_t del_width, String maxHum, String minHum, String averageHum) {
  bool is_always_flushold = false;
  if (old_width != del_width) {
    is_always_flushold = true;

    //Нарисовали саму шкалу
    display.drawLine(103 -old_width, 62, 103  -old_width, 20, SSD1306_BLACK);
    display.drawLine(103 -old_width, 61, 108  -old_width, 61, SSD1306_BLACK);
    display.drawLine(103 -old_width, 20, 108  -old_width, 20, SSD1306_BLACK);
    
    display.drawLine(103 -del_width, 62, 103  -del_width, 20, SSD1306_WHITE);
    display.drawLine(103 -del_width, 61, 108  -del_width, 61, SSD1306_WHITE);
    display.drawLine(103 -del_width, 20, 108  -del_width, 20, SSD1306_WHITE);
  }

  if (is_always_flushold || old_scale_maxhum != maxHum) { // MAX
    if (is_always_flushold || old_scale_maxhum != "") {
      display.setCursor(109 -old_width, 20);
      display.setTextColor(SSD1306_BLACK);
      display.print(old_scale_maxhum);
    }

    old_scale_maxhum = maxHum;
    display.setCursor(109 -del_width, 20);
    display.setTextColor(SSD1306_WHITE);
    display.print(old_scale_maxhum);
  }

  if (is_always_flushold || old_scale_minhum != minHum) { // MIN
    if (is_always_flushold || old_scale_minhum != "") {
      display.setCursor(109 -old_width, 55);
      display.setTextColor(SSD1306_BLACK);
      display.print(old_scale_minhum);
    }

    old_scale_minhum = minHum;
    display.setCursor(109 -del_width, 55);
    display.setTextColor(SSD1306_WHITE);
    display.print(old_scale_minhum);
  }
  
  if (is_always_flushold || old_scale_averagehum != averageHum) { // AVERAGE
    if (is_always_flushold || old_scale_averagehum != "") {
      display.setCursor(109 -old_width, 55 - 20 + 2);
      display.setTextColor(SSD1306_BLACK);
      display.print(old_scale_averagehum);
    }
  
    old_scale_averagehum = averageHum;
    display.setCursor(109 -del_width, 55 - 20 + 2);
    display.setTextColor(SSD1306_WHITE);
    display.print(old_scale_averagehum);
  }

  if (old_width != del_width) {
    old_width = del_width;
  }
}

String a_sp02_bmp = "";
void update_high_line(String res) {
  if (a_sp02_bmp != res) {
    if (a_sp02_bmp != "") {
      display.setCursor(8, 5);
      display.setTextColor(SSD1306_BLACK);
      display.print(a_sp02_bmp);
    }
    display.setCursor(8, 5);
    display.setTextColor(SSD1306_WHITE);
        
    a_sp02_bmp = res;
    display.print(a_sp02_bmp);
  }
}

void update_sp02_bmp(String sp02, String bmp) {
  String res = "> SP02:" + (String)sp02 + "; BMP:" + bmp + ";";
  update_high_line(res);
}


bool is_force_loop = false;
void loop() {
  while (true) {
    float n_spo2,ratio,correl = 0.0;  //SPO2 value
    int8_t ch_spo2_valid = 0;  //indicator to show if the SPO2 calculation is valid
    int32_t n_heart_rate = 0; //heart rate value
    int8_t  ch_hr_valid = 0;  //indicator to show if the heart rate calculation is valid
    uint8_t i = 0;
    char hr_str[10] = {0};

    for (i = 99; i > 0; i--) { //делать кольцевой массив лень
      humidity[i] = humidity[i - 1];
    }

    i = 0;
    for(i=0;i<BUFFER_SIZE;i++) {
      while(digitalRead(int_pin) == HIGH) {
        //
      }
      maxim_max30102_read_fifo((aun_red_buffer+i), (aun_ir_buffer+i));  //read from MAX30102 FIFO
      delay(3); // need time for int pin to reset
    }
    humidity[0] = aun_red_buffer[0];
    for(i=1;i<BUFFER_SIZE;i++) {
      humidity[0] = (((uint64_t)humidity[0]) + aun_red_buffer[i])/2;
    }
    yield();
  
    //calculate heart rate and SpO2 after BUFFER_SIZE samples (ST seconds of samples) using Robert's method
    rf_heart_rate_and_oxygen_saturation(
      aun_red_buffer,
      
      BUFFER_SIZE, 
      aun_ir_buffer, 
      &n_spo2, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid, &ratio, &correl
    ); 
  
    yield();
    //humidity[0] = random(random(random(1,125),random(1,125)));//Меряем влажность
    if (count < 90) count++;       //Сколько атуальных значений в массиве
    //для исключения нулей при включении
  
    //
    //yield();
    
    //Нашли минимум и максимум на графике
    uint32_t minHum = humidity[0];
    uint32_t maxHum = humidity[0] + 1;
    uint64_t averageHum = 0;
    
    for (i = 0; i < count/3; i++) {
      averageHum += humidity[i];
      averageHum = averageHum / 2;
      
      minHum = min(minHum, humidity[i]);
      maxHum = max(maxHum, humidity[i]);
    }
    //Написали их на шкале справа
    //display.setFont(SmallFont);
    //display.drawString(lightMeter.readLightLevel(), CENTER, 0);

    if (n_spo2 >= 90.0) {
      old_sp02 = n_spo2;
    }
    if (n_spo2 < 98.0) {
      n_spo2 = 98.0;
    }
    if (n_heart_rate > 82 && n_heart_rate < 300) {
      //humidity[0] = n_heart_rate;
      old_ubmp = n_heart_rate;
    }else {
      //humidity[0] = 0;
    }

     if (is_update_warning) {
        if (is_warning) {
          display.setTextColor(SSD1306_WHITE);
        }else {
          display.setTextColor(SSD1306_BLACK);
        }
        display.setCursor(2, 5);
        display.print("!");
        
        display.setTextColor(SSD1306_WHITE);
     }
     if (is_warning) {
      if (anim_warning > 0) {
        anim_warning += 1;
        if (anim_warning >= 6) {
          anim_warning = 0;
        }
        display.setTextColor(SSD1306_WHITE);
      }else {
        anim_warning = 1;
        display.setTextColor(SSD1306_BLACK);
      }
      display.setCursor(2, 5);
      display.print("!");
      
      display.setTextColor(SSD1306_WHITE);
     }

    uint8_t old_del_c_width = old_width;
    uint8_t del_width = 0;
    if (minHum >= 1000000 || maxHum >= 1000000 || averageHum >= 1000000) {
      del_width = 20;
    }else
    if (minHum >= 100000 || maxHum >= 100000 || averageHum >= 100000) {
      del_width = 18;
    }else
    if (minHum >= 10000 || maxHum >= 10000 || averageHum >= 10000) {
      del_width = 12;
    }else
    if (minHum >= 1000 || maxHum >= 1000 || averageHum >= 1000) {
      del_width = 10;
    }else
    if (minHum >= 100 || maxHum >= 100 || averageHum >= 100) {
      del_width = 0;
    }

    bool is_en_flush_lines = true;
    if (old_del_c_width != del_width) {
      is_en_flush_lines = false;
      for (int i = 0; i < count; i++) {
        display.drawLine(
          101 - i  -old_del_c_width, 19, 
          101 - i  -old_del_c_width, 62, 
          
          SSD1306_BLACK
        );
      }
    }

    if (minHum < 10000 || maxHum < 10000) {
      count = 0;
      update_high_line("> WAIT FINGER;");
      //update_scale_min_max(10, "MAX", "MIN", "AVE");
      display.display();
      server.handleClient();
      yield();

      if (is_update_warning) {
        if (!is_warning) {
          display.setTextColor(SSD1306_BLACK);
          uint8_t i = 12;
          while (i < 50) {
            i += 12;
            
            display.setCursor(8, i);
            display.print((String)"ATTENTION");
          }
          display.setTextColor(SSD1306_WHITE);
        }
      }
      if (is_warning) {
        if (anim_warning > 0) {
          display.setTextColor(SSD1306_BLACK);
        }else {
          display.setTextColor(SSD1306_WHITE);
        }
        
        uint8_t i = 12;
        while (i < 50) {
          i += 12;
          
          display.setCursor(8, i);
          display.print((String)"ATTENTION");
        }
        display.setTextColor(SSD1306_WHITE);
      }

      continue;
    }
    
    if (old_sp02 < 50.0 || old_ubmp < 50.0) {
      update_sp02_bmp("?", "?");
    }else {
      update_sp02_bmp((String)(uint8_t)round(old_sp02), (String)(uint32_t)round(old_ubmp));

      const uint32_t amillis = millis();
      if (amillis - old_update_bmpsp02_time >= 5000) {
        old_update_bmpsp02_time = amillis;
        mqtt_update_sp02((int)round(old_sp02));
        mqtt_update_bpm((int)round(old_ubmp));
      }
    }
    yield();

    

    update_scale_min_max(del_width, (String)maxHum, (String)minHum, (String)averageHum);
    //И деления на ней
    int j = 10; //шаг делений 10%
    if (maxHum - minHum < 50) j = 5; //или 5% если размах графика меньше
    if (maxHum - minHum < 11) j = 1; //или 1% если совсем маленький

    yield();
    //Нарисовали график

    // штрихи?!
    for (uint8_t i = 0; i < count; i++) {
      uint32_t a = humidity[i];
      if (a > maxHum) {
        a = maxHum;
      }
      if (a < minHum) {
        a = minHum;
      }
      const uint32_t y = map(a, minHum, maxHum, 61, 20);

      if (is_en_flush_lines) {
        display.drawLine(
          101 - i  -del_width, 19, 
          101 - i  -del_width, 62, 
          
          SSD1306_BLACK
        );
      }
      display.drawLine(
        101 - i  -del_width, 62, 
        101 - i  -del_width, y, 
        
        SSD1306_WHITE
      );
    }
    /*for (int i = 0; i < count; i++) {
      int y = map(humidity[i] * 10, minHum * 10, maxHum * 10, 61, 20);
      display.drawLine(101 - i, 62, 101 - i, y, SSD1306_WHITE);
    }*/

    if (is_update_warning) {
      if (!is_warning) {
        display.setTextColor(SSD1306_BLACK);
        uint8_t i = 12;
        while (i < 50) {
          i += 12;
          
          display.setCursor(8, i);
          display.print((String)"ATTENTION");
        }
        display.setTextColor(SSD1306_WHITE);
      }
    }
    if (is_warning) {
      if (anim_warning > 0) {
        display.setTextColor(SSD1306_BLACK);
      }else {
        display.setTextColor(SSD1306_WHITE);
      }
      
      uint8_t i = 12;
      while (i < 50) {
        i += 12;
        
        display.setCursor(8, i);
        display.print((String)"ATTENTION");
      }
      display.setTextColor(SSD1306_WHITE);
    }
    if (is_update_warning) {
      update_all_borders();
      is_update_warning = false;
    }
    
    
    //Вывели данные из буфера на дисплей
    display.display();
    server.handleClient();
    yield();
  }
}
