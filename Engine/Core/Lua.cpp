#include "Lua.h"
#include "../Data/String.h"
#include "Core.h"
#include "../Utils/Logger.h"
#include "../Core/Time.h"
#include "../Utils/Console.h"

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
		: _scriptParsed(false)
	{
		_globalState.open_libraries(sol::lib::base);
		_globalState.open_libraries(sol::lib::string);

		_engineTable = _globalState.create_named_table("Engine");

		Core::Instance()->OnUpdate += std::bind(&Lua::Update, this);
		Core::Instance()->OnShutdown += std::bind(&Lua::Shutdown, this);
	}

	Lua::~Lua()
	{
		_pInstance = nullptr;
	}

	void Lua::Shutdown()
	{
		if (_pInstance != nullptr)
		{
			if (_scriptParsed)
			{
				_globalState.script("Destroy()");
			}
			
			_classTableMap.clear();
			_scriptParsed = false;

			delete _pInstance;
		}
	}

	void Lua::Load(String filePath)
	{
		try
		{
			_globalState.script_file(filePath);
			_globalState.script("Start()");
			_scriptParsed = true;
		} 
		catch (const std::exception& e)
		{
			Logger::Instance()->LogError(e.what());
		}
	}
	
	void Lua::Update()
	{
		if (!_scriptParsed)
		{
			return;
		}

		const float deltaTime = Time::Instance()->DeltaTime();
		_globalState.script(String("Update(") + String(deltaTime) + String(")"));
	}

	void Lua::Draw()
	{
		_globalState.script("Draw()");
	}
}
