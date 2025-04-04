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

class ObjectWrapper;

class ObjRef
{
    lv_obj_t* obj;

public:
    constexpr ObjRef(lv_obj_t* obj) : obj(obj) {}
    constexpr ObjRef(const ObjectWrapper* obj);
    constexpr ObjRef(const ObjectWrapper& obj);

    constexpr operator lv_obj_t*() const { return obj; }
};

class ObjectWrapper
{
public:
    ObjectWrapper(lv_obj_t* obj)
        : obj(obj) {}

    constexpr lv_obj_t* Obj() const { return obj; }
    constexpr operator lv_obj_t*() const { return obj; }
    constexpr ObjRef Ref() const { return this; }

    void SetPosition(int32_t x, int32_t y)
        { lv_obj_set_pos(obj, x, y); }
    void SetSize(int32_t width, int32_t height)
        { lv_obj_set_size(obj, width, height); }
    void SetVisible(bool visible)
        { SetOpacity(visible ? LV_OPA_100 : LV_OPA_0); }

    void SetStyle(lv_style_prop_t prop, lv_style_value_t value, lv_style_selector_t selector = LV_PART_MAIN | LV_STATE_DEFAULT)
        { lv_obj_set_local_style_prop(obj, prop, value, selector); }
    lv_style_value_t GetStyle(lv_style_prop_t prop, lv_part_t part = LV_PART_MAIN)
        { return lv_obj_get_style_prop(obj, part, prop); }

    ALWAYS_INLINE FLATTEN void SetStyle(lv_style_prop_t prop, int32_t value, lv_style_selector_t selector = LV_PART_MAIN | LV_STATE_DEFAULT)
        { SetStyle(prop, { .num = value }, selector); }
    ALWAYS_INLINE FLATTEN void SetStyle(lv_style_prop_t prop, lv_color_t value, lv_style_selector_t selector = LV_PART_MAIN | LV_STATE_DEFAULT)
        { SetStyle(prop, { .color = value }, selector); }

#define LV_STYLE_HELPER(name, style, stype, type, value, ...) \
    ALWAYS_INLINE FLATTEN void Set ## name(type value, lv_style_selector_t selector = LV_PART_MAIN | LV_STATE_DEFAULT) \
        { __VA_ARGS__; SetStyle(style, { .stype = value }, selector); } \
    ALWAYS_INLINE FLATTEN type Get ## name(lv_part_t part = LV_PART_MAIN) \
        { return (type)GetStyle(style, part).stype; }

    LV_STYLE_HELPER(Font, LV_STYLE_TEXT_FONT, ptr, const lv_font_t*, font)
    LV_STYLE_HELPER(Layout, LV_STYLE_LAYOUT, num, lv_layout_t, layout)
    LV_STYLE_HELPER(Align, LV_STYLE_ALIGN, num, lv_align_t, align)
    LV_STYLE_HELPER(Radius, LV_STYLE_RADIUS, num, int, radius)
    LV_STYLE_HELPER(Opacity, LV_STYLE_OPA, num, uint8_t, opacity)

    LV_STYLE_HELPER(TranslateX, LV_STYLE_TRANSLATE_X, num, int, x)
    LV_STYLE_HELPER(TranslateY, LV_STYLE_TRANSLATE_Y, num, int, y)
    ALWAYS_INLINE FLATTEN void SetTranslate(int x, int y)
         { SetTranslateX(x); SetTranslateY(y); }

    LV_STYLE_HELPER(Width, LV_STYLE_WIDTH, num, int, width)
    LV_STYLE_HELPER(Height, LV_STYLE_HEIGHT, num, int, height)

#if LV_USE_FLEX
    LV_STYLE_HELPER(FlexGrow, LV_STYLE_FLEX_GROW, num, uint8_t, grow)
#endif

#if LV_USE_GRID
    LV_STYLE_HELPER(GridColumn, LV_STYLE_GRID_CELL_COLUMN_POS, num, int, column)
    LV_STYLE_HELPER(GridColumnSpan, LV_STYLE_GRID_CELL_COLUMN_SPAN, num, int, span)
    LV_STYLE_HELPER(GridColumnAlign, LV_STYLE_GRID_CELL_X_ALIGN, num, lv_grid_align_t, align)

