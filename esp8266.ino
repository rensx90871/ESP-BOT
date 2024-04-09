#include <datatypes.h>
#include <WiFiClient.h>
#include <utils.h>
#include <string>
#include <FastBot.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#define WIFI_SSID "TP-Link_AC5C"
#define WIFI_PASS "99931728"
#define BOT_TOKEN "6435083940:AAGMSQN1fn1891vLicfYMAGbLk0cDCq_LjM"
FastBot bot(BOT_TOKEN);
HTTPClient http;
WiFiClient wifiClient;

//переменные
String monday[8] = { "0.Разговор о важном", "1.Алгебра", "2.Англ.яз", "3.ТВИС", "4.Алгебра", "5.История", "6.Литература", "7.Физика" };
String tuesday[8] = { "0", "1.Геометрия", "2.Физ-ра", "3.Русский яз.", "4.Общество", "5.Физика", "6.Биология", "7.Индивидуальный проект" };
String wednesday[8] = { "0", "1", "2.Литература", "3.Англ.яз", "4.Геометрия", "5.Химия", "6.Физика", "7.История" };
String thursday[8] = { "0.Профмин", "1.Информатика", "2.Русский.яз", "3.ОБЖ", "4.Алгебра", "5.Алгебра", "6.Физика", "7.Общество" };
String friday[8] = { "0", "1.Англ.яз", "2.Литература", "3.География", "4.Физика", "5.Геометрия", "6.Физ-ра", "7.КНКБР" };
String call[8] = { "0.08:00-08:20", "1.08:30-09:10", "2.09:20-10:00", "3.10:15-10:55", "4.11:10-11:50", "5.12:05-12:45", "6.13:00-13:40", "7.13:55-14:35" };


void setup() {
  connectWiFi();
  bot.attach(new2Msg);
}


