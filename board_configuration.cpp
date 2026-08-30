#include "pch.h"
#include "board_overrides.h"

// SPECTRE has no dedicated status LEDs - all on-board LEDs are per-channel output indicators
Gpio getCommsLedPin() {
	return Gpio::Unassigned;
}

Gpio getRunningLedPin() {
	return Gpio::Unassigned;
}

Gpio getWarningLedPin() {
	return Gpio::Unassigned;
}

// VR1/Hall1 and VR2/Hall2 are conditioned by the on-board MAX9926 (JP2/JP3 select VR vs Hall)
// and its digital outputs land on PE0/PE1 regardless of which sensor type is selected
static void setTriggerPins() {
	engineConfiguration->triggerInputPins[0] = Gpio::E0;
	engineConfiguration->triggerInputPins[1] = Gpio::E1;
}

// Connector pins 32,44,28,24,7,8,6,5 = INJ_CH1..8
static void setInjectorPins() {
	engineConfiguration->injectionPins[0] = Gpio::D12;
	engineConfiguration->injectionPins[1] = Gpio::D13;
	engineConfiguration->injectionPins[2] = Gpio::D14;
	engineConfiguration->injectionPins[3] = Gpio::D15;
	engineConfiguration->injectionPins[4] = Gpio::E9;
	engineConfiguration->injectionPins[5] = Gpio::E11;
	engineConfiguration->injectionPins[6] = Gpio::E14;
	engineConfiguration->injectionPins[7] = Gpio::E13;
}

// Connector pins 13,31,36,40 = IGN_CH1..4
static void setIgnitionPins() {
	engineConfiguration->ignitionPins[0] = Gpio::D7;
	engineConfiguration->ignitionPins[1] = Gpio::B9;
	engineConfiguration->ignitionPins[2] = Gpio::A8;
	engineConfiguration->ignitionPins[3] = Gpio::D10;

	// IGN_CH5/IGN_CH6 share connector pins 22/26 with GND - only wired to IGN5-OUT (PD9) /
	// IGN6-OUT (PB7) if JP18 / JP16 are bridged away from their default (GND) position
	// engineConfiguration->ignitionPins[4] = Gpio::D9;
	// engineConfiguration->ignitionPins[5] = Gpio::B7;
}

static void setSensorPins() {
	// MAP - connector pin 25
	engineConfiguration->map.sensor.hwChannel = EFI_ADC_12;
	// CLT - connector pin 27
	engineConfiguration->clt.adcChannel = EFI_ADC_13;
	// IAT - connector pin 17
	engineConfiguration->iat.adcChannel = EFI_ADC_10;
	// TPS - connector pin 35
	engineConfiguration->tps1_1AdcChannel = EFI_ADC_11;
	// O2 (primary lambda) - connector pin 23
	engineConfiguration->afr.hwChannel = EFI_ADC_14;
	// BARO - connector pin 10, exposed pin for an external sensor, no on-board baro chip
	// so only the channel is set here - sensor type/curve is configured in TunerStudio
	engineConfiguration->baroSensor.hwChannel = EFI_ADC_9;
}

static void setAuxOutputs() {
	// FAN - connector pin 15
	engineConfiguration->fanPin = Gpio::E6;
	// FUEL_PUMP - connector pin 19
	engineConfiguration->fuelPumpPin = Gpio::E3;
	// TACHO-OUT - connector pin 48
	engineConfiguration->tachOutputPin = Gpio::C13;
	// BOOST-OUT - connector pin 47
	engineConfiguration->boostControlPin = Gpio::C6;
	// FLEX_FUEL_IN - connector pin 38
	engineConfiguration->flexSensorPin = Gpio::D4;

	// Spare_1_Out / Spare_2_out - connector pins 12/11, default (un-bridged) JP6/JP7 state
	engineConfiguration->auxValves[0] = Gpio::B13;
	engineConfiguration->auxValves[1] = Gpio::B12;
}

static void setIdleConfig() {
	// Active: 2-wire PWM idle solenoid on IDLE1-OUT (connector pin 9), the board's
	// default (un-bridged JP5/JP8) jumper state.
	engineConfiguration->idle.solenoidPin = Gpio::C7;

	// Alternate: 4-wire bipolar stepper idle motor via the on-board DRV8825 breakout.
	// Requires JP5-JP8 bridged to the STEP_xx alternate position. The DRV8825's
	// STEP/DIR/EN control lines are fixed regardless of jumper state - swap to this
	// block (and comment out the solenoidPin line above) if building with a stepper:
	// engineConfiguration->idle.stepperStepPin = Gpio::E5;
	// engineConfiguration->idle.stepperDirectionPin = Gpio::E7;
	// engineConfiguration->stepperEnablePin = Gpio::E2;
	// engineConfiguration->useStepperIdle = true;
}

static void setCanPins() {
	// CANH/CANL - connector pins 29/45
	engineConfiguration->canRxPin = Gpio::D0;
	engineConfiguration->canTxPin = Gpio::D1;
}

static void setupVbatt() {
	// VBAT divider: VBAT -> R44 (33k) -> node -> R45 (5.1k) -> GND, sensed on PC5
	// (R50 470R + clamp diodes/caps between the divider node and PC5 are filtering only)
	engineConfiguration->vbattAdcChannel = EFI_ADC_15;
	engineConfiguration->vbattDividerCoeff = (33.0f + 5.1f) / 5.1f;
	engineConfiguration->adcVcc = 3.3f;
}

// board-specific configuration setup
static void customBoardDefaultConfiguration() {
	setTriggerPins();
	setInjectorPins();
	setIgnitionPins();
	setSensorPins();
	setAuxOutputs();
	setIdleConfig();
	setCanPins();
	setupVbatt();
}

void setup_custom_board_overrides() {
    custom_board_DefaultConfiguration = customBoardDefaultConfiguration;
}
