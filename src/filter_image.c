#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#define TWOPI 6.2831853

void l1_normalize(image im)
{
    // TODO
    // TO normalize the sum of image across all channels to 1
    for(int channel = 0; channel < im.c; channel++)
    {
        for(int row = 0 ; row < im.h ; row++)
        {
            for(int column = 0; column < im.h; column++)
            {
                float pixel_value= get_pixel(im, column, row, channel);

                set_pixel(im, column, row, channel, pixel_value/(im.w*im.h));
        }
    }
        
}
}

image make_box_filter(int w)
{
    // TODO
    // return make_image(1,1,1);
    // Creates a box filter with one channel and then normalise it 
    image new_image = make_image(w, w, 1);
    // NOw set all the values to 1
    for(int channel = 0; channel < new_image.c; channel ++)
    {
        for(int row = 0; row < w ; row++)
        {
            for(int column = 0 ; column < w; column++)
            {
                set_pixel(new_image, column, row, channel, 1);
            }
        }
    }
    

    // Finally normalise the box-filter
    l1_normalize(new_image);

    return new_image;

}


float box_filter_result(image im, image filter, int row, int column, int channel, int preserve)
{
    float q = 0;
    int f_c;

    if(filter.c == 1) f_c = 0 ;
    else f_c = channel;

    for(int frow = 0; frow < filter.h; frow++) {
        for(int fcol = 0; fcol < filter.w; fcol++) {
          //  float before = q;
            float fil = get_pixel(filter, fcol, frow, f_c);
            int fx = column + fcol - filter.w/2;
            int fy = row + frow - filter.h/2;
            float im_val = get_pixel(im, fx, fy, channel);
            q = q + (fil * im_val);
        }
    }

    return q;
}

image convolve_image(image im, image filter, int preserve)
{
    // TODO
    // return make_image(1,1,1);

    // Actually convolution is the the cross-correlation between the filter and the image

    // 1. If the number of channels in the filter is same as the the number of channels in
    // im image. Then compute the filter spatially on differnet channels and take the average of the
    // pixel values at all the locations within image. So finally getting a 1 channel image.

    // 2. If preserve is set to 1 the final image should have the number of channels to be presered.

    //3. THe channel can have only 1 channel or same number of channels as that of image im
    // Check this with the help of assert

    // Checking if the number of channels in filter is 1 or equal to im.c
    assert(filter.c == 1 || filter.c == im.c);


     //Create a convolved image
    image convolved_image;
    if(preserve) convolved_image = make_image(im.w, im.h, im.c);
    else convolved_image = make_image(im.w, im.h, im.c);

    if(preserve == 0 )
    {   

        for(int channel = 0; channel < convolved_image.c; channel++)
        {
            for(int column = 0; column < convolved_image.w; column++)
            {
                // float value = 0;

                for(int row = 0; row < convolved_image.h ; row++)
                {   

                    set_pixel(im, column, row, channel, box_filter_result(im, filter, row, column, channel, preserve));

                    // value += get_pixel(im, column, row, channel);
                    
                }
                // set_pixel(convolved_image, column, row, value, 1);

            }
        }

        for(int column = 0; column < im.w ; column++)
        { 
            for(int row = 0; row < im.h ; row++)
            {
                float r_pixel = get_pixel(im, column, row, 0);
                float g_pixel = get_pixel(im, column, row, 1);
                float b_pixel = get_pixel(im, column, row, 2);

                set_pixel(convolved_image, column, row, 0, (r_pixel + g_pixel + b_pixel)/3);

            }
        }
    }


    if(preserve == 1)
    {

        for(int channel = 0; channel < convolved_image.c; channel++)
        {
            for(int column = 0; column < convolved_image.w; column++)
            {
                // float value = 0;

                for(int row = 0; row < convolved_image.h ; row++)
                {   

                    set_pixel(convolved_image, column, row, channel, box_filter_result(im, filter, row, column, channel, preserve));

                    // value += get_pixel(im, column, row, channel) 
                    
                }
                // set_pixel(convolved_image, column, row, value);

            }
        }
    }

    return convolved_image;
}


image make_highpass_filter()
{
    // TODO

    // highpass filter involves the use pf sobel filter
    image highpass_filter = make_image(3,3,1);
    // Fill the zeoes
    set_pixel(highpass_filter, 0, 0, 0, 0);
    set_pixel(highpass_filter, 2, 0, 0, 0);
    set_pixel(highpass_filter, 0, 2, 0, 0);
    set_pixel(highpass_filter, 2, 2, 0, 0);

    // Fill -1s
    set_pixel(highpass_filter, 1, 0, 0, -1);
    set_pixel(highpass_filter, 0, 1,0, -1);
    set_pixel(highpass_filter, 2, 1, 0,-1);
    set_pixel(highpass_filter, 1, 2, 0,-1);

    // fill 4
    set_pixel(highpass_filter, 1, 1,0, 4);



    return highpass_filter;
}

image make_sharpen_filter()
{
    // TODO
     image sharpen_filter = make_image(3,3,1);
    // Fill the zeoes
    set_pixel(sharpen_filter, 0, 0, 0, 0);
    set_pixel(sharpen_filter, 2, 0, 0, 0);
    set_pixel(sharpen_filter, 0, 2, 0, 0);
    set_pixel(sharpen_filter, 2, 2, 0, 0);

    // Fill -1s
    set_pixel(sharpen_filter, 1, 0, 0, -1);
    set_pixel(sharpen_filter, 0, 1,0, -1);
    set_pixel(sharpen_filter, 2, 1, 0,-1);
    set_pixel(sharpen_filter, 1, 2, 0,-1);

    // fill 4
    set_pixel(sharpen_filter, 1, 1,0, 5);



    return sharpen_filter;
}

image make_emboss_filter()
{
    // TODO
    image emboss_filter = make_image(3,3,1);
    // Fill the zeoes
    set_pixel(emboss_filter, 0, 0, 0, -2);
    set_pixel(emboss_filter, 2, 0, 0, 0);
    set_pixel(emboss_filter, 0, 2, 0, 0);
    set_pixel(emboss_filter, 2, 2, 0, 2);

    // Fill -1s
    set_pixel(emboss_filter, 1, 0, 0, -1);
    set_pixel(emboss_filter, 0, 1,0, -1);
    set_pixel(emboss_filter, 2, 1, 0,1);
    set_pixel(emboss_filter, 1, 2, 0,-1);

    // fill 4
    set_pixel(emboss_filter, 1, 1,0, 1);



    return emboss_filter;
}

// Question 2.2.1: Which of these filters should we use preserve when we run our convolution and which ones should we not? Why?
// Answer: TODO

// Question 2.2.2: Do we have to do any post-processing for the above filters? Which ones and why?
// Answer: TODO

image make_gaussian_filter(float sigma)
{
    // TODO
    return make_image(1,1,1);
}

image add_image(image a, image b)
{
    // TODO
    return make_image(1,1,1);
}

image sub_image(image a, image b)
{
    // TODO
    return make_image(1,1,1);
}

image make_gx_filter()
{
    // TODO
    return make_image(1,1,1);
}

image make_gy_filter()
{
    // TODO
    return make_image(1,1,1);
}

void feature_normalize(image im)
{
    // TODO
}

image *sobel_image(image im)
{
    // TODO
    return calloc(2, sizeof(image));
}

image colorize_sobel(image im)
{
    // TODO
    return make_image(1,1,1);
}
