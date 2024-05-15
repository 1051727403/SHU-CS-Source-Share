import random


def create_list() -> list:
    """

    :rtype: list
    """
    ls = [random.randint(0, 365) for i in range(100)]
    return ls


def remove_redundant_list(ls: list) -> list:
    """

    :rtype: list
    """
    processed_ls = []
    for item in ls:
        if item not in processed_ls:
            processed_ls.append(item)
    return processed_ls


def create_dict() -> dict:
    """

    :rtype: dict
    """
    d = {i: random.randint(0, 365) for i in range(100)}
    return d


def remove_redundant_dict(raw_dic):
    # 设置已出现过值的set集合
    appeared_set = set()
    processed_dic = dict()
    # 遍历字典的键值对
    for k, v in raw_dic.items():
        if v not in appeared_set:
            appeared_set.add(v)
        else:
            processed_dic[k] = v
    return processed_dic


def main():
    # 处理列表类型
    raw_ls = create_list()
    processed_ls = remove_redundant_list(raw_ls)
    # 便于显示，加入排序
    print("列表去重前:", sorted(raw_ls))
    print("列表去重后:", sorted(processed_ls))
    print("*" * 50)

    # 处理字典类型
    raw_dic = create_dict()
    processed_dic = remove_redundant_dict(raw_dic)

    print("字典去重前:", raw_dic)
    print("字典去重后:", processed_dic)
    pass


if __name__ == '__main__':
    main()
