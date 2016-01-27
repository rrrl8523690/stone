#pragma once

#include <iostream>

#define equal(t1,t2)  \
{if(!((t1)==(t2)))std::cerr << "ERROR: " << (#t1) << " != " << (#t2) << std::endl\
<< (#t1) << " = " << (t1) << ", " << (#t2) << " = " << (t2) << std::endl;\
else cerr << (#t1) << " == " << (#t2) << std::endl;}
