#pragma once

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <cstdio>

// Represents an HTML tag.
struct Tag {
    std::string name;
    std::string text;
    std::vector<Tag> children;
    std::vector<std::pair<std::string, std::string>> attributes;
    const size_t indent_size = 2;

    // Overload the << operator for easy output.
    friend std::ostream& operator<<(std::ostream& os, const Tag& tag) {
        return print(os, tag, 0);
    }

    // Utility function to print a Tag and its children recursively.
    static std::ostream& print(std::ostream& os, const Tag& tag, int indent) {
        for (int i = 0; i < indent; ++i) os << "  ";
        os << "<" << tag.name;

        // Printing attributes of the tag.
        for (const auto& att: tag.attributes)
            os << " " << att.first << "=\"" << att.second << "\"";

        if (tag.children.size() == 0 && tag.text.length() == 0) {
            os << "/>" << std::endl;
        } else {
            os << ">" << std::endl;

            if (tag.text.length()) {
                for (int i = 0; i < indent + 1; ++i) os << "  ";
                os << tag.text << std::endl;
            }

            // Recursive call to print child tags.
            for (const auto& child: tag.children)
                print(os, child, indent + 1);

            for (int i = 0; i < indent; ++i) os << "  ";
            os << "</" << tag.name << ">" << std::endl;
        }

        return os;
    }

protected:
    Tag(std::string name, std::string text)
            : name{std::move(name)}, text{std::move(text)} {
    }

    Tag(std::string name, std::initializer_list<Tag>& children)
            : name{std::move(name)}, children{children} {
    }
};

// Represents a <p> tag in HTML.
struct P : Tag {
    explicit P(std::string&& text)
            : Tag{"p", std::move(text)} {
    }

    P(std::initializer_list<Tag> children)
            : Tag("p", children) {
    }
};

// Represents an <img> tag in HTML.
struct IMG : Tag {
    explicit IMG(std::string&& url)
            : Tag{"img", ""} {
        attributes.emplace_back("src", std::move(url));
    }
};

// Represents a <code> tag in HTML.
struct CODE : Tag {
    explicit CODE(std::string&& codeText, std::string&& attributeName, std::string&& attributeValue)
            : Tag{"code", std::move(codeText)} {
        attributes.emplace_back(std::move(attributeName), std::move(attributeValue));
    }
};

bool Testing() {
    std::cout <<
              P{
                      IMG{"https://pokemon.com/"},
                      IMG{"https://www.pokemoncenter.com/"},
                      CODE{"int x = 1", "language", "cpp"}
              }
              << std::endl;

    return true;
}

int main()
{
    return Testing();
}
