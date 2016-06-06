/******************************************************************************
 * @file     Main.c
 * @brief    Easy Start project: reads potentiometer in XMC4500 Hexagon
 *           Application Kit (Port 14.1) and uses this value for changing
 *           the blinking speed of LED located in port 3.9.
 *           ADC is converting continuously Ch1 in group 0 in background source
 *           The different blinking delays are implemented using a
 *           system timer that decrements a counter on each timer overflow
 *           This counter is controlled by the ADC result value (potentiometer)
 * @version  V1.0
 * @date     20. February 2015
 * @note
 * Copyright (C) 2015 Infineon Technologies AG. All rights reserved.
 ******************************************************************************
 * @par
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon’s microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *****************************************************************************/


#include <XMC4500.h>                    //SFR declarations of the selected device
#include "GPIO.h"

#define TICKS_PER_SECOND 10000

unsigned long timingdelay, adc_result;

void ADC0_Init(void);
void Delay100US (unsigned long time);
void SysTick_Handler(void);

int main(void)
{
	/* Setup the system timer to tick every 100us */
	SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

	/* Configure P3.9 (LED) */
	// P3.9 is used as GPIO for LED indication. Macros can be find in GPIO.h
	P3_9_set_mode(OUTPUT_PP_GP);
	P3_9_set_driver_strength(STRONG);
	P3_9_reset();

	/* Initialize and start ADC */
	ADC0_Init();

	/* Infinite loop */
	for(;;){
		do{
			adc_result =  VADC_G0->RES[1];
		} while (!(adc_result >> VADC_G_RES_VF_Pos));
                                        // wait until ADC result register 0 value is valid
                                        // VADC.G0RES1.VF = 1: Valid Flag
                                        // Indicates a new result in bitfield RESULT or bit FCR.
                                        // 1B = Bitfield RESULT has been updated with new
                                        // result value and has not yet been read, or bit
                                        // FCR has been updated

		adc_result &= 0xFFF;           // mask ADC result
		Delay100US((adc_result << 1) + 500);
                                       // tune minimum and maximum flashing time

		P3_9_toggle();
                                       // toggle P3.9 (toggle LED) using GPIO.h macros
	}
	return 0;
}


/**
 * @brief This function is to initialize the VADC peripheral to continuous conversion with background source\n
 * Channel 1 in group 0 takes part in the scan sequence. The result is sent to RESREG[0]\n
 * @param[in]   none \n
 * @return none\n
 *
 * <b>Reentrancy:  no</b><BR>
 *
 */
