#include "ab/combat.hpp"
#include <algorithm>

namespace {

    int baseDamage(const ab::Combatant& a) {
        return a.weapon.baseDamage + a.stats.str;
    }

    int bonusRogueHidden(const ab::Combatant& a, const ab::Combatant& d) {
        if (!a.classes || a.classes->rogue < 1) return 0;
        return (a.stats.dex > d.stats.dex) ? 1 : 0;
    }

    int bonusWarriorSurge(const ab::Combatant& a) {
        if (!a.classes || a.classes->warrior < 1) return 0;
        return a.state.firstAttackDone ? 0 : a.weapon.baseDamage;
    }

    int bonusBarbarianRage(const ab::Combatant& a) {
        if (!a.classes || a.classes->barbarian < 1) return 0;
        int n = a.state.turnsAttacked + 1;
        return (n <= 3) ? 2 : -1;
    }

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
        return x;
    }

    CombatEngine::CombatEngine(IRng& rng) : rng_(rng) {}

    bool CombatEngine::missCheck(const Combatant& att, const Combatant& def) {
        int s = att.stats.dex + def.stats.dex;
        if (s <= 0) return false;
        int roll = rng_.uniform(1, s);
        return roll <= def.stats.dex;
    }

    int ab::CombatEngine::attack(Combatant& attacker, Combatant& defender) {
        if (missCheck(attacker, defender)) {
            attacker.state.turnsAttacked++;
            attacker.state.firstAttackDone = true;
            return 0;
        }

        int dmg = baseDamage(attacker);
        dmg += bonusRogueHidden(attacker, defender);
        dmg += bonusWarriorSurge(attacker);
        dmg += bonusBarbarianRage(attacker);

        if (dmg < 0) dmg = 0;
        if (dmg > 0) {
            defender.curHP -= dmg;
            if (defender.curHP < 0) defender.curHP = 0;
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
