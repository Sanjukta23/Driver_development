/*
 * 002led_button.c
 *
 *  Created on: Jun 10, 2026
 *      Author: SANJU
 */


#include "stm32f4466xx.h"

#define BTN_PRESSED 0 //active low

void delay(void)
{
	for(uint32_t i = 0 ; i < 500000/2 ; i ++);
}


int main(void)
{

	GPIO_Handle_t GpioLed, GPIOBtn;

	//this is led gpio configuration
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA,ENABLE);

	GPIO_Init(&GpioLed);


	//this is btn gpio configuration
	GPIOBtn.pGPIOx = GPIOC;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOC,ENABLE);

	GPIO_Init(&GPIOBtn);

	while(1)
	{
		if(GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13) == BTN_PRESSED)
		{
			delay();
			GPIO_ToggleOutputPin(GPIOA,GPIO_PIN_NO_5);
		}
	}
	return 0;
}
