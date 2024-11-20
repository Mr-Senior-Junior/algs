from sys import stdin

# Количество уникальных объектов (чисел)
N = 100

# Инициализация массивов
array = list(range(N))
sizes = [1] * N

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


	# Опреация ОБЪЕДИНЕНИЕ (корень МЕНЬШЕГО дерева ссылаем на корень БОЛЬШЕГО дерева, затем увеличиваем размер БОЛЬШЕГО дерева)
	if sizes[i] < sizes[j]:
		array[i] = j
		sizes[j] += sizes[i]
	else:
		array[j] = i
		sizes[i] += sizes[j]


	# Вывод пары чисел
	print(" {} {}".format(p, q))
