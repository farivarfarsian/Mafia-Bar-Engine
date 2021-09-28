#include "Discord.h"


void Discord::SetupDiscord()
{
	if (gRPC)
	{
		DiscordEventHandlers handlers;
		memset(&handlers, 0, sizeof(handlers));
		Discord_Initialize("886327228818923551", &handlers, 1, "0"); //Mafia Bar Engine: 886327228818923551, MDE MP: 886278900378919032, NFS WM: 886495980059525121 
	}
	else
	{
		Discord_Shutdown();
	}
}

void Discord::UpdateDiscord()
{
	static int64_t StartTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	if (gRPC)
	{
		DiscordRichPresence discordPresence;
		memset(&discordPresence, 0, sizeof(discordPresence));
		discordPresence.state = "In Progress...";
		discordPresence.details = "Mafia Bar Engine Using DirectX 11 With MP Support";
		discordPresence.startTimestamp = StartTime;
		discordPresence.endTimestamp = NULL;
		discordPresence.largeImageKey = "artboard_1_2x-100";
		discordPresence.largeImageText = "Mafia Bar Engine Logo";
		discordPresence.instance = 1;
		Discord_UpdatePresence(&discordPresence);
	}
	else
	{
		Discord_ClearPresence();
	}
}
