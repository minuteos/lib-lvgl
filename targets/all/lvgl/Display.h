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
    //! Adusts the area to be flushed so it satisfies any constraints required by the display
    virtual void AdjustFlushArea(lv_area_t* area) = 0;
    //! Asks the driver to flush the specified area to output display
    /*!
     * @param data pixel data to update, assumed to be reusable after this method returns
     * @param stride specifies the stride of one row of pixel data
     * @param last is true for the last flush that is part of one refresh
     */
    virtual void Flush(const lv_area_t* area, const uint8_t* data, size_t stride, bool last) = 0;
};

}
