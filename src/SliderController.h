// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _SliderController_H_
#define _SliderController_H_
//add your includes for the project SliderController here
#include "Global.h"
#include "Arduino.h"
#include "param/DelayParam.h"
#include "param/WaitParam.h"
#include "param/ModeParam.h"
#include "param/WayParam.h"
#include "states/WelcomeState.h"
#include "states/SettingsState.h"
#include "states/SimulateState.h"
#include "states/PlayState.h"
#include "io/Relay.h"
//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif
//Do not add code below this line

template<class T>
T * const getNext(T * const array[], int const size, T * const item, bool const isNext);
SettingsState * const getNext(SettingsState * const state, bool const isNext);
SimulateState * const getNext(SimulateState * const state, bool const isNext);
PlayState * const getNext(PlayState * const state, bool const isNext);
bool setState(AbstractSliderState * const newState);
bool setState(SettingsState * const newSettingsState);
bool setState(AbstractActionState * const newActionState);
void activateRelays(AbstractActionState * const newActionState);
void manageRelays();
void cancelRelays();
void startSequence();
void readButtonsAndUpdateState();
void updateSequence();
void Encoder_san();
int read_LCD_buttons();

#endif /* _SliderController_H_ */
