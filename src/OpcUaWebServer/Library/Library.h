/*
   Copyright 2015-2019 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Kai Huebl (kai@huebl-sgh.de)
 */

#ifndef __OpcUaWebServer_Library_h__
#define __OpcUaWebServer_Library_h__

#include "OpcUaStackServer/Application/ApplicationIf.h"
#include "OpcUaWebServer/WebServer/WebServer.h"
#include "OpcUaWebServer/WebSocket/WebSocket.h"
#include "OpcUaWebServer/MessageServer/MessageServer.h"
#include "OpcUaWebServer/OpcUaClient/OpcUaClientManager.h"

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

namespace OpcUaWebServer
{

	class Library
	: public ApplicationIf
	, public WebSocketServerIf
	, public MessageServerIf
	, public OpcUaClientManagerIf
	{
	  public:
		Library(void);
		virtual ~Library(void);

		//- ApplicationIf -----------------------------------------------------
		virtual bool startup(void);
		virtual bool shutdown(void);
		virtual std::string version(void);
		//- ApplicationIf -----------------------------------------------------

		//- WebSocketServerIf -------------------------------------------------
		void webSocketMessage(WebSocketMessage& webSocketMessage);
		//- WebSocketServerIf -------------------------------------------------

		//- MessageServerIf ---------------------------------------------------
		void messageServerMessage(Message::SPtr& message);
		void messageServerMessage(uint32_t channelId, const std::string& message);
		//- MessageServerIf ---------------------------------------------------

		//- OpcUaClientManagerIf ----------------------------------------------
		void clientManagerMessage(Message::SPtr& message);
		//- OpcUaClientManagerIf ----------------------------------------------

	  private:
		IOThread::SPtr ioThread_;
		WebServer webServer_;
		WebSocket webSocket_;
		MessageServer messageServer_;
		OpcUaClientManager opcUaClientManager_;
	};

}

#endif
