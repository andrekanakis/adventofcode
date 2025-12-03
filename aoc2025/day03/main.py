from itertools import combinations

def part1():
    data = open("input.txt")
    res: int = 0
    for line in data:
        left = 0
        right = 0
        numbers = list(line[:-1])
        left = numbers[0]
        right = numbers[1]
        left_idx = 0
        for i in range(0, len(numbers)-1):
            if numbers[i] > left:
                left = numbers[i]
                left_idx = i
        right = numbers[left_idx + 1]
        for i in range(left_idx + 2, len(numbers)):
            right = max(right, numbers[i])
        res += int(left+right)
    print(res)


def part2():
    data = open("input.txt")
    res = 0
    for line in data:
        numbers = list(line[:-1])
        combs = combinations(numbers, 12)
        max_value = max(combs)
        res += int("".join(max_value))
    print(res)


def part2_2():
    data = open("input.txt")
    res = 0
    for line in data:
        numbers = list(line[:-1])
        values = []
        start_idx = 0

        for _ in range(12):
            end_idx = len(numbers) - (12 - len(values)) + 1
            max_val = "-1"
            max_idx = start_idx

            for j in range(start_idx, end_idx):
                if numbers[j] > max_val:
                    max_val = numbers[j]
                    max_idx = j
                if max_val == "9":
                    break
            values.append(max_val)
            start_idx = max_idx + 1

        res += int("".join(values))

    print(res)




if __name__ == "__main__":
    # part1()
    # part2()
    part2_2()
