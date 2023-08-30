/*
 * description:
 * author@elecfrog
 */
#pragma once

#include <iostream>
#include <cstdio>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <memory>

using namespace std;

struct HtmlBuilder;

struct HtmlElement {
    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;

    HtmlElement() = default;

    HtmlElement(string name, string text) : name(std::move(name)), text(std::move(text)) {}

    string str(int indent = 0) const {
        ostringstream oss;
        string i(indent_size * indent, ' ');
        oss << i << "<" << name << ">" << endl;
        if (!text.empty())
            oss << string(indent_size * (indent + 1), ' ') << text << endl;

        for (const auto &e: elements)
            oss << e.str(indent + 1);

        oss << i << "</" << name << ">" << endl;
        return oss.str();
    }

    static unique_ptr<HtmlBuilder> build(const string &root_name) {
        return make_unique<HtmlBuilder>(root_name);
    }
};

struct HtmlBuilder {
    explicit HtmlBuilder(string root_name) {
        root.name = std::move(root_name);
    }

    // void to start with
    HtmlBuilder &add_child(const string &child_name, const string &child_text) {
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return *this;
    }

    string str() const { return root.str(); }

    operator HtmlElement() const { return root; }

    HtmlElement root;
};

bool Testing() {
    // <p>hello</p>
    auto text = "hello";
    string output;
    output += "<p>";
    output += text;
    output += "</p>";
    printf("<p>%s</p>", text);

    // <ul><li>hello</li><li>world</li></ul>
    string words[] = {"hello", "world"};
    ostringstream oss;
    oss << "<ul>";
    for (auto w: words)
        oss << "  <li>" << w << "</li>";
    oss << "</ul>";
    printf(oss.str().c_str());

    // easier
    HtmlBuilder builder{"ul"};
    builder.add_child("li", "hello").add_child("li", "world");
    cout << builder.str() << endl;

    HtmlElement e = HtmlElement::build("ul")->add_child("li", "hello").add_child("li", "world");
    cout << e.str() << endl;

    getchar();
    return true;
}
