#pragma once
#include "Signals.h"
// Handler files
#include "events/handlers_Server.h"
#include "events/handlers_Client.h"
#include "events/handlers_Player.h"
#include "events/handlers_Vehicle.h"
#include "events/handlers_Object.h"
#include "events/handlers_Pickup.h"
#include "events/handlers_Sphere.h"
#include "events/handlers_Checkpoint.h"

class EventHandler {
	EventHandler() {
		bindEvents_Server();
		bindEvents_Client();
		bindEvents_Player();
		bindEvents_Vehicle();
		bindEvents_Object();
		bindEvents_Pickup();
		bindEvents_Sphere();
		bindEvents_Checkpoint();
	}

	// Server
	void bindEvents_Server() {
		signal_onServerInitalize.connect(onServerInit);
	}

	// Client
	void bindEvents_Client() {

	}

	// Player
	void bindEvents_Player() {

	}

	// Vehicle
	void bindEvents_Vehicle() {

	}

	// Object
	void bindEvents_Object() {

	}

	// Pickup
	void bindEvents_Pickup() {

	}

	// Sphere
	void bindEvents_Sphere() {

	}

	// Checkpoints
	void bindEvents_Checkpoint() {

	}
};