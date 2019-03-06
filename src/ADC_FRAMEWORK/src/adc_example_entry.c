/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2017 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
#include <stdio.h>
#include "adc_example.h"
#include "sf_adc_periodic_api.h"


#define UNUSED(x) (void)(x)
void adc_example_entry(void);

#define SEMI_HOSTING

#ifdef SEMI_HOSTING
#include "stdio.h"
    /* GCC Compiler */
    #ifdef __GNUC__
        extern void initialise_monitor_handles(void);
    #endif
#endif


/**********************************************************************************************************************
  This project demonstrates the typical use of the ADC Periodic framework module APIs. The thread entry initializes the ADC
  Periodic Framework and periodically scans the temperature sensor. The scan result is placed in a user-specified
  buffer. A user-callback function is entered when the scan result is available. The user-specified callback function
  prints the result on the debug console using the common semi-hosting function.
 */


/* ADC framework example thread entry function */
void adc_example_entry(void)
{
    /* variable to capture ADC errors */
    ssp_err_t err = SSP_SUCCESS;

    #ifdef SEMI_HOSTING
            /* GCC Compiler */
        #if   defined(__GNUC__)
            initialise_monitor_handles();
        #endif
    #endif

    /* Initialize the ADC Framework*/
    err = (g_sf_adc_periodic0.p_api->open(g_sf_adc_periodic0.p_ctrl, g_sf_adc_periodic0.p_cfg));
    if(err != SSP_SUCCESS)
    {
        #ifdef SEMI_HOSTING
            if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
            {
                printf("Failed to open ADC framework, error:%d\n",err);
            }
        #endif
        tx_thread_sleep(TX_WAIT_FOREVER);
    }

    while (1)
    {
        /* Start the ADC scan */
        err = (g_sf_adc_periodic0.p_api->start(g_sf_adc_periodic0.p_ctrl));
        if(err != SSP_SUCCESS)
        {
            // Add Error correction mechanism
            #ifdef SEMI_HOSTING
                if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
                {
                    printf("Failed to start ADC framework, error:%d\n",err);
                }
            #endif
            tx_thread_sleep(TX_WAIT_FOREVER);
        }

        /* Stop the scan */
        err = (g_sf_adc_periodic0.p_api->stop(g_sf_adc_periodic0.p_ctrl));
        if(err != SSP_SUCCESS)
        {
            // Add Error correction mechanism
            #ifdef SEMI_HOSTING
                if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
                {
                    printf("Failed to stop ADC framework, error:%d\n",err);
                }
            #endif
            tx_thread_sleep(TX_WAIT_FOREVER);
        }
    }
}

void g_adc_framework_user_callback(sf_adc_periodic_callback_args_t * p_args)
{
    UNUSED(p_args);

        /* Read conversion result of 10 samples from buffer */
    #ifdef SEMI_HOSTING
       if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
       {
           /* Print the value measured by the ADC */
           printf("Internal Temperature Sensor value measured by ADC: %d\n", g_user_buffer[p_args->buffer_index]);
       }
    #endif
}



