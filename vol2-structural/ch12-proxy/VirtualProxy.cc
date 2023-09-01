#include <iostream>
#include <string>
#include <sstream>
#include <memory>

using namespace std;

struct Image {
    virtual ~Image() = default;

    virtual void draw() = 0;
};

struct Bitmap : Image {
    Bitmap(const string &filename) {
        cout << "Loading image from " << filename << endl;
    }

    void draw() override {
        cout << "Drawing image" << endl;
    }
};

struct LazyBitmap : Image {
    LazyBitmap(const string &filename) : filename(filename) {}

    ~LazyBitmap() { delete bmp; }

    void draw() override {
        if (!bmp)
            bmp = new Bitmap(filename);
        bmp->draw();
    }

private:
    Bitmap *bmp{nullptr};
    string filename;
};

void draw_image(Image &img) {
    cout << "About to draw the image" << endl;
    img.draw();
    cout << "Done drawing the image" << endl;
}

bool Testing() {
    Bitmap imgBit{"pokemon.png"};
    draw_image(imgBit); // loaded whether the bitmap is loaded or not

    LazyBitmap img{"pokemon.png"};
    draw_image(img);
    return true;
}

int main()
{
    return Testing();
}
