from PIL import Image

im = Image.open('cliff.jpg')
pix = im.load()


width, height = im.size
print(f"{width} {height}")

for i in range(width):
    for j in range(height):
        print(pix[j, i][0], pix[j, i][1], pix[j, i][2], sep=' ')


print('')

