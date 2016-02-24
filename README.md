mruby-gpio-bbb
=====================
- GPIO mrbgem for BeagleBoneBlack

##Installation
- Download mruby

        git clone http://github.com/mruby/mruby


- Edit mruby/build\_config.rb  
Insert the following one line after "conf.gembox 'default'" in `build_config.rb`

        conf.gem :github => 'https://github.com/kout08/mruby-gpio-bbb'


- Build mruby

        make

Method list
----------------------
###Gpio.pinMode(int pin, int mode)
- Setting pin mode INPUT or OUTPUT
- Parameters

        pin  : the pin number
        mode : GPIO::INPUT or GPIO::OUTPUT

- Returns 

        None

###Gpio.digitalWrite(int pin, int value)
- Write HIGH or LOW value to a digital pin
- Parameters

        pin   : the pin number
        value : GPIO::HIGH or GPIO::LOW

- Returns

        None

### Gpio.digitalRead(int pin)
- Reads the value from a digital pin, either HIGH or LOW.
- Parameters

        pin : the pin number

- Returns

        1(HIGH) or 0(LOW)
