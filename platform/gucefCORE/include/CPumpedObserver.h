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

#ifndef GUCEF_CORE_CPUMPEDOBSERVER_H
#define GUCEF_CORE_CPUMPEDOBSERVER_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_MT_CTMAILBOX_H
#include "gucefMT_CTMailBox.h"
#define GUCEF_MT_CTMAILBOX_H
#endif /* GUCEF_MT_CTMAILBOX_H ? */

#ifndef GUCEF_CORE_COBSERVER_H
#include "CObserver.h"
#define GUCEF_CORE_COBSERVER_H
#endif /* GUCEF_CORE_COBSERVER_H ? */

#ifndef GUCEF_CORE_CTEVENTHANDLERFUNCTOR_H
#include "gucefCORE_CTEventHandlerFunctor.h"
#define GUCEF_CORE_CTEVENTHANDLERFUNCTOR_H
#endif /* GUCEF_CORE_CTEVENTHANDLERFUNCTOR_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace CORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

class CPulseGenerator;

/*-------------------------------------------------------------------------*/

class GUCEF_CORE_PUBLIC_CPP CPumpedObserver : public CObserver
{
    public:

    CPumpedObserver( void );

    CPumpedObserver( CPulseGenerator& pulsGenerator );

    CPumpedObserver( const CPumpedObserver& src );

    virtual ~CPumpedObserver();

    CPumpedObserver& operator=( const CPumpedObserver& src );

    virtual const CString& GetClassTypeName( void ) const GUCEF_VIRTUAL_OVERRIDE;

    CPulseGenerator* GetPulseGenerator( void ) const;

    /**
     *  A pumped observer uses pulse generator events to allow for async 
     *  OnNotify processing via OnPumpedNotify()
     *
     *  When doing this it does NOT by default also consider the pulse event itself as a
     *  event message to be propagated. You can change this with SetPropagatePulseEvent()
     *  This allows you to take advantage of the same pulse to trigger other things.
     */
    void SetPropagatePulseEvent( bool propagatePulseEventMsg );

    bool GetPropagatePulseEvent( void ) const;

    protected:

    /**
     *  Event callback member function.
     *  Implement this in your descending class to handle
     *  notification events.
     *
     *  Note that in contrast to OnNotify, which is performed in
     *  the calling thread, this call is always made in the main
     *  application thread or whatever thread provided the pulse generator. 
     *  As such it is well suited for linking
     *  non-tread safe code via an observer to a notifier that
     *  operates from within another thread.
     *
     *  @param notifier the notifier that sent the notification
     *  @param eventid the unique event id for an event
     *  @param eventdata optional notifier defined userdata
     */
    virtual void OnPumpedNotify( CNotifier* notifier                 ,
                                 const CEvent& eventid               ,
                                 CICloneable* eventdata = GUCEF_NULL );

    virtual const MT::CILockable* AsLockable( void ) const GUCEF_VIRTUAL_OVERRIDE;

    protected:

    /**
     *  Event callback member function.
     *  Places the given event in the mailbox where is awaits
     *  the next pump cycle.
     *
     *  Note: DO NOT OVERRIDE !!!
     *
     *  @param notifier the notifier that sent the notification
     *  @param eventid the unique event id for an event
     *  @param eventdata optional notifier defined userdata
     */
    virtual void OnNotify( CNotifier* notifier           ,
                           const CEvent& eventid         ,
                           CICloneable* eventdata = NULL ) GUCEF_VIRTUAL_OVERRIDE;
    
    virtual bool Lock( UInt32 lockWaitTimeoutInMs = GUCEF_MT_DEFAULT_LOCK_TIMEOUT_IN_MS ) const GUCEF_VIRTUAL_OVERRIDE;

    virtual bool Unlock( void ) const GUCEF_VIRTUAL_OVERRIDE;

    private:
    typedef CTEventHandlerFunctor< CPumpedObserver > TEventCallback;

    void OnPulse( CNotifier* notifier           ,
                  const CEvent& eventid         ,
                  CICloneable* eventdata = NULL );

    void OnPulseGeneratorDestruction( CNotifier* notifier           ,
                                      const CEvent& eventid         ,
                                      CICloneable* eventdata = NULL );

    private:

    CPulseGenerator* m_pulsGenerator;
    bool m_propagatePulseEvent;
    MT::CTMailBox< CEvent > m_mailbox;
    MT::CMutex m_mutex;
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/

#endif /* GUCEF_CORE_CPUMPEDOBSERVER_H  ? */
