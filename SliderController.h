// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _SliderController_H_
#define _SliderController_H_
#include "Arduino.h"
//add your includes for the project SliderController here
#include <LiquidCrystal.h>
//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project SliderController here
int read_LCD_buttons();
void Encoder_san();



//Do not add code below this line
#endif /* _SliderController_H_ */
