def is_valid(row, col, table):
    if table[row][col] != "@":
        return False
    max_rows = len(table)-1
    max_cols = len(table[0])-1
    dir_col = [-1, 0, 1]
    dir_row = [-1, 0, 1]
    count = 0

    for r in dir_row:
        if row + r < 0 or row + r > max_rows:
            continue
        for c in dir_col:
            if r == 0 and c == 0:
                continue
            if col + c < 0 or col + c > max_cols:
                continue
            if table[row+r][col+c] == "@":
                count += 1
            if count > 3:
                return False
    return True

def part1():
    data = open("input.txt")
    res: int = 0
    table = []
    for line in data:
        table.append(list(line[:-1]))

    for r in range(len(table)):
        for c in range(len(table[0])):
            res += 1 if is_valid(r, c, table) else 0
    print(res)

def part2():
    data = open("input.txt")
    res: int = 0
    table = []
    for line in data:
        table.append(list(line[:-1]))

    while True:
        value_pre = res
        for r in range(len(table)):
            for c in range(len(table[0])):
                if is_valid(r, c, table):
                    res += 1
                    table[r][c] = "."
        if value_pre == res:
            break
    print(res)

if __name__ == "__main__":
    # part1()
    part2()
