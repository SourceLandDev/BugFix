#include <ll/api/memory/Hook.h>
#include <mc/world/actor/Actor.h>
#include <mc/world/level/block/BlockLegacy.h>

LL_AUTO_TYPE_INSTANCE_HOOK(
    NoBadFallingHook,
    ll::memory::HookPriority::Normal,
    BlockLegacy,
    "?shouldStopFalling@BlockLegacy@@UEBA_NAEAVActor@@@Z",
    bool,
    Actor& entity
) {
    if (!origin(entity)) {
        return false;
    }
    entity.remove();
    return true;
}