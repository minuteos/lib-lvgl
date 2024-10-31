/*
 * Copyright (c) 2024 triaxis s.r.o.
 * Licensed under the MIT license. See LICENSE.txt file in the repository root
 * for full license information.
 *
 * lv_conf.h
 *
 * Basic configuration, when overriding from app you can #include_next
 * this or override in full.
 */

#pragma once

#define LV_CONF_H

#define LV_USE_LOG  1

#define LV_USE_STDLIB_MALLOC    LV_STDLIB_CLIB
#define LV_USE_STDLIB_STRING    LV_STDLIB_CLIB
#define LV_USE_STDLIB_SPRINTF   LV_STDLIB_CUSTOM

// this is a lie, but it prevents LVGL from attributing the printf-like
// functions with format-checker that breaks on our custom directives
#define PYCPARSER
