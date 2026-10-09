#include <iostream>


class Character {
protected :
    std::string name;
    int hp;
    int maxHp;
    int attackPower;

public :
    Character(std::string n, int h, int ap) {
        this->name = n;
        hp = maxHp = h;
        attackPower = ap;
    }

    void takeDamage(int damage) {
        hp -= damage;
        if (hp < 0) {
            hp = 0;
        }
    }

    virtual void attack(Character &target) {
        target.takeDamage(attackPower);
    }

    bool isAlive() const {
        if (hp <= 0) {
            return false;
        }
        return true;
    }

    virtual void print() const {
        std::cout << name << " hp: " << hp << "/" << maxHp << '\n';
    }

    std::string getName() const {
        return name;
    }

    virtual ~Character() = default;
};

class Warrior : public Character {
public :
    Warrior(std::string n) : Character(n, 200, 25) {
    }

    void attack(Character &target) override {
        target.takeDamage(attackPower);
        std::cout << name << " GRAAAA\n";
    }
};

class Mage : public Character {
protected :
    int mana;

public :
    Mage(std::string n) : Character(n, 80, 40), mana(200) {
    }

    void attack(Character &target) override {
        if (mana < 20) {

            std::cout << name << " out of mana\n";
            //нужно сделать так, чтобы нельзя было атаковать, можно конечно сделать ap=0,но это не рение проблемы потому что когда мана появится ap будет = 0
            return;

        }
        target.takeDamage(attackPower);
        mana -= 20;
    }

    void print() const override {
        std::cout << name << " hp: " << hp << "/" << maxHp << " mana: " << mana << '\n';
    }
};

int main() {
    Character* c1= new Warrior("axe");
    Character* c2= new Mage("banana");
    c2->print();
    c2->attack(*c1);
    c1->attack(*c2);
    c1->print();
    if (c1->isAlive()) {
        std::cout<<"yes\n";
    }
    delete c1;
    delete c2;
    return 0;

}
