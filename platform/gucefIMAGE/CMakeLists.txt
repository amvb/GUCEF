#-------------------------------------------------------------------
# This file was automatically generated by ProjectGenerator
# which is tooling part the build system designed for GUCEF
#     (Galaxy Unlimited Framework)
# For the latest info, see http://www.VanvelzenSoftware.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------
#

# Configuration for module: gucefIMAGE

set( HEADER_FILES 
  include/CGUCEFIMAGEModule.h
  include/gucefIMAGE.h
  include/gucefIMAGEDLLInit.h
  include/gucefIMAGE_CGUIImageCodec.h
  include/gucefIMAGE_CIImageCodec.h
  include/gucefIMAGE_CIMGCodec.h
  include/gucefIMAGE_CImage.h
  include/gucefIMAGE_CImageCodecPlugin.h
  include/gucefIMAGE_CImageCodecPluginManager.h
  include/gucefIMAGE_CImageCodecRegistry.h
  include/gucefIMAGE_CImageGlobal.h
  include/gucefIMAGE_CPixel.h
  include/gucefIMAGE_CPixelMap.h
  include/gucefIMAGE_CPluginImageCodecItem.h
  include/gucefIMAGE_ETypes.h
  include/gucefIMAGE_config.h
  include/gucefIMAGE_imagedata.h
  include/gucefIMAGE_macros.h
)

set( SOURCE_FILES 
  src/CGUCEFIMAGEModule.cpp
  src/gucefIMAGE.cpp
  src/gucefIMAGE_CCPluginImageCodecItem.cpp
  src/gucefIMAGE_CGUIImageCodec.cpp
  src/gucefIMAGE_CIImageCodec.cpp
  src/gucefIMAGE_CIMGCodec.cpp
  src/gucefIMAGE_CImage.cpp
  src/gucefIMAGE_CImageCodecPlugin.cpp
  src/gucefIMAGE_CImageCodecPluginManager.cpp
  src/gucefIMAGE_CImageCodecRegistry.cpp
  src/gucefIMAGE_CImageGlobal.cpp
  src/gucefIMAGE_CPixel.cpp
  src/gucefIMAGE_CPixelMap.cpp
)

# Make sure the PLATFORM_HEADER_FILES variable is always defined
 set( PLATFORM_HEADER_FILES "" )

# Make sure the PLATFORM_SOURCE_FILES variable is always defined
 set( PLATFORM_SOURCE_FILES "" )

# For ease of use make a variable that has all files for this module
set( ALL_FILES ${HEADER_FILES} ${SOURCE_FILES} ${PLATFORM_HEADER_FILES} ${PLATFORM_SOURCE_FILES} )

set( MODULE_NAME "gucefIMAGE" )
add_library( ${MODULE_NAME} ${ALL_FILES} )
add_dependencies( ${MODULE_NAME} gucefCORE gucefMT )
target_link_libraries( ${MODULE_NAME} gucefCORE gucefMT )
set_property( TARGET ${MODULE_NAME} APPEND_STRING PROPERTY COMPILE_DEFINITIONS "GUCEFIMAGE_BUILD_MODULE" )

include_directories( ../../common/include ../gucefCORE/include ../gucefMT/include include )

if ( ANDROID )
  include_directories( ../gucefCORE/include/android )
endif( ANDROID )

if ( LINUX32 )
  include_directories( ../gucefCORE/include/linux )
endif( LINUX32 )

if ( LINUX64 )
  include_directories( ../gucefCORE/include/linux )
endif( LINUX64 )

if ( WIN32 )
  include_directories( ../gucefCORE/include/mswin )
endif( WIN32 )

if ( WIN64 )
  include_directories( ../gucefCORE/include/mswin )
endif( WIN64 )



#******** START OF AUTOGENERATED TEMPLATED ADDITION CONTENT ********




if (ANDROID)
GUCEF_config_lib( ${MODULE_NAME} )
elseif (LINUX32)
GUCEF_config_lib( ${MODULE_NAME} )
elseif (LINUX64)
GUCEF_config_lib( ${MODULE_NAME} )
elseif (OSX)
GUCEF_config_lib( ${MODULE_NAME} )
elseif (WIN32)
GUCEF_config_lib( ${MODULE_NAME} )
elseif (WIN64)
GUCEF_config_lib( ${MODULE_NAME} )
else()
GUCEF_config_lib( ${MODULE_NAME} )
endif()



#******** END OF AUTOGENERATED TEMPLATED ADDITION CONTENT ********


