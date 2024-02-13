#include <ll/api/memory/Hook.h>
#include <mc/server/commands/MinecartBlockCommandOrigin.h>
#include <mc/world/actor/Actor.h>

LL_AUTO_TYPE_INSTANCE_HOOK(
    NoCommandBlockMinecartHook,
    ll::memory::HookPriority::Normal,
    MinecartBlockCommandOrigin,
    "??0MinecartBlockCommandOrigin@@QEAA@AEAVBlockSource@@AEBUActorUniqueID@@@Z",
    MinecartBlockCommandOrigin*,
    BlockSource&         region,
    ActorUniqueID const& minecartId
) {
    MinecartBlockCommandOrigin* result = origin(region, minecartId);
    result->getEntity()->remove();
    return result;
}

#include <mc/world/level/block/Block.h>
#include <mc/world/level/block/utils/BedrockBlocks.h>

LL_AUTO_TYPE_INSTANCE_HOOK(
    NoBadFallingBlockMinecartHook,
    ll::memory::HookPriority::Normal,
    Block,
    "?shouldStopFalling@Block@@QEBA_NAEAVActor@@@Z",
    bool,
    Actor& entity
) {
    bool result = origin(entity);
    if (!isFallingBlock()) {
        entity.remove();
        return false;
    }

    return result;
}