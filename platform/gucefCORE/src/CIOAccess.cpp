/*
 *  gucefCORE: GUCEF module providing O/S abstraction and generic solutions
 *  Copyright (C) 2002 - 2007.  Dinand Vanvelzen
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#include <string.h>

#ifndef GUCEF_CORE_CDYNAMICBUFFER_H
#include "CDynamicBuffer.h"
#define GUCEF_CORE_CDYNAMICBUFFER_H
#endif /* GUCEF_CORE_CDYNAMICBUFFER_H ? */

#include "CIOAccess.h"

#ifndef GUCEF_CORE_GUCEF_ESSENTIALS_H
#include "gucef_essentials.h"
#define GUCEF_CORE_GUCEF_ESSENTIALS_H
#endif /* GUCEF_CORE_GUCEF_ESSENTIALS_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace CORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

UInt32 GUCEF_CALLSPEC_PREFIX
fa_open( struct SIOAccess* access ) GUCEF_CALLSPEC_SUFFIX
{GUCEF_TRACE;
        ( (CIOAccess*) access->privdata )->Open();
        return 0;
}

/*-------------------------------------------------------------------------*/

UInt32 GUCEF_CALLSPEC_PREFIX
fa_opened( struct SIOAccess* access ) GUCEF_CALLSPEC_SUFFIX
{GUCEF_TRACE;
        return ( (CIOAccess*) access->privdata )->Opened();
}

/*-------------------------------------------------------------------------*/

UInt32 GUCEF_CALLSPEC_PREFIX
fa_close( struct SIOAccess* access ) GUCEF_CALLSPEC_SUFFIX
{GUCEF_TRACE;
        ( (CIOAccess*) access->privdata )->Close();
        return 0;
}

/*-------------------------------------------------------------------------*/

UInt32 GUCEF_CALLSPEC_PREFIX
fa_readl( struct SIOAccess* access ,
          char **dest              ) GUCEF_CALLSPEC_SUFFIX
{GUCEF_TRACE;
        CString str = ( (CIOAccess*) access->privdata )->ReadLine();
        *dest = new char[ str.Length()+1 ];
        memcpy( *dest, str.C_String(), str.Length() );
        return str.Length();
}

/*-------------------------------------------------------------------------*/

UInt32 GUCEF_CALLSPEC_PREFIX
fa_reads( struct SIOAccess* access ,
          char **dest              ) GUCEF_CALLSPEC_SUFFIX
{GUCEF_TRACE;
        CString str = ( (CIOAccess*) access->privdata )->ReadString();
        *dest = new char[ str.Length()+1 ];
        memcpy( *dest, str.C_String(), str.Length() );
        return str.Length();
}

/*-------------------------------------------------------------------------*/

UInt32 GUCEF_CALLSPEC_PREFIX
fa_write( struct SIOAccess* access ,
          const void *srcData      ,
          UInt32 esize             ,
          UInt32 elements          ) GUCEF_CALLSPEC_SUFFIX
{GUCEF_TRACE;
        return ( (CIOAccess*) access->privdata )->Write( srcData  ,
                                                         esize    ,
                                                         elements );
}

/*-------------------------------------------------------------------------*/

UInt32 GUCEF_CALLSPEC_PREFIX
fa_read( struct SIOAccess* access ,
         void *dest               ,
         UInt32 esize             ,
         UInt32 elements          ) GUCEF_CALLSPEC_SUFFIX
{GUCEF_TRACE;
        return ( (CIOAccess*) access->privdata )->Read( dest     ,
                                                        esize    ,
                                                        elements );
}

/*-------------------------------------------------------------------------*/

UInt32 GUCEF_CALLSPEC_PREFIX
fa_tell( struct SIOAccess* access ) GUCEF_CALLSPEC_SUFFIX
{GUCEF_TRACE;

        return ( (CIOAccess*) access->privdata )->Tell();
}

/*-------------------------------------------------------------------------*/

Int32 GUCEF_CALLSPEC_PREFIX
fa_seek( struct SIOAccess* access ,
         Int32 offset             ,
         Int32 origin             ) GUCEF_CALLSPEC_SUFFIX
{GUCEF_TRACE;
        return ( (CIOAccess*) access->privdata )->Seek( offset ,
                                                        origin );
}

/*-------------------------------------------------------------------------*/

UInt32 GUCEF_CALLSPEC_PREFIX
fa_setpos( struct SIOAccess* access ,
           UInt32 pos               ) GUCEF_CALLSPEC_SUFFIX
{GUCEF_TRACE;
        return ( (CIOAccess*) access->privdata )->Setpos( pos );
}

/*-------------------------------------------------------------------------*/

