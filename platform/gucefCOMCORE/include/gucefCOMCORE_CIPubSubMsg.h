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

#ifndef GUCEF_COMCORE_CIPUBSUBMSG_H
#define GUCEF_COMCORE_CIPUBSUBMSG_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_MT_CMUTEX_H
#include "gucefMT_CMutex.h"
#define GUCEF_MT_CMUTEX_H
#endif /* GUCEF_MT_CMUTEX_H ? */

#ifndef GUCEF_CORE_CTSHAREDPTR_H
#include "CTSharedPtr.h"
#define GUCEF_CORE_CTSHAREDPTR_H
#endif /* GUCEF_CORE_CTSHAREDPTR_H ? */

#ifndef GUCEF_CORE_CVALUELIST_H
#include "CValueList.h"
#define GUCEF_CORE_CVALUELIST_H
#endif /* GUCEF_CORE_CVALUELIST_H ? */

#ifndef GUCEF_CORE_CVARIANT_H
#include "gucefCORE_CVariant.h"
#define GUCEF_CORE_CVARIANT_H
#endif /* GUCEF_CORE_CVARIANT_H ? */

#ifndef GUCEF_CORE_CDATETIME_H
#include "gucefCORE_CDateTime.h"
#define GUCEF_CORE_CDATETIME_H
#endif /* GUCEF_CORE_CDATETIME_H ? */

#ifndef GUCEF_CORE_CDYNAMICBUFFER_H
#include "CDynamicBuffer.h"
#define GUCEF_CORE_CDYNAMICBUFFER_H
#endif /* GUCEF_CORE_CDYNAMICBUFFER_H ? */

#ifndef GUCEF_CORE_CICLONEABLE_H
#include "CICloneable.h"
#define GUCEF_CORE_CICLONEABLE_H
#endif /* GUCEF_CORE_CICLONEABLE_H ? */

#ifndef GUCEF_CORE_CLONEABLES_H
#include "cloneables.h"
#define GUCEF_CORE_CLONEABLES_H
#endif /* GUCEF_CORE_CLONEABLES_H ? */

#ifndef GUCEF_COMCORE_MACROS_H
#include "gucefCOMCORE_macros.h"      /* often used gucefCOMCORE macros */
#define GUCEF_COMCORE_MACROS_H
#endif /* GUCEF_COMCORE_MACROS_H ? */

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

/**
 *  Class providing a generic representation of a pub-sub message
 *  Based on the client used different capabilities will be available and 
 *  client will use beft effort to simulate others
 */
class GUCEF_COMCORE_EXPORT_CPP CIPubSubMsg : public CORE::CICloneable
{
    public:

    typedef std::pair< CORE::CVariant, CORE::CVariant > TKeyValuePair;
    typedef std::vector< TKeyValuePair > TKeyValuePairs;

    CIPubSubMsg( void );

    CIPubSubMsg( const CIPubSubMsg& src );

    virtual ~CIPubSubMsg();
    
    virtual CORE::CVariant& GetMsgId( void ) = 0;    
    virtual const CORE::CVariant& GetMsgId( void ) const = 0;
    
    virtual CORE::CDateTime& GetMsgDateTime( void ) = 0;    
    virtual const CORE::CDateTime& GetMsgDateTime( void ) const = 0;

    /**
     *  If the pub-sub system does not itself support key-value attributes per
     *  message this member function is intended to provide easy access to the 
     *  payload.
     *  If used in cases where only/specifically key-value attributes are supported the client
     *  will attempt to provide the value of the first key-value pair in a best
     *  effort manner.
     */    
    virtual CORE::CVariant& GetPrimaryPayload( void ) = 0;
    virtual const CORE::CVariant& GetPrimaryPayload( void ) const = 0;

    virtual TKeyValuePairs& GetKeyValuePairs( void ) = 0;
    virtual const TKeyValuePairs& GetKeyValuePairs( void ) const = 0;

    virtual TKeyValuePairs& GetMetaDataKeyValuePairs( void ) = 0;
    virtual const TKeyValuePairs& GetMetaDataKeyValuePairs( void ) const = 0;
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace COMCORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/

#endif /* GUCEF_COMCORE_CIPUBSUBMSG_H ? */
