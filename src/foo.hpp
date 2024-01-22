struct Foo
{
    // demo for normal member method
    int foo();

    // demo for virtual method
    virtual int bar();  
};

struct Bar: Foo
{
    int bar() override;
};
