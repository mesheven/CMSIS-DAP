/* CMSIS-DAP Interface Firmware
 * Copyright (c) 2009-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <LPC11Uxx.h>
#include "uart.h"


// Size must be 2^n
#define  BUFFER_SIZE          (64)

#define PIN_UART_TX       (1<<19)
#define PIN_UART_RX       (1<<18)
#define PIN_UART_RTS      (1<<17)
#define PIN_UART_CTS      (1<<7)


UART_Configuration	dummycfg;


int32_t uart_initialize (void) {
		//init to GPIOs
    // enable clock for GPIO port 0
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6);

    // configure TX(p019)output
    LPC_GPIO->DIR[0]  |= (PIN_UART_TX);
    LPC_GPIO->CLR[0]  |= (PIN_UART_TX);
	
    // configure RX(p018)intput
    LPC_GPIO->DIR[0]  &= ~(PIN_UART_RX);
	
    // configure CTS(p07)intput
    LPC_GPIO->DIR[0]  &= ~(PIN_UART_CTS);
	
    // configure RTS(p017)output
    LPC_GPIO->DIR[0]  |= (PIN_UART_RTS);
    LPC_GPIO->CLR[0]  |= (PIN_UART_RTS);	
	
		dummycfg.Baudrate = 9600;
		dummycfg.DataBits = UART_DATA_BITS_8;
	  dummycfg.Parity = UART_PARITY_NONE;
		dummycfg.StopBits = UART_STOP_BITS_1;
		dummycfg.FlowControl = UART_FLOW_CONTROL_NONE;
	
    return 1;
}


int32_t uart_uninitialize (void) {

    return 1;
}


int32_t uart_reset (void) {


    return 1;
}


int32_t uart_set_configuration (UART_Configuration *config) {
	
		dummycfg.Baudrate    = config->Baudrate;
		dummycfg.DataBits    = config->DataBits;
	  dummycfg.Parity      = config->Parity;
		dummycfg.StopBits    = config->StopBits;
		dummycfg.FlowControl = config->FlowControl;

    return 1;
}


int32_t uart_get_configuration (UART_Configuration *config) {

		config->Baudrate    = dummycfg.Baudrate;
		config->DataBits    = dummycfg.DataBits;
	  config->Parity      = dummycfg.Parity;
	  config->StopBits    = dummycfg.StopBits;
	  config->FlowControl = UART_FLOW_CONTROL_NONE;
	
    return 1;
}

int32_t uart_write_free(void) {
    return BUFFER_SIZE;
}

int32_t uart_write_data (uint8_t *data, uint16_t size) {

    return size;
}


int32_t uart_read_data (uint8_t *data, uint16_t size) {

    return 0;
}


void uart_gpio_update(void)
{
		//check RX/set TX
		if((LPC_GPIO->PIN[0] & (PIN_UART_RX)) == 0)
		{
				LPC_GPIO->SET[0] |= (PIN_UART_TX);
		}
		else
		{
				LPC_GPIO->CLR[0] |= (PIN_UART_TX);
		}
		
		//check CTS/set RTS
		if((LPC_GPIO->PIN[0] &(PIN_UART_CTS)) == 0)
		{
				LPC_GPIO->SET[0] |= (PIN_UART_RTS);
		}
		else
		{
				LPC_GPIO->CLR[0] |= (PIN_UART_RTS);
		}
}

/*------------------------------------------------------------------------------
 * End of file
 *----------------------------------------------------------------------------*/

