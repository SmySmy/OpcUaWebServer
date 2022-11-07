/*
   Copyright 2015-2022 ASNeG (info@asneg.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Samuel Huebl
 */

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaWebServer/WebSocket/WebSocketMessage.h"

namespace OpcUaWebServer
{

	class DLLEXPORT WebSocketMessageContext
	{
	  public:
        typedef enum {
            FrameType_Unknown = 0,
            FrameType_SingleFrame = 1,
            FrameType_Frame = 2,
            FrameType_FirstFrame = 3,
            FrameType_LastFrame = 4
        } EnumFrameType;

	    typedef boost::shared_ptr<WebSocketMessageContext> SPtr;

	    WebSocketMessageContext(void) = default;
	    virtual ~WebSocketMessageContext(void) = default;

	    void setHeader(bool fin, uint8_t opcode, bool mask, uint32_t length);
	    bool fin(void);
	    uint8_t opcode(void);
	    bool mask(void);
	    uint32_t length(void);

	    void setMessageFragment(WebSocketMessage::SPtr message);
	    WebSocketMessage::SPtr getMessageFragments(void);

	    void clear(void);

	    EnumFrameType getFrameType(void);

	  private:
	    bool fin_ { true };
	    uint8_t opcode_ { 0x1 };
	    bool mask_ { true };
	    uint32_t length_ { 0x0 };

	    WebSocketMessage::SPtr webSocketMessageFragmentation_ { nullptr };
	};

}
