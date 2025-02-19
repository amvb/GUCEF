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

#ifndef GUCEF_WEB_CIHTTPSERVERREQUESTHANDLER_H
#define GUCEF_WEB_CIHTTPSERVERREQUESTHANDLER_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_WEB_CHTTPREQUESTDATA_H
#include "gucefWEB_CHttpRequestData.h"
#define GUCEF_WEB_CHTTPREQUESTDATA_H
#endif /* GUCEF_WEB_CHTTPREQUESTDATA_H ? */

#ifndef GUCEF_WEB_CHTTPRESPONSEDATA_H
#include "gucefWEB_CHttpResponseData.h"
#define GUCEF_WEB_CHTTPRESPONSEDATA_H
#endif /* GUCEF_WEB_CHTTPRESPONSEDATA_H ? */

#ifndef GUCEF_WEB_CIHTTPSERVERROUTERCONTROLLER_H
#include "gucefWEB_CIHTTPServerRouterController.h"
#define GUCEF_WEB_CIHTTPSERVERROUTERCONTROLLER_H
#endif /* GUCEF_WEB_CIHTTPSERVERROUTERCONTROLLER_H ? */

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

class GUCEF_WEB_PUBLIC_CPP CIHttpServerRequestHandler
{
    public:

    virtual bool OnRequest( const CHttpRequestData& request ,
                            CHttpResponseData& response     ) = 0;

    virtual bool OnRead( const CHttpRequestData& request ,
                         CHttpResponseData& response     ) = 0;

    virtual bool OnReadMetaData( const CHttpRequestData& request ,
                                 CHttpResponseData& response     ) = 0;
    
    virtual bool OnUpdate( const CHttpRequestData& request ,
                           bool isDeltaUpdateOnly          ,
                           CHttpResponseData& response     ) = 0;
    
    virtual bool OnCreate( const CHttpRequestData& request ,
                           CHttpResponseData& response     ) = 0;
    
    virtual bool OnDelete( const CHttpRequestData& request ,
                           CHttpResponseData& response     ) = 0;

    virtual bool SetRouterController( CIHTTPServerRouterController* routerController ) = 0;
    
    virtual CIHTTPServerRouterController* GetRouterController( void ) const = 0;

    CIHttpServerRequestHandler( void );
    CIHttpServerRequestHandler( const CIHttpServerRequestHandler& src );
    virtual ~CIHttpServerRequestHandler();
};

/*-------------------------------------------------------------------------*/

typedef CORE::CTFactoryBase< CIHttpServerRequestHandler > THttpServerRequestHandlerFactory;

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

} /* namespace COM */
} /* namespace GUCEF */

/*-------------------------------------------------------------------------*/

#endif /* GUCEF_WEB_CIHTTPSERVERREQUESTHANDLER_H ? */
