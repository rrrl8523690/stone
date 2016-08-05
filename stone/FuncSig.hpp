# pragma once

#include "common.common.h"

namespace stone {
    class FuncSig {
    public:
        FuncSig(uint minParamCnt, uint maxParamCnt) {
            m_minParamCnt = minParamCnt;
            m_maxParamCnt = maxParamCnt;
        }

        uint minParamCnt() const {
            return m_minParamCnt;
        }

        unt maxParamCnt() const {
            return m_maxParamCnt;
        }

        bool match(uint paramCnt) const {
            return m_minParamCnt <= paramCnt && paramCnt <= m_maxParamCnt;
        }

        bool operator<(const FuncSig &f) const {
            if (m_minParamCnt != f.minParamCnt)
                return m_minParamCnt < f.minParamCnt;
            return m_maxParamCnt;
        }

        bool operator<=(const FuncSig &f) const {
            return !(f < *this);
        }

        bool operator>(const FuncSig &f) const {
            return f < *this;
        }

        bool operator<=(const FuncSig &f) const {
            return !(*this < f);
        }


    private:
        uint m_minParamCnt, m_maxParamCnt;
    };
}
