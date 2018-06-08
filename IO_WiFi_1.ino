// Ehsan Sarhadi
// An Arduino IDE library for using Telegram Bot
// Control ESP8266 Module with Telegram Bot


#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Initialize Wifi connection to the router
char ssid[] = " ??? ";     
char password[] = " ??? ";

// Initialize Telegram BOT
#define BOTtoken " ??? " //  Telegram Token

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 1000;
long Bot_lasttime;  
bool Start = false;

const int relay1 = D1;
const int relay2 = D2;
const int relay3 = D3;
const int relay4 = D4;
int relaystatus = 0;

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));


  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    
    if (text == "/hi_digi") {
        bot.sendChatAction(chat_id, "typing");
        delay(4000);
        bot.sendMessage(chat_id, "Hi which room light?");
    }

          if (text == "1") {
      digitalWrite(relay1, LOW);   // turn the LED on (HIGH is the voltage level)
      relaystatus = 1;
      bot.sendMessage(chat_id, "Room 1 is on", "");
          }

       if (text == "11") {
      digitalWrite(relay1, HIGH);    // turn the LED off (LOW is the voltage level)
      relaystatus = HIGH;
      bot.sendMessage(chat_id, "Room 1 turned OFF", "");
       }

          if (text == "2") {
      digitalWrite(relay2, LOW);   // turn the LED on (HIGH is the voltage level)
      relaystatus = 1;
      bot.sendMessage(chat_id, "Room 2 is on", "");
          }

       if (text == "22") {
      digitalWrite(relay2, HIGH);    // turn the LED off (LOW is the voltage level)
      relaystatus = HIGH;
      bot.sendMessage(chat_id, "Room 2 turned OFF", "");
       }

          if (text == "3") {
      digitalWrite(relay3, LOW);   // turn the LED on (HIGH is the voltage level)
      relaystatus = 1;
      bot.sendMessage(chat_id, "Room 3 is on", "");
          }

       if (text == "33") {
      digitalWrite(relay3, HIGH);    // turn the LED off (LOW is the voltage level)
      relaystatus = HIGH;
      bot.sendMessage(chat_id, "Room 3 turned OFF", "");
       }

       
          if (text == "4") {
      digitalWrite(relay4, LOW);   // turn the LED on (HIGH is the voltage level)
      relaystatus = 1;
      bot.sendMessage(chat_id, "Room 4 is on", "");
          }

       if (text == "44") {
      digitalWrite(relay4, HIGH);    // turn the LED off (LOW is the voltage level)
      relaystatus = HIGH;
      bot.sendMessage(chat_id, "Room 4 turned OFF", "");
       }

 if (text == "1" ) {
        bot.sendChatAction(chat_id, "typing");
        delay(4000);
        bot.sendMessage(chat_id, "oh, Thats great, check Digispark.ir");
 }
        if (text == "3" ) {
        bot.sendChatAction(chat_id, "typing");
        delay(4000);
        bot.sendMessage(chat_id, "oh, Thats great, check digispark.ir/w5100-running-arduino-ip-printing/");
 }
 if (text == "no") {
        bot.sendChatAction(chat_id, "typing");
        delay(4000);
        bot.sendMessage(chat_id, "Ok, How about digispark.ir/telegram-bot-iot-arduino/");
 }
    

    if (text == "/start") {
      String welcome = "Welcom to Digispark onlie IOT Chat" + from_name + ".\n";
      welcome += "/hi_digi : This is Digispark IOT Chat.\n\n";
      bot.sendMessage(chat_id, welcome);
    }
  }
}


void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  pinMode(D1, OUTPUT); // initialize digital ledPin as an output.
  delay(10);
  digitalWrite(relay1, HIGH); // initialize pin as off

  pinMode(D2, OUTPUT); // initialize digital ledPin as an output.
  delay(10);
  digitalWrite(relay2, HIGH); // initialize pin as off

  pinMode(D3, OUTPUT); // initialize digital ledPin as an output.
  delay(10);
  digitalWrite(relay3, HIGH); // initialize pin as off

  pinMode(D4, OUTPUT); // initialize digital ledPin as an output.
  delay(10);
  digitalWrite(relay4, HIGH); // initialize pin as off


  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
}
