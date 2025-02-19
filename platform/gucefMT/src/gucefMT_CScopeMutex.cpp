/*
 *  gucefMT: GUCEF module providing multithreading solutions
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

#include <assert.h>

#ifndef GUCEF_MT_CMUTEX_H
#include "gucefMT_CMutex.h"
#define GUCEF_MT_CMUTEX_H
#endif /* GUCEF_MT_CMUTEX_H ? */

#include "gucefMT_CScopeMutex.h"     /* Our mutex class definition */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace MT {

/*-------------------------------------------------------------------------//
//                                                                         //
//      IMPLEMENTATION                                                     //
//                                                                         //
//-------------------------------------------------------------------------*/

CScopeMutex::CScopeMutex( const CMutex& mutex )
    : m_mutex( &mutex )
    , m_isLocked( false )
{
    assert( m_mutex );
        
    m_isLocked = m_mutex->Lock();
}

/*--------------------------------------------------------------------------*/

CScopeMutex::~CScopeMutex()
{
    if ( m_isLocked )
        m_isLocked = !m_mutex->Unlock();
}

/*--------------------------------------------------------------------------*/

bool 
CScopeMutex::IsLocked( void ) const
{
    return m_isLocked;
}

/*--------------------------------------------------------------------------*/

bool
CScopeMutex::EarlyUnlock( void )
{
    if ( m_isLocked )
    {
        m_isLocked = !m_mutex->Unlock();
        return !m_isLocked;
    }
    return false;
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace MT */
}; /* namespace GUCEF */

/*--------------------------------------------------------------------------*/
