#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<int> myVector{1, 2, 3, 4, 5, 6, 7, 8};

    int myArr2D[2][3] = {
            {0, 1, 2},
            {3, 4, 5}
    };
    cout << &myArr2D[0][0] << " " << &myArr2D[0][1] << " " << &myArr2D[0][2] << endl;
    cout << &myArr2D[1][0] << " " << &myArr2D[1][1] << " " << &myArr2D[1][2] << endl;
    
    // 000000EED82FF990 000000EED82FF994 000000EED82FF998
    // 000000EED82FF99C 000000EED82FF9A0 000000EED82FF9A4
    
    return 0;
}