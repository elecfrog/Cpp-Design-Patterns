/*
 * description:
 * author@elecfrog
 */
#pragma once

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;

struct Tag {
    string name;
    string text;
    vector<Tag> children;
    vector<pair<string, string>> attributes;

    friend ostream &operator<<(ostream &os, const Tag &tag) {
        return print(os, tag, 0);
    }

    static ostream &print(ostream &os, const Tag &tag, int indent) {
        for (int i = 0; i < indent; ++i) os << "  ";
        os << "<" << tag.name;

        for (const auto &att: tag.attributes)
            os << " " << att.first << "=\"" << att.second << "\"";

        if (tag.children.size() == 0 && tag.text.length() == 0) {
            os << "/>" << endl;
        } else {
            os << ">" << endl;

            if (tag.text.length()) {
                for (int i = 0; i < indent + 1; ++i) os << "  ";
                os << tag.text << endl;
            }

            for (const auto &child: tag.children)
                print(os, child, indent + 1);

            for (int i = 0; i < indent; ++i) os << "  ";
            os << "</" << tag.name << ">" << endl;
        }

        return os;
    }

protected:

    Tag(string name, string text)
            : name{std::move(name)},
              text{std::move(text)} {
    }


    Tag(string name, initializer_list<Tag> &children)
            : name{std::move(name)},
              children{children} {
    }
};

struct P : Tag {
    explicit P(string &&text)
            : Tag{"p", std::move(text)} {
    }

    P(initializer_list<Tag> children)
            : Tag("p", children) {
    }

};

struct IMG : Tag {
    explicit IMG(string &&url)
            : Tag{"img", ""} {
        attributes.emplace_back("src", std::move(url));
    }
};


struct CODE : Tag {
    explicit CODE(std::string &&codeText, string &&attributeName, string &&attributeValue)
            : Tag{"code", std::move(codeText)} {
        attributes.emplace_back(attributeName, attributeValue);
    }
};


bool Testing() {
    cout <<

         P{
                 IMG{"https://pokemon.com/",},
                 IMG{"https://www.pokemoncenter.com/",},
                 CODE{"int x = 1", "language", "cpp"}
         }

         << endl;

    getchar();
    return true;
}