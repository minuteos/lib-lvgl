/*
 * Copyright (c) 2025 triaxis s.r.o.
 * Licensed under the MIT license. See LICENSE.txt file in the repository root
 * for full license information.
 *
 * lvgl/Widgets.cpp
 */

#include "Widgets.h"

#include <base/Span.h>

namespace lvgl
{

#if LV_USE_LABEL

void Label::SetTextIfChanged(const char *text)
{
    if (strcmp(lv_label_get_text(Obj()), text))
    {
        lv_label_set_text(Obj(), text);
    }
}

void Label::SetTextFormatIfChanged(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char buffer[64];
    Buffer(buffer).FormatSZVA(format, args);
    SetTextIfChanged(buffer);
}

#endif

}
