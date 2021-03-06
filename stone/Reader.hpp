#pragma once

#include "ds/String.hpp"

using namespace ds;

namespace stone {
    template<class CharType = char>
    class Reader {
    public:
        virtual CharType read() = 0;

        virtual String<CharType> readLine() {
            String<CharType> res;
            CharType ch;
            while (!isEnd()) {
                ch = read();
                next();
                if ('\n' == ch)
                    break;
                res.append(ch);
            }
            return res;
        }

        virtual bool isEnd() = 0;

        virtual void next() = 0;

        virtual void prev() = 0;

        virtual ~Reader() {
        }
    };

    template<class CharType = char>
    class StringReader : public Reader<CharType> {
    public:
        StringReader() = delete;

        StringReader(String<CharType> *string_) {
            string = string_;
            pos = 0;
        }

        CharType read() {
            return string->at(pos);
        }

        void next() {
            pos++;
        }

        void prev() {
            pos--;
        }

        bool isEnd() {
            return pos >= string->size();
        }

    private:
        ds::String<CharType> *string;
        uint pos;
    };
}