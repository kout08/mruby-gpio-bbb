mruby-gpio-bbb
=====================
- Beale Bone Black用のmruby汎用入出力ライブラリ

##インストール方法
- mrubyをダウンロードする

        git clone http://github.com/mruby/mruby

- mruby/build\_config.rb の conf.gembox 'default' の次の行に、下記の設定を追加する

        conf.gem :github => 'https://github.com/kout08/mruby-gpio-bbb'
- mrubyをビルドする

        make

使用可能なメソッド
----------------------
###Gpio.pinMode(int pin, int mode)
- ピンの動作を入力または出力として設定する  
- パラメータ

        pin  : 設定したいピンの番号
        mode : 入力はGPIO::INPUT、出力はGPIO::OUTPUTを指定

- 戻り値 

        なし(エラーの場合は-1を返す)

###Gpio.digitalWrite(int pin, int value)
- ピンの出力をHIGHかLOWに指定する  
- パラメータ

        pin   : 設定したいピンの番号
        value : HIGHの場合はGPIO::HIGH、LOWの場合はGPIO::LOW

- 戻り値

        なし(エラーの場合は-1を返す)

### Gpio.digitalRead(int pin)
- 指定したピンの値を読み取る
- パラメータ

        pin : 読み取りたいピンの番号

- 戻り値

        HIGHなら1、LOWなら0を返す
