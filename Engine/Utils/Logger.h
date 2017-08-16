#pragma once

// Checks if a result has failed and logs an error.
#define LOGFAILED(x,y) if(FAILED(x)) { Engine::Logging::LogError(y); }

// Checks if a result has failed and logs the last Win32 error message.
#define LOGFAILEDCOM(x) if(FAILED(x)) { Engine::Logging::LogError(Engine::Logging::GetCOMError(_com_error(x), __FUNCTION__)); }

// Checks if a result has failed, logs an error message and returns a specified return value.
#define LOGFAILEDRETURN(x,y,z) if(FAILED(x)) { Engine::Logging::LogError(y); return z; }

// Checks if a result has failed, logs the last Win32 error message and returns a specified return value.
#define LOGFAILEDCOMRETURN(x,y) if(FAILED(x)) { Engine::Logging::LogError(Engine::Logging::GetWin32ErrorString()); return y; }

#include "../Data/String.h"
#include "../Core/IRegisteredClass.h"
#include <comdef.h>
#include <mutex>

namespace Engine
{
	class Logger : IRegisteredClass
	{
	public:
		ENGINE_API void Log(const std::string& message);
		ENGINE_API void LogError(const std::string& message);
		ENGINE_API void LogWarning(const std::string& message);
		void LogWin32Error();
		static String GetWin32ErrorString();
		static String GetCOMError(const _com_error& error, const String& caller);
		ENGINE_API void EnableFileLogging(bool enabled);
		ENGINE_API void SetLogPath(const std::string& filePath);
		void Register() override;

		template <typename... Args>
		void Log(const String& string, Args ... args)
		{
			std::string text = fmt::format(string.Str(), args...);
			Log(text);
		}

		template <typename... Args>
		void LogWarning(const String& string, Args ... args)
		{
			std::string text = fmt::format(string.Str(), args...);
			LogWarning(text);
		}

		template <typename... Args>
		void LogError(const String& string, Args ... args)
		{
			std::string text = fmt::format(string.Str(), args...);
			LogError(text);
		}

		static ENGINE_API Logger* Instance();

	private:
		Logger();
		static void Shutdown();

		static Logger* _pInstance;

		enum LogPriority
		{
			Info,
			Warning,
			Error
		};

		LogPriority _logLevel;
		bool _logToFile;
		String _logFilePath;
		std::mutex _mutex;
	};
}
