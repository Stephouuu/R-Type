#include "RequestBuilder.hpp"

const std::unordered_map<CommandType, std::function<std::unique_ptr<IRequest>(void)>, EnumHash> RequestBuilder::Requests = {
	{ CommandType::Connect, std::bind(&RequestBuilder::create_ConnectRequest) },
	{ CommandType::CreateParty, std::bind(&RequestBuilder::create_CreatePartyRequest) },
	{ CommandType::Move, std::bind(&RequestBuilder::create_MoveRequest) },
	{ CommandType::Destroyed, std::bind(&RequestBuilder::create_DestroyedRequest) },
	{ CommandType::Fire, std::bind(&RequestBuilder::create_FireRequest) },
	{ CommandType::LoadedPowder, std::bind(&RequestBuilder::create_LoadedPowderRequest) },
	{ CommandType::Collision, std::bind(&RequestBuilder::create_CollisionRequest) },
	{ CommandType::Respawn, std::bind(&RequestBuilder::create_RespawnRequest) },
	{ CommandType::GetParty, std::bind(&RequestBuilder::create_GetPartyRequest) },
	{ CommandType::GameStatus, std::bind(&RequestBuilder::create_GameStatusRequest) },
	{ CommandType::Message, std::bind(&RequestBuilder::create_MessageRequest) },
	{ CommandType::Score, std::bind(&RequestBuilder::create_ScoreRequest) },
	{ CommandType::Disconnect, std::bind(&RequestBuilder::create_DisconnectRequest) },
	{ CommandType::Effect, std::bind(&RequestBuilder::create_EffectRequest) }
};

std::unique_ptr<IRequest> RequestBuilder::Build(CommandType type)
{
	if (Requests.find(type) != Requests.cend()) {
		return (std::move(Requests.at(type)()));
	}
	return (NULL);
}

std::unique_ptr<IRequest> RequestBuilder::create_EffectRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestEffect));
}

std::unique_ptr<IRequest> RequestBuilder::create_DisconnectRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestDisconnect));
}

std::unique_ptr<IRequest> RequestBuilder::create_ScoreRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestScore));
}

std::unique_ptr<IRequest> RequestBuilder::create_MessageRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestMessage));
}

std::unique_ptr<IRequest> RequestBuilder::create_GameStatusRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestGameStatus));
}

std::unique_ptr<IRequest> RequestBuilder::create_GetPartyRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestGetParty));
}

std::unique_ptr<IRequest> RequestBuilder::create_RespawnRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestRespawn));
}

std::unique_ptr<IRequest> RequestBuilder::create_LoadedPowderRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestLoadedPowder));
}

std::unique_ptr<IRequest> RequestBuilder::create_ConnectRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestConnect));
}

std::unique_ptr<IRequest> RequestBuilder::create_CreatePartyRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestCreateParty));
}

std::unique_ptr<IRequest> RequestBuilder::create_SpawnRequest(void)
{
	return (NULL);
}

std::unique_ptr<IRequest> RequestBuilder::create_MoveRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestMove));
}

std::unique_ptr<IRequest> RequestBuilder::create_CollisionRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestCollision));
}

std::unique_ptr<IRequest> RequestBuilder::create_ErrorRequest(void)
{
	return NULL;
}

std::unique_ptr<IRequest> RequestBuilder::create_PingRequest(void)
{
	return NULL;
}

std::unique_ptr<IRequest> RequestBuilder::create_FireRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestFire));
}

std::unique_ptr<IRequest> RequestBuilder::create_DestroyedRequest(void)
{
	return (std::unique_ptr<IRequest>(new RequestDestroyed));
}