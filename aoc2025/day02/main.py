def part1():
    numbers = open("input.txt").read()
    invalid_ids = []
    list_of_ranges = numbers.split(",")
    for single_range in list_of_ranges:
        nums = single_range.split("-")
        for i in range(int(nums[0]), int(nums[1]) + 1):
            s = str(i)
            if len(s) % 2 != 0:
                continue
            mid_point = len(s) // 2
            if s[0:mid_point] == s[mid_point:]:
                invalid_ids.append(i)

    print(sum(invalid_ids))



def part2():
    numbers = open("input.txt").read()
    invalid_ids = []
    list_of_ranges = numbers.split(",")
    for single_range in list_of_ranges:
        nums = single_range.split("-")
        for i in range(int(nums[0]), int(nums[1]) + 1):
            s = str(i)
            if s in (s+s)[1:-1]:
                invalid_ids.append(i)

    print(sum(invalid_ids))



if __name__ == "__main__":
    # part1()
    part2()
