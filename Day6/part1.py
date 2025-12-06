import sys
matrix = [line.split() for line in sys.stdin]

rows = len(matrix) - 1
grand_total = 0
for (column, operation) in enumerate(matrix[-1]):
    if operation == '+':
        for i in range(rows):
            grand_total += int(matrix[i][column])
    else:
        col_total = 1
        for i in range(rows):
            col_total *= int(matrix[i][column])
        grand_total += col_total

print(grand_total)