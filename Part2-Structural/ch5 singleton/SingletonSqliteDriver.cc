#pragma once

#include <QtSql>
#include <unordered_map>
#include "Singleton.hpp"

class Database {
public:
    virtual int getPopulation(const std::string &name) = 0;
};


class DatabaseDriver {
public:
    virtual bool connect(const std::string &dbPath) = 0;
};

// It should be a fake sql
class DummyDatabase : public DatabaseDriver {

    DatabaseStatus status;
    QSqlDatabase db;

    bool connect(const std::string &dbPath) override {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbPath);
        if (!db.open()) {
            status = DatabaseStatus::Error;
            qDebug() << "Error opening database:" << db.lastError().text();
            return false;
        }
        status = DatabaseStatus::Connected;

        return true;
    }
};

// Copy from Q3M Project
namespace elf {
    class SqliteDriver : public elf::base::Singleton<SqliteDriver>, public DatabaseDriver {
    public:
        // using dependency injection to improve it!
        explicit SqliteDriver() = default;

        bool connect(const std::string &dbPath) override {
            db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName(dbPath);
            if (!db.open()) {
                status = DatabaseStatus::Error;
                qDebug() << "Error opening database:" << db.lastError().text();
                return false;
            }
            status = DatabaseStatus::Connected;

            return true;
        }

    private:
        DatabaseStatus status;
        QSqlDatabase db;
    };
}

class SingletonDatabase {
    SingletonDatabase() {
        std::ifstream ifstream("...txt");

        std::string s1, s2;
        while (std::getline(ifstream, s1)) {
            std::getline(ifstream, s2);
        }

        /*
         * READ*/
    }

public:
    static SingletonDatabase &get() {
        static SingletonDatabase db;
        return db;
    }

    int getData(const std::string &name) {
        return captionals[name];
    }

public:
    SingletonDatabase(const SingletonDatabase &) = delete;

    void operator=(const SingletonDatabase &) = delete;

    std::unordered_map<std::string, int> captionals;
};

struct DataFinder {
    int findSomethings(std::vector<std::string> names) {
        int ret = 0;
        for (auto &n: names) {
            ret += SingletonDatabase::get().getData(n);
        }
        return ret;
    }
};


// just for connecting the connection with the database
struct ConfigFinder {
    Database &db;

    ConfigFinder(Database &db) : db(db) {}

    int findSomethings(std::vector<std::string> names) {
        int ret = 0;
        for (auto &n: names) {
            ret += db.getPopulation(n);
        }
        return ret;
    }
};