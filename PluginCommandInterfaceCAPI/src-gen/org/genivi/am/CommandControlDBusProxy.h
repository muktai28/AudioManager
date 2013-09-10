/*
* This file was generated by the CommonAPI Generators.
*
 * Copyright (C) 2013, BMW AG
 *
 * \author Christian Linke, christian.linke@bmw.de BMW 2012,2013
*/
#ifndef ORG_GENIVI_AM_Command_Control_DBUS_PROXY_H_
#define ORG_GENIVI_AM_Command_Control_DBUS_PROXY_H_

#include <org/genivi/am/CommandControlProxyBase.h>

#define COMMONAPI_INTERNAL_COMPILATION

#include <CommonAPI/DBus/DBusFactory.h>
#include <CommonAPI/DBus/DBusProxy.h>
#include <CommonAPI/DBus/DBusEvent.h>

#undef COMMONAPI_INTERNAL_COMPILATION

#include <string>

namespace org {
namespace genivi {
namespace am {

class CommandControlDBusProxy: virtual public CommandControlProxyBase, virtual public CommonAPI::DBus::DBusProxy {
 public:
    CommandControlDBusProxy(
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyconnection);

    virtual ~CommandControlDBusProxy() { }


    virtual NewMainConnectionEvent& getNewMainConnectionEvent();
    virtual RemovedMainConnectionEvent& getRemovedMainConnectionEvent();
    virtual NewSinkEvent& getNewSinkEvent();
    virtual RemovedSinkEvent& getRemovedSinkEvent();
    virtual NewSourceEvent& getNewSourceEvent();
    virtual RemovedSourceEvent& getRemovedSourceEvent();
    virtual NumberOfSinkClassesChangedEvent& getNumberOfSinkClassesChangedEvent();
    virtual NumberOfSourceClassesChangedEvent& getNumberOfSourceClassesChangedEvent();
    virtual MainConnectionStateChangedEvent& getMainConnectionStateChangedEvent();
    virtual MainSinkSoundPropertyChangedEvent& getMainSinkSoundPropertyChangedEvent();
    virtual MainSourceSoundPropertyChangedEvent& getMainSourceSoundPropertyChangedEvent();
    virtual SinkAvailabilityChangedEvent& getSinkAvailabilityChangedEvent();
    virtual SourceAvailabilityChangedEvent& getSourceAvailabilityChangedEvent();
    virtual VolumeChangedEvent& getVolumeChangedEvent();
    virtual SinkMuteStateChangedEvent& getSinkMuteStateChangedEvent();
    virtual SystemPropertyChangedEvent& getSystemPropertyChangedEvent();
    virtual TimingInformationChangedEvent& getTimingInformationChangedEvent();
    virtual SinkUpdatedEvent& getSinkUpdatedEvent();
    virtual SourceUpdatedEvent& getSourceUpdatedEvent();
    virtual SinkNotificationEvent& getSinkNotificationEvent();
    virtual SourceNotificationEvent& getSourceNotificationEvent();
    virtual MainSinkNotificationConfigurationChangedEvent& getMainSinkNotificationConfigurationChangedEvent();
    virtual MainSourceNotificationConfigurationChangedEvent& getMainSourceNotificationConfigurationChangedEvent();


