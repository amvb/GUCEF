#-------------------------------------------------------------------
# This file has been automatically generated by ProjectGenerator    
# which is part of a build system designed for GUCEF                
#     (Galaxy Unlimited Framework)                                  
# For the latest info, see http://www.VanvelzenSoftware.com/        
#                                                                   
# The contents of this file are placed in the public domain. Feel   
# free to make use of it in any way you like.                       
#-------------------------------------------------------------------


#
# This is the project makefile which includes all modules which are part of this project
#
# PROJECT: "GUCEF_exe_gucefPRODMAN_TestApp"
#

ifndef PROJECT_ROOT_PATH
  PROJECT_ROOT_PATH := $(call my-dir)
endif

include $(CLEAR_VARS)

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/../../../../platform/gucefCORE
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/../../../../platform/gucefMT
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/../../../../platform/gucefCOMCORE
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/../../../../platform/gucefCOM
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/../../../../platform/gucefPATCHER
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/../../../../platform/gucefPRODMAN
include $(MY_MODULE_PATH)/Android.mk

MY_MODULE_PATH := $(PROJECT_ROOT_PATH)/../../../../tests/gucefPRODMAN_TestApp
include $(MY_MODULE_PATH)/Android.mk

