/*
   Copyright 2019 Kai Huebl (kai@huebl-sgh.de)

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

#include <boost/algorithm/string/replace.hpp>
#include <OpcUaWebServer/WebGateway/RequestHeader.h>
#include "OpcUaStackCore/Base/Log.h"

using namespace OpcUaStackCore;

namespace OpcUaWebServer
{

	RequestHeader::RequestHeader(void)
	: messageType_("")
	, clientHandle_("")
	, sessionId_("")
	{
	}

	RequestHeader::RequestHeader(const RequestHeader& RequestHeader)
	: messageType_(RequestHeader.messageType_)
	, clientHandle_(RequestHeader.clientHandle_)
	, sessionId_(RequestHeader.sessionId_)
	{
	}

	RequestHeader::RequestHeader(
	    const OpcUaString& messageType,
		const OpcUaString& clientHandle,
		const OpcUaString& sessionId
	)
	: messageType_(messageType)
	, clientHandle_(clientHandle)
	, sessionId_(sessionId)
	{
	}

	RequestHeader::~RequestHeader(void)
	{
	}

	OpcUaString&
	RequestHeader::messageType(void)
	{
		return messageType_;
	}

	OpcUaString&
	RequestHeader::clientHandle(void)
	{
		return clientHandle_;
	}

	OpcUaString&
	RequestHeader::sessionId(void)
	{
		return sessionId_;
	}

    bool
	RequestHeader::jsonEncodeImpl(boost::property_tree::ptree& pt) const
    {
    	bool rc = true;
    	rc = rc & jsonObjectEncode(pt, messageType_, "MessageType");
    	rc = rc & jsonObjectEncode(pt, clientHandle_, "ClientHandle");
    	rc = rc & jsonObjectEncode(pt, sessionId_, "SessionId", true);
    	return rc;
    }

    bool
	RequestHeader::jsonDecodeImpl(const boost::property_tree::ptree& pt)
    {
       	bool rc = true;
       	rc = rc & jsonObjectDecode(pt, messageType_, "MessageType");
        rc = rc & jsonObjectDecode(pt, clientHandle_, "ClientHandle");
        rc = rc & jsonObjectDecode(pt, sessionId_, "SessionId", true);
        return rc;
    }

}

