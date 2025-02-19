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

#include <string.h>             /* needed for memset() */

#ifndef GUCEF_CORE_CLOGMANAGER_H
#include "CLogManager.h"
#define GUCEF_CORE_CLOGMANAGER_H
#endif /* GUCEF_CORE_CLOGMANAGER_H ? */

#ifndef GUCEF_CORE_DVCPPSTRINGUTILS_H
#include "dvcppstringutils.h"
#define GUCEF_CORE_DVCPPSTRINGUTILS_H
#endif /* GUCEF_CORE_DVCPPSTRINGUTILS_H ? */

#ifndef GUCEF_COMCORE_DVSOCKET_H
#include "dvwinsock.h"          /* socket API */
#define GUCEF_COMCORE_DVSOCKET_H
#endif /* GUCEF_COMCORE_DVSOCKET_H ? */

#ifndef GUCEF_COMCORE_CSOCKET_H
#include "CSocket.h"            /* base class for all sockets */
#define GUCEF_COMCORE_CSOCKET_H
#endif /* GUCEF_COMCORE_CSOCKET_H ? */

#include "CCom.h"               /* definition of CCom class */

#ifdef ACTIVATE_MEMORY_MANAGER
  #ifndef GUCEF_NEW_ON_H
  #include "gucef_new_on.h"   /* Use the GUCEF memory manager instead of the standard manager ? */
  #define GUCEF_NEW_ON_H
  #endif /* GUCEF_NEW_ON_H ? */
#endif /* ACTIVATE_MEMORY_MANAGER ? */

#if ( GUCEF_PLATFORM_MSWIN == GUCEF_PLATFORM )

  #ifndef GUCEF_COMCORE_CWIN32SERIALPORT_H
  #include "gucefCOMCORE_CWin32SerialPort.h"
  #define GUCEF_COMCORE_CWIN32SERIALPORT_H
  #endif /* GUCEF_COMCORE_CWIN32SERIALPORT_H ? */

  #ifndef GUCEF_COMCORE_CWIN32NETWORKINTERFACE_H
  #include "gucefCOMCORE_CWin32NetworkInterface.h"
  #define GUCEF_COMCORE_CWIN32NETWORKINTERFACE_H
  #endif /* GUCEF_COMCORE_CWIN32NETWORKINTERFACE_H ? */

#endif

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace COMCORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

#if ( GUCEF_PLATFORM == GUCEF_PLATFORM_MSWIN )

bool
GetMSWinInternetProxyFromRegistry( CORE::CString& remoteHost ,
                                   UInt16& port              ,
                                   bool& active              )
{GUCEF_TRACE;

    char lszValue[ 255 ];
    HKEY hKey;
    DWORD dwType = REG_SZ;
    DWORD dwSize = 255;

    if( ERROR_SUCCESS == RegOpenKeyEx( HKEY_CURRENT_USER                                                 ,
                                       "SOFTWARE\\MICROSOFT\\WINDOWS\\CURRENTVERSION\\INTERNET SETTINGS" ,
                                       0L                                                                ,
                                       KEY_ALL_ACCESS                                                    ,
                                       &hKey                                                             ) )
    {
        if ( ERROR_SUCCESS == RegQueryValueEx( hKey              ,
                                               "ProxyServer"     ,
                                               NULL              ,
                                               &dwType           ,
                                               (LPBYTE)&lszValue ,
                                               &dwSize           ) )
        {
            CORE::CString regValue( lszValue );
            remoteHost = regValue.SubstrToChar( ':', true );
            port = 80;

            CORE::CString portStr( regValue.SubstrToChar( ':', false ) );
            if ( portStr.Length() > 0 )
            {
                port = static_cast< UInt16 >( CORE::StringToInt32( portStr ) );
            }

            active = false;
            if ( ERROR_SUCCESS == RegQueryValueEx( hKey              ,
                                                   "ProxyEnable"     ,
                                                   NULL              ,
                                                   &dwType           ,
                                                   (LPBYTE)&lszValue ,
                                                   &dwSize           ) )
            {
                active = CORE::StringToBool( lszValue );
            }
            return true;
        }
        RegCloseKey( hKey );
    }
    return false;
}

