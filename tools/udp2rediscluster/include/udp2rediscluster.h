/*
 *  Udp2RedisCluster: service which pushes UDP packets into Redis streams
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

#include <deque>

#ifndef GUCEF_MT_CTMAILBOX_H
#include "gucefMT_CTMailBox.h"
#define GUCEF_MT_CTMAILBOX_H
#endif /* GUCEF_MT_CTMAILBOX_H ? */

#ifndef GUCEF_CORE_CITASKCONSUMER_H
#include "gucefCORE_CITaskConsumer.h"
#define GUCEF_CORE_CITASKCONSUMER_H
#endif /* GUCEF_CORE_CITASKCONSUMER_H ? */

#ifndef GUCEF_COMCORE_CUDPSOCKET_H
#include "CUDPSocket.h"
#define GUCEF_COMCORE_CUDPSOCKET_H
#endif /* GUCEF_COMCORE_CUDPSOCKET_H ? */

#ifndef GUCEF_COMCORE_CHOSTADDRESS_H
#include "CHostAddress.h"
#define GUCEF_COMCORE_CHOSTADDRESS_H
#endif /* GUCEF_COMCORE_CHOSTADDRESS_H ? */

#ifndef GUCEF_CORE_CICONFIGURABLE_H
#include "CIConfigurable.h"
#define GUCEF_CORE_CICONFIGURABLE_H
#endif /* GUCEF_CORE_CICONFIGURABLE_H ? */

#ifndef GUCEF_CORE_CVALUELIST_H
#include "CValueList.h"
#define GUCEF_CORE_CVALUELIST_H
#endif /* GUCEF_CORE_CVALUELIST_H ? */

#ifndef GUCEF_CORE_CDATANODE_H
#include "CDataNode.h"
#define GUCEF_CORE_CDATANODE_H
#endif /* GUCEF_CORE_CDATANODE_H ? */

#ifndef GUCEF_CORE_CTIMER_H
#include "CTimer.h"
#define GUCEF_CORE_CTIMER_H
#endif /* GUCEF_CORE_CTIMER_H ? */

#ifndef GUCEF_COM_CHTTPSERVER_H
#include "gucefCOM_CHTTPServer.h"
#define GUCEF_COM_CHTTPSERVER_H
#endif /* GUCEF_COM_CHTTPSERVER_H ? */

#ifndef GUCEF_COM_CDEFAULTHTTPSERVERROUTER_H
#include "gucefCOM_CDefaultHTTPServerRouter.h"
#define GUCEF_COM_CDEFAULTHTTPSERVERROUTER_H
#endif /* GUCEF_COM_CDEFAULTHTTPSERVERROUTER_H ? */

#ifndef GUCEF_COM_CCODECBASEDHTTPSERVERRESOURCE_H
#include "gucefCOM_CCodecBasedHTTPServerResource.h"
#define GUCEF_COM_CCODECBASEDHTTPSERVERRESOURCE_H
#endif /* GUCEF_COM_CCODECBASEDHTTPSERVERRESOURCE_H ? */

#ifndef GUCEF_COM_CTCONFIGURABLEMAPHTTPSERVERRESOURCE_H
#include "gucefCOM_CTConfigurableMapHttpServerResource.h"
#define GUCEF_COM_CTCONFIGURABLEMAPHTTPSERVERRESOURCE_H
#endif /* GUCEF_COM_CTCONFIGURABLEMAPHTTPSERVERRESOURCE_H ? */

#include "hiredis.h"
#include "async.h"

#include "redis++.h"

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

using namespace GUCEF;

/*-------------------------------------------------------------------------//
//                                                                         //
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

class ChannelSettings : public CORE::CIConfigurable
{
    public:

    typedef std::vector< COMCORE::CHostAddress > HostAddressVector;

    ChannelSettings( void );
    ChannelSettings( const ChannelSettings& src );
    ChannelSettings& operator=( const ChannelSettings& src );

    CORE::Int32 channelId;
    COMCORE::CHostAddress redisAddress;
    CORE::CString channelStreamName;
    COMCORE::CHostAddress udpInterface;
    HostAddressVector udpMulticastToJoin;
    bool collectMetrics;
    bool wantsTestPackage;
    CORE::UInt32 ticketRefillOnBusyCycle;
    CORE::UInt32 nrOfUdpReceiveBuffersPerSocket;
    CORE::UInt32 udpSocketOsReceiveBufferSize;
    CORE::UInt32 udpSocketUpdateCyclesPerPulse;
    bool performRedisWritesInDedicatedThread;
    CORE::Int32 maxSizeOfDedicatedRedisWriterBulkMailRead;
    bool applyThreadCpuAffinity;
    CORE::UInt32 cpuAffinityForDedicatedRedisWriterThread;
    CORE::UInt32 cpuAffinityForMainChannelThread;
    CORE::Int32 redisXAddMaxLen;
    bool redisXAddMaxLenIsApproximate;
    CORE::UInt32 redisReconnectDelayInMs;

    virtual bool SaveConfig( CORE::CDataNode& tree ) const GUCEF_VIRTUAL_OVERRIDE;

    virtual bool LoadConfig( const CORE::CDataNode& tree ) GUCEF_VIRTUAL_OVERRIDE;

    virtual const CORE::CString& GetClassTypeName( void ) const GUCEF_VIRTUAL_OVERRIDE;
};

/*-------------------------------------------------------------------------*/

