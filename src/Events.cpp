#pragma once
#include "Events.h"
#include "oxyMeter.h"
#include "Settings.h"
#include "RE/U/UI.h"
#include "string.h"

MenuOpenCloseEventHandler* MenuOpenCloseEventHandler::GetSingleton()
{
	static MenuOpenCloseEventHandler singleton;
	return std::addressof(singleton);
}

void MenuOpenCloseEventHandler::Register()
{
	auto ui = RE::UI::GetSingleton();
	ui->AddEventSink<RE::MenuOpenCloseEvent>(GetSingleton());
	logger::info("Registered {}"sv, typeid(RE::MenuOpenCloseEvent).name());
}

RE::BSEventNotifyControl MenuOpenCloseEventHandler::ProcessEvent(const RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*)
{
<<<<<<< HEAD
	// from ersh TrueHud pretty much verbatim
	if (a_event)
		logger::debug("Received RE::MenuOpenCloseEvent for {} with opening {}"sv, a_event->menuName, a_event->opening);

	using ContextID = RE::UserEvents::INPUT_CONTEXT_ID;
	// On HUD menu open/close - open/close the plugin's HUD menu
	if (a_event && (a_event->menuName == RE::HUDMenu::MENU_NAME || a_event->menuName == "TrueHUD"sv)) {
		if (a_event->opening) {
=======
	auto ui = RE::UI::GetSingleton();
	if (a_event) {
		logger::info("Menu: {} :: {}",a_event->menuName.c_str(), a_event->opening ? "opening" : "closing");
		if (a_event->menuName == RE::HUDMenu::MENU_NAME) {
			if (a_event->opening) {
				oxygenMenu::Show();
			} else {
				oxygenMenu::Hide();
			}
		} else if (a_event->menuName == RE::RaceSexMenu::MENU_NAME && !a_event->opening) {
			oxygenMenu::Show();
			logger::info("showing menu when racemenu closes");
		} else if (a_event->menuName == RE::LoadingMenu::MENU_NAME && !a_event->opening) {
>>>>>>> master
			oxygenMenu::Show();
		} else {
			oxygenMenu::Hide();
		}
<<<<<<< HEAD
=======
		if (a_event->menuName == RE::ContainerMenu::MENU_NAME && !a_event->opening && !ui->IsMenuOpen("PluginExplorerMenu")) {
			oxygenMenu::Show();
		}
		if (a_event->menuName == RE::JournalMenu::MENU_NAME) {
			Settings::GetSingleton()->Load();
		}
>>>>>>> master
	}

	// Hide the widgets when a menu is open
	auto controlMap = RE::ControlMap::GetSingleton();
	if (controlMap) {
		auto& priorityStack = controlMap->contextPriorityStack;
		if (priorityStack.empty()) {
			oxygenMenu::want_visible = false;
		}
		else if (priorityStack.back() == ContextID::kGameplay ||
				 priorityStack.back() == ContextID::kFavorites ||
				 priorityStack.back() == ContextID::kConsole) 
		{
			oxygenMenu::want_visible = true;
		} else {
			oxygenMenu::want_visible = false;
		}
	}

	return RE::BSEventNotifyControl::kContinue;
}
