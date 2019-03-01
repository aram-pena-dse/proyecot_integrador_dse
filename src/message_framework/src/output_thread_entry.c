#include "output_thread.h"
#include "sensordata_api.h"
#include "stdio.h"

extern void initialise_monitor_handles(void);

/* Output Thread entry function */
//static volatile uint8_t uartdone=0;

//void user_uart_callback(uart_callback_args_t *p_args)
//{
//    if (p_args->event == UART_EVENT_TX_COMPLETE)
//        uartdone=1;
//    return;
//}

void output_thread_entry(void)
{
    initialise_monitor_handles();
    printf("initialize output thread\n");

    uint8_t cstr[18*NUMCHANNELS];// = "Channel X: 12345\n"; //the text to be sent, stored as unsigned 8 bit data.

//    g_uart0.p_api->open(g_uart0.p_ctrl, g_uart0.p_cfg); //initialization of the UART module

    sf_message_header_t * pHeader; //pointer to the message header
    sensordata_payload_t * thepayload; //pointer to the message payload

    while (1)
    {
        g_sf_message0.p_api->pend(g_sf_message0.p_ctrl, &output_thread_message_queue,
                                  &pHeader, TX_WAIT_FOREVER); //wait for a message forever

        if (pHeader->event_b.class_code == SF_MESSAGE_EVENT_CLASS_SENSORDATA) //if the message if the right kind
        {
            thepayload = (sensordata_payload_t *) pHeader; //cast the received message to the custom type
            if (thepayload->header.event_b.code == SF_MESSAGE_EVENT_NEW_DATA) //if the message event is the right kind
            {

                printf("receive message from computation, class_instance: %d, duty_cycle: %d\n",
                       thepayload->header.event_b.class_instance,
                       thepayload->duty_cycle);
                //spit out to UART
//                for (uint8_t index=0; index<NUMCHANNELS; index++)
//                {
//                    sprintf(cstr +index*18, "Channel %1c: %5d\n", thepayload->sensorchannel[index]+'0', thepayload->sensordata[index]);
//                }
//                g_uart0.p_api->write(g_uart0.p_ctrl, cstr, 18*NUMCHANNELS); //send the information over UART
//                while(uartdone==0); //block until uart completes
//                uartdone=0;
                g_sf_message0.p_api->bufferRelease(g_sf_message0.p_ctrl, pHeader, SF_MESSAGE_RELEASE_OPTION_NONE);
            }
        }
        tx_thread_sleep (1);
    }
}
