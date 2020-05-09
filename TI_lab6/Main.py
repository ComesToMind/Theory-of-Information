from pathlib import Path
# filename = input("Enter address or drop file here: ")
# print(filename)

filename = Path("C:/Users/Данила/source/repos/theory of information/TI_lab6/qr-code.png")
if not filename.exists():
    print("Oops, file doesn't exist!")

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
img = mpimg.imread('test1.png')
# пройтись по всем строкам не заходя на последний столбец (там не цвет, а какое-то другое значение)
# найти макс и мин, по среднему найти если больше то 0 бит, если меньше то 1
# все 111 - белый 000 - черный

# содежит уже битовое значение каждого пикселя
bitarray = np.zeros((np.size(img, 0), np.size(img, 1)))

# если все 3 бита 1 (белый), то  пишем 0,  иначе 1
# np.sum(array1, axis=1)

print(bitarray)
# works fine))
for i in range(0,np.size(img, 0)):
    for j in range(0, np.size(img, 1)):
        bitarray[i, j] = np.sum(img[i, j, 0:3]) # сумма каждогой R G B без херни на конце если изображение цветное
        bitarray[i, j] = 0 if bitarray[i, j] == 3. else 1



print(img)
# print(np.shape(bitarray))
print(bitarray)
plt.imshow(img)
plt.imshow(bitarray)
plt.show()
