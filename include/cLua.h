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
	bool		RunString(const char *pCommand);	//�����ַ�������
	const char *GetErrorString(void);				//��ô����ַ���
	bool		AddFunction(const char *pFunctionName, LuaFunctionType pFunction);
	const char *GetStringArgument(int num, const char *pDefault=NULL);	//���LuaGlue�����Ĳ���������ָ���ֵ��ֹ�ַ�����ָ�����NULL��ʾ��������numָ��������λ�ã���1��ʼ��
	double		GetNumberArgument(int num, double dDefault=0.0);		//���LuaGlue�����Ĳ���������˫���ȸ���������0.0��ʾû�в�����numָ��������λ�ã���1��ʼ��
	void		PushString(const char *pString);	//��Luaջ���뷵��ֵ
	void		PushNumber(double value);			//��Luaջ���뷵��ֵ

	void		SetErrorHandler(void(*pErrHandler)(const char *pError)) {m_pErrorHandler = pErrHandler;}

	lua_State	*GetScriptContext(void)		{return m_pScriptContext;}

private:
	lua_State	*m_pScriptContext;
	void(*m_pErrorHandler)(const char *pError);
};

#endif