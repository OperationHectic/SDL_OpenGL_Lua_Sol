#include "LuaManager.h"

//sol::state LuaManager::m_LuaState;
//bool LuaManager::m_IsScriptActive = false;
//std::string LuaManager::m_ScriptName = nullptr;

/*template<typename T>
T GetLuaValue(std::string varName)
{
	if (LuaManager::m_IsScriptActive)
	{
		try
		{
			return LuaManager::m_LuaState[varName];
		}
		catch (const std::runtime_error& ex)
		{
			std::cout << "Lua variable name " << varName
				<< " was not found in file " << LuaManager::m_ScriptName << '\n';

			std::cout << "Terminating with error: " << ex.what() << '\n';
		}
	}

	return T();
}*/

LuaManager::LuaManager()
{
	m_LuaState.open_libraries(sol::lib::base);
}

LuaManager::~LuaManager()
{
}

void LuaManager::SetActiveScript(std::string scriptName)
{
	m_LuaState.script_file(scriptName);
	m_IsScriptActive = true;
}

std::string LuaManager::GetString(std::string varName)
{
	//return GetLuaValue<std::string>(varName);
	if (m_IsScriptActive)
	{
		try
		{
			return m_LuaState[varName];
		}
		catch (const std::runtime_error& ex)
		{
			std::cout << "Lua variable name " << varName
				<< " was not found in file " << m_ScriptName << '\n';

			std::cout << "Terminating with error: " << ex.what() << '\n';
		}
	}

	return std::string();
}

int LuaManager::GetInteger(std::string varName)
{
	//return GetLuaValue<int>(varName);
	if (m_IsScriptActive)
	{
		try
		{
			return m_LuaState[varName];
		}
		catch (const std::runtime_error& ex)
		{
			std::cout << "Lua variable name " << varName
				<< " was not found in file " << m_ScriptName << '\n';

			std::cout << "Terminating with error: " << ex.what() << '\n';
		}
	}

	return 0;
}

double LuaManager::GetDouble(std::string varName)
{
	//return GetLuaValue<double>(varName);
	if (m_IsScriptActive)
	{
		try
		{
			return m_LuaState[varName];
		}
		catch (const std::runtime_error& ex)
		{
			std::cout << "Lua variable name " << varName
				<< " was not found in file " << m_ScriptName << '\n';

			std::cout << "Terminating with error: " << ex.what() << '\n';
		}
	}

	return 0.0;
}

sol::table LuaManager::GetTable(std::string tableName)
{
	if (m_IsScriptActive)
	{
		try
		{
			return m_LuaState[tableName];
		}
		catch (const std::runtime_error& ex)
		{
			std::cout << "Lua variable name " << tableName
				<< " was not found in file " << m_ScriptName << '\n';

			std::cout << "Terminating with error: " << ex.what() << '\n';
		}
	}

	return sol::table();
}
