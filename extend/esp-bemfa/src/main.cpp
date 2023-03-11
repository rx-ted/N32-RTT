#include "PubSubClient.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h>

const char *ssid = "IOT";
const char *password = "2018060332011";
const char *mqtt_server = "bemfa.com";
const int mqtt_server_port = 9501;
#define ID_MQTT "78a469b6a127e35a718ca034632d9729"
const char *topic = "bemfa";
const char *bin_url = "http://bin.bemfa.com/b/1BcNzhhNDY5YjZhMTI3ZTM1YTcxOGNhMDM0NjMyZDk3Mjk=bemfa.bin";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
void turnOnLed();
void turnOffLed();
void blink();

const int b_led = LED_BUILTIN;

// 当升级开始时，打印日志
void update_started()
{
  Serial.println("CALLBACK:  HTTP update process started");
}

// 当升级结束时，打印日志
void update_finished()
{
  Serial.println("CALLBACK:  HTTP update process finished");
}

// 当升级中，打印日志
void update_progress(int cur, int total)
{
  Serial.printf("CALLBACK:  HTTP update process at %d of %d bytes...\n", cur, total);
}

// 当升级失败时，打印日志
void update_error(int err)
{
  Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", err);
}

void updateBin()
{
  Serial.println("start update");

  ESPhttpUpdate.onStart(update_started);     // 当升级开始时
  ESPhttpUpdate.onEnd(update_finished);      // 当升级结束时
  ESPhttpUpdate.onProgress(update_progress); // 当升级中
  ESPhttpUpdate.onError(update_error);       // 当升级失败时

  t_httpUpdate_return ret = ESPhttpUpdate.update(espClient, bin_url);
  switch (ret)
  {
  case HTTP_UPDATE_FAILED: // 当升级失败
    Serial.println("[update] Update failed.");
    client.publish(topic, "[update] Update failed.");
    break;
  case HTTP_UPDATE_NO_UPDATES: // 当无升级
    Serial.println("[update] Update no Update.");
    client.publish(topic, "[update] Update no Update.");

    break;
  case HTTP_UPDATE_OK: // 当升级成功
    Serial.println("[update] Update ok.");
    client.publish(topic, "[update] Update ok.");
    break;
  }
}

void wifi_init()
{
  Serial.println();
  Serial.print("Connecting to ");
  Serial1.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String Mqtt_Buff = "";
  for (unsigned int i = 0; i < length; i++)
  {
    Mqtt_Buff += (char)payload[i];
  }

  if (length < 10)
  {
    // Switch on the LED if an 1 was received as first character
    if (Mqtt_Buff == "on")
    {              // 如果接收字符on，亮灯
      turnOnLed(); // 开灯函数
    }
    else if (Mqtt_Buff == "off")
    {               // 如果接收字符off，亮灯
      turnOffLed(); // 关灯函数
    }
    else if (Mqtt_Buff == "blink")
    {
      blink();
    }
    else if (Mqtt_Buff == "update")
    {
      updateBin();
    }
  }
  else
  {
    Serial.println(">>>");
    Serial.println(Mqtt_Buff);
  }

  Mqtt_Buff = "";
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(ID_MQTT))
    {
      Serial.println("connected");

      client.subscribe(topic); // 修改，修改为你的主题
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void setup()
{
  delay(3000);
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("ESP01S server is startup!");
  pinMode(b_led, OUTPUT);
  wifi_init();
  client.setServer(mqtt_server, mqtt_server_port);
  client.setCallback(callback);
  client.publish("bemfa", "ESP01S server startup.");
  blink();
}
void loop()
{

  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  delay(1000);
}

// 打开灯泡
void turnOnLed()
{
  Serial.println("turn on light");
  digitalWrite(b_led, LOW);
}
// 关闭灯泡
void turnOffLed()
{
  Serial.println("turn off light");
  digitalWrite(b_led, HIGH);
}

void blink()
{
  unsigned int i = 100;
  while (i--)
  {
    delay(50);
    digitalWrite(b_led, LOW);
    delay(50);
    digitalWrite(b_led, HIGH);
  }
}
