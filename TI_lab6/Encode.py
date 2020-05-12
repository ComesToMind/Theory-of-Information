import numpy as np
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from PIL import Image
import copy
# здесь лежат индексы для буквенно-цифрового кодирвоания
indexes = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
           'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '$', '%', '*', '+', '-', '.', '/', ':']

# В таблице 2 указано максимальное количество полезной информации вместе со служебной (в битах),
# которое можно закодировать в QR коде этой версии.
# Из этой таблицы определется версия нашего QR кода.

# здесь лежат версии с 1-9 с уровнем сжатия М(15%)
VERSIES = [128, 224, 352, 512, 688, 864, 992, 1232, 1456]
AMOUNT_OF_BLOCKS = [1, 1, 1, 2, 2, 4, 4, 4, 5]
# здесь храним посчитанный номер версии
V: int = -1
# здесь количество байтов коррекции для версии
AMOUNT_OF_CORRECTION_BYTES = [10, 16, 26, 18, 24, 16, 18, 22, 22]
# Генерирующие многочлены
GENERATING_POLYNOMS = [[251, 67, 46, 61, 118, 70, 64, 94, 32, 45],
                       [120, 104, 107, 109, 102, 161, 76, 3, 91, 191, 147, 169, 182, 194, 225, 120],
                       [173, 125, 158, 2, 103, 182, 118, 17, 145, 201, 111, 28, 165, 53, 161, 21, 245, 142, 13, 102,48 ,227 , 153, 145, 218, 70],
                       [215, 234, 158, 94, 184, 97, 118, 170, 79, 187, 152, 148, 252, 179, 5, 98, 96, 153],
                       [229, 121, 135, 48, 211, 117, 251, 126, 159, 180, 169, 152, 192, 226, 228, 218, 111, 0, 117, 232, 87, 96, 227, 21],
                       [120, 104, 107, 109, 102, 161, 76, 3, 91, 191, 147, 169, 182, 194, 225, 120],
                       [215, 234, 158, 94, 184, 97, 118, 170, 79, 187, 152, 148, 252, 179, 5, 98, 96, 153],
                       [210, 171, 247, 242, 93, 230, 14, 109, 221, 53, 200, 74, 8, 172, 98, 80, 219, 134, 160, 105, 165, 231],
                       [210, 171, 247, 242, 93, 230, 14, 109, 221, 53, 200, 74, 8, 172, 98, 80, 219, 134, 160, 105, 165, 231]]

# Поле Галуа
GALOIS_FIELD = [ 1, 2, 4, 8, 16, 32, 64, 128, 29, 58, 116, 232, 205, 135, 19, 38,
                            76, 152, 45, 90, 180, 117, 234, 201, 143, 3, 6, 12, 24, 48, 96, 192,
                            157, 39, 78, 156, 37, 74, 148, 53, 106, 212, 181, 119, 238, 193, 159, 35,
                            70, 140, 5, 10, 20, 40, 80, 160, 93, 186, 105, 210, 185, 111, 222, 161,
                            95, 190, 97, 194, 153, 47, 94, 188, 101, 202, 137, 15, 30, 60, 120, 240,
                            253, 231, 211, 187, 107, 214, 177, 127, 254, 225, 223, 163, 91, 182, 113, 226,
                            217, 175, 67, 134, 17, 34, 68, 136, 13, 26, 52, 104, 208, 189, 103, 206,
                            129, 31, 62, 124, 248, 237, 199, 147, 59, 118, 236, 197, 151, 51, 102, 204,
                            133, 23, 46, 92, 184, 109, 218, 169, 79, 158, 33, 66, 132, 21, 42, 84,
                            168, 77, 154, 41, 82, 164, 85, 170, 73, 146, 57, 114, 228, 213, 183, 115,
                            230, 209, 191, 99, 198, 145, 63, 126, 252, 229, 215, 179, 123, 246, 241, 255,
                            227, 219, 171, 75, 150, 49, 98, 196, 149, 55, 110, 220, 165, 87, 174, 65,
                            130, 25, 50, 100, 200, 141, 7, 14, 28, 56, 112, 224, 221, 167, 83, 166,
                            81, 162, 89, 178, 121, 242, 249, 239, 195, 155, 43, 86, 172, 69, 138, 9,
                            18, 36, 72, 144, 61, 122, 244, 245, 247, 243, 251, 235, 203, 139, 11, 22,
                            44, 88, 176, 125, 250, 233, 207, 131, 27, 54, 108, 216, 173, 71, 142, 1]

