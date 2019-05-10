#include "pch.h"
#include <Signals.h>
#include <Utils.h>

PluginFuncs* g_Funcs;
PluginCallbacks* g_Calls;
PluginInfo* g_Info;

HSQUIRRELVM sqvm;
HSQAPI sqapi;

uint8_t OnInternalCommand(uint32_t uCmdType, const char* pszText);

extern "C" EXPORT unsigned int VcmpPluginInit(PluginFuncs* pluginFuncs, PluginCallbacks* pluginCalls, PluginInfo* pluginInfo) {
	g_Funcs = pluginFuncs;
	g_Calls = pluginCalls;
	g_Info = pluginInfo;

	pluginInfo->pluginVersion = 0x1001;
	pluginInfo->apiMajorVersion = PLUGIN_API_MAJOR;
	pluginInfo->apiMinorVersion = PLUGIN_API_MINOR;

	pluginCalls->OnPluginCommand = OnInternalCommand;

	pluginCalls->OnServerInitialise = _OnServerInitialise;
	pluginCalls->OnServerShutdown = _OnServerShutdown;
	pluginCalls->OnServerFrame = _OnServerFrame;

	pluginCalls->OnIncomingConnection = _OnIncomingConnection;
	pluginCalls->OnClientScriptData = _OnClientScriptData;

	pluginCalls->OnPlayerConnect = _OnPlayerConnect;
	pluginCalls->OnPlayerDisconnect = _OnPlayerDisconnect;
	pluginCalls->OnPlayerModuleList = _OnPlayerModuleList;

	pluginCalls->OnPlayerRequestClass = _OnPlayerRequestClass;
	pluginCalls->OnPlayerRequestSpawn = _OnPlayerRequestSpawn;
	pluginCalls->OnPlayerSpawn = _OnPlayerSpawn;
	pluginCalls->OnPlayerDeath = _OnPlayerDeath;
	pluginCalls->OnPlayerUpdate = _OnPlayerUpdate;

	pluginCalls->OnPlayerRequestEnterVehicle = _OnPlayerRequestEnterVehicle;
	pluginCalls->OnPlayerEnterVehicle = _OnPlayerEnterVehicle;
	pluginCalls->OnPlayerExitVehicle = _OnPlayerExitVehicle;

	pluginCalls->OnPlayerNameChange = _OnPlayerNameChange;
	pluginCalls->OnPlayerStateChange = _OnPlayerStateChange;
	pluginCalls->OnPlayerActionChange = _OnPlayerActionChange;
	pluginCalls->OnPlayerOnFireChange = _OnPlayerOnFireChange;
	pluginCalls->OnPlayerCrouchChange = _OnPlayerCrouchChange;
	pluginCalls->OnPlayerGameKeysChange = _OnPlayerGameKeysChange;
	pluginCalls->OnPlayerBeginTyping = _OnPlayerBeginTyping;
	pluginCalls->OnPlayerEndTyping = _OnPlayerEndTyping;
	pluginCalls->OnPlayerAwayChange = _OnPlayerAwayChange;

	pluginCalls->OnPlayerMessage = _OnPlayerMessage;
	pluginCalls->OnPlayerCommand = _OnPlayerCommand;
	pluginCalls->OnPlayerPrivateMessage = _OnPlayerPrivateMessage;

	pluginCalls->OnPlayerKeyBindDown = _OnPlayerKeyBindDown;
	pluginCalls->OnPlayerKeyBindUp = _OnPlayerKeyBindUp;
	pluginCalls->OnPlayerSpectate = _OnPlayerSpectate;
	pluginCalls->OnPlayerCrashReport = _OnPlayerCrashReport;

	pluginCalls->OnVehicleUpdate = _OnVehicleUpdate;
	pluginCalls->OnVehicleExplode = _OnVehicleExplode;
	pluginCalls->OnVehicleRespawn = _OnVehicleRespawn;

	pluginCalls->OnObjectShot = _OnObjectShot;
	pluginCalls->OnObjectTouched = _OnObjectTouched;

	pluginCalls->OnPickupPickAttempt = _OnPickupPickAttempt;
	pluginCalls->OnPickupPicked = _OnPickupPicked;
	pluginCalls->OnPickupRespawn = _OnPickupRespawn;

	pluginCalls->OnCheckpointEntered = _OnCheckpointEntered;
	pluginCalls->OnCheckpointExited = _OnCheckpointExited;

	pluginCalls->OnEntityPoolChange = _OnEntityPoolChange;
	pluginCalls->OnServerPerformanceReport = _OnServerPerformanceReport;
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