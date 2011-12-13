/*
 * routingInterfaceTest.h
 *
 *  Created on: Dec 10, 2011
 *      Author: christian
 */

#ifndef ROUTINGINTERFACETEST_H_
#define ROUTINGINTERFACETEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <dlt/dlt.h>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include "MockRoutingInterface.h"
#include "DatabaseHandler.h"
#include "ControlReceiver.h"
#include "ControlSender.h"
#include "Observer.h"
#include "../RoutingInterfaceBackdoor.h"
#include "../CommandInterfaceBackdoor.h"
#include "../CommonFunctions.h"

DLT_DECLARE_CONTEXT(AudioManager)

using namespace testing;
using namespace am;

class routingInterfaceTest : public Test{
public:
	routingInterfaceTest();
	virtual ~routingInterfaceTest();
	DatabaseHandler pDatabaseHandler;
	RoutingSender pRoutingSender;
	CommandSender pCommandSender;
	MockRoutingSendInterface pMockInterface;
	RoutingInterfaceBackdoor pRoutingInterfaceBackdoor;
	CommandInterfaceBackdoor pCommandInterfaceBackdoor;
	ControlReceiver pControlReceiver;
	Observer pObserver;
	CommonFunctions pCF;
	void SetUp();
	void TearDown();
};

#endif /* ROUTINGINTERFACETEST_H_ */