#endif /* GUCEF_PLATFORM_MSWIN ? */

/*-------------------------------------------------------------------------*/

CCom::CCom()
    : _keep_gstats( false ) ,
      _scount( 0 )          ,
      m_sockets()           ,
      m_proxyList()
{GUCEF_TRACE;

    memset( &_stats, 0, sizeof(TSocketStats) );

    #if ( GUCEF_PLATFORM == GUCEF_PLATFORM_MSWIN )

// @TODO use InternetQueryOption
// http://msdn2.microsoft.com/en-us/library/aa385101.aspx

    /*
     *  Read the O/S proxy server settings
     */

    CORE::CString remoteHost;
    UInt16 port;
    bool active;

    if ( GetMSWinInternetProxyFromRegistry( remoteHost ,
                                            port       ,
                                            active     ) )
    {
        SetSystemWideProxyServer( "http"     ,
                                  remoteHost ,
                                  port       ,
                                  active     );
    }

    #endif /* GUCEF_PLATFORM_MSWIN ? */
}

/*-------------------------------------------------------------------------*/

CCom::~CCom()
{GUCEF_TRACE;

}

/*-------------------------------------------------------------------------*/

void
CCom::RegisterSocketObject( CSocket* socket )
{GUCEF_TRACE;

    _mutex.Lock();
    m_sockets.insert( socket );
    ++_scount;
    _mutex.Unlock();
}

/*-------------------------------------------------------------------------*/

void
CCom::UnregisterSocketObject( CSocket* socket )
{GUCEF_TRACE;

    _mutex.Lock();
    m_sockets.erase( socket );
    --_scount;
    _mutex.Unlock();
}

/*-------------------------------------------------------------------------*/

UInt32
CCom::GetSocketCount( void ) const
{GUCEF_TRACE;

    return _scount;
}

/*-------------------------------------------------------------------------*/

void
CCom::SetUseGlobalStats( bool keep_gstats )
{GUCEF_TRACE;

    _keep_gstats = keep_gstats;
}

/*-------------------------------------------------------------------------*/

bool
CCom::GetUseGlobalStats( void ) const
{GUCEF_TRACE;

    return _keep_gstats;
}

/*-------------------------------------------------------------------------*/

void
CCom::ResetGlobalStats( void )
{GUCEF_TRACE;

    _stats.bytes_sent = 0;
    _stats.bytes_recieved = 0;
    _stats.bps_sent = 0;
    _stats.bps_recieved = 0;
}

/*-------------------------------------------------------------------------*/

const CCom::TSocketStats&
CCom::GetGlobalStats( void ) const
{GUCEF_TRACE;

    return _stats;
}

/*-------------------------------------------------------------------------*/

bool
CCom::GetCommunicationPortList( const CORE::CString& portType ,
                                TStringList& portList         ) const
{
    CORE::CString typeOfPort = portType.Lowercase();
    if ( "serial" == typeOfPort ||
         "com" == typeOfPort     )
    {
        #if ( GUCEF_PLATFORM_MSWIN == GUCEF_PLATFORM )
        CWin32SerialPort::PopulatePortList( portList );
        return true;
        #endif
    }    
    return false;
}

/*-------------------------------------------------------------------------*/
    
CICommunicationInterface*
CCom::GetCommunicationPort( const CORE::CString& portType ,
                            const CORE::CString& portId   )
{
    CORE::CString typeOfPort = portType.Lowercase();

    _mutex.Lock();

    // Check to see if we already have an entry for the given port
    TPortIndex::iterator i = m_portObjs.find( typeOfPort );
    if ( i != m_portObjs.end() )
    {
        TPortMap& portMap = (*i).second;
        TPortMap::iterator n = portMap.find( portId );
        if ( n != portMap.end() )
        {
            CICommunicationInterface* port = (*n).second;
            _mutex.Unlock();
            return port;
        }
    }

    // No such port object was found, check to see if we can create it
    if ( "serial" == typeOfPort ||
         "com" == typeOfPort     )
    {
        #if ( GUCEF_PLATFORM_MSWIN == GUCEF_PLATFORM )

        CICommunicationInterface* port = CWin32SerialPort::Create( portId );
        if ( NULL != port )
        {
            TPortMap& portMap = m_portObjs[ portType ];
            portMap[ portId ] = port;
            _mutex.Unlock();
            return port;
        }

        #endif
    }
    
    _mutex.Unlock();    
    return NULL;
}

