#include "app.h"
#include "main.h"
#define DEBOUNCE_TİME 100

GPIO_PinState userButtonState;
GPIO_PinState lastStatus;
int pushCounter;

GPIO_PinState GPIO_Read_With_Debounce(GPIO_TypeDef* debouncePort, uint16_t debouncePin){

	static GPIO_PinState lastState;
	static GPIO_PinState lastStableState;
	static uint32_t currentTime;


	GPIO_PinState currentState = HAL_GPIO_ReadPin(debouncePort, debouncePin);

	if(currentState == GPIO_PIN_SET){
		if (currentState != lastState) {

			currentTime = HAL_GetTick();
			lastState = currentState;
		}
	}else
	{
		lastState = currentState;
		lastStableState = lastState;
	}


	if((HAL_GetTick() - currentTime) >= DEBOUNCE_TİME){
		if(lastState == currentState){
			if(lastStableState != lastState){

				lastStableState = lastState;
			}
		}

	}


	return lastStableState;
}


void App_Init(void)
{


}

void App_Run(void)
{
	userButtonState = GPIO_Read_With_Debounce(User_Button_GPIO_Port, User_Button_Pin);

	if(userButtonState == GPIO_PIN_RESET){
		if(userButtonState != lastStatus){
			lastStatus = userButtonState;
			pushCounter++;
		}
	}else
	{
		lastStatus = userButtonState;
	}


}
