#include "ab/combat.hpp"
#include <algorithm>

namespace ab::attackEffects {

    int bonusRogueHidden(const Combatant& a, const Combatant& d) {
        if (!(a.classes && a.classes->rogue >= 1)) return 0;
        return (a.stats.dex > d.stats.dex) ? 1 : 0;
    }

    int bonusGhostHidden(const Combatant& a, const Combatant& d) {
        if (!a.hasHiddenAttackLikeRogue) return 0;
        return (a.stats.dex > d.stats.dex) ? 1 : 0;
    }

    int bonusWarriorSurge(const Combatant& a) {
        if (!(a.classes && a.classes->warrior >= 1)) return 0;
        return a.state.firstAttackDone ? 0 : a.weapon.baseDamage;
    }

    int bonusBarbarianRage(const Combatant& a) {
        if (!(a.classes && a.classes->barbarian >= 1)) return 0;
        int n = a.state.turnsAttacked + 1;
        return (n <= 3) ? 2 : -1;
    }

    int bonusRoguePoison(const Combatant& a) {
        if (!(a.classes && a.classes->rogue >= 3)) return 0;
        int n = a.state.turnsAttacked + 1;
        return (n >= 2) ? (n - 1) : 0;
    }

    int bonusDragonBreath(const Combatant& a) {
        if (!a.hasDragonBreath) return 0;
        int n = a.state.turnsAttacked + 1;
        return (n % 3 == 0) ? 3 : 0;
    }

} // namespace ab::attackEffects

namespace ab::defenseEffects {

    int reduceWarriorShield(const Combatant& attacker, const Combatant& defender) {
        if (!(defender.classes && defender.classes->warrior >= 2)) return 0;
        return (defender.stats.str > attacker.stats.str) ? 3 : 0;
    }

    int reduceStoneSkinClasses(const Combatant& defender) {
        if (!(defender.classes && defender.classes->barbarian >= 2)) return 0;
        return defender.stats.endu;
    }

    int reduceStoneSkinGolem(const Combatant& defender) {
        return defender.hasStoneSkinLikeBarbarian ? defender.stats.endu : 0;
    }

} // namespace ab::defenseEffects

namespace {

    int baseWeapon(const ab::Combatant& a) { return a.weapon.baseDamage; }
    int baseStr(const ab::Combatant& a) { return a.stats.str; }

    bool isSlashing(const ab::Combatant& a) { return a.weapon.type == ab::WeaponType::Slashing; }
    bool isBludgeoning(const ab::Combatant& a) { return a.weapon.type == ab::WeaponType::Bludgeoning; }

}

namespace ab {

    Combatant makePlayer(const Character& c) {
        Combatant x;
        x.name = "Игрок";
        x.curHP = c.curHp();
        x.maxHP = c.maxHp();
        x.stats = c.stats();
        x.weapon = c.weapon();
        x.classes = &c.levels();
        x.isPlayer = true;
        return x;
    }

    Combatant makeMonster(const Monster& m) {
        Combatant x;
        x.name = m.name;
        x.curHP = m.maxHP;
        x.maxHP = m.maxHP;
        x.stats = m.stats;
        x.weapon = m.weapon;
        x.isPlayer = false;
        x.takesDoubleFromBludgeoning = m.takesDoubleFromBludgeoning;
        x.immuneToSlashingWeaponBase = m.immuneToSlashingWeaponBase;
        x.hasHiddenAttackLikeRogue = m.hasHiddenAttackLikeRogue;
        x.hasStoneSkinLikeBarbarian = m.hasStoneSkinLikeBarbarian;
        x.hasDragonBreath = m.hasDragonBreath;
        return x;
    }

    CombatEngine::CombatEngine(IRng& rng) : rng_(rng) {}

    bool CombatEngine::missCheck(const Combatant& att, const Combatant& def) {
        int s = att.stats.dex + def.stats.dex;
        if (s <= 0) return false;
        int roll = rng_.uniform(1, s);
        return roll <= def.stats.dex;
    }

    int CombatEngine::attack(Combatant& attacker, Combatant& defender) {
        if (missCheck(attacker, defender)) {
            attacker.state.turnsAttacked++;
            attacker.state.firstAttackDone = true;
            return 0;
        }

        int weaponPart = baseWeapon(attacker);
        int dmg = weaponPart + baseStr(attacker);

        if (defender.immuneToSlashingWeaponBase && isSlashing(attacker)) {
            dmg -= weaponPart;
        }

        dmg += attackEffects::bonusRogueHidden(attacker, defender);
        dmg += attackEffects::bonusGhostHidden(attacker, defender);
        dmg += attackEffects::bonusWarriorSurge(attacker);
        dmg += attackEffects::bonusBarbarianRage(attacker);
        dmg += attackEffects::bonusRoguePoison(attacker);
        dmg += attackEffects::bonusDragonBreath(attacker);

        int mitigation = 0;
        mitigation += defenseEffects::reduceWarriorShield(attacker, defender);
        mitigation += defenseEffects::reduceStoneSkinClasses(defender);
        mitigation += defenseEffects::reduceStoneSkinGolem(defender);

        dmg = std::max(0, dmg - mitigation);

        if (defender.takesDoubleFromBludgeoning && isBludgeoning(attacker) && dmg > 0) {
            dmg *= 2;
        }

        if (dmg > 0) {
            defender.curHP -= dmg;
            defender.curHP = std::max(0, defender.curHP);
        }

        attacker.state.turnsAttacked++;
        attacker.state.firstAttackDone = true;
        return dmg;
    }

    bool CombatEngine::duel(Combatant a, Combatant b) {
        bool playerTurn = (a.stats.dex >= b.stats.dex);
        while (a.curHP > 0 && b.curHP > 0) {
            if (playerTurn) attack(a, b);
            else            attack(b, a);
            if (a.curHP <= 0 || b.curHP <= 0) break;
            playerTurn = !playerTurn;
        }
        return a.curHP > 0;
    }

} 
