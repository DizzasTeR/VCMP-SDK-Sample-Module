#pragma once
#include "../pch.h"

// Signals

nod::signal<uint8_t(void)> signal_onServerInitalize;
nod::signal<void(void)> signal_onServerShutdown;
nod::signal<void(float elapsedTime)> signal_onServerFrame;

nod::signal<uint8_t(char* playerName, size_t nameBufferSize, const char* userPassword, const char* ipAddress)> signal_onPlayerConnection;
nod::signal<void(int32_t playerId, const uint8_t* data, size_t size)> signal_onClientScriptData;

nod::signal<void(int32_t playerId)> signal_onPlayerConnect;
nod::signal<void(int32_t playerId, vcmpDisconnectReason reason)> signal_onPlayerDisconnect;
nod::signal<void(int32_t playerId, const char* list)> signal_onPlayerModuleList;

nod::signal<uint8_t(int32_t playerId, int32_t offset)> signal_onPlayerRequestClass;
nod::signal<uint8_t(int32_t playerId)> signal_onPlayerRequestSpawn;
nod::signal<void(int32_t playerId)> signal_onPlayerSpawn;
nod::signal<void(int32_t playerId, int32_t killerId, int32_t reason, vcmpBodyPart bodyPart)> signal_onPlayerDeath;
nod::signal<void(int32_t playerId, vcmpPlayerUpdate updateType)> signal_onPlayerUpdate;

nod::signal<uint8_t(int32_t playerId, int32_t vehicleId, int32_t slotIndex)> signal_onPlayerRequestEnterVehicle;
nod::signal<void(int32_t playerId, int32_t vehicleId, int32_t slotIndex)> signal_onPlayerEnterVehicle;
nod::signal<void(int32_t playerId, int32_t vehicleId)> signal_onPlayerExitVehicle;

nod::signal<void(int32_t playerId, const char* oldName, const char* newName)> signal_onPlayerNameChange;
nod::signal<void(int32_t playerId, vcmpPlayerState oldState, vcmpPlayerState newState)> signal_onPlayerStateChange;
nod::signal<void(int32_t playerId, int32_t oldAction, int32_t newAction)> signal_onPlayerActionChange;
nod::signal<void(int32_t playerId, uint8_t isOnFire)> signal_onPlayerOnFireChange;
nod::signal<void(int32_t playerId, uint8_t isCrouching)> signal_onPlayerCrouchChange;
nod::signal<void(int32_t playerId, uint32_t oldKeys, uint32_t newKeys)> signal_onPlayerGameKeysChange;
nod::signal<void(int32_t playerId)> signal_onPlayerBeginTyping;
nod::signal<void(int32_t playerId)> signal_onPlayerEndTyping;
nod::signal<void(int32_t playerId, uint8_t isAway)> signal_onPlayerAwayChange;

nod::signal<uint8_t(int32_t playerId, const char* message)> signal_onPlayerMessage;
nod::signal<uint8_t(int32_t playerId, std::string command, std::vector<std::string> params)> signal_onPlayerCommand;
nod::signal<uint8_t(int32_t playerId, int32_t targetPlayerId, const char* message)> signal_onPlayerPrivateMessage;

nod::signal<void(int32_t playerId, int32_t bindId)> signal_onPlayerKeyBindDown;
nod::signal<void(int32_t playerId, int32_t bindId)> signal_onPlayerKeyBindUp;
nod::signal<void(int32_t playerId, int32_t targetPlayerId)> signal_onPlayerSpectate;
nod::signal<void(int32_t playerId, const char* report)> signal_onPlayerCrashReport;

nod::signal<void(int32_t vehicleId, vcmpVehicleUpdate updateType)> signal_onVehicleUpdate;
nod::signal<void(int32_t vehicleId)> signal_onVehicleExplode;
nod::signal<void(int32_t vehicleId)> signal_onVehicleRespawn;

