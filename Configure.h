#pragma once

//通过预编译的方法去掉Unicode字符集
#ifdef UNICODE
#undef UNICODE
#endif // UNICODE

#include <easyx.h>
#include<graphics.h>
#include <string>