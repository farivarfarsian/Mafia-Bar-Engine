#pragma once
#include "def.h"
#include "pch.h"

#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

namespace MafiaBar
{
	namespace Engine
	{
		class MB_ENGINE_API UI final
		{
		public:
			UI();
			~UI();
			void Initialize(HWND Handle, ID3D11Device* Device, ID3D11DeviceContext* Context, bool LightMode);
			void NewFrame();
			void Render();
		};
	}
}