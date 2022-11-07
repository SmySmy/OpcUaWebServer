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

#include <boost/make_shared.hpp>

#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaWebServer/WebSocket/WebSocketMessageContext.h"

using namespace OpcUaStackCore;

namespace OpcUaWebServer
{

    void
    WebSocketMessageContext::setHeader(bool fin, uint8_t opcode, bool mask, uint32_t length)
    {
        fin_ = fin;
        opcode_ = opcode;
        mask_ = mask;
        length_ = length;

        Log(Info, "WebSocketServer set new message header")
            .parameter("fin", fin_)
            .parameter("opcode", opcode_)
            .parameter("mask", mask_)
            .parameter("length", length_);
    }

    bool
    WebSocketMessageContext::fin(void)
    {
        return fin_;
    }

    uint8_t
    WebSocketMessageContext::opcode(void)
    {
        return opcode_;
    }

    bool
    WebSocketMessageContext::mask(void)
    {
        return mask_;
    }

    uint32_t
    WebSocketMessageContext::length(void)
    {
        return length_;
    }

    void
    WebSocketMessageContext::setMessageFragment(WebSocketMessage::SPtr message)
    {
        Log(Info, "WebSocketServer add container for message fragmentation.");

        if (webSocketMessageFragmentation_ != nullptr) {
            webSocketMessageFragmentation_.reset();
            webSocketMessageFragmentation_ = nullptr;
        }

        webSocketMessageFragmentation_ = message;
    }

    WebSocketMessage::SPtr
    WebSocketMessageContext::getMessageFragments(void)
    {
        return webSocketMessageFragmentation_;
    }

    void
    WebSocketMessageContext::clear(void)
    {
        Log(Info, "WebSocketServer clears message context.");

        fin_ = true;
        opcode_ = 1;
        mask_ = true;
        length_ = 0;

        if (webSocketMessageFragmentation_ != nullptr) {
            webSocketMessageFragmentation_.reset();
            webSocketMessageFragmentation_ = nullptr;
        }
    }


    WebSocketMessageContext::EnumFrameType
    WebSocketMessageContext::getFrameType(void)
    {
        // https://www.rfc-editor.org/rfc/rfc6455#section-5.4
        // opcode == 0 && fin == true  => LastFrame
        // opcode == 0 && fin == false => Frame
        // opcode != 0 && fin == false => FirstFrame
        // opcode != 0 && fin == true  => SingleFrame

        if (opcode_ == 0x00 /*OP_CONTINUATION_FRAME*/) {
            if (fin_) return EnumFrameType::FrameType_LastFrame;
            else      return  EnumFrameType::FrameType_Frame;
        }

        if (!fin_) return EnumFrameType::FrameType_FirstFrame;

        return EnumFrameType::FrameType_SingleFrame;
    }

}
