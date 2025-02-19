#-------------------------------------------------------------------
# This file has been automatically generated by ProjectGenerator    
# which is part of a build system designed for GUCEF                
#     (Galaxy Unlimited Framework)                                  
# For the latest info, see http://www.VanvelzenSoftware.com/        
#                                                                   
# The contents of this file are placed in the public domain. Feel   
# free to make use of it in any way you like.                       
#-------------------------------------------------------------------


ifndef MY_MODULE_PATH
  MY_MODULE_PATH := $(call my-dir)
endif
LOCAL_PATH := $(MY_MODULE_PATH)

include $(CLEAR_VARS)

@echo Module path: $(MY_MODULE_PATH)
LOCAL_MODULE := aws-cpp-sdk-core
LOCAL_MODULE_FILENAME := libaws-cpp-sdk-core
@echo Module name: $(LOCAL_MODULE)

LOCAL_SRC_FILES := \
  source/AmazonSerializableWebServiceRequest.cpp \
  source/AmazonStreamingWebServiceRequest.cpp \
  source/AmazonWebServiceRequest.cpp \
  source/Aws.cpp \
  source/Globals.cpp \
  source/Version.cpp \
  source/auth/AWSAuthSigner.cpp \
  source/auth/AWSAuthSignerProvider.cpp \
  source/auth/AWSCredentialsProvider.cpp \
  source/auth/AWSCredentialsProviderChain.cpp \
  source/auth/STSCredentialsProvider.cpp \
  source/client/AWSClient.cpp \
  source/client/AWSErrorMarshaller.cpp \
  source/client/AsyncCallerContext.cpp \
  source/client/ClientConfiguration.cpp \
  source/client/CoreErrors.cpp \
  source/client/DefaultRetryStrategy.cpp \
  source/client/SpecifiedRetryableErrorsRetryStrategy.cpp \
  source/config/AWSProfileConfigLoader.cpp \
  source/external/cjson/cJSON.cpp \
  source/external/tinyxml2/tinyxml2.cpp \
  source/http/HttpClient.cpp \
  source/http/HttpClientFactory.cpp \
  source/http/HttpRequest.cpp \
  source/http/HttpTypes.cpp \
  source/http/Scheme.cpp \
  source/http/URI.cpp \
  source/http/curl/CurlHandleContainer.cpp \
  source/http/curl/CurlHttpClient.cpp \
  source/http/standard/StandardHttpRequest.cpp \
  source/http/standard/StandardHttpResponse.cpp \
  source/internal/AWSHttpResourceClient.cpp \
  source/monitoring/DefaultMonitoring.cpp \
  source/monitoring/HttpClientMetrics.cpp \
  source/monitoring/MonitoringManager.cpp \
  source/platform/android/Environment.cpp \
  source/platform/android/FileSystem.cpp \
  source/platform/android/LogcatLogSystem.cpp \
  source/platform/android/OSVersionInfo.cpp \
  source/platform/android/Platform.cpp \
  source/platform/android/Security.cpp \
  source/platform/android/Time.cpp \
  source/utils/ARN.cpp \
  source/utils/Array.cpp \
  source/utils/DNS.cpp \
  source/utils/DateTimeCommon.cpp \
  source/utils/Directory.cpp \
  source/utils/EnumParseOverflowContainer.cpp \
  source/utils/FileSystemUtils.cpp \
  source/utils/GetTheLights.cpp \
  source/utils/HashingUtils.cpp \
  source/utils/StringUtils.cpp \
  source/utils/TempFile.cpp \
  source/utils/UUID.cpp \
  source/utils/base64/Base64.cpp \
  source/utils/crypto/Cipher.cpp \
  source/utils/crypto/ContentCryptoMaterial.cpp \
  source/utils/crypto/ContentCryptoScheme.cpp \
  source/utils/crypto/CryptoBuf.cpp \
  source/utils/crypto/CryptoStream.cpp \
  source/utils/crypto/EncryptionMaterials.cpp \
  source/utils/crypto/KeyWrapAlgorithm.cpp \
  source/utils/crypto/MD5.cpp \
  source/utils/crypto/Sha256.cpp \
  source/utils/crypto/Sha256HMAC.cpp \
  source/utils/crypto/factory/Factories.cpp \
  source/utils/event/EventDecoderStream.cpp \
  source/utils/event/EventEncoderStream.cpp \
  source/utils/event/EventHeader.cpp \
  source/utils/event/EventMessage.cpp \
  source/utils/event/EventStreamBuf.cpp \
  source/utils/event/EventStreamDecoder.cpp \
  source/utils/event/EventStreamEncoder.cpp \
  source/utils/event/EventStreamErrors.cpp \
  source/utils/json/JsonSerializer.cpp \
  source/utils/logging/AWSLogging.cpp \
  source/utils/logging/ConsoleLogSystem.cpp \
  source/utils/logging/DefaultLogSystem.cpp \
  source/utils/logging/FormattedLogSystem.cpp \
  source/utils/logging/LogLevel.cpp \
  source/utils/memory/AWSMemory.cpp \
  source/utils/memory/stl/SimpleStringStream.cpp \
  source/utils/stream/ConcurrentStreamBuf.cpp \
  source/utils/stream/PreallocatedStreamBuf.cpp \
  source/utils/stream/ResponseStream.cpp \
  source/utils/stream/SimpleStreamBuf.cpp \
  source/utils/threading/Executor.cpp \
  source/utils/threading/ReaderWriterLock.cpp \
  source/utils/threading/Semaphore.cpp \
  source/utils/threading/ThreadTask.cpp \
  source/utils/xml/XmlSerializer.cpp

