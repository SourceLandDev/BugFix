#include <ll/api/memory/Hook.h>
#include <mc/network/NetworkIdentifier.h>
#include <mc/network/ServerNetworkHandler.h>
#include <mc/network/packet/SpawnExperienceOrbPacket.h>
#include <mc/server/ServerPlayer.h>

LL_AUTO_TYPE_INSTANCE_HOOK(
    NoBadExperienceOrbsHook,
    ll::memory::HookPriority::Normal,
    ServerNetworkHandler,
    &ServerNetworkHandler::handle,
    void,
    NetworkIdentifier const&        source,
    SpawnExperienceOrbPacket const& packet
) {
    optional_ref<ServerPlayer> player = getServerPlayer(source, packet.mClientSubId);
    std::cerr << "Player " << player->getRealName() << " (xuid: " << player->getXuid()
              << ") is trying to spawn experience orbs with a total experience of " << packet.mCount << "!";
    // droped
}