/*
 * Copyright (c) 2024 triaxis s.r.o.
 * Licensed under the MIT license. See LICENSE.txt file in the repository root
 * for full license information.
 *
 * lvgl/lvgl.cpp
 */

#include "lvgl.h"
#include <src/lvgl_private.h>

#include <kernel/mono.h>

#define MYDBG(...)  DBGCL("lvgl", __VA_ARGS__)

#define LVGL_DIAG_HANDLER   1
#define LVGL_DIAG_REFRESH   2

//#define LVGL_DIAG   LVGL_DIAG_HANDLER | LVGL_DIAG_REFRESH

extern "C" void logcb(lv_log_level_t level, const char * buf)
{
    MYDBG("%s", buf);
}

namespace lvgl
{

INIT_PRIORITY(-5000)
Lvgl lvgl;

static uint32_t tick_cb()
{
    static struct
    {
        mono_t last;
        uint64_t t64;
    } state = {};

    auto mono = MONO_CLOCKS;
    auto elapsed = (mono - state.last);
    state.last = mono;
    return ((state.t64 += elapsed) * ((int64_t)1000 << 17)) >> 32;
}

void Lvgl::Initialize(Display& disp, AsyncDelegate<> render, int width, int height, lv_color_format_t colorFormat, int bufferSplit)
{
    lv_init();

    this->disp = &disp;
    this->render = render;
    lvd = lv_display_create(width, height);
    lv_display_set_color_format(lvd, colorFormat);
    lv_display_set_user_data(lvd, this);
    lv_tick_set_cb(tick_cb);

    // disable screen scrolling
    lv_obj_clear_flag(lv_display_get_screen_active(lvd), LV_OBJ_FLAG_SCROLLABLE);

    // calculate full invalidation area and adjust the buffer to be able to fill it
    lv_area_t dispArea = { 0, 0, width - 1, height - 1 };
    disp.AdjustFlushArea(&dispArea);

    int fbStride = lv_draw_buf_width_to_stride(
        dispArea.x2 - dispArea.x1 + 1,
        colorFormat);

    int fbHeight = dispArea.y2 - dispArea.y1 + 1;

    // allocate buffers
    int bufHeight = (fbHeight + bufferSplit - 1) / bufferSplit;
    const unsigned bufSize = fbStride * bufHeight + 8;
    auto fb = malloc(bufSize);

    // initalize buffers and events
    lv_display_set_buffers(lvd, fb, NULL, bufSize, LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_add_event_cb(lvd, LvInvalidate, LV_EVENT_INVALIDATE_AREA, this);
    lv_display_set_flush_cb(lvd, LvFlush);

    // delete refresh timer, we handle refreshing on our own
    lv_display_delete_refr_timer(lvd);
    lv_obj_invalidate(lvd->act_scr);

    kernel::Task::Run(this, &Lvgl::Task);
}

void Lvgl::LvInvalidate(lv_event_t * e)
{
    auto instance = (Lvgl*)e->user_data;
    lv_area_t* a = (lv_area_t*)e->param;
    instance->Invalidate(a);
}

void Lvgl::Invalidate(lv_area_t* area)
{
    disp->AdjustFlushArea(area);
}

void Lvgl::LvFlush(lv_display_t * display, const lv_area_t * area, uint8_t * px_map)
{
    auto instance = (Lvgl*)display->user_data;
    ASSERT(display == instance->lvd);
    instance->Flush(area, px_map, display->layer_head->draw_buf->header.stride, display->flushing_last);
}

void Lvgl::Flush(const lv_area_t* area, uint8_t* px_map, size_t stride, bool last)
{
    if (lvd->color_format == LV_COLOR_FORMAT_I1)
    {
        px_map += 8;
    }
    disp->Flush(area, px_map, stride, last);
    lvd->flushing = false;
}

async(Lvgl::Task)
async_def(
#if LVGL_DIAG & (LVGL_DIAG_HANDLER | LVGL_DIAG_REFRESH)
    uint32_t start;
#endif
)
{
    for (;;)
    {
        // ask the app to update display
        await(render);

        // call the LVGL handler
#if LVGL_DIAG & LVGL_DIAG_HANDLER
        f.start = MONO_US;
#endif
        UNUSED auto wait = await(kernel::Worker::Run, lv_timer_handler);
#if LVGL_DIAG & LVGL_DIAG_HANDLER
        MYDBG("Handler: %.3q ms, wait %d ms", MONO_US - f.start, wait);
#endif

        // update the display
#if LVGL_DIAG & LVGL_DIAG_REFRESH
        MYDBG("Refresh start");
        f.start = MONO_US;
#endif
        await(kernel::Worker::RunWithOptions, { .stack = 4096 }, _lv_display_refr_timer, (lv_timer_t*)NULL);
#if LVGL_DIAG & LVGL_DIAG_REFRESH
        MYDBG("Refresh: %.3q ms", MONO_US - f.start);
#endif
    }
}
async_end

}
