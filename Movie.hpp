/*
 * description:
 * author@elecfrog
 */
#pragma once

#include <QString>
#include <unordered_set>
#include <utility>

namespace elf {
    struct FMovie {
        QString unicode;
        QString title;
        QString pubDate; // formal name releaseDate
        QString duration;
        QString score;

        std::unordered_set<QString> actors; // formal type std::vector
        std::unordered_set<QString> tags; // formal type std::vector

        QString libLink;
        QString coverLink;
        QString torrentLink;
        QString localFileLink;  // formal name localFile
    };

    static void SaveTags(const FMovie &movie, const QString &filename) {
        std::ofstream ofstream(filename.toStdString());
        for (auto &item: movie.tags) {
            ofstream << item.toStdString() << std::endl;
        }
    }

    // separation of concerns
    static void SaveTagsToDatabase(const FMovie &movie, const QString &filename) {

        // Database Streaming
        //    std::ofstream ofstream(filename.toStdString());
        //    for (auto &item: movie.tags) {
        //        ofstream << item.toStdString() << std::endl;
        //    }
    }

    static std::vector<FMovie *> FilterByUnicode(const std::vector<FMovie *> &movies, const QString &unicode) {
        std::vector<FMovie *> ret;
        for (auto &m: movies) {
            if (m->unicode == unicode)
                ret.emplace_back(m);

        }
        return ret;
    }

    static std::vector<FMovie *> FilterByActor(const std::vector<FMovie *> &movies, const QString &actor) {
        std::vector<FMovie *> ret;
        for (auto &m: movies) {
            if (m->actors.find(actor) != m->actors.end()) {
                ret.emplace_back(m);
            }
            return ret;
        }
    }

    static std::vector<FMovie *> FilterByTag(const std::vector<FMovie *> &movies, const QString &tag) {
        std::vector<FMovie *> ret;
        for (auto &m: movies) {
            if (m->tags.find(tag) != m->tags.end()) {
                ret.emplace_back(m);
            }
            return ret;
        }
    }

    static std::vector<FMovie *>
    FilterByActorAndTag(const std::vector<FMovie *> &movies, const QString &actor, const QString &tag) {
        std::vector<FMovie *> ret;
        for (auto &m: movies) {
            if ((m->tags.find(tag) != m->tags.end()) && (m->actors.find(actor) != m->actors.end())) {
                ret.emplace_back(m);
            }
            return ret;
        }
    }

    // etc...

    template<typename T>
    struct Specification {
        virtual bool IsSatisfied(T *movie) = 0;
    };

    template<typename T>
    struct Filter {
        virtual std::vector<T *> FilterFunc(const std::vector<T *> &items, Specification<T> &spec) = 0;
    };

    struct MovieFilter : Filter<FMovie> {
        std::vector<FMovie *>
        FilterFunc(const std::vector<FMovie *> &movies, Specification<FMovie> &spec) override {
            std::vector<FMovie *> ret;
            for (auto &item: movies) {
                if (spec.IsSatisfied(item)) {
                    ret.emplace_back(item);
                }
            }
            return ret;
        }
    };

    struct ActorSpecification : Specification<FMovie> {
        QString actor;

        explicit ActorSpecification(const QString &actor) : actor(actor) {}

        bool IsSatisfied(FMovie *movie) override {
            return (movie->actors.find(actor) != movie->actors.end());
        }
    };

    struct TagSpecification : Specification<FMovie> {
        QString tag;

        explicit TagSpecification(const QString &tag) : tag(tag) {}

        bool IsSatisfied(FMovie *movie) override {
            return (movie->tags.find(tag) != movie->tags.end());
        }
    };


    template<typename T>
    struct AndSpecification : Specification<T> {
        Specification<T> &lhs;
        Specification<T> &rhs;

        AndSpecification(Specification<T> &lhs, Specification<T> &rhs)
                : lhs(lhs), rhs(rhs) {

        }

        bool IsSatisfied(T *movie) override
        {
            return lhs.IsSatisfied() && rhs.IsSatisfied();
        }
    };
}
