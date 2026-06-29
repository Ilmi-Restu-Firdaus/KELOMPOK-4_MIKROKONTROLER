#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

//======================================================
// WIFI
//======================================================

const char* ssid1 = "******";
const char* password1 = "*****";

const char* ssid2 = "*****";
const char* password2 = "*******";

//======================================================
// MQTT
//======================================================

const char* mqtt_broker   = "kelompok4mikrokontroller.cloud.shiftr.io";
const char* mqtt_user     = "kelompok4mikrokontroller";
const char* mqtt_password = "*********";
const char* mqtt_client   = "esp32-smarthome";

//======================================================
// PIN
//======================================================

#define LED_PIN   13
#define FAN_PIN   12
#define DHT_PIN   14
#define DHT_TYPE  DHT22

//======================================================
// OBJECT
//======================================================

DHT dht(DHT_PIN, DHT_TYPE);

WiFiClient espClient;
PubSubClient client(espClient);

//======================================================
// GLOBAL VARIABLE
//======================================================

float suhu = 0;
float lembab = 0;

bool fanManual = false;
bool fanStatus = false;

SemaphoreHandle_t sensorMutex;

//======================================================
// FUNCTION DECLARATION
//======================================================

void connectWiFi();
void connectMQTT();

void TaskWiFi(void *pvParameters);
void TaskMQTT(void *pvParameters);
void TaskSensor(void *pvParameters);
void TaskFan(void *pvParameters);

//======================================================
// MQTT CALLBACK
//======================================================
void callback(char* topic, byte* payload, unsigned int length)
{
    String msg = "";

    for(int i=0;i<length;i++)
    {
        msg += (char)payload[i];
    }

    Serial.println("========================");
    Serial.print("Topic : ");
    Serial.println(topic);

    Serial.print("Message : ");
    Serial.println(msg);

    Serial.println("========================");

    //---------------------------------------
    // LED
    //---------------------------------------

    if(String(topic)=="smarthome/led")
    {

        if(msg=="ON")
        {
            digitalWrite(LED_PIN,HIGH);
            Serial.println("LED ON");
        }

        else if(msg=="OFF")
        {
            digitalWrite(LED_PIN,LOW);
            Serial.println("LED OFF");
        }

    }

    //---------------------------------------
    // FAN
    //---------------------------------------

    if(String(topic)=="smarthome/fan")
    {

        if(msg=="ON")
        {

            fanManual=true;
            fanStatus=true;

            digitalWrite(FAN_PIN,HIGH);

            Serial.println("Fan Manual ON");

        }

        else if(msg=="OFF")
        {

            fanManual=true;
            fanStatus=false;

            digitalWrite(FAN_PIN,LOW);

            Serial.println("Fan Manual OFF");

        }

        else if(msg=="AUTO")
        {

            fanManual=false;

            Serial.println("Fan AUTO");

        }

    }

}
//======================================================
// CONNECT WIFI
//======================================================

void connectWiFi()
{

    WiFi.mode(WIFI_STA);

    if (WiFi.status() == WL_CONNECTED)
        return;

    //========================
    // WIFI 1
    //========================

    Serial.println("Mencoba WiFi 1...");

    WiFi.begin(ssid1, password1);

    int timeout = 0;

    while (WiFi.status() != WL_CONNECTED && timeout < 20)
    {

        delay(500);
        Serial.print(".");

        timeout++;

    }

    if (WiFi.status() == WL_CONNECTED)
    {

        Serial.println();
        Serial.println("Terhubung ke WiFi 1");

        Serial.print("IP : ");
        Serial.println(WiFi.localIP());

        return;

    }
    //========================
    // WIFI 2
    //========================

    Serial.println();
    Serial.println("WiFi 1 gagal");

    WiFi.disconnect(true);

    delay(1000);

    Serial.println("Mencoba WiFi 2...");

    WiFi.begin(ssid2, password2);

    timeout = 0;

    while (WiFi.status() != WL_CONNECTED && timeout < 20)
    {
        delay(500);
        Serial.print(".");

        timeout++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println();
        Serial.println("Terhubung ke WiFi 2");

        Serial.print("IP : ");
        Serial.println(WiFi.localIP());
    }
    else
    {

        Serial.println();
        Serial.println("Semua WiFi gagal");
    }
}

//======================================================
// CONNECT MQTT
//======================================================

