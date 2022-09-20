#pragma once
#include "Bindable.h"

#include "Logger.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class MB_ENGINE_API Shader : public Bindable
			{
			public:
				Shader() = default; //Used in Inheritances of Shader Class 
				virtual ~Shader() = default;
			public:
				const wchar_t* GetShaderPath() const;
				ID3DBlob* GetShaderBlob() const;
			protected:
				const wchar_t* Path = nullptr;
				Microsoft::WRL::ComPtr<ID3DBlob> ShaderBlob = nullptr;
				bool ReadFile(const std::wstring& ShaderPath);
			};

			class MB_ENGINE_API VertexShader : public Shader
			{
			public:
				VertexShader(const std::wstring& VertexShaderPathName);
				~VertexShader() = default;
				void Bind() override;
				/// <summary>
				///  Replaces the old VertexShader with the new one.
				/// </summary>
				void Replace(const std::wstring& VertexShaderPathName);
			public:
				ID3D11VertexShader* GetVertexShader() const;
			private:
				Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader = nullptr;
			};

			class MB_ENGINE_API PixelShader : public Shader
			{
			public:
				PixelShader(const std::wstring& PixelShaderPathName);
				~PixelShader() = default;
				void Bind() override;
				/// <summary>
				///  Replaces the old PixelShader with the new one.
				/// </summary>
				void Replace(const std::wstring& PixelShaderPathName);
			public:
				ID3D11PixelShader* GetPixelShader() const;
			private:
				Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader = nullptr;
			};
		}
	}
}