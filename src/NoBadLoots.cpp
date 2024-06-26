#include <ll/api/memory/Hook.h>
#include <mc/entity/components/ProjectileComponent.h>
#include <mc/world/actor/ActorDamageSource.h>
#include <mc/world/actor/Mob.h>
#include <mc/world/actor/player/Player.h>
#include <vector>

std::vector<Actor*> actors{};

LL_AUTO_TYPE_INSTANCE_HOOK(
    MobDieHook,
    ll::memory::HookPriority::Normal,
    Mob,
    "?die@Mob@@UEAAXAEBVActorDamageSource@@@Z",
    void,
    ActorDamageSource const& a2
) {
    origin(a2);
    if (a2.getEntityType() != ActorType::Player || a2.getEntityType() == a2.getDamagingEntityType()) {
        return;
    }
    actors.push_back(this);
}

Player* lastPlayer = nullptr;

LL_AUTO_TYPE_INSTANCE_HOOK(GetLastHurtHook, ll::memory::HookPriority::Normal, Actor, &Actor::getLastHurtByPlayer, Player*) {
    auto result = origin();
    auto index  = std::find(actors.begin(), actors.end(), this);
    if (index == actors.end()) {
        return result;
    }
    lastPlayer = result;
    actors.erase(index);
    return result;
}

LL_AUTO_TYPE_INSTANCE_HOOK(GetSelectedItemHook, ll::memory::HookPriority::Normal, Player, &Player::getSelectedItem, ItemStack const&) {
    if (lastPlayer == this) {
        lastPlayer = nullptr;
        return ItemStack::EMPTY_ITEM;
    }
    lastPlayer = nullptr;
    return origin();
}