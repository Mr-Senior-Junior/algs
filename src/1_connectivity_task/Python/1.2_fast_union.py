from sys import stdin

# Количество уникальных объектов (чисел)
N = 100

# Инициализация массива с начальными значениями от 0 до N-1
array = list(range(N))

# Основной цикл ввода данных (пар чисел) до достижения EOF (конца файла)
for line in stdin:
	p, q = [int(x) for x in line.split()]

	# Проверка, связаны ли объекты (опреация ПОИСК)
	i = p
	while i != array[i]:
		i = array[i]

	j = q
	while j != array[j]:
		j = array[j]

	if i == j:
		continue

	# Опреация ОБЪЕДИНЕНИЕ
	array[i] = j

	# Вывод пары чисел
	print(" {} {}".format(p, q))
