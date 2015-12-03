// 简单Lua控制台（有限的词汇）
// Simple Lua console with limited vocabulary

// 包含标准系统头文件
// include the standard system headers.
#include <stdio.h>
#include <string.h>

/*
** 包含Lua头文件。
**  注意它们是C语言头文件。
**  因为这些是C++程序，我们需要让C++
**  编译器知道这个引用原型和数据不会有C++名称空间处理
** Include the Lua headers. 
**	Note that they are "C" language headers.
**	Since we are C++ program, we need to let the C++ compiler 
**	know that the referenced prototypes and data will not have C++
**	namespace processing.
*/
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

/*
** 这是一个LuaGlue函数的例子。
** 这个函数会被Lua环境调用。
** 再次，因为Lua是ANSI C写的，我们需要关掉C++名称空间函数(extern "C")
** This is an example of a LuaGlue function
** The function will be called from the Lua Environment
** Again, since Lua is written in ANSI C, we need to 
** turn off the C++ namespace function (extern "C")
*/
extern "C" int _Version(lua_State *L)
{
	puts("This is Version 1.0 of the Console Program");
	puts(LUA_VERSION);
	puts(LUA_COPYRIGHT);
	puts(LUA_AUTHORS);
	return 0;
}

/*
**　这是我们勾住"Glue"函数的地方。
** 这个程序会注册每一个定义函数，并且让它们被Lua调用
** This is where we hook up out "Glue" functions. 
** The program will register each of the defined functions 
** and allow them to be called from Lua.
*/
static luaL_reg ConsoleGlue[] = 
{
	{"Version",		_Version},
	{NULL, NULL}
};

char gpCommandBuffer[254];

const char *GetCommand(void)
{
	printf("Ready> ");
	return gets(gpCommandBuffer);
	puts("\n");
}

void main(void)
{
	// print the banner.
	// 打印标语
	puts("Lua Console (basic) (c) 2004 Charles River Media");
	puts("Enter Lua commands at the prompt, [QUIT] to exit\n\n");

	// Init the Lua environment
	// 初始化Lua环境
	lua_State *pLuaState = lua_open();
	// 这里初始化所有Lua 5.0.2 版本的程序库，这样可以让Lua脚本访问所有的函数
	luaopen_base(pLuaState);
	luaopen_io(pLuaState);
	luaopen_string(pLuaState);
	luaopen_math(pLuaState);
	luaopen_debug(pLuaState);
	luaopen_table(pLuaState);

	// 这个循环使用我们提供的名字来注册我们在Lua环境使用的所有LuaGlue函数
	// this loop registers all of our LuaGlue functions with
	// the Lua Environment using the names we provide.
	for(int i=0; ConsoleGlue[i].name; i++)
	{
		lua_register(pLuaState, ConsoleGlue[i].name, ConsoleGlue[i].func);
	}


	// 处理命令
	// process commands
	const char *pCommand = GetCommand();
	while(stricmp(pCommand, "QUIT") != 0)
	{
		// 发送命令到lua环境
		// send command to the lua environment
		if (luaL_loadbuffer(pLuaState, pCommand, strlen(pCommand), NULL) == 0)
		{
			if(lua_pcall(pLuaState, 0, LUA_MULTRET, 0) != 0)
			{
				// 运行命令时发生错误
				// error on running the command
				printf("ERROR:%s\n", luaL_checkstring(pLuaState, -1));
			}
		}
		else
		{
			// 载入命令时发生错误
			//error loading the command
			printf("ERROR:%s\n", luaL_checkstring(pLuaState, -1));
		}

		// 取得下一个命令
		// get next command
		pCommand = GetCommand();
	}

	lua_close(pLuaState);
}
