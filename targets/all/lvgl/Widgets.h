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
    Label(ObjRef parent) : LvObject(parent) {}

    void SetText(const char* text)
        { lv_label_set_text(Obj(), text); }
    template<typename... Args> void SetTextFormat(const char* format, Args... args)
        { lv_label_set_text_fmt(Obj(), format, args...); }
    const char* GetText() const
        { return lv_label_get_text(Obj()); }

    void SetLongMode(lv_label_long_mode_t mode)
        { lv_label_set_long_mode(Obj(), mode); }
    lv_label_long_mode_t GetLongMode() const
        { return lv_label_get_long_mode(Obj()); }
};

#endif

#if LV_USE_IMAGE

LV_BIND_CLASS(lv_image_t, lv_image_class);

class Image : public LvObject<lv_image_t>
{
public:
    Image(ObjRef parent) : LvObject(parent) {}
};

#endif

#if LV_USE_LIST

struct lv_list_t : lv_obj_t {}; // there is no lv_list_t in LVGL

LV_BIND_CLASS(lv_list_t, lv_list_class);

class List : public LvObject<lv_list_t>
{
public:
    List(ObjRef parent) : LvObject(parent) {}

    ObjectWrapper AddText(const char* text)
        { return lv_list_add_text(Obj(), text); }
    ObjectWrapper AddButton(const void* icon, const char* text)
        { return lv_list_add_button(Obj(), icon, text); }
};

#endif

}
