#ifndef __CLUA__
#define __CLUA__

struct lua_State;

#define LuaGlue extern "C" int
extern "C" {
typedef int (*LuaFunctionType)(struct lua_State *pLuaState);
};

class cLua
{
public:
	cLua();
	virtual ~cLua();

	bool		RunScript(const char *pFilename);
	bool		RunString(const char *pCommand);	//运行字符串命令
	const char *GetErrorString(void);				//获得错误字符串
	bool		AddFunction(const char *pFunctionName, LuaFunctionType pFunction);
	const char *GetStringArgument(int num, const char *pDefault=NULL);	//获得LuaGlue函数的参数，返回指向空值终止字符串的指针或者NULL表示参数错误，num指定参数的位置（从1开始）
	double		GetNumberArgument(int num, double dDefault=0.0);		//获得LuaGlue函数的参数，返回双精度浮点数或者0.0表示没有参数，num指定参数的位置（从1开始）
	void		PushString(const char *pString);	//向Lua栈存入返回值
	void		PushNumber(double value);			//向Lua栈存入返回值

	void		SetErrorHandler(void(*pErrHandler)(const char *pError)) {m_pErrorHandler = pErrHandler;}

	lua_State	*GetScriptContext(void)		{return m_pScriptContext;}

private:
	lua_State	*m_pScriptContext;
	void(*m_pErrorHandler)(const char *pError);
};

#endif