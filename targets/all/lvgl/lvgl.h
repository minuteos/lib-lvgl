/*
 * Copyright (c) 2024 triaxis s.r.o.
 * Licensed under the MIT license. See LICENSE.txt file in the repository root
 * for full license information.
 *
 * lvgl/lvgl.h
 *
 * Main header for LVGL integration into MinuteOS
 */

#pragma once

#include <kernel/kernel.h>

#include <lvgl.h>
#include <lvgl/Display.h>

namespace lvgl
{

class Lvgl
{
public:
    //! Intializes display of a specified size using the specified driver
    void Initialize(Display& display, int width, int height, lv_color_format_t colorFormat = LV_COLOR_FORMAT_NATIVE);

private:
    async(Handler);
    async(Refresh);

    static void LvInvalidate(lv_event_t* e);
    void Invalidate(lv_area_t* area);
    static void LvFlush(lv_display_t* display, const lv_area_t* area, uint8_t* px_map);
    void Flush(const lv_area_t* area, uint8_t* px_map);

    Display* disp;
    lv_disp_t* lvd;

    enum class Signal
    {
        Refresh = 1,
        Tick = 2,
    } signals;

    DECLARE_FLAG_ENUM(Signal);
};

DEFINE_FLAG_ENUM(Lvgl::Signal);

extern Lvgl lvgl;

}
