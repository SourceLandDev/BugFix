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

LL_AUTO_TYPE_INSTANCE_HOOK(NoBadNPCHook, ll::memory::HookPriority::Normal, Npc, "?newServerAiStep@Npc@@UEAAXXZ", void) {
    remove();
}

LL_AUTO_TYPE_INSTANCE_HOOK(
    NoBadDeadOnHurtHook,
    ll::memory::HookPriority::Normal,
    Actor,
    &Actor::hurt,
    bool,
    ActorDamageSource const& source,
    float                    damage,
    bool                     knock,
    bool                     ignite
) {
    bool result = origin(source, damage, knock, ignite);
    if (!result && isDead() && getHealth() > 0) {
        setDead(false);
        return origin(source, damage, knock, ignite);
    }
    return result;
}

LL_AUTO_TYPE_INSTANCE_HOOK(
    NoBadDeadHook,
    ll::memory::HookPriority::Normal,
    Actor,
    "??0Actor@@QEAA@PEAVActorDefinitionGroup@@AEBUActorDefinitionIdentifier@@AEAVEntityContext@@@Z",
    Actor*,
    ActorDefinitionGroup*            definitions,
    ActorDefinitionIdentifier const& definitionName,
    EntityContext&                   entityContext
) {
    Actor* result = origin(definitions, definitionName, entityContext);
    if (result->isDead()) {
        result->remove();
    }
    return result;
}