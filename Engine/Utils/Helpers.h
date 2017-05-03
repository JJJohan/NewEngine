#pragma once

#include <comdef.h>
#include "../Core/Core.h"
#include "Logger.h"

namespace Engine
{
	static bool Failed(HRESULT task)
	{
		if (task < 0)
		{
			_com_error err(task);
			std::wstring wide = std::wstring(err.ErrorMessage());
			std::string errorString(wide.begin(), wide.end());
			Logger::Instance()->Log(errorString);

			return true;
		}

		return false;
	}

	static std::string GetRelativePath(const char* relativePath)
	{
		std::string appDirectory = Core::Instance()->GetApplicationDirectory();
		appDirectory.append(relativePath);
		return appDirectory;
	}

	static std::wstring GetRelativePath(const wchar_t* relativePath)
	{
		std::string appDirectory = Core::Instance()->GetApplicationDirectory();
		std::wstring wide = std::wstring(appDirectory.begin(), appDirectory.end());
		wide.append(relativePath);
		return wide;
	}
}
