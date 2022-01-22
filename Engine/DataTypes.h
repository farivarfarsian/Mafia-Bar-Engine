#pragma once
#include "Engine.h"
#include <codecvt>

namespace MafiaBar
{
	namespace DataTypes
	{
		class EXP_ENGINE MafiaBarString : public std::string
		{
		public:
			MafiaBarString() : std::string() {};
			MafiaBarString(const char* buf) : std::string(buf) {};
			MafiaBarString(const std::string& buf) : std::string(buf) {};
			std::wstring GetWString()
			{
				std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> ConvertWString;
				return ConvertWString.from_bytes(*this);
			}
			void ToLowerCase() { std::transform(begin(), end(), begin(), ::tolower); }
			void ToUpperCase() { std::transform(begin(), end(), begin(), ::toupper); }
		};
		class EXP_ENGINE MafiaBarWString : public std::wstring
		{
		public:
			MafiaBarWString() : std::wstring() {};
			MafiaBarWString(const wchar_t* buf) : std::wstring(buf) {};
			MafiaBarWString(const std::wstring& buf) : std::wstring(buf) {};
			std::string GetString()
			{
				std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> ConvertWString;
				return ConvertWString.to_bytes(*this);
			}
			void ToLowerCase() { std::transform(begin(), end(), begin(), ::tolower); }
			void ToUpperCase() { std::transform(begin(), end(), begin(), ::toupper); }
		};
		struct Vertex
		{
			struct
			{
				float x;
				float y;
				float z;
			} position;
		};
		struct ConstantBuffer
		{
			DirectX::XMMATRIX transform;
		};
		struct ConstantBuffer2
		{
			struct
			{
				float r;
				float g;
				float b;
				float a;
			} face_colors[6];
		};
	}
}
