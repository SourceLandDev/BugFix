#include <ll/api/memory/Hook.h>
#include <mc/deps/core/utility/BinaryStream.h>

LL_AUTO_INSTANCE_HOOK(
    HideSeedHook,
    ll::memory::HookPriority::Normal,
    "?write@StartGamePacket@@UEBAXAEAVBinaryStream@@@Z",
    void,
    BinaryStream& stream
) {
    ll::memory::dAccess<int64>(this, 48) = 0;
    origin(stream);
}