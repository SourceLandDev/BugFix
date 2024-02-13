#include <ll/api/memory/Hook.h>
#include <mc/server/ServerPlayer.h>

LL_AUTO_TYPE_INSTANCE_HOOK(
    NoBadBedTeleportHook,
    ll::memory::HookPriority::Normal,
    ServerPlayer,
    "?changeDimension@ServerPlayer@@UEAAXV?$AutomaticID@VDimension@@H@@@Z",
    void,
    DimensionType toId
) {
    if (isSleeping()) {
        return;
    }

    origin(toId);
}