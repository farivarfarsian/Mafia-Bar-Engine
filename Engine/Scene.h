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
			void Clear(const float ClearRenderColor[4], float ClearDepthBuffer, UINT8 ClearStencilBuffer);
			void Clear(float R, float G, float B, float A, float ClearDepthBuffer, UINT8 ClearStencilBuffer);
			void SetSceneProjection(const DirectX::FXMMATRIX& Projection);
			void Render();
		public:
			DirectX::XMMATRIX GetSceneProjection() const;
		private:
			DirectX::XMMATRIX m_SceneProjection;
			MafiaBar::Engine::Graphics::Graphics* m_Graphics;
		};
	}
}