    virtual void connect(const am_sourceID_t& sourceID, const am_sinkID_t& sinkID, CommonAPI::CallStatus& callStatus, am_mainConnectionID_t& mainConnectionID, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> connectAsync(const am_sourceID_t& sourceID, const am_sinkID_t& sinkID, ConnectAsyncCallback callback);

    virtual void disconnect(const am_mainConnectionID_t& mainConnectionID, CommonAPI::CallStatus& callStatus, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> disconnectAsync(const am_mainConnectionID_t& mainConnectionID, DisconnectAsyncCallback callback);

    virtual void setVolume(const am_sinkID_t& sinkID, const am_mainVolume_t& volume, CommonAPI::CallStatus& callStatus, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> setVolumeAsync(const am_sinkID_t& sinkID, const am_mainVolume_t& volume, SetVolumeAsyncCallback callback);

    virtual void volumeStep(const am_sinkID_t& sinkID, const int16_t& volumeStep, CommonAPI::CallStatus& callStatus, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> volumeStepAsync(const am_sinkID_t& sinkID, const int16_t& volumeStep, VolumeStepAsyncCallback callback);

    virtual void setSinkMuteState(const am_sinkID_t& sinkID, const am_MuteState_e& muteState, CommonAPI::CallStatus& callStatus, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> setSinkMuteStateAsync(const am_sinkID_t& sinkID, const am_MuteState_e& muteState, SetSinkMuteStateAsyncCallback callback);

    virtual void setMainSinkSoundProperty(const am_sinkID_t& sinkID, const am_MainSoundProperty_s& soundProperty, CommonAPI::CallStatus& callStatus, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> setMainSinkSoundPropertyAsync(const am_sinkID_t& sinkID, const am_MainSoundProperty_s& soundProperty, SetMainSinkSoundPropertyAsyncCallback callback);

    virtual void setMainSourceSoundProperty(const am_sourceID_t& sourceID, const am_MainSoundProperty_s& soundProperty, CommonAPI::CallStatus& callStatus, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> setMainSourceSoundPropertyAsync(const am_sourceID_t& sourceID, const am_MainSoundProperty_s& soundProperty, SetMainSourceSoundPropertyAsyncCallback callback);

    virtual void setSystemProperty(const am_SystemProperty_s& property, CommonAPI::CallStatus& callStatus, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> setSystemPropertyAsync(const am_SystemProperty_s& property, SetSystemPropertyAsyncCallback callback);

    virtual void getListMainConnections(CommonAPI::CallStatus& callStatus, am_Error_e& error, am_MainConnection_L& listConnections);
    virtual std::future<CommonAPI::CallStatus> getListMainConnectionsAsync(GetListMainConnectionsAsyncCallback callback);

    virtual void getListMainSinks(CommonAPI::CallStatus& callStatus, am_SinkType_L& listMainSinks, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> getListMainSinksAsync(GetListMainSinksAsyncCallback callback);

    virtual void getListMainSources(CommonAPI::CallStatus& callStatus, am_SourceType_L& listMainSources, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> getListMainSourcesAsync(GetListMainSourcesAsyncCallback callback);

    virtual void getListMainSinkSoundProperties(const am_sinkID_t& sinkID, CommonAPI::CallStatus& callStatus, am_MainSoundProperty_L& listSoundProperties, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> getListMainSinkSoundPropertiesAsync(const am_sinkID_t& sinkID, GetListMainSinkSoundPropertiesAsyncCallback callback);

    virtual void getListMainSourceSoundProperties(const am_sourceID_t& sourceID, CommonAPI::CallStatus& callStatus, am_MainSoundProperty_L& listSourceProperties, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> getListMainSourceSoundPropertiesAsync(const am_sourceID_t& sourceID, GetListMainSourceSoundPropertiesAsyncCallback callback);

    virtual void getListSourceClasses(CommonAPI::CallStatus& callStatus, am_SourceClass_L& listSourceClasses, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> getListSourceClassesAsync(GetListSourceClassesAsyncCallback callback);

    virtual void getListSinkClasses(CommonAPI::CallStatus& callStatus, am_SinkClass_L& listSinkClasses, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> getListSinkClassesAsync(GetListSinkClassesAsyncCallback callback);

    virtual void getListSystemProperties(CommonAPI::CallStatus& callStatus, am_SystemProperty_L& listSystemProperties, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> getListSystemPropertiesAsync(GetListSystemPropertiesAsyncCallback callback);

    virtual void getTimingInformation(const am_mainConnectionID_t& mainConnectionID, CommonAPI::CallStatus& callStatus, am_timeSync_t& delay, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> getTimingInformationAsync(const am_mainConnectionID_t& mainConnectionID, GetTimingInformationAsyncCallback callback);

    virtual void getListMainSinkNotificationConfigurations(const am_sinkID_t& sinkID, CommonAPI::CallStatus& callStatus, am_NotificationConfiguration_L& listMainNotificationConfigurations, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> getListMainSinkNotificationConfigurationsAsync(const am_sinkID_t& sinkID, GetListMainSinkNotificationConfigurationsAsyncCallback callback);

    virtual void getListMainSourceNotificationConfigurations(const am_sourceID_t& sourceID, CommonAPI::CallStatus& callStatus, am_NotificationConfiguration_L& listMainNotificationConfigurations, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> getListMainSourceNotificationConfigurationsAsync(const am_sourceID_t& sourceID, GetListMainSourceNotificationConfigurationsAsyncCallback callback);

    virtual void setMainSinkNotificationConfiguration(const am_sinkID_t& sinkID, const am_NotificationConfiguration_s& mainNotificationConfiguration, CommonAPI::CallStatus& callStatus, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> setMainSinkNotificationConfigurationAsync(const am_sinkID_t& sinkID, const am_NotificationConfiguration_s& mainNotificationConfiguration, SetMainSinkNotificationConfigurationAsyncCallback callback);

    virtual void setMainSourceNotificationConfiguration(const am_sourceID_t& sourceID, const am_NotificationConfiguration_s& mainNotificationConfiguration, CommonAPI::CallStatus& callStatus, am_Error_e& error);
    virtual std::future<CommonAPI::CallStatus> setMainSourceNotificationConfigurationAsync(const am_sourceID_t& sourceID, const am_NotificationConfiguration_s& mainNotificationConfiguration, SetMainSourceNotificationConfigurationAsyncCallback callback);
    
    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

 private:

    CommonAPI::DBus::DBusEvent<NewMainConnectionEvent> newMainConnection_;
    CommonAPI::DBus::DBusEvent<RemovedMainConnectionEvent> removedMainConnection_;
    CommonAPI::DBus::DBusEvent<NewSinkEvent> newSink_;
    CommonAPI::DBus::DBusEvent<RemovedSinkEvent> removedSink_;
    CommonAPI::DBus::DBusEvent<NewSourceEvent> newSource_;
    CommonAPI::DBus::DBusEvent<RemovedSourceEvent> removedSource_;
    CommonAPI::DBus::DBusEvent<NumberOfSinkClassesChangedEvent> numberOfSinkClassesChanged_;
    CommonAPI::DBus::DBusEvent<NumberOfSourceClassesChangedEvent> numberOfSourceClassesChanged_;
    CommonAPI::DBus::DBusEvent<MainConnectionStateChangedEvent> mainConnectionStateChanged_;
    CommonAPI::DBus::DBusEvent<MainSinkSoundPropertyChangedEvent> mainSinkSoundPropertyChanged_;
    CommonAPI::DBus::DBusEvent<MainSourceSoundPropertyChangedEvent> mainSourceSoundPropertyChanged_;
    CommonAPI::DBus::DBusEvent<SinkAvailabilityChangedEvent> sinkAvailabilityChanged_;
    CommonAPI::DBus::DBusEvent<SourceAvailabilityChangedEvent> sourceAvailabilityChanged_;
    CommonAPI::DBus::DBusEvent<VolumeChangedEvent> volumeChanged_;
    CommonAPI::DBus::DBusEvent<SinkMuteStateChangedEvent> sinkMuteStateChanged_;
    CommonAPI::DBus::DBusEvent<SystemPropertyChangedEvent> systemPropertyChanged_;
    CommonAPI::DBus::DBusEvent<TimingInformationChangedEvent> timingInformationChanged_;
    CommonAPI::DBus::DBusEvent<SinkUpdatedEvent> sinkUpdated_;
    CommonAPI::DBus::DBusEvent<SourceUpdatedEvent> sourceUpdated_;
    CommonAPI::DBus::DBusEvent<SinkNotificationEvent> sinkNotification_;
    CommonAPI::DBus::DBusEvent<SourceNotificationEvent> sourceNotification_;
    CommonAPI::DBus::DBusEvent<MainSinkNotificationConfigurationChangedEvent> mainSinkNotificationConfigurationChanged_;
    CommonAPI::DBus::DBusEvent<MainSourceNotificationConfigurationChangedEvent> mainSourceNotificationConfigurationChanged_;
};

} // namespace am
} // namespace genivi
} // namespace org

#endif // ORG_GENIVI_AM_Command_Control_DBUS_PROXY_H_