nod::signal<void(int32_t objectId, int32_t playerId, int32_t weaponId)> signal_onObjectShot;
nod::signal<void(int32_t objectId, int32_t playerId)> signal_onObjectTouched;

nod::signal<uint8_t(int32_t pickupId, int32_t playerId)> signal_onPickupPickAttempt;
nod::signal<void(int32_t pickupId, int32_t playerId)> signal_onPickupPicked;
nod::signal<void(int32_t pickupId)> signal_onPickupRespawn;

nod::signal<void(int32_t checkPointId, int32_t playerId)> signal_onCheckpointEntered;
nod::signal<void(int32_t checkPointId, int32_t playerId)> signal_onCheckpointExited;

nod::signal<void(vcmpEntityPool entityType, int32_t entityId, uint8_t isDeleted)> signal_onEntityPoolChange;
nod::signal<void(size_t entryCount, const char** descriptions, uint64_t* times)> signal_onServerPerformanceReport;

// Connectors

uint8_t _OnServerInitialise(void) {
	signal_onServerInitalize();
}
void _OnServerShutdown(void) {
	signal_onServerShutdown();
}
void _OnServerFrame(float elapsedTime) {
	signal_onServerFrame(elapsedTime);
}

uint8_t _OnIncomingConnection(char* playerName, size_t nameBufferSize, const char* userPassword, const char* ipAddress) {
	signal_onPlayerConnection(playerName, nameBufferSize, userPassword, ipAddress);
}
void _OnClientScriptData(int32_t playerId, const uint8_t* data, size_t size) {
	signal_onClientScriptData(playerId, data, size);
}

void _OnPlayerConnect(int32_t playerId) {
	signal_onPlayerConnect(playerId);
}
void _OnPlayerDisconnect(int32_t playerId, vcmpDisconnectReason reason) {
	signal_onPlayerDisconnect(playerId, reason);
}
void _OnPlayerModuleList(int32_t playerId, const char* list) {
	signal_onPlayerModuleList(playerId, list);
}

uint8_t _OnPlayerRequestClass(int32_t playerId, int32_t offset) {
	signal_onPlayerRequestClass(playerId, offset);
}
uint8_t _OnPlayerRequestSpawn(int32_t playerId) {
	signal_onPlayerRequestSpawn(playerId);
}
void _OnPlayerSpawn(int32_t playerId) {
	signal_onPlayerSpawn(playerId);
}
void _OnPlayerDeath(int32_t playerId, int32_t killerId, int32_t reason, vcmpBodyPart bodyPart) {
	signal_onPlayerDeath(playerId, killerId, reason, bodyPart);
}
void _OnPlayerUpdate(int32_t playerId, vcmpPlayerUpdate updateType) {
	signal_onPlayerUpdate(playerId, updateType);
}

uint8_t _OnPlayerRequestEnterVehicle(int32_t playerId, int32_t vehicleId, int32_t slotIndex) {
	signal_onPlayerRequestEnterVehicle(playerId, vehicleId, slotIndex);
}
void _OnPlayerEnterVehicle(int32_t playerId, int32_t vehicleId, int32_t slotIndex) {
	signal_onPlayerEnterVehicle(playerId, vehicleId, slotIndex);
}
void _OnPlayerExitVehicle(int32_t playerId, int32_t vehicleId) {
	signal_onPlayerExitVehicle(playerId, vehicleId);
}