# Обратное поле Галуа
REV_GALOIS_FIELD = [ -1, 0, 1, 25, 2, 50, 26, 198, 3, 223, 51, 238, 27, 104, 199, 75,
                     4, 100, 224, 14, 52, 141, 239, 129, 28, 193, 105, 248, 200, 8, 76, 113,
                     5, 138, 101, 47, 225, 36, 15, 33, 53, 147, 142, 218, 240, 18, 130, 69,
                     29, 181, 194, 125, 106, 39, 249, 185, 201, 154, 9, 120, 77, 228, 114, 166,
                     6, 191, 139, 98, 102, 221, 48, 253, 226, 152, 37, 179, 16, 145, 34, 136,
                     54, 208, 148, 206, 143, 150, 219, 189, 241, 210, 19, 92, 131, 56, 70, 64,
                     30, 66, 182, 163, 195, 72, 126, 110, 107, 58, 40, 84, 250, 133, 186, 61,
                     202, 94, 155, 159, 10, 21, 121, 43, 78, 212, 229, 172, 115, 243, 167, 87,
                     7, 112, 192, 247, 140, 128, 99, 13, 103, 74, 222, 237, 49, 197, 254, 24,
                     227, 165, 153, 119, 38, 184, 180, 124, 17, 68, 146, 217, 35, 32, 137, 46,
                     55, 63, 209, 91, 149, 188, 207, 205, 144, 135, 151, 178, 220, 252, 190, 97,
                     242, 86, 211, 171, 20, 42, 93, 158, 132, 60, 57, 83, 71, 109, 65, 162,
                     31, 45, 67, 216, 183, 123, 164, 118, 196, 23, 73, 236, 127, 12, 111, 246,
                     108, 161, 59, 82, 41, 157, 85, 170, 251, 96, 134, 177, 187, 204, 62, 90,
                     203, 89, 95, 176, 156, 169, 160, 81, 11, 245, 22, 235, 122, 117, 44, 215,
                     79, 174, 213, 233, 230, 231, 173, 232, 116, 214, 244, 234, 168, 80, 88, 175 ]


SEARCH_ELEMENT = [[0,0,0,0,0,0,0],
                           [0,1,1,1,1,1,0],
                           [0,1,0,0,0,1,0],
                           [0,1,0,0,0,1,0],
                           [0,1,0,0,0,1,0],
                           [0,1,1,1,1,1,0],
                           [0,0,0,0,0,0,0]]
ALIGNMENT_PATTERN_LOC = [[18],[22],[26],[30],[34],[6,22,38],[6,24,42],[6,26,46]]

ONE_ALIGNMENT = [[0,0,0,0,0],
                 [0,1,1,1,0],
                 [0,1,0,1,0],
                 [0,1,1,1,0],
                 [0,0,0,0,0]]

def decimals_to_binaries():
    # Этот тип кодирования требует 10 бит на 3 символа.
    # Вся последовательность символов разбивается на группы по 3 цифры,
    # и каждая группа (трёхзначное число) переводится в 10-битное двоичное число и добавляется к последовательности бит.
    # Если общее количество символов не кратно 3,
    # то если в конце остаётся 2 символа, полученное двузначное число кодируется 7 битами, а если 1 символ, то 4 битами.

    decimals: str = input("Введите последовательность цифр: ")
    decimals.upper()
    i = 0
    split_by_three_to_bin: str = ""
    for i in range(i, len(decimals), 3):
        split_by_three = decimals[i:i+3:1]
        if len(split_by_three) == 3:
            temp = bin(int(split_by_three))[2:]  # обрезаем у bin() 0b в начале
            split_by_three_to_bin += (temp.rjust(10, '0')) # дополняет до 10 бит и кидаем в
            continue
        if len(split_by_three) == 2:
            temp = bin(int(split_by_three))[2:]
            split_by_three_to_bin += (temp.rjust(7, '0'))  # дополняет до 7 бит и кидаем в
            continue
        if len(split_by_three) == 1:
            temp = bin(int(split_by_three))[2:]  # обрезаем у bin() 0b в начале
            split_by_three_to_bin +=(temp.rjust(4, '0'))  # дополняет до 4 бит и кидаем в
            continue
    return add_type_and_length(split_by_three_to_bin, '0001') # добавили служебную информацию


