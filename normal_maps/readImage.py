from PIL import Image

im = Image.open('water.jpg')
pix = im.load()

# print(im.size)

for i in range(im.size[0]):
    for j in range(im.size[1]):
        print(pix[i,j][0], pix[i,j][1], pix[i,j][2])

        # print("{0:.3f}".format(pix[i,j][0] / 255), "{0:.3f}".format(pix[i,j][1] / 255), "{0:.3f}".format(pix[i,j][2] / 255))

