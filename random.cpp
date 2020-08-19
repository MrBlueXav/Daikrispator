/**
 ******************************************************************************
 * File Name          : random.c
 * Author			  : Xavier Halgand
 * Date               :
 * Description        :
 ******************************************************************************
 */
//-------------------------------------------------------------------------------------------------------

#include "random.h"

//-------------------------------------------------------------------------------------------------------

/* RNG handler declaration */
RNG_HandleTypeDef RngHandle;

//-------------------------------------------------------------------------------------------------------

void HAL_RNG_MspInit(RNG_HandleTypeDef *hrng)
{
  /* RNG Peripheral clock enable */
  __RNG_CLK_ENABLE();
  __HAL_RNG_ENABLE(&RngHandle);
}
//-------------------------------------------------------------------------------------------------------

/**
  * @brief RNG MSP De-Initialization
  *        This function freeze the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  * @param hrng: RNG handle pointer
  * @retval None
  */
void HAL_RNG_MspDeInit(RNG_HandleTypeDef *hrng)
{
  /* Enable RNG reset state */
  __RNG_FORCE_RESET();

  /* Release RNG from reset state */
  __RNG_RELEASE_RESET();
}

//---------------------------------------------------------------------------
void randomGen_init(void)
{
	/* Configure the RNG peripheral #######################################*/

	  RngHandle.Instance = RNG;
    uint32_t random32bit;

	  if(HAL_RNG_Init(&RngHandle) != HAL_OK)
	  {
	    /* Initialization Error */
	    //Error_Handler();
	  }
    HAL_RNG_GenerateRandomNumber(&RngHandle, &random32bit);
	srand(random32bit);
}
//---------------------------------------------------------------------------
/**************
 * returns a random float between a and b
 *****************/
float_t frand_a_b(float_t a, float_t b)
{
	return ( rand()/(float_t)RAND_MAX ) * (b-a) + a ;
}


//---------------------------------------------------------------------------
/**************
 * returns a random float between 0 and 1
 *****************/
float_t randomNum(void)
{
	float_t random = 1.0f;
  uint32_t random32bit;

  HAL_RNG_GenerateRandomNumber(&RngHandle, &random32bit);

	random = (float_t) (random32bit / 4294967294.0f);
	return random;
}

/*-----------------------------------------------------------------------------*/
/**************
 * returns a random integer between 0 and MIDI_MAX
 *****************/
uint8_t MIDIrandVal(void)
{
	return (uint8_t)lrintf(frand_a_b(0 , MIDI_MAX));
}

//-------------------------------------------------------------------------------------------------------
