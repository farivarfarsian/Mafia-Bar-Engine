#pragma once
#include "Bindable.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class MB_ENGINE_API Viewport : public Bindable
			{
			public:
				Viewport(MafiaBar::Engine::Graphics::Graphics& graphics);
				Viewport(MafiaBar::Engine::Graphics::Graphics& graphics, float Width, float Height);
				void Bind(MafiaBar::Engine::Graphics::Graphics& graphics) override;
				/// <summary>
				///  Replaces the old Viewport with the new one.
				/// </summary>
				void Replace(Graphics& Graphics, const D3D11_VIEWPORT& Viewport);
			public:
				D3D11_VIEWPORT GetViewport() const;
			private:
				D3D11_VIEWPORT mViewport;
			};
		}
	}
}