void _OnPlayerNameChange(int32_t playerId, const char* oldName, const char* newName) {
	signal_onPlayerNameChange(playerId, oldName, newName);
}
void _OnPlayerStateChange(int32_t playerId, vcmpPlayerState oldState, vcmpPlayerState newState) {
	signal_onPlayerStateChange(playerId, oldState, newState);
}
void _OnPlayerActionChange(int32_t playerId, int32_t oldAction, int32_t newAction) {
	signal_onPlayerActionChange(playerId, oldAction, newAction);
}
void _OnPlayerOnFireChange(int32_t playerId, uint8_t isOnFire) {
	signal_onPlayerOnFireChange(playerId, isOnFire);
}
void _OnPlayerCrouchChange(int32_t playerId, uint8_t isCrouching) {
	signal_onPlayerCrouchChange(playerId, isCrouching);
}
void _OnPlayerGameKeysChange(int32_t playerId, uint32_t oldKeys, uint32_t newKeys) {
	signal_onPlayerGameKeysChange(playerId, oldKeys, newKeys);
}
void _OnPlayerBeginTyping(int32_t playerId) {
	signal_onPlayerBeginTyping(playerId);
}
void _OnPlayerEndTyping(int32_t playerId) {
	signal_onPlayerEndTyping(playerId);
}
void _OnPlayerAwayChange(int32_t playerId, uint8_t isAway) {
	signal_onPlayerAwayChange(playerId, isAway);
}

uint8_t _OnPlayerMessage(int32_t playerId, const char* message) {
	signal_onPlayerMessage(playerId, message);
}
uint8_t _OnPlayerCommand(int32_t playerId, const char* message) {
	std::string data(message);
	std::vector<std::string> args = std::split(data, ' ');
	if(args.size() <= 0) {
		signal_onPlayerCommand(playerId, NULL, std::vector<std::string>());
	}
	else {
		std::string command = args.at(0);
		args.erase(args.begin());
		signal_onPlayerCommand(playerId, command, args);
	}

}
uint8_t _OnPlayerPrivateMessage(int32_t playerId, int32_t targetPlayerId, const char* message) {
	signal_onPlayerPrivateMessage(playerId, targetPlayerId, message);
}

void _OnPlayerKeyBindDown(int32_t playerId, int32_t bindId) {
	signal_onPlayerKeyBindDown(playerId, bindId);
}
void _OnPlayerKeyBindUp(int32_t playerId, int32_t bindId) {
	signal_onPlayerKeyBindUp(playerId, bindId);
}
void _OnPlayerSpectate(int32_t playerId, int32_t targetPlayerId) {
	signal_onPlayerSpectate(playerId, targetPlayerId);
}
void _OnPlayerCrashReport(int32_t playerId, const char* report) {
	signal_onPlayerCrashReport(playerId, report);
}

void _OnVehicleUpdate(int32_t vehicleId, vcmpVehicleUpdate updateType) {
	signal_onVehicleUpdate(vehicleId, updateType);
}
void _OnVehicleExplode(int32_t vehicleId) {
	signal_onVehicleExplode(vehicleId);
}
void _OnVehicleRespawn(int32_t vehicleId) {
	signal_onVehicleRespawn(vehicleId);
}

void _OnObjectShot(int32_t objectId, int32_t playerId, int32_t weaponId) {
	signal_onObjectShot(objectId, playerId, weaponId);
}
void _OnObjectTouched(int32_t objectId, int32_t playerId) {
	signal_onObjectTouched(objectId, playerId);
}

uint8_t _OnPickupPickAttempt(int32_t pickupId, int32_t playerId) {
	signal_onPickupPickAttempt(pickupId, playerId);
}
void _OnPickupPicked(int32_t pickupId, int32_t playerId) {
	signal_onPickupPicked(pickupId, playerId);
}
void _OnPickupRespawn(int32_t pickupId) {
	signal_onPickupRespawn(pickupId);
}

void _OnCheckpointEntered(int32_t checkPointId, int32_t playerId) {
	signal_onCheckpointEntered(checkPointId, playerId);
}
void _OnCheckpointExited(int32_t checkPointId, int32_t playerId) {
	signal_onCheckpointExited(checkPointId, playerId);
}

void _OnEntityPoolChange(vcmpEntityPool entityType, int32_t entityId, uint8_t isDeleted) {
	signal_onEntityPoolChange(entityType, entityId, isDeleted);
}
void _OnServerPerformanceReport(size_t entryCount, const char** descriptions, uint64_t * times) {
	signal_onServerPerformanceReport(entryCount, descriptions, times);
}
