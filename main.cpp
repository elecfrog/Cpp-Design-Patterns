#include <iostream>
#include <vector>
#include <QString>
#include <QDebug>
#include <fstream>
#include "Movie.hpp"

using namespace elf;


int main() {
    auto movie = Movie{{}};
    movie.AddTag("nmsl");
    std::cout << "Hello, World!" << std::endl;
    return 0;
}


