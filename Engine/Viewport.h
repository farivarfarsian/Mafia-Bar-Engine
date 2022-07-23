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
				Viewport();
				Viewport(float Width, float Height);
				void Bind() override;
				/// <summary>
				///  Replaces the old Viewport with the new one.
				/// </summary>
				void Replace(const D3D11_VIEWPORT& Viewport);
			public:
				D3D11_VIEWPORT GetViewport() const;
			private:
				D3D11_VIEWPORT mViewport;
			};
		}
	}
}
