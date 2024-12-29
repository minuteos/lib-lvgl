/*
 * Copyright (c) 2024 triaxis s.r.o.
 * Licensed under the MIT license. See LICENSE.txt file in the repository root
 * for full license information.
 *
 * lvgl/Widgets.h
 *
 * C++ wrappers of standard LVGL widgets
 */

#pragma once

#include <lvgl/lvgl.h>

namespace lvgl
{

#if LV_USE_LABEL

LV_BIND_CLASS(lv_label_t, lv_label_class);

class Label : public LvObject<lv_label_t>
{
public:
    Label(lv_obj_t* parent) : LvObject(parent) {}

    template<typename... Args> void SetTextFormat(const char* format, Args... args)
        { lv_label_set_text_fmt(*this, format, args...); }
};

#endif

#if LV_USE_IMAGE

LV_BIND_CLASS(lv_image_t, lv_image_class);

class Image : public LvObject<lv_image_t>
{
public:
    Image(lv_obj_t* parent) : LvObject(parent) {}
};

#endif

}
