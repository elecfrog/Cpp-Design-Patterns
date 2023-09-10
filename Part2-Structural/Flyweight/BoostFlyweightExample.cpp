#include <iostream>
#include <string>
#include <cstdint>
#include <bimap>
#include <boost/bimap.hpp>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>

// naive implementation of flyweight-pattern
namespace native {
    // define the key type
    using key = uint32_t;

    // assume it is User class for Genshin Impact!
    struct User {
        User(const std::string &first_name, const std::string &last_name)
                : first_name{add(first_name)}, last_name{add(last_name)} {
        }

        const std::string &get_first_name() const {
            return names.left.find(last_name)->second;
        }

        const std::string &get_last_name() const {
            return names.left.find(last_name)->second;
        }

        static void info() {
            for (auto entry: names.left) {
                std::cout << "Key: " << entry.first << ", Value: " << entry.second << std::endl;
            }
        }

        friend std::ostream &operator<<(std::ostream &os, const User &obj) {
            return os
                    << "first_name: " << obj.first_name << " " << obj.get_first_name()
                    << " last_name: " << obj.last_name << " " << obj.get_last_name();
        }

    protected:
        static boost::bimap<key, std::string> names;
        static int seed;

        static key add(const std::string &s) {
            auto it = names.right.find(s);
            if (it == names.right.end()) {
                // add it
                key id = ++seed;
                names.insert(boost::bimap<key, std::string>::value_type(seed, s));
                return id;
            }
            return it->second;
        }

        key first_name, last_name;
    };

    int User::seed = 0;
    boost::bimap<key, std::string> User::names{};

    bool Testing() {
        User john_doe{"John", "Doe"};
        User jane_doe{"Jane", "Doe"};
        std::cout << "John " << john_doe << std::endl;
        std::cout << "Jane " << jane_doe << std::endl;
        User::info();
        return true;
    }
}

// boost implementation
namespace external {
    struct User {
        // users share names! e.g., John Smith
        boost::flyweights::flyweight<std::string> first_name, last_name;
        //string first_name, last_name;
        // ...
        User(const std::string &first_name, const std::string &last_name) {}
    };

    bool Testing() {
        User john_doe{"John", "Doe"};
        User jane_doe{"Jane", "Doe"};
        std::cout << std::boolalpha << (&jane_doe.last_name.get() == &john_doe.last_name.get());
        return true;
    }
}
