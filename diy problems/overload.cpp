#include <iostream>
using namespace std;

// Volume of cube
int volume(int side)
{
    return side * side * side;
}

// Volume of cylinder
float volume(float radius, float height)
{
    return 3.14 * radius * radius * height;
}

// Volume of cuboid
int volume(int length, int breadth, int height)
{
    return length * breadth * height;
}

int main()
{
    cout << "Volume of cube = " << volume(5) << endl;
    cout << "Volume of cylinder = " << volume(3.0f, 5.0f) << endl;
    cout << "Volume of cuboid = " << volume(4, 5, 6) << endl;

    return 0;
}