#include "ab/ui.hpp"
#include <iostream>

namespace ab::ui {

    void printSheet(const Character& c) {
        std::cout << "HP " << c.curHp() << "/" << c.maxHp()
            << "  STR " << c.stats().str
            << "  DEX " << c.stats().dex
            << "  END " << c.stats().endu
            << "  Weapon=" << c.weapon().name << " (" << c.weapon().baseDamage << ")\n";
        std::cout << "Levels: Rogue=" << c.levels().rogue
            << " Warrior=" << c.levels().warrior
            << " Barbarian=" << c.levels().barbarian
            << "  total=" << c.levels().total() << "\n";
    }

    void printMonster(const Monster& m) {
        std::cout << "Monster: " << m.name
            << "  HP " << m.maxHP
            << "  STR " << m.stats.str
            << "  DEX " << m.stats.dex
            << "  END " << m.stats.endu
            << "  Weapon=" << m.weapon.name << " (" << m.weapon.baseDamage << ")\n";
    }

    void printHeader(const std::string& title) {
        std::cout << "=== " << title << " ===\n";
    }

    static int askIntInRange(const std::string& prompt, int lo, int hi, int def = -1) {
        for (;;) {
            std::cout << prompt;
            int v;
            if (std::cin >> v) {
                if (v >= lo && v <= hi) return v;
            }
            else {
                std::cin.clear();
            }
            if (def >= lo && def <= hi) return def;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод. Повторите.\n";
        }
    }

    ClassKind askClass(const std::string& title) {
        std::cout << "\n=== " << title << " ===\n";
        std::cout << "1) Разбойник  2) Воин  3) Варвар\n";
        int v = askIntInRange("Выберите класс [1..3]: ", 1, 3);
        if (v == 1) return ClassKind::Rogue;
        if (v == 2) return ClassKind::Warrior;
        return ClassKind::Barbarian;
    }

    bool askYesNo(const std::string& question) {
        for (;;) {
            std::cout << question << " [y/n]: ";
            char c;
            if (std::cin >> c) {
                if (c == 'y' || c == 'Y') return true;
                if (c == 'n' || c == 'N') return false;
            }
            else {
                std::cin.clear();
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Введите y или n.\n";
        }
    }

    int askTargetWins(int defaultWins) {
        int v = askIntInRange("Сколько побед подряд нужно для победы? ", 1, 1000, defaultWins);
        return v;
    }

}
