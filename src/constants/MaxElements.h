#ifndef MAX_ELEMENTS_H
#define MAX_ELEMENTS_H

#if (GSLC_USE_PROGMEM)
#define MAX_ELEM_PG_MAIN_PROG 19 // # Elems in Flash
#define MAX_ELEM_PG_XYMAP_PROG 8 // # Elems in Flash
#else
#define MAX_ELEM_PG_MAIN_PROG 0 // # Elems in Flash
#define MAX_ELEM_PG_XYMAP_PROG 0 // # Elems in Flash
#endif

#define MAX_ELEM_PG_MAIN 42 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN - MAX_ELEM_PG_MAIN_PROG // # Elems in RAM

#define MAX_ELEM_PG_XYMAP 8 // # Elems total on page
#define MAX_ELEM_PG_XYMAP_RAM MAX_ELEM_PG_XYMAP - MAX_ELEM_PG_XYMAP_PROG // # Elems in RAM

#define MAX_STR 100

#endif // MAX_ELEMENTS_H