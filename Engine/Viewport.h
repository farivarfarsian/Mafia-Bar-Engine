#pragma once
#include "Engine.h"
#include "Bindable.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class EXP_ENGINE Viewport : public Bindable
			{
			public:
				Viewport(MafiaBar::Engine::Graphics::Graphics& graphics);
				Viewport(MafiaBar::Engine::Graphics::Graphics& graphics, float Width, float Height);
				void Bind(MafiaBar::Engine::Graphics::Graphics& graphics) override;
			public:
				D3D11_VIEWPORT GetViewport() const;
			private:
				D3D11_VIEWPORT mViewport;
			};
		}
	}
}
