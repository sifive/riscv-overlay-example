// overlay_manager.c
/* Basic overlay manager */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Number of overlays present */
#define NUM_OVERLAYS 2

/* struct to hold addresses and lengths */
typedef struct overlay_region_t_struct
{
  void* load_text_base;
  void* load_data_base;
  unsigned int text_length;
  unsigned int data_length;
  unsigned int bss_length;
} overlay_region_t;

/* Record for current overlay */
int current_overlay = 0;

/* Array describing the overlays */
extern overlay_region_t overlay_regions[NUM_OVERLAYS];


/* Exported by linker script */
extern void * code_base;
extern void * data_base;
extern void * bss_base;


void load_overlay(int n)
{
    const overlay_region_t * selected_region;

    if(n == current_overlay)
    {
        printf("Overlay %d already loaded.\n", n);
        return;
    }

    /* boundary check */
    if(n<1 || n>NUM_OVERLAYS)
    {
        printf("Error - invalid overlay number %d specified\n", n);
        exit(1);
    }

    /* Load the corresponding overlay */
    printf("Loading overlay %d...\n", n);

    /* set selected region */
    selected_region = &overlay_regions[n-1];

    /* load code overlay */
    printf("  Loading text ...\n");
    printf("    VMA: %p\n", &code_base);
    printf("    start: %p\n", selected_region->load_text_base);
    printf("    length: %d bytes\n", selected_region->text_length);
    memcpy(&code_base, selected_region->load_text_base, selected_region->text_length);

    /* load data overlay */
    printf("  Loading data ...\n");
    printf("    VMA: %p\n", &data_base);
    printf("    start: %p\n", selected_region->load_data_base);
    printf("    length: %d bytes\n", selected_region->data_length);
    memcpy(&data_base, selected_region->load_data_base, selected_region->data_length);

    /* Comment out the next line if your overlays have any static ZI variables
     * and should not be reinitialized each time, and move them out of the
     * overlay region in your scatter file */
    printf("  Loading bss ...\n");
    printf("    start: %p\n", &bss_base);
    printf("    length: %d bytes\n", selected_region->bss_length);
    memset(&bss_base, 0, selected_region->bss_length);

    /* update record of current overlay */
    current_overlay=n;

    printf("...Done.\n");

}
