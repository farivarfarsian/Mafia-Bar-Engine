#include "Shader.h"

MafiaBar::Engine::Graphics::Shader::Shader(const std::wstring& ShaderPathName, ShaderType shadertype)
	: Path(ShaderPathName.c_str())
{
	switch (shadertype)
	{
	case ShaderType::VertexShader:
		if (ReadFile(ShaderPathName) == true) { MB_EXCEPTION(Graphics->GetDevice()->CreateVertexShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, &mVertexShader)); }
		else { Logger::Message("Mafia Bar Engine: Shader Class: Error", "Shader Class: Failed to read the Vertex Shader to Blob", MB_ICONERROR); }
		break;
	case ShaderType::PixelShader:
		if (ReadFile(ShaderPathName) == true) { MB_EXCEPTION(Graphics->GetDevice()->CreatePixelShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, &mPixelShader)); }
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

const wchar_t* MafiaBar::Engine::Graphics::Shader::GetShaderPath() const { return Path; }

ID3DBlob* MafiaBar::Engine::Graphics::Shader::GetShaderBlob() const { return ShaderBlob.Get(); }

bool MafiaBar::Engine::Graphics::Shader::ReadFile(const std::wstring& ShaderPath)
{
	#pragma message(__FILE__ "(" _CRT_STRINGIZE(__LINE__) ")"  ": warning: " "Fix this function, Improve")
	HRESULT hr = D3DReadFileToBlob(ShaderPath.c_str(), &ShaderBlob);
	MB_EXCEPTION(hr);
	if (hr == S_FALSE) { return false; }
	else { return true; }
}

MafiaBar::Engine::Graphics::VertexShader::VertexShader(const std::wstring& VertexShaderPathName)
	: Shader(VertexShaderPathName, ShaderType::VertexShader)
{}

void MafiaBar::Engine::Graphics::VertexShader::Bind() { Graphics->GetContext()->VSSetShader(mVertexShader.Get(), nullptr, 0u); }

void MafiaBar::Engine::Graphics::VertexShader::Replace(const std::wstring& VertexShaderPathName)
{
	//Releasing the already existing data from the buffer and shader blob.
	mVertexShader->Release();
	ShaderBlob->Release();

	//Reading the new Shader to Blob
	if (ReadFile(VertexShaderPathName) == true)
	{
		//Creating the new VertexShaderBuffer
		DebugCode DEBUGCODE = Graphics->GetDevice()->CreateVertexShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, mVertexShader.GetAddressOf());
		MB_EXCEPTION(DEBUGCODE);
	}

	//Copying the VertexShader Path
	this->Path = VertexShaderPathName.c_str();
}

ID3D11VertexShader* MafiaBar::Engine::Graphics::VertexShader::GetVertexShader() const { return mVertexShader.Get(); }

MafiaBar::Engine::Graphics::PixelShader::PixelShader(const std::wstring& PixelShaderPathName)
	: Shader(PixelShaderPathName, ShaderType::PixelShader)
{}

void MafiaBar::Engine::Graphics::PixelShader::Bind() { Graphics->GetContext()->PSSetShader(mPixelShader.Get(), nullptr, 0u); }

void MafiaBar::Engine::Graphics::PixelShader::Replace(const std::wstring& PixelShaderPathName)
{
	//Releasing the already existing data from the buffer and shader blob.
	mVertexShader->Release();
	ShaderBlob->Release();

	//Reading the new Shader to Blob
	if (ReadFile(PixelShaderPathName) == true)
	{
		//Creating the new PixelShaderBuffer
		DebugCode DEBUGCODE = Graphics->GetDevice()->CreatePixelShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, mPixelShader.GetAddressOf());
		MB_EXCEPTION(DEBUGCODE);
	}

	//Copying the VertexShader Path
	this->Path = PixelShaderPathName.c_str();
}

ID3D11PixelShader* MafiaBar::Engine::Graphics::PixelShader::GetPixelShader() const { return mPixelShader.Get(); }
