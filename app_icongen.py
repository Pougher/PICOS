#!usr/bin/python3
from PIL import Image
import sys

def threshold(pixel):
    result = pixel[0] + pixel[1] + pixel[2]
    return not (result >= ((255 * 3) / 2) - 1)

def main():
    if len(sys.argv) != 3:
        print("Expected filename + output name");
        sys.exit(1)
    img = Image.open(sys.argv[1])
    pixels = img.load()

    width, height = img.size
    if width != 32 and height != 19:
        print("Image dimensions are wrong - should be 32x19 image")
        sys.exit(1)

    current_byte = 0
    c_string = "static char " + sys.argv[2] + "[APP_ICON_HEIGHT][APP_ICON_WIDTH] = {\n    { "

    for j in range(height):
        for i in range(width):
            if i % 8 == 0 and i != 0:
                c_string += "0x{:02x}".format(current_byte) + ", "
                current_byte = threshold(pixels[i, j]) << (7 - (i % 8))
            elif i == 31:
                current_byte += threshold(pixels[i, j]) << (7 - (i % 8))
                c_string += "0x{:02x}".format(current_byte) + " }, \n    { "
                current_byte = 0
            else:
                current_byte += threshold(pixels[i, j]) << (7 - (i % 8))

    c_string = c_string[:len(c_string) - 6] + "};"
    print(c_string)

if __name__ == '__main__':
    main()
