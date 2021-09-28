#pragma once
#include "DiscordSDK/include/discord_rpc.h"
#include <chrono>//We will use chrono for the elapsed time.

static bool gInit, gRPC = true;
namespace Discord
{
	extern "C" __declspec(dllexport) void SetupDiscord();
	extern "C" __declspec(dllexport) void UpdateDiscord();
}
