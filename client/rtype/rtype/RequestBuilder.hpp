#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

#include <boost/noncopyable.hpp>

#include "Protocol.hpp"
#include "IRequest.hpp"
#include "EnumHash.hpp"

#include "RequestSpawnMonster.hpp"
#include "RequestDisconnected.hpp"
#include "RequestMove.hpp"
#include "RequestFire.hpp"
#include "RequestPowder.hpp"
#include "RequestDestroyed.hpp"
#include "RequestCollision.hpp"
#include "RequestRespawn.hpp"
#include "RequestGetParty.hpp"
#include "RequestGameStatus.hpp"
#include "RequestMessage.hpp"
#include "RequestScore.hpp"
#include "RequestSpawnPowerUp.hpp"
#include "RequestSpawnPlayer.hpp"

class RequestBuilder : private boost::noncopyable
{
public:
	static std::unique_ptr<IRequest> Build(CommandType type);

private:
	static std::unique_ptr<IRequest> create_SpawnPlayerRequest(void);
	static std::unique_ptr<IRequest> create_SpawnPowerUpRequest(void);
	static std::unique_ptr<IRequest> create_ScoreRequest(void);
	static std::unique_ptr<IRequest> create_MessageRequest(void);
	static std::unique_ptr<IRequest> create_GameStatusRequest(void);
	static std::unique_ptr<IRequest> create_GetPartyRequest(void);
	static std::unique_ptr<IRequest> create_RespawnRequest(void);
	static std::unique_ptr<IRequest> create_DestroyedRequest(void);
	static std::unique_ptr<IRequest> create_LoadedPowderRequest(void);
	static std::unique_ptr<IRequest> create_ConnectRequest(void);
	static std::unique_ptr<IRequest> create_DisconnectedRequest(void);
	static std::unique_ptr<IRequest> create_SpawnMonsterRequest(void);
	static std::unique_ptr<IRequest> create_MoveRequest(void);
	static std::unique_ptr<IRequest> create_CollisionRequest(void);
	static std::unique_ptr<IRequest> create_ErrorRequest(void);
	static std::unique_ptr<IRequest> create_PingRequest(void);
	static std::unique_ptr<IRequest> create_FireRequest(void);

	static const std::unordered_map<CommandType, std::function<std::unique_ptr<IRequest>(void)>, EnumHash> Requests;
};
