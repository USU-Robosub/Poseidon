# Arduino Controller

This code is for the Arduino Due.
The Arduino Due controls the submarine's thrusters, and some sensors.

## Serial Protocol

The pins used by each controller are set in `PinMap.h`.

### Controllers

| name | index | parameter | type | output | type | note |
| - | - | - | - | - | - | - |
| Kill Switch | 0 | | | isActive 0=inactive 1=active | byte | When kill switch goes active then all controllers are killed. |
| Move Thrust | 1 | power 1000-2000 | ushort | | | A value of 1500 will set the motors to idle (off). |
| Strafe Thrust | 2 | power 1000-2000 | ushort | | | A value of 1500 will set the motors to idle (off). |
| Dive Thrust | 3 | power 1000-2000 | ushort | | | A value of 1500 will set the motors to idle (off). |
| Yaw Thrust | 4 | power 1000-2000 | ushort | | | A value of 1500 will set the motors to idle (off). |
| Pitch Thrust | 5 | power 1000-2000 | ushort | | | A value of 1500 will set the motors to idle (off). |
| Roll Thrust | 6 | power 1000-2000 | ushort | | | A value of 1500 will set the motors to idle (off). |
| Esc Power | 7 | toggle 0=off 1=on | byte | | | |
| Led Power | 8 | | | | | Blinks led twice for 250ms. |
| Ping | 9 | | | "I'm Here!"\0 | string | |
| Light Power | 10 | toggle 0=off 1=on | byte | | | |
| Voltage | 11 | | | voltage (V) | double | |
| Start | 12 | | | isActive | byte | This controller does nothing but toggle its internal state. |

### Boot

**Warning**: The first byte sent to the Arduino is destroyed.

Data sent to serial

```
["Ready!"\0]
```

### Command structure

#### Input

```
[byte: controller index][data: data for controller][...][no new line]
```

#### Output

```
[data: raw data from controller][no new line]
```

## How to compile and upload to Arduino

The project is currently not setup to be used with PlatformIO.
Therefore the Arduino needs to be programmed using the [Arduino IDE](https://www.arduino.cc/en/Main/Software).
Load the `ArduinoController` folder in the Arduino IDE, and then upload it to the Arduino.

#### Arduino Due

It is recommended to upload to the Arduino Due using the programming port.
The programming port is the closest USB port to the DC power in.
