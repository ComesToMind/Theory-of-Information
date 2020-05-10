# здесь лежат индексы для буквенно-цифрового кодирвоания
indexes = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
           'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '$', '%', '*', '+', '-', '.', '/', ':']

# В таблице 2 указано максимальное количество полезной информации вместе со служебной (в битах),
# которое можно закодировать в QR коде этой версии.
# Из этой таблицы определется версия нашего QR кода.

# здесь лежат версии с 1-9 с уровнем сжатия М(15%)
VERSIES = [128, 224, 352, 512, 688, 864, 992, 1232, 1456]
AMOUNT_OF_BLOCKS = [1, 1, 1, 2, 2, 4, 4, 4, 5]
V: int = -1
# здесь храним посчитанный номер версии


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
    V = -1
    # ищим подходящую версию по длине бит
    i = 0
    for i in range(0,9):
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
        i +=1
    return for_fill


def forming_blocks(whole_data: str):
    # Разделение информации на блоки
    # сначала делим все на блоки по 8 байт
    number_of_bytes = len(whole_data)//8
    remainder = number_of_bytes % AMOUNT_OF_BLOCKS[V]  # делим на количество блоков в версии, остаток есть блоки с доп байтом
    bytes_in_one_block = number_of_bytes // AMOUNT_OF_BLOCKS[V]
    blocks = []
    



    return

for_fill: str = decimalsANDsymbols_to_binaries()
ready_data: str = fill_to_certain_length(for_fill)


print(ready_data)
# print(decimalsANDsymbols_to_binaries())

# print(decimals_to_binaries())
# print("0110000101101111000110011000")

