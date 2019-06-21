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

#ifndef __OpcUaWebServer_WebSocketChannel_h__
#define __OpcUaWebServer_WebSocketChannel_h__

#include <map>
#include "OpcUaStackCore/Network/TCPConnection.h"
#include "OpcUaStackCore/Utility/SlotTimer.h"
#include "OpcUaWebServer/WebSocket/WebSocketRequest.h"
#include "OpcUaWebServer/WebSocket/WebSocketResponse.h"

using namespace OpcUaStackCore;

namespace OpcUaWebServer
{

	class WebSocketChannel
	: public TCPConnection
	{
	  public:
		typedef std::map<uint32_t, WebSocketChannel*> Map;

		static uint32_t gChannelId_;

		WebSocketChannel(boost::asio::io_service& io_service);
		virtual ~WebSocketChannel(void);

		std::string getId(void);

		OpcUaStackCore::SlotTimerElement::SPtr slotTimerElement_;

		bool timeout_;
		uint32_t id_;
		uint8_t opcode_;
		boost::asio::streambuf recvBuffer_;
		boost::asio::streambuf sendBuffer_;
		WebSocketRequest webSocketRequest_;
		WebSocketResponse webSocketResponse_;
		boost::asio::ip::tcp::endpoint partner_;
	};

}

#endif
