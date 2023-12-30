// overlay_stub.c
extern void func1(void);
extern void func2(void);

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
