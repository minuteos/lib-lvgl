/*
 * Copyright (c) 2024 triaxis s.r.o.
 * Licensed under the MIT license. See LICENSE.txt file in the repository root
 * for full license information.
 *
 * lvgl/lvgl-support.c
 *
 * Custom implementations of lv_ for better code sharing
 */

#include <base/format.h>

int lv_snprintf(char * buffer, size_t count, const char * format, ...)
{
    va_list va;
    va_start(va, format);
    const int ret = vsniprintf(buffer, count, format, va);
    va_end(va);
    return ret;
}

int lv_vsnprintf(char * buffer, size_t count, const char * format, va_list va)
{
    return vsniprintf(buffer, count, format, va);
}
