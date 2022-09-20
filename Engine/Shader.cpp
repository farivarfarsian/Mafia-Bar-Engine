#include "Shader.h"

const wchar_t* MafiaBar::Engine::Graphics::Shader::GetShaderPath() const { return Path; }

ID3DBlob* MafiaBar::Engine::Graphics::Shader::GetShaderBlob() const { return ShaderBlob.Get(); }

bool MafiaBar::Engine::Graphics::Shader::ReadFile(const std::wstring& ShaderPath)
{
	HRESULT hr = D3DReadFileToBlob(ShaderPath.c_str(), &ShaderBlob);
	MB_EXCEPTION(hr);
	if (hr == S_FALSE) { return false; }
	else { return true; }
}

MafiaBar::Engine::Graphics::VertexShader::VertexShader(const std::wstring& VertexShaderPathName)
{
	if (ReadFile(VertexShaderPathName) == true) { MB_EXCEPTION(Graphics->GetDevice()->CreateVertexShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, &mVertexShader)); }
	else { Logger::Message("Mafia Bar Engine: Shader Class: Error", "Shader Class: Failed to read the Vertex Shader to Blob", MB_ICONERROR); }
	SetDebugCOMObjectName(mVertexShader.Get(), "Vertex Shader Bindable");
}

void MafiaBar::Engine::Graphics::VertexShader::Bind() { Graphics->GetContext()->VSSetShader(mVertexShader.Get(), NULL, 0); }

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
{
	if (ReadFile(PixelShaderPathName) == true) { MB_EXCEPTION(Graphics->GetDevice()->CreatePixelShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, &mPixelShader)); }
	else { Logger::Message("Mafia Bar Engine: Shader Class: Error", "Shader Class: Failed to read the Pixel Shader to Blob", MB_ICONERROR); }
	SetDebugCOMObjectName(mPixelShader.Get(), "Pixel Shader Bindable");
}

void MafiaBar::Engine::Graphics::PixelShader::Bind() { Graphics->GetContext()->PSSetShader(mPixelShader.Get(), nullptr, 0u); }

void MafiaBar::Engine::Graphics::PixelShader::Replace(const std::wstring& PixelShaderPathName)
{
	//Releasing the already existing data from the buffer and shader blob.
	mPixelShader->Release();
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
