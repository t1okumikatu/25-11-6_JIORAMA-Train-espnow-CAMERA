#include <esp_now.h>
#include <WiFi.h>
#include "src/constant.h"

// Station（親）の STAモードMACアドレス
uint8_t stationAddress[] = {0xA0, 0xB7, 0x65, 0x58, 0x7A, 0xFC};

// データ構造体
typedef struct struct_message {
  //int command;
  float voltage;
} struct_message;
struct_message sendData;
//struct_message recvData;


// ===== 受信コールバック =====
/*
void OnDataRecv(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
  memcpy(&recvData, incomingData, sizeof(recvData));
  Serial.print("[Recv Command] ");
  Serial.println(recvData.command);
  switch (recvData.command) {
    case 0: Serial.println("停止"); break;
    case 1: Serial.println("前進"); break;
    case 2: Serial.println("後退"); break;
    default: break;
  }
}*/

// ===== 送信完了コールバック =====
void OnDataSent(const wifi_tx_info_t *info, esp_now_send_status_t status) {
  //Serial.print("Send Status: ");
  //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}
void setup() {
  Serial.begin(115200);
  delay(1000);
  ledcAttachChannel(in1, freq, resolution,ch1);
  ledcAttachChannel(in2, freq, resolution,ch2);

  APSTA();
  nowpeer();
  }

void loop() {
  readV();
  forward(170);
  //brake();
  delay(2000);
}

