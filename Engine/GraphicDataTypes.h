#pragma once
#include <DirectXMath.h>

namespace MafiaBar
{
	namespace Graphics
	{
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

