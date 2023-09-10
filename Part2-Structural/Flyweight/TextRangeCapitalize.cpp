#include <iostream>
#include <string>
#include <ostream>
#include <utility>
#include <vector>

// A naive text formatting class
class FormattedText {
    // Plain text to be formatted
    std::string text;
    // Array indicating which characters should be capitalized
    bool *caps;

public:
    // Constructor that initializes the plain text and caps array
    explicit FormattedText(const std::string &text)
            : text{text} {
        // Initialize the caps array to all false
        caps = new bool[text.length()]{};
    }

    // Destructor to free the dynamically allocated caps array
    ~FormattedText() {
        delete[] caps;
    }

    // Capitalize the characters from start to end (both inclusive)
    void capitalize(int start, int end) {
        for (int i = start; i <= end; ++i)
            caps[i] = true;
    }

    // Overloaded output operator to display the formatted text
    friend std::ostream &operator<<(std::ostream &os, const FormattedText &obj) {
        std::string s;
        for (int i = 0; i < obj.text.length(); ++i) {
            char c = obj.text[i];
            s += obj.caps[i] ? std::toupper(c) : c;
        }
        return os << s;
    }
};

// An improved text formatting class
class BetterFormattedText {
public:
    // Structure representing a range of text and its formatting details
    struct TextRange {
        int start, end;
        bool capitalize, bold, italic;

        // Check if the given position is within this range
        bool covers(size_t position) const {
            return position >= start && position <= end;
        }
    };

    // Get a text range for given start and end, to apply formatting
    TextRange &get_range(int start, int end) {
        formatting.emplace_back(TextRange{start, end});
        return *formatting.rbegin();
    }

    // Constructor that initializes the plain text
    explicit BetterFormattedText(std::string text)
            : text{std::move(text)} {}

    // Overloaded output operator to display the formatted text
    friend std::ostream &operator<<(std::ostream &os, const BetterFormattedText &obj) {
        std::string s;
        for (size_t i = 0; i < obj.text.length(); i++) {
            auto c = obj.text[i];
            for (const auto &rng: obj.formatting) {
                if (rng.covers(i) && rng.capitalize)
                    c = std::toupper(c);
                s += c;
            }
        }
        return os << s;
    }

private:
    // Plain text to be formatted
    std::string text;
    // List of text ranges with their respective formatting
    std::vector<TextRange> formatting;
};

int main() {
    FormattedText ft("This is a brave new world");
    // Capitalize the word "brave"
    ft.capitalize(10, 15);
    std::cout << ft << std::endl;

    BetterFormattedText bft("This is a brave new world");
    // Capitalize the word "brave"
    bft.get_range(10, 15).capitalize = true;
    std::cout << bft << std::endl;
    return 0;
}
