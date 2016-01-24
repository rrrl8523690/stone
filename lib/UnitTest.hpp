#pragma once

#include <iostream>

#define equal(t1,t2)  int res=((t1)==(t2));\
if(!res)std::cerr << "ERROR: Not equal.\nVariable names: " << (#t1) << ", " << (#t2) << "." << std::endl\
<< "Variable values: " << t1 << ", " << t2 << "." << std::endl;\
else cerr << "Equal: OK" << std::endl;
