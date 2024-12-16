# Đồ án thiết kế luận lý - Học kì 241
Hệ thống giám sát điều khiển nhiệt độ, độ ẩm và Web Server

## Mục Lục
- [Giới Thiệu](#giới-thiệu)
- [Yêu Cầu Hệ Thống](#yêu-cầu-hệ-thống)
- [Cài Đặt](#cài-đặt)
<!-- - [Sử Dụng](#sử-dụng)
- [Tính Năng](#tính-năng)
- [Góp Ý và Phát Triển](#góp-ý-và-phát-triển)
- [Thông Tin Liên Hệ](#thông-tin-liên-hệ) -->

## Giới Thiệu
Hệ thống giám sát và điều khiển nhiệt độ, độ ẩm dựa trên việc sử dụng các thành phần chính bao gồm cảm biến DHT20, bộ vi điều khiển STM32, module ESP32, quạt mini, LED báo hiệu và các giao tiếp như UART, I2C, HTTP. Hệ thống này có khả năng đo đạc các thông số môi trường, hiển thị dữ liệu, điều khiển thiết bị ngoại vi, và truyền tải dữ liệu đến web server.


## Yêu Cầu Hệ Thống
- Các công cụ sử dụng
  - `STM32CubeIDE`
  - `AdruinoIDE`
  - `STM32Programmer`
  - Có thể sử dụng các công cụ tương đương,...

## Cài Đặt
Hướng dẫn chi tiết cách cài đặt dự án.

```bash
# Clone repository
git clone https://github.com/leduccuonghcmut/DA241.git

# Nối mạch như trong bài report

# Nạp code
Nạp code STM32
Nạp code ESP32