void connectMQTT()
{
    while (!client.connected())
    {
        Serial.println("Menghubungkan MQTT...");

        if (client.connect(
                mqtt_client,
                mqtt_user,
                mqtt_password))
        {
            Serial.println("MQTT Connected");

            client.subscribe("smarthome/led");
            client.subscribe("smarthome/fan");

        }
        else
        {
            Serial.print("MQTT Gagal rc = ");
            Serial.println(client.state());

            vTaskDelay(3000 / portTICK_PERIOD_MS);

        }
    }
}

//======================================================
// TASK WIFI
//======================================================

void TaskWiFi(void *pvParameters)
{
    while (true)
    {
        if (WiFi.status() != WL_CONNECTED)
        {

            Serial.println("[Task WiFi] Reconnect...");

            connectWiFi();

        }

        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

//======================================================
// TASK MQTT
//======================================================

void TaskMQTT(void *pvParameters)
{
    while (true)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            if (!client.connected())
            {

                connectMQTT();

            }

            client.loop();
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);

    }

}
//======================================================
// TASK SENSOR
//======================================================

void TaskSensor(void *pvParameters)
{
    while (true)
    {
        float t = dht.readTemperature();
        float h = dht.readHumidity();

        if (!isnan(t) && !isnan(h))
        {

            // Mengunci data agar task lain tidak membaca saat diubah
            if (xSemaphoreTake(sensorMutex, portMAX_DELAY))
            {

                suhu = t;
                lembab = h;

                xSemaphoreGive(sensorMutex);

            }
            // Publish MQTT
            if (client.connected())
            {

                String payload =
                "{"
                "\"suhu\":" + String(t,1) +
                ",\"lembab\":" + String(h,1) +
                "}";

                client.publish(
                    "smarthome/sensor",
                    payload.c_str()
                );

                Serial.println("--------------------------------");
                Serial.println("Data Sensor");
                Serial.println(payload);
                Serial.println("--------------------------------");

            }
        }
        else
        {
            Serial.println("Gagal membaca DHT22");
        }
        // baca setiap 5 detik
        vTaskDelay(5000 / portTICK_PERIOD_MS);

    }

}

//======================================================
// TASK FAN
//======================================================

void TaskFan(void *pvParameters)
{
    float suhuSekarang = 0;

    while (true)
    {
        if (xSemaphoreTake(sensorMutex, portMAX_DELAY))
        {

            suhuSekarang = suhu;

            xSemaphoreGive(sensorMutex);

        }
        //==========================
        // MODE AUTO
        //==========================

        if (!fanManual)
        {
            if (suhuSekarang >= 30)
            {
                if (!fanStatus)
                {
                    fanStatus = true;

                    digitalWrite(FAN_PIN, HIGH);

                    Serial.println("AUTO FAN ON");
                }

            }
            else
            {
                if (fanStatus)
                {

                    fanStatus = false;

                    digitalWrite(FAN_PIN, LOW);

                    Serial.println("AUTO FAN OFF");

                }
            }
        }

        vTaskDelay(500 / portTICK_PERIOD_MS);

    }

}
//======================================================
// SETUP
//======================================================

void setup()
{

    Serial.begin(115200);

    pinMode(LED_PIN, OUTPUT);
    pinMode(FAN_PIN, OUTPUT);

    digitalWrite(LED_PIN, LOW);
    digitalWrite(FAN_PIN, LOW);

    dht.begin();

    // Membuat Mutex
    sensorMutex = xSemaphoreCreateMutex();

    // Konfigurasi MQTT
    client.setServer(mqtt_broker, 1883);
    client.setCallback(callback);

    //==================================================
    // MEMBUAT TASK
    //==================================================

    // Core 0
    xTaskCreatePinnedToCore(
        TaskWiFi,
        "WiFi Task",
        4096,
        NULL,
        2,
        NULL,
        0
    );

    xTaskCreatePinnedToCore(
        TaskMQTT,
        "MQTT Task",
        6144,
        NULL,
        2,
        NULL,
        0
    );

    // Core 1
    xTaskCreatePinnedToCore(
        TaskSensor,
        "Sensor Task",
        4096,
        NULL,
        1,
        NULL,
        1
    );

    xTaskCreatePinnedToCore(
        TaskFan,
        "Fan Task",
        2048,
        NULL,
        1,
        NULL,
        1
    );
    Serial.println();
    Serial.println("==============================");
    Serial.println(" Smart Home RTOS Started ");
    Serial.println("==============================");

}
//======================================================
// LOOP
//======================================================
void loop()
{
    // Loop kosong karena semua proses berjalan di Task RTOS
    vTaskDelay(portMAX_DELAY);

}
