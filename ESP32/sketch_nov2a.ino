// Load Wi-Fi library
#include <WiFi.h>
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"
#include "driver/gpio.h"
#define TXD_PIN (GPIO_NUM_17)
#define RXD_PIN (GPIO_NUM_16)
 
#define TXD2_PIN (GPIO_NUM_4)  // UART1 TX
#define RXD2_PIN (GPIO_NUM_5)  // UART1 RX
// Replace with your network credentials
const char* ssid = "Hao_Thai";             // tên wifi
const char* password = "h@oth@i30082002";  // password của wifi
// Set web server port number to 80
WiFiServer server(80);
// Variable to store the HTTP request
String header;

// Assign output variables to GPIO pins

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

float value;
float value1;
void setup() {
  Serial.begin(115200);

 
 // Config UART2
    const uart_port_t uart_num = UART_NUM_2;
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS,
        .rx_flow_ctrl_thresh = 122,
    };
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_2, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    const int uart_buffer_size = (1024 * 2);
    QueueHandle_t uart_queue;
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_2, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));
 
    // Config UART1
    const uart_port_t uart_num1 = UART_NUM_1;
 
    ESP_ERROR_CHECK(uart_param_config(uart_num1, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_1, TXD2_PIN, RXD2_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_1, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();  // Listen for incoming clients
    const uart_port_t uart_num = UART_NUM_2;
    uint8_t data[128];
    int length = 0;
    ESP_ERROR_CHECK(uart_get_buffered_data_len(uart_num, (size_t*)&length));
    length = uart_read_bytes(uart_num, data, length, 100);
    if (length > 0) {
        char * test = (char*) data;
     value = strtof(test, nullptr); // Sử dụng strtof để chuyển đổi

    }
 
    // Read data from UART1
    const uart_port_t uart_num1 = UART_NUM_1;
    uint8_t data1[128];
    int length1 = 0;
    ESP_ERROR_CHECK(uart_get_buffered_data_len(uart_num1, (size_t*)&length1));
    length1 = uart_read_bytes(uart_num1, data1, length1, 100);
    if (length1 > 0) {
        char * test1 = (char*) data1;
     value1 = strtof(test1, nullptr); // Sử dụng strtof để chuyển đổi
        // Serial.print("UART1....................................");
        // Serial.println(test1);
    }
  if (client) {  // Nếu có client kết nối
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");
    String currentLine = "";
while (client.connected() && currentTime - previousTime <= timeoutTime) {
  currentTime = millis();
  if (client.available()) {
    char c = client.read();
    Serial.write(c);
    header += c;

    // Kiểm tra yêu cầu cho các endpoint
    if (header.indexOf("GET /data") >= 0) {
      // Gửi dữ liệu JSON
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: application/json");
      client.println("Connection: close");
      client.println();
      client.print("{\"tempC\":");
      client.print(value);
      client.print(", \"tempF\":");
      client.print((value * 9 / 5) + 32);
      client.print(", \"humidity\":");
      client.print(value1);
      client.println("}");
      break;  // Thoát vòng lặp sau khi gửi dữ liệu
    }

    if (c == '\n') {
      if (currentLine.length() == 0) {
        // Gửi HTML khi client yêu cầu trang chính
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println("Connection: close");
        client.println();
        // Gửi mã HTML
        client.println("<!DOCTYPE html>");
        client.println("<html lang=\"en\">");
        client.println("<head>");
        client.println("  <meta charset=\"UTF-8\">");
        client.println("  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
        client.println("  <link href=\"https://f...content-available-to-author-only...s.com/css2?family=Poppins:wght@100&display=swap\" rel=\"stylesheet\">");
        client.println("  <style>");
        client.println("    * { padding: 0; margin: 0; font-family: 'Poppins', sans-serif; }");
        client.println("    body { height: 100vh; background-image: linear-gradient(41deg, #00bcd4, #3b0aff); display: flex; justify-content: center; align-items: center; }");
        client.println("    :root { --size: 300px; --bord: 50px; --a: 60%; --b: 60%; --c: 60%; }");
        client.println("    .DoC { width: var(--size); height: var(--size); margin: 1em auto; border-radius: 50%; background: conic-gradient(red var(--value), lightgrey var(--value)); position: relative; display: flex; justify-content: center; align-items: center; margin: 80px; }");
        client.println("    .DoC::after { content: ''; position: absolute; left: 50%; top: 50%; transform: translate(-50%, -50%); width: calc(100% - var(--bord)); height: calc(100% - var(--bord)); background: white; border-radius: inherit; }");
        client.println("     .DoF { width: var(--size); height: var(--size); margin: 1em auto; border-radius: 50%; background: conic-gradient(green var(--value), lightgrey var(--value)); position: relative; display: flex; justify-content: center; align-items: center; margin: 80px; }");
        client.println("    .DoF::after { content: ''; position: absolute; left: 50%; top: 50%; transform: translate(-50%, -50%); width: calc(100% - var(--bord)); height: calc(100% - var(--bord)); background: white; border-radius: inherit; }");
        client.println("         .DoAm { width: var(--size); height: var(--size); margin: 1em auto; border-radius: 50%; background: conic-gradient(rgb(18, 190, 224) var(--value), lightgrey var(--value)); position: relative; display: flex; justify-content: center; align-items: center; margin: 80px; }");
        client.println("    .DoAm::after { content: ''; position: absolute; left: 50%; top: 50%; transform: translate(-50%, -50%); width: calc(100% - var(--bord)); height: calc(100% - var(--bord)); background: white; border-radius: inherit; }");
        client.println("    .inner-head { display: flex; }");
        client.println("    .text { position: absolute; top: 350px; }");
        client.println("    p { position: relative; z-index: 1; font-size: 2em; font-weight: 900; }");
        client.println("    .DoC { --value: var(--a); }");
        client.println("    .DoF { --value: var(--b); }");
        client.println("    .DoAm { --value: var(--c); }");
        client.println("    .b-skills { padding-top: 46px; text-align: center; }");
        client.println("    .b-skills:last-child { margin-bottom: -30px; }");
        client.println("    .b-skills h2 { margin-bottom: 50px; font-weight: 900; text-transform: uppercase; }");
        client.println("    .skill-item { max-width: 250px; width: 100%; margin-bottom: 30px; color: black; position: relative; }");
        client.println("    .chart-container { position: relative; width: 100%; padding-top: 100%; margin-bottom: 27px; }");
        client.println("    .skill-item .chart, .skill-item .chart canvas { position: absolute; top: 0; left: 0; width: 100% !important; height: 100% !important; }");
        client.println("    .skill-item .chart:before { content: ''; width: 0; height: 100%; display: inline-block; vertical-align: middle;}"); 
        client.println("    .skill-item .percent { display: inline-block; vertical-align: middle; line-height: 1; font-size: 40px; font-weight: 900; position: relative; z-index: 2; }"); 
        client.println("    .skill-item .percent:after { content: attr(data-after); font-size: 20px; }"); 
        client.println("    p { font-weight: 900; }"); 
        client.println("  </style>");
        client.println("</head>");
        client.println("<body>");
        client.println("  <div class=\"inner-head\">");
        client.println("    <div class=\"chart DoC\">");
        client.println("      <p id='tempC'></p>");
        client.println("      <p class=\"text\">Nhiệt Độ(&deg;C)<br>Max 100&deg;C</p>");
        client.println("    </div>");
        client.println("    <div class=\"chart DoF\">");
        client.println("      <p id='tempF'></p>");
        client.println("      <p class=\"text\">Nhiệt Độ(&deg;F)<br>Max 373&deg;F</p>");
        client.println("    </div>");
        client.println("    <div class=\"chart DoAm\">");
        client.println("      <p id='humidity'></p>");
        client.println("      <p class=\"text\">Độ Ẩm( %)<br>Max 100%</p>");
        client.println("    </div>");
        client.println("  </div>");
        client.println("  <script>");
        client.println("    function updateValues() {");
        client.println("      fetch('/data')"); // Gọi endpoint mới
        client.println("        .then(response => response.json())");
        client.println("        .then(data => {");
        client.println("          document.getElementById('tempC').innerText = data.tempC + '°C';");
        client.println("          document.getElementById('tempF').innerText = Math.floor((data.tempC * 9/5) + 32) + '°F';");
        client.println("          document.getElementById('humidity').innerText = data.humidity + '%';");
        client.println("          document.documentElement.style.setProperty('--a', data.tempC + '%');");
        client.println("          document.documentElement.style.setProperty('--b', Math.floor((data.tempC * 9/5) + 32) / 3.73 + '%');");
        client.println("          document.documentElement.style.setProperty('--c', data.humidity + '%');");
        client.println("        });");
        client.println("    }");
        client.println("    setInterval(updateValues, 500);"); // Cập nhật mỗi giây
        client.println("  </script>");
        client.println("</body>");
        client.println("</html>");
        client.println();
        break;  // Thoát vòng lặp sau khi gửi HTML
      } else {
        currentLine = "";
      }
    } else if (c != '\r') {
      currentLine += c;
    }
  }
}
    header = "";
    client.stop();  // Đóng kết nối client
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}