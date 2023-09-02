#include <iostream>
#include <string>
#include <sstream>
#include <memory>

// Abstract class representing an Image with a draw function
struct Image {
    virtual ~Image() = default;

    virtual void draw() = 0;
};

// Bitmap representation of an Image
struct Bitmap : Image {
    Bitmap(const std::string &filename) {
        std::cout << "Loading image from " << filename << std::endl;
    }

    void draw() override {
        std::cout << "Drawing image" << std::endl;
    }
};

// Lazy loading of Bitmap
struct LazyBitmap : Image {
    LazyBitmap(const std::string &filename) : filename(filename) {}

    ~LazyBitmap() { delete bmp; }

    void draw() override {
        if (!bmp)
            bmp = new Bitmap(filename);
        bmp->draw();
    }

private:
    Bitmap *bmp{nullptr};
    std::string filename;
};

void draw_image(Image &img) {
    std::cout << "About to draw the image" << std::endl;
    img.draw();
    std::cout << "Done drawing the image" << std::endl;
}

bool Testing() {
    Bitmap imgBit{"pokemon.png"};
    draw_image(imgBit); // loaded whether the bitmap is loaded or not

    LazyBitmap img{"pokemon.png"};
    draw_image(img);
    return true;
}

int main() {
    return Testing();
}
