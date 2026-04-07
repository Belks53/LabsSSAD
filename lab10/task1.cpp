#include <iostream>
#include <utility>
#include <memory>

using namespace std;

class Enemy {
    // member variables: name and health
    // parametrized constructor
    // member functions: takeDamage and getName
    private:
    string name;
    int health;

    public:
    Enemy(string name, int health) : name(std::move(name)), health(health) {}

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    [[nodiscard]] string getName() const {
        return name;
    }

    void printStrength() {
        cout << name << "STRENGTH LEVEL IS: " << health << endl;
    }



};

class AttackStrategy {
public:
    virtual ~AttackStrategy() = default;
    virtual void attack(Enemy &enemy) = 0;
};

class MageAttack : public AttackStrategy {
public:
    int damageOnAttack = 10;
    void attack(Enemy &enemy) override {
        enemy.takeDamage(damageOnAttack);
        cout << "Mage attack!" << endl;
    }
};

class RogueAttack : public AttackStrategy {
public:
    int damageOnAttack = 15;
    void attack(Enemy& enemy) override {
        enemy.takeDamage(damageOnAttack);
        cout << "Rogue attack!" << endl;
    }
};

class WarriorAttack : public AttackStrategy {
public:
    int damageOnAttack = 25;
    void attack(Enemy& enemy) override {
        enemy.takeDamage(damageOnAttack);
        cout << "Warrior attack!" << endl;
    }
};

class Character {
private:
    string name;
    unique_ptr<AttackStrategy> attackStrategy;
public:
    Character(string n, unique_ptr<AttackStrategy> strategy)
        : name(std::move(n)), attackStrategy(move(strategy)) {}

    void attack(Enemy& enemy) {;
        attackStrategy->attack(enemy);
    }

    void setAttackStrategy(unique_ptr<AttackStrategy> newStrategy) {
        this->attackStrategy = move(newStrategy);
    }
};

int main() {
    Character warrior("Warrior", make_unique<WarriorAttack>());
    Character mage("Mage", make_unique<MageAttack>());
    Character rogue("Rogue", make_unique<RogueAttack>());

    Enemy enemy1("Skull Crusher", 100);
    Enemy enemy2("Bone Breaker", 25);

    warrior.attack(enemy1);      // Warrior attack! (-25 HP)
    enemy1.printStrength();      // Skull Crusher STRENGTH LEVEL IS: 75

    mage.attack(enemy2);         // Mage attack! (-10 HP)
    enemy2.printStrength();      // Bone Breaker STRENGTH LEVEL IS: 15

    rogue.attack(enemy1);        // Rogue attack! (-15 HP)
    enemy1.printStrength();      // Skull Crusher STRENGTH LEVEL IS: 60

    return 0;
}

EXAMPLE OUTPUT:
Warrior attack!
Skull Crusher STRENGTH LEVEL IS: 75
Mage attack!
Bone Breaker STRENGTH LEVEL IS: 15
Rogue attack!
Skull Crusher STRENGTH LEVEL IS: 60
