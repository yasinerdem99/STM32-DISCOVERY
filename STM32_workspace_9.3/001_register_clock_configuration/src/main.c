
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

extern uint32_t SystemCoreClock;

uint32_t systemClock;

void RCC_Config(void)
{
	RCC->CR &= 0x00000083;
	RCC->CR &= ~(1<<0);                     //HSI OFF
	RCC->CR |= 1<<16;                      // HSE ON
	while(!(RCC->CR & (1<<17)));           // WAIT HSE ACTIVE
	RCC->CR |= 1<<19;

	/*RCC->PLLCFGR &= ~(1<<0); //PLLM0 0	  div->4
	RCC->PLLCFGR &= ~(1<<1); //PLLM1 0    div->4
	RCC->PLLCFGR |= (1<<2); //PLLM2 1     div->4
	RCC->PLLCFGR &= ~(1<<3); //PLLM3 0    div->4
	RCC->PLLCFGR &= ~(1<<4); //PLLM4 0    div->4
	RCC->PLLCFGR &= ~(1<<5); //PLLM5 0    div->4*/

	RCC->PLLCFGR = 0X00000000;            //PLLCFGR RESET
	RCC->PLLCFGR |= (1<<22);              //PLL SOURCE HSE
	RCC->PLLCFGR |= (4<<0);               //PLL M 4
	RCC->PLLCFGR |= (168<<6);             //PLL N 168

	RCC->CR |= (1<<24);              //PLL ON
	while(!(RCC->CR & (1<<25)));           // WAIT PLL ACTIVE

	RCC->CFGR &= ~(1<<0);
	RCC->CFGR |= (1<<1);                //system clock is pll
	while(!(RCC->CFGR & (1<<1)));       //select system clock pll clock


}



int main(void)
{
  systemClock= SystemCoreClock;

  RCC_DeInit();

  SystemCoreClockUpdate(); // 16 000 000

  systemClock = SystemCoreClock;

  RCC_Config();

  SystemCoreClockUpdate();

  systemClock = SystemCoreClock;

  while (1)
  {

  }
}


/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
