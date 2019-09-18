

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
    im = load_image("data/ron.png")
    a = nn_resize(im, im.w/2, im.h/2)
    save_image(a, directory_name  + "dog4x-nn")

def bilinear_interpolate_verification():
    im = load_image("data/dogsmall.jpg")
    a = bilinear_resize(im, im.w*8, im.h*8)
    save_image(a, directory_name + 'bilinear_dog_4x' )

def test_convolution():
    im = load_image("data/dog.jpg")
    f = make_box_filter(7)
    blur = convolve_image(im, f, 1)
    save_image(blur, directory_name + "box_filter")

def shrink_after_convolution():
    im = load_image("data/dog.jpg")
    f = make_box_filter(7)
    blur = convolve_image(im, f, 1)
    thumb = nn_resize(blur, blur.w//7, blur.h//7)
    save_image(thumb, directory_name+"dogthumb")

def test_highpass_filter():
    im = load_image("data/dog.jpg")
    f = make_highpass_filter()
    blur = convolve_image(im, f, 1)
    save_image(blur, directory_name + "test_highpass_filter")

def test_sharpen_filter():
    im = load_image("data/dog.jpg")
    f = make_sharpen_filter()
    blur = convolve_image(im, f, 1)
    save_image(blur, directory_name + "test_sharpen_filter")

def test_emboss_filter():
    im = load_image("data/dog.jpg")
    f = make_emboss_filter()
    blur = convolve_image(im, f, 1)
    save_image(blur, directory_name + "test_emboss_filter")


if __name__ == "__main__":
    create_photos_directory()
    #  nn_interpolate_verification()
    # bilinear_interpolate_verification()
    # test_convolution()
    # shrink_after_convolution()
    test_highpass_filter()
    test_sharpen_filter()
    test_emboss_filter()