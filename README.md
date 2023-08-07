# Esp8266 OledMax30102MQTT

### Notice: Old prototype of the final product, development 2022. Provided as is.

The main task was to develop a miniature battery device capable of measuring human oxygen saturation (BMP) and heart rate (SP) in real time, and then send the data to the server using MQTT and WIFI networks.

# Client:

Small device based on `esp8266` code developed using `Arduino` environment and `C++` programming language.

| | Data  | URL |
|-| -------- | -- |
|1| design1 (photo) | <a href="photo/demo design.jpg">Next</a> |
|2| design bmp/sp graph (photo) | <a href="photo/demo oled.jpg">Next</a> |
|3| design demo graph (photo) | <a href="photo/demo graph.jpg">Next</a> |
|4| demo job (video) | <a href="https://disk.yandex.ru/i/amWGP29OHDuyUw">Next</a> |

<b> Components: </b>

| | Name | 
|-| -------- |
|1| Esp8266 D1 Mini |
|2| SSD1306 |
|3| TP4056 |
|4| Battery 800mah |
|5| Max30102 |

<b>!ATTENTION!</b> `Max30102` comes with different LED channels (IR can be RED or vice versa).

# Server:

The server part is allocated separately and is not included in this project.

<b> Components: </b>

| | Name | 
|-| -------- |
|1| MQTT Server |
|2| Domoticz Server |
|..| ... NodeJS |
