#include <iosfwd>
class Box
{
    public:
    unsigned int length, width, height;

    Box()
    {
        length = 0, width = 0, height = 0;
    }
    Box(unsigned int l, unsigned int w, unsigned int h)
    {
        length = l;
        width = w;
        height = h;
    }
    Box(const Box& box)
    {
        length = box.length;
        width = box.width;
        height = box.height;
    }

    Box& operator=(const Box& other) {
        return *this;
    }

    unsigned int getVolume() const {
        return length * width * height;
    }

    void scale(unsigned int scaleValue)
    {
        length *= scaleValue;
        width *= scaleValue;
        height *= scaleValue;
    }

    bool isBigger(const Box& other)
    {
        if (other.getVolume() > getVolume()) {
            return true;
        }
        return false;
    }

    bool isSmaller(const Box& other)
    {
        if (other.getVolume() < getVolume()) {
            return true;
        }
        return false;
    }

    Box operator*(unsigned int scale) const
    {
        return Box(scale * length, scale * width, scale * height);
    }

    friend Box operator*(unsigned int scale, const Box& box)
    {
        return box * scale;
    }

    bool operator==(const Box& other) const {
        return length == other.length && width == other.width && height == other.height;
    }
};

class Cube
{
    public:
    unsigned int length;
    unsigned int width;
    unsigned int height;
    Cube ()
    {
        length = 0, width = 0, height = 0;
    }
    Cube(unsigned int l, unsigned int w, unsigned int h)
    {
        length = l;
        width = w;
        height = h;
    }
    Cube(Box& box)
    {
        box.length = length;
        box.width = width;
        box.height = height;
    }
};
