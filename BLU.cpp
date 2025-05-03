/*****************
blu.cpp

******************/
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "BLU.h"
#include "Arduino.h"

// 自定义UUID，随意生成或使用在线工具
//TODO 生成随机码
#define SERVICE_UUID "12345678-1234-1234-1234-1234567890AB"
#define CHARACTERISTIC_UUID_RX "12345678-1234-1234-1234-1234567890AC"
#define CHARACTERISTIC_UUID_TX "12345678-1234-1234-1234-1234567890AD"

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristicTx = NULL;
bool deviceConnected = false;
//目前已有客户端数量
int clientCount = 0;

// 回调函数：连接、断开时的处理
class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    Serial.println("BLE device connected.");
    deviceConnected = true;
    clientCount++;
    if (deviceConnected) {
      Serial.println(" 3333cuurent status: true");
    } else {
      Serial.println(" 3333cuurent status: false");
    }
  }

  void onDisconnect(BLEServer* pServer) {
    Serial.println("BLE device disconnected.");
    deviceConnected = false;
    clientCount--;
  }
};

BLU::BLU() {
  Serial.println("BLE start init code.");
}

BLU::~BLU() {
  Serial.println("BLE finish init code.");
}

void BLU::initBlu() {

  // 1. 初始化 BLE
  BLEDevice::init("ESP32-jiahangchun-BLE");
  //获取本机地址
  auto local_address = BLEDevice::getAddress();
  Serial.println("local_address:" + String(local_address.toString().c_str()));

  // 2. 创建BLE服务器
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // 3. 创建服务
  BLEService* pService = pServer->createService(SERVICE_UUID);

  // 4. 在该服务下创建一个可读写的Characteristic
  pCharacteristicTx = pService->createCharacteristic(
    CHARACTERISTIC_UUID_TX,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_WRITE);

  // 5. 为Characteristic添加描述（可选）
  pCharacteristicTx->addDescriptor(new BLE2902());

  // 6. 启动服务
  pService->start();

  // 7. 设为可被Central发现、连接
  BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  BLEDevice::startAdvertising();

  Serial.println("BLE Peripheral set up. Waiting for connections...");
}

void BLU::loopBlu() {
  static int count = 0;
  if (deviceConnected) {
    count++;
    String data = "Msg count: " + String(count);
    pCharacteristicTx->setValue(data.c_str());
    pCharacteristicTx->notify();
    Serial.println("Notify data: " + data);
  }
  if (deviceConnected) {
    Serial.println(" 222cuurent status: true");
  } else {
    Serial.println(" 222cuurent status: false");
  }
}

bool BLU::getConnectState() {
  return deviceConnected;
}