class RedisNode
{
    public:

    COMCORE::CHostAddress host;
    CORE::CString nodeId;
    CORE::UInt32 startSlot;
    CORE::UInt32 endSlot;

    RedisNode( void );
};

typedef std::map< CORE::UInt32, RedisNode > RedisNodeMap;

/*-------------------------------------------------------------------------*/

class ClusterChannelRedisWriter : public CORE::CTaskConsumer
{
    public:

    typedef CORE::CTEventHandlerFunctor< ClusterChannelRedisWriter > TEventCallback;
    typedef COMCORE::CUDPSocket::TPacketEntryVector TPacketEntryVector;
    typedef std::vector< const TPacketEntryVector* >  TPacketEntryVectorPtrVector;
    typedef std::vector< CORE::UInt32 >             TUInt32Vector;
    typedef COMCORE::CUDPSocket::TPacketEntry TPacketEntry;

    ClusterChannelRedisWriter();
    virtual ~ClusterChannelRedisWriter();

    virtual bool OnTaskStart( CORE::CICloneable* taskData ) GUCEF_VIRTUAL_OVERRIDE;

    virtual bool OnTaskCycle( CORE::CICloneable* taskData ) GUCEF_VIRTUAL_OVERRIDE;

    virtual void OnTaskEnding( CORE::CICloneable* taskdata ,
                               bool willBeForced           ) GUCEF_VIRTUAL_OVERRIDE;

    virtual void OnTaskEnded( CORE::CICloneable* taskdata ,
                               bool wasForced             ) GUCEF_VIRTUAL_OVERRIDE;

    virtual CORE::CString GetType( void ) const GUCEF_VIRTUAL_OVERRIDE;

    bool RedisSendASync( const TPacketEntryVector& udpPackets, CORE::UInt32 packetCount );

    bool RedisSendSync( const TPacketEntryVector& udpPackets, CORE::UInt32 packetCount );

    bool RedisSendSync( const TPacketEntryVectorPtrVector& udpPackets, const TUInt32Vector& packetCounts );

    CORE::UInt32 GetRedisErrorRepliesCounter( bool resetCounter );

    CORE::UInt32 GetRedisMsgsTransmittedCounter( bool resetCounter );

    CORE::UInt32 GetRedisPacketsInMsgsTransmittedCounter( bool resetCounter );

    CORE::UInt32 GetRedisPacketsInMsgsRatio( void ) const;

    CORE::UInt32 GetRedisTransmitQueueSize( void ) const;

    CORE::UInt32 GetCurrentRedisHashSlot( void ) const;

    CORE::UInt32 CalculateRedisHashSlot( const CORE::CString& keyStr ) const;

    bool LoadConfig( const ChannelSettings& channelSettings );

    const ChannelSettings& GetChannelSettings( void ) const;

    private:

    bool RedisSendSyncImpl( const TPacketEntryVectorPtrVector& udpPackets, const TUInt32Vector& packetCounts );

    bool AddToOverflowQueue( const TPacketEntryVectorPtrVector& udpPackets, const TUInt32Vector& packetCounts );

    bool SendQueuedPackagesIfAny( void );

    bool RedisConnect( void );

    bool RedisDisconnect( void );

    bool GetRedisClusterNodeMap( RedisNodeMap& nodeMap );

    void RegisterEventHandlers( void );

    void
    OnMetricsTimerCycle( CORE::CNotifier* notifier    ,
                         const CORE::CEvent& eventId  ,
                         CORE::CICloneable* eventData );

    void
    OnRedisReconnectTimerCycle( CORE::CNotifier* notifier    ,
                                const CORE::CEvent& eventId  ,
                                CORE::CICloneable* eventData );

    private:

    ClusterChannelRedisWriter( const ClusterChannelRedisWriter& src ); // not implemented

