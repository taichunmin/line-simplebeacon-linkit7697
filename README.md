# LINE Simple Beacon for Linkit 7697

Arduino code for LINE Simple Beacon work with Linkit 7697

## Requirements

* [Arduino IDE](https://www.arduino.cc/en/Main/Software)
* [MediaTek Linkit 7697](https://labs.mediatek.com/en/platform/linkit-7697)
* Micro-USB to USB Cable
* [Create a channel on the LINE Developers console](https://developers.line.me/en/docs/line-login/getting-started/)

## Installation

Please ensure you have Arduino IDE installed and the board **disconnected**.

1. Open Arduino IDE
2. Go into **Preferences**
3. Add `http://download.labs.mediatek.com/package_mtk_linkit_7697_index.json` as an 'Additional Board Manager URL'
4. Go to **Boards Manager** from the Tools -> Board menu
5. Search for Linkit and install **Linkit 7697**.
6. Download and install the [CP2102N driver](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)

## Setup
1. Connect the **Linkit 7697** board via Micro-USB cable to your computer
2. Go into Tools -> Board and select **Linkit 7697** from the list
3. Under Tools -> Port select the appropriate device *ie. COM1, /dev/cu.SLAB_USBtoUART*
4. Test uploading to the board by uploading an empty sketch to make sure there are no issues.
5. [Issue LINE Simple Beacon Hardware ID](https://manager.line.biz/beacon/register)
    ![](https://i.imgur.com/wHCaMzJ.jpg)
    ![](https://i.imgur.com/lF2lGDO.jpg)
    ![](https://i.imgur.com/INgnfju.jpg)

> If you can not find your channel in new [LINE Official Account Manager Beacon Register](https://manager.line.biz/beacon/register), you can try to register at old [LINE@ Manager Beacon Register](https://admin-official.line.me/beacon/register).
> ![](https://user-images.githubusercontent.com/30001185/50584877-afe5a900-0ea4-11e9-9130-69c3c893a301.png)
> ![](https://user-images.githubusercontent.com/30001185/50584907-e3283800-0ea4-11e9-8f3f-6645e1797785.png)
> ![](https://user-images.githubusercontent.com/30001185/50584909-e7545580-0ea4-11e9-97f2-063cfb1bfd8d.png)

## Upload

1. From this repository, open **sample/sample.ino**
2. Change the `HWID` to your generated HWID.
3. Upload and Enjoy!

## Reference

* https://docs.labs.mediatek.com/resource/linkit7697-arduino/en/developer-guide/using-bluetooth/beacons
* https://github.com/MediaTek-Labs/Arduino-Add-On-for-LinkIt-SDK/blob/a09619ecec2f51fd6d447b0b2c0de0ae3bb950c5/middleware/third_party/arduino/hardware/arduino/mt7697/libraries/LBLE/src/LBLEPeriphral.cpp
* https://github.com/line/line-simple-beacon

## LICENSE

MIT
