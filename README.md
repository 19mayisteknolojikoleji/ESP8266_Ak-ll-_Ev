# 🏠 ESP8266 Akıllı Ev Web Sitesi İle

Bu proje, **ESP8266** tabanlı bir web sunucusu oluşturarak evin içindeki sıcaklık ve nem değerlerini gerçek zamanlı olarak izlemenizi ve bir lambayı/röleyi web arayüzü üzerinden kontrol etmenizi sağlar.

---

## ✨ Özellikler

* 🌡️ **Gerçek Zamanlı Takip:** DHT11 sensörü ile sıcaklık ve nem verilerini anlık olarak okur.
* 💡 **Uzaktan Kontrol:** Web arayüzü üzerinden lamba (LED) açma/kapama işlemi gerçekleştirir.
* 📱 **Responsive Arayüz:** Mobil ve masaüstü cihazlarla uyumlu, FontAwesome ikonlarıyla zenginleştirilmiş HTML arayüzü.
* 🔄 **Otomatik Yenileme:** Web sayfası her 4 saniyede bir verileri güncelleyerek en son ölçümleri gösterir.
* 🚀 **Timer Yönetimi:** `millis()` fonksiyonu kullanılarak sensör verileri işlemciyi yormadan belirli aralıklarla güncellenir.

---

## 🛠️ Kullanılan Teknolojiler & Bileşenler

* **Mikrokontrolcü:** ESP8266 (NodeMCU)
* **Sensör:** DHT11 (Sıcaklık ve Nem Sensörü)
* **İletişim:** Wi-Fi (Station Modu)
* **Yazılım Dili:** C++ (Arduino IDE)
* **Arayüz:** HTML5, CSS3, FontAwesome (CDN)

---

## 🔌 Pin Bağlantıları

| Bileşen | ESP8266 Pin | Açıklama |
| :--- | :--- | :--- |
| **DHT11 Veri** | D4 | Sıcaklık ve Nem Verisi |
| **LED / Lamba** | D6 | Kontrol Edilecek Cihaz |

---

## 🚀 Kurulum ve Çalıştırma

### 1. Hazırlık
Arduino IDE'nize aşağıdaki kütüphaneleri kurduğunuzdan emin olun:
* `DHT sensor library` (Adafruit)
* `Adafruit Unified Sensor`

### 2. Yapılandırma
Kod içerisindeki şu satırları kendi Wi-Fi ağınıza göre güncelleyin:
```cpp
const char* ssid = "WifiAdiniz";
const char* password = "Sifreniz";
```

## 📸 Ekran Görüntüleri
<img width="1200" height="1600" alt="image" src="https://github.com/user-attachments/assets/20ca78ba-1182-4d8f-8178-5d8a73329d50" />
