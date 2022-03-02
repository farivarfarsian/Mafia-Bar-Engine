#pragma once
#include "Bindable.h"
#include "MafiaBarString.h"
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
				Shader(MafiaBar::Engine::Graphics::Graphics& graphics, const MafiaBar::MafiaBarString& ShaderPathName, ShaderType shadertype);
			public:
				const char* GetShaderPath() const;
				ID3DBlob* GetShaderBlob() const;
			protected:
				const char* Path;
				Microsoft::WRL::ComPtr<ID3DBlob> ShaderBlob;
				Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;
				Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;
				Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGeometryShader;
				Microsoft::WRL::ComPtr<ID3D11HullShader> mHullShader;
			private:
				bool ReadFile(const MafiaBar::MafiaBarString& ShaderPath);
			};

			class MB_ENGINE_API VertexShader : public Shader
			{
			public:
				VertexShader(MafiaBar::Engine::Graphics::Graphics& graphics, const MafiaBar::MafiaBarString& VertexShaderPathName);
				void Bind(MafiaBar::Engine::Graphics::Graphics& graphics) override;
			};

			class MB_ENGINE_API PixelShader : public Shader
			{
			public:
				PixelShader(MafiaBar::Engine::Graphics::Graphics& graphics, const MafiaBar::MafiaBarString& PixelShaderPathName);
				void Bind(MafiaBar::Engine::Graphics::Graphics& graphics) override;
			};
		}
	}
}