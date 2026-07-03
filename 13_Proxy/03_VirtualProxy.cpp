#include "../header.h"

struct Image {
    virtual void draw() = 0;    
};

// lets say we cant modify it (either open-close or unlucky)
struct Bitmap : Image {
    Bitmap(const string& filename) {
        cout << "Loading bitmap from " << filename << endl;
    }

    void draw() override {
        cout << "Drawing bitmap" << endl;
    }
};

// build a virtual proxy - same IF, but not the same implementation
struct LazyBitmap : Image {
private:
    string filename;
    Bitmap *bitmap{nullptr}; // unique_ptr<Bitmap> bitmap; to stop memory leak

public:
    LazyBitmap(const string& filename) : filename(filename) {}

    void draw() override {
        if (!bitmap) {
            bitmap = new Bitmap(filename); // if unique ptr - bitmap = make_unique<Bitmap>(filename);
        }
        bitmap->draw();
    }
};

int main()
{
    // Bitmap bitmap{"my_file.bmp"};
    LazyBitmap bitmap{"my_file.bmp"}; // thats all we need to do
    bitmap.draw();

    return 0;
}
