# 🏠 Smart Home Elektronik

## Deskripsi Proyek

Project ini merupakan sistem **Smart Home berbasis Internet of Things (IoT)** yang menggunakan **ESP32 WeMos D1 R32** sebagai mikrokontroler utama dan protokol **MQTT** sebagai media komunikasi data secara real-time.

Sistem ini memungkinkan pengguna untuk mengontrol perangkat elektronik seperti **lampu** dan **kipas**, serta memonitor **suhu** dan **kelembaban** melalui antarmuka website. Selain kontrol manual, sistem juga memiliki mode otomatis dimana kipas akan menyala ketika suhu mencapai **30°C** atau lebih.

Selain itu, proyek ini memanfaatkan **FreeRTOS** bawaan ESP32 sehingga setiap proses dapat berjalan secara paralel, membuat sistem lebih responsif dan stabil.

---

# 👥 Kelompok 4 - Mikrokontroler

| Nama | NIM |
|------|------|
| ILMI RESTU FIRDAUS | 23552011044 |
| ELSA NURLIA | 23552011331 |
| NAUFAL EKA PUTRA PRATAMA | 23552011445 |

---

# ✨ Fitur Utama

- 💡 Kontrol Lampu ON/OFF melalui website
- 🌬️ Kontrol Kipas ON/OFF secara manual
- 🤖 Mode Kipas Otomatis berdasarkan suhu
- 🌡️ Monitoring suhu dan kelembaban menggunakan DHT22
- 📡 Komunikasi data menggunakan MQTT
- 🌐 Monitoring perangkat secara real-time
- 📶 Mendukung pergantian koneksi ke dua jaringan WiFi
- ⚡ Menggunakan FreeRTOS agar sistem berjalan lebih responsif

---

# 🛠 Hardware

- ESP32 WeMos D1 R32
- Sensor DHT22
- Lampu LED
- Kipas DC 5V
- Transistor NPN
- Resistor 220Ω
- Breadboard
- Kabel Jumper

---

# 💻 Software

- Arduino IDE
- FreeRTOS (ESP32)
- HTML
- CSS
- JavaScript
- MQTT Protocol
- HiveMQ / MQTT Broker
- Shiftr.io

---

# 📚 Library Arduino

```cpp
WiFi.h
PubSubClient.h
DHT.h
```

---

# ⚙ Cara Kerja Sistem

1. ESP32 terhubung ke jaringan WiFi.
2. ESP32 melakukan koneksi ke MQTT Broker.
3. Website mengirimkan perintah ON/OFF ke topic MQTT.
4. ESP32 menerima perintah tersebut.
5. ESP32 mengontrol lampu dan kipas sesuai perintah.
6. Sensor DHT22 membaca suhu dan kelembaban setiap 5 detik.
7. Data sensor dikirim ke MQTT Broker.
8. Website menerima data sensor secara real-time.
9. Jika mode otomatis aktif dan suhu ≥ 30°C maka kipas akan menyala secara otomatis.

---

# 📡 MQTT Topic

| Topic | Fungsi |
|--------|--------|
| `smarthome/led` | Kontrol Lampu |
| `smarthome/fan` | Kontrol Kipas |
| `smarthome/sensor` | Mengirim data suhu dan kelembaban |

---

# 🧠 Implementasi FreeRTOS

Project ini menggunakan **FreeRTOS** bawaan ESP32 untuk membagi pekerjaan menjadi beberapa **Task**, sehingga sistem dapat menjalankan beberapa proses secara bersamaan.

Task yang digunakan:

| Task | Fungsi |
|------|--------|
| TaskWiFi | Menghubungkan dan menjaga koneksi WiFi |
| TaskMQTT | Menghubungkan MQTT dan menerima perintah |
| TaskSensor | Membaca data DHT22 dan mengirim data ke MQTT |
| TaskFan | Mengontrol kipas otomatis berdasarkan suhu |

Pembagian task tersebut membuat komunikasi jaringan dan pembacaan sensor dapat berjalan secara paralel sehingga sistem lebih cepat dan responsif.

---

# 🏗 Arsitektur Sistem

```text
                     Web Dashboard
                           │
                   MQTT Publish/Subscribe
                           │
                     MQTT Broker
                           │
                        ESP32
             ┌─────────────┴─────────────┐
             │                           │
        Sensor DHT22               Kontrol Output
             │                 ┌─────────┴─────────┐
             ▼                 ▼                   ▼
   Monitoring Suhu        Lampu LED          Kipas DC
```

---

# 🚀 Instalasi

## 1. Clone Repository

```bash
git clone https://github.com/username/smart-home-elektronik.git
```

---

## 2. Install Library Arduino

Install library berikut melalui **Library Manager** Arduino IDE.

- PubSubClient
- DHT Sensor Library
- Adafruit Unified Sensor

---

## 3. Pilih Board

```
ESP32 WeMos D1 R32
```

atau

```
ESP32 Dev Module
```

---

## 4. Upload Program

- Hubungkan ESP32 ke komputer.
- Pilih Port COM.
- Klik Upload pada Arduino IDE.

---

## 5. Jalankan MQTT Broker

Broker yang dapat digunakan:

- HiveMQ
- Mosquitto
- EMQX

---

## 6. Jalankan Website

Buka file **index.html** atau jalankan menggunakan Local Server.

---

# 📂 Struktur Project

```text
smart-home/
│
├── backend/
│   └── (Source Code Backend)
│
├── esp32/
│   └── smart_home.ino
│
├── frontend/
│   ├── index.html
│   ├── style.css
│   └── script.js
│
├── images/
│   ├── dashboard.png
│   ├── rangkaian.png
│   └── esp32.png
│
└── README.md
```

---

# 🔗 Link Wokwi

https://wokwi.com/projects/466313882452088833

---

# 📄 License

Project ini dibuat untuk memenuhi tugas mata kuliah **Mikrokontroler**.

---

# ⭐ Teknologi yang Digunakan

- ESP32 WeMos D1 R32
- FreeRTOS
- MQTT
- IoT
- HTML
- CSS
- JavaScript
- Arduino IDE
- DHT22
- WiFi
- HiveMQ
- Shiftr.io
