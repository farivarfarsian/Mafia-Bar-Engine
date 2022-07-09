#pragma once
#include "def.h"
#include "pch.h"

#include "Graphics.h"
#include "Entity.h"

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
			void SetSceneClearColor(const float ClearRenderColor[4]);
			void SetSceneClearColor(float R, float G, float B, float A);
			void SetSceneProjection(const DirectX::FXMMATRIX& Projection);
			void Render();
		public:
			DirectX::XMMATRIX GetSceneProjection() const;
			const float* GetSceneClearColor() const;
		private:
			DirectX::XMMATRIX m_SceneProjection;
			float m_SceneClearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
			MafiaBar::Engine::Graphics::Graphics* m_Graphics;
		};
	}
}