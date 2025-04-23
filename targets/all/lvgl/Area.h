/*
 * Copyright (c) 2025 triaxis s.r.o.
 * Licensed under the MIT license. See LICENSE.txt file in the repository root
 * for full license information.
 *
 * lvgl/Area.h
 */

#pragma once

#include <base/base.h>

#include <lvgl.h>

namespace lvgl
{

class Area : public lv_area_t
{
public:
    constexpr int32_t Left() const { return x1; }
    constexpr int32_t Right() const { return x2; }
    constexpr int32_t Top() const { return y1; }
    constexpr int32_t Bottom() const { return y2; }
    constexpr int32_t MidX() const { return (x1 + x2) / 2; }
    constexpr int32_t MidY() const { return (y1 + y2) / 2; }

    constexpr int32_t Width() const { return x2 - x1 + 1; }
    constexpr int32_t Height() const { return y2 - y1 + 1; }

    constexpr bool operator ==(const Area& other) const
    {
        return x1 == other.x1 && x2 == other.x2 && y1 == other.y1 && y2 == other.y2;
    }

    constexpr bool operator !=(const Area& other) const
    {
        return x1 != other.x1 || x2 != other.x2 || y1 != other.y1 || y2 != other.y2;
    }
};

}


