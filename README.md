# ChunithmIO Lightning Model

Use a Chunithm control panel on PC!

This fork adds reactive lightning to the air towers, and in the future maybe some on-boot preset settings selection.

Oh and the pinout is slightly changed from the upstream, to work with a Pro Micro board.

## Overview

The Chunithm panel is made of air towers and a ground slider.
3
### Air towers

The air towers are made of 6 photo interrupters and 2 LED strips which can be interfaced with an Arduino. See `ChunithmIO` for a firmware example which turns them into a keyboard device.

In this example, each IR sensor responds 1:1 to a key, i.e. when covered, the key is pressed, and when uncovered, the key is released. Going from the bottom to the top the keys are `a`, `b`, `c`, `d`, `e`, `f`. Their keycodes are as follows

```
ir1=0x41
ir2=0x42
ir3=0x43
ir4=0x44
ir5=0x45
ir6=0x46
```

As each tower has 3 sensors and 3 emitters, so if you switch sides when wiring them up, the keys will get shuffled into the following order: `b`, `a`, `d`, `c`, `f`, `e`.

### Ground Slider

The Ground Slider is an RS232 device and can be connected directly to the PC for native use. This repo contains a python script to help verify correct wiring. See `slidertest` folder readme for more info.
It's the best to keep the slider connected to a `COM1` port.

## Pinout

If you are this deep, you will surely be fine without diagrams. Especially since everything is pretty self-explanatory and all pin holes in JST plugs are clearly **numbered**.

### Ground Slider

#### YLP-03V (connects into an YLR-03V)

This is the power input connector. Goes to a 12V source. You will most likely use a dedicated 12V wall adapter, but you can get creative here (e.g. get a Molex plug or a PD charger and trigger).

- yellow - +12V
- black - GND
- green - earth (can be left disconnected)

#### SMR-04V (connects into an SMP-04V)

This is the serial input/output connector. Goes to your RS232 adapter.

- white (RX) - DB9 pin 2
- red (TX) - DB9 pin 3
- black (GND) - DB9 pin 5

### Air towers

#### YLP-15V (connects into an YLR-15V)

This is the air strings (sensors) connector. 

- 1 (red) - to Arduino +5V (may be marked `RAW` on the PCB),
- 2 to 7 (stripped grey) - to the other tower pins 2 to 7,
- 8 to 10 (stripped white) - to the Arduino GPIO 8, 9, and 10 (left tower) or 14, 15, and 16 (right tower),
- 11 and 12 (black) - to Arduino GND,
- 15 (green) - earth (can be left disconnected)

#### YLP-06V (connects into an YLR-06V)

This is the LED strip connector. Needs a 12V source. Yes, **another 12V** line. But it can be connected in parallel with slider's 12V supply (keeping in mind the wire gauge and the rated power of your 12V source).

- yellow - +12V
- striped white - LED data - goes to Arduino GPIO 5 (blue - left tower) or 6 (orange - right tower).
- black GND - goes to power supply GND and Arduino GND (but they are probably common ground anyway)

The LEDs are WS2811 in RGB order, with 9 LEDs per strip. They are, however, wired such that each WS2811 ID controls a group of 3 actual LEDs, so it's not possible to control each one separately. It comes out to 2 sensors per group of 3 LEDs.

## Power considerations

According to rough calculations done on the Cons&Stuff Discord server, all LEDs in the whole panel assembly (slider + towers) could draw as much as 18W. However, such situation is highly unlikely, with 15W being suggested to have a reasonable margin already. And on top of that, people's experiences show that a 12W PSUs are fine.