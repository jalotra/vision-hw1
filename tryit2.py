

# Python module to test all the written functions

from uwimg import *
import os
import sys

directory_name = "Tryit2Photos/"

def create_photos_directory():    
    try:
        os.mkdir(path = os.path.join(os.getcwd(), directory_name), mode = 777 )
    except FileExistsError:
        pass

def nn_interpolate_verification():
    im = load_image("data/dogsmall.jpg")
    a = nn_resize(im, im.w*8, im.h*8)
    save_image(a, directory_name  + "dog4x-nn")

def bilinear_interpolate_verification():
    im = load_image("data/dogsmall.jpg")
    a = bilinear_resize(im, im.w*8, im.h*8)
    save_image(a, directory_name + 'bilinear_dog_4x' )

def test_convolution():
    im = load_image("data/ron.png")
    f = make_box_filter(7)
    blur = convolve_image(im, f, 0)
    save_image(blur, directory_name + "box_filter")

#  This function doesn't work
#  There is a implementation error
# def shrink_after_convolution():
    # im = load_image("data/dog.jpg")
    # f = make_box_filter(7)
    # blur = convolve_image(im, f, 1)
    # thumb = nn_resize(blur, blur.w//7, blur.h//7)        
    # save_image(thumb, directory_name+"dogthumb")

def test_highpass_filter():
    im = load_image("data/dog.jpg")
    f = make_highpass_filter()
    blur = convolve_image(im, f, 1)
    save_image(blur, directory_name + "test_highpass_filter")

def test_sharpen_filter():
    im = load_image("data/dog.jpg")
    # g = make_gaussian_filter(3)
    # blur = convolve_image(im, g, 1)
    f = make_sharpen_filter()
    blur = convolve_image(im, f, 1)
    save_image(blur, directory_name + "test_sharpen_filter")

def test_emboss_filter():
    im = load_image("data/dog.jpg")
    f = make_emboss_filter()
    blur = convolve_image(im, f, 1)
    save_image(blur, directory_name + "test_emboss_filter")

def test_add_substract():
    im = load_image("data/dog.jpg")
    f = make_gaussian_filter(3)
    lfreq = convolve_image(im, f, 1)
    hfreq = im - lfreq
    reconstruct = lfreq + hfreq
    save_image(lfreq, directory_name + "low-frequency")
    save_image(hfreq, directory_name + "high-frequency")
    save_image(reconstruct, directory_name + "reconstruct")

def test_gaussian_function():
    im = load_image("data/ron.png")
    f = make_gaussian_filter(3)
    blur = convolve_image(im, f, 1)
    save_image(blur, directory_name + "dog-gauss2")

def create_ron_image():
    im = load_image("data/ron.png")
    f = make_gaussian_filter(3.5)
    blur = im - convolve_image(im, f, 1)

    return blur

def create_dumbledore_image():
    im = load_image("data/dumbledore.png")
    f = make_gaussian_filter(1.5)
    blur = convolve_image(im, f, 1)

    return blur

def final_addition_ron_dumbledore(m1 = create_dumbledore_image(), m2 = create_ron_image()):
    final_im = m1 + m2 
    save_image(final_im, directory_name + "ron_dumbledore_hybrid")    



# def create_hybrid_ron_dombeldore():
#     # the dumbeldores low frequency has to be added to ron's high frequency
#     ron_im = load_image("data/ron.png")
#     dumbledore_im = load_image("data/dumbledore.png")
#     f = make_gaussian_filter(2)
#     lfreq_dumbledore = convolve_image(dumbledore_im, f, 1)
#     high_freq_ron = ron_im - convolve_image(ron_im, f, 1)

#     # FiNALLY ADD THESE images
#     final_im = dumbledore_im + ron_im
#     save_image(final_im, directory_name + "ron_dumbledore_hybrid")

def gradient_x():
    im = load_image("data/dog.jpg")
    f = make_gx_filter()
    blur = convolve_image(im, f, 0)
    feature_normalize(blur)
    save_image(blur, directory_name + "gradient_x")

def gradient_y():
    im = load_image("data/dog.jpg")
    f = make_gx_filter()
    blur = convolve_image(im, f, 0)
    feature_normalize(blur)
    save_image(blur, directory_name + "gradient_y")


def gradient_mag_and_direction():
    im = load_image("data/dog.jpg")
    res = sobel_image(im)
    mag = res[0]
    feature_normalize(mag)
    save_image(mag, directory_name + "magnitude")  

def test_colorise_sobel():
    im = load_image("data/dog.jpg")
    res = colorize_sobel(im)
    feature_normalize(res)
    save_image(res, directory_name + "colorise_sobel")  






if __name__ == "__main__":
    create_photos_directory()
    nn_interpolate_verification()
    bilinear_interpolate_verification()
    test_convolution()
    # shrink_after_convolution()
    test_highpass_filter()
    test_sharpen_filter()
    test_emboss_filter()
    test_add_substract()
    test_gaussian_function()
    final_addition_ron_dumbledore()
    gradient_y()
    gradient_x()
    gradient_mag_and_direction()
    test_colorise_sobel()