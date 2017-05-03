#pragma once

#include "Common.h"
#include "Lua/sol.hpp"
#include "../Data/String.h"

namespace Engine
{
	template<typename Object, typename R, typename ...Args>
	struct smart_func
	{
		Object & obj;
		R(Object::*fun)(Args...);

		R operator()(Args... args)
		{
			return (obj.*fun)(args...);
		}
	};
	
	template<typename C, typename R, typename ...Args>
	auto smart_bind(C & c, R(C::*fun)(Args...)) -> smart_func<C, R, Args...>
	{
		return smart_func<C, R, Args...>{c, fun};
	}
	
	class Lua
	{
	public:
		void Load(String filePath);

		template<typename Obj, typename Result, typename ...Args>
		void RegisterMethod(String functionName, smart_func<Obj, Result, Args...> funcDelegate)
		{
			_globalState.set_function(functionName.Str().c_str(), funcDelegate);
		}

		template<typename Obj, typename Result, typename ...Args>
		void RegisterMethod(String functionName, sol::table table, smart_func<Obj, Result, Args...> funcDelegate)
		{
			table.set_function(functionName.Str().c_str(), funcDelegate);
		}

		static Lua* Instance();

	private:
		Lua();
		~Lua();

		void InitialiseMethods();
		void Update();
		void Draw();

		sol::state _globalState;
		static Lua* _pInstance;
	};
}
