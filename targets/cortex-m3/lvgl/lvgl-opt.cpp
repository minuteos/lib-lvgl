/*
 * Copyright (c) 2024 triaxis s.r.o.
 * Licensed under the MIT license. See LICENSE.txt file in the repository root
 * for full license information.
 *
 * cortex-m/lvgl/lvgl-opt.cpp
 */

#define LV_USE_PRIVATE_API  1

#include "lvgl-opt.h"

OPTIMIZE void lv_draw_arm_blend_color_to_i1(bool set, lv_draw_sw_blend_fill_dsc_t * dsc)
{
    unsigned w = dsc->dest_w;
    unsigned o = dsc->relative_area.x1 & 7;
    auto p = (uint8_t*)dsc->dest_buf;
    unsigned s = dsc->dest_stride;
    auto e = p + s * dsc->dest_h;

    while (w)
    {
        unsigned n = 32 - o;
        if (n > w) { n = w; }
        uint32_t mask = __REV(__RBIT(MASK(n) << o));    // create a mask to apply to all rows
        o = 0;
        w -= n;

        if (set)
        {
            for (auto pp = p; pp < e; pp += s) { *(uint32_t*)pp |= mask; }
        }
        else
        {
            mask = ~mask;
            for (auto pp = p; pp < e; pp += s) { *(uint32_t*)pp &= mask; }
        }
        p += 4;
    }
}