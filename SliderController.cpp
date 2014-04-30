// Do not remove the include below
#include "SliderController.h"

// LCD
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Set Encoder pin
const int Encoder_A = 3;            // Incremental Encoder singal A is PD3
const int Encoder_B = 2;            // Incremental Encoder singal B is PD2
bool needToRefreshValueOnLCD = false;
bool needToSaveValueOnEeprom = false;
bool fistActionStep = false;

// define some values used by the panel and buttons
int lcd_key = 0;
int adc_key_in = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
#define btnEncodeOK  6
#define lcdBackLight 10

// Relays
Relay * const relayTrigger = new Relay(15);
Relay * const relayBackward = new Relay(16);
Relay * const relayForward = new Relay(17);
Relay * const relayStop = new Relay(18);

// Some delays
#define PUSH_BUTTON_DELAY    100
#define WELCOME_STATE_DELAY 1000

// Config values
DelayParam * const paramStartIn = new DelayParam(&lcd, 0);
DelayParam * const paramTrigger = new DelayParam(&lcd, 4);
DelayParam * const paramPostTrig = new DelayParam(&lcd, 8);
DelayParam * const paramMove = new DelayParam(&lcd, 12);
WaitParam * const paramPostMove = new WaitParam(&lcd, 16, paramStartIn);
ModeParam * const paramMode = new ModeParam(&lcd, 20);
WayParam * const paramWay = new WayParam(&lcd);

char const * const stateLabelTriggering = "Click";
char const * const stateLabelMoving = "Moving";
char const * const stateLabelWaiting = "Waiting";

// States
WelcomeState * const stateWelcome = new WelcomeState(&lcd);
SettingsState * const stateSettings1StartIn = new SettingsState(&lcd, "Start in", paramStartIn);
SettingsState * const stateSettings2Trigger = new SettingsState(&lcd, "Trigger", paramTrigger);
SettingsState * const stateSettings3PostTrig = new SettingsState(&lcd, "Post-trig", paramPostTrig);
SettingsState * const stateSettings4Move = new SettingsState(&lcd, "Move", paramMove);
SettingsState * const stateSettings5PostMove = new SettingsState(&lcd, "Post-move", paramPostMove);
SettingsState * const stateSettings6Mode = new SettingsState(&lcd, "Mode", paramMode);
SimulateState * const stateSimulate1Triggering = new SimulateState(&lcd, stateLabelTriggering, paramTrigger, paramWay);
SimulateState * const stateSimulate2Moving = new SimulateState(&lcd, stateLabelMoving, paramMove, paramWay);
PlayState * const statePlay1Triggering = new PlayState(&lcd, stateLabelTriggering, paramTrigger, paramWay);
PlayState * const statePlay2PostTrig = new PlayState(&lcd, stateLabelWaiting, paramPostTrig, paramWay);
PlayState * const statePlay3Moving = new PlayState(&lcd, stateLabelMoving, paramMove, paramWay);
PlayState * const statePlay4PostMove = new PlayState(&lcd, stateLabelWaiting, paramPostMove, paramWay);

// Sequences
#define SEQ_SETTINGS_SIZE 6
SettingsState * const seqSettings[SEQ_SETTINGS_SIZE] = { stateSettings1StartIn, stateSettings2Trigger,
		stateSettings3PostTrig,stateSettings4Move,stateSettings5PostMove,stateSettings6Mode };
#define SEQ_SIMULATE_SIZE 2
SimulateState * const seqSimulate[SEQ_SIMULATE_SIZE] = { stateSimulate1Triggering, stateSimulate2Moving };
#define SEQ_PLAY_SIZE 4
PlayState * const seqPlay[SEQ_PLAY_SIZE] = { statePlay1Triggering, statePlay2PostTrig, statePlay3Moving, statePlay4PostMove };

// States var
AbstractSliderState* currentState = stateSettings1StartIn;
SettingsState* lastSettingsState = stateSettings1StartIn;
unsigned long timeOfLastActionStateChange = 0;

