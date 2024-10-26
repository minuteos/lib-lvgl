#
# Copyright (c) 2024 triaxis s.r.o.
# Licensed under the MIT license. See LICENSE.txt file in the repository root
# for full license information.
#
# Include.mk
#

LVGL_MAKEFILE := $(call curmake)
LVGL_DIR = $(call parentdir, $(call parentdir, $(call parentdir, $(dir $(LVGL_MAKEFILE)))))lvgl/

INCLUDE_DIRS += $(LVGL_DIR)
SOURCE_DIRS += $(LVGL_DIR)src/draw/sw/blend/ $(LVGL_DIR)src/themes/*/

DEFINES += LV_CONF_INCLUDE_SIMPLE
