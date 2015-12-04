// 简单Lua控制台（有限的词汇）
// 使用cLua对象和Lua库
// Simple Lua console with limited vocabulary
// Using cLua object and Lua library

// 包含标准系统头文件
// include the standard system headers.
#include <stdio.h>
#include <string.h>
#include <cLua.h>

LuaGlue _Version(lua_State *L)
{
	puts("This is Version 2.0 of the Console Program");
	return 0;
}

char gpCommandBuffer[254];

const char *GetCommand(void)
{
	printf("Ready> ");
	return gets(gpCommandBuffer);
	puts("\n");
}

void main(void)
{
	// 打印标语
	// print the banner.
	puts("Lua Console (c) 2004 Charles River Media");
	puts("Enter Lua commands at the prompt, [QUIT] to exit\n\n");

	cLua *pLua = new cLua;

	pLua->AddFunction("Version", _Version);

	// 处理命令
	// process commands
	const char *pCommand = GetCommand();
	while(stricmp(pCommand, "QUIT") != 0)
	{
		// 传递字符串给cLua
		// pass the string to cLua
		if(!pLua->RunString(pCommand))
		{
			printf("ERROR:%s\n", pLua->GetErrorString());
		}

		// 获得下一个命令
		// get next command
		pCommand = GetCommand();
	}
	
	delete pLua;
}
