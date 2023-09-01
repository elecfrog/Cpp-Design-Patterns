#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <memory>

// Forward declaration for the HtmlBuilder
struct HtmlBuilder;

// Represents a node in the HTML tree structure
struct HtmlElement {
    std::string name;
    std::string text;
    std::vector<HtmlElement> elements;
    const size_t indent_size = 2;

    // Default constructor
    HtmlElement() = default;

    // Constructor that initializes name and text
    HtmlElement(std::string name, std::string text)
            : name(std::move(name)), text(std::move(text)) {}


    // Converts the HTML element to a string representation with proper indentation
    std::string str(int indent = 0) const {
        std::ostringstream oss;
        std::string i(indent_size * indent, ' ');
        oss << i << "<" << name << ">" << std::endl;
        if (!text.empty())
            oss << std::string(indent_size * (indent + 1), ' ') << text << std::endl;

        for (const auto &e: elements)
            oss << e.str(indent + 1);

        oss << i << "</" << name << ">" << std::endl;
        return oss.str();
    }
};

// Facilitates the building of HTML structures
struct HtmlBuilder {
    // Root element of the HTML document
    HtmlElement root;

    // Constructor that initializes root's name
    explicit HtmlBuilder(std::string rootName) {
        root.name = std::move(rootName);
    }

    // Adds a child to the root with a given name and text
    HtmlBuilder *addChild(const std::string &childName, const std::string &childText) {
        HtmlElement e{childName, childText};
        root.elements.emplace_back(e);
        return this;
    }

    // void to start with
    HtmlBuilder *addChild(HtmlElement &&e) {
        root.elements.emplace_back(std::move(e));
        return this;
    }

    // Converts the root to its string representation
    std::string str() const { return root.str(); }

    // type casting operator, implicit cast a HtmlBuilder to a HtmlElement object, 
    // but it is confusing, I don't want to use it
//    operator HtmlElement() const { return root; }

    // use this function to replace it!
    HtmlElement toHtmlElement() const { return root; }

    // A static function to initiate the building process, 
    // remove from HtmlElement, cuz I don't like insert logic into data structures
    static std::unique_ptr<HtmlBuilder> BuildHTML(const std::string &root_name) {
        return std::make_unique<HtmlBuilder>(root_name);
    }
};

/*
 * Using BuildHTMLPtr or BuildHTML?
 * I have no exact idea about it. 
 * But consider the size and the complexity and recursive data structure,
 * I currently think using pointer is better!
 * */

bool Testing() {
    // Demonstrates the fluent interface building process
    HtmlElement e = HtmlBuilder::BuildHTML("ul")
            ->addChild("li", "hello")
            ->addChild("li", "world")
            ->toHtmlElement();

    // Demonstrates adding an existing HtmlElement as a child to another HtmlElement
    HtmlElement e2 = HtmlBuilder::BuildHTML("pre")
            ->addChild(std::move(e))
            ->addChild("li", "world")
            ->toHtmlElement();

    std::cout << e2.str() << std::endl;
    return true;
}

int main() {
    return Testing();
}
