

def decimals_to_binaries():
    # Этот тип кодирования требует 10 бит на 3 символа.
    # Вся последовательность символов разбивается на группы по 3 цифры,
    # и каждая группа (трёхзначное число) переводится в 10-битное двоичное число и добавляется к последовательности бит.
    # Если общее количество символов не кратно 3,
    # то если в конце остаётся 2 символа, полученное двузначное число кодируется 7 битами, а если 1 символ, то 4 битами.

    decimals: str = input("Введите последовательность цифр: ")
    i = 0
    split_by_three_to_bin: str = ""
    for i in range(i, len(decimals), 3):
        split_by_three = decimals[i:i+3:1]
        if len(split_by_three) == 3:
            temp = bin(int(split_by_three))[2:]  # обрезаем у bin() 0b в начале
            split_by_three_to_bin +=(temp.rjust(10, '0')) # дополняет до 10 бит и кидаем в
            continue
        if len(split_by_three) == 2:
            temp = bin(int(split_by_three))[2:]
            split_by_three_to_bin += (temp.rjust(7, '0'))  # дополняет до 7 бит и кидаем в
            continue
        if len(split_by_three) == 1:
            temp = bin(int(split_by_three))[2:]  # обрезаем у bin() 0b в начале
            split_by_three_to_bin +=(temp.rjust(4, '0'))  # дополняет до 4 бит и кидаем в
            continue
    return split_by_three_to_bin

def decimalsANDsymbols_to_binaries():
    # В этом случае на 2 символа требуется 11 бит информации.
    # Входной поток символов разделяется на группы по 2,
    # в группе каждый символ кодируется согласно таблице внизу,
    # значение первого символа в группе умножается на 45 и прибавляется к значение второго символа.
    # Полученное число переводится в 11-битное двоичное число и добавляется к последовательности бит.
    # Если в последней группе 1 символ,
    # то его значение сразу кодируется 6-битным числом и добавляется к последовательности бит
    inputs: str = input("Введите последовательность букв или цифр: ")
    i = 0
    split_by_two_to_bin: str = ""
    for i in range(i, len(inputs), 2):
        split_by_two = inputs[i:i+2:1]
        if len(split_by_two) == 2:
            temp = bin(int(split_by_two))[2:]
            split_by_two_to_bin += (temp.rjust(7, '0'))  # дополняет до 7 бит и кидаем в
            continue
        if len(split_by_two) == 1:
            temp = bin(int(split_by_two))[2:]  # обрезаем у bin() 0b в начале
            split_by_two_to_bin +=(temp.rjust(4, '0'))  # дополняет до 4 бит и кидаем в
            continue
    return split_by_two_to_bin


print(decimals_to_binaries())
# print("000111101101110010001001110") 12345678

