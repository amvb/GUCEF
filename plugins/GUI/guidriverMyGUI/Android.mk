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
LOCAL_MODULE := guidriverMyGUI
LOCAL_MODULE_FILENAME := libguidriverMyGUI
@echo Module name: $(LOCAL_MODULE)

LOCAL_SRC_FILES := \
  include/guceMyGUI_CIOAccessToMyGuiDataStreamAdapter.cpp \
  src/guceMyGUI.cpp \
  src/guceMyGUI_CButtonImp.cpp \
  src/guceMyGUI_CCheckboxImp.cpp \
  src/guceMyGUI_CComboboxImp.cpp \
  src/guceMyGUI_CDataManager.cpp \
  src/guceMyGUI_CEditboxImp.cpp \
  src/guceMyGUI_CFileOpenDialogImp.cpp \
  src/guceMyGUI_CFileSaveDialogImp.cpp \
  src/guceMyGUI_CFileSystemDialogImp.cpp \
  src/guceMyGUI_CFormBackendImp.cpp \
  src/guceMyGUI_CGUIContext.cpp \
  src/guceMyGUI_CGridViewImp.cpp \
  src/guceMyGUI_CImageFrameImp.cpp \
  src/guceMyGUI_CLabelImp.cpp \
  src/guceMyGUI_CListboxImp.cpp \
  src/guceMyGUI_CMemoboxImp.cpp \
  src/guceMyGUI_CMenuBarImp.cpp \
  src/guceMyGUI_CModule.cpp \
  src/guceMyGUI_CMyGUIInputAdapter.cpp \
  src/guceMyGUI_CPopupMenuImp.cpp \
  src/guceMyGUI_CProgressBarImp.cpp \
  src/guceMyGUI_CPushButtonImp.cpp \
  src/guceMyGUI_CRenderContextImp.cpp \
  src/guceMyGUI_CSpinnerImp.cpp \
  src/guceMyGUI_CTabContentPaneImp.cpp \
  src/guceMyGUI_CTabControlImp.cpp \
  src/guceMyGUI_CTreeviewImp.cpp \
  src/guceMyGUI_CVFSHandleToMyGuiDataStreamAdapter.cpp \
  src/guceMyGUI_CVFSInfoProvider.cpp \
  src/guceMyGUI_CWidgetImp.cpp \
  src/guceMyGUI_CWindowImp.cpp \
  src/guceMyGUI_pluginAPI.cpp \
  src/guidriverMyGUI_CLogAdapter.cpp \
  src/guidriverMyGUI_CMyGuiDriver.cpp \
  src/guidriverMyGUI_widgets.cpp

LOCAL_C_INCLUDES := \
  $(MY_MODULE_PATH)/include \
  $(MY_MODULE_PATH)/../../../common/include \
  $(MY_MODULE_PATH)/../../../dependencies/MyGui/MyGUIEngine/include \
  $(MY_MODULE_PATH)/../../../dependencies/freetype/include \
  $(MY_MODULE_PATH)/../../../dependencies/freetype/include/freetype \
  $(MY_MODULE_PATH)/../../../dependencies/freetype/include/freetype/config \
  $(MY_MODULE_PATH)/../../../dependencies/freetype/include/freetype/internal \
  $(MY_MODULE_PATH)/../../../dependencies/freetype/include/freetype/internal/services \
  $(MY_MODULE_PATH)/../../../dependencies/freetype/src \
  $(MY_MODULE_PATH)/../../../dependencies/freetype/src/winfonts \
  $(MY_MODULE_PATH)/../../../platform/gucefCORE/include \
  $(MY_MODULE_PATH)/../../../platform/gucefCORE/include/android \
  $(MY_MODULE_PATH)/../../../platform/gucefGUI/include \
  $(MY_MODULE_PATH)/../../../platform/gucefIMAGE/include \
  $(MY_MODULE_PATH)/../../../platform/gucefINPUT/include \
  $(MY_MODULE_PATH)/../../../platform/gucefMT/include \
  $(MY_MODULE_PATH)/../../../platform/gucefVFS/include

LOCAL_CFLAGS := -DGUIDRIVERMYGUI_BUILD_MODULE


LOCAL_SHARED_LIBRARIES := \
  MyGUI.Engine \
  freetype \
  gucefCORE \
  gucefGUI \
  gucefINPUT \
  gucefMT \
  gucefVFS

include $(BUILD_SHARED_LIBRARY)

