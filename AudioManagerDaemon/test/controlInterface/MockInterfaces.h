/**
* Copyright (C) 2011, BMW AG
*
* GeniviAudioMananger AudioManagerDaemon
*
* \file MockInterfaces.h
*
* \date 20-Oct-2011 3:42:04 PM
* \author Christian Mueller (christian.ei.mueller@bmw.de)
*
* \section License
* GNU Lesser General Public License, version 2.1, with special exception (GENIVI clause)
* Copyright (C) 2011, BMW AG Christian Mueller  Christian.ei.mueller@bmw.de
*
* This program is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License, version 2.1, as published by the Free Software Foundation.
* This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License, version 2.1, for more details.
* You should have received a copy of the GNU Lesser General Public License, version 2.1, along with this program; if not, see <http://www.gnu.org/licenses/lgpl-2.1.html>.
* Note that the copyright holders assume that the GNU Lesser General Public License, version 2.1, may also be applicable to programs even in cases in which the program is not a library in the technical sense.
* Linking AudioManager statically or dynamically with other modules is making a combined work based on AudioManager. You may license such other modules under the GNU Lesser General Public License, version 2.1. If you do not want to license your linked modules under the GNU Lesser General Public License, version 2.1, you may use the program under the following exception.
* As a special exception, the copyright holders of AudioManager give you permission to combine AudioManager with software programs or libraries that are released under any license unless such a combination is not permitted by the license of such a software program or library. You may copy and distribute such a system following the terms of the GNU Lesser General Public License, version 2.1, including this special exception, for AudioManager and the licenses of the other code concerned.
* Note that people who make modified versions of AudioManager are not obligated to grant this special exception for their modified versions; it is their choice whether to do so. The GNU Lesser General Public License, version 2.1, gives permission to release a modified version without this exception; this exception also makes it possible to release a modified version which carries forward this exception.
*
*/

#ifndef MOCKROUTINGINTERFACE_H_
#define MOCKROUTINGINTERFACE_H_

#include <control/ControlSendInterface.h>
#include <routing/RoutingSendInterface.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace am {

class MockRoutingSendInterface : public RoutingSendInterface {
 public:
  MOCK_METHOD1(startupRoutingInterface,
      void(RoutingReceiveInterface* routingreceiveinterface));
  MOCK_METHOD0(routingInterfacesReady,
      void());
  MOCK_METHOD0(routingInterfacesRundown,
      void());
  MOCK_METHOD1(asyncAbort,
      am_Error_e(const am_Handle_s handle));
  MOCK_METHOD5(asyncConnect,
      am_Error_e(const am_Handle_s handle, const am_connectionID_t connectionID, const am_sourceID_t sourceID, const am_sinkID_t sinkID, const am_ConnectionFormat_e connectionFormat));
  MOCK_METHOD2(asyncDisconnect,
      am_Error_e(const am_Handle_s handle, const am_connectionID_t connectionID));
  MOCK_METHOD5(asyncSetSinkVolume,
      am_Error_e(const am_Handle_s handle, const am_sinkID_t sinkID, const am_volume_t volume, const am_RampType_e ramp, const am_time_t time));
  MOCK_METHOD5(asyncSetSourceVolume,
      am_Error_e(const am_Handle_s handle, const am_sourceID_t sourceID, const am_volume_t volume, const am_RampType_e ramp, const am_time_t time));
  MOCK_METHOD3(asyncSetSourceState,
      am_Error_e(const am_Handle_s handle, const am_sourceID_t sourceID, const am_SourceState_e state));
  MOCK_METHOD3(asyncSetSinkSoundProperties,
      am_Error_e(const am_Handle_s handle, const std::vector<am_SoundProperty_s>& listSoundProperties, const am_sinkID_t sinkID));
  MOCK_METHOD3(asyncSetSinkSoundProperty,
      am_Error_e(const am_Handle_s handle, const am_SoundProperty_s& soundProperty, const am_sinkID_t sinkID));
  MOCK_METHOD3(asyncSetSourceSoundProperties,
      am_Error_e(const am_Handle_s handle, const std::vector<am_SoundProperty_s>& listSoundProperties, const am_sourceID_t sourceID));
  MOCK_METHOD3(asyncSetSourceSoundProperty,
      am_Error_e(const am_Handle_s handle, const am_SoundProperty_s& soundProperty, const am_sourceID_t sourceID));
  MOCK_METHOD5(asyncCrossFade,
      am_Error_e(const am_Handle_s handle, const am_crossfaderID_t crossfaderID, const am_HotSink_e hotSink, const am_RampType_e rampType, const am_time_t time));
  MOCK_METHOD2(setDomainState,
      am_Error_e(const am_domainID_t domainID, const am_DomainState_e domainState));
  MOCK_CONST_METHOD1(returnBusName,
      am_Error_e(std::string& BusName));
  MOCK_CONST_METHOD0(getInterfaceVersion,
      uint16_t());
};


