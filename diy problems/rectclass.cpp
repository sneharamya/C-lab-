#include <iostream>
using namespace std;

class Rectangle
{
private:
    float length;
    float width;

public:
    void setLength(float l)
    {
        if (l >= 0)
            length = l;
        else
            cout << "Invalid length!" << endl;
    }

    void setWidth(float w)
    {
        if (w >= 0)
            width = w;
        else
            cout << "Invalid width!" << endl;
    }

    float getLength()
    {
        return length;
    }

    float getWidth()
    {
        return width;
    }

    float area()
    {
        return length * width;
    }

    float perimeter()
    {
        return 2 * (length + width);
    }
};

int main()
{
    Rectangle r;

    r.setLength(10);
    r.setWidth(5);

    cout << "Length = " << r.getLength() << endl;
    cout << "Width = " << r.getWidth() << endl;
    cout << "Area = " << r.area() << endl;
    cout << "Perimeter = " << r.perimeter() << endl;

    return 0;
}