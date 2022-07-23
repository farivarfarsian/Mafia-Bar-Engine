#pragma once
#include "Graphics.h"
#include "Entity.h"
#include "UUID.h"

#include <unordered_map>

namespace MafiaBar
{
	namespace Engine
	{
		class MB_ENGINE_API Scene final
		{
		public:
			Scene() = default;
			Scene(const Scene&) = delete;
			Scene& operator=(const Scene&) = delete;
			~Scene() = default;
		public:
			void Initialize(MafiaBar::Engine::Graphics::Graphics* Graphics);
			void Clear(float ClearDepthBuffer, UINT8 ClearStencilBuffer);
			void NewFrame();
			void Render();
			void AddEntity(const std::shared_ptr<Entity>& Entity);
			void AddEntity(std::shared_ptr<Entity>&& Entity);
			void DeleteEntity(EntityID EntityID);
			Entity* GetEntity(EntityID EntityID);
		public: //Setters
			void SetSceneClearColor(const float ClearRenderColor[4]);
			void SetSceneClearColor(float R, float G, float B, float A);
			void SetSceneProjection(const DirectX::FXMMATRIX& Projection);
		public: //Getters
			DirectX::XMMATRIX GetSceneProjection() const;
			const float* GetSceneClearColor() const;
			float GetDeltaTime() const;
		private:
			DirectX::XMMATRIX m_SceneProjection;
			float m_SceneClearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
			float m_DeltaTime = 1.0f / 60.0f;
			MafiaBar::Engine::Graphics::Graphics* m_Graphics;
			std::unordered_map<UUID, std::shared_ptr<Entity>> Entities;
		}; //TODO: For Entities Use the Custom Smart Pointer Type.
	}
}