    LV_STYLE_HELPER(GridRow, LV_STYLE_GRID_CELL_ROW_POS, num, int, row)
    LV_STYLE_HELPER(GridRowSpan, LV_STYLE_GRID_CELL_ROW_SPAN, num, int, span)
    LV_STYLE_HELPER(GridRowAlign, LV_STYLE_GRID_CELL_Y_ALIGN, num, lv_grid_align_t, align)

    ALWAYS_INLINE FLATTEN void SetGridPlacement(int column, int row)
        { SetGridColumn(column); SetGridRow(row); }
    ALWAYS_INLINE FLATTEN void SetGridSpan(int columnSpan, int rowSpan)
        { SetGridColumnSpan(columnSpan); SetGridRowSpan(rowSpan); }
    ALWAYS_INLINE FLATTEN void SetGridAlign(lv_grid_align_t colAlign, lv_grid_align_t rowAlign)
        { SetGridColumnAlign(colAlign); SetGridRowAlign(rowAlign); }
#endif

    LV_STYLE_HELPER(BackgroundColor, LV_STYLE_BG_COLOR, color, lv_color_t, color)
    LV_STYLE_HELPER(BackgroundOpacity, LV_STYLE_BG_OPA, num, uint8_t, opacity)
    ALWAYS_INLINE FLATTEN void SetBackground(lv_color_t color, uint8_t opacity = 255, lv_style_selector_t selector = LV_PART_MAIN | LV_STATE_DEFAULT)
        { SetBackgroundColor(color, selector); SetBackgroundOpacity(opacity, selector); }

    LV_STYLE_HELPER(BorderWidth, LV_STYLE_BORDER_WIDTH, num, int, width)
    LV_STYLE_HELPER(BorderColor, LV_STYLE_BORDER_COLOR, color, lv_color_t, color)
    LV_STYLE_HELPER(BorderSide, LV_STYLE_BORDER_SIDE, num, lv_border_side_t, side)
    ALWAYS_INLINE FLATTEN void SetBorder(int width, lv_color_t color, lv_border_side_t side = LV_BORDER_SIDE_FULL, lv_style_selector_t selector = LV_PART_MAIN | LV_STATE_DEFAULT)
        { SetBorderWidth(width, selector); SetBorderColor(color, selector); SetBorderSide(side, selector); }

    LV_STYLE_HELPER(TextColor, LV_STYLE_TEXT_COLOR, color, lv_color_t, color)
    LV_STYLE_HELPER(TextAlign, LV_STYLE_TEXT_ALIGN, num, lv_text_align_t, align)

    LV_STYLE_HELPER(PaddingTop, LV_STYLE_PAD_TOP, num, int, padding)
    LV_STYLE_HELPER(PaddingBottom, LV_STYLE_PAD_BOTTOM, num, int, padding)
    LV_STYLE_HELPER(PaddingLeft, LV_STYLE_PAD_LEFT, num, int, padding)
    LV_STYLE_HELPER(PaddingRight, LV_STYLE_PAD_RIGHT, num, int, padding)
    ALWAYS_INLINE FLATTEN void SetPadding(int vertical, int horizontal)
        { SetPaddingTop(vertical); SetPaddingBottom(vertical); SetPaddingLeft(horizontal); SetPaddingRight(horizontal); }
    ALWAYS_INLINE FLATTEN void SetPadding(int padding)
        { SetPadding(padding, padding); }

    LV_STYLE_HELPER(MarginTop, LV_STYLE_MARGIN_TOP, num, int, margin)
    LV_STYLE_HELPER(MarginBottom, LV_STYLE_MARGIN_BOTTOM, num, int, margin)
    LV_STYLE_HELPER(MarginLeft, LV_STYLE_MARGIN_LEFT, num, int, margin)
    LV_STYLE_HELPER(MarginRight, LV_STYLE_MARGIN_RIGHT, num, int, margin)
    ALWAYS_INLINE FLATTEN void SetMargin(int vertical, int horizontal)
        { SetMarginTop(vertical); SetMarginBottom(vertical); SetMarginLeft(horizontal); SetMarginRight(horizontal); }
    ALWAYS_INLINE FLATTEN void SetMargin(int margin)
        { SetMargin(margin, margin); }

