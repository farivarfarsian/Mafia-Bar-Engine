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

		/// <summary>
		/// Generating Component IDs for Using in ECS.
		/// </summary>
		class ComponentID
		{
		public:
			template <typename T>
			static int GetComponentID()
			{
				static int ComponentID = m_ComponentCounter++;
				return ComponentID;
			}
		private:
			static int m_ComponentCounter;
		};

		__declspec(selectany) int ComponentID::m_ComponentCounter;
	}
}
