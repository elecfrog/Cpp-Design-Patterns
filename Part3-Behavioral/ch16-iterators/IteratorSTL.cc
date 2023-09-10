#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {
    vector<string> names{"A", "B", "C", "D", "E"};

    auto iterator = names.begin(); // begin(names)

    cout << "First name: " << names[0] << *iterator << endl;

    ++iterator;

    cout << "Second name: " << names[1] << *iterator << endl;

    iterator->append("&B");

    cout << "Second name: " << names[1] << *iterator << endl;

    // "A", "B", "C", "D", "E"
    // ----------------------- ^^^
    
    while (++iterator != names.end()) {
        cout << "Next name: " << *iterator << endl;
    }

    //           "A", "B", "C", "D", "E"
    // rend()^^^ ------------------- ^^^rbegin()
    for (auto ri = rbegin(names); ri != rend(names); ++ri) {
        cout << *ri;
        if (ri + 1 != rend(names))
            cout << ",";
    }
    
    vector<string>::const_reverse_iterator crit = crbegin(names);
    // *crit += string ("X");

    for (auto&& n: names) {

    }
}