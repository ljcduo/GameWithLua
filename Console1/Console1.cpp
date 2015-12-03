// ��Lua����̨�����޵Ĵʻ㣩
// Simple Lua console with limited vocabulary

// ������׼ϵͳͷ�ļ�
// include the standard system headers.
#include <stdio.h>
#include <string.h>

/*
** ����Luaͷ�ļ���
**  ע��������C����ͷ�ļ���
**  ��Ϊ��Щ��C++����������Ҫ��C++
**  ������֪���������ԭ�ͺ����ݲ�����C++���ƿռ䴦��
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
** ����һ��LuaGlue���������ӡ�
** ��������ᱻLua�������á�
** �ٴΣ���ΪLua��ANSI Cд�ģ�������Ҫ�ص�C++���ƿռ亯��(extern "C")
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
**���������ǹ�ס"Glue"�����ĵط���
** ��������ע��ÿһ�����庯�������������Ǳ�Lua����
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
	// ��ӡ����
	puts("Lua Console (basic) (c) 2004 Charles River Media");
	puts("Enter Lua commands at the prompt, [QUIT] to exit\n\n");

	// Init the Lua environment
	// ��ʼ��Lua����
	lua_State *pLuaState = lua_open();
	// �����ʼ������Lua 5.0.2 �汾�ĳ���⣬����������Lua�ű��������еĺ���
	luaopen_base(pLuaState);
	luaopen_io(pLuaState);
	luaopen_string(pLuaState);
	luaopen_math(pLuaState);
	luaopen_debug(pLuaState);
	luaopen_table(pLuaState);

	// ���ѭ��ʹ�������ṩ��������ע��������Lua����ʹ�õ�����LuaGlue����
	// this loop registers all of our LuaGlue functions with
	// the Lua Environment using the names we provide.
	for(int i=0; ConsoleGlue[i].name; i++)
	{
		lua_register(pLuaState, ConsoleGlue[i].name, ConsoleGlue[i].func);
	}


	// ��������
	// process commands
	const char *pCommand = GetCommand();
	while(stricmp(pCommand, "QUIT") != 0)
	{
		// �������lua����
		// send command to the lua environment
		if (luaL_loadbuffer(pLuaState, pCommand, strlen(pCommand), NULL) == 0)
		{
			if(lua_pcall(pLuaState, 0, LUA_MULTRET, 0) != 0)
			{
				// ��������ʱ��������
				// error on running the command
				printf("ERROR:%s\n", luaL_checkstring(pLuaState, -1));
			}
		}
		else
		{
			// ��������ʱ��������
			//error loading the command
			printf("ERROR:%s\n", luaL_checkstring(pLuaState, -1));
		}

		// ȡ����һ������
		// get next command
		pCommand = GetCommand();
	}

	lua_close(pLuaState);
}
