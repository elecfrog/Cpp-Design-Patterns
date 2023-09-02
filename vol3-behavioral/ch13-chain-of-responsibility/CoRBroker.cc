#include <iostream>
#include <string>
#include <QObject>
#include <utility>

// Event broker using Qt's signal and slot mechanism
struct Query : public QObject {
Q_OBJECT

public:
    std::string creature_name;

    enum Argument {
        attack,
        defense
    } argument;

    int result;

    Query(std::string creature_name, const Argument argument, const int result)
            : creature_name(std::move(creature_name)), argument(argument), result(result) {}

signals:

    void querySignal(Query &q);
};

struct Game : public QObject {
Q_OBJECT

signals:

    void queries(Query &q);
};

class Creature : public QObject {
Q_OBJECT

    Game &game;
    int attack, defense;
public:
    std::string name;

    Creature(Game &game, std::string name, const int attack, const int defense)
            : QObject(), game(game), attack(attack), defense(defense), name(std::move(name)) {}

    [[nodiscard]] int GetAttack() const {
        Query q{name, Query::Argument::attack, attack};
        emit game.queries(q);
        return q.result;
    }

    friend std::ostream &operator<<(std::ostream &os, const Creature &obj) {
        return os
                << "name: " << obj.name
                << " attack: " << obj.GetAttack() // invoke the attack
                << " defense: " << obj.defense;
    }
};

class CreatureModifier : public QObject {
Q_OBJECT

    Game &game;
public:
    Creature &creature;
public:
    ~CreatureModifier() override = default;

    CreatureModifier(Game &game, Creature &creature)
            : QObject(), game(game), creature(creature) {
    }
};

class DoubleAttackModifier : public CreatureModifier {
Q_OBJECT

public:
    DoubleAttackModifier(Game &game, Creature &creature)
            : CreatureModifier(game, creature) {
        // here also could use a lambda
        connect(&game, &Game::queries, this, &DoubleAttackModifier::handleQuery);
    }

public slots:
    void handleQuery(Query &q) {
        if (q.creature_name == creature.name && q.argument == Query::Argument::attack) {
            q.result *= 2;
        }
    }
};

int main(int ac, char *av[]) {
    Game game;
    Creature goblin{game, "Strong Goblin", 2, 2};

    std::cout << goblin << std::endl;

    {
        DoubleAttackModifier dam{game, goblin};

        std::cout << goblin << std::endl;
    }

    std::cout << goblin << std::endl;

    getchar();
    return 0;
}
