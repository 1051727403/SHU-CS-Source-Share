def Ackermann(m: int, n: int) -> int:
    """

    :rtype: int
    """
    if m == 0:
        return n + 1
    if n == 0:
        return Ackermann(m - 1, 1)
    return Ackermann(m - 1, Ackermann(m, n - 1))


def main():
    res = Ackermann(3, 4)
    print(res)


if __name__ == '__main__':
    main()
