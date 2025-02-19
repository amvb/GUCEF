--------------------------------------------------------------------
-- This file was automatically generated by ProjectGenerator
-- which is tooling part the build system designed for GUCEF
--     (Galaxy Unlimited Framework)
-- For the latest info, see http://www.VanvelzenSoftware.com/
--
-- The contents of this file are placed in the public domain. Feel
-- free to make use of it in any way you like.
--------------------------------------------------------------------
--

-- Configuration for module: inputdriverXWINMSG


configuration( { "LINUX32" } )
  project( "inputdriverXWINMSG" )

configuration( { "LINUX64" } )
  project( "inputdriverXWINMSG" )

configuration( {} )
  location( os.getenv( "PM5OUTPUTDIR" ) )

configuration( {} )
  targetdir( os.getenv( "PM5TARGETDIR" ) )

configuration( {} )
language( "C" )

configuration( { "LINUX32" } )
language( "C++" )

configuration( { "LINUX64" } )
language( "C++" )

configuration( { "LINUX32" } )


configuration( { LINUX32 } )
kind( "SharedLib" )
configuration( { "LINUX64" } )


configuration( { LINUX64 } )
kind( "SharedLib" )
  
configuration( { LINUX32 } )
links( { "gucefCORE", "gucefINPUT", "gucefMT" } )
  links( { "gucefCORE", "gucefINPUT", "gucefMT" } )
  

configuration( { LINUX32 } )
defines( { "BUILD_GUCEF_INPUT_PLUGIN_DLL", "INPUTDRIVERXWINMSG_BUILD_MODULE" } )
  
configuration( { LINUX64 } )
links( { "gucefCORE", "gucefINPUT", "gucefMT" } )
  links( { "gucefCORE", "gucefINPUT", "gucefMT" } )
  

configuration( { LINUX64 } )
defines( { "BUILD_GUCEF_INPUT_PLUGIN_DLL", "INPUTDRIVERXWINMSG_BUILD_MODULE" } )


configuration( { "LINUX32" } )
    vpaths { ["Platform Headers"] = { "**.h", "**.hpp", "**.hxx" } }
    files( {
      "include/inputdriverXWINMSG.h",
      "include/inputdriverXWINMSG_CEventListner.h"
    } )

    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/inputdriverXWINMSG.cpp",
      "src/inputdriverXWINMSG_CEventListner.cpp"
    } )



configuration( { "LINUX64" } )
    vpaths { ["Platform Headers"] = { "**.h", "**.hpp", "**.hxx" } }
    files( {
      "include/inputdriverXWINMSG.h",
      "include/inputdriverXWINMSG_CEventListner.h"
    } )

    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/inputdriverXWINMSG.cpp",
      "src/inputdriverXWINMSG_CEventListner.cpp"
    } )


configuration( {} )
includedirs( { "../../../common/include", "../../../platform/gucefCORE/include", "../../../platform/gucefINPUT/include", "../../../platform/gucefMT/include" } )

configuration( { "LINUX32" } )
includedirs( { "../../../platform/gucefCORE/include/linux", "include" } )

configuration( { "LINUX64" } )
includedirs( { "../../../platform/gucefCORE/include/linux", "include" } )
