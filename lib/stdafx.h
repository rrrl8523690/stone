// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include <stdio.h>
#include <tchar.h>

typedef unsigned int uint;

template<class T>
const T& min(const T& t1, const T& t2) {
	if (t1 < t2)
		return t1;
	return t2;
}
template<class T>
const T& max(const T& t1, const T& t2) {
	if (t1 > t2)
		return t1;
	return t2;
}
// TODO:  在此处引用程序需要的其他头文件
