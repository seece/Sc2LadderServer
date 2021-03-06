#pragma once
#include <memory.h>
#include <sstream>
#include <mutex>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sc2api/sc2_api.h>
#include "LadderConfig.h"
#include "AgentsConfig.h"


class LadderManager
{
public:
	LadderManager(int InCoordinatorArgc, char** inCoordinatorArgv);
	LadderManager(int InCoordinatorArgc, char** inCoordinatorArgv, const char *InConfigFile);
    bool LoadSetup();
	void SaveJsonResult(const BotConfig & Bot1, const BotConfig & Bot2, const std::string & Map, GameResult Result);
	void RunLadderManager();

    void LogNetworkFailiure(const std::string &Agent1, const std::string &Action);

private:
    bool IsBotEnabled(std::string BotName);
	bool IsInsideEloRange(std::string Bot1Name, std::string Bot2Name);
	bool DownloadBot(const BotConfig &bot, std::string Checksum);
    bool VerifyUploadRequest(const std::string & uploadResult);
    bool UploadBot(const BotConfig &bot);
	bool UploadCmdLine(GameResult result, const Matchup &ThisMatch, std::string UploadLocation);

	bool LoginToServer();
    std::vector<std::string> MapList;
	std::string ResultsLogFile;

	void SaveError(const std::string &Agent1, const std::string &Agent2, const std::string &Map);

	bool IsValidResult(GameResult Result);

    int CoordinatorArgc;
    int32_t MaxEloDiff;
    char **CoordinatorArgv;
	std::string ConfigFile;

	bool EnableReplayUploads;
	bool EnableServerLogin;
    std::string BotCheckLocation;
	std::string ServerUsername;
	std::string ServerPassword;
	std::string ServerLoginAddress;
    LadderConfig *Config;
    AgentsConfig *AgentConfig;
};
