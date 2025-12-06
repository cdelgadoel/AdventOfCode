import sys
matrix = [line for line in sys.stdin]

# obtain column-like numbers
nums = [0] * len(matrix[0])
for line in matrix[0:-1]:
    for indx, c in enumerate(line):
        if '1' <= c <= '9':
            nums[indx] = 10*nums[indx] + int(c)

# process operands
grand_total = 0
for indx, c in enumerate(matrix[-1]):
    if c == '+':
        it = indx
        while nums[indx] != 0:
            grand_total += nums[indx]
            indx += 1
    elif c == '*':
        it = indx
        operation_result = 1
        while nums[indx] != 0:
            operation_result *= nums[indx]
            indx += 1
        grand_total += operation_result
print(grand_total)