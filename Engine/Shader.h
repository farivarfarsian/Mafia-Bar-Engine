#pragma once
#include "Bindable.h"

#include "Logger.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			enum class ShaderType
			{
				VertexShader,
				PixelShader,
				GeometryShader,
				HullShader,
			};
			class MB_ENGINE_API Shader : public Bindable
			{
			public:
				Shader() = default; //Used in Inheritances of Shader Class 
				Shader(const std::wstring& ShaderPathName, ShaderType shadertype);
			public:
				const wchar_t* GetShaderPath() const;
				ID3DBlob* GetShaderBlob() const;
			protected:
				const wchar_t* Path;
				Microsoft::WRL::ComPtr<ID3DBlob> ShaderBlob;
				Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;
				Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;
				Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGeometryShader;
				Microsoft::WRL::ComPtr<ID3D11HullShader> mHullShader;
				bool ReadFile(const std::wstring& ShaderPath);
			};

			class MB_ENGINE_API VertexShader : public Shader
			{
			public:
				VertexShader( const std::wstring& VertexShaderPathName);
				void Bind() override;
				/// <summary>
				///  Replaces the old VertexShader with the new one.
				/// </summary>
				void Replace(const std::wstring& VertexShaderPathName);
			public:
				ID3D11VertexShader* GetVertexShader() const;
			};

			class MB_ENGINE_API PixelShader : public Shader
			{
			public:
				PixelShader(const std::wstring& PixelShaderPathName);
				void Bind() override;
				/// <summary>
				///  Replaces the old PixelShader with the new one.
				/// </summary>
				void Replace(const std::wstring& PixelShaderPathName);
			public:
				ID3D11PixelShader* GetPixelShader() const;
			};
		}
	}
}