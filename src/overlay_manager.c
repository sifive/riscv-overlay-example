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
        void* load_text_start;
        void* load_text_stop;
        void* load_data_start;
        void* load_data_stop;
        void* load_bss_start;
        void* load_bss_stop;
} overlay_region_t;

/* Record for current overlay */
int current_overlay = 0;

/* Array describing the overlays */
overlay_region_t overlay_regions[NUM_OVERLAYS];


/* Exported by linker script */
extern void * const __overlay_text;
extern void * const __overlay_data;
extern void * const __overlay_bss;

extern void * const __load_start_overlay_text1;
extern void * const __load_stop_overlay_text1;

extern void * const __load_start_overlay_bss1;
extern void * const __load_stop_overlay_bss1;

extern void * const __load_start_overlay_data1;
extern void * const __load_stop_overlay_data1;

extern void * const __load_start_overlay_text2;
extern void * const __load_stop_overlay_text2;

extern void * const __load_start_overlay_bss2;
extern void * const __load_stop_overlay_bss2;

extern void * const __load_start_overlay_data2;
extern void * const __load_stop_overlay_data2;

static void initialize_overlay()
{
  overlay_regions[0].load_text_start = __load_start_overlay_text1;
  overlay_regions[0].load_text_stop = __load_start_overlay_text1;
  overlay_regions[0].load_data_start = __load_start_overlay_data1;
  overlay_regions[0].load_data_stop = __load_start_overlay_data1;
  overlay_regions[0].load_bss_start = __load_start_overlay_bss1;
  overlay_regions[0].load_bss_stop = __load_start_overlay_bss1;

  overlay_regions[1].load_text_start = __load_start_overlay_text2;
  overlay_regions[1].load_text_stop = __load_start_overlay_text2;
  overlay_regions[1].load_data_start = __load_start_overlay_data2;
  overlay_regions[1].load_data_stop = __load_start_overlay_data2;
  overlay_regions[1].load_bss_start = __load_start_overlay_bss2;
  overlay_regions[1].load_bss_stop = __load_start_overlay_bss2;
}

void load_overlay(int n)
{
    static bool initialized = false;
    if (!initialized)
    {
      initialize_overlay();
      initialized = true;
    }

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
    memcpy(__overlay_text,
           selected_region->load_text_start,
           selected_region->load_text_stop - selected_region->load_text_start);

    /* load data overlay */
    memcpy(__overlay_data,
           selected_region->load_data_start,
           selected_region->load_data_stop - selected_region->load_data_start);

    /* Comment out the next line if your overlays have any static ZI variables
     * and should not be reinitialized each time, and move them out of the
     * overlay region in your scatter file */
    memset(selected_region->load_bss_start,
           0,
           selected_region->load_bss_stop - selected_region->load_bss_start);

    /* update record of current overlay */
    current_overlay=n;

    printf("...Done.\n");

}
