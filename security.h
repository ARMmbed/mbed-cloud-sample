/*
 * Copyright (c) 2015 ARM Limited. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __SECURITY_H__
#define __SECURITY_H__

// We will use mbed Cloud Support
#define ENABLE_MBED_CLOUD_SUPPORT       true

// Storage handling for Updater (wont reset storage on each reboot...)
#define MBED_CLOUD_STORAGE_INIT		true
// #define MBED_RESET_STORAGE		true

// We will use the developer flow 
#define MBED_CLOUD_DEV_FLOW_INIT	true

// mbed Cloud includes
#include "mbed-cloud-client/MbedCloudClient.h"
#include "mbed_cloud_client_user_config.h"

#endif // __SECURITY_H__
