# Spectre pin mappings

Board uses a molex 48 pin header p/n 5007620481

| STM32 pin | Pin# | Function   | Alternative | Switch |
|-----------|-----|-------------|-------------|--------|
|           | 1   | GND_PWR     |
|           | 2   | GND_PWR     |
|           | 3   | 12V_ECU     |
|           | 4   | 12V_ECU     |
| PE13      | 5   | INJ_CH8     |
| PE14      | 6   | INJ_CH7     |
| PE9       | 7   | INJ_CH5     |
| PE11      | 8   | INJ_CH6     |
| PC7       | 9   | IDLE1-OUT   | STEP_1A_OUT | JP5
| PB1       | 10  | BARO        |
| PB12      | 11  | Spare_2_out | Step_2B_OUT | JP6
| PB13      | 12  | Spare_1_Out | Step_1B_OUT | JP7
| PD7       | 13  | IGN_CH1     |
| PA4       | 14  | O2_2 / AIN_2        |
| PE6       | 15  | FAN         |
| PD3       | 16  | IDLE2-OUT   | STEP_2A_OUT | JP8
| PC0       | 17  | IAT         |
| PA0       | 18  | IAT_2 / AIN_1      |
| PE3       | 19  | FUEL_PUMP   |
| PA1       | 20  | CLT_2 / AIN_3      |
|           | 21  | RS232_TX    |
|           | 22  | GND         | IGN5-OUT / PD9   | JP18
| PC4       | 23  | O2          |
| PD15      | 24  | INJ_CH4     |
| PC2       | 25  | MAP         |
|           | 26  | GND         | IGN6-OUT / PB7   | JP16
| PC3       | 27  | CLT         |
| PD14      | 28  | INJ_CH3     |
|           | 29  | CANH        |
|           | 30  | GND         |
| PB9       | 31  | IGN_CH2     |
| PD12      | 32  | INJ_CH1     |
|           | 33  | GND         |
|           | 34  | RS232_RX    |
| PC1       | 35  | TPS         |
| PA8       | 36  | IGN_CH3     |
|           | 37  | 5V          |
| PD4       | 38  | FLEX_FUEL_IN     |
|           | 39  | VR2-        |
| PD10      | 40  | IGN_CH4     |
|           | 41  | VR2+        |
|           | 42  | VR1-        |
|           | 43  | VR1+        |
| PD13      | 44  | INJ_CH2     |
|           | 45  | CANL        |
|           | 46  | 3.3V        |
| PC6       | 47  | BOOST-OUT   |
| PC13      | 48  | TACHO-OUT   |

STEP_1A_OUT/STEP_1B_OUT/STEP_2A_OUT/STEP_2B_OUT control DRV8825:
DIR PE7
STEP PE5
EN PE2

CANH/CANL:
PD0 rx
PD1 tx

VR1+/VR1-/VR2+/VR2- conditioner MAX9926:
COUT1 PE0
COUT2 PE1

VBAT battery voltage is on PC5