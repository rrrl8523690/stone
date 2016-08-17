#pragma once

#include "ds/Array.hpp"
#include "ds/Pair.hpp"
#include "stone/FuncSig.hpp"
#include "stone/AST.hpp"
#include "stone/Env.hpp"

namespace stone {
    class IntData;

    class FuncData;

    class ObjData;

    class ArrayData;

    class Env;

    class Data {
    public:
        virtual ~Data() {
        }

        using DataPtr = std::shared_ptr<Data>;
        using DataPtrPtr = std::shared_ptr<DataPtr>;
        using IntDataPtr = std::shared_ptr<IntData>;
        using FuncDataPtr = std::shared_ptr<FuncData>;
        using ArrayDataPtr = std::shared_ptr<ArrayData>;
        enum DataType {
            INT,
            DOUBLE,
            ARRAY,
            OBJ,
            FUNC,
            ENV
        };

        inline virtual DataType type() const = 0;

        DataPtrPtr toDataPtrPtr() {
            std::shared_ptr<Data> tmp(this);
            DataPtrPtr res(new std::shared_ptr<Data>(tmp));
            return res;
        }

        static IntDataPtr toInt(DataPtr dataPtr) {
            return std::dynamic_pointer_cast<IntData>(dataPtr);
        }

        static FuncDataPtr toFunc(DataPtr dataPtr) {
            return std::dynamic_pointer_cast<FuncData>(dataPtr);
        }

        static ArrayDataPtr toArray(DataPtr dataPtr) {
            return std::dynamic_pointer_cast<ArrayData>(dataPtr);
        }

        static bool isTrue(const DataPtr ptr);


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
       ArrayData(int initialSize = 0) {
            m_array = new Array<DataPtr>(initialSize);
        }

        DataType type() const {
            return ARRAY;
        }

        ~ArrayData() {
            delete m_array;
        }

        Array<DataPtr> *array() {
            return m_array;
        }
    private:
        Array<DataPtr> *m_array;
    };

    class ObjData : public Data {
    public:
        DataType type() const {
            return OBJ;
        }
    };


    bool Data::isTrue(const DataPtr ptr) {
        switch (ptr->type()) {
            case Data::INT:
                return toInt(ptr)->value();
            default: // TODO: error
                return false;
        }
    }
}