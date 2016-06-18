#pragma once


class Data {
public:
	enum DataType {
		INT,
		ARRAY,
		OBJ,
		FUNC
	};
	inline virtual DataType type() = 0;
};

class IntData : public Data {
	
};

class ArrayData : public Data {

};

class ObjData : public Data {

};

class FuncData : public Data {

};