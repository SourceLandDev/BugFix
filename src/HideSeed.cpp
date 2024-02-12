#include <ll/api/memory/Hook.h>

LL_AUTO_INSTANCE_HOOK(
    HideSeedHook,
    ll::memory::HookPriority::Normal,
    "?write@StartGamePacket@@UEBAXAEAVBinaryStream@@@Z",
    void
) {
    *((int64*)(this + 48)) = 0;
    origin();
}