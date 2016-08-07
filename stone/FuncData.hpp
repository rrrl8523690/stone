#pragma once

#include "stone/Data.hpp"
#include "stone/Env.hpp"

namespace stone {

    class FuncData : public Data {
        using DefFuncArray = ds::Array<ds::Pair<FuncSig, DefFuncStmtAST *>>;
    public:

        FuncData(Env::EnvPtr env_) {
            m_functions = new ds::Array<ds::Pair<FuncSig, DefFuncStmtAST *>>();
            m_env = env_;
        }

        DefFuncArray *functions() {
            return m_functions;
        }

        ~FuncData() {
            delete m_functions;
        }

        DataType type() const {
            return FUNC;
        }

        Env::EnvPtr env() {
            return m_env;
        }

    private:
        DefFuncArray *m_functions;
        Env::EnvPtr m_env;
    };
}
