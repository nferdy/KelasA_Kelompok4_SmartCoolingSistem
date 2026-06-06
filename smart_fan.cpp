#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

const int pinBtnMode = 18;
const int pinBtnEmg  = 19;

const int pinLedHijau  = 25;
const int pinLedKuning = 26;
const int pinLedMerah  = 27;

const int pinBuzzer = 13;

// L298N
const int pinENA = 23;
const int pinIN1 = 32;
const int pinIN2 = 33;

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

volatile bool emgPressed = false;
bool systemOff = false;

float suhu = 0;
float suhuTampil = 0;
bool modeFahrenheit = false;

String kipas = "Mati";
int pwm = 0;

const int fanFreq = 1000;
const int fanResolution = 8;

const int buzzerFreq = 2000;
const int buzzerResolution = 8;

void IRAM_ATTR toggleEmergency() {
  emgPressed = true;
}

void setMotor(int value) {

  if (value <= 10) {
    ledcWrite(pinENA, 0);
    digitalWrite(pinIN1, LOW);
    digitalWrite(pinIN2, LOW);
    return;
  }

  digitalWrite(pinIN1, HIGH);
  digitalWrite(pinIN2, LOW);
  ledcWrite(pinENA, value);
}

// ================= TASK CONTROL =================
void taskControl(void *pvParameters) {

  while (1) {

    if (systemOff) {
      setMotor(0);
      ledcWrite(pinBuzzer, 0);

      digitalWrite(pinLedHijau, LOW);
      digitalWrite(pinLedKuning, LOW);
      digitalWrite(pinLedMerah, HIGH);

      vTaskDelay(pdMS_TO_TICKS(200));
      continue;
    }

    float t = suhu;

    suhuTampil = modeFahrenheit
      ? (t * 9.0 / 5.0) + 32.0
      : t;

    if (t < 20) {
      kipas = "Mati"; pwm = 0;
    } else if (t < 25) {
      kipas = "Lambat"; pwm = 110;
    } else if (t < 30) {
      kipas = "Sedang"; pwm = 170;
    } else {
      kipas = "Maks"; pwm = 255;
    }

    setMotor(pwm);

    if (t > 30) ledcWrite(pinBuzzer, 150);
    else ledcWrite(pinBuzzer, 0);

    vTaskDelay(pdMS_TO_TICKS(300));
  }
}

// ================= SENSOR TASK =================
void taskSensor(void *pvParameters) {
  while (1) {
    float t = dht.readTemperature();
    if (!isnan(t)) suhu = t;
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

// ================= LCD TASK =================
void taskLCD(void *pvParameters) {
  while (1) {

    lcd.setCursor(0,0);
    lcd.print("Suhu:");
    lcd.print(suhuTampil,1);

    lcd.setCursor(0,1);
    lcd.print("Kipas:");
    lcd.print(kipas);

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(pinBtnMode, INPUT_PULLUP);
  pinMode(pinBtnEmg, INPUT_PULLUP);

  pinMode(pinLedHijau, OUTPUT);
  pinMode(pinLedKuning, OUTPUT);
  pinMode(pinLedMerah, OUTPUT);

  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);

  Wire.begin(21,22);

  lcd.init();
  lcd.backlight();
  dht.begin();

  ledcAttach(pinENA, fanFreq, fanResolution);
  ledcAttach(pinBuzzer, buzzerFreq, buzzerResolution);

  attachInterrupt(digitalPinToInterrupt(pinBtnEmg), toggleEmergency, FALLING);

  xTaskCreate(taskSensor,"Sensor",4096,NULL,1,NULL);
  xTaskCreate(taskControl,"Control",4096,NULL,2,NULL);
  xTaskCreate(taskLCD,"LCD",4096,NULL,1,NULL);
}

void loop() {

  if (emgPressed) {
    emgPressed = false;
    systemOff = !systemOff;
  }
}
