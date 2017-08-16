#pragma once

#include "Lua/sol.hpp"
#include "../Data/String.h"
#include <map>

namespace Engine
{
	template<typename Object, typename R, typename ...Args>
	struct SmartFunc
	{
		Object & obj;
		R(Object::*fun)(Args...);

		R operator()(Args... args)
		{
			return (obj.*fun)(args...);
		}
	};
	
	template<typename C, typename R, typename ...Args>
	auto SmartBind(C & c, R(C::*fun)(Args...)) -> SmartFunc<C, R, Args...>
	{
		return SmartFunc<C, R, Args...>{c, fun};
	}

	class Lua
	{
	public:
		ENGINE_API void Load(String filePath);

		template<typename Obj, typename Result, typename ...Args>
		void RegisterMethod(std::string className, std::string methodName, SmartFunc<Obj, Result, Args...> funcDelegate)
		{
			sol::table table;
			const auto iterator = _classTableMap.find(className);
			if (iterator != _classTableMap.end())
			{
				table = iterator->second;
			}
			else
			{
				table = _engineTable.create_named(className);
				_classTableMap[className] = table;
			}

			table.set_function(methodName, funcDelegate);
		}

		ENGINE_API static Lua* Instance();

	private:
		Lua();
		~Lua();

		void Update();
		void Draw();
		void Shutdown();

		std::map<std::string, sol::table> _classTableMap;
		sol::state _globalState;
		sol::table _engineTable;
		static Lua* _pInstance;
		bool _scriptParsed;
	};
}
