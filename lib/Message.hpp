#pragma once

#include "String.hpp"
#include "Token.hpp"

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
		virtual MessageType type() {
			return MSG;
		}
		virtual ~Message() {
		}
	private:
		String<char_type> m_text;
	};


	class CodeMsg : virtual public Message, virtual public CodePosition {
	public:
	private:
	};

	class Error : virtual public CodeMsg {
	public:
		MessageType type() {
			return ERR;
		}
	private:
	};

	class Warning : virtual public CodeMsg {
	public:
		MessageType type() {
			return WARN;
		}
	private:
	};

	class MsgHandler {
	public:
		virtual void receive(Message *) = 0;
		
	private:
	};



}