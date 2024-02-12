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

#include <mc/world/actor/projectile/FallingBlockActor.h>
#include <mc/world/level/block/Block.h>
#include <mc/world/level/block/utils/BedrockBlocks.h>

LL_AUTO_TYPE_INSTANCE_HOOK(
    NoBadFallingBlockMinecartHook,
    ll::memory::HookPriority::Normal,
    FallingBlockActor,
    "??0FallingBlockActor@@QEAA@PEAVActorDefinitionGroup@@AEBUActorDefinitionIdentifier@@AEAVEntityContext@@@Z",
    FallingBlockActor*,
    ActorDefinitionGroup*            definitions,
    ActorDefinitionIdentifier const& definitionName,
    EntityContext&                   entityContext
) {
    FallingBlockActor* result = origin(definitions, definitionName, entityContext);
    Block const&       block  = result->getFallingBlock();
    if (!block.isFallingBlock()) {
        result->setFallingBlock(*BedrockBlocks::mAir, result + 1232);
    }

    return result;
}