// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
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
// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
