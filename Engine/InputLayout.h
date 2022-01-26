#pragma once
#include "Engine.h"
#include "Bindable.h"


namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class EXP_ENGINE InputLayout : public Bindable
			{
			public:
				InputLayout(MafiaBar::Engine::Graphics::Graphics& graphics, const MafiaBar::SDK::Vector<D3D11_INPUT_ELEMENT_DESC>& InputLayout, ID3DBlob* VertexShaderBlob);
				void Bind(MafiaBar::Engine::Graphics::Graphics& graphics) override;
			private:
				Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;
			};
		}
	}
}
