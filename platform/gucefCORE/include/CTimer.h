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

#ifndef GUCEF_CORE_CTIMER_H
#define GUCEF_CORE_CTIMER_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_CORE_COBSERVINGNOTIFIER_H
#include "CObservingNotifier.h"
#define GUCEF_CORE_COBSERVINGNOTIFIER_H
#endif /* GUCEF_CORE_COBSERVINGNOTIFIER_H ? */

#ifndef GUCEF_CORE_CTEVENTHANDLERFUNCTOR_H
#include "gucefCORE_CTEventHandlerFunctor.h"
#define GUCEF_CORE_CTEVENTHANDLERFUNCTOR_H
#endif /* GUCEF_CORE_CTEVENTHANDLERFUNCTOR_H ? */

#ifndef GUCEF_CORE_CTCLONEABLEOBJ_H
#include "CTCloneableObj.h"
#define GUCEF_CORE_CTCLONEABLEOBJ_H
#endif /* GUCEF_CORE_CTCLONEABLEOBJ_H ? */

#ifndef GUCEF_CORE_CLONEABLES_H
#include "cloneables.h"
#define GUCEF_CORE_CLONEABLES_H
#endif /* GUCEF_CORE_CLONEABLES_H ? */

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

/**
 *  Timer implementation that attempts to provide a timing mechanism with a
 *  millisecond resolution.
 *
 *  Note that timer calls are performed in the thread triggering the timer's action.
 *  If you pass a pulse generator then its pulse thus its thread will run the timer actions
 *  Keep this in mind when hooking up lengthy actions to a timer.
 *
 *  Note that the timer resolution is NOT guaranteed. An attempt is made to
 *  provide the theoretical minimum resolution of 1 millisecond.
 */
class GUCEF_CORE_PUBLIC_CPP CTimer : public CObservingNotifier
{
    public:

    static const CEvent TimerStartedEvent;
    static const CEvent TimerUpdateEvent;
    static const CEvent TimerStoppedEvent;
    static const CEvent TimerIntervalChangedEvent;

    struct STimerUpdateData
    {
        UInt64 tickCount;
        Float64 updateDeltaInMilliSecs;
    };
    typedef struct STimerUpdateData TTimerUpdateData;
    typedef CTCloneableObj< TTimerUpdateData > TimerUpdateEventData;
    typedef TCloneableUInt32 TimerIntervalChangedEventData;

    static void RegisterEvents( void );

    public:

    CTimer( CPulseGenerator* pulseGenerator          ,
            const UInt32 updateDeltaInMilliSecs = 25 );

    CTimer( CPulseGenerator& pulseGenerator          ,
            const UInt32 updateDeltaInMilliSecs = 25 );

    CTimer( const UInt32 updateDeltaInMilliSecs = 25 );

    CTimer( const CTimer& src );

    ~CTimer();

    CTimer& operator=( const CTimer& src );

    void SetInterval( const UInt32 updateDeltaInMilliSecs );

    UInt32 GetInterval( void ) const;

    void SetEnabled( const bool enabled );

    bool GetEnabled( void ) const;

    /**
     *  Returns the tick count since the start of the timer.
     *
     *  Note that reseting the timer alters the timer count
     *  but not the run ticks since the timer didn't actually stop.
     */
    UInt64 GetRunTicks( void ) const;

    Float64 GetRunTimeInMilliSecs( void ) const;

    /**
     *  Returns the actual tick count of the timer.
     *
     *  Note that the tick count gets reset by either the start
     *  of a timer or trough the use of an explicit Reset() call.
     */
    UInt64 GetTickCount( void ) const;

    Float64 GetTimeInMilliSecs( void ) const;

	void Reset( void );

    /**
     *  Allows you to bypass the wait on the timer time-out and 
     *  trigger the timer event right away
     */
    void TriggerNow( void );

	const CString& GetClassTypeName( void ) const GUCEF_VIRTUAL_OVERRIDE;

	/**
	 *  Returns the approximated maximum timer resolution in milliseconds
	 *
	 *  Note that this is the theoretical maximum resolution of the timer in milliseconds
	 *  Application update delays and timer logic will increase the actual maximum resolution.
	 *
	 *  @return approximated maximum timer resolution in milliseconds
	 */
	static Float64 GetApproxMaxTimerResolutionInMilliSecs( void );

    protected:

    virtual bool Lock( UInt32 lockWaitTimeoutInMs = GUCEF_MT_DEFAULT_LOCK_TIMEOUT_IN_MS ) const GUCEF_VIRTUAL_OVERRIDE;

    virtual bool Unlock( void ) const GUCEF_VIRTUAL_OVERRIDE;

    private:
    typedef CTEventHandlerFunctor< CTimer > TEventCallback;

    void OnPulse( CNotifier* notifier           ,
                  const CEvent& eventid         ,
                  CICloneable* eventdata = NULL );

    void OnPulseGeneratorDestruction( CNotifier* notifier           ,
                                      const CEvent& eventid         ,
                                      CICloneable* eventdata = NULL );

    private:

    Float64 m_timerFreq;
    UInt64 m_lastTimerCycle;
    UInt64 m_tickCount;
    UInt32 m_updateDeltaInMilliSecs;
    UInt64 m_activationTickCount;
    bool m_enabled;
    CPulseGenerator* m_pulseGenerator;
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 03-03-2007 :
        - Dinand: Added this section.
        - Dinand: Converted class from callback interface based mechanics to
          notification

-----------------------------------------------------------------------------*/

#endif /* GUCEF_CORE_CTIMER_H  ? */
