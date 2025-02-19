/*
 *  pubsubpluginREDISCLUSTER: Generic GUCEF COMCORE plugin for providing pubsub via Redis
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

#ifndef PUBSUBPLUGIN_REDISCLUSTER_CREDISCLUSTERPUBSUBCLIENTTOPIC_H
#define PUBSUBPLUGIN_REDISCLUSTER_CREDISCLUSTERPUBSUBCLIENTTOPIC_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_CORE_CTIMER_H
#include "CTimer.h"
#define GUCEF_CORE_CTIMER_H
#endif /* GUCEF_CORE_CTIMER_H ? */

#ifndef GUCEF_COMCORE_CHOSTADDRESS_H
#include "CHostAddress.h"
#define GUCEF_COMCORE_CHOSTADDRESS_H
#endif /* GUCEF_COMCORE_CHOSTADDRESS_H ? */

#ifndef GUCEF_COMCORE_CPUBSUBCLIENTTOPIC_H
#include "gucefCOMCORE_CPubSubClientTopic.h"
#define GUCEF_COMCORE_CPUBSUBCLIENTTOPIC_H
#endif /* GUCEF_COMCORE_CPUBSUBCLIENTTOPIC_H ? */

#include "hiredis.h"
#include "async.h"
#include "redis++.h"

#ifndef PUBSUBPLUGIN_REDISCLUSTER_CREDISCLUSTERPUBSUBCLIENTTOPICCONFIG_H
#include "pubsubpluginREDISCLUSTER_CRedisClusterPubSubClientTopicConfig.h"
#define PUBSUBPLUGIN_REDISCLUSTER_CREDISCLUSTERPUBSUBCLIENTTOPICCONFIG_H
#endif /* PUBSUBPLUGIN_REDISCLUSTER_CREDISCLUSTERPUBSUBCLIENTTOPICCONFIG_H ? */

#ifndef PUBSUBPLUGIN_REDISCLUSTER_CREDISCLUSTERPUBSUBCLIENTTOPICREADER_H
#include "pubsubpluginREDISCLUSTER_CRedisClusterPubSubClientTopicReader.h"
#define PUBSUBPLUGIN_REDISCLUSTER_CREDISCLUSTERPUBSUBCLIENTTOPICREADER_H
#endif /* PUBSUBPLUGIN_REDISCLUSTER_CREDISCLUSTERPUBSUBCLIENTTOPICREADER_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace PUBSUBPLUGIN {
namespace REDISCLUSTER {

/*-------------------------------------------------------------------------//
//                                                                         //
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

class CRedisClusterPubSubClient;

/**
 *  Clustered Redis implementation of the conceptual pub-sub "topic"
 *  For Redis we use streams to implement the topic concept
 */
class PUBSUBPLUGIN_REDISCLUSTER_PLUGIN_PRIVATE_CPP CRedisClusterPubSubClientTopic : public COMCORE::CPubSubClientTopic
{
    public:

    typedef std::vector< std::pair< sw::redis::StringView, sw::redis::StringView > > TRedisArgs;

    CRedisClusterPubSubClientTopic( CRedisClusterPubSubClient* client );

    virtual ~CRedisClusterPubSubClientTopic() GUCEF_VIRTUAL_OVERRIDE;

    virtual bool InitializeConnectivity( void ) GUCEF_VIRTUAL_OVERRIDE;

    virtual bool Disconnect( void ) GUCEF_VIRTUAL_OVERRIDE;

    virtual bool IsConnected( void ) GUCEF_VIRTUAL_OVERRIDE;

    virtual bool IsPublishingSupported( void ) GUCEF_VIRTUAL_OVERRIDE;

    virtual bool IsSubscribingSupported( void ) GUCEF_VIRTUAL_OVERRIDE;

    virtual bool Subscribe( void ) GUCEF_VIRTUAL_OVERRIDE;
    
    virtual bool SubscribeStartingAtMsgId( const CORE::CVariant& msgIdBookmark ) GUCEF_VIRTUAL_OVERRIDE;

    virtual bool SubscribeStartingAtMsgDateTime( const CORE::CDateTime& msgDtBookmark ) GUCEF_VIRTUAL_OVERRIDE;

    virtual const CORE::CString& GetTopicName( void ) const GUCEF_VIRTUAL_OVERRIDE;

