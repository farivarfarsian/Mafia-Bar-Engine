#pragma once
#include "def.h"
#include "pch.h"

namespace MafiaBar
{
	namespace Engine
	{
		
		struct MB_ENGINE_API UUID final
		{
		public:
			UUID();
			UUID(unsigned long long UUID);
			~UUID();
		public:
			operator unsigned long long() const;
			static UUID GetUUID();
		private:
			unsigned long long m_UUID;
		};
		//UUID structure has been created to be used everywhere not only for Entities.
	}
}

//Compatibility of the UUID stucture with Hashmaps.
namespace std
{
	template<>
	struct std::hash<MafiaBar::Engine::UUID>
	{
		std::size_t operator()(const MafiaBar::Engine::UUID& UUID) const noexcept
		{
			return UUID;
		}
	};
}
