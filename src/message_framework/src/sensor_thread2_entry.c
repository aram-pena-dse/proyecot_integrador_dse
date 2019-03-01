#include "sensor_thread2.h"
#include "sensordata_api.h"
#include <stdio.h>

extern void initialise_monitor_handles(void);
static uint32_t rpms_tmp = 0;

/* Sensor Thread 2 entry function */
void sensor_thread2_entry(void)
{
    initialise_monitor_handles();
    printf("Initialize sensor thread 2\n");

    //Message init
    //sending sensordata init
    sf_message_header_t * pPostBuffer; //pointer for the buffer that must be acquired
    sf_message_acquire_cfg_t acquireCfg = {.buffer_keep =false}; //do not keep the buffer, other threads need it
    ssp_err_t errorBuff; //place for error codes from buffer acquisition to go
    sf_message_post_err_t errPost; //place for posting error codes to go
    sf_message_post_cfg_t post_cfg =
    {
      .priority = SF_MESSAGE_PRIORITY_NORMAL, //normal priority
      .p_callback = NULL //no callback needed
    };
    sensordata_payload_t * pDataPayload; //pointer to the receiving message payload

    while (1)
    {
        //send as message if possible
        errorBuff = g_sf_message0.p_api->bufferAcquire(g_sf_message0.p_ctrl, &pPostBuffer, &acquireCfg, 0);
        if (errorBuff==SSP_SUCCESS)
        {
            pDataPayload = (sensordata_payload_t *) pPostBuffer; //cast buffer to our payload
            pDataPayload->header.event_b.class_code = SF_MESSAGE_EVENT_CLASS_SENSORDATA; //set the event class
            pDataPayload->header.event_b.class_instance = 1; //set the class instance
            pDataPayload->header.event_b.code = SF_MESSAGE_EVENT_NEW_DATA; //set the message type
            pDataPayload->rpms = rpms_tmp++;

            g_sf_message0.p_api->post(g_sf_message0.p_ctrl, (sf_message_header_t *) pDataPayload,
                                      &post_cfg, &errPost, TX_WAIT_FOREVER); //post the message
        }
        tx_thread_sleep (100);
    }
}