    typedef std::deque< TPacketEntry > TPacketEntryQueue;
    typedef CORE::CTCloneableExpansion< TPacketEntryVector > TCloneablePacketEntryVector;
    typedef std::vector< std::pair< sw::redis::StringView, sw::redis::StringView > > TRedisArgs;
    typedef MT::CTMailBox< CORE::UInt32 > TBufferMailbox;

    sw::redis::RedisCluster* m_redisContext;
    sw::redis::Pipeline* m_redisPipeline;
    TPacketEntryVectorPtrVector m_redisMsgQueueOverflowQueue;
    TUInt32Vector m_redisMsgQueueOverflowQueueCounts;
    CORE::UInt32 m_redisErrorReplies;
    CORE::UInt32 m_redisTransmitQueueSize;
    CORE::UInt32 m_redisMsgsTransmitted;
    CORE::UInt32 m_redisPacketsInMsgsTransmitted;
    CORE::UInt32 m_redisPacketsInMsgsRatio;
    CORE::UInt32 m_redisHashSlot;
    COMCORE::CHostAddress m_redisShardHost;
    CORE::CString m_redisShardNodeId;
    ChannelSettings m_channelSettings;
    TBufferMailbox m_mailbox;
    TBufferMailbox::TMailList m_bulkMail;
    TPacketEntryVectorPtrVector m_bulkPackets;
    TUInt32Vector m_bulkPacketCounts;
    TRedisArgs m_redisPacketArgs;
    CORE::CTimer* m_metricsTimer;
    CORE::CTimer* m_redisReconnectTimer;
};

/*-------------------------------------------------------------------------*/

typedef CORE::CTSharedPtr< ClusterChannelRedisWriter, MT::CMutex > ClusterChannelRedisWriterPtr;

/*-------------------------------------------------------------------------*/

class Udp2RedisClusterChannel : public CORE::CTaskConsumer
{
    public:

    typedef CORE::CTEventHandlerFunctor< Udp2RedisClusterChannel > TEventCallback;

    Udp2RedisClusterChannel();
    Udp2RedisClusterChannel( const Udp2RedisClusterChannel& src );
    virtual ~Udp2RedisClusterChannel();

    virtual bool OnTaskStart( CORE::CICloneable* taskData ) GUCEF_VIRTUAL_OVERRIDE;

    virtual bool OnTaskCycle( CORE::CICloneable* taskData ) GUCEF_VIRTUAL_OVERRIDE;

    virtual void OnTaskEnding( CORE::CICloneable* taskdata ,
                               bool willBeForced           ) GUCEF_VIRTUAL_OVERRIDE;

    virtual void OnTaskEnded( CORE::CICloneable* taskdata ,
                              bool wasForced              ) GUCEF_VIRTUAL_OVERRIDE;

    virtual CORE::CString GetType( void ) const GUCEF_VIRTUAL_OVERRIDE;

    virtual bool WaitForTaskToFinish( CORE::Int32 timeoutInMs ) GUCEF_VIRTUAL_OVERRIDE;

    bool LoadConfig( const ChannelSettings& channelSettings );

    const ChannelSettings& GetChannelSettings( void ) const;

    class ChannelMetrics
    {
        public:

        ChannelMetrics( void );

        CORE::UInt32 udpBytesReceived;
        CORE::UInt32 udpPacketsReceived;
        CORE::UInt32 redisMessagesTransmitted;
        CORE::UInt32 redisPacketsInMsgsTransmitted;
        CORE::UInt32 redisPacketsInMsgsRatio;
        CORE::UInt32 redisTransmitQueueSize;
        CORE::UInt32 redisErrorReplies;
    };

    const ChannelMetrics& GetMetrics( void ) const;

    private:

    void
    OnUDPSocketError( CORE::CNotifier* notifier   ,
                      const CORE::CEvent& eventID ,
                      CORE::CICloneable* evenData );

    void
    OnUDPSocketClosed( CORE::CNotifier* notifier   ,
                       const CORE::CEvent& eventID ,
                       CORE::CICloneable* evenData );

    void
    OnUDPSocketClosing( CORE::CNotifier* notifier   ,
                        const CORE::CEvent& eventID ,
                        CORE::CICloneable* evenData );

    void
    OnUDPSocketOpened( CORE::CNotifier* notifier   ,
                       const CORE::CEvent& eventID ,
                       CORE::CICloneable* evenData );

    void
    OnUDPPacketsRecieved( CORE::CNotifier* notifier   ,
                          const CORE::CEvent& eventID ,
                          CORE::CICloneable* evenData );

