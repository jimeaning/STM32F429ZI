#include "button.h"
#include "dcmotor.h"

extern TIM_HandleTypeDef htim4;

void dcmotor_pwm_control(void);

// BUTTON0 : start/stop : LED1 (toggle)
// BUTTON1 : SPEED-UP : LED2 (toggle)
// BUTTON2 : SPEED-DOWN : LED3 (toggle)
uint8_t pwm_start_flag = 0;		// dcmotor start/stop indicator flag
uint16_t CCR_UP_Value = 0;		// PWM UP control
uint16_t CCR_DOWN_Value = 0;		// PWM DOWN control

void dcmotor_pwm_control(void)
{
	if (get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);	// LED1
		if (!pwm_start_flag)
		{
			pwm_start_flag = 1;
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
		}
		else
		{
			pwm_start_flag = 0;
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
		}
	}
	// speed-up : button1
	if (get_button(BUTTON1_GPIO_Port, BUTTON1_Pin, 1) == BUTTON_PRESS)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);	// LED2
		CCR_UP_Value = __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_1);
		CCR_UP_Value += 10;
		if (CCR_UP_Value > 100) CCR_UP_Value = 100;
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, CCR_UP_Value);
	}
	// speed-up : button1
	if (get_button(BUTTON2_GPIO_Port, BUTTON2_Pin, 2) == BUTTON_PRESS)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);	// LED2
		CCR_DOWN_Value = __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_1);
		CCR_DOWN_Value -= 10;
		if (CCR_DOWN_Value < 60) CCR_DOWN_Value = 60;
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, CCR_DOWN_Value);
	}
	if (get_button(BUTTON2_GPIO_Port, BUTTON2_Pin, 3) == BUTTON_PRESS)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, 0);	// LED2
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 1);	// LED2
	}
}
