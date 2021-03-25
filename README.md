# agility_trainer

<br>
<p align="center">
  <img src="https://user-images.githubusercontent.com/44078452/112398594-4ea78b80-8ce3-11eb-8e08-b5a89963784e.gif" alt="animated" />
</p>
<br>

## Table of Contents

- [Description](#description)
- [Working Principle](#working-principle)
- [Construction](#construction)
  - [List of Components](#list-ofcComponents)
  - [Schematic](#schematic)
  - [Connections](#connections)
- [Operating Modes](#operating-modes)
  - [1- Solo](#1--solo)
  - [2- Radio Controlled](2-radio-controlled)
  - [3- Randomly Generated Sequence](3--randomly-generated-sequence)
  - [4- Autonomous Random Selection](4--autonomous-random-selection)
<br>
<br>

## Description

This project was based on [this kind of device.](https://www.youtube.com/watch?v=AvRM1_2BJDQ)

Agility trainers are small wirelessly communicating devices that shine lights in sequence. Depending on the color of the light, the user must do an action. Once the action is completed, the current device changes color and a new device gets a new color as well to indicate to the user what action he/she must do.

Colors can be changed randomly and autonomously by the devices themselves, or they can be preprogrammed as a sequence of which device and which color should be picked at each time or a person with a remote can choose the device and color.
<br>
<br>
<br>

## Working Principle

Each device is comprised of an [RF-NANO](https://www.embeddedcomputing.com/technology/processing/for-the-professional-maker-getting-started-with-the-rf-nano-arduino-nrf24l01-combo) micro controller (based on the [Arduino Nano](https://www.arduino.cc/en/pmwiki.php?n=Main/ArduinoBoardNano)), which has an on board nRF24L01 wireless transceiver, capable of wireless communication, in addition, they also have an IR proximity sensor and at least one RGB LED. Optionally, you can add a buzzer to make sounds.

Initially, all devices are in idle mode, with a static color (in my case, magenta). Once one of the devices changes color, the user must take the corresponding action. Each action can have a different feedback (i.e.: time since the color changed, the user touching the device or a radio signal). Once the feedback is returned, the device sends a wireless signal to the others, telling them that the action was completed. This signal can also contain the next device to be activated and with which color. The cycle repeats.

## Construction

#### List of Components:
* [RF-NANO](https://www.aliexpress.com/i/32980796969.html?albagn=888888&&src=google&albch=search&acnt=479-062-3723&isdl=y&aff_short_key=UneMJZVf&albcp=12368716241&albag=118463975912&slnk=&trgt=dsa-42862830006&plac=&crea=499556369737&netw=g&device=c&mtctp=b&memo1=&albbt=Google_7_search&aff_platform=google&gclid=CjwKCAjwxuuCBhATEiwAIIIz0c9ig4hvKiucy0oishyY9e06ONHDCcG3aNFU0sxL3ObZKQKujlwlmRoCA1MQAvD_BwE&gclsrc=aw.ds)
* [IR proximity sensor](https://www.banggood.com/1pcs-TCRT5000-950mm-5V-3A-Infrared-Reflective-Optical-Sensor-For-Tracking-Car-p-1160588.html?cur_warehouse=CN&rmmds=search)
* [RGB LEDs (common cathode)](https://www.banggood.com/50pcs-LED-RGB-Common-Cathode-4-Pin-F5-5MM-Diode-p-1016398.html?cur_warehouse=CN&rmmds=search)
* [Resistor Kit](https://www.banggood.com/560-Pcs-1-ohm-to-10M-ohm-1-or-4W-5-pencent-Metal-Film-Resistor-56-Value-Assorted-Kit-p-1072159.html?cur_warehouse=CN&rmmds=search) (we only need 1x10K, 1x1K and 2x200R)
<br>
<br>

#### Schematic:

<p align="center">
  <img src="https://user-images.githubusercontent.com/44078452/112412309-13b25180-8cfd-11eb-9256-f0600568e850.png" />
</p>


_yes, i made this using paint_
<br>
<br>

#### Connections:
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
<br>
<br>

#### IMPORTANT:
As of today, the circuit used for this project isn't optimized at all. For example, each pin of the RGB LEDs should have a resistor, instead of only one being connected between the cathode and GND. The resistor in the buzzer can also be changed and maybe the buzzer could be controlled with a transistor to make it louder. If many RGB LEDs are used, it is also a good idea to drive it with a transistor. Feel free to adapt everything suggested here.
<br>
<br>
<br>

## Operating Modes

Each of the operating modes has an Arduino sketch. You can simply clone this repository and try the different codes.

It is important to change the `device_number` to your device's number. For example: if you made 3 devices, name one of them as 1, the other one as 2 and another as 3. Before uploading the code, choose `device_number` according to the device you are programming.

### 1- Solo
<p align="center">
  <img src="https://user-images.githubusercontent.com/44078452/112419098-8b867900-8d09-11eb-811f-66cbfe94d00e.gif" alt="animated" />
</p>

The device randomly picks a color and waits until the suitable action is done by the user. After that, another color is picked and the cycle goes on.
<br>
<br>

### 2- Radio Controlled
<p align="center">
  <img src="https://user-images.githubusercontent.com/44078452/112419179-b40e7300-8d09-11eb-8171-e15e9aec2ec9.gif" alt="animated" />
</p>

A coach or any other person has a remote and chooses the order in which the lights will shine and with which color.
<br>
<br>

### 3- Randomly Generated Sequence

One of the devices acts as a master while the other ones, as slaves. The master generates a random sequence with the order and colors that will be picked and stores it in an array. After that, the master executes this sequence, telling the other devices when they should light up.

<br>
<br>

### 4- Autonomous Random Selection
<p align="center">
  <img src="https://user-images.githubusercontent.com/44078452/112417217-d69e8d00-8d05-11eb-8c97-63810ac0e3c0.png" />
</p>

Similarly to the [Randomly Generated Sequence](#3--randomly-generated-sequence), this mode also has a master and slaves, however, the master changes and is always the device which is active. Once the demanded action is completed, it chooses another device to be the master and the loop continues.

This mode is functionally very similar to the [Randomly Generated Sequence](#3--randomly-generated-sequence)... Therefore, maybe it shouldn't even be implemented.
