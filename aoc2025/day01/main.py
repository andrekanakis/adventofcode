def part1():
    input = open("input.txt")

    result: int = 50
    amt_zero: int = 0


    for row in input:
        direction = row[0]
        value = int(row[1:])

        value %= 100
        if direction == "L":
            result -= value
            if result < 0:
                result = 100 - abs(result)
        elif direction == "R":
            result += value
            if result > 99:
                result -= 100
        if result == 0:
            amt_zero += 1
        print(f"{direction}: {value}, {result}")

    print(amt_zero)


def part2():
    input = open("input.txt")

    result: int = 50
    amt_zero: int = 0


    for row in input:

        direction = row[0]
        value = int(row[1:])

        cycles = value // 100
        amt_zero += cycles

        value %= 100

        if direction == "L":
            if result > 0 and (result - value) <= 0:
                amt_zero += 1
            result = (result - value) % 100
        elif direction == "R":
            if result + value >= 100:
                amt_zero += 1
            result = (result + value) % 100
        print(f"{direction}: {value}, {result}")


    print(amt_zero)


if __name__ == "__main__":
    part1()
    part2()
