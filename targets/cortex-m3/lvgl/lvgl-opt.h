/*
 * Copyright (c) 2024 triaxis s.r.o.
 * Licensed under the MIT license. See LICENSE.txt file in the repository root
 * for full license information.
 *
 * cortex-m/lvgl/lvgl-opt.h
 *
 * Optimized implementations of some basic monochrome LVGL functions
 */

#pragma once

#include <base/base.h>

#include <lvgl.h>

EXTERN_C void lv_draw_arm_blend_color_to_i1(bool set, lv_draw_sw_blend_fill_dsc_t * dsc);

#define LV_DRAW_SW_COLOR_BLEND_TO_I1(dsc)    (lv_draw_arm_blend_color_to_i1(src_color, dsc), LV_RESULT_OK)
