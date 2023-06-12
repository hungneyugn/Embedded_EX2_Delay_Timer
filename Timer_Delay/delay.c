#include "delay.h"

static volatile uint32_t TimingDelay;

void TIM2_INT_Init(void){
	/*Init struct*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	/*Enable clock for TIM2*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	/*Timer counter in 1ms*/
	TIM_TimeBaseInitStruct.TIM_Prescaler = 3599;
	TIM_TimeBaseInitStruct.TIM_Period = 19;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	/*Enable TIM2 interrupt*/
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	/*Start TIM2*/
	TIM_Cmd(TIM2, ENABLE);
	
	/*Nested vectored interrupt settings*/
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

void DelayMs(uint32_t ms){
		TIM2_INT_Init();
		TimingDelay = ms;
		while(TimingDelay != 0);
}
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		TimingDelay--;

		/*Clears the TIM2 interrupt pending bit*/
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
