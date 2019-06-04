#include <LBLE.h>
#include <LBLEPeriphral.h>

#define HWID "0123456789"

class MyLBLEAdvertisementData : public LBLEAdvertisementData
{
public:
  int htoi(unsigned char c)
  {
    if ('0' <= c && c <= '9')
      return c - '0';
    if ('A' <= c && c <= 'F')
      return c - 'A' + 10;
    if ('a' <= c && c <= 'f')
      return c - 'a' + 10;
    return -1;
  }

  void configAsLINEBeacon(const String &hwid, const String &device_message)
  {
    // check hwid
    if (hwid.length() != 10)
      return;
    for (int i = 0; i < 10; i++)
      if (htoi(hwid[i]) == -1)
        return;

    // remove all existing AD
    LBLEAdvertisementData();

    LBLEAdvDataItem item;

    // flag
    item.clear();
    item.adType = BT_GAP_LE_AD_TYPE_FLAG;
    item.adData[0] = BT_GAP_LE_AD_FLAG_BR_EDR_NOT_SUPPORTED | BT_GAP_LE_AD_FLAG_GENERAL_DISCOVERABLE;
    item.adDataLen = 1;
    addAdvertisementData(item);

    // LINE Corp UUID
    item.clear();
    item.adType = BT_GAP_LE_AD_TYPE_16_BIT_UUID_COMPLETE;
    *(uint16_t *)item.adData = 0xFE6F;
    item.adDataLen = 2;
    addAdvertisementData(item);

    // Service Data
    item.clear();
    item.adType = BT_GAP_LE_AD_TYPE_SERVICE_DATA;
    uint8_t *pData = item.adData;
    // SERVICE UUID for LINE CORP
    *(uint16_t *)item.adData = 0xFE6F;
    pData += 2;
    // Frame Type of the LINE Simple Beacon Frame
    *pData++ = 0x02;
    // HWID of LINE Simple Beacon
    for (int i = 0; i < 5; i++)
    {
      *pData++ = (uint8_t)((htoi(hwid[2 * i]) << 4) + htoi(hwid[2 * i + 1]));
    }
    // Measured TxPower of the LINE Simple Beacon Frame
    *pData++ = 0x7F;
    // Device message of LINE Simple Beacon Frame
    const size_t device_message_len = std::min((size_t)13, (size_t)device_message.length());
    if (device_message_len)
    {
      memcpy(pData, device_message.c_str(), device_message_len);
      pData += device_message_len;
    }
    // item len
    item.adDataLen = (pData - item.adData);
    addAdvertisementData(item);
  }
};

String LBLEAddressToDeviceMessage(const LBLEAddress &btAddr)
{
  char buf[13] = {};
  sprintf(buf, "%02X%02X%02X%02X%02X%02X",
          btAddr.m_addr.addr[5],
          btAddr.m_addr.addr[4],
          btAddr.m_addr.addr[3],
          btAddr.m_addr.addr[2],
          btAddr.m_addr.addr[1],
          btAddr.m_addr.addr[0]);
  return String(buf);
}

void setup()
{
  // init
  Serial.begin(9600);
  LBLE.begin();
  while (!LBLE.ready())
  {
    delay(100);
  }
  Serial.print("LBLEAddresss: ");
  Serial.println(LBLE.getDeviceAddress());

  // config as LINE Beacon
  MyLBLEAdvertisementData beaconData;
  beaconData.configAsLINEBeacon(HWID, LBLEAddressToDeviceMessage(LBLE.getDeviceAddress()));
  LBLEPeripheral.advertise(beaconData);

  Serial.print("LINE HWID: ");
  Serial.println(HWID);
}

void loop()
{
  // The underlying framework will advertise periodically.
  // we simply wait here.
  delay(3000);
}
