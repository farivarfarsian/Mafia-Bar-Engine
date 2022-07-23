#include "Pipeline.h"

void MafiaBar::Engine::Graphics::Pipeline::BindThePipline() { for (auto& Bindable : Bindables) { Bindable->Bind(); } }

void MafiaBar::Engine::Graphics::Pipeline::AddBindable(const std::shared_ptr<Bindable>& Bind) { Bindables.EmplaceBack(Bind); }

void MafiaBar::Engine::Graphics::Pipeline::AddBindable(std::shared_ptr<Bindable>&& Bind) { Bindables.EmplaceBack(std::move(Bind)); }

constexpr bool MafiaBar::Engine::Graphics::Pipeline::IsStaticBindablesInitialized() { return !StaticBindables.Empty(); }

void MafiaBar::Engine::Graphics::Pipeline::AddStaticBindable(const std::shared_ptr<Bindable>& Bind) { StaticBindables.EmplaceBack(Bind); }

void MafiaBar::Engine::Graphics::Pipeline::AddStaticBindable(std::shared_ptr<Bindable>&& Bind) { StaticBindables.EmplaceBack(std::move(Bind)); }

void MafiaBar::Engine::Graphics::Pipeline::BindTheStaticPipline() { for (auto& Bindable : StaticBindables) { Bindable->Bind(); } }

MafiaBar::SDK::Vector<std::shared_ptr<MafiaBar::Engine::Graphics::Bindable>> MafiaBar::Engine::Graphics::Pipeline::StaticBindables;

