/*
 * Copyright (c) 2024 triaxis s.r.o.
 * Licensed under the MIT license. See LICENSE.txt file in the repository root
 * for full license information.
 *
 * lv_conf.h
 *
 * Extend base lv_conf with some optimized implementations
 */

#pragma once

#include_next <lv_conf.h>

#define LV_USE_DRAW_SW_ASM   LV_DRAW_SW_ASM_CUSTOM
#define LV_DRAW_SW_ASM_CUSTOM_INCLUDE    <lvgl/lvgl-opt.h>
