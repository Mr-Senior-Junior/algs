from sys import stdin

# Количество уникальных объектов (чисел)
N = 100

# Инициализация массива с начальными значениями от 0 до N-1
array = list(range(N))

# Основной цикл ввода данных (пар чисел) до достижения EOF (конца файла)
for line in stdin:
	p, q = [int(x) for x in line.split()]

	# Запоминаем значение p-й ячейки
	t = array[p]

	# Проверка, связаны ли объекты (опреация ПОИСК)
	if t == array[q]:
		continue

	# Опреация ОБЪЕДИНЕНИЕ
	for i in range(N):
		if array[i] == t:
			array[i] = array[q]

	# Вывод пары чисел
	print(" {} {}".format(p, q))
