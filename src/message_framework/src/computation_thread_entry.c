#include "computation_thread.h"
#include "sensordata_api.h"
#include <stdio.h>

extern void initialise_monitor_handles(void);
static uint32_t duty_cycle = 0;

/* Computation Thread entry function */
void computation_thread_entry(void)
{
    initialise_monitor_handles();
    printf("initialize computation thread\n");

    //Messaging init
    ////Recieving init
    sf_message_header_t * pSensorDataHeader; //pointer to the message header
    sensordata_payload_t * pSensorDataPayload; //pointer to the message payload

    ////Sending init
    sf_message_header_t * pOutputBuffer; //pointer for the buffer that must be acquired
    sf_message_acquire_cfg_t acquireCfgPost = {.buffer_keep =false}; //could keep the buffer, because this thread is the only one posting to the receiving thread
    ssp_err_t errorBuffPost; //place for error codes from buffer acquisition to go
    sf_message_post_err_t errPost; //place for posting error codes to go
    sf_message_post_cfg_t post_cfg =
    {
      .priority = SF_MESSAGE_PRIORITY_NORMAL, //normal priority
      .p_callback = NULL //no callback needed
    };
    sensordata_payload_t * pOutputPost; //pointer to data to be sent to uart

    uint16_t lastknownsensor1values[NUMCHANNELS]; //buffer to keep sensor1 readings in
    uint16_t lastknownsensor2values[NUMCHANNELS]; //buffer to keep sensor2 readings in

    while (1)
    {
        g_sf_message0.p_api->pend(g_sf_message0.p_ctrl, &computation_thread_message_queue,
                             &pSensorDataHeader, TX_NO_WAIT); //if a message has been posted to the queue, store its address in pSensorDataHeader

        if (pSensorDataHeader->event_b.class_code == SF_MESSAGE_EVENT_CLASS_SENSORDATA) //if the message is the right kind
        {
            pSensorDataPayload = (sensordata_payload_t *) pSensorDataHeader; //cast the received message to the custom type
            //store the sensor information in some buffers, this part is application dependent
            if (pSensorDataPayload->header.event_b.code == SF_MESSAGE_EVENT_NEW_DATA) //if the message event is the right kind
            {
                if (pSensorDataPayload->header.event_b.class_instance ==0) //from sensor 1
                {
                    printf("receive message from sensor 1, class_instance: %d, rpms: %d\n",
                           pSensorDataPayload->header.event_b.class_instance,
                           pSensorDataPayload->rpms);
                }
                if (pSensorDataPayload->header.event_b.class_instance ==1) //from sensor 2
                {
                    printf("receive message from sensor 2, class_instance: %d, rpms: %d\n",
                           pSensorDataPayload->header.event_b.class_instance,
                           pSensorDataPayload->rpms);
                }
                g_sf_message0.p_api->bufferRelease(g_sf_message0.p_ctrl, pSensorDataHeader, SF_MESSAGE_RELEASE_OPTION_NONE);
            }
        }

        //send a message about the most recent sensor data
        errorBuffPost = g_sf_message0.p_api->bufferAcquire(g_sf_message0.p_ctrl, &pOutputBuffer, &acquireCfgPost, 300); //attempt to acquire the posting buffer
        if (errorBuffPost==SSP_SUCCESS)
        {
            pOutputPost = (sensordata_payload_t *) pOutputBuffer; //cast buffer to our payload
            pOutputPost->header.event_b.class_code = SF_MESSAGE_EVENT_CLASS_SENSORDATA; //set the event class
            pOutputPost->header.event_b.class_instance = 2; //set the class instance
            pOutputPost->header.event_b.code = SF_MESSAGE_EVENT_NEW_DATA; //set the message type

            pOutputPost->duty_cycle = duty_cycle++;

            g_sf_message0.p_api->post(g_sf_message0.p_ctrl, (sf_message_header_t *) pOutputPost,
                                                          &post_cfg, &errPost, TX_WAIT_FOREVER); //post the message
        }
        tx_thread_sleep (50);
    }
}