Int32 GUCEF_CALLSPEC_PREFIX
fa_getc( struct SIOAccess* access ) GUCEF_CALLSPEC_SUFFIX
{GUCEF_TRACE;
        return ( (CIOAccess*) access->privdata )->GetChar();
}

/*-------------------------------------------------------------------------*/

Int32 GUCEF_CALLSPEC_PREFIX
fa_eof( struct SIOAccess* access ) GUCEF_CALLSPEC_SUFFIX
{GUCEF_TRACE;
        return ( (CIOAccess*) access->privdata )->Eof();
}

/*-------------------------------------------------------------------------*/

void GUCEF_CALLSPEC_PREFIX
fa_free( void* mem ) GUCEF_CALLSPEC_SUFFIX
{GUCEF_TRACE;
        delete []((char*)mem);
}

/*-------------------------------------------------------------------------*/

CIOAccess::CIOAccess( void )
{GUCEF_TRACE;

    LinkCStyleAccess();
}

/*-------------------------------------------------------------------------*/

CIOAccess::CIOAccess( const CIOAccess& src )
{GUCEF_TRACE;

    LinkCStyleAccess();
}

/*-------------------------------------------------------------------------*/

CIOAccess::~CIOAccess()
{GUCEF_TRACE;

    memset( &m_cStyleAccess, 0, sizeof( TIOAccess ) );
}

/*-------------------------------------------------------------------------*/

CIOAccess&
CIOAccess::operator=( const CIOAccess& src )
{
    if ( this != &src )
    {

    }
    return *this;
}

/*-------------------------------------------------------------------------*/

void
CIOAccess::LinkCStyleAccess( void )
{GUCEF_TRACE;

    memset( &m_cStyleAccess, 0, sizeof( TIOAccess ) );

    m_cStyleAccess.close = fa_close;
    m_cStyleAccess.open = fa_open;
    m_cStyleAccess.write = fa_write;
    m_cStyleAccess.close = fa_close;
    m_cStyleAccess.opened = fa_opened;
    m_cStyleAccess.readl = fa_readl;
    m_cStyleAccess.reads = fa_reads;
    m_cStyleAccess.read = fa_read;
    m_cStyleAccess.tell = fa_tell;
    m_cStyleAccess.seek = fa_seek;
    m_cStyleAccess.setpos = fa_setpos;
    m_cStyleAccess.getc = fa_getc;
    m_cStyleAccess.eof = fa_eof;
    m_cStyleAccess.memfree = fa_free;
    m_cStyleAccess.privdata = this;
}

/*-------------------------------------------------------------------------*/

UInt32
CIOAccess::ReadUntill( void *dest            ,
                       UInt32 bsize          ,
                       const void* delimiter ,
                       UInt32 delimsize      )
{
        //DEBUGOUTPUT( "CIOAccess::ReadUntill()" );

        GUCEF_BEGIN;
        if ( !bsize )
        {
                GUCEF_END;
                return 0;
        }
        if ( !delimsize )
        {
                GUCEF_END_RET( UInt32, Read( dest  ,
                                                bsize ,
                                                1     ) );
        }

        char* buffer = new char[ delimsize ];
        char* bufwritepos = buffer;
        char* destbuf = static_cast<char*>( dest );
        UInt32 i;
        for ( i=0; i<bsize; ++i )
        {
                if ( !Eof() )
                {
                        /*
                         *      Add a byte to our read buffer
                         */
                        if ( bufwritepos - buffer < (Int32)delimsize-1 )
                        {
                                *bufwritepos = GetChar();
                                ++bufwritepos;
                        }
                        else
                        {
                                for ( UInt32 n=0; n<delimsize-1; ++n )
                                {
                                        buffer[ n ] = buffer[ n+1 ];
                                }
                                *bufwritepos = GetChar();
                        }

                        /*
                         *      Have we reached the delimiter ?
                         */
                        if ( memcmp( buffer, delimiter, delimsize ) == 0 )
                        {
                                delete []buffer;
                                destbuf[ i ] = '\0';
                                GUCEF_END;
                                return i;

                        }
                        destbuf[ i ] = *bufwritepos;
                }
                else
                {
                        delete []buffer;
                        destbuf[ i ] = '\0';
                        GUCEF_END;
                        return i;
                }
        }
        delete []buffer;
        destbuf[ bsize-i ] = '\0';
        GUCEF_END;
        return i;
}

/*-------------------------------------------------------------------------*/

/**
 *      Skips bytes untill the delimiter is reached or
 *      untill the end of the file is reached.
 *      the actual number of bytes skipped is returned.
 *
 *      @param delimiter the delimiter bytes
 *      @param delimsize size of the delimiter segment
 *      @return the actual number of bytes skipped.
 */
