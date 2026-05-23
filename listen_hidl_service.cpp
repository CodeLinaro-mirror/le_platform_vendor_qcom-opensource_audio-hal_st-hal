/*
 * Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
*/

// listen_hidl_service.cpp
#include <hidl/HidlTransportSupport.h>
#include <vendor/qti/hardware/ListenSoundModel/1.0/IListenSoundModel.h>
//#include "ListenSoundModel.h"   // your implementation class

//#include <hidl/HidlTransportSupport.h>
//#include <hidl/LegacySupport.h>
//#include <lsm_server_wrapper.h>
//
//#include <vendor/qti/hardware/ListenSoundModel/1.0/IListenSoundModel.h>
//using vendor::qti::hardware::ListenSoundModel::V1_0::IListenSoundModel;
//using vendor::qti::hardware::ListenSoundModel::V1_0::implementation::ListenSoundModel;
//using android::hardware::defaultPassthroughServiceImplementation;
//using namespace android::hardware;
using android::OK;
using android::sp;
using android::hardware::configureRpcThreadpool;
using vendor::qti::hardware::ListenSoundModel::V1_0::IListenSoundModel;
//using vendor::qti::hardware::ListenSoundModel::V1_0::implementation::ListenSoundModel;

extern "C" void register_lsm_hidl_service(void) {
    // Use HIDL getService() to get the implementation from the pre-built .so
    // The impl .so registers via HIDL lazy/passthrough mechanism
    //
    ALOGE("%s : get service IListenSoundModel::getService/default ",__func__);
    sp<IListenSoundModel> service = IListenSoundModel::getService("default", true /*getStub*/);
    				//new ListenSoundModel();
    if (service == nullptr) {
        ALOGE("%s: Failed to get IListenSoundModel implementation", __func__);
        return;
    }
    ALOGE("%s : Success registered LSM HIDL service ",__func__);
    configureRpcThreadpool(32, false /*callerWillJoin*/);
    if (android::OK != service->registerAsService()) {
        ALOGE("Failed to register LSM HIDL service");
    }
}
