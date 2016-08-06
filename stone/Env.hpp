#pragma once

#include "stone/Data.hpp"
#include "ds/String.hpp"
#include "common/Common.h"
#include "ds/Map.hpp"
#include <memory>

namespace stone {
    class Env : public Data {
    public:
        using EnvPtr = std::shared_ptr<Env>;

        virtual ~Env() {
        }

        DataType type() const {
            return ENV;
        }

        virtual DataPtrPtr get(const ds::String<char_type> &name) = 0;

        virtual DataPtrPtr getOrCreate(const ds::String<char_type> &name) = 0;

        virtual DataPtrPtr create(const ds::String<char_type> &name) = 0;

        virtual DataPtrPtr getInCurrentEnv(const ds::String<char_type> &name) = 0;

        EnvPtr &outer() {
            return m_outer;
        }

        EnvPtr &parent() {
            return m_parent;
        }

    private:
        EnvPtr m_outer, m_parent;
    };
}