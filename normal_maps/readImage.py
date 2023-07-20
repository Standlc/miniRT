from PIL import Image

im = Image.open('wood.jpg')
pix = im.load()

# print(im.size)

for i in range(im.size[0]):
    for j in range(im.size[1]):
        print(pix[i,j][0], pix[i,j][1], pix[i,j][2], end='')
        if j < im.size[1] - 1:
            print(',', end='')
        else:
            print('')

