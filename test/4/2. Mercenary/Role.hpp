#include <iostream>
#include <string>

#ifndef ROLE_HPP
#define ROLE_HPP

using namespace std;

namespace final {

class Fighter;
class Protector;
class Caster;

// uncompleted, you should add code into this class
class Base {
    friend class Fighter;
    friend class Protector;
    friend class Caster;

  private:
    // WARNING: NO OTHER MEMBER VARIABLE IS ALLOWED TO BE ADDED HERE.
    std::string name;
    int health, attack;
    bool alive, defensive;
    static int aliveNumber;
    // you only need to define aliveNumber here.
    inline int type();
    void output_info() {
        int tp = type();
        if (tp == 1)
            cout << "Fighter " << name << " ";
        if (tp == 2)
            cout << "Protector " << name << " ";
        if (tp == 3)
            cout << "Caster " << name << " ";
    }

  public:
    // WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
    // WARNING: THIS CLASS(Base) CAN NOT BE INSTANTIATED（实例化）.
    // WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
    // the function you need to implement or define is as follows.
    //(1) getAliveNumber
    static int getAliveNumber() { return Base::aliveNumber; }
    //(2) Constructor
    Base(const string &_name, const int _health, const int _attack)
        : name(_name), health(_health), attack(_attack), alive(1), defensive(0) {

        aliveNumber++;
    }
    //(3) launch_attack
    virtual void launch_attack(Base *target) = 0;
    //(4) defend
    virtual void defend(bool flag) = 0;

    bool isAlive() { return alive; }
    bool isDefensive() { return defensive; }

    // void output() {
    //     cout << name << " " << health << " " << attack << (isAlive() ? " isAlive" : " dead") << ' ' << defensive << '\n';
    // }
};

class Fighter : public Base {
  public:
    // WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
    // WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
    Fighter(const std::string &name, const int health, const int attack) : Base(name, health, attack) {}

    void launch_attack(Base *target) override {
        if (!alive)
            return;
        if (!target->alive)
            return;
        // cout << name << " attack " << target->name << '\n';
        if (!target->isDefensive()) {
            if (target->type() == 3)
                target->health -= max(0, attack * 2);
            else
                target->health -= max(0, attack);
        } else {
            if (target->type() == 3)
                target->health -= max(0, attack * 2 - target->attack);
            else
                target->health -= max(0, attack - target->attack);
            health -= target->attack;
        }
        if (target->health <= 0) {
            target->output_info();
            cout << "is killed\n";
            target->alive = 0;
            Base::aliveNumber--;
        }
        if (health <= 0) {
            output_info();
            cout << "is killed\n";
            alive = 0;
            Base::aliveNumber--;
        }
    }

    void defend(bool flag) override {
        if (flag) {
            defensive = 1;
            health += 3;
            attack += 2;
        } else {
            defensive = 0;
        }
    }
};

class Protector : public Base {
  public:
    // WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
    // WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
    Protector(const std::string &name, const int health, const int attack) : Base(name, health, attack) {}

    void launch_attack(Base *target) {
        // cout << name << " attack " << target->name << '\n';
        if (!alive)
            return;
        if (!target->alive)
            return;
        if (!target->isDefensive()) {
            if (target->type() == 1)
                target->health -= max(0, attack * 2);
            else
                target->health -= max(0, attack);
        } else {
            if (target->type() == 1)
                target->health -= max(0, attack * 2 - target->attack);
            else
                target->health -= max(0, attack - target->attack);
            health -= target->attack;
        }
        if (target->health <= 0) {
            target->output_info();
            cout << "is killed\n";
            target->alive = 0;
            Base::aliveNumber--;
        }
        if (health <= 0) {
            output_info();
            cout << "is killed\n";
            alive = 0;
            Base::aliveNumber--;
        }
    }

    void defend(bool flag) {
        if (flag) {
            defensive = 1;
            health += 7;
            attack += 1;
        } else {
            defensive = 0;
        }
    }
};

class Caster : public Base {
  public:
    // WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
    // WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
    Caster(const std::string &name, const int health, const int attack) : Base(name, health, attack) {}

    void launch_attack(Base *target) {
        if (!alive)
            return;
        if (!target->alive)
            return;
        // cout << name << " attack " << target->name << '\n';
        if (!target->isDefensive()) {
            if (target->type() == 2)
                target->health -= max(0, attack * 2);
            else
                target->health -= max(0, attack);
        } else {
            if (target->type() == 2)
                target->health -= max(0, attack * 2 - target->attack);
            else
                target->health -= max(0, attack - target->attack);
        }
        if (target->health <= 0) {
            target->output_info();
            cout << "is killed\n";
            target->alive = 0;
            Base::aliveNumber--;
        }
        if (health <= 0) {
            output_info();
            cout << "is killed\n";
            alive = 0;
            Base::aliveNumber--;
        }
    }

    void defend(bool flag) {
        if (flag) {
            defensive = 1;
            health += 5;
        } else {
            defensive = 0;
        }
    }
};

// I don't know whether this is permitted, considering that it's a static member variable. If not, please delete my submission
// and I'll be sorry for my misunderstanding.
int Base::aliveNumber = 0;

inline int Base::type() {
    if (dynamic_cast<Fighter *>(this) != nullptr)
        return 1;
    if (dynamic_cast<Protector *>(this) != nullptr)
        return 2;
    return 3;
}

} // namespace final

#endif // ROLE_HPP