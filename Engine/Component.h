#pragma once
#include "def.h"
#include <DirectXMath.h>

namespace MafiaBar
{
	namespace Engine
	{
		/// <summary>
		/// Component structure is needed for all the Components that will be derived in Entity Component classes like Transform, Mesh and etc.
		/// </summary>
		struct MB_ENGINE_API Component
		{
		public:
			Component();
			virtual const char* GetName() const;
			virtual ~Component();
		};
	}
}