LOCAL_C_INCLUDES := \
  $(MY_MODULE_PATH)/include/aws/core \
  $(MY_MODULE_PATH)/include/aws/core/auth \
  $(MY_MODULE_PATH)/include/aws/core/client \
  $(MY_MODULE_PATH)/include/aws/core/config \
  $(MY_MODULE_PATH)/include/aws/core/external/cjson \
  $(MY_MODULE_PATH)/include/aws/core/external/tinyxml2 \
  $(MY_MODULE_PATH)/include/aws/core/http \
  $(MY_MODULE_PATH)/include/aws/core/http/curl \
  $(MY_MODULE_PATH)/include/aws/core/http/standard \
  $(MY_MODULE_PATH)/include/aws/core/internal \
  $(MY_MODULE_PATH)/include/aws/core/monitoring \
  $(MY_MODULE_PATH)/include/aws/core/net \
  $(MY_MODULE_PATH)/include/aws/core/platform \
  $(MY_MODULE_PATH)/include/aws/core/platform/refs \
  $(MY_MODULE_PATH)/include/aws/core/utils \
  $(MY_MODULE_PATH)/include/aws/core/utils/base64 \
  $(MY_MODULE_PATH)/include/aws/core/utils/crypto \
  $(MY_MODULE_PATH)/include/aws/core/utils/crypto/bcrypt \
  $(MY_MODULE_PATH)/include/aws/core/utils/crypto/commoncrypto \
  $(MY_MODULE_PATH)/include/aws/core/utils/crypto/openssl \
  $(MY_MODULE_PATH)/include/aws/core/utils/event \
  $(MY_MODULE_PATH)/include/aws/core/utils/json \
  $(MY_MODULE_PATH)/include/aws/core/utils/logging \
  $(MY_MODULE_PATH)/include/aws/core/utils/logging/android \
  $(MY_MODULE_PATH)/include/aws/core/utils/memory \
  $(MY_MODULE_PATH)/include/aws/core/utils/memory/stl \
  $(MY_MODULE_PATH)/include/aws/core/utils/ratelimiter \
  $(MY_MODULE_PATH)/include/aws/core/utils/stream \
  $(MY_MODULE_PATH)/include/aws/core/utils/threading \
  $(MY_MODULE_PATH)/include/aws/core/utils/xml \
  $(MY_MODULE_PATH)/../aws-c-common/include \
  $(MY_MODULE_PATH)/../aws-c-event-stream/include \
  $(MY_MODULE_PATH)/../aws-checksums/include \
  $(MY_MODULE_PATH)/../aws-checksums/include/aws \
  $(MY_MODULE_PATH)/../aws-checksums/include/aws/checksums \
  $(MY_MODULE_PATH)/../aws-checksums/include/aws/checksums/private \
  $(MY_MODULE_PATH)/../curl/include \
  $(MY_MODULE_PATH)/../curl/include/curl \
  $(MY_MODULE_PATH)/../curl/lib \
  $(MY_MODULE_PATH)/../curl/lib/vauth \
  $(MY_MODULE_PATH)/../curl/lib/vquic \
  $(MY_MODULE_PATH)/../curl/lib/vssh \
  $(MY_MODULE_PATH)/../curl/lib/vtls \
  $(MY_MODULE_PATH)/include \
  $(MY_MODULE_PATH)/include/aws \
  $(MY_MODULE_PATH)/include/aws/core/external

LOCAL_CFLAGS := -DAWS_CORE_EXPORTS=1 -DENABLE_OPENSSL_ENCRYPTION -DUSE_IMPORT_EXPORT=1


LOCAL_SHARED_LIBRARIES := \
  curl


LOCAL_STATIC_LIBRARIES := \
  aws-c-common \
  aws-c-event-stream \
  aws-checksums

include $(BUILD_SHARED_LIBRARY)

