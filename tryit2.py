

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
    f = make_box_filter(3)
    blur = convolve_image(im, f, 0)
    save_image(blur, directory_name + "box_filter")


if __name__ == "__main__":
    create_photos_directory()
    #  nn_interpolate_verification()
    # bilinear_interpolate_verification()
    test_convolution()