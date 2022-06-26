#include "Topology.h"
#include "Viewport.h"

MafiaBar::Engine::Graphics::Topology::Topology(D3D_PRIMITIVE_TOPOLOGY Topolgy)
	: mTopolgyType(Topolgy)
{
}

void MafiaBar::Engine::Graphics::Topology::Bind(MafiaBar::Engine::Graphics::Graphics& graphics) { graphics.GetContext()->IASetPrimitiveTopology(mTopolgyType); }

void MafiaBar::Engine::Graphics::Topology::Replace(Graphics& Graphics, const D3D_PRIMITIVE_TOPOLOGY& TopolgyType) { this->mTopolgyType = TopolgyType; }