    virtual bool Publish( const COMCORE::CIPubSubMsg& msg ) GUCEF_VIRTUAL_OVERRIDE;

    virtual bool SaveConfig( COMCORE::CPubSubClientTopicConfig& config ) const;

    virtual bool LoadConfig( const COMCORE::CPubSubClientTopicConfig& config );

    bool RedisSendSyncImpl( const sw::redis::StringView& msgId, const TRedisArgs& kvPairs );

    bool RedisRead( void );

    CORE::UInt32 CalculateRedisHashSlot( const CORE::CString& keyStr ) const;

    void
    OnMetricsTimerCycle( CORE::CNotifier* notifier    ,
                         const CORE::CEvent& eventId  ,
                         CORE::CICloneable* eventData );

    void
    OnRedisReconnectTimerCycle( CORE::CNotifier* notifier    ,
                                const CORE::CEvent& eventId  ,
                                CORE::CICloneable* eventData );
    
    virtual const MT::CILockable* AsLockable( void ) const GUCEF_VIRTUAL_OVERRIDE;

    protected:

    virtual bool Lock( CORE::UInt32 lockWaitTimeoutInMs = GUCEF_MT_DEFAULT_LOCK_TIMEOUT_IN_MS ) const GUCEF_VIRTUAL_OVERRIDE;

    virtual bool Unlock( void ) const GUCEF_VIRTUAL_OVERRIDE;

    private:

    void RegisterEventHandlers( void );

    void PrepStorageForReadMsgs( CORE::UInt32 msgCount );

    bool SubscribeImpl( const std::string& readOffset );

    private:

    typedef CORE::CTEventHandlerFunctor< CRedisClusterPubSubClientTopic > TEventCallback;
    
    // Types to read from redis-plus-plus
    typedef std::pair< std::string, std::string > TRedisMsgAttribute;
    typedef std::vector< TRedisMsgAttribute > TRedisMsgAttributes;
    typedef std::pair< std::string, TRedisMsgAttributes > TRedisMsg;
    typedef std::vector< TRedisMsg > TRedisMsgVector;
    typedef std::unordered_map< std::string, TRedisMsgVector > TRedisMsgByStream;
    typedef std::insert_iterator< TRedisMsgByStream > TRedisMsgByStreamInserter;

    // Types to implement/hook-up topic interface
    typedef std::vector< COMCORE::CBasicPubSubMsg > TPubSubMsgsVector;
    typedef std::pair< CORE::CDynamicBuffer, CORE::CDynamicBuffer > TBufferPair;
    typedef std::vector< TBufferPair > TBufferVector;

    CRedisClusterPubSubClient* m_client;
    sw::redis::Pipeline* m_redisPipeline;
    sw::redis::RedisCluster* m_redisContext;
    CORE::UInt32 m_redisErrorReplies;
    CORE::UInt32 m_redisTransmitQueueSize;
    CORE::UInt32 m_redisMsgsTransmitted;
    CORE::UInt32 m_redisFieldsInMsgsTransmitted;
    CORE::UInt32 m_redisFieldsInMsgsRatio;
    CORE::UInt32 m_redisHashSlot;
    CORE::UInt32 m_redisXreadCount;
    CORE::UInt32 m_redisXreadBlockTimeoutInMs;
    TRedisMsgByStream m_redisReadMsgs;
    TPubSubMsgsVector m_pubsubMsgs;
    TMsgsRecievedEventData m_pubsubMsgsRefs;
    TBufferVector m_pubsubMsgAttribs;
    TRedisArgs m_redisMsgArgs;
    COMCORE::CHostAddress m_redisShardHost;
    CORE::CString m_redisShardNodeId;
    CORE::CTimer* m_redisReconnectTimer;
    CRedisClusterPubSubClientTopicConfig m_config;
    std::string m_readOffset;    
    RedisClusterPubSubClientTopicReaderPtr m_readerThread;
    MT::CMutex m_lock;
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace REDISCLUSTER */
}; /* namespace PUBSUBPLUGIN */
}; /* namespace GUCEF */

/*--------------------------------------------------------------------------*/

#endif /* PUBSUBPLUGIN_REDISCLUSTER_CREDISCLUSTERPUBSUBCLIENTTOPIC_H ? */
