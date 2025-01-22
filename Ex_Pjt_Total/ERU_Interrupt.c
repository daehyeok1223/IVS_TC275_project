/**********************************************************************************************************************
 * \file ERU_Interrupt.c
 * \copyright Copyright (C) Infineon Technologies AG 2019
 * 
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of 
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and 
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all 
 * derivative works of the Software, unless such copies or derivative works are solely in the form of 
 * machine-executable object code generated by a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE 
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN 
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 *********************************************************************************************************************/


/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "ERU_Interrupt.h"
#include "GPIO_Setting_Ex.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define ISR_PRIORITY_SCUERU_INT0   40                       /* Define the SCU ERU interrupt priority                */
#define REQ_IN                     &IfxScu_REQ14_P02_1_IN   /* External request pin (defined @IfxScu_PinMap.c       */

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
ERUconfig g_ERUconfig;

/*********************************************************************************************************************/
/*--------------------------------------------Private Variables/Constants--------------------------------------------*/
/*********************************************************************************************************************/
 volatile Ifx_SRC_SRCR *src;                 /* Service request register                                         */

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
/* Interrupt definition */
IFX_INTERRUPT(SCUERU_Int0_Handler, 0, ISR_PRIORITY_SCUERU_INT0);

/* Interrupt Service Routine */
void SCUERU_Int0_Handler(void)
{
    IfxPort_setPinLow(RGBR_LED);
    IfxPort_setPinLow(RGBG_LED);
    IfxPort_setPinLow(RGBB_LED);
}

void init_eru(void)
{
      /* initialize external request pin */
        g_ERUconfig.reqPin = REQ_IN; /* Select external request pin */
        IfxScuEru_initReqPin(g_ERUconfig.reqPin, IfxPort_InputMode_pullUp);

      /* Select which edge should trigger the interrupt */
        g_ERUconfig.inputChannel = (IfxScuEru_InputChannel) g_ERUconfig.reqPin->channelId;
        IfxScuEru_enableRisingEdgeDetection(g_ERUconfig.inputChannel);

       /* Enable generation of trigger events with the function    */
        /* Signal destination */
        g_ERUconfig.outputChannel = IfxScuEru_OutputChannel_2;                  /* OGU channel 0                    */
         /* Event from input ETL0 triggers output OGU0 (signal TRx0) */
        g_ERUconfig.triggerSelect = IfxScuEru_InputNodePointer_2;

        IfxScuEru_enableTriggerPulse(g_ERUconfig.inputChannel);

     /* Choose the output channel by selecting the Output Gating Unit (OGUz) and the trigger pulse output (TRxz) */
        IfxScuEru_connectTrigger(g_ERUconfig.inputChannel, g_ERUconfig.triggerSelect);

        /*Select the condition to generate an interrupt with the function */
        IfxScuEru_setInterruptGatingPattern(g_ERUconfig.outputChannel, IfxScuEru_InterruptGatingPattern_alwaysActive);

        /* Configure and enable the service request  */
        g_ERUconfig.src = &MODULE_SRC.SCU.SCU.ERU[(int) g_ERUconfig.outputChannel % 4];
        IfxSrc_init(g_ERUconfig.src, IfxSrc_Tos_cpu0, ISR_PRIORITY_SCUERU_INT0);
        IfxSrc_enable(g_ERUconfig.src);
}