class MockControlSendInterface : public ControlSendInterface {
 public:
  MOCK_METHOD1(startupController,
      am_Error_e(ControlReceiveInterface* controlreceiveinterface));
  MOCK_METHOD0(stopController,
      am_Error_e());
  MOCK_METHOD0(hookAllPluginsLoaded,
      void());
  MOCK_METHOD3(hookUserConnectionRequest,
      am_Error_e(const am_sourceID_t sourceID, const am_sinkID_t sinkID, am_mainConnectionID_t& mainConnectionID));
  MOCK_METHOD1(hookUserDisconnectionRequest,
      am_Error_e(const am_mainConnectionID_t connectionID));
  MOCK_METHOD2(hookUserSetMainSinkSoundProperty,
      am_Error_e(const am_sinkID_t sinkID, const am_MainSoundProperty_s& soundProperty));
  MOCK_METHOD2(hookUserSetMainSourceSoundProperty,
      am_Error_e(const am_sourceID_t sourceID, const am_MainSoundProperty_s& soundProperty));
  MOCK_METHOD1(hookUserSetSystemProperty,
      am_Error_e(const am_SystemProperty_s& property));
  MOCK_METHOD2(hookUserVolumeChange,
      am_Error_e(const am_sinkID_t SinkID, const am_mainVolume_t newVolume));
  MOCK_METHOD2(hookUserVolumeStep,
      am_Error_e(const am_sinkID_t SinkID, const int16_t increment));
  MOCK_METHOD2(hookUserSetSinkMuteState,
      am_Error_e(const am_sinkID_t sinkID, const am_MuteState_e muteState));
  MOCK_METHOD2(hookSystemRegisterDomain,
      am_Error_e(const am_Domain_s& domainData, am_domainID_t& domainID));
  MOCK_METHOD1(hookSystemDeregisterDomain,
      am_Error_e(const am_domainID_t domainID));
  MOCK_METHOD1(hookSystemDomainRegistrationComplete,
      void(const am_domainID_t domainID));
  MOCK_METHOD2(hookSystemRegisterSink,
      am_Error_e(const am_Sink_s& sinkData, am_sinkID_t& sinkID));
  MOCK_METHOD1(hookSystemDeregisterSink,
      am_Error_e(const am_sinkID_t sinkID));
  MOCK_METHOD2(hookSystemRegisterSource,
      am_Error_e(const am_Source_s& sourceData, am_sourceID_t& sourceID));
  MOCK_METHOD1(hookSystemDeregisterSource,
      am_Error_e(const am_sourceID_t sourceID));
  MOCK_METHOD2(hookSystemRegisterGateway,
      am_Error_e(const am_Gateway_s& gatewayData, am_gatewayID_t& gatewayID));
  MOCK_METHOD1(hookSystemDeregisterGateway,
      am_Error_e(const am_gatewayID_t gatewayID));
  MOCK_METHOD2(hookSystemRegisterCrossfader,
      am_Error_e(const am_Crossfader_s& crossfaderData, am_crossfaderID_t& crossfaderID));
  MOCK_METHOD1(hookSystemDeregisterCrossfader,
      am_Error_e(const am_crossfaderID_t crossfaderID));
  MOCK_METHOD3(hookSystemSinkVolumeTick,
      void(const am_Handle_s handle, const am_sinkID_t sinkID, const am_volume_t volume));
  MOCK_METHOD3(hookSystemSourceVolumeTick,
      void(const am_Handle_s handle, const am_sourceID_t sourceID, const am_volume_t volume));
  MOCK_METHOD2(hookSystemInterruptStateChange,
      void(const am_sourceID_t sourceID, const am_InterruptState_e interruptState));
  MOCK_METHOD2(hookSystemSinkAvailablityStateChange,
      void(const am_sinkID_t sinkID, const am_Availability_s& availability));
  MOCK_METHOD2(hookSystemSourceAvailablityStateChange,
      void(const am_sourceID_t sourceID, const am_Availability_s& availability));
  MOCK_METHOD2(hookSystemDomainStateChange,
      void(const am_domainID_t domainID, const am_DomainState_e state));
  MOCK_METHOD1(hookSystemReceiveEarlyData,
      void(const std::vector<am_EarlyData_s>& data));
  MOCK_METHOD1(hookSystemSpeedChange,
      void(const am_speed_t speed));
  MOCK_METHOD2(hookSystemTimingInformationChanged,
      void(const am_mainConnectionID_t mainConnectionID, const am_timeSync_t time));
  MOCK_METHOD2(cbAckConnect,
      void(const am_Handle_s handle, const am_Error_e errorID));
  MOCK_METHOD2(cbAckDisconnect,
      void(const am_Handle_s handle, const am_Error_e errorID));
  MOCK_METHOD3(cbAckCrossFade,
      void(const am_Handle_s handle, const am_HotSink_e hostsink, const am_Error_e error));
  MOCK_METHOD3(cbAckSetSinkVolumeChange,
      void(const am_Handle_s handle, const am_volume_t volume, const am_Error_e error));
  MOCK_METHOD3(cbAckSetSourceVolumeChange,
      void(const am_Handle_s handle, const am_volume_t voulme, const am_Error_e error));
  MOCK_METHOD2(cbAckSetSourceState,
      void(const am_Handle_s handle, const am_Error_e error));
  MOCK_METHOD2(cbAckSetSourceSoundProperties,
      void(const am_Handle_s handle, const am_Error_e error));
  MOCK_METHOD2(cbAckSetSourceSoundProperty,
      void(const am_Handle_s handle, const am_Error_e error));
  MOCK_METHOD2(cbAckSetSinkSoundProperties,
      void(const am_Handle_s handle, const am_Error_e error));
  MOCK_METHOD2(cbAckSetSinkSoundProperty,
      void(const am_Handle_s handle, const am_Error_e error));
  MOCK_METHOD4(getConnectionFormatChoice,
      am_Error_e(const am_sourceID_t sourceID, const am_sinkID_t sinkID, const std::vector<am_ConnectionFormat_e> listPossibleConnectionFormats, std::vector<am_ConnectionFormat_e>& listPrioConnectionFormats));
  MOCK_CONST_METHOD0(getInterfaceVersion,
      uint16_t());
};



}  // namespace am



#endif /* MOCKROUTINGINTERFACE_H_ */
