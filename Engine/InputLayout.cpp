#include "InputLayout.h"

MafiaBar::Engine::Graphics::InputLayout::InputLayout(const MafiaBar::SDK::Vector<D3D11_INPUT_ELEMENT_DESC>& InputLayout, ID3DBlob* VertexShaderBlob) 
{ 
	MB_EXCEPTION(Graphics->GetDevice()->CreateInputLayout(InputLayout.GetData(), (unsigned int)InputLayout.GetSize(), VertexShaderBlob->GetBufferPointer(), VertexShaderBlob->GetBufferSize(), &mInputLayout));
}

void MafiaBar::Engine::Graphics::InputLayout::Bind() { Graphics->GetContext()->IASetInputLayout(mInputLayout.Get()); }

void MafiaBar::Engine::Graphics::InputLayout::Replace(const MafiaBar::SDK::Vector<D3D11_INPUT_ELEMENT_DESC>& InputLayout, ID3DBlob* VertexShaderBlob)
{
	//Releasing the already existing data from the buffer.
	mInputLayout->Release();

	//Creating the new InputLayout
	DebugCode DEBUGCODE = Graphics->GetDevice()->CreateInputLayout(InputLayout.GetData(), (unsigned int)InputLayout.GetSize(), VertexShaderBlob->GetBufferPointer(), VertexShaderBlob->GetBufferSize(), mInputLayout.GetAddressOf());

	if (DEBUGCODE != S_OK)
	{
		MB_EXCEPTION(DEBUGCODE);
	}
}

ID3D11InputLayout* MafiaBar::Engine::Graphics::InputLayout::GetInputLayout() const { return mInputLayout.Get(); }
