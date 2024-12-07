def binary_search(arr, target):
    left, right = 0, len(arr)
    while left != right:
        mid = left + (right - left) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid
    return -1



arr = [1, 7, 8, 13, 36, 44, 72, 89, 103, 231, 243, 287]
target = 13
print(binary_search(arr, target))
