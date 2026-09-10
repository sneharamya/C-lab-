#include<iostream>
#include <cstring>
using namespace std;

class MyString {
    char *data;
    public:
    MyString (const char *s){
        data=new char [strlen(s)+1];
        strcpy (data,s);
    }
    MyString (const MyString &o){
        data=new char [strlen(o.data)+1];
        strcpy (data, o.data);
    }
    ~MyString () {delete [ ] data;}
    void Print () const {cout <<data<<endl;}
};
int main (){
MyString a ("Hardware");
MyString b=a;
a.Print();
b.Print();
return 0;
}
