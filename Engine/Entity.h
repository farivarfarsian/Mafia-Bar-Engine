#pragma once
#include "Graphics.h"
#include "Component.h"
#include "UUID.h"

namespace MafiaBar
{
	namespace Engine
	{
		class MB_ENGINE_API Entity
		{
		public:
			Entity() = default;
			virtual ~Entity() = default;
		public:
			virtual void Input();
			virtual void Update(float DeltaTime);
			virtual void Draw(Graphics::Graphics& Graphics);
			template<typename T>
			void Assign(const Component& Component)
			{
				int ComponentID = ComponentID::GetComponentID<T>();
				Components.EmplaceBack((void*)(&Component));
			}
		public:
			MafiaBar::SDK::Vector<void*> GetComponents() const;
			EntityID GetEntityID() const;
			template<typename T>
			T* GetComponent() const
			{
				int ComponentID = ComponentID::GetComponentID<T>();
				return static_cast<T*>(Components[ComponentID]);
			}
		protected:
			MafiaBar::SDK::Vector<void*> Components; //For some reason it doesn't work by Component or Component*, it can't store the components correctly and their memory address get lost. TODO: Fix this problem.
			EntityID EntityID = MafiaBar::Engine::UUID::GetUUID();
		};
	}
}