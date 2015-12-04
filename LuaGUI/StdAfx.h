﻿// 忽略关于长名字和调试生成的微软警告
// disable MS warning about long names/debug builds
#pragma warning ( disable : 4786 )

#include <windows.h>
#include <mmsystem.h>
#include <string>
#include <map>
#include <list>

#include <cLua.h>
#include <DXBase.h>

#define SAFE_RELEASE(x) if (x) {x->Release(); x=NULL;}
#define SAFE_DELETE(x) if (x) {delete x; x=NULL;} 

#define SAFE_DELETE_ARRAY(x) if(x) {delete[] x; x=NULL;}
