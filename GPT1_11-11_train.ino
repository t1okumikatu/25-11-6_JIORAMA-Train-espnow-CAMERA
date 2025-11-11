#include <esp_now.h>
#include <WiFi.h>

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
  Serial.print("Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}
void setup() {
  Serial.begin(115200);
  delay(1000);
  APSTA();

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed!");
    return;
  }

  //esp_now_register_recv_cb(OnDataRecv);
  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, stationAddress, 6);
  peerInfo.channel = 1;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("peer失敗");
    return;
  }

  Serial.println("Train Ready (listening for commands...)");
}

void loop() {
  readV();
  delay(2000);
}

