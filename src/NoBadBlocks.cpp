#include <ll/api/memory/Hook.h>
#include <mc/world/level/BlockSource.h>
#include <mc/world/level/block/Block.h>
#include <mc/world/level/block/utils/VanillaBlockTypeIds.h>

LL_AUTO_TYPE_INSTANCE_HOOK(
    NoBadSnifferEggSpeedHook,
    ll::memory::HookPriority::Normal,
    Block,
    "?onRemove@Block@@QEBAXAEAVBlockSource@@AEBVBlockPos@@@Z",
    void,
    BlockSource&    region,
    BlockPos const& pos
) {
    origin(region, pos);
    if (getTypeName() == VanillaBlockTypeIds::SnifferEgg.getString()) {
        region.removeFromRandomTickingQueue(pos, *this);
    }
}