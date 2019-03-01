/* generated messaging source file - do not edit */
#include "sf_message.h"
#ifndef SF_MESSAGE_CFG_QUEUE_SIZE
#define SF_MESSAGE_CFG_QUEUE_SIZE (16)
#endif
TX_QUEUE computation_thread_message_queue;
static uint8_t queue_memory_computation_thread_message_queue[SF_MESSAGE_CFG_QUEUE_SIZE];
TX_QUEUE output_thread_message_queue;
static uint8_t queue_memory_output_thread_message_queue[SF_MESSAGE_CFG_QUEUE_SIZE];
static sf_message_subscriber_t computation_thread_message_queue_0_1 =
{ .p_queue = &computation_thread_message_queue, .instance_range =
{ .start = 0, .end = 1 } };
static sf_message_subscriber_t output_thread_message_queue_2_2 =
{ .p_queue = &output_thread_message_queue, .instance_range =
{ .start = 2, .end = 2 } };
static sf_message_subscriber_t * gp_group_SF_MESSAGE_EVENT_CLASS_SENSORDATA[] =
{ &computation_thread_message_queue_0_1, &output_thread_message_queue_2_2, };
static sf_message_subscriber_list_t g_list_SF_MESSAGE_EVENT_CLASS_SENSORDATA =
{ .event_class = (uint16_t) SF_MESSAGE_EVENT_CLASS_SENSORDATA, .number_of_nodes = 2, .pp_subscriber_group =
          gp_group_SF_MESSAGE_EVENT_CLASS_SENSORDATA };
sf_message_subscriber_list_t * p_subscriber_lists[] =
{ &g_list_SF_MESSAGE_EVENT_CLASS_SENSORDATA, NULL };
void g_message_init(void);
void g_message_init(void)
{
    tx_queue_create (&computation_thread_message_queue, (CHAR *) "Computation Thread Message Queue", 1,
                     &queue_memory_computation_thread_message_queue,
                     sizeof(queue_memory_computation_thread_message_queue));
    tx_queue_create (&output_thread_message_queue, (CHAR *) "Output Thread Message Queue", 1,
                     &queue_memory_output_thread_message_queue, sizeof(queue_memory_output_thread_message_queue));
}