    static constexpr lv_color_t ColorWhite = { 255, 255, 255 };
    static constexpr lv_color_t ColorBlack = { 0, 0, 0 };

    void AddToGroup(lv_group_t* group = lv_group_get_default()) { lv_group_add_obj(group, obj); }
    void AddFlag(lv_obj_flag_t flag) { lv_obj_add_flag(obj, flag); }
    void AddState(lv_state_t state) { lv_obj_add_state(obj, state); }
    void RemoveFlag(lv_obj_flag_t flag) { lv_obj_remove_flag(obj, flag); }
    void RemoveState(lv_state_t state) { lv_obj_remove_state(obj, state); }

    void Focus() { lv_group_focus_obj(obj); }

    ObjectWrapper GetChild(int index) { return lv_obj_get_child(obj, index); }

protected:
    template<auto Handler> void AddEvent(lv_event_code_t event = __EventThunk<Handler>::DefaultEvent)
    {
        lv_obj_add_event_cb(obj, __EventThunk<Handler>::cb, event, this);
    }

private:
    lv_obj_t* obj = NULL;

    template<auto Handler> struct __EventThunk {};
    template<typename Owner, void (Owner::*Handler)(lv_event_t&)> struct __EventThunk<Handler>
    {
        static void cb(lv_event_t* evt)
        {
            (((Owner*)(ObjectWrapper*)evt->user_data)->*Handler)(*evt);
        }
    };

    template<typename Owner, void (Owner::*Handler)(lv_key_t)> struct __EventThunk<Handler>
    {
        static constexpr lv_event_code_t DefaultEvent = LV_EVENT_KEY;
        static void cb(lv_event_t* evt)
        {
            (((Owner*)(ObjectWrapper*)evt->user_data)->*Handler)(*(lv_key_t*)evt->param);
        }
    };

    friend class Object;
};

template<typename T> class Model
{
public:
    void Bind(const T& model) { this->model = &model; }

protected:
    const T* model = NULL;

    friend class Object;
};

class Object : public ObjectWrapper
{
public:
    typedef Delegate<class Object*, ObjRef> factory_t;

    template<typename Type> static factory_t GetFactory()
    {
        return +[](void*, ObjRef parent) { return (Object*)new Type(parent); };
    }

    template<typename Type, typename TModel> static factory_t GetFactory(const TModel& model)
    {
        return GetDelegate(
            +[](void* model, ObjRef parent) {
                auto o = new Type(parent);
                static_cast<lvgl::Model<TModel>*>(o)->model = (const TModel*)model;
                return (Object*)o;
            }, (void*)&model);
    }

    // delete the copy ctor, it is very dangerous when invoked accidentally
    Object(const Object&) = delete;

    Object(const lv_obj_class_t& cls, ObjRef parent)
        : ObjectWrapper(lv_obj_class_create_obj(&cls, parent))
    {
        obj->user_data = this;
        lv_obj_class_init_obj(obj);
    }

    virtual ~Object()
    {
        lv_obj_delete(obj);
    }

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

protected:
    virtual void Update() {}
};

template<typename LvType> constexpr const lv_obj_class_t& GetClass() { static_assert(false, "Unsupported lv_obj class"); return lv_obj_class; }

#define LV_BIND_CLASS(tObj, tClass) \
template<> constexpr const lv_obj_class_t& GetClass<tObj>() { return tClass; }

LV_BIND_CLASS(lv_obj_t, lv_obj_class);

template<typename LvType = lv_obj_t> class LvObject : public Object
{
public:
    LvObject(ObjRef parent)
        : Object(GetClass<LvType>(), parent) {}
};

constexpr ObjRef::ObjRef(const ObjectWrapper* obj) : obj(obj ? obj->Obj() : NULL) {}
constexpr ObjRef::ObjRef(const ObjectWrapper& obj) : obj(obj.Obj()) {}

}
