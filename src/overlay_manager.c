// overlay_manager.c
/* Basic overlay manager */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Defined and exported by linker script */
extern void * code_base;
extern void * data_base;
extern void * bss_base;

/* Defined automatically with OVERLAY keyword in linker script.  */
extern void *__load_start_code_func1;
extern void *__load_stop_code_func1;
extern void *__load_start_data_func1;
extern void *__load_stop_data_func1;

extern void *__load_start_code_func2;
extern void *__load_stop_code_func2;
extern void *__load_start_data_func2;
extern void *__load_stop_data_func2;

extern void *__load_start_code_foo;
extern void *__load_stop_code_foo;
extern void *__load_start_data_foo;
extern void *__load_stop_data_foo;

/* 'overlay' is declared in linker script.
 * 
 */
#define LOAD_OVERLAY(vma, overlay) \
    printf("  Loading section %s\n", "overlay"); \
    printf("    VMA: %p\n", &vma); \
    printf("    LMA: %p\n", &__load_start_##overlay); \
    printf("    length: %ld bytes\n", &__load_stop_##overlay - &__load_start_##overlay); \
    memcpy(&vma, \
           &__load_start_##overlay, \
           &__load_stop_##overlay - &__load_start_##overlay);



void load_overlay(int n)
{

    /* Record for current overlay */
    static int current_overlay = 0;

    if (n == current_overlay)
    {
        printf("Overlay %d already loaded.\n", n);
        return;
    }

    /* Load the corresponding overlay */
    printf("Loading overlay %d...\n", n);
    switch (n) {
      case 1:
        LOAD_OVERLAY(code_base, code_func1);
        LOAD_OVERLAY(data_base, data_func1);
        break;

      case 2:
        LOAD_OVERLAY(code_base, code_func2);
        LOAD_OVERLAY(data_base, data_func2);
        break;

      case 3:
        LOAD_OVERLAY(code_base, code_foo);
        LOAD_OVERLAY(code_base, data_foo);
        break;

      default:
        printf("Error - invalid overlay number %d specified\n", n);
        exit(1);
        break;    
    }


    /* update record of current overlay */
    current_overlay=n;

    printf("...Done.\n");
}
