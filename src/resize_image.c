#include <math.h>
#include "image.h"

float nn_interpolate(image im, float x, float y, int c)
{
    // ALgorithmic steps 
    // what is a nn algorithm?
    // we are given a (x,y) value representing the column , row of the newly made image
    // Now suppose that the points given

    int nearest_x, nearest_y;
    // It should return the nearest value 
    nearest_x = (floor(x) < ceil(x)) ? floor(x) : ceil(x);
    nearest_y = (floor(y) < floor(y)) ? floor(y) : ceil(y);

    return get_pixel(im, nearest_x, nearest_y, c);          // return the pixel value in the image 

    // return 0;
}

image nn_resize(image im, int w, int h)
{
    // TODO Fill in (also fix that first line)
    image new_image = make_image(w ,h, im.c);           // creates a new image of the size (w*h*im.c)
    int row_scaling_factor = h/im.h;                    // denotes the scaling factor in y direction
    int column_scaling_factor = w/im.w;                 // denotes the scaling factor in x direction
    for(int column = 0 ; column < w ; column++)
    {
        for(int row = 0; row < h; row ++)
        {
            // pixel = get_pixel(round(x), round(y), c)
            float r_new_image = nn_interpolate(im, column/column_scaling_factor, row/row_scaling_factor, 0);
            float g_new_image = nn_interpolate(im, column/column_scaling_factor, row/row_scaling_factor, 1);
            float b_new_image = nn_interpolate(im, column/column_scaling_factor, row/row_scaling_factor, 2);

            // Now set these pixels in the new_image created
            set_pixel(new_image, column, row, 0, r_new_image);
            set_pixel(new_image, column, row, 1, g_new_image);
            set_pixel(new_image, column, row, 2, b_new_image);
        }
    }

    return new_image;

}

float bilinear_interpolate(image im, float x, float y, int c)
{
    // TODO
    return 0;
}

image bilinear_resize(image im, int w, int h)
{
    // TODO
    return make_image(1,1,1);
}

