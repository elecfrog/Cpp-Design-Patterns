#pragma once

#include <iostream>
#include <string>
#include <QObject>

using namespace std;

struct Game;
struct Player;

struct EventData {
    virtual ~EventData() = default;

    virtual void print() const = 0;
};

// performed as a concrete data bundle/package to send
struct PlayerScoredData : EventData {
    string player_name;
    int goals_scored_so_far;

    PlayerScoredData(const string &player_name, const int goals_scored_so_far)
            : player_name(player_name), goals_scored_so_far(goals_scored_so_far) {}

    void print() const override {
        cout << player_name << " has scored! (their "
             << goals_scored_so_far << " goal)" << "\n";
    }
};

// where game is a only a event broker
struct Game : public QObject {
Q_OBJECT

signals:

    void playerScored(EventData *data);  // emit by player class
};

struct Player {
    string name;
    int goals_scored = 0;
    Game &game;

    Player(string name, Game &game)
            : name(std::move(name)), game(game) {}

    // when the player score, it "send" a msg bundle and emit a signal to tell Coach
    void score() {
        goals_scored++;
        PlayerScoredData ps{name, goals_scored};
        emit game.playerScored(&ps);
    }
};

struct Coach : public QObject {
Q_OBJECT

    Game &game;

public:
    explicit Coach(Game &game)
            : QObject(&game), game(game) {

        // using lambda to avoid using Qt slots
        auto onPlayerScored = [&](EventData *e) {
            auto *ps = dynamic_cast<PlayerScoredData *>(e);
            if (ps && ps->goals_scored_so_far < 3) {
                cout << "coach says: well done, " << ps->player_name << "\n";
            }
        };

        // celebrate if player has scored <3 goals
        connect(&game, &Game::playerScored, onPlayerScored);
    }
};
