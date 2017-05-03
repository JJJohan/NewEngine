#include "Lua.h"
#include "../Data/String.h"
#include "Core.h"
#include "../Utils/SystemInfo.h"
#include "../Utils/Logger.h"
#include "../Core/Time.h"

namespace Engine
{
	Lua* Lua::_pInstance = nullptr;

	Lua* Lua::Instance()
	{
		if (_pInstance == nullptr)
		{
			_pInstance = new Lua();
		}

		return _pInstance;
	}

	Lua::Lua()
	{
		_globalState.open_libraries(sol::lib::base);
		_globalState.open_libraries(sol::lib::string);

		InitialiseMethods();

		Core::Instance()->OnUpdate += std::bind(&Lua::Update, this);
	}

	Lua::~Lua()
	{
		if (_pInstance != nullptr)
		{
			delete _pInstance;
			_pInstance = nullptr;
		}
	}

	void Lua::InitialiseMethods()
	{
		sol::table engineTable = _globalState.create_named_table("Engine");
		
		sol::table table = engineTable.create_named("Core");
		RegisterMethod("Initialise", table, smart_bind(*Core::Instance(), &Core::Initialise));
		RegisterMethod("SetMaxFPS", table, smart_bind(*Core::Instance(), &Core::SetMaxFPS));
		RegisterMethod("PrintSystemInfo", table, smart_bind(*SystemInfo::Instance(), &SystemInfo::PrintSystemInfo));

		table = engineTable.create_named("Logger");
		RegisterMethod("Log", table, smart_bind<Logger, void, const std::string&>(*Logger::Instance(), &Logger::Log));
		RegisterMethod("LogError", table, smart_bind<Logger, void, const std::string&>(*Logger::Instance(), &Logger::LogError));
		RegisterMethod("LogWarning", table, smart_bind<Logger, void, const std::string&>(*Logger::Instance(), &Logger::LogWarning));

		table = engineTable.create_named("Time");
		table.set_function("DeltaTime", std::bind(&Time::DeltaTime, Time::Instance()));
	}

	void Lua::Load(String filePath)
	{
		try
		{
			_globalState.script_file(filePath);
			_globalState.script("Start()");
		} 
		catch (const std::exception& e)
		{
			Logger::Instance()->LogError(e.what());
		}
	}
	
	void Lua::Update()
	{
		_globalState.script("Update()");
	}

	void Lua::Draw()
	{
		_globalState.script("Draw()");
	}
}
