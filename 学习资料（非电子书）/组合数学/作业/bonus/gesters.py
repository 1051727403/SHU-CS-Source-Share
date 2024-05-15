import math
vis = [[False, False, False],
       [False, False, False],
       [False, False, False]]

ans = [0, ] * 9


def dfs(n: int, count: list, x: int, y: int):
    global vis
    global ans
    if n == 1:
        count[0] += 1
        for i in range(0, 3):
            for j in range(0, 3):
                if vis[i][j] is True:
                    ans[i * 3 + j] += 1
        return
    for i in range(0, 3):
        for j in range(0, 3):
            # 如果这个点没有访问过
            if vis[i][j] is False:
                distance = math.sqrt(math.pow((i - x), 2) + math.pow((j - y), 2))
                # 此点相邻(横、斜1格) 或 日字格
                if distance <= math.sqrt(2) or abs(distance - math.sqrt(5)) <= 1e-10:
                    vis[i][j] = True
                    dfs(n - 1, count, i, j)
                    # 恢复现场，下面同
                    vis[i][j] = False
                # 此点连成一条直线(中间隔一点)
                elif vis[(i + x) // 2][(j + y) // 2] is True and (
                        abs(distance - 2) <= 1e-10 or abs(distance - 2 * math.sqrt(2)) <= 1e-10):
                    vis[i][j] = True
                    dfs(n - 1, count, i, j)
                    vis[i][j] = False


if __name__ == '__main__':
    sum_ = 0
    print("-" * 30)
    print("手势点个数情况如下所示")
    print("-" * 30)
    for n in range(4, 10):
        count = [0]
        for x in range(0, 3):
            for y in range(0, 3):
                vis = [[False, False, False],
                       [False, False, False],
                       [False, False, False]]
                vis[x][y] = True
                dfs(n, count, x, y)
        sum_ += count[0]

        print("当手势点个数为%d时有%d种情况" % (n, count[0]))

    print("总计有%d种情况" % sum_)
    print()
    print("-" * 30)
    print("手势点中包含每个点的情况如下所示")
    print("-" * 30)
    for i in range(0, 9):
        print("第%d个点共出现了%d次" % (i + 1, ans[i]))
    print("-" * 30)
