/*
 * Copyright (c) 2024 triaxis s.r.o.
 * Licensed under the MIT license. See LICENSE.txt file in the repository root
 * for full license information.
 *
 * lvgl/Screen.h
 */

#pragma once

#include <lvgl/lvgl.h>

namespace lvgl
{

class Screen : public Container
{
public:
    Screen() : Container((lv_obj_t*)NULL) {}

    void Load() { lv_screen_load(*this); }
};

}
