#include <esp_now.h>
#include <WiFi.h>

// 列車（ESP32-S3）の STAモードMACアドレスを入力　
//uint8_t trainAddress[] = {0x98, 0x3D, 0xAE, 0x60, 0x05, 0x38};

// データ構造体
typedef struct struct_message {
  //int command;     // 0=停止, 1=前進, 2=後退など
  float voltage;   // 電圧（列車からの返信用）
} struct_message;

//struct_message sendData;
struct_message recvData;

// === 受信コールバック ===incomingDataをrecvDataに
void OnDataRecv(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
  memcpy(&recvData, incomingData, sizeof(recvData));
  Serial.print("受信電圧Voltage] ");
  Serial.print(recvData.voltage, 2);
  Serial.println(" V");
}

// === 送信完了コールバック ===
/*
void OnDataSent(const wifi_tx_info_t *info, esp_now_send_status_t status) {
  Serial.print("Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}*/
void setup() {
  Serial.begin(115200);
  delay(1000);
  APSTA();
  

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed!");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
  //esp_now_register_send_cb(OnDataSent);
/*
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, trainAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
*/
  Serial.println("Station Ready (Waiting for Train...)");
}

void loop() {
  // 定期的にコマンド送信（1秒ごと）
  /*
  static unsigned long prevMillis = 0;
  if (millis() - prevMillis > 1000) {
    prevMillis = millis();
    sendData.command = 1;  // 1 = 前進コマンド（任意）
    esp_err_t result = esp_now_send(trainAddress, (uint8_t *)&sendData, sizeof(sendData));
    Serial.println(result == ESP_OK ? "[Send] OK" : "[Send] FAIL");
  }*/
  delay(1000);
}
