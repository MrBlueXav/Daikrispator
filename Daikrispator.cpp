//-------------------------------------------------------------------------------------
//
//        Dekrispator for Daisy pod platform
//        by Xavier Halgand
//			august 2020
//
//*************************************************************************************

#include "daisysp.h"
#include "daisy_pod.h"

#include <math.h>
#include <stdint.h>
#include <stdbool.h>

#include "constants.h"
#include "math_tools.h"
#include "random.h"
#include "sequencer.h"
#include "oscillators.h"
#include "delay.h"
#include "chorusFD.h"
#include "phaser.h"
#include "sinetable.h"
#include "notesTables.h"
#include "resonantFilter.h"
#include "adsr.h"
#include "blepvco.h"
#include "soundGen.h"

//--------------------------------------------------------------------------
using namespace daisysp;
using namespace daisy;

extern Sequencer_t   seq;
extern bool delayON  _CCM_;
extern bool phaserON _CCM_;
extern bool chorusON _CCM_;

static DaisyPod pod;
float           sample_rate;
Parameter       p_knob1, p_knob2;

bool freeze    = false;
bool demoMode  = true;
bool stopSound = false;

float oldk1, oldk2, k1, k2;

//--------------------------------------------------------------------------

void ConditionalParameter(float  oldVal,
                          float  newVal,
                          float &param,
                          float  update);

//--------------------------------------------------------------------------

void Controls();

//--------------------------------------------------------------------------

static void AudioCallback(float *in, float *out, size_t size)
{
    Controls();

    float yL, yR;

    // for (size_t i = 0; i < size; i += 2) {
    // 	computeSound(&yL, &yR);

    // 	// left out
    // 	out[i] = yL;

    // 	// right out
    // 	out[i + 1] = yR;
    // }

    if(!stopSound)
    {
        for(size_t i = 0; i < size; i += 2)
        {
            computeSound(&yL, &yR);

            // left out
            out[i] = yL;

            // right out
            out[i + 1] = yR;
        }
    }
    else
    {
        for(size_t i = 0; i < size; i += 2)
        {
            // left out
            out[i] = 0;

            // right out
            out[i + 1] = 0;
        }
    }
}

//--------------------------------------------------------------------------

//Updates values if knob had changed
void ConditionalParameter(float  oldVal,
                          float  newVal,
                          float &param,
                          float  update)
{
    if(abs(oldVal - newVal) > 0.0005)
    {
        param = update;
    }
}

//--------------------------------------------------------------------------

//Controls Helpers
void UpdateEncoder() {}

//--------------------------------------------------------------------------

void UpdateKnobs()
{
    k1 = pod.knob1.Process();
    k2 = pod.knob2.Process();
    //ConditionalParameter(oldk1, k1, seq.tempo, k1);
    seq.tempo    = 480 * k1 + 20;
    seq.steptime = lrintf(sample_rate * 60 / seq.tempo);
    if(k2 < 0.25f)
    {
        delayON  = false;
        phaserON = false;
        chorusON = false;
    }
    else if(k2 < 0.5)
    {
        delayON  = true;
        phaserON = false;
        chorusON = false;
    }
    else if(k2 < 0.75)
    {
        delayON  = true;
        phaserON = true;
        chorusON = false;
    }
    else
    {
        delayON  = true;
        phaserON = true;
        chorusON = true;
    }

    oldk1 = k1;
    oldk2 = k2;
}

//--------------------------------------------------------------------------

void UpdateLeds()
{
    pod.led1.Set(freeze, freeze, freeze);
    pod.led2.Set(stopSound, !stopSound, 0);
    pod.UpdateLeds();
}

//--------------------------------------------------------------------------

void UpdateButtons()
{
    if(pod.button1.RisingEdge())
    {
        freeze = !freeze;
    }
    if(pod.button2.RisingEdge())
    {
        stopSound = !stopSound;
    }
}

//--------------------------------------------------------------------------

void Controls()
{
    pod.UpdateAnalogControls();
    pod.DebounceControls();
    UpdateEncoder();
    UpdateKnobs();
    UpdateButtons();
    UpdateLeds();
}

//**************************************************************************

int main(void)
{
    oldk1 = oldk2 = 0;
    k1 = k2 = 0;

    //Init everything
    pod.Init();
    sample_rate = pod.AudioSampleRate();
    p_knob1.Init(pod.knob1, 20, 500, Parameter::LINEAR);

    /* Initialize the on-board random number generator ! */
    randomGen_init();
    /* dekrispator synth init  */
    Synth_Init();

    // start callback
    pod.StartAdc();
    pod.StartAudio(AudioCallback);

    while(1) {}
}

/*--------------------------------END ------------------------------------*/
