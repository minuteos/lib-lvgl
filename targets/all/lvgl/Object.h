/*
 * Copyright (c) 2024 triaxis s.r.o.
 * Licensed under the MIT license. See LICENSE.txt file in the repository root
 * for full license information.
 *
 * lvgl/Object.h
 *
 * Creates a C++ abstraction on top of a standard lv_obj
 */

#pragma once

#include <lvgl/lvgl.h>

#include <src/lvgl_private.h>

namespace lvgl
{

class Object
{
public:
    Object(const lv_obj_class_t& cls, lv_obj_t* parent)
    {
        obj = lv_obj_class_create_obj(&cls, parent);
        obj->user_data = this;
        lv_obj_class_init_obj(obj);
    }

    virtual ~Object()
    {
        lv_obj_delete(obj);
    }

    constexpr operator lv_obj_t*() const { return obj; }
    constexpr operator lv_obj_t*() { return obj; }

    void UpdateTree()
    {
        Update();

        if (auto spec = obj->spec_attr)
        {
            for (int i = 0; i < spec->child_cnt; i++)
            {
                if (auto ud = spec->children[i]->user_data)
                {
                    ((Object*)ud)->UpdateTree();
                }
            }
        }
    }

    void SetSize(int32_t width, int32_t height)
        { lv_obj_set_size(obj, width, height); }

    void SetStyle(lv_style_prop_t prop, int32_t value, lv_style_selector_t selector = LV_PART_MAIN | LV_STATE_DEFAULT)
        { lv_obj_set_local_style_prop(obj, prop, { .num = value }, selector); }
    void SetStyle(lv_style_prop_t prop, lv_color_t value, lv_style_selector_t selector = LV_PART_MAIN | LV_STATE_DEFAULT)
        { lv_obj_set_local_style_prop(obj, prop, { .color = value }, selector); }
    void SetFont(const lv_font_t& font, lv_style_selector_t selector = LV_PART_MAIN | LV_STATE_DEFAULT)
        { lv_obj_set_local_style_prop(obj, LV_STYLE_TEXT_FONT, { .ptr = &font }, selector); }
    lv_style_value_t GetStyle(lv_style_prop_t prop, lv_part_t part = LV_PART_MAIN)
        { return lv_obj_get_style_prop(obj, part, prop); }

#define LV_STYLE_HELPER(name, style, type, value, ...) \
    ALWAYS_INLINE FLATTEN void Set ## name(type value, lv_style_selector_t selector = LV_PART_MAIN | LV_STATE_DEFAULT) \
        { __VA_ARGS__; SetStyle(style, value, selector); } \
    ALWAYS_INLINE FLATTEN type Get ## name(lv_part_t part = LV_PART_MAIN) \
        { auto res = GetStyle(style, part); return *(const type*)&res; }

    LV_STYLE_HELPER(Layout, LV_STYLE_LAYOUT, lv_layout_t, layout)

    LV_STYLE_HELPER(FlexFlow, LV_STYLE_FLEX_FLOW, lv_flex_flow_t, flow, SetLayout(LV_LAYOUT_FLEX))
    LV_STYLE_HELPER(FlexAlignMain, LV_STYLE_FLEX_MAIN_PLACE, lv_flex_align_t, align)
    LV_STYLE_HELPER(FlexAlignCross, LV_STYLE_FLEX_CROSS_PLACE, lv_flex_align_t, align)
    LV_STYLE_HELPER(FlexAlignTrack, LV_STYLE_FLEX_TRACK_PLACE, lv_flex_align_t, align)
    ALWAYS_INLINE FLATTEN void SetFlexAlign(lv_flex_align_t main, lv_flex_align_t cross, lv_flex_align_t track)
        { SetFlexAlignMain(main); SetFlexAlignCross(cross); SetFlexAlignTrack(track); }
    LV_STYLE_HELPER(FlexGapRow, LV_STYLE_PAD_ROW, int, gap)
    LV_STYLE_HELPER(FlexGapColumn, LV_STYLE_PAD_COLUMN, int, gap)
    ALWAYS_INLINE FLATTEN void SetFlexGap(int row, int column)
        { SetFlexGapRow(row); SetFlexGapColumn(column); }
    ALWAYS_INLINE FLATTEN void SetFlexGap(int gap)
        { SetFlexGap(gap, gap); }
    LV_STYLE_HELPER(FlexGrow, LV_STYLE_FLEX_GROW, uint8_t, grow)

    LV_STYLE_HELPER(BorderWidth, LV_STYLE_BORDER_WIDTH, int, width)
    LV_STYLE_HELPER(BorderColor, LV_STYLE_BORDER_COLOR, lv_color_t, color)
    LV_STYLE_HELPER(BorderSide, LV_STYLE_BORDER_SIDE, lv_border_side_t, side)
    ALWAYS_INLINE FLATTEN void SetBorder(int width, lv_color_t color, lv_border_side_t side, lv_style_selector_t selector = LV_PART_MAIN | LV_STATE_DEFAULT)
        { SetBorderWidth(width, selector); SetBorderColor(color, selector); SetBorderSide(side, selector); }

    LV_STYLE_HELPER(TextColor, LV_STYLE_TEXT_COLOR, lv_color_t, color)

    LV_STYLE_HELPER(PaddingTop, LV_STYLE_PAD_TOP, int, padding);
    LV_STYLE_HELPER(PaddingBottom, LV_STYLE_PAD_BOTTOM, int, padding);
    LV_STYLE_HELPER(PaddingLeft, LV_STYLE_PAD_LEFT, int, padding);
    LV_STYLE_HELPER(PaddingRight, LV_STYLE_PAD_RIGHT, int, padding);
    ALWAYS_INLINE FLATTEN void SetPadding(int vertical, int horizontal)
        { SetPaddingTop(vertical); SetPaddingBottom(vertical); SetPaddingLeft(horizontal); SetPaddingRight(horizontal); }
    ALWAYS_INLINE FLATTEN void SetPadding(int padding)
        { SetPadding(padding, padding); }

    LV_STYLE_HELPER(MarginTop, LV_STYLE_MARGIN_TOP, int, margin);
    LV_STYLE_HELPER(MarginBottom, LV_STYLE_MARGIN_BOTTOM, int, margin);
    LV_STYLE_HELPER(MarginLeft, LV_STYLE_MARGIN_LEFT, int, margin);
    LV_STYLE_HELPER(MarginRight, LV_STYLE_MARGIN_RIGHT, int, margin);
    ALWAYS_INLINE FLATTEN void SetMargin(int vertical, int horizontal)
        { SetMarginTop(vertical); SetMarginBottom(vertical); SetMarginLeft(horizontal); SetMarginRight(horizontal); }
    ALWAYS_INLINE FLATTEN void SetMargin(int margin)
        { SetMargin(margin, margin); }

    static constexpr lv_color_t ColorWhite = { 255, 255, 255 };
    static constexpr lv_color_t ColorBlack = { 0, 0, 0 };

protected:
    virtual void Update() {}

private:
    lv_obj_t* obj = NULL;
};

template<typename LvType> constexpr const lv_obj_class_t& GetClass() { static_assert(false, "Unsupported lv_obj class"); return lv_obj_class; }

#define LV_BIND_CLASS(tObj, tClass) \
template<> constexpr const lv_obj_class_t& GetClass<tObj>() { return tClass; }

LV_BIND_CLASS(lv_obj_t, lv_obj_class);

template<typename LvType = lv_obj_t> class LvObject : public Object
{
public:
    LvObject(lv_obj_t* parent)
        : Object(GetClass<LvType>(), parent) {}
};

using Container = LvObject<lv_obj_t>;

}
