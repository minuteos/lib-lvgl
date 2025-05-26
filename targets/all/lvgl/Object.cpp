/*
 * Copyright (c) 2025 triaxis s.r.o.
 * Licensed under the MIT license. See LICENSE.txt file in the repository root
 * for full license information.
 *
 * lvgl/Object.cpp
 */

#include <lvgl/lvgl.h>

namespace lvgl
{

Object::Object(const lv_obj_class_t& cls, ObjRef parent)
    : ObjectWrapper(lv_obj_class_create_obj(&cls, parent))
{
    obj->user_data = (ObjectWrapper*)this;
    lv_obj_class_init_obj(obj);
}

Object::~Object()
{
    lv_obj_delete(obj);
}

void Object::UpdateTree()
{
    Update();

    for (auto child: GetChildren())
    {
        if (child.HasUserData())
        {
            child.UnsafeCast<Object>().UpdateTree();
        }
    }
}

void ObjectWrapper::AddStyle(const lv_style_t& style, lv_style_selector_t selector) const
{
    // check if the style is already the last added style on the object
    // if it is, do nothing to prevent unnecessary invalidation
    for (int i = 0; i < obj->style_cnt; i++)
    {
        if (obj->styles[i].is_trans || obj->styles[i].is_local) continue;
        if (obj->styles[i].style == &style && obj->styles[i].selector == selector) return;
        break;
    }

    lv_obj_add_style(obj, &style, selector);
}

void ObjectWrapper::RemoveStyle(const lv_style_t& style, lv_style_selector_t selector) const
{
    // check if the style is even present in the object
    // if it is not, do nothing to prevent unnecessary invalidation
    for (int i = 0; i < obj->style_cnt; i++)
    {
        if (obj->styles[i].style == &style)
        {
            lv_obj_remove_style(obj, &style, selector);
            return;
        }
    }
}

void ObjectWrapper::SetStyle(lv_style_prop_t prop, lv_style_value_t value, lv_style_selector_t selector) const
{
    lv_style_value_t currentValue;
    if (lv_obj_get_local_style_prop(obj, prop, &currentValue, selector) == LV_STYLE_RES_FOUND &&
        currentValue.ptr == value.ptr)
    {
        return;
    }

    lv_obj_set_local_style_prop(obj, prop, value, selector);
}

}
