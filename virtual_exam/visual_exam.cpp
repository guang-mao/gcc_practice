#include <iostream>
using namespace std;

class Foo1{
public:
    virtual void show(){
        cout << "Foo1's show" << endl;
    }
};

class Foo2 : public Foo1 {
public:
    virtual void show(){
        cout << "Foo2's show" << endl;
    }
};

class Foo3{
public:
    virtual void show(){
        cout << "Foo3's show" << endl;
    }
};

class Foo4 : public Foo3{
public:
    virtual void show(){
        cout << "Foo4's show" << endl;
    }
};

void showFooByPtr(Foo1 *foo){
    foo->show();
}

void showFooByRef(Foo1 &foo){
    foo.show();
}

Foo4 f4;
Foo3 *f3 = &f4;  //if you want to use pointer and reference in class, you have to do that with inheritance and virtual in your class.
int main()
{
    Foo1 f1;
    Foo2 f2;

    showFooByPtr(&f1);
    showFooByPtr(&f2);
    cout << endl;

    showFooByRef(f1);
    showFooByRef(f2);
    cout << endl;

    f1.show();
    f2.show();
    cout << endl;

    f3->show();

    return 0;
}
