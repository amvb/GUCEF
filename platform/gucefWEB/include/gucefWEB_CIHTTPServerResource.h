/*
 *  gucefWEB: GUCEF module providing Web application functionality 
 *  for standardized protocols
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

#ifndef GUCEF_WEB_CIHTTPSERVERRESOURCE_H
#define GUCEF_WEB_CIHTTPSERVERRESOURCE_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#include <vector>

#ifndef GUCEF_MT_CMUTEX_H
#include "gucefMT_CMutex.h"
#define GUCEF_MT_CMUTEX_H
#endif /* GUCEF_MT_CMUTEX_H ? */

#ifndef GUCEF_CORE_CDYNAMICBUFFER_H
#include "CDynamicBuffer.h"
#define GUCEF_CORE_CDYNAMICBUFFER_H
#endif /* GUCEF_CORE_CDYNAMICBUFFER_H ? */

#ifndef GUCEF_CORE_CTSHAREDPTR_H
#include "CTSharedPtr.h"
#define GUCEF_CORE_CTSHAREDPTR_H
#endif /* GUCEF_CORE_CTSHAREDPTR_H ? */

#ifndef GUCEF_WEB_MACROS_H
#include "gucefWEB_macros.h"
#define GUCEF_WEB_MACROS_H
#endif /* GUCEF_WEB_MACROS_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace WEB {

/*-------------------------------------------------------------------------//
//                                                                         //
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

class GUCEF_WEB_PUBLIC_CPP CIHTTPServerResource
{
    public:
    
    typedef std::vector< CString > TStringVector;
    typedef CORE::CTSharedPtr< CIHTTPServerResource, MT::CMutex > THTTPServerResourcePtr;

    /**
     *  Result of a CreateResource operation.
     */
    enum ECreateState
    {
        CREATESTATE_CREATED                   , /**< The resource has been created and persisted as desired by the backend */
        CREATESTATE_CONFLICTING               , /**< Unable to create due to a conflicted data state (think of conflicting unique ids inside the data etc with those in a collection) */
        CREATESTATE_DESERIALIZATIONFAILED     , /**< Failed to deserialize the resource with given representation. */
        CREATESTATE_UNSUPPORTEDREPRESENTATION , /**< Resource representation is not supported for deserialization. */
        CREATESTATE_FAILED                      /**< Failed to create the resource */
    };
    typedef enum ECreateState TCreateState; 

    /**
     *  Result of a Deserialize operation.
     */
    enum EDeserializeState
    {
        DESERIALIZESTATE_SUCCEEDED      , /**< deserialization succeeded without any problems */
        DESERIALIZESTATE_CORRUPTEDINPUT , /**< Unable to deserialize because the input data is corrupt */
        DESERIALIZESTATE_UNABLETOUPDATE , /**< Unable to deserialize because after reading the input data successfully updating the resource failed. */
        DESERIALIZESTATE_NOTSUPPORTED
    };
    typedef enum EDeserializeState TDeserializeState;
    
    public:
    
    CIHTTPServerResource( void );
    
    CIHTTPServerResource( const CIHTTPServerResource& src );
    
    virtual ~CIHTTPServerResource();
    
    CIHTTPServerResource& operator=( const CIHTTPServerResource& src );

    /**
     *  Identifier of the resource, relative to the context of the handler.
     */
    virtual void SetURL( const CString& url ) = 0;

    /**
     *  Identifier of the resource, relative to the context of the handler.
     */
    virtual const CString& GetURL( void ) const = 0;

    /**
     *  Encoding of the resource (i.e. gzip compression). Matches the HTTP:Content-Encoding field.
     *  Typical example would be zip/gzip compressed content
     */
    virtual const CString& GetEncoding( const CString& resourcePath ) const = 0;

    /**
     *  Serializes the resource into a stream according to the representation.
     */
    virtual bool Serialize( const CString& resourcePath        ,
                            CORE::CDynamicBuffer& outputBuffer ,
                            const CString& representation      ,
                            const CString& params              ) = 0;
                    
    /**
     *   Returns a list of all representations the resource can be serialized to.
     */
    virtual const TStringVector& GetSupportedSerializationRepresentations( const CString& resourcePath ) = 0;

    /**
     *  Returns the representation that best matches a given list of representions for serialization.
     *  Returns "" in case no match can be found.
     */
    virtual CString GetBestMatchedSerializationRepresentation( const CString& resourcePath          ,
                                                               const TStringVector& representations ) = 0;

    /**
     *  Deserialize the resource from the given stream with given resource representation.
     *  @param isDeltaUpdateOnly Signals whether we are trying to deserialize a full resource in one go or just apply a delta update
     */
    virtual TDeserializeState Deserialize( const CString& resourcePath             ,
                                           const CORE::CDynamicBuffer& inputBuffer ,
                                           const CString& representation           ,
                                           bool isDeltaUpdateOnly                  ) = 0;

    /**
     *   Returns a list of all representations the resource can be deserialized from.
     */
    virtual const TStringVector& GetSupportedDeserializationRepresentations( const CString& resourcePath ) = 0;

    /**
     *  Returns the representation that best matches a given list of representions for deserialization.
     *  In common situations, this may be the same as the GetBestMatchedSerializationRepresentation(..) operation.
     *  Returns "" in case no match can be found.
     */
    virtual CString GetBestSupportedDeserializationRepresentation( const CString& resourcePath          ,
                                                                   const TStringVector& representations ) = 0;

    /**
     *  Create a new (contained) resource
     *
     *  @param transactionID The unique identifier of the create operation. If a resource was created earlier using the same transactionId, this operation should not create a new one but return the originally created resource instead.
     *  @param inputBuffer The buffer containing the serialized representation of the resource to create.
     *  @param representation The representation of the resource to create
     *  @param resourceOutput The created IResource. The representation of this resource shall match the representation of the resource to create.
     *  @param supportedRepresentationsOutput In case the representation is not supported for creation, this returns the list of supported representations.
     *  @return The status of the operation. See TCreateState.
     */
    virtual TCreateState CreateResource( const CString& resourcePath                   ,
                                         const CString& transactionID                  ,
                                         const CORE::CDynamicBuffer& inputBuffer       ,
                                         const CString& representation                 ,
                                         const CString& params                         ,
                                         THTTPServerResourcePtr& resourceOutput        ,
                                         TStringVector& supportedRepresentationsOutput ) = 0;
    
    /**
     *  Deletes this resource
     *
     *  @return Returns true if the resource could be deleted.
     */
    virtual bool DeleteResource( const CString& resourcePath ) = 0;

    /**
     *  The version of the resource (HTTP: Etag)
     */
    virtual const CString& GetResourceVersion( const CString& resourcePath ) = 0;
    
    virtual const CString& GetLastModifiedTime( const CString& resourcePath ) = 0;

    /**
     *  The cacheability of the resource.
     */
    virtual const CString& GetCacheability( const CString& resourcePath ) = 0;

    /**
     *  Signals whether the resource is a collection of other resources
     */
    virtual bool IsCollection( const CString& resourcePath ) const = 0;
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

} /* namespace COM */
} /* namespace GUCEF */

/*-------------------------------------------------------------------------*/

#endif /* GUCEF_WEB_CIHTTPSERVERRESOURCE_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 03-03-2007 :
        - Dinand: Added this section

---------------------------------------------------------------------------*/
    