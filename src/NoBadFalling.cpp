#include <ll/api/memory/Hook.h>
#include <mc/deps/core/string/HashedString.h>
#include <mc/world/actor/Actor.h>
#include <mc/world/level/BlockSource.h>
#include <mc/world/level/block/Block.h>
#include <mc/world/level/block/BlockLegacy.h>
#include <mc/world/level/block/utils/VanillaBlockTypeIds.h>

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
    Vec3 const&        pos         = entity.getPosition();
    BlockSource const& blockSource = entity.getDimensionBlockSourceConst();
    Block const&       block       = blockSource.getBlock(pos);
    if (block == VanillaBlockTypeIds::Water || block == VanillaBlockTypeIds::BigDripleaf) {
        return false;
    }
    return true;
}