// overlay_stub.c
extern void __real_func1(void);
extern void __real_func2(void);
extern void __real__ZN3Foo3fooEv(void);
extern void __real__ZN3Bar3barEv(void);

extern void load_overlay(int n);

void __wrap_func1(void)
{
    load_overlay(1);
    __real_func1();
}

void __wrap_func2(void)
{
    load_overlay(2);
    __real_func2();
}


void __wrap__ZN3Foo3fooEv(void)
{
    load_overlay(3);
    __real__ZN3Foo3fooEv();
}

void __wrap__ZN3Bar3barEv(void)
{
    load_overlay(4);
    __real__ZN3Bar3barEv();
}
