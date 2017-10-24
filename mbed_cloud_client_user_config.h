//----------------------------------------------------------------------------
// The confidential and proprietary information contained in this file may
// only be used by a person authorised under and to the extent permitted
// by a subsisting licensing agreement from ARM Limited or its affiliates.
//
// (C) COPYRIGHT 2016 ARM Limited or its affiliates.
// ALL RIGHTS RESERVED
//
// This entire notice must be reproduced on all copies of this file
// and copies of this file may only be made by a person if such person is
// permitted to do so under the terms of a subsisting license agreement
// from ARM Limited or its affiliates.
//----------------------------------------------------------------------------

#ifndef MBED_CLOUD_CLIENT_USER_CONFIG_H
#define MBED_CLOUD_CLIENT_USER_CONFIG_H

#define MBED_CLOUD_CLIENT_ENDPOINT_TYPE         "mbed-endpoint"
#define MBED_CLOUD_CLIENT_TRANSPORT_MODE_TCP
#define MBED_CLOUD_CLIENT_LIFETIME              120

#ifdef FREERTOS
    #define SN_COAP_MAX_BLOCKWISE_PAYLOAD_SIZE       512
#else
    #define MBED_CLOUD_CLIENT_SUPPORT_UPDATE
    #define SN_COAP_MAX_BLOCKWISE_PAYLOAD_SIZE       1024
#endif

/* set flag to enable update support in mbed Cloud client */
#ifndef FREERTOS
    #define MBED_CLOUD_CLIENT_SUPPORT_UPDATE
#endif
/* set download buffer size in bytes (min. 1024 bytes) */

/* Use larger buffers in Linux */
#ifdef __linux__
#define MBED_CLOUD_CLIENT_UPDATE_BUFFER          (2 * 1024 * 1024)
#else
#define MBED_CLOUD_CLIENT_UPDATE_BUFFER          2048
#endif

/* Developer flags for Update feature */
#ifdef MBED_CONF_APP_DEVELOPER_MODE
    #define MBED_CLOUD_DEV_UPDATE_CERT
    #define MBED_CLOUD_DEV_UPDATE_ID
#endif /* MBED_CONF_APP_DEVELOPER_MODE */

#endif /* MBED_CLOUD_CLIENT_USER_CONFIG_H */
