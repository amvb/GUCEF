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
LOCAL_MODULE := hiredis
LOCAL_MODULE_FILENAME := libhiredis
@echo Module name: $(LOCAL_MODULE)

LOCAL_SRC_FILES := \
  async.c \
  dict.c \
  hiredis.c \
  net.c \
  read.c \
  sds.c \
  sockcompat.c

LOCAL_C_INCLUDES := \
  $(MY_MODULE_PATH)

include $(BUILD_STATIC_LIBRARY)

