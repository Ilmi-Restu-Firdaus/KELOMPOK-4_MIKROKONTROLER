# Smart Home Elektronik 🏠⚡

## Deskripsi Proyek
Project ini merupakan sistem **Smart Home berbasis IoT** yang menggunakan **ESP32** sebagai mikrokontroler utama dan protokol **MQTT** sebagai media komunikasi data secara real-time. Sistem memungkinkan pengguna untuk mengontrol perangkat elektronik seperti lampu dan kipas melalui antarmuka web.

Tujuan utama dari proyek ini adalah membangun sistem otomasi rumah sederhana yang ringan, responsif, dan dapat diakses dari mana saja melalui jaringan internet maupun lokal.

---

# 👥 KELOMPOK 4 - MIKROKONTROLER

| Nama | NIM |
|------|------|
| ILMI RESTU FIRDAUS | 23552011044 |
| ELSA NURLIA | 23552011331 |
| NAUFAL EKA PUTRA PRATAMA | 23552011445 |

---

## ✨ Fitur Utama
- 💡 Kontrol lampu secara real-time melalui web
- 🌬️ Kontrol kipas melalui dashboard web
- 📡 Komunikasi cepat menggunakan protokol MQTT
- 📊 Monitoring status perangkat secara real-time
- 🌐 Dapat diakses melalui jaringan lokal maupun internet

---

## 🛠️ Teknologi yang Digunakan

### Hardware
- ESP32
- Lampu LED
- Kipas DC
- Breadboard
- Kabel jumper

### Software
- Arduino IDE
- MQTT Protocol
- HTML, CSS, JavaScript
- Web Dashboard

---

## ⚙️ Cara Kerja Sistem

1. ESP32 terhubung ke jaringan WiFi.
2. ESP32 terkoneksi ke MQTT Broker.
3. Website mengirim perintah ON/OFF ke topic MQTT tertentu.
4. ESP32 menerima data dari broker dan menjalankan aksi:
   - Menyalakan atau mematikan lampu
   - Mengontrol kipas
5. Status perangkat dikirim kembali ke website secara real-time.

---

## 📌 Arsitektur Sistem

```text
[ Web Dashboard ]
        │
        │ MQTT
        ▼
[ MQTT Broker ]
        │
        ▼
[ ESP32 Controller ]
     │         │
     ▼         ▼
 [ Lampu ]   [ Kipas ]
```

---

## 🚀 Instalasi dan Penggunaan

### 1. Clone Repository
```bash
git clone https://github.com/username/smart-home-elektronik.git
```

### 2. Upload Program ke ESP32
- Buka project menggunakan Arduino IDE
- Install library MQTT yang diperlukan
- Pilih board ESP32
- Upload program ke ESP32

### 3. Jalankan MQTT Broker
Gunakan broker seperti:
- Mosquitto
- HiveMQ
- EMQX

### 4. Jalankan Web Dashboard
Buka file HTML atau jalankan menggunakan local server.

---

## 📷 Tampilan Sistem

Tambahkan screenshot dashboard atau rangkaian di folder `images/`.

```md
![Dashboard](images/dashboard.png)
```

---

## 📂 Struktur Project

```text
smart-home-elektronik/
│
├── esp32/
│   └── smart_home.ino
│
├── web/
│   ├── index.html
│   ├── style.css
│   └── script.js
│
├── images/
│
└── README.md
```

---

## 🔮 Pengembangan Selanjutnya
- Penambahan sensor suhu dan kelembapan
- Monitoring konsumsi listrik
- Integrasi dengan aplikasi mobile
- Sistem notifikasi otomatis
- Voice control menggunakan Google Assistant

---

## 📄 License
Project ini dibuat untuk kebutuhan Mata kuliah Mikrokontroler.
