#pragma once

namespace ds {
    template<class T1, class T2>
    class Pair {
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

        bool operator

    private:
        T1 m_member1;
}
