#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "";
const char* password = "";
const char* mqtt_server = "";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

bool verboseWifi = false;
bool runLed = false;

void setup_wifi(bool verboseWifi);
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    setup_wifi(verboseWifi);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    // put your main code here, to run repeatedly:
    if (!client.connected()) {
      reconnect();
    }
    if (runLed) {
      digitalWrite(LED_BUILTIN, LOW);  // LED on
      delay(5000);
      digitalWrite(LED_BUILTIN, HIGH); // LED off
      delay(5000);
    } else {
      digitalWrite(LED_BUILTIN, HIGH); // LED off
    }

}

void setup_wifi(bool verboseWifi) {

  Serial.println();
  Serial.printf("Connecting to %s.", ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.printf("Connected, IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("WiFi mode set to WIFI_STA %s\n", WiFi.mode(WIFI_STA) ? "" : "Failed!");

  if (verboseWifi) {WiFi.printDiag(Serial);}
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED is a 1 was recieved as first char
  if ((char)payload[0] == '1') {
    digitalWrite(LED_BUILTIN, LOW); // Turn LED on
  } else {
    digitalWrite(LED_BUILTIN, HIGH); // Turn LED off
  }
}

void reconnect() {
  // Loop until reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish connected state:
      client.publish(const char *topic, const char *payload)
    }
    
  }
}
