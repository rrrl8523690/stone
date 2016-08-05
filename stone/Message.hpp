#pragma once

#include "ds/String.hpp"
#include "stone/Token.hpp"

namespace stone {
    using namespace ds;
    typedef char char_type;

    class Message {
    public:
        enum MessageType {
            MSG, ERR, WARN
        };

        Message(const String<char_type> &text_) {
            m_text = text_;
        }

        const String<char_type> &text() const {
            return m_text;
        }

        virtual const String<char_type> textToPrint() const {
            return m_text;
        }

        virtual MessageType type() {
            return MSG;
        }

        virtual ~Message() {
        }

    private:
        String<char_type> m_text;
    };


    class CodeMsg : public Message, public CodePosition {
    public:
        CodeMsg(const String<char_type> &text_, CodePosition codePos_) : Message(text_), CodePosition(codePos_) {

        }

        const String<char_type> textToPrint() const {
            return String<char_type>::number(line()) + ", " + String<char_type>::number(kth()) + ": " + Message::text();
        }

    private:
    };

    class Error : public CodeMsg {
    public:
        Error(const String<char_type> &string, const CodePosition &codePos_) : CodeMsg(string, codePos_) {

        }

        MessageType type() {
            return ERR;
        }

        const String<char_type> textToPrint() const {
            return String<char_type>("Error at ") + CodeMsg::textToPrint();
        }

    private:
    };

    class MsgHandler {
    public:
        virtual    ~MsgHandler() {
        }

        virtual void receive(Message *) = 0;

    private:
    };

    class MsgPrinter : virtual public MsgHandler {
    public:
        MsgPrinter(std::ostream &os) : m_os(os) {
        }

        void receive(Message *message) {
            m_msgArray.append(message);
            m_os << message->textToPrint() << std::endl;
        }

    private:
        std::ostream &m_os;
        Array<Message *> m_msgArray;
    };

}