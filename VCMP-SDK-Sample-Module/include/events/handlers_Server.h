#pragma once
#include <thread>

extern PluginFuncs* g_Funcs;

namespace ServerMessages {
	std::thread* thread;
	std::vector<std::string> g_vector_InfoMessages = {
		"Msg 1",
		"Msg 2",
		"Msg 3"
	};
	std::vector<std::string>::const_iterator g_vit_InfoMessages = g_vector_InfoMessages.begin();
	
	void onMessageAnnounce() {
		using namespace ServerMessages;
		while (true) {
			if (g_vit_InfoMessages == g_vector_InfoMessages.end())
				g_vit_InfoMessages = g_vector_InfoMessages.begin();

			Plugin::Player::MessageToAll(g_vit_InfoMessages->c_str());
			Plugin::Log::INF(g_vit_InfoMessages->c_str());
			g_vit_InfoMessages++;

			using namespace std::literals::chrono_literals;
			std::this_thread::sleep_for(1min);
		}
	}
}

uint8_t onServerInit() {
	g_Funcs->SetServerName("Doom_Kill3R's Development Server");
	g_Funcs->SetGameModeText("D-SDK v1.0 (C++)");
	g_Funcs->SetServerPassword("DDev");
	//

	ServerMessages::thread = new std::thread([]() { std::thread(ServerMessages::onMessageAnnounce).join(); });
	
	//
	Plugin::Log::INF("onServerInit :: Server initialized!");
	return 1;
} 