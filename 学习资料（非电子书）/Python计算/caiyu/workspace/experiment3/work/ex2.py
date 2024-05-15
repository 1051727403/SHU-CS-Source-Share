class Time:
    _hour: int
    _minute: int
    _second: int


    def __init__(self, hour: int, minute: int, second: int):
        self._hour = hour
        self._minute = minute
        self._second = second


    def __add__(self, other):
        ts = int(self) + int(other)
        tsa = abs(ts)
        return self.__class__(ts // 3600, (tsa // 60) % 60, tsa % 60)


    def __sub__(self, other):
        ts = int(self) - int(other)
        tsa = abs(ts)
        return self.__class__(ts // 3600, (tsa // 60) % 60, tsa % 60)


    def __int__(self):
        h, m, s = self._hour, self._minute, self._second
        if m < 0:
            s *= -1
        if h < 0:
            m *= -1
            s *= -1
        return h * 3600 + m * 60 + s


    def __str__(self):
        return '{:0>2d}:{:0>2d}:{:0>2d}'.format(self._hour, self._minute, self._second)


    def __lt__(self, other):
        return int(self) < int(other)


    def __gt__(self, other):
        return other < self


    def __le__(self, other):
        return not (self > other)


    def __ge__(self, other):
        return not (self < other)


    def __eq__(self, other):
        return int(self) == int(other)


    def time2int(self):
        return int(self)


    def printtime(self):
        print(self)


    def isafter(self, other):
        return self > other


    def increment(self, n):
        seconds = int(self) + n
        seconds_a = abs(seconds)
        self._hour = seconds // 3600
        self._minute = (seconds_a // 60) % 60
        self._second = seconds_a // 3600


    def isvalid(self):
        return 0 <= self._hour < 24 and 0 <= self._minute < 60 and 0 <= self._second < 60


def main():
    a = Time(12, 53, 18)
    b = Time(-3, 30, 2)
    a.printtime()
    b.printtime()
    (a + b).printtime()


if __name__ == '__main__':
    main()