void setup() {
#ifdef DEBUG
	Serial.begin(9600);
	Serial.println("Start serial port");
#endif

	// Init LCD lib
	lcd.begin(16, 2);
	pinMode(lcdBackLight, OUTPUT);
	digitalWrite(lcdBackLight, HIGH);
	setState(stateWelcome);

	// Init Encoder
	pinMode(Encoder_A, INPUT);
	pinMode(Encoder_B, INPUT);
	digitalWrite(Encoder_A, 1);
	digitalWrite(Encoder_B, 1);
	attachInterrupt(1, Encoder_san, FALLING);       //interrupts: numbers 0 (on digital pin 2) and 1 (on digital pin 3).

	// Let the welcome state for 1sec
	delay(WELCOME_STATE_DELAY);
	// Show first setting state
	setState(stateSettings1StartIn);
}

template<class T>
T * const getNext(T * const array[], int const size, T * const item, bool const isNext) {
	for (int i = 0; i < size; i++) {
		if (item == array[i]) {
			int nextIndex;
			if (isNext) {
				nextIndex = i + 1;
				if (nextIndex >= size) {
					nextIndex = 0;
				}
			} else {
				nextIndex = i - 1;
				if (nextIndex < 0) {
					nextIndex = size - 1;
				}
			}
			return array[nextIndex];
		}
	}
}

SettingsState * const getNext(SettingsState * const state, bool const isNext) {
	return getNext(seqSettings, SEQ_SETTINGS_SIZE, state, isNext);
}

SimulateState * const getNext(SimulateState * const state, bool const isNext) {
	return getNext(seqSimulate, SEQ_SIMULATE_SIZE, state, isNext);
}

PlayState * const getNext(PlayState * const state, bool const isNext) {
	return getNext(seqPlay, SEQ_PLAY_SIZE, state, isNext);
}

bool setState(AbstractSliderState * const newState) {
	if (newState != currentState) {
		// Save when we quit a settings state with a modified value
		if (currentState->getType() == typeState_Settings && needToSaveValueOnEeprom) {
			((SettingsState*) currentState)->getParam()->save();
			needToSaveValueOnEeprom = false;
		}
		currentState = newState;
		newState->print();
		return true;
	}
	return false;
}

bool setState(SettingsState * const newSettingsState) {
	if (currentState->getType() > typeState_Settings) {
		// If the previous state was an action state, cancel relays
		cancelRelays();
	}
	if (newSettingsState != lastSettingsState) {
		lastSettingsState = newSettingsState;
	}
	timeOfLastActionStateChange = 0;
	return setState((AbstractSliderState*) newSettingsState);
}

bool setState(AbstractActionState * const newActionState) {
	if (newActionState != currentState) {
		activateRelays(newActionState);
		timeOfLastActionStateChange = millis();
	}
	return setState((AbstractSliderState*) newActionState);
}

void activateRelays(AbstractActionState * const newActionState) {
	if (newActionState->m_label == stateLabelWaiting ) {
		relayStop->switchOnFor(PUSH_BUTTON_DELAY);
	} else if (newActionState->m_label == stateLabelTriggering) {
		relayStop->switchOnFor(PUSH_BUTTON_DELAY);
		relayTrigger->switchOnFor(newActionState->getParam()->getDelayInMs());
	} else if (newActionState->m_label == stateLabelMoving) {
		if (paramWay->isGoLeft()) {
			relayBackward->switchOnFor(PUSH_BUTTON_DELAY);
		} else {
			relayForward->switchOnFor(PUSH_BUTTON_DELAY);
		}
	}
}

void manageRelays() {
	relayTrigger->update();
	relayBackward->update();
	relayForward->update();
	relayStop->update();
}

void cancelRelays() {
	relayTrigger->cancel();
	relayBackward->cancel();
	relayForward->cancel();
	relayStop->cancel();
	relayStop->switchOnFor(PUSH_BUTTON_DELAY);
}

