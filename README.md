# KelasA_Kelompok4_SmartCoolingSistem

# Smart Cooling System

## Identitas Kelompok

### Kelompok 4

| Nama | NIM |
|---|---|
| Dedi Kurniawan | H1H024022 |
| Nursyafika | H1H024023 |
| Nesa Dwi Cahyani | H1H024024 |
| David Ananta Nugraha | H1H024025 |
| Javier Anthonio Justiansah | H1H024026 |
| Yogi Ferdiansyah Amta Miluloh | H1H024027 |
| Dendro Iqbal Pratama | H1H024028 |

---

## Dokumentasi

<img width="4096" height="3072" alt="Image" src="https://github.com/user-attachments/assets/d1b6d615-5de3-4d8d-b14e-eb5df87c73f7" />


Video:
https://drive.google.com/file/d/1X7EJUeB1AI30bs11OdPSwcFdYJYhN-N2/view?usp=sharing

---

## Deskripsi Sistem

Smart Cooling System merupakan sistem pendingin otomatis berbasis ESP32 yang digunakan untuk melakukan monitoring suhu secara real-time dan mengontrol kecepatan kipas secara otomatis berdasarkan kondisi suhu.

Sistem juga dilengkapi fitur emergency stop untuk menghentikan seluruh sistem ketika kondisi darurat terjadi.

---

## Fitur Sistem

- Monitoring suhu menggunakan sensor TMP36
- Kontrol otomatis kipas menggunakan PWM
- Tampilan suhu pada LCD I2C
- LED indikator kondisi suhu
- Alarm buzzer suhu tinggi
- Emergency stop berbasis interrupt
- Mode Celsius dan Fahrenheit

---

## Komponen yang Digunakan

- ESP32
- Sensor TMP36
- LCD 16x2 I2C
- Motor DC / Kipas
- LED
- Buzzer
- Push Button
- Transistor NPN
- Breadboard
- Resistor
- Kabel Jumper

---

## Diagram Blok / Flowchart

Diagram blok dan flowchart sistem akan ditambahkan pada progress selanjutnya.

---

## Mekanisme Kerja Sistem

1. Sensor TMP36 membaca suhu lingkungan.
2. Arduino memproses data suhu.
3. Sistem menentukan kondisi suhu.
4. Kipas akan menyesuaikan kecepatan secara otomatis.
5. LED dan buzzer menjadi indikator kondisi suhu.
6. LCD menampilkan suhu dan status kipas.
7. Emergency stop akan mematikan seluruh output sistem.

---

## Mata Kuliah

Sistem Mikrokontroler A
Jurusan Teknik Komputer  
Universitas Jenderal Soedirman
