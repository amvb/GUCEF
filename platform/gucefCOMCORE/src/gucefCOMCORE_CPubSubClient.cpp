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

#ifndef GUCEF_CORE_LOGGING_H
#include "gucefCORE_Logging.h"
#define GUCEF_CORE_LOGGING_H
#endif /* GUCEF_CORE_LOGGING_H ? */

#include "gucefCOMCORE_CPubSubClient.h"    

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace COMCORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      IMPLEMENTATION                                                     //
//                                                                         //
//-------------------------------------------------------------------------*/

CPubSubClient::CPubSubClient( void )
    : CORE::CObservingNotifier()
    , CORE::CIConfigurable()
{GUCEF_TRACE;

}

/*-------------------------------------------------------------------------*/

CPubSubClient::CPubSubClient( const CPubSubClient& src )
    : CORE::CObservingNotifier( src )
    , CORE::CIConfigurable( src )
{GUCEF_TRACE;

}

/*-------------------------------------------------------------------------*/

CPubSubClient::~CPubSubClient()
{GUCEF_TRACE;

}

/*-------------------------------------------------------------------------*/

CPubSubClient& 
CPubSubClient::operator=( const CPubSubClient& src )
{GUCEF_TRACE;

    if ( &src != this )
    {
        CORE::CIConfigurable::operator=( *this );
        CORE::CObservingNotifier::operator=( *this );
    }
    return *this;
}

/*-------------------------------------------------------------------------*/

const CString& 
CPubSubClient::GetClassTypeName( void ) const
{GUCEF_TRACE;

    static const CString classTypeName = "GUCEF::COMCORE::CPubSubClient";
    return classTypeName;
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace COMCORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/
