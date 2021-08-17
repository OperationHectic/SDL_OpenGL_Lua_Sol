#ifndef LUA_MANAGER
#define LUA_MANAGER

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

class LuaManager
{
private:
	sol::state m_LuaState;
	bool m_IsScriptActive;
	std::string m_ScriptName;

public:
	LuaManager();
	~LuaManager();
	//template<typename T>
	//friend T GetLuaValue(std::string varName);
	void SetActiveScript(std::string scriptName);
	std::string GetString(std::string varName);
	int GetInteger(std::string varName);
	double GetDouble(std::string varName);
	sol::table GetTable(std::string tableName);
};

#endif
