/*
 *  gucefCOMCORE: GUCEF module providing basic communication facilities
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

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#include "gucefCOMCORE_CIDiscoveryClient.h"

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace COMCORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

CIDiscoveryClient::CIDiscoveryClient( void )
    : CORE::CITypeNamed()
    , CORE::CIConfigurable()
    , CIDiscovery()
{GUCEF_TRACE;

}

/*-------------------------------------------------------------------------*/

CIDiscoveryClient::CIDiscoveryClient( const CIDiscoveryClient& src )
    : CORE::CITypeNamed( src )
    , CORE::CIConfigurable( src )
    , CIDiscovery( src )
{GUCEF_TRACE;

}

/*-------------------------------------------------------------------------*/

CIDiscoveryClient::~CIDiscoveryClient()
{GUCEF_TRACE;
}

/*-------------------------------------------------------------------------*/

CIDiscoveryClient& 
CIDiscoveryClient::operator=( const CIDiscoveryClient& src )
{GUCEF_TRACE;

    return *this;
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace COMCORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/
