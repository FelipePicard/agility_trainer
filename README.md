# agility_trainer

<br>
<p align="center">
  <img src="https://user-images.githubusercontent.com/44078452/112398594-4ea78b80-8ce3-11eb-8e08-b5a89963784e.gif" alt="animated" />
</p>
<br>

## description

This project was based on [this kind of device.](https://www.youtube.com/watch?v=AvRM1_2BJDQ)

Agility trainers are small wirelessly communicating devices that shine lights in sequence. Depending on the color of the light, the user must do an action. Once the action is completed, the current device changes color and a new device gets a new color as well to indicate to the user what action he/she must do.

Colors can be changed randomly and autonomously by the devices themselves, or they can be preprogrammed as a sequence of which device and which color should be picked at each time or a person with a remote can choose the device and color.


## construction

Each device is comprised of an [RF-NANO](https://www.embeddedcomputing.com/technology/processing/for-the-professional-maker-getting-started-with-the-rf-nano-arduino-nrf24l01-combo) micro controller (based on the [Arduino Nano](https://www.arduino.cc/en/pmwiki.php?n=Main/ArduinoBoardNano)), which has an on board nRF24L01, capable of wireless communication, in addition, they also have an IR proximity sensor and at least one RGB LED. Optionally, you can add a buzzer to make sounds.

##### List of Components:
* [RF-NANO](https://www.aliexpress.com/i/32980796969.html?albagn=888888&&src=google&albch=search&acnt=479-062-3723&isdl=y&aff_short_key=UneMJZVf&albcp=12368716241&albag=118463975912&slnk=&trgt=dsa-42862830006&plac=&crea=499556369737&netw=g&device=c&mtctp=b&memo1=&albbt=Google_7_search&aff_platform=google&gclid=CjwKCAjwxuuCBhATEiwAIIIz0c9ig4hvKiucy0oishyY9e06ONHDCcG3aNFU0sxL3ObZKQKujlwlmRoCA1MQAvD_BwE&gclsrc=aw.ds)
* [IR proximity sensor](https://www.banggood.com/1pcs-TCRT5000-950mm-5V-3A-Infrared-Reflective-Optical-Sensor-For-Tracking-Car-p-1160588.html?cur_warehouse=CN&rmmds=search)
* [RGB LEDs (common cathode)](https://www.banggood.com/50pcs-LED-RGB-Common-Cathode-4-Pin-F5-5MM-Diode-p-1016398.html?cur_warehouse=CN&rmmds=search)
* [Resistor Kit](https://www.banggood.com/560-Pcs-1-ohm-to-10M-ohm-1-or-4W-5-pencent-Metal-Film-Resistor-56-Value-Assorted-Kit-p-1072159.html?cur_warehouse=CN&rmmds=search) (we only need 1x10K, 1x1K and 2x200R)
<br>

#### Schematic:

<p align="center">
  <img src="https://user-images.githubusercontent.com/44078452/112412309-13b25180-8cfd-11eb-9256-f0600568e850.png" />
</p>
<p> _ yes, i made this using paint _ </p>

##### connections:
- RGB LED
  - redPin - D3
  - greenPin - D5
  - bluePin - D6
  - RGB LED's cathode - 1K resistor to GND
- IR Sensor (better to just follow the image)
  - black diode's annode - 5V
  - blue diode's annode - 5V
  - black diode's cathode - A6 and 10K resistor to GND
  - blue diode's cathode - 200R resistor to GND
- Buzzer
  - one pin - GND
  - other pin - 200R resistor going to A3


## operating modes
