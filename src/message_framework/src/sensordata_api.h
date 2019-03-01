/*
 * sensordata_api.h
 *
 *  Created on: 22/02/2019
 *      Author: alana
 */

#ifndef SENSORDATA_API_H_
#define SENSORDATA_API_H_

#define NUMCHANNELS (uint8_t)10

#include "sf_message_api.h" //this is a message, so the message api is needed

typedef struct sensordata_payload_s
{
    sf_message_header_t header; //every message must include a header of this type
    union
    {
        uint32_t rpms;
        uint32_t duty_cycle;
    };
} sensordata_payload_t; //This name is specified in "Event Class" properties as "Payload Type"

#endif /* SENSORDATA_API_H_ */