/*-------------------------------------------------------------------------*/

void
CCom::LazyInitNetworkInterfaces( void ) const
{
    if ( m_nics.empty() )
    {
        #if ( GUCEF_PLATFORM_MSWIN == GUCEF_PLATFORM )
        CWin32NetworkInterface::EnumNetworkAdapters( m_nics );
        #endif
    }
}

/*-------------------------------------------------------------------------*/

bool 
CCom::GetNetworkInterfaceList( TStringList& interfaceIDs ) const
{GUCEF_TRACE;

    LazyInitNetworkInterfaces();
    
    TNetworkInterfaceVector::const_iterator i = m_nics.begin();
    while ( i != m_nics.end() )
    {
        interfaceIDs.push_back( (*i)->GetAdapterName() );
        ++i;
    }
    return true;
}

/*-------------------------------------------------------------------------*/

CINetworkInterface* 
CCom::GetNetworkInterface( const CORE::CString& interfaceID )
{GUCEF_TRACE;

    LazyInitNetworkInterfaces();
    
    TNetworkInterfaceVector::const_iterator i = m_nics.begin();
    while ( i != m_nics.end() )
    {
        if ( interfaceID == (*i)->GetAdapterName() )
        {
            return (*i);
        }
        ++i;
    }
    return GUCEF_NULL;
}

/*-------------------------------------------------------------------------*/

bool 
CCom::GetAllNetworkInterfaceIPInfo( CINetworkInterface::TIPInfoVector& ipInfo )
{GUCEF_TRACE;

    LazyInitNetworkInterfaces();
    
    bool totalSuccess = true;
    TNetworkInterfaceVector::const_iterator i = m_nics.begin();
    while ( i != m_nics.end() )
    {
        totalSuccess = totalSuccess && (*i)->GetIPInfo( ipInfo, false );
        ++i;
    }
    return totalSuccess;
}

/*-------------------------------------------------------------------------*/

bool
CCom::SetSystemWideProxyServer( const CORE::CString& protocol ,
                                const bool active             )
{GUCEF_TRACE;

    TProxyList::iterator i = m_proxyList.find( protocol );
    if ( i != m_proxyList.end() )
    {
        (*i).second.active = active;
        return true;
    }
    return false;
}

/*-------------------------------------------------------------------------*/

bool
CCom::SetSystemWideProxyServer( const CORE::CString& protocol   ,
                                const CORE::CString& remoteHost ,
                                const UInt16 remotePort         ,
                                const bool active               )
{GUCEF_TRACE;

    GUCEF_SYSTEM_LOG( CORE::LOGLEVEL_NORMAL, "Setting system wide proxy server for protocol " + protocol +
                          " to " + remoteHost + ":" + CORE::UInt16ToString( remotePort ) + " and active state " + CORE::BoolToString( active ) );

    TProxyServer& proxyServer = m_proxyList[ protocol ];
    proxyServer.host = remoteHost;
    proxyServer.port = remotePort;
    proxyServer.active = active;
    return true;
}

/*-------------------------------------------------------------------------*/

bool
CCom::GetSystemWideProxyServer( const CORE::CString& protocol ,
                                CORE::CString& remoteHost     ,
                                UInt16& remotePort            ,
                                bool& active                  ) const
{GUCEF_TRACE;

    TProxyList::const_iterator i = m_proxyList.find( protocol );
    if ( i != m_proxyList.end() )
    {
        const TProxyServer& proxyServer = (*i).second;
        remoteHost = proxyServer.host;
        remotePort = proxyServer.port;
        active = proxyServer.active;
        return true;
    }
    return false;
}

/*-------------------------------------------------------------------------*/

bool
CCom::IsSystemWideProxyServerActive( const CORE::CString& protocol ) const
{GUCEF_TRACE;

    TProxyList::const_iterator i = m_proxyList.find( protocol );
    if ( i != m_proxyList.end() )
    {
        return (*i).second.active;
    }
    return false;
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace COMCORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/
