#include "Shader.h"

MafiaBar::Engine::Graphics::Shader::Shader(MafiaBar::Engine::Graphics::Graphics& graphics, const MafiaBar::MafiaBarString& ShaderPathName, ShaderType shadertype)
	: Path(ShaderPathName.c_str())
{
	switch (shadertype)
	{
	case ShaderType::VertexShader:
		if (ReadFile(ShaderPathName) == true) { MB_GRAPHIC_EXCEPTION(graphics.GetDevice()->CreateVertexShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, &mVertexShader)); }
		else { Logger::Message("Mafia Bar Engine: Shader Class: Error", "Shader Class: Failed to read the Vertex Shader to Blob", MB_ICONERROR); }
		break;
	case ShaderType::PixelShader:
		if (ReadFile(ShaderPathName) == true) { MB_GRAPHIC_EXCEPTION(graphics.GetDevice()->CreatePixelShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, &mPixelShader)); }
		else { Logger::Message("Mafia Bar Engine: Shader Class: Error", "Shader Class: Failed to read the Pixel Shader to Blob", MB_ICONERROR); }
		break;
	case ShaderType::GeometryShader:
		//Didn't Setup Yet
		break;
	case ShaderType::HullShader:
		//Didn't Setup Yet
		break;
	}
}

const char* MafiaBar::Engine::Graphics::Shader::GetShaderPath() const { return Path; }

ID3DBlob* MafiaBar::Engine::Graphics::Shader::GetShaderBlob() const { return ShaderBlob.Get(); }

bool MafiaBar::Engine::Graphics::Shader::ReadFile(const MafiaBar::MafiaBarString& ShaderPath)
{
	#pragma message(__FILE__ "(" _CRT_STRINGIZE(__LINE__) ")"  ": warning: " "Fix this function, Improve")
	HRESULT hr = D3DReadFileToBlob(ShaderPath.GetWString().c_str(), &ShaderBlob);
	MB_GRAPHIC_EXCEPTION(hr);
	if (hr == S_FALSE) { return false; }
	else { return true; }
}

MafiaBar::Engine::Graphics::VertexShader::VertexShader(MafiaBar::Engine::Graphics::Graphics& graphics, const MafiaBar::MafiaBarString& VertexShaderPathName)
	: Shader(graphics, VertexShaderPathName, ShaderType::VertexShader)
{}

void MafiaBar::Engine::Graphics::VertexShader::Bind(MafiaBar::Engine::Graphics::Graphics& graphics) { graphics.GetContext()->VSSetShader(mVertexShader.Get(), nullptr, 0u); }

MafiaBar::Engine::Graphics::PixelShader::PixelShader(MafiaBar::Engine::Graphics::Graphics& graphics, const MafiaBar::MafiaBarString& PixelShaderPathName)
	: Shader(graphics, PixelShaderPathName, ShaderType::PixelShader)
{}

void MafiaBar::Engine::Graphics::PixelShader::Bind(MafiaBar::Engine::Graphics::Graphics & graphics) { graphics.GetContext()->PSSetShader(mPixelShader.Get(), nullptr, 0u); }
