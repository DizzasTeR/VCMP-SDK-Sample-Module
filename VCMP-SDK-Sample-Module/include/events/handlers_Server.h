#pragma once

uint8_t onServerInit() {
	Plugin::Log::INF("onServerInit :: Server initialized!");
	return 1;
}