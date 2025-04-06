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

}
