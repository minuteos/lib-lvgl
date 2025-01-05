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

#include <lvgl/Object.h>
#include <lvgl/Container.h>
#include <lvgl/Screen.h>
#include <lvgl/Widgets.h>

namespace lvgl
{

class Lvgl
{
public:
    //! Intializes display of a specified size using the specified driver
    void Initialize(Display& display, AsyncDelegate<> render, int width, int height, lv_color_format_t colorFormat = LV_COLOR_FORMAT_NATIVE, int bufferSplit = 1);

private:
    async(Task);

    static void LvInvalidate(lv_event_t* e);
    void Invalidate(lv_area_t* area);
    static void LvFlush(lv_display_t* display, const lv_area_t* area, uint8_t* px_map);
    void Flush(const lv_area_t* area, uint8_t* px_map, size_t stride, bool last);

    Display* disp;
    AsyncDelegate<> render;
    lv_disp_t* lvd;
    uint8_t stack[LV_DRAW_THREAD_STACK_SIZE];
};

extern Lvgl lvgl;

}
