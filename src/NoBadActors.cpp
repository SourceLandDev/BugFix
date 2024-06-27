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

LL_AUTO_TYPE_INSTANCE_HOOK(
    NoBadFallingBlockHook,
    ll::memory::HookPriority::Normal,
    Block,
    &Block::shouldStopFalling,
    bool,
    Actor& entity
) {
    if (!isFallingBlock()) {
        entity.remove();
        return false;
    }

    return origin(entity);
}

#include <mc/world/level/block/actor/MovingBlockActor.h>

LL_AUTO_TYPE_INSTANCE_HOOK(
    NoBadMovingBlockHook,
    ll::memory::HookPriority::Normal,
    MovingBlockActor,
    "?tick@MovingBlockActor@@UEAAXAEAVBlockSource@@@Z",
    void,
    BlockSource& region
) {
    if (!isMovable(region)) {
        return;
    }

    origin(region);
}

#include <mc/world/actor/npc/Npc.h>

LL_AUTO_TYPE_INSTANCE_HOOK(
    NoBadNPCHook,
    ll::memory::HookPriority::Normal,
    Npc,
    "?newServerAiStep@Npc@@UEAAXXZ",
    void
) {
    remove();
}

#include <mc/world/actor/Mob.h>

LL_AUTO_TYPE_INSTANCE_HOOK(
    NoBadDeadHook,
    ll::memory::HookPriority::Normal,
    Mob,
    "??0Mob@@QEAA@PEAVActorDefinitionGroup@@AEBUActorDefinitionIdentifier@@AEAVEntityContext@@@Z",
    Mob*,
    ActorDefinitionGroup*            definitions,
    ActorDefinitionIdentifier const& definitionName,
    EntityContext&                   entityContext
) {
    Mob* reault = origin(definitions, definitionName, entityContext);
    if (reault->isDead()) {
        reault->setDead(false);
        reault->kill();
    }
    return reault;
}