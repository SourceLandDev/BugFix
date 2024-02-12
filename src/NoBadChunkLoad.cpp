#include <ll/api/memory/Hook.h>
#include <ll/api/memory/Memory.h>
#include <ll/api/service/Bedrock.h>
#include <mc/server/ServerLevel.h>
#include <mc/server/ServerPlayer.h>
#include <mc/world/ActorUniqueID.h>
#include <mc/world/components/MapDataManager.h>
#include <mc/world/level/saveddata/maps/MapItemSavedData.h>

LL_AUTO_TYPE_INSTANCE_HOOK(
    NoBadChunkLoadHook,
    ll::memory::HookPriority::Normal,
    ServerPlayer,
    "?disconnect@ServerPlayer@@QEAAXXZ",
    void
) {
    origin();
    MapDataManager& manager = ((ServerLevel&)ll::service::getLevel().get())._getMapDataManager();
    for (auto& [id, data] : ll::memory::dAccess<std::unordered_map<
             ActorUniqueID,
             std::unique_ptr<MapItemSavedData>,
             std::hash<ActorUniqueID>,
             std::equal_to<ActorUniqueID>,
             std::allocator<std::pair<ActorUniqueID const, std::unique_ptr<MapItemSavedData>>>>>(&manager, 112)) {
        auto& v = ll::memory::dAccess<std::vector<std::shared_ptr<MapItemTrackedActor>>>(data.get(), 96);
        v.erase(
            std::remove_if(
                v.begin(),
                v.end(),
                [this](auto& ptr) { return ll::memory::dAccess<ActorUniqueID>(ptr.get(), 8) == getOrCreateUniqueID(); }
            ),
            v.end()
        );
    }
}