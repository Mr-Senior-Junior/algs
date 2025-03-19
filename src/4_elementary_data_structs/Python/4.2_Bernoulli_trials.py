import numpy as np
import math


def heads():
	return np.random.randint(0, 10000) < 5000


# M экспериментов по N подбрасываний
N = 40
M = 6000


results = [0 for _ in range(N + 1)]
cnt = 0

# Основная часть программы - подсчет успешных бросков
for _1 in range(M):
	cnt = 0
	for _2 in range(N + 1):
		if heads():
			cnt += 1
	results[cnt] += 1


for result in results:
	if result == 0:
		print('.')
		continue

	resultStr = ''.join("*" for _ in range(math.ceil(result / 10.)))
	print(resultStr)
