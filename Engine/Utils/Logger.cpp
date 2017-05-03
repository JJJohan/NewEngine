#include "Win32Utils.h"
#include "Helpers.h"
#include "Logger.h"
#include "Console.h"
#include <iostream>
#include "../Core/Lua.h"

namespace Engine
{
	Logger* Logger::_pInstance = nullptr;

	Logger::Logger()
		: _logLevel(Info)
		, _logToFile(true)
	{
		_logFilePath = GetRelativePath("");
	}

	Logger::~Logger()
	{
		if (_pInstance != nullptr)
		{
			delete _pInstance;
			_pInstance = nullptr;
		}
	}

	Logger* Logger::Instance()
	{
		if (_pInstance == nullptr)
		{
			_pInstance = new Logger();
		}

		return _pInstance;
	}
	
	void Logger::LogError(const std::string& message)
	{
		_logLevel = Error;
		Log(message);
		Win32Utils::ShowMessageBox(message, "Error");
	}

	void Logger::LogWarning(const std::string& message)
	{
		_logLevel = Warning;
		Log(message);
	}

	void Logger::Log(const std::string& message)
	{
		std::lock_guard<std::mutex> lock(_mutex);

#ifdef _DEBUG
		Console::ConsoleColour currentColour = Console::GetTextColour();
#endif

		std::string outString = message;
		if (_logLevel == Error)
		{
			outString = "[ERROR] " + outString;
#ifdef _DEBUG
			Console::SetColour(Console::ConsoleColour::Red);
#endif
		}
		else if (_logLevel == Warning)
		{
			outString = "[WARNING] " + outString;

#ifdef _DEBUG
			Console::SetColour(Console::ConsoleColour::Yellow);
#endif
		}

		std::cout << outString << std::endl;

#ifdef _DEBUG
		std::string output = outString + "\n";
		std::wstring outputW = std::wstring(output.begin(), output.end());
		OutputDebugString(outputW.c_str());
		Console::SetColour(currentColour);
#endif
		_logLevel = Info;
	}

	void Logger::LogWin32Error()
	{
		DWORD errorCode = GetLastError();
		std::string errorString = GetWin32ErrorString();
		if (!errorString.empty())
		{
			std::cout << "Error " << errorCode << ": " << errorString << std::endl;
		}
	}

	//Returns the last Win32 error, in string format. Returns an empty string if there is no error.
	String Logger::GetWin32ErrorString()
	{
		DWORD errorCode = GetLastError();
		if (errorCode == 0)
		{
			return std::string();
		}

		LPSTR messageBuffer = nullptr;
		size_t size = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), LPWSTR(&messageBuffer), 0, nullptr);

		std::string message(messageBuffer, size);

		//Free the buffer.
		LocalFree(messageBuffer);

		return message;
	}

	//Returns a COM error message.
	String Logger::GetCOMError(const _com_error& error, const String& caller)
	{
		return String(caller + ": " + error.ErrorMessage());
	}

	void Logger::EnableFileLogging(bool enabled)
	{
		_logToFile = enabled;
	}

	void Logger::SetLogPath(const std::string& filePath)
	{
		_logFilePath = filePath;
	}
}
