# pragma once

#include "common/Common.h"
#include "ds/AutoComparable.hpp"

namespace stone {
    class FuncSig : virtual public AutoComparable<FuncSig> {
    public:
        FuncSig(uint minParamCnt, uint maxParamCnt) {
            m_minParamCnt = minParamCnt;
            m_maxParamCnt = maxParamCnt;
        }

        uint minParamCnt() const {
            return m_minParamCnt;
        }

        uint maxParamCnt() const {
            return m_maxParamCnt;
        }

        bool match(uint paramCnt) const {
            return m_minParamCnt <= paramCnt && paramCnt <= m_maxParamCnt;
        }

        bool operator<(const FuncSig &f) const {
            if (m_minParamCnt != f.m_minParamCnt)
                return m_minParamCnt < f.m_minParamCnt;
            return m_maxParamCnt;
        }

    private:
        uint m_minParamCnt, m_maxParamCnt;
    };
}
