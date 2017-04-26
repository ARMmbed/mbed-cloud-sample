/**
 * @file    main.cpp
 * @brief   mbed Endpoint Sample main
 * @author  Doug Anson
 * @version 1.0
 * @see
 *
 * Copyright (c) 2014
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

// Use K64F Accelerometer
#define USE_K64F_ACCELEROMETER		true

// Use mbedApplicationShield resources 
#define USE_APP_SHIELD_RESOURCES	false

// Include security.h
#include "security.h"

// mbed Endpoint Network
#include "mbed-connector-interface/mbedEndpointNetwork.h"

// Logger
#include "mbed-connector-interface/Logger.h"
Serial pc(USBTX,USBRX);
Logger logger(&pc);

// Sample Static Resource
#include "mbed-connector-interface/StaticResource.h"
StaticResource static_sample(&logger,"101","1010","hello mbed");

// Sample Dynamic Resource (a counter)
#include "mbed-endpoint-resources/SampleDynamicResource.h"
SampleDynamicResource sample_counter(&logger,"123","4567",true);			// "true" -> resource is observable

// Light Resource
#include "mbed-endpoint-resources/LightResource.h"
LightResource light(&logger,"311","5850");

// AppShield has its own accelerometer and temperature sensors
#if USE_APP_SHIELD_RESOURCES
    // Temperature Resource
    #include "mbed-endpoint-resources/TemperatureResource.h"
    TemperatureResource temperature(&logger,"303","5700",true);            // "true" --> resource is observable

    // MMA7660 Accelerometer Resource
    #include "mbed-endpoint-resources/MMAccelerometerResource.h"
    MMAccelerometerResource accel(&logger,"888","7700",true);              // "true" --> resource is observable
#endif // USE_APP_SHIELD_RESOURCES

// K64F has an embedded accelerometer
#if USE_K64F_ACCELEROMETER
    // FXQ Accelerometer Resource
    #include "mbed-endpoint-resources/FXAccelerometerResource.h"
    FXAccelerometerResource accel(&logger,"888","7700",true);              // "true" --> resource is observable
#endif // USE_K64F_ACCELEROMETER

// called from the Endpoint::start() below to create resources and the endpoint internals...
Connector::Options *configure_endpoint(Connector::OptionsBuilder &config)
{    
    // Build the endpoint configuration parameters
    logger.log("Endpoint::main (%s): customizing endpoint configuration...",net_get_type());
    return config                 
        // add a Sample Static Resource
        .addResource(&static_sample)
                 
        // add a Sample Counter (Dynamic Resource)
        .addResource(&sample_counter,10000)			// observe every 10 seconds
                   
        // Add my specific physical dynamic resources...

	// LED light that we can toggle on and off...
        .addResource(&light)

#if USE_APP_SHIELD_RESOURCES
	// Temperature sensor (LM75B)
        .addResource(&temperature,8000) 			// observe every 8 seconds 

	// MMA7660 Accelerometer
        .addResource(&accel,13000)				    // observe every 13 seconds
#endif // USE_APP_SHIELD_RESOURCES

#if USE_K64F_ACCELEROMETER
	// K64F FXOS8700CQ Accelerometer
	.addResource(&accel,(bool)false)            // observe on demand ("shake"...)
#endif // USE_K64F_ACCELEROMETER
                   
        // finalize the configuration...
        .build();
}

// main entry point...
int main()
{
    // set Serial
    pc.baud(115200);
	
    // Announce
    logger.log("\r\n\r\nmbed Cloud Sample Endpoint (%s)",net_get_type());
    
    // we have to plumb our network first
    Connector::Endpoint::plumbNetwork(NULL);
    
    // starts the endpoint by finalizing its configuration (configure_endpoint() above called),creating a Thread and reading mbed Cloud events...
    Connector::Endpoint::start();
}
