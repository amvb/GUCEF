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

#include "gucefMT_CObjectScopeReadOnlyLock.h"

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

CObjectScopeReadOnlyLock::CObjectScopeReadOnlyLock( const CILockable* lockableObject )
    : m_lockableObject( lockableObject )
    , m_isLocked( false )
{
    assert( 0 != m_lockableObject );
        
    m_isLocked = m_lockableObject->ReadOnlyLock();
}

/*--------------------------------------------------------------------------*/

CObjectScopeReadOnlyLock::CObjectScopeReadOnlyLock( const CILockable& lockableObject )
    : m_lockableObject( &lockableObject )
    , m_isLocked( false )
{
    assert( 0 != m_lockableObject );
        
    m_isLocked = m_lockableObject->ReadOnlyLock();
}

/*--------------------------------------------------------------------------*/

CObjectScopeReadOnlyLock::~CObjectScopeReadOnlyLock()
{
    if ( m_isLocked )
    {
        m_isLocked = !m_lockableObject->ReadOnlyUnlock();
    }
}

/*--------------------------------------------------------------------------*/

bool 
CObjectScopeReadOnlyLock::IsLocked( void ) const
{
    return m_isLocked;
}

/*--------------------------------------------------------------------------*/

bool 
CObjectScopeReadOnlyLock::EarlyReaderUnlock( void )
{
    if ( m_isLocked )
    {
        m_isLocked = !m_lockableObject->ReadOnlyUnlock();
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
