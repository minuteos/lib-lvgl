/*
 * Copyright (c) 2024 triaxis s.r.o.
 * Licensed under the MIT license. See LICENSE.txt file in the repository root
 * for full license information.
 *
 * lvgl/Display.h
 */

#pragma once

#include <base/base.h>

#include <lvgl.h>

namespace lvgl
{

//! Interface for an LVGL display
class Display
{
public:
    //! Informs the driver of the LVGL buffer size so it can initialize its own internal buffer
    virtual void BufferSize(size_t stride, size_t rows) = 0;
    //! Adusts the area to be flushed so it satisfies any constraints required by the display
    virtual void AdjustFlushArea(lv_area_t* area) = 0;
    //! Asks the driver to flush the specified area to output display
    /*!
     * Note: @param data is assumed to be reusable after this method returns
     */
    virtual void Flush(const lv_area_t* area, const uint8_t* data) = 0;
    //! Should return after the last flushed data is visible on display, i.e. next frame can be prepared
    virtual async_once(Sync) = 0;
};

}
