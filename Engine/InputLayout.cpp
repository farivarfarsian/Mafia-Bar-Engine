#include "InputLayout.h"

MafiaBar::Engine::Graphics::InputLayout::InputLayout(MafiaBar::Engine::Graphics::Graphics& graphics, const std::vector<D3D11_INPUT_ELEMENT_DESC>& InputLayout, ID3DBlob* VertexShaderBlob) { MB_GRAPHIC_EXCEPTION(graphics.GetDevice()->CreateInputLayout(InputLayout.data(), (unsigned int)InputLayout.size(), VertexShaderBlob->GetBufferPointer(), VertexShaderBlob->GetBufferSize(), &mInputLayout)); }

void MafiaBar::Engine::Graphics::InputLayout::Bind(MafiaBar::Engine::Graphics::Graphics& graphics) { graphics.GetContext()->IASetInputLayout(mInputLayout.Get()); }
