#include <vector>
using namespace std;

/*
Example 1:
    [1,2,3]
    [8,9,4]
    [7,6,5]
    Input: n = 3
    Output: [[1,2,3],[8,9,4],[7,6,5]]

Example 2:

    Input: n = 1
    Output: [[1]]

 */

vector<vector<int>> generateMatrix(int n) {

    // initialize a 2D matrix with 0
    vector<vector<int>> ret(n, vector<int>(n, 0));

    // start point of the looping
    int startX = 0;
    int startY = 0;

    // 2 * 4 = 8
    // 3 * 4 = 12
    // length of the length * 4 = the number of elements most outside 
    int currLength = n - 1;
    // current value of node
    int currValue = 1;

    // define odd as the situation of odd, 
    // while it only has 0 or 1 here, so, 
    // it also is a bool 
    int odd = n % 2;
    while (currLength > odd) {
        // => Right
        for (int idx = 0; idx < currLength; ++idx) {
            ret[startX][startY] = currValue++;
            startY++;
        }

        // => Down
        for (int idx = 0; idx < currLength; ++idx) {
            ret[startX][startY] = currValue++;
            startX++;
        }

        // => Left
        for (int idx = 0; idx < currLength; ++idx) {
            ret[startX][startY] = currValue++;
            startY--;
        }

        // => Up
        for (int idx = 0; idx < currLength; ++idx) {
            ret[startX][startY] = currValue++;
            startX--;
        }
        // update start points
        startX++;
        startY++;
        // each loop solves two boundaries in row and column
        currLength -= 2;
    }

    // solving the center point if odd
    if (odd) {
        int mid = n / 2;
        ret[mid][mid] = currValue;
    }


    // return mat
    return ret;
}

int main() {
    auto mat = generateMatrix(5);
    
    return 0;
}