void ADC0_Init(void)
{
	SCU_RESET->PRCLR0 |= ((1 << SCU_RESET_PRSET0_VADCRS_Pos) & SCU_RESET_PRSET0_VADCRS_Msk);
                                        // De-assert reset: VADC Reset Clear Reset Clear = 1

	//Global ADC Initialization

	VADC->CLC         =  ((0 << VADC_CLC_DISR_Pos) & VADC_CLC_DISR_Msk) |
                                        // DISR = 0: Module Disable Request Bit
                                        // 0B On request: enable the module clock
                       	 ((0 << VADC_CLC_DISS_Pos) & VADC_CLC_DISS_Msk) |
                                        // DISS = 0: Module Disable Status Bit
                                        // 0B Module clock is enabled
                       	 ((0 << VADC_CLC_EDIS_Pos) & VADC_CLC_EDIS_Msk);
                                        // EDIS = 0: Sleep Mode Enable Control
                                        // 0B Sleep mode request is enabled and functional
	// Wait for module clock enabled
	while(VADC->CLC!=0);                  // DISS: Module Disable Status Bit
                                        //  0B Module clock is enabled

	VADC->GLOBCFG     =  ((6 << VADC_GLOBCFG_DIVA_Pos) & VADC_GLOBCFG_DIVA_Msk) |
                                        // DIVA = 6: Divider Factor for the Analog Internal Clock
                                        // fADCI = fADC / (DIVA + 1) = fADC / 7
                       	 ((1 << VADC_GLOBCFG_DIVWC_Pos) & VADC_GLOBCFG_DIVWC_Msk);
                                        // DIVWC = 1: Write Control for Divider Parameters
                                        // Bitfields DIVA, DCMSB, DIVD can be written

	//Arbitration
	VADC_G0->ARBCFG   =  ((VADC_G0->ARBCFG &
                       	 ~(VADC_G_ARBCFG_ANONC_Msk | VADC_G_ARBCFG_ARBRND_Msk | VADC_G_ARBCFG_ARBM_Msk)) |
                                        // Clear relevant bits
                       	 (((3 << VADC_G_ARBCFG_ANONC_Pos) & VADC_G_ARBCFG_ANONC_Msk) |
                                        // ANONS = 11B: Analog Converter Control: Normal Operation
                                        //  The converter is active, conversions are started immediately.
                                        //  Requires no wakeup time.
                       	 ((0 << VADC_G_ARBCFG_ARBRND_Pos) & VADC_G_ARBCFG_ARBRND_Msk)|
                                        // ARBRND = 00B: Arbitration Round Length
                                        //  00B: 4 arbitration slots per round (tARB = 4 / fADCD)
                         ((0 << VADC_G_ARBCFG_ARBM_Pos) & VADC_G_ARBCFG_ARBM_Msk)));
                                        // ARBM = 0B: Arbitration Mode: The arbiter runs permanently
  
	VADC_G0->ARBPR    =  ((VADC_G0->ARBPR &
                         ~(VADC_G_ARBPR_ASEN2_Msk | VADC_G_ARBPR_PRIO0_Msk)) |
                                        // clear relevant bits
                         (((1 << VADC_G_ARBPR_PRIO0_Pos) & VADC_G_ARBPR_PRIO0_Msk) |
                                        // PRIO0 = 1: Priority of Request Source x (x = 0)
                                        //  Arbitration priority of request source x (in slot x)
                         ((1 << VADC_G_ARBPR_ASEN2_Pos) & VADC_G_ARBPR_ASEN2_Msk)));
                                        // ASEN2 = 1: Arbitration Slot 2 Enable

	//Conversion result storage
	VADC_G0->CHCTR[1] =  ((0x1 << VADC_G_CHCTR_RESREG_Pos) & VADC_G_CHCTR_RESREG_Msk);
                                        // Channel 1 is directed to RESREG1
                                        //  0001B Store result in group result register GxRES1
                                        //  = VADC_G0->RES[1]

	//BACKGROUND SOURCE
	VADC->BRSSEL[0]   =  (1UL << 1);
                                        // CHSELG1 = 1: Channel Selection Group 0: Channel 1
                                        //  1B This channel is part of the scan sequence

	VADC->BRSCTRL     =  ((0 << VADC_BRSCTRL_XTSEL_Pos) & VADC_BRSCTRL_XTSEL_Msk) |
                                        // XTSEL = 0: External Trigger Input Selection
                                        //   not used: see XTMODE
                         ((0 << VADC_BRSCTRL_XTMODE_Pos) & VADC_BRSCTRL_XTMODE_Msk) |
                                        // XTMODE = 0: Trigger Operating Mode: No external trigger
                         ((1 << VADC_BRSCTRL_XTWC_Pos) & VADC_BRSCTRL_XTWC_Msk) |
                                        // XTWC = 1: Write Control for Trigger Configuration
                                        //  Bitfields XTMODE and XTSEL can be written
                         ((0 << VADC_BRSCTRL_GTSEL_Pos) & VADC_BRSCTRL_GTSEL_Msk) |
                                        // GTSEL = 0: Gate Input Selection
                         ((1 << VADC_BRSCTRL_GTWC_Pos) & VADC_BRSCTRL_GTWC_Msk);
                                        // GTWC = 1: Write Control for Gate Configuration
                                        //  Bitfield GTSEL can be written

	VADC->BRSMR       =  ((1 << VADC_BRSMR_ENGT_Pos) & VADC_BRSMR_ENGT_Msk) |
                                        // ENGT = 1: Enable Gate: 01B Conversion requests are
                                        //  issued if at least one pending bit is set
                       	 ((0 << VADC_BRSMR_ENTR_Pos) & VADC_BRSMR_ENTR_Msk) |
                                        // ENTR = 0: Enable External Trigger: 0B External trigger disabled
                         ((0 << VADC_BRSMR_ENSI_Pos) & VADC_BRSMR_ENSI_Msk) |
                                        // ENSI = 0: Enable Source Interrupt: 0B No request source interrupt
                         ((1 << VADC_BRSMR_SCAN_Pos) & VADC_BRSMR_SCAN_Msk) |
                                        // SCAN = 1: Autoscan Enable: 1B Autoscan functionality enabled:
                                        //  a request source event automatically generates a load event
                         ((0 << VADC_BRSMR_LDM_Pos) & VADC_BRSMR_LDM_Msk) |
                                        // LDM = 0: Autoscan Source Load Event Mode:
                                        //  0B Overwrite mode: Copy all bits from the select registers to the
                                        //  pending registers upon a load event
                         ((1 << VADC_BRSMR_LDEV_Pos) & VADC_BRSMR_LDEV_Msk);
                                        // LDEV = 1: Generate Load Event: 1B A load event is generated
                                        //  it is important to have a load event in initialization!
                                        //  after that autoscan takes control
}


/**
 * @brief Inserts a delay time based on system timer configuration\n
 *
 * @param[in]   Time  Specifies the delay time length, in 100 micro seconds multiples\n
 * @return none\n
 *
 * <b>Reentrancy:  no</b><BR>
 *
 */
void Delay100US (unsigned long time)
{
	timingdelay =  time;
	while (timingdelay != 0);             //timingdelay is modified upon a system timer overflow in SysTick_Handler routine
}



/**
 * @brief SysTick_Handler is called after every System Timer overflow \n
 *
 * @param[in] none\n
 * @return none\n
 *
 * <b>Reentrancy:  no</b><BR>
 *
 */
void SysTick_Handler (void)             // SysTick Interrupt Handler
{
	if(timingdelay != 0x00){
		timingdelay--;                    //Decrease the time counter timingdelay
    }

}

/*Hint: for register modification, user might use next macros declared in XMC4500.h
*
* -- Macro to write new value to the bits in register
*#define WR_REG(reg, mask, pos, val) {  \
                     reg &= ~(mask);\
                     reg |= (val << pos) & mask;\
                    }

* -- Macro to read the bits in register
*#define RD_REG(reg, mask, pos)            (((reg)&mask) >> pos)
* -- Macro to set the particular bit in register
*#define SET_BIT(reg, pos)                 (reg) |= (1U<<pos)
* -- Macro to clear the particular bit in register
*#define CLR_BIT(reg, pos)                 (reg) &= ~(1U<<pos)
*/
