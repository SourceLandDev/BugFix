#include <ll/api/memory/Hook.h>
#include <mc/nbt/CompoundTag.h>
#include <mc/nbt/ListTag.h>
#include <mc/world/item/registry/ItemStack.h>

LL_AUTO_TYPE_INSTANCE_HOOK(
    NoBadEnchantsHook,
    ll::memory::HookPriority::Normal,
    ItemStackBase,
    "??0ItemStackBase@@IEAA@AEBV0@@Z",
    ItemStackBase*,
    ItemStackBase const& a2
) {
    ItemStackBase* result = origin(a2);
    if (!a2 || !result || result->isNull() || !result->hasUserData()) {
        return result;
    }

    CompoundTag* nbt = result->getUserData();
    if (nbt->isEmpty() || !nbt->contains("ench")) {
        return result;
    }

    ListTag* ench = nbt->getList("ench");
    if (ench->size() <= 0) {
        nbt->remove("ench");
    }

    return result;
}