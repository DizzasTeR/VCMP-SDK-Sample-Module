#pragma once
#include "../pch.h"
#include <Utils.h>

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