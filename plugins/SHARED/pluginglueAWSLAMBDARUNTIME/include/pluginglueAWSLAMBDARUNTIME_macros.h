/*
 *  pluginglueAWSLAMBDARUNTIME: Library to push AWS Lambda work into the platform
 *
 *  Copyright (C) 1998 - 2020.  Dinand Vanvelzen
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_MACROS_H
#define GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_MACROS_H

/*
 *      Build configuration specific macros.
 *      Also includes the generic macros which are build config independant.
 */

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_CORE_MACROS_H
#include "gucefCORE_macros.h"      /* CORE Module build configuration */
#define GUCEF_CORE_MACROS_H
#endif /* GUCEF_CORE_MACROS_H ? */

#ifndef GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_CONFIG_H
#include "pluginglueAWSLAMBDARUNTIME_config.h"
#define GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_CONFIG_H
#endif /* GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_CONFIG_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      GENERAL MACROS                                                     //
//                                                                         //
//-------------------------------------------------------------------------*/

#undef GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_EXPORT
#ifdef GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_BUILD_MODULE
  #define GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_EXPORT GUCEF_EXPORT
#else
  #define GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_EXPORT GUCEF_IMPORT
#endif /* GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_BUILD_MODULE ? */

#undef GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_EXPORT_CPP
#ifdef GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_EXPORT_CPP_CODE
  #define GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_EXPORT_CPP GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_EXPORT
#else
  #define GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_EXPORT_CPP
#endif /* GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_EXPORT_CPP_CODE */

#undef GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_EXPORT_C
#ifdef GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_EXPORT_C_CODE
  #define GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_EXPORT_C GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_EXPORT
#else
  #define GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_EXPORT_C
#endif /* GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_EXPORT_C_CODE */

/*-------------------------------------------------------------------------*/

#endif /* GUCEF_PLUGINGLUE_AWSLAMBDARUNTIME_MACROS_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 26-03-2005 :
       - Initial version of this file.

-----------------------------------------------------------------------------*/