def decimalsANDsymbols_to_binaries():
    # В этом случае на 2 символа требуется 11 бит информации.
    # Входной поток символов разделяется на группы по 2,
    # в группе каждый символ кодируется согласно таблице внизу,
    # значение первого символа в группе умножается на 45 и прибавляется к значение второго символа.
    # Полученное число переводится в 11-битное двоичное число и добавляется к последовательности бит.
    # Если в последней группе 1 символ,
    # то его значение сразу кодируется 6-битным числом и добавляется к последовательности бит
    inputs: str = input("Введите последовательность букв или цифр: ")
    inputs = inputs.upper()
    i = 0
    split_by_two_to_bin: str = ""
    for i in range(i, len(inputs), 2):
        split_by_two = inputs[i:i+2:1]
        if len(split_by_two) == 2:
            temp_dec = 45*indexes.index(split_by_two[0]) + indexes.index(split_by_two[1])
            temp = bin(temp_dec)[2:]
            split_by_two_to_bin += temp.rjust(11, '0')  # дополняет до 11 бит и кидаем в
            continue
        if len(split_by_two) == 1:
            temp = bin(indexes.index(split_by_two))[2:]  # обрезаем у bin() 0b в начале
            split_by_two_to_bin += temp.rjust(6, '0')  # дополняет до 4 бит и кидаем в
            continue
    return add_type_and_length(split_by_two_to_bin, '0010') # добавили служебную информацию


def add_type_and_length(initial_binaries : str, t : str):

    # длина количества поля данных (initial_binaries)
    # цифровое 10 бит
    # буквенно-циф 9 бит

    # в будущем проверить на слишком большое кол-во байт
    dec = len(initial_binaries)
    if t == '0010':
        dec_str = (bin(dec)[2:0]).rjust(9,'0')
        return "0010" + dec_str + initial_binaries
    if t == '0001':
        dec_str = (bin(dec)[2:0]).rjust(10, '0')
        return "0001" + dec_str + initial_binaries


def fill_to_certain_length(for_fill: str):
    # заполнение до длины равной ближайщей версии
    addit_byte1 = "11101100"
    addit_byte2 = "00010001"
    # делаем последовательность кратной 8
    while len(for_fill) % 8 != 0:
        for_fill += '0'
    global V
    V = -1
    # ищим подходящую версию по длине бит
    i = 0
    deb = len(for_fill)
    for i in range(0, 9):
        if (VERSIES[i] - len(for_fill)) >= 0:
            V = i
            break
    i = 0
    # ПОТОМ ПРОВЕРИТЬ НА -1
    while len(for_fill) != VERSIES[V]:
        if i % 2 == 0:
            for_fill += addit_byte1;
            i +=1
            continue
        for_fill += addit_byte2
        i += 1
    return for_fill


def forming_blocks(whole_data: str):
    # Разделение информации на блоки
    # сначала делим все на блоки по 8 байт
    number_of_bytes = len(whole_data)//8
    # сейчас разедлим все на байты
    bytes_as_decimals = []
    for k in range(0, len(whole_data), 8):
        bytes_as_decimals.append(int(whole_data[k:k+8:1], 2))

    remainder = number_of_bytes % AMOUNT_OF_BLOCKS[V]  # делим на количество блоков в версии, остаток есть блоки с доп байтом
    bytes_in_one_block = number_of_bytes // AMOUNT_OF_BLOCKS[V]
    blocks = []
    # remainder есть кол-во блоков с +1 байтом
    usual_block_count = AMOUNT_OF_BLOCKS[V] - remainder
    i = 0
    place = 0
    while i < AMOUNT_OF_BLOCKS[V]:
        if i < usual_block_count:
            right_border = place + bytes_in_one_block
            temp  = bytes_as_decimals[place: right_border: 1]
            blocks.append(temp)
            place = right_border
            i += 1
            continue
        else:
            right_border = place + bytes_in_one_block +1
            temp = bytes_as_decimals[place: right_border: 1]
            blocks.append(temp)
            place = right_border
            i += 1
    return blocks


def create_correcting_bytes(blocks_):
    # создаем в зависимости от уровня корекции кол-во байт
    # заполняем их данными из блока а затем нулями
    # чекаем,что больше
    # arr = np.zeros(AMOUNT_OF_CORRECTION_BYTES[V], dtype=int)
    for i in range(0, len(blocks_)):
        len_blocks = len(blocks_[i])
        while len(blocks_[i]) < AMOUNT_OF_CORRECTION_BYTES[V]:
            blocks_[i].append(0)
        for j in range(0, len_blocks):
            temp_A = blocks_[i][0]
            blocks_[i].pop(0)
            blocks_[i].append(0)
            if temp_A == 0:
                continue
            temp_B = REV_GALOIS_FIELD[temp_A]
            place = 0
            for k in GENERATING_POLYNOMS[V]:
                temp_D = (temp_B + k) % 255
                temp_D = GALOIS_FIELD[temp_D]
                blocks_[i][place] ^= temp_D
                place += 1
    return blocks_