    void
    OnMetricsTimerCycle( CORE::CNotifier* notifier    ,
                         const CORE::CEvent& eventId  ,
                         CORE::CICloneable* eventData );

    private:

    typedef COMCORE::CUDPSocket::TPacketEntryVector TPacketEntryVector;
    typedef COMCORE::CUDPSocket::TPacketEntry TPacketEntry;

    void RegisterEventHandlers( void );

    private:

    ChannelSettings m_channelSettings;
    GUCEF::COMCORE::CUDPSocket* m_udpSocket;
    CORE::CTimer* m_metricsTimer;
    ChannelMetrics m_metrics;
    ClusterChannelRedisWriterPtr m_redisWriter;
};

/*-------------------------------------------------------------------------*/

typedef CORE::CTSharedPtr< Udp2RedisClusterChannel, MT::CMutex > Udp2RedisClusterChannelPtr;

/*-------------------------------------------------------------------------*/

class Udp2RedisCluster;

class RestApiUdp2RedisInfoResource : public COM::CCodecBasedHTTPServerResource
{
    public:

    RestApiUdp2RedisInfoResource( Udp2RedisCluster* app );

    virtual ~RestApiUdp2RedisInfoResource();

    virtual bool Serialize( CORE::CDataNode& output             ,
                            const CORE::CString& representation ,
                            const CORE::CString& params         ) GUCEF_VIRTUAL_OVERRIDE;

    private:

    Udp2RedisCluster* m_app;
};

/*-------------------------------------------------------------------------*/

class RestApiUdp2RedisConfigResource : public COM::CCodecBasedHTTPServerResource
{
    public:

    RestApiUdp2RedisConfigResource( Udp2RedisCluster* app, bool appConfig );

    virtual ~RestApiUdp2RedisConfigResource();

    virtual bool Serialize( CORE::CDataNode& output             ,
                            const CORE::CString& representation ,
                            const CORE::CString& params         ) GUCEF_VIRTUAL_OVERRIDE;

    virtual TDeserializeState Deserialize( const CORE::CDataNode& input        ,
                                           const CORE::CString& representation ,
                                           bool isDeltaUpdateOnly              ) GUCEF_VIRTUAL_OVERRIDE;

    private:

    Udp2RedisCluster* m_app;
    bool m_appConfig;
};

/*-------------------------------------------------------------------------*/

//COM::CTConfigurableMapHttpServerResource<

/*-------------------------------------------------------------------------*/

class Udp2RedisCluster : public CORE::CObserver
{
    public:

    Udp2RedisCluster( void );
    virtual ~Udp2RedisCluster();

    bool Start( void );

    bool SetStandbyMode( bool newMode );

    bool IsGlobalStandbyEnabled( void ) const;

    bool LoadConfig( const CORE::CValueList& appConfig   ,
                     const CORE::CDataNode& globalConfig );

    const CORE::CValueList& GetAppConfig( void ) const;

    const CORE::CDataNode& GetGlobalConfig( void ) const;

    private:

    typedef CORE::CTEventHandlerFunctor< Udp2RedisCluster > TEventCallback;

    void
    OnMetricsTimerCycle( CORE::CNotifier* notifier    ,
                         const CORE::CEvent& eventId  ,
                         CORE::CICloneable* eventData );

    void
    OnTransmitTestPacketTimerCycle( CORE::CNotifier* notifier    ,
                                    const CORE::CEvent& eventId  ,
                                    CORE::CICloneable* eventData );

    private:

    typedef std::map< CORE::Int32, ChannelSettings > ChannelSettingsMap;
    typedef std::map< CORE::Int32, Udp2RedisClusterChannelPtr > Udp2RedisClusterChannelMap;

    bool m_isInStandby;
    bool m_globalStandbyEnabled;
    bool m_autoChannelNumbering;
    CORE::UInt16 m_udpStartPort;
    CORE::UInt16 m_channelCount;
    CORE::Int32 m_redisStreamStartChannelID;
    CORE::CString m_redisStreamName;
    CORE::CString m_redisHost;
    CORE::UInt16 m_redisPort;
    Udp2RedisClusterChannelMap m_channels;
    ChannelSettingsMap m_channelSettings;
    COM::CHTTPServer m_httpServer;
    COM::CDefaultHTTPServerRouter m_httpRouter;
    CORE::CValueList m_appConfig;
    CORE::CDataNode m_globalConfig;
    CORE::CTimer m_metricsTimer;
    bool m_transmitMetrics;
    COMCORE::CUDPSocket m_testUdpSocket;
    CORE::CTimer m_testPacketTransmitTimer;
    bool m_transmitTestPackets;
};

/*-------------------------------------------------------------------------*/
