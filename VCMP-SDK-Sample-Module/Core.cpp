#include "pch.h"
#include <Signals.h>
#include <Utils.h>

#include <events/hooks.h>

PluginFuncs* g_Funcs;
PluginCallbacks* g_Calls;
PluginInfo* g_Info;

HSQUIRRELVM sqvm;
HSQAPI sqapi;

void BindHandlers();
uint8_t OnInternalCommand(uint32_t uCmdType, const char* pszText);

extern "C" EXPORT unsigned int VcmpPluginInit(PluginFuncs* pluginFuncs, PluginCallbacks* pluginCalls, PluginInfo* pluginInfo) {
	g_Funcs = pluginFuncs;
	g_Calls = pluginCalls;
	g_Info = pluginInfo;

	pluginInfo->pluginVersion = 0x1001;
	pluginInfo->apiMajorVersion = PLUGIN_API_MAJOR;
	pluginInfo->apiMinorVersion = PLUGIN_API_MINOR;

	pluginCalls->OnPluginCommand = OnInternalCommand;

	pluginCalls->OnServerInitialise = []() {
		signal_onServerInitalize();
		return (uint8_t)1;
	};
	pluginCalls->OnServerShutdown = []() {
		signal_onServerShutdown();
	};
	pluginCalls->OnServerFrame = [](float) {
		signal_onServerShutdown();
	};

	pluginCalls->OnIncomingConnection = [](char* _1, size_t _2, const char* _3, const char* _4) {
		signal_onPlayerConnection(_1, _2, _3, _4);
		return (uint8_t)1;
	};
	pluginCalls->OnClientScriptData = [](int32_t playerId, const uint8_t* data, size_t size) {
		signal_onClientScriptData(playerId, data, size);
	};

	pluginCalls->OnPlayerConnect = [](int32_t playerId) {
		signal_onPlayerConnect(playerId);
	};
	pluginCalls->OnPlayerDisconnect = [](int32_t playerId, vcmpDisconnectReason reason) {
		signal_onPlayerDisconnect(playerId, reason);
	};
	pluginCalls->OnPlayerModuleList = [](int32_t playerId, const char* list) {
		signal_onPlayerModuleList(playerId, list);
	};

	pluginCalls->OnPlayerRequestClass = [](int32_t playerId, int32_t offset) {
		signal_onPlayerRequestClass(playerId, offset);
		return (uint8_t)1;
	};
	pluginCalls->OnPlayerRequestSpawn = [](int32_t playerId) {
		signal_onPlayerRequestSpawn(playerId);
		return (uint8_t)1;
	};
	pluginCalls->OnPlayerSpawn = [](int32_t playerId) {
		signal_onPlayerSpawn(playerId);
	};
	pluginCalls->OnPlayerDeath = [](int32_t playerId, int32_t killerId, int32_t reason, vcmpBodyPart bodyPart) {
		signal_onPlayerDeath(playerId, killerId, reason, bodyPart);
	};
	pluginCalls->OnPlayerUpdate = [](int32_t playerId, vcmpPlayerUpdate updateType) {
		signal_onPlayerUpdate(playerId, updateType);
	};

	pluginCalls->OnPlayerRequestEnterVehicle = [](int32_t playerId, int32_t vehicleId, int32_t slotIndex) {
		signal_onPlayerRequestEnterVehicle(playerId, vehicleId, slotIndex);
		return (uint8_t)1;
	};
	pluginCalls->OnPlayerEnterVehicle = [](int32_t playerId, int32_t vehicleId, int32_t slotIndex) {
		signal_onPlayerEnterVehicle(playerId, vehicleId, slotIndex);
	};
	pluginCalls->OnPlayerExitVehicle = [](int32_t playerId, int32_t vehicleId) {
		signal_onPlayerExitVehicle(playerId, vehicleId);
	};

	pluginCalls->OnPlayerNameChange = [](int32_t playerId, const char* oldName, const char* newName) {
		signal_onPlayerNameChange(playerId, oldName, newName);
	};
	pluginCalls->OnPlayerStateChange = [](int32_t playerId, vcmpPlayerState oldState, vcmpPlayerState newState) {
		signal_onPlayerStateChange(playerId, oldState, newState);
	};
	pluginCalls->OnPlayerActionChange = [](int32_t playerId, int32_t oldAction, int32_t newAction) {
		signal_onPlayerActionChange(playerId, oldAction, newAction);
	};
	pluginCalls->OnPlayerOnFireChange = [](int32_t playerId, uint8_t isOnFire) {
		signal_onPlayerOnFireChange(playerId, isOnFire);
	};
	pluginCalls->OnPlayerCrouchChange = [](int32_t playerId, uint8_t isCrouching) {
		signal_onPlayerCrouchChange(playerId, isCrouching);
	};
	pluginCalls->OnPlayerGameKeysChange = [](int32_t playerId, uint32_t oldKeys, uint32_t newKeys) {
		signal_onPlayerGameKeysChange(playerId, oldKeys, newKeys);
	};
	pluginCalls->OnPlayerBeginTyping = [](int32_t playerId) {
		signal_onPlayerBeginTyping(playerId);
	};
	pluginCalls->OnPlayerEndTyping = [](int32_t playerId) {
		signal_onPlayerEndTyping(playerId);
	};
	pluginCalls->OnPlayerAwayChange = [](int32_t playerId, uint8_t isAway) {
		signal_onPlayerAwayChange(playerId, isAway);
	};

	pluginCalls->OnPlayerMessage = [](int32_t playerId, const char* message) {
		signal_onPlayerMessage(playerId, message);
		return (uint8_t)1;
	};
	pluginCalls->OnPlayerCommand = [](int32_t playerId, const char* message) {

		//
		std::string data(message);
		std::vector<std::string> args = std::split(data, ' ');
		if (args.size() <= 0) {
			signal_onPlayerCommand(playerId, NULL, std::vector<std::string>());
		}
		else {
			std::string command = args.at(0);
			args.erase(args.begin());
			signal_onPlayerCommand(playerId, command, args);
		}
		return (uint8_t)1;
	};
	pluginCalls->OnPlayerPrivateMessage = [](int32_t playerId, int32_t targetPlayerId, const char* message) {
		signal_onPlayerPrivateMessage(playerId, targetPlayerId, message);
		return (uint8_t)1;
	};

	pluginCalls->OnPlayerKeyBindDown = [](int32_t playerId, int32_t bindId) {
		signal_onPlayerKeyBindDown(playerId, bindId);
	};
	pluginCalls->OnPlayerKeyBindUp = [](int32_t playerId, int32_t bindId) {
		signal_onPlayerKeyBindUp(playerId, bindId);
	};
	pluginCalls->OnPlayerSpectate = [](int32_t playerId, int32_t targetPlayerId) {
		signal_onPlayerSpectate(playerId, targetPlayerId);
	};
	pluginCalls->OnPlayerCrashReport = [](int32_t playerId, const char* report) {
		signal_onPlayerCrashReport(playerId, report);
	};

	pluginCalls->OnVehicleUpdate = [](int32_t vehicleId, vcmpVehicleUpdate updateType) {
		signal_onVehicleUpdate(vehicleId, updateType);
	};
	pluginCalls->OnVehicleExplode = [](int32_t vehicleId) {
		signal_onVehicleExplode(vehicleId);
	};
	pluginCalls->OnVehicleRespawn = [](int32_t vehicleId) {
		signal_onVehicleRespawn(vehicleId);
	};

	pluginCalls->OnObjectShot = [](int32_t objectId, int32_t playerId, int32_t weaponId) {
		signal_onObjectShot(objectId, playerId, weaponId);
	};
	pluginCalls->OnObjectTouched = [](int32_t objectId, int32_t playerId) {
		signal_onObjectTouched(objectId, playerId);
	};

	pluginCalls->OnPickupPickAttempt = [](int32_t pickupId, int32_t playerId) {
		signal_onPickupPickAttempt(pickupId, playerId);
		return (uint8_t)1;
	};
	pluginCalls->OnPickupPicked = [](int32_t pickupId, int32_t playerId) {
		signal_onPickupPicked(pickupId, playerId);
	};
	pluginCalls->OnPickupRespawn = [](int32_t pickupId) {
		signal_onPickupRespawn(pickupId);
	};

	pluginCalls->OnCheckpointEntered = [](int32_t checkPointId, int32_t playerId) {
		signal_onCheckpointEntered(checkPointId, playerId);
	};
	pluginCalls->OnCheckpointExited = [](int32_t checkPointId, int32_t playerId) {
		signal_onCheckpointExited(checkPointId, playerId);
	};

	pluginCalls->OnEntityPoolChange = [](vcmpEntityPool entityType, int32_t entityId, uint8_t isDeleted) {
		signal_onEntityPoolChange(entityType, entityId, isDeleted);
	};
	pluginCalls->OnServerPerformanceReport = [](size_t entryCount, const char** descriptions, uint64_t* times) {
		signal_onServerPerformanceReport(entryCount, descriptions, times);
	};

	return 1;
}

void OnSquirrelScriptLoad() {
	size_t size;
	int32_t sqID = g_Funcs->FindPlugin("SQHost2");
	const void** sqExports = g_Funcs->GetPluginExports(sqID, &size);
	if(sqExports != NULL && size > 0) {
		SquirrelImports* sqFuncs = (SquirrelImports*)(*sqExports);
		if(sqFuncs) {
			sqvm = *sqFuncs->GetSquirrelVM();
			sqapi = *sqFuncs->GetSquirrelAPI();
		}
	}
}

uint8_t OnInternalCommand(uint32_t uCmdType, const char* pszText) {
	switch(uCmdType) {
	case 0x7D6E22D8:
		OnSquirrelScriptLoad();
		break;

	default:
		break;
	}
	return 1;
}