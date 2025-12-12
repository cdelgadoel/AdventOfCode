import sys

def count_chars(piece):
    return sum(row.count('#') for row in piece)

def parse_input():
    pieces = []
    dimensions = []

    current_piece = []
    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue

        if line.endswith(':') and line[0].isdigit():
            # Start a new piece
            if current_piece:
                pieces.append(current_piece)
                current_piece = []
        elif ':' in line:
            # Parse dimensions and required counts
            dim, *counts = line.split()
            a, b = map(int, dim[:-1].split('x'))  # Remove the colon
            
            dimensions.append([(a,b),list(map(int, counts))])
        else:
            # Add row to the current piece
            current_piece.append(line)

    # Add the last piece
    if current_piece:
        pieces.append(current_piece)

    return pieces, dimensions

def main():
    # Parse the input
    pieces, dimensions = parse_input()

    # Count the number of '#' in each piece
    piece_areas = [count_chars(piece) for piece in pieces]

    # Check each dimension
    ans = 0
    for (a, b), counts in dimensions:
        total_area = sum(piece_areas[i] * counts[i] for i in range(len(piece_areas)))
        if a * b >= total_area:
            ans += 1
    print(ans)

if __name__ == "__main__":
    main()