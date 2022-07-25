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
			void Assign(const std::shared_ptr<Component>& Component)
			{
				int ComponentID = ComponentID::GetComponentID<T>();
				Components.EmplaceBack(Component);
			}
		public:
			MafiaBar::SDK::Vector<std::shared_ptr<Component>> GetComponents() const;
			EntityID GetEntityID() const;
			template<typename T>
			T* GetComponent() const
			{
				int ComponentID = ComponentID::GetComponentID<T>();
				return static_cast<T*>(Components[ComponentID].get());
			}
		protected:
			MafiaBar::SDK::Vector<std::shared_ptr<Component>> Components;
			EntityID EntityID = MafiaBar::Engine::UUID::GetUUID();
		};
	}
}