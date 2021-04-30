//
// Created by xiaofan on 2021/4/30.
//

//MUPDF_ALL_IN_ONE_H
/*
Multi-threaded rendering of all pages in a document to PNG images.
look at docs/examples/multi-thread.c
*/
#ifndef MUPDF_ALL_IN_ONE_H
#define MUPDF_ALL_IN_ONE_H

#endif
//Include the MuPDF header file, and pthread's header file.
#include <mupdf/fitz.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// The data structure passed between the requesting main thread and
// each rendering thread.

struct render_data {
    // A pointer to the original context in the main thread sent
    // from main to rendering thread. It will be used to create
    // each rendering thread's context clone.
    fz_context *ctx;

    // Page number sent from main to rendering thread for printing
    int pagenumber;

    // The display list as obtained by the main thread and sent
    // from main to rendering thread. This contains the drawing
    // commands (text, images, etc.) for the page that should be
    // rendered.
    fz_display_list *list;

    // The area of the page to render as obtained by the main
    // thread and sent from main to rendering thread.
    fz_rect bbox;

    // This is the result, a pixmap containing the rendered page.
    // It is passed first from main thread to the rendering
    // thread, then its samples are changed by the rendering
    // thread, and then back from the rendering thread to the main
    // thread.
    fz_pixmap *pix;
};

// This is the function run by each rendering function. It takes
// pointer to an instance of the data structure described above and
// renders the display list into the pixmap before exiting.
void * renderer(void *data);

// These are the two locking functions required by MuPDF when
// operating in a multi-threaded environment. They each take a user
// argument that can be used to transfer some state, in this case a
// pointer to the array of mutexes.

void lock_mutex(void *user, int lock);

void unlock_mutex(void *user, int lock);


typedef struct fz_pfd_convert_png_output {
    const unsigned char**pngBytes;
    int pageCount;
    char *err;
} fz_pfd_convert_png_output;

fz_pfd_convert_png_output *fz_multi_thread_convert_pages_to_png(const unsigned char *data, size_t len, float dpi);


