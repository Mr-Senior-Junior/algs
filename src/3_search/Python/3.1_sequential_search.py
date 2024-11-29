def linear_search(arr, target):
    for i in range(len(arr)):
        if arr[i] == target:
            return i
    return -1



arr = [7, 21, 66, 13, 8, 1, 36, 72]
target = 13
print(linear_search(arr, target))
