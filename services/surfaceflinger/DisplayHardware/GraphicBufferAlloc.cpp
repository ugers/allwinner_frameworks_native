/*
 **
 ** Copyright 2012 The Android Open Source Project
 **
 ** Licensed under the Apache License Version 2.0(the "License");
 ** you may not use this file except in compliance with the License.
 ** You may obtain a copy of the License at
 **
 **     http://www.apache.org/licenses/LICENSE-2.0
 **
 ** Unless required by applicable law or agreed to in writing software
 ** distributed under the License is distributed on an "AS IS" BASIS
 ** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND either express or implied.
 ** See the License for the specific language governing permissions and
 ** limitations under the License.
 */

#include <cutils/log.h>

#include <ui/GraphicBuffer.h>

#include "DisplayHardware/GraphicBufferAlloc.h"

// ----------------------------------------------------------------------------
namespace android {
// ----------------------------------------------------------------------------

GraphicBufferAlloc::GraphicBufferAlloc() {
}

GraphicBufferAlloc::~GraphicBufferAlloc() {
}

sp<GraphicBuffer> GraphicBufferAlloc::createGraphicBuffer(uint32_t w, uint32_t h,
        PixelFormat format, uint32_t usage, status_t* error) {
    sp<GraphicBuffer> graphicBuffer(new GraphicBuffer(w, h, format, usage));
    status_t err = graphicBuffer->initCheck();
	ALOGI("GraphicBufferAlloc::createGraphicBuffer ");
    *error = err;
    if (err != 0 || graphicBuffer->handle == 0) {
		ALOGI("GraphicBufferAlloc::createGraphicBuffer00 ");
        if (err == NO_MEMORY) {
			ALOGI("GraphicBufferAlloc::createGraphicBuffer11 ");
            GraphicBuffer::dumpAllocationsToSystemLog();
        }
        ALOGE("GraphicBufferAlloc::createGraphicBuffer(w=%d, h=%d) "
             "failed (%s), handle=%p",
                w, h, strerror(-err), graphicBuffer->handle);
        return 0;
    }
    return graphicBuffer;
}

// ----------------------------------------------------------------------------
}; // namespace android
// ----------------------------------------------------------------------------
