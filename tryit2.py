

# Python module to test all the written functions

from uwimg import *
import os
import sys

directory_name = "Tryit2Photos"

def create_photos_directory():    
    try:
        os.mkdir(path = os.path.join(os.getcwd(), directory_name), mode = 777 )
    except FileExistsError:
        pass

def nn_interpolate_verification():
    im = load_image("data/dogsmall.jpg")
    a = nn_resize(im, im.w*4, im.h*4)
    save_image(a, directory_name + '/' + "dog4x-nn")

def bilinear_interpolate_verification():
    im = load_image("data/dogsmall.jpg")
    a = bilinear_resize(im, im.w*4, im.h*4)
    save_image(a, directory_name + '/' + 'bilinear_dog_4x' )


if __name__ == "__main__":
    create_photos_directory()
    nn_interpolate_verification()
    bilinear_interpolate_verification()