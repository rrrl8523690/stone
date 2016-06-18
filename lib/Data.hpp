#pragma once


class Data {
public:
	virtual ~Data() {
	}
	enum DataType {
		INT,
		DOUBLE,
		ARRAY,
		OBJ,
		FUNC
	};
	inline virtual DataType type() = 0;
};

class IntData : public Data {
public:
	DataType type() {
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
	DataType type() {
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
	DataType type() {
		return ARRAY;
	}
};

class ObjData : public Data {
public:
	DataType type() {
		return OBJ;
	}
};

class FuncData : public Data {
public:
	DataType type() {
		return FUNC;
	}
};