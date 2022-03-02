#include "InputLayout.h"

MafiaBar::Engine::Graphics::InputLayout::InputLayout(MafiaBar::Engine::Graphics::Graphics& graphics, const MafiaBar::SDK::Vector<D3D11_INPUT_ELEMENT_DESC>& InputLayout, ID3DBlob* VertexShaderBlob) { MB_EXCEPTION(graphics.GetDevice()->CreateInputLayout(InputLayout.GetData(), (unsigned int)InputLayout.GetSize(), VertexShaderBlob->GetBufferPointer(), VertexShaderBlob->GetBufferSize(), &mInputLayout)); }

void MafiaBar::Engine::Graphics::InputLayout::Bind(MafiaBar::Engine::Graphics::Graphics& graphics) { graphics.GetContext()->IASetInputLayout(mInputLayout.Get()); }
