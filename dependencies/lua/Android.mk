#-------------------------------------------------------------------
# This file has been automatically generated by ProjectGenerator    
# which is part of a build system designed for GUCEF                
#     (Galaxy Unlimited Framework)                                  
# For the latest info, see http://www.VanvelzenSoftware.com/        
#                                                                   
# The contents of this file are placed in the public domain. Feel   
# free to make use of it in any way you like.                       
#-------------------------------------------------------------------


ifndef MY_MODULE_PATH
  MY_MODULE_PATH := $(call my-dir)
endif
LOCAL_PATH := $(MY_MODULE_PATH)

include $(CLEAR_VARS)

@echo Module path: $(MY_MODULE_PATH)
LOCAL_MODULE := lua
LOCAL_MODULE_FILENAME := liblua
@echo Module name: $(LOCAL_MODULE)

LOCAL_SRC_FILES := \
  src/lapi.c \
  src/lauxlib.c \
  src/lbaselib.c \
  src/lbitlib.c \
  src/lcode.c \
  src/lcorolib.c \
  src/lctype.c \
  src/ldblib.c \
  src/ldebug.c \
  src/ldo.c \
  src/ldump.c \
  src/lfunc.c \
  src/lgc.c \
  src/linit.c \
  src/liolib.c \
  src/llex.c \
  src/lmathlib.c \
  src/lmem.c \
  src/loadlib.c \
  src/lobject.c \
  src/lopcodes.c \
  src/loslib.c \
  src/lparser.c \
  src/lstate.c \
  src/lstring.c \
  src/lstrlib.c \
  src/ltable.c \
  src/ltablib.c \
  src/ltm.c \
  src/luac.c \
  src/lundump.c \
  src/lutf8lib.c \
  src/lvm.c \
  src/lzio.c

LOCAL_C_INCLUDES := \
  $(MY_MODULE_PATH)/src

LOCAL_CFLAGS := -DLUA_BUILD_AS_DLL

include $(BUILD_SHARED_LIBRARY)

