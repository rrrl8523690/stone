#pragma once

#include "ds/Array.hpp"
#include "stone/AST.hpp"

namespace stone {
    class Data {
    public:
        virtual ~Data() {
        }

        enum DataType {
            INT,
            DOUBLE,
            ARRAY,
            OBJ,
            FUNC,
            ENV
        };

        inline virtual DataType type() const = 0;
    };

    class IntData : public Data {
    public:
        IntData(int value_) {
            m_value = value_;
        }

        DataType type() const {
            return INT;
        }

        int &value() {
            return m_value;
        }

    private:
        int m_value;
    };

    class DoubleData : public Data {
    public:
        DataType type() const {
            return DOUBLE;
        }

        double &value() {
            return m_value;
        }

    private:
        double m_value;
    };

    class ArrayData : public Data {
    public:
        DataType type() const {
            return ARRAY;
        }
    };

    class ObjData : public Data {
    public:
        DataType type() const {
            return OBJ;
        }
    };

    class FuncData : public Data {
        using DefFuncArray = ds::Array<DefFuncStmtAST *>;
    public:
        FuncData(DefFuncArray *functions_) {
            m_functions = functions_;
        }

        DataType type() const {
            return FUNC;
        }

    private:
        DefFuncArray *m_functions;
    };
}