#include <ll/api/memory/Hook.h>
#include <mc/entity/components/ProjectileComponent.h>
#include <mc/world/actor/Mob.h>
#include <mc/world/actor/player/Player.h>
#include <vector>

bool hited = false;

LL_AUTO_TYPE_INSTANCE_HOOK(
    ProjectileHitHook,
    ll::memory::HookPriority::Normal,
    ProjectileComponent,
    &ProjectileComponent::onHit,
    void,
    Actor&           a2,
    HitResult const& a3
) {
    hited = true;
    origin(a2, a3);
    hited = false;
}

std::vector<Actor*> actors{};

LL_AUTO_TYPE_INSTANCE_HOOK(
    MobDieHook,
    ll::memory::HookPriority::Normal,
    Mob,
    "?die@Mob@@UEAAXAEBVActorDamageSource@@@Z",
    void,
    ActorDamageSource const& a2
) {
    if (hited) {
        actors.push_back(this);
    }
    origin(a2);
}

Player* lastPlayer = nullptr;

LL_AUTO_TYPE_INSTANCE_HOOK(GetLastHurtHook, ll::memory::HookPriority::Normal, Actor, &Actor::getLastHurtByPlayer, Player*) {
    auto result = origin();
    auto index  = std::find(actors.begin(), actors.end(), this);
    if (index != actors.end()) {
        lastPlayer = result;
        actors.erase(index);
    }
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