#include <ll/api/memory/Hook.h>
#include <mc/world/item/VanillaItemTags.h>
#include <mc/world/item/registry/ItemStack.h>
#include <mc/world/level/block/Block.h>
#include <mc/world/level/block/utils/VanillaBlockTypeIds.h>
#include <mc/nbt/CompoundTag.h>

LL_AUTO_TYPE_INSTANCE_HOOK(
    NoBadItemsHook,
    ll::memory::HookPriority::Normal,
    ItemStackBase,
    "??0ItemStackBase@@IEAA@AEBV0@@Z",
    ItemStackBase*,
    ItemStackBase const& a2
) {
    ItemStackBase* result = origin(a2);
    if (!result || result->isNull()) {
        return result;
    }

    if (result->hasTag(VanillaItemTags::SpawnEgg)) {
        result->setNull(std::optional<std::string>());
        return result;
    }

    if (!(result->isBlock())) {
        return result;
    }

    Block const* block = result->getBlock();
    if (!block) {
        return result;
    }

    if (!(block->isUnbreakable())) {
        return result;
    }

    result->setNull(std::optional<std::string>());
    return result;
}