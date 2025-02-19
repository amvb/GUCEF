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
LOCAL_MODULE := redis-plus-plus
LOCAL_MODULE_FILENAME := libredis-plus-plus
@echo Module name: $(LOCAL_MODULE)

LOCAL_SRC_FILES := \
  command.cpp \
  command_options.cpp \
  connection.cpp \
  connection_pool.cpp \
  crc16.cpp \
  errors.cpp \
  pipeline.cpp \
  redis.cpp \
  redis_cluster.cpp \
  reply.cpp \
  sentinel.cpp \
  shards.cpp \
  shards_pool.cpp \
  subscriber.cpp \
  transaction.cpp

LOCAL_C_INCLUDES := \
  $(MY_MODULE_PATH) \
  $(MY_MODULE_PATH)/../../../../../dependencies \
  $(MY_MODULE_PATH)/../../../../../dependencies/Ogre \
  $(MY_MODULE_PATH)/../../../../../dependencies/Ogre/RenderSystems \
  $(MY_MODULE_PATH)/../../../../../dependencies/Ogre/RenderSystems/GLES2 \
  $(MY_MODULE_PATH)/../../../../../dependencies/Ogre/RenderSystems/GLES2/include \
  $(MY_MODULE_PATH)/../../../../../dependencies/Ogre/RenderSystems/GLES2/include/EGL \
  $(MY_MODULE_PATH)/../../../../../dependencies/Ogre/RenderSystems/GLES2/include/EGL/Android \
  $(MY_MODULE_PATH)/../../../../hiredis

LOCAL_CFLAGS := -DREDIS_PLUS_PLUS_BUILD_TEST=OFF -DREDIS_PLUS_PLUS_CXX_STANDARD=11


LOCAL_STATIC_LIBRARIES := \
  hiredis

include $(BUILD_STATIC_LIBRARY)

