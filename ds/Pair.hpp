#pragma once

#include "ds/AutoComparable.hpp"

namespace ds {
    template<class T1, class T2>
    class Pair : virtual public AutoComparable<Pair<T1, T2>> {
    public:
        T1 &first() {
            return m_member1;
        }

        T2 &second() {
            return m_member2;
        }

        T1 &left() {
            return m_member1;
        }

        T2 &right() {
            return m_member2;
        }

        T1 &x() {
            return m_member1;
        }

        T2 &y() {
            return m_member2;
        }

        bool operator<(const Pair &t) const {
            if (m_member1 != t.m_member1)
                return m_member1 < t.m_member1;
            return m_member2 < t.m_member2;
        }

    private:
        T1 m_member1;
        T2 m_member2;
    };
}
