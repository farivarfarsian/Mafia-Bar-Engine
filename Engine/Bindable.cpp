#include "Bindable.h"
#include "Engine.h"

MafiaBar::Engine::Graphics::Bindable::Bindable() : Graphics(&MafiaBar::Engine::Engine::Get().GetGraphics()) //Setting The Graphics Pointer For All Bindables to Use.
{

}