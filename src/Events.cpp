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
	// from ersh TrueHud pretty much verbatim
	if (a_event)
		logger::debug("Received RE::MenuOpenCloseEvent for {} with opening"sv, a_event->menuName);

	// On HUD menu open/close - open/close the plugin's HUD menu
	if (a_event && (a_event->menuName == RE::HUDMenu::MENU_NAME || a_event->menuName == "TrueHUD"sv)) {
		if (a_event->opening) {
			oxygenMenu::Show();
		} else {
			oxygenMenu::Hide();
		}
	}

	// Hide the widgets when a menu is open
	auto controlMap = RE::ControlMap::GetSingleton();
	if (controlMap) {
		auto& priorityStack = controlMap->contextPriorityStack;
		if (priorityStack.empty()) {
			oxygenMenu::want_visible = false;
		} else if (priorityStack.back() == RE::UserEvents::INPUT_CONTEXT_ID::kGameplay ||
				   priorityStack.back() == RE::UserEvents::INPUT_CONTEXT_ID::kFavorites ||
				   priorityStack.back() == RE::UserEvents::INPUT_CONTEXT_ID::kConsole) 
		{
			oxygenMenu::want_visible = true;
		} else {
			oxygenMenu::want_visible = false;
		}
	}

	return RE::BSEventNotifyControl::kContinue;
}
