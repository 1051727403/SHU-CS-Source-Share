import glob
import os
import re

# 定义关键字列表
keywords = [
    'const',
    'var',
    'procedure',
    'call',
    'begin',
    'end',
    'if',
    'then',
    'while',
    'do',
    'read',
    'write',
    'odd',
    'for',
    'to'
]


def parse_identifiers(source_file, output_file):
    # 读取源代码文件内容
    with open(source_file, 'r') as f:
        source_code = f.read()

    # 将源代码中的非字母、数字和下划线都替换为空格
    source_code = re.sub("[^a-zA-Z0-9_]", ' ', source_code)

    # 将源代码中的所有字母都转换为小写
    source_code = source_code.lower()

    # 分割源代码为单词列表
    words = source_code.split()

    # 过滤出标识符
    identifiers = []
    for word in words:
        if re.match(r"^[a-z][a-z0-9_]*$", word) and word not in keywords:
            identifiers.append(word)

    # 统计标识符出现次数
    count = {}
    for identifier in identifiers:
        if identifier in count:
            count[identifier] += 1
        else:
            count[identifier] = 1

    # 按标识符出现顺序输出识别结果
    with open(output_file, 'w') as f:
        for identifier in identifiers:
            if identifier in count and count[identifier] > 0:
                f.write('(%s, %d)\n' % (identifier, count[identifier]))
                count[identifier] = 0

    print('识别完成，输出结果已保存到文件 %s' % output_file)


# 测试代码
if __name__ == '__main__':
    # 遍历当前目录下以 input 开头的 txt 文件
    for filepath in glob.glob('input*.txt'):
        # 将识别结果输出到 output.txt 文件中
        output_path = 'output' + os.path.splitext(filepath)[0][-1] + '.txt'
        parse_identifiers(filepath, output_path)
