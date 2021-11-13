#include <at89x52.h>
#include "util.h"

#include "scanner.h"
#include "images/love.h"
#include "images/hearts.h"
#include "images/hope.h"

// the current column of the image being displayed, 255 if the image is done
volatile uchar image_progress = 0;
// total number of columns in the current image
uchar image_cols = 0;
// pointer to the start of the current image
ushort *image_ptr = 0;

void show_image()
{
    // leave some free time after the shake sensor triggered
    if (image_progress == 0)
        sleep(8000);

    if (image_progress < image_cols)
    {
        // display the next column of the image
        ushort col = image_ptr[image_progress++];
        show_column(col);
    }
    else
    {
        // we reached the end of the image, turn off the LEDs
        // and wait for the next sensor trigger
        show_column(0);
        // mark the image as done, so the interrupt can reset it
        image_progress = 255;
    }
    sleep(120);
}

void set_image(ushort *ptr, uchar cols)
{
    image_ptr = ptr;
    image_cols = cols;
    image_progress = 0;
}

// this will be triggered by the shake sensor
void intersvr0(void) __interrupt(0)
{
    // reset the image if done
    if (image_progress == 255)
        image_progress = 0;
}

// the function that will be called in the main loop
void (*step)(void) = scanner;

// switch to the next mode
// if you want to add more modes, add them here
void next_mode()
{
    static uchar mode = 0;
    mode = (mode + 1) % 5;
    switch (mode)
    {
    case 0:
        step = scanner;
        break;
    case 1:
        step = scanner_back;
        break;
    case 2:
        set_image(love, love_cols);
        step = show_image;
        break;
    case 3:
        set_image(hearts, hearts_cols);
        break;
    case 4:
        set_image(hope, hope_cols);
        break;
    }
}

void main()
{
    // setting up interrupts...
    IT0 = 1;
    EX0 = 1;
    EA = 1;

    while (1)
    {
        step();

        if (!P3_7)
        {
            // the mode-switch button was pressed
            next_mode();

            // wait for the button to be released again
            while (!P3_7)
                ;
        }
    }
}