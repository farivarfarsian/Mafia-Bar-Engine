#pragma once
#include "Bindable.h"


namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class MB_ENGINE_API InputLayout : public Bindable
			{
			public:
				InputLayout(const MafiaBar::SDK::Vector<D3D11_INPUT_ELEMENT_DESC>& InputLayout, ID3DBlob* VertexShaderBlob);
				void Bind() override;
				/// <summary>
				///  Replaces the old InputLayout with the new one.
				/// </summary>
				void Replace(const MafiaBar::SDK::Vector<D3D11_INPUT_ELEMENT_DESC>& InputLayout, ID3DBlob* VertexShaderBlob);
			public:
				ID3D11InputLayout* GetInputLayout() const;
			private:
				Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;
			};
		}
	}
}