def merge_blocks():
    return

# for_fill: str = decimalsANDsymbols_to_binaries()
# ready_to_form_blocks: str = fill_to_certain_length(for_fill)
#
# blocks = forming_blocks(ready_to_form_blocks)
# blocks_of_correct = create_correcting_bytes(blocks)

def draw_search_pattern(pixels):
    # 3 поисковых узора
    for i in range(len(SEARCH_ELEMENT)):
        for j in range(len(SEARCH_ELEMENT)):
            pixels[i, j] = SEARCH_ELEMENT[i][j]  # левый верхний
            pixels[i, img.size[0] - 7 + j] = SEARCH_ELEMENT[i][j]  # левый нижний
            pixels[img.size[0] - 7 + i, j] = SEARCH_ELEMENT[i][j]  # правый верхний
    return pixels


def draw_synchr_strip(pixels):
    # здесь полосы синхронизации (черно-бел черед)
    i = 9
    for i in range(i, img.size[0]-8):
        if i % 2 == 0:
            pixels[6, i] = 1
            pixels[i,6] = 1
            continue
        pixels[6,i] = 0
        pixels[i,6] = 0
    return pixels


def draw_alignment_patterns(pixels):

    # Есть одно важное условие: выравнивающие узоры не должны наслаиваться на поисковые узоры.
    # То есть, когда версия больше 6, в точках (первая, первая),
    # (первая, последняя) и (последняя, первая) выравнивающих узоров не должно быть
    global V
    if V == 0:
        return
    coordinates  = []
    if V < 6:
        temp = []
        temp.append(ALIGNMENT_PATTERN_LOC[V-1][0])
        temp.append(ALIGNMENT_PATTERN_LOC[V-1][0])
        coordinates.append(temp)
        # вызвать функцию рисования
        return draw_one_alignment(pixels,coordinates)


    patterns = ALIGNMENT_PATTERN_LOC[V-1]
    temp = []
    temp2 = []
    temp3 = []
    temp.append(patterns[0])
    temp.append(patterns[1])
    coordinates.append(temp) # первый второй
    coordinates.append(temp[::-1]) # второй первый
    temp2.append(patterns[1])
    temp2.append(patterns[1])
    coordinates.append(temp2) # второй второй
    temp4 = []
    temp4.append(patterns[1])
    temp4.append(patterns[2])# вторйо третий
    coordinates.append(temp4)
    coordinates.append(temp4[::-1]) # третий второй
    temp3.append(patterns[2])
    temp3.append(patterns[2])
    coordinates.append(temp3)
    return draw_one_alignment(pixels,coordinates)

def draw_one_alignment(pixels, coordinates):
    # рисуем каждый выравнивающий узор
    for k in coordinates:
        i = k[0]-2
        j = k[1]-2
        m = 0
        for i in range(i, k[0]+3):
            n = 0
            for j in range(j,k[1]+3):
                pixels[i,j] = ONE_ALIGNMENT[m][n]
                n+=1
            m +=1
            j = k[1] - 2
    return pixels

#### ЗДЕСЬ ВЕСЬ НАЧАЛОСЬ (и порешалось)

# for_fill: str = decimalsANDsymbols_to_binaries()
# ready_to_form_blocks: str = fill_to_certain_length(for_fill)
#
# blocks = forming_blocks(ready_to_form_blocks)
# print(blocks)
#
# blocks_of_correct = copy.deepcopy(blocks)
# create_correcting_bytes(blocks_of_correct)
# print(blocks_of_correct)
# print(blocks)

V = 5
if V == 0:
    img = Image.new('1', (21, 21), color='white')
else:
    # максимальное число в выравнивающем узоре есть размер, к которому + 7 надо
    max = ALIGNMENT_PATTERN_LOC[V-1][len(ALIGNMENT_PATTERN_LOC[V-1])-1] + 7
    img = Image.new('1', (max, max), color='white')

pixels = img.load()

draw_search_pattern(pixels)
draw_synchr_strip(pixels)
draw_alignment_patterns(pixels)




plt.imshow(np.asarray(img), cmap='gray')
plt.show()



#img.show()

# print(decimalsANDsymbols_to_binaries())
# print(decimals_to_binaries())
# print("0110000101101111000110011000")

