#pragma once

namespace Engine
{
	class IRegisteredClass
	{
	public:
		virtual ~IRegisteredClass() = default;
		virtual void Register() = 0;
	};
}