UInt32
CIOAccess::SkipUntill( const void* delimiter ,
                       UInt32 delimsize      )
{
        //DEBUGOUTPUT( "CIOAccess::SkipUntill()" );

        GUCEF_BEGIN;
        if ( !delimsize )
        {
                Seek( 0, SEEK_END );
        }

        char* buffer = new char[ delimsize ];
        char* bufwritepos = buffer;
        UInt32 pos = Tell();
        while( !Eof() )
        {
                /*
                 *      Add a byte to our read buffer
                 */
                if ( bufwritepos - buffer < (Int32)delimsize-1 )
                {
                        *bufwritepos = GetChar();
                        ++bufwritepos;
                }
                else
                {
                        for ( UInt32 n=0; n<delimsize-1; ++n )
                        {
                                buffer[ n ] = buffer[ n+1 ];
                        }
                        *bufwritepos = GetChar();
                }

                /*
                 *      Have we reached the delimiter ?
                 */
                if ( memcmp( buffer, delimiter, delimsize ) == 0 )
                {
                        delete []buffer;
                        GUCEF_END_RET( UInt32, Tell() - pos );
                }
        }
        delete []buffer;
        GUCEF_END_RET( UInt32, Tell() - pos );
}

/*-------------------------------------------------------------------------*/

UInt32
CIOAccess::Read( CDynamicBuffer& dest ,
                 UInt32 esize         ,
                 UInt32 elements      )
{GUCEF_TRACE;

    // First we ensure that we have enough space in the buffer to copy our data
    // into the buffer manually
    dest.SetBufferSize( dest.GetDataSize() + ( esize * elements ) ,
                        false                                     );

    // Perform the actual read
    UInt32 nrOfBytesRead = Read( static_cast< UInt8* >( dest.GetBufferPtr() ) + dest.GetDataSize() ,
                                 esize                                                             ,
                                 elements                                                          );

    // Correct the data delimiter in the buffer
    dest.SetDataSize( dest.GetDataSize() + nrOfBytesRead );

    return nrOfBytesRead;
}

/*-------------------------------------------------------------------------*/

UInt32
CIOAccess::Read( CDynamicBuffer& dest ,
                 UInt32 esize         )
{GUCEF_TRACE;

    UInt32 currentOffset = Tell();
    Seek( 0, SEEK_END );
    UInt32 endOffset = Tell();
    Setpos( currentOffset );

    UInt32 bytesToRead = endOffset - currentOffset;
    UInt32 elementsToRead = bytesToRead / esize;

    return Read( dest, esize, elementsToRead );
}

/*-------------------------------------------------------------------------*/

TIOAccess*
CIOAccess::CStyleAccess( void )
{GUCEF_TRACE;

    return &m_cStyleAccess;
}

/*-------------------------------------------------------------------------*/

UInt32
CIOAccess::Write( const void* srcdata ,
                  UInt32 esize        ,
                  UInt32 elements     )
{GUCEF_TRACE;

    // Dummy at this level, override to implement
    return 0;
}

/*-------------------------------------------------------------------------*/

UInt32
CIOAccess::Write( CIOAccess& sourceData )
{GUCEF_TRACE;

    UInt32 byteCount=0, totalByteCount=0;
    CDynamicBuffer readBuffer( 1024, true );
    readBuffer.SetDataSize( 1024 );

    while ( !sourceData.Eof() )
    {
        byteCount = sourceData.Read( readBuffer.GetBufferPtr(), 1, 1024 );
        if ( byteCount > 0 )
        {
            Write( readBuffer.GetBufferPtr(), 1, byteCount );
            totalByteCount += byteCount;
        }
        else
        {
            return totalByteCount;
        }
    }

    return totalByteCount;
}

/*-------------------------------------------------------------------------*/

UInt32
CIOAccess::Write( const CString& string )
{GUCEF_TRACE;

    UInt32 bytesWritten = Write( string.C_String(), 1, string.Length() );
    if ( bytesWritten == string.Length() ) 
    {
        bytesWritten += Write( GUCEF_EOL, 1, GUCEF_EOL_LENGTH );
    }
    return bytesWritten;
}

/*-------------------------------------------------------------------------*/

UInt32
CIOAccess::GetSize( void ) const
{GUCEF_TRACE;

    UInt32 pos = Tell();
    const_cast< CIOAccess* >( this )->Seek( 0, SEEK_END );
    UInt32 size = Tell();
    const_cast< CIOAccess* >( this )->Seek( pos, SEEK_SET );
    return size;
}

/*-------------------------------------------------------------------------*/

UInt32
CIOAccess::Setpos( UInt32 position )
{GUCEF_TRACE;

    return Seek( position, SEEK_SET );
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/