void readButtonsAndUpdateState() {
	lcd_key = read_LCD_buttons(); // read the buttons

	// User turn the encoder
	if (needToRefreshValueOnLCD) {
		// Go back to settings mode if necessary
		if (!setState(lastSettingsState)) {
			// If we are already on settings, refresh only value
			lastSettingsState->getParam()->print();
		}
		needToRefreshValueOnLCD = false;
	} else if (lcd_key == btnSELECT) {
		// Turn on/off the LCD backlight
		if (digitalRead(lcdBackLight) == HIGH) {
			digitalWrite(lcdBackLight, LOW);
		} else {
			digitalWrite(lcdBackLight, HIGH);
		}
	} else if (lcd_key != btnNONE) {
		switch (lcd_key)               // depending on which button was pushed, we perform an action
		{
		case btnRIGHT:
			// Set way and launch sequence
			paramWay->increase();
			startSequence();
			break;
		case btnLEFT:
			// Set way and launch sequence
			paramWay->decrease();
			startSequence();
			break;
		case btnUP:
			if (currentState == lastSettingsState) {
				// Go to previous settings state
				setState(getNext(lastSettingsState, false));
			} else {
				// Go to settings mode
				setState(lastSettingsState);
			}
			break;
		case btnDOWN:
			if (currentState == lastSettingsState) {
				// Go to next settings state
				setState(getNext(lastSettingsState, true));
			} else {
				// Go to settings mode
				setState(lastSettingsState);
			}
			break;
		case btnEncodeOK:
			AbstractSliderParam* param = lastSettingsState->getParam();
			if (param->getType() == typeParam_Delay) {
				// Change unit
				((DelayParam*) param)->changeUnit(true);
				needToSaveValueOnEeprom = true;
				// If the state do not need to be changed
				if (!setState(lastSettingsState)) {
					// Then only refresh the param
					param->print();
				}
			} else {
				setState(lastSettingsState);
			}
			break;
		}
	}
}

void startSequence() {
	if (currentState->getType() == typeState_Settings) {
		fistActionStep = true;
		if (paramMode->isSimulate()) {
			setState(stateSimulate1Triggering);
		} else if (paramStartIn->getValue() > 0) {
			setState(statePlay4PostMove);
		} else {
			setState(statePlay1Triggering);
		}
	} else {
		paramWay->print();
	}
}

void updateSequence() {
	if (timeOfLastActionStateChange > 0) {
		AbstractActionState* currentActionState = ((AbstractActionState*) currentState);
		if (!currentActionState->getParam()->printRemaining(timeOfLastActionStateChange, fistActionStep)) {
			fistActionStep = false;
			if (currentState->getType() == typeState_Simulate) {
				setState(getNext((SimulateState*) currentState, true));
			} else if (currentState->getType() == typeState_Play) {
				setState(getNext((PlayState*) currentState, true));
			}
		}
	}
}

void loop() {
	readButtonsAndUpdateState();
	updateSequence();
	manageRelays();
}

void Encoder_san() {
	if (digitalRead(Encoder_B)) {
		lastSettingsState->getParam()->increase();
	} else {
		lastSettingsState->getParam()->decrease();
	}
	needToRefreshValueOnLCD = true;
	needToSaveValueOnEeprom = true;
}

// ####### Buttons management #######

#define DEBOUNCE_DELAY 50
int lastButton = btnNONE;
unsigned long lastButtonTime = 0;

// read the buttons
int read_LCD_buttons() {
	adc_key_in = analogRead(0);
	int newButton = btnNONE;
	// read the value from the sensor
	// my buttons when read are centered at these valies: 0, 144, 329, 504, 741
	// we add approx 50 to those values and check to see if we are close
	if (adc_key_in <= 1000) {
		// We make this the 1st option for speed reasons since it will be the most likely result
		// For V1.1 us this threshold
		if (adc_key_in < 50)
			newButton = btnLEFT;
		else if (adc_key_in < 150)
			newButton = btnUP;
		else if (adc_key_in < 250)
			newButton = btnRIGHT;
		else if (adc_key_in < 450)
			newButton = btnSELECT;
		else if (adc_key_in < 700)
			newButton = btnDOWN;
		else if (adc_key_in < 850)
			newButton = btnEncodeOK;
	}
	// Only return button changes
	unsigned long currentTime = millis();
	if (newButton != lastButton && currentTime - lastButtonTime > DEBOUNCE_DELAY) {
		lastButton = newButton;
		lastButtonTime = currentTime;
		return newButton;
	}
	return btnNONE;
}