void new2Msg(FB_msg& msg) {
  if (msg.OTA && msg.chatID == "718856532") bot.update();
  else if (msg.text == "/start") {
    bot.sendMessage("Привет, это бот созданный для физмата 10А класса", msg.chatID);
  } else if (msg.text == "/lesson0schedule") {
    FB_Time t(msg.unix, 3);  // передали unix и часовой пояс
    uint8_t day = t.dayWeek;
    if (day == 1) {
      int i;
      for (i = 0; i < 8; i = i + 1) {
        bot.sendMessage(monday[i], msg.chatID);
      }
    } else if (day == 2) {
      int i;
      for (i = 0; i < 8; i = i + 1) {
        bot.sendMessage(tuesday[i], msg.chatID);
      }
    } else if (day == 3) {
      int i;
      for (i = 0; i < 8; i = i + 1) {
        bot.sendMessage(wednesday[i], msg.chatID);
      }
    } else if (day == 4) {
      int i;
      for (i = 0; i < 8; i = i + 1) {
        bot.sendMessage(thursday[i], msg.chatID);
      }
    } else if (day == 5) {
      int i;
      for (i = 0; i < 8; i = i + 1) {
        bot.sendMessage(friday[i], msg.chatID);
      }
    } else if (day > 5) {
      bot.sendMessage("Уроков нет", msg.chatID);
    }
  } else if (msg.text == "/call0schedule") {
    int i;
    for (i = 0; i < 8; i = i + 1) {
      bot.sendMessage(call[i], msg.chatID);
    }
  } else if (msg.text == "/next0lesson") {
    FB_Time t(msg.unix, 3);
    String d[8];
    if (t.dayWeek == 1) {
      for (int i = 0; i < 9; i++) {
        d[i] = monday[i];
      }
    } else if (t.dayWeek == 2) {
      for (int i = 0; i < 9; i++) {
        d[i] = tuesday[i];
      }
    } else if (t.dayWeek == 3) {
      for (int i = 0; i < 9; i++) {
        d[i] = wednesday[i];
      }
    } else if (t.dayWeek == 4) {
      for (int i = 0; i < 9; i++) {
        d[i] = thursday[i];
      }
    } else if (t.dayWeek == 5) {
      for (int i = 0; i < 9; i++) {
        d[i] = friday[i];
      }
    }
    if (t.hour <= 7) bot.sendMessage(d[0], msg.chatID);
    else if (t.hour == 8 && t.minute < 30) bot.sendMessage(d[1], msg.chatID);
    else if ((t.hour == 8 && t.minute >= 30) or (t.hour == 9 && t.minute < 20)) bot.sendMessage(d[2], msg.chatID);
    else if ((t.hour == 9 && t.minute >= 20) or (t.hour == 10 && t.minute < 15)) bot.sendMessage(d[3], msg.chatID);
    else if ((t.hour == 10 && t.minute >= 15) or (t.hour == 11 && t.minute < 10)) bot.sendMessage(d[4], msg.chatID);
    else if ((t.hour == 11 && t.minute >= 10) or (t.hour == 12 && t.minute < 5)) bot.sendMessage(d[5], msg.chatID);
    else if ((t.hour == 12 && t.minute >= 5) or (t.hour == 13 && t.minute == 0)) bot.sendMessage(d[6], msg.chatID);
    else if ((t.hour == 13 && t.minute >= 0) and (t.hour == 13 && t.minute < 55)) bot.sendMessage(d[7], msg.chatID);
    else if ((t.hour == 13 && t.minute >= 55) or (t.hour == 14 && t.minute < 35)) bot.sendMessage("Домой", msg.chatID);
    else bot.sendMessage("Уроков нет", msg.chatID);
  } else if (msg.text == "/how0long0until0the0bell") {
    FB_Time t(msg.unix, 3);
    if (t.hour <= 7) {
      byte hour, minute;
      String ost;
      hour = 8 * 60 + 0 - t.hour * 60 - t.minute;
      minute = hour % 60;
      hour = hour / 60;
      ost += hour;
      ost += "ч";
      ost += minute;
      ost += "м";
    } else if (t.hour == 8 && t.minute < 30) {
      byte hour, minute;
      String ost;
      hour = 8 * 60 + 30 - t.hour * 60 - t.minute;
      minute = hour % 60;
      hour = hour / 60;
      ost += hour;
      ost += "ч";
      ost += minute;
      ost += "м";
      bot.sendMessage(ost, msg.chatID);
    } else if ((t.hour == 8 && t.minute >= 30) or (t.hour == 9 && t.minute < 20)) {
      byte hour, minute;
      String ost;
      hour = 9 * 60 + 20 - t.hour * 60 - t.minute;
      minute = hour % 60;
      hour = hour / 60;
      ost += hour;
      ost += "ч";
      ost += minute;
      ost += "м";
      bot.sendMessage(ost, msg.chatID);
    } else if ((t.hour == 9 && t.minute >= 20) or (t.hour == 10 && t.minute < 15)) {
      byte hour, minute;
      String ost;
      hour = 10 * 60 + 15 - t.hour * 60 - t.minute;
      minute = hour % 60;
      hour = hour / 60;
      ost += hour;
      ost += "ч";
      ost += minute;
      ost += "м";
      bot.sendMessage(ost, msg.chatID);
    } else if ((t.hour == 10 && t.minute >= 15) or (t.hour == 11 && t.minute < 10)) {
      byte hour, minute;
      String ost;
      hour = 11 * 60 + 10 - t.hour * 60 - t.minute;
      minute = hour % 60;
      hour = hour / 60;
      ost += hour;
      ost += "ч";
      ost += minute;
      ost += "м";
      bot.sendMessage(ost, msg.chatID);
    } else if ((t.hour == 11 && t.minute >= 10) or (t.hour == 12 && t.minute < 5)) {
      byte hour, minute;
      String ost;
      hour = 12 * 60 + 5 - t.hour * 60 - t.minute;
      minute = hour % 60;
      hour = hour / 60;
      ost += hour;
      ost += "ч";
      ost += minute;
      ost += "м";
      bot.sendMessage(ost, msg.chatID);
    } else if ((t.hour == 12 && t.minute >= 5) or (t.hour == 13 && t.minute == 0)) {
      byte hour, minute;
      String ost;
      hour = 13 * 60 - t.hour * 60 - t.minute;
      minute = hour % 60;
      hour = hour / 60;
      ost += hour;
      ost += "ч";
      ost += minute;
      ost += "м";
      bot.sendMessage(ost, msg.chatID);
    } else if ((t.hour == 13 && t.minute >= 0) or (t.hour == 13 && t.minute < 55)) {
      byte hour, minute;
      String ost;
      hour = 13 * 60 + 55 - t.hour * 60 - t.minute;
      minute = hour % 60;
      hour = hour / 60;
      ost += hour;
      ost += "ч";
      ost += minute;
      ost += "м";
      bot.sendMessage(ost, msg.chatID);
    } else if ((t.hour == 13 && t.minute >= 55) or (t.hour == 14 && t.minute < 35)) {
      byte hour, minute;
      String ost;
      hour = 14 * 60 + 35 - t.hour * 60 - t.minute;
      minute = hour % 60;
      hour = hour / 60;
      ost += hour;
      ost += "ч";
      ost += minute;
      ost += "м";
      bot.sendMessage(ost, msg.chatID);
    } else bot.sendMessage("Уроков нет", msg.chatID);
  } else if (msg.text == "/post") {
    http.begin(wifiClient, "https://school.07.edu.o7.com/auth/login-page");
    http.addHeader("username", "/auth/login");
    String httpRequestData = "Кобылянский2007";
    int httpResponseCode = http.POST(httpRequestData);
    http.addHeader("password", "/auth/login");
    String httpRequestData2 = "CACnhWgb";
    int httpResponseCode2 = http.POST(httpRequestData2);
    String payload = http.getString();
    String s = String(httpResponseCode, DEC);
    String s2 = String(httpResponseCode2, DEC);
    bot.sendMessage(s, msg.chatID);
    bot.sendMessage(s2, msg.chatID);
    bot.sendMessage(payload, msg.chatID);
  }
}

void connectWiFi() {  //подключение к интернету
  delay(2000);
  Serial.begin(115200);
  Serial.println();
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 15000) ESP.restart();
  }
  Serial.println("Connected");
}

//функции команд


void loop() {
  // put your main code here, to run repeatedly:
  bot.tick();
}
