/*
 * pwm.c
 *
 *  Created on: May 3, 2017
 *      Author: jonathanwingfield
 */
#include "pwm.h"

void pwm_init(void){
	// TPM0 ch0 used for RED LED
	// TPM0 ch1 used for GREEN LED
	// TPM0 ch2 used for BLUE LED

	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
	// enable clock source for TPM0
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);
	// specify clock source as MCGPLLCLK

	TPM0_SC = TPM_SC_TOIE_MASK|TPM_SC_CMOD(1)|TPM_SC_PS(1);
	// divide clock source by 2, set to up counting mode, interrupt when timer hits modulo value
	TPM0_CNT = 0; // reset count value
	TPM0_MOD = 0xFFFF; // max count value
	TPM0_C0SC = TPM_CnSC_CHIE_MASK|TPM_CnSC_MSB_MASK;
	// sets as software capture mode
	TPM0_C0V = 0; // initialize channel to 0% duty cycle

	TPM0_C1SC = TPM_CnSC_CHIE_MASK|TPM_CnSC_MSB_MASK;
	// sets as software capture mode
	TPM0_C1V = 0;

	TPM0_C2SC = TPM_CnSC_CHIE_MASK|TPM_CnSC_MSB_MASK;
	// sets as software capture mode
	TPM0_C2V = 0;

	NVIC_EnableIRQ(TPM0_IRQn);
}

void pwm_set_duty_cycle(tpm0_channel_t channel, uint32_t duty_cycle){

	TPM0_CNT = 0; // reset TPM0 count value
	TPM0_SC |= TPM_SC_CMOD(0); // disable channel while modifying
	if(duty_cycle > 100) duty_cycle = 100;

	TPM_CnV_REG(TPM0,(uint32_t)channel) = ((uint16_t)((duty_cycle/100.0) * 0xFFFF));
	// adjust duty cycle to appropriate percentage of counts
	TPM0_SC |= TPM_SC_CMOD(1)|TPM_SC_TOIE_MASK;
	// re enable clock source
}

extern void TPM0_IRQHandler(void){
	// check channel flag, toggle led appropriately
	uint32_t status = TPM0_STATUS;
	if(status & TPM_STATUS_TOF_MASK){ // set LEDS on overflow
		led_red_set();
		led_green_set();
		led_blue_set();
		TPM0_SC |= TPM_SC_TOF_MASK;
	}
	// clear LEDS when counter hits modulo value
	if(status & TPM_STATUS_CH0F_MASK){
		led_red_clear();
		TPM0_STATUS = TPM_STATUS_CH0F_MASK;
	}
	if(status & TPM_STATUS_CH1F_MASK){
		led_green_clear();
		TPM0_STATUS = TPM_STATUS_CH1F_MASK;
	}
	if(status & TPM_STATUS_CH2F_MASK){
		led_blue_clear();
		TPM0_STATUS = TPM_STATUS_CH2F_MASK;
	}
}
