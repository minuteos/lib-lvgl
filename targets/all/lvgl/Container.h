/*
 * Copyright (c) 2024 triaxis s.r.o.
 * Licensed under the MIT license. See LICENSE.txt file in the repository root
 * for full license information.
 *
 * lvgl/Container.h
 */

#pragma once

#include <lvgl/lvgl.h>

namespace lvgl
{

class Container : public LvObject<lv_obj_t>
{
public:
    Container(ObjRef parent) : LvObject(parent) {}

#if LV_USE_FLEX
    LV_STYLE_HELPER(FlexFlow, LV_STYLE_FLEX_FLOW, num, lv_flex_flow_t, flow, SetLayout(LV_LAYOUT_FLEX))
    LV_STYLE_HELPER(FlexAlignMain, LV_STYLE_FLEX_MAIN_PLACE, num, lv_flex_align_t, align)
    LV_STYLE_HELPER(FlexAlignCross, LV_STYLE_FLEX_CROSS_PLACE, num, lv_flex_align_t, align)
    LV_STYLE_HELPER(FlexAlignTrack, LV_STYLE_FLEX_TRACK_PLACE, num, lv_flex_align_t, align)
    ALWAYS_INLINE FLATTEN void SetFlexAlign(lv_flex_align_t main, lv_flex_align_t cross, lv_flex_align_t track)
        { SetFlexAlignMain(main); SetFlexAlignCross(cross); SetFlexAlignTrack(track); }
    LV_STYLE_HELPER(FlexGapRow, LV_STYLE_PAD_ROW, num, int, gap)
    LV_STYLE_HELPER(FlexGapColumn, LV_STYLE_PAD_COLUMN, num, int, gap)
    ALWAYS_INLINE FLATTEN void SetFlexGap(int row, int column)
        { SetFlexGapRow(row); SetFlexGapColumn(column); }
    ALWAYS_INLINE FLATTEN void SetFlexGap(int gap)
        { SetFlexGap(gap, gap); }
#endif

#if LV_USE_GRID
    LV_STYLE_HELPER(GridColumns, LV_STYLE_GRID_COLUMN_DSC_ARRAY, ptr, const int*, colSpec);
    LV_STYLE_HELPER(GridColumnAlignDefault, LV_STYLE_GRID_COLUMN_ALIGN, num, lv_grid_align_t, align)

    LV_STYLE_HELPER(GridRows, LV_STYLE_GRID_ROW_DSC_ARRAY, ptr, const int*, rowSpec);
    LV_STYLE_HELPER(GridRowAlignDefault, LV_STYLE_GRID_ROW_ALIGN, num, lv_grid_align_t, align)
#endif

};

}
