# M5Core2_SG90_StackChan_BTSPK
Bluetooth Speaker StackChan

@mongonta555 さんが[ｽﾀｯｸﾁｬﾝ M5GoBottom版組み立てキット](https://raspberrypi.mongonta.com/about-products-stackchan-m5gobottom-version/ "Title")の頒布を始められたので、それに対応したBluetooth Speakerｽﾀｯｸﾁｬﾝファームを作りました。<br>

![画像ataru](images/ataru.png)<br>

---
### M5GoBottom版ｽﾀｯｸﾁｬﾝ本体を作るのに必要な物、及び作り方 ###
こちらを参照してください。<br>
* [ｽﾀｯｸﾁｬﾝ M5GoBottom版組み立てキット](https://raspberrypi.mongonta.com/about-products-stackchan-m5gobottom-version/ "Title")<br>

### このプログラムをビルドするのに必要な物 ###
* Arduino IDE (バージョン 1.8.15で動作確認をしました。)<br>
* [M5Stack-Avatar](https://github.com/meganetaaan/m5stack-avatar/ "Title")ライブラリ(バージョン 0.7.4で動作確認をしました。)<br>
* [ServoEasing](https://github.com/ArminJo/ServoEasing/ "Title")ライブラリ(バージョン 2.4.0で動作確認をしました。)<br>
* [ESP32Servo](https://github.com/madhephaestus/ESP32Servo/ "Title")ライブラリ(バージョン 0.9.0で動作確認をしました。)<br>
* [ESP32-A2DP](https://github.com/pschatzmann/ESP32-A2DP/ "Title")ライブラリ<br>
<br>

### M5Stack-Avatarライブラリを変更する ###
Windows11の場合はライブラリのソースはここにあります。<br>
C:\Users\ユーザー名\Documents\Arduino\libraries\m5stack-avatar<br>

* "Avatar.cpp""Avatar.h"の下図赤枠部分を追加します。
![画像2](images/image2.png)<br><br><br>
![画像3](images/image3.png)<br><br><br>
* "DrawContext.h"の下図赤枠部分を変更します。
![画像4](images/image4.png)<br><br><br>

### ESP32-A2DPライブラリを変更する ###
* "BluetoothA2DPSink.cpp"の下図赤枠部分を追加します。<br>
![画像1](images/image5.png)<br>
<br><br>

---
### M5Stack-SD-Updaterに対応させる場合 ###

* [M5Stack-SD-Updater](https://github.com/tobozo/M5Stack-SD-Updater/ "Title")ライブラリが必要です。<br>
* "M5Core2_SG90_StackChan_BTSPK.ino"の17行目のコメントを外して"#define USE_SD_UPDATER"を有効にします。<br>

M5Stack-SD-Updaterの使い方はこちらを参照してください。：<https://github.com/tobozo/M5Stack-SD-Updater>


---

### 使い方 ###
* スマホなどでペアリングを選択すると"Avatar"というデバイスが表示されるので選択して接続してください。<br>
* M5Stack Core2のボタンA,B,Cを押すと、それぞれ異なった顔を表示します。　<br>
<br><br>

