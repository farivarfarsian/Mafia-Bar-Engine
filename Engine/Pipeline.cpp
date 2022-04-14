#include "Pipeline.h"

void MafiaBar::Engine::Graphics::Pipeline::BindThePipline(Graphics& Graphics) { for (auto& Bindable : Bindables) { Bindable->Bind(Graphics); } }

void MafiaBar::Engine::Graphics::Pipeline::AddBindable(Bindable* Bind) { Bindables.EmplaceBack(Bind); }

constexpr bool MafiaBar::Engine::Graphics::Pipeline::IsStaticBindablesInitialized() { return !StaticBindables.Empty(); }

void MafiaBar::Engine::Graphics::Pipeline::AddStaticBindable(Bindable* Bind) { StaticBindables.EmplaceBack(Bind); }

void MafiaBar::Engine::Graphics::Pipeline::BindTheStaticPipline(Graphics& Graphics) { for (auto& Bindable : StaticBindables) { Bindable->Bind(Graphics); } }

MafiaBar::Engine::Graphics::Pipeline::~Pipeline() { for (auto& Bindable : Bindables) { delete Bindable; } }

MafiaBar::SDK::Vector<MafiaBar::Engine::Graphics::Bindable*> MafiaBar::Engine::Graphics::Pipeline::StaticBindables;

