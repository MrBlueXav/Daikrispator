/*
 * MIDI_application.h
 *
 *  Created on:  2014
 *
 */

#ifndef MIDI_APPLICATION_H_
#define MIDI_APPLICATION_H_

/* Includes ------------------------------------------------------------------*/

#include "constants.h"
#include "drifter.h"
#include "math.h"
#include "notesTables.h"
#include "random.h"
#include "sinetable.h"
#include "soundGen.h"

#include <stdint.h>
#include <stdbool.h>

/*------------------------------------------------------------------------------*/


/* Exported functions ------------------------------------------------------- */
void MagicPatch(uint8_t val); /* random sound parameters */
void MagicFX(uint8_t val);

/*------------------------------------------------------------------------------*/
#endif /* MIDI_APPLICATION_H_ */
