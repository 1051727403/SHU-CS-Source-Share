'''
<表达式> ::= [+|-]<项>{<加法运算符> <项>}
<项> ::= <因子>{<乘法运算符> <因子>}
<因子> ::= <标识符>|<无符号整数>| ‘(’<表达式>‘)’
<加法运算符> ::= +|-
<乘法运算符> ::= *|/
'''

import re

inputNum = 10
index = 0
tokens = []
tI = 1
## 属性
# v = []  # 语义栈
# top = 0 # 栈顶位置

lexical_dict = {
    "+": "plus",
    "-": "minus",
    "*": "times",
    "/": "slash",
    "=": "eql",
    "#": "neq",
    "<": "lss",
    "<=": "leq",
    ">": "gtr",
    ">=": "geq",
    ":=": "becomes",
    "(": "lparen",
    ")": "rparen",
    ",": "comma",
    ";": "semicolon",
    ".": "period",
}

q = {"op": [], "arg1": [], "arg2": [], "result": []}

def quadappend(op, arg1, arg2, result):
    q["op"].append(op)
    q["arg1"].append(arg1)
    q["arg2"].append(arg2)
    q["result"].append(result)


def newT():
    global tI
    ti = "t" + str(tI)
    tI += 1
    return ti


def lexical_analysis(filename):
    print(filename, end=' ')
    # 读入源程序文件
    with open(filename, encoding="utf-8") as file:
        source_code = file.read()
    # 将所有的换行符替换为空格
    source_code = source_code.replace("\n", " ")
    # 将多个空格替换为一个空格
    source_code = re.sub(r"\s+", " ", source_code)
    # 转换为全小写字符，方便后续处理
    source_code = source_code.lower()
    # 将代码分词，保存成一个数组
    token = re.split(r"(\W)", source_code)
    # 将数组中的空格全部删除，并删除数组中前后的空格
    token = [i.strip() for i in token if i != " " and i != ""]
    # 对:=, <=, >=进行合并
    for item in range(len(token)):
        if token[item] == ":" and token[item + 1] == "=":
            token[item] = ":="
            token[item + 1] = " "
        elif token[item] == "<" and token[item + 1] == "=":
            token[item] = "<="
            token[item + 1] = " "
        elif token[item] == ">" and token[item + 1] == "=":
            token[item] = ">="
            token[item + 1] = " "
    # 将合并后产生的空格删除
    token = [item.strip() for item in token if item != " "]
    global tokens
    tokens = []
    tuple_line = ()
    for item in token:
        if lexical_dict.get(item, None) is not None:
            tuple_line = tuple([lexical_dict[item], item])
        elif item.isdigit():
            tuple_line = tuple(["number", item])
        elif re.match(r"[a-z]+[0-9]*[a-z|0-9]*", item):
            tuple_line = tuple(["ident", item])
        tokens.append(tuple_line)
    parse()  # 开始分析


def parse():
    global index, tokens, tI, q
    try:
        index = 0
        tI = 1
        q = {'op': [], 'arg1': [], 'arg2': [], 'result': []}
        expression()
        if index < len(tokens):
            raise ValueError(f"第 {index} - {index + 1} 位置的 {tokens[index - 1][1]} {tokens[index][1]} 语法不正确")
        print("语法正确，四元式序列为: ")
        for i in range(len(q['op'])):
            print('(', q['op'][i], q['arg1'][i], q['arg2'][i], q['result'][i], ')')
    except ValueError as error:
        print(f"语法错误: {error}")


def expression():
    # <表达式> ::= [+|-]<项>{<加法运算符> <项>}
    global index, tokens
    # 首先判断是否有正负号
    if tokens[index][0] == 'plus' or tokens[index][0] == 'minus':
        op = tokens[index][1]
        advance()
        temp1 = term()
        t = newT()
        quadappend(op, temp1, " ", t)
        temp1 = t
    # 没有正负号，则直接处理项
    else:
        temp1 = term()
    # 处理可能的重复项
    try:
        while index < len(tokens) and (tokens[index][0] == 'plus' or tokens[index][0] == 'minus'):
            op = tokens[index][1]
            advance()
            temp2 = term()
            result = newT()
            quadappend(op, temp1, temp2, result)
            temp1 = result
    except IndexError:
        raise ValueError(f"第 {index} 位置的加法运算符 {tokens[index - 1][1]} 后没有项")
    return temp1


def term():
    # <项> ::= <因子>{<乘法运算符> <因子>}
    global index, tokens
    temp1 = factor()
    try:
        while index < len(tokens) and (tokens[index][0] == 'times' or tokens[index][0] == 'slash'):
            op = tokens[index][1]
            advance()
            temp2 = factor()
            result = newT()
            quadappend(op, temp1, temp2, result)
            temp1 = result
    except IndexError:
        raise ValueError(f"第 {index} 位置的乘法运算符 {tokens[index - 1][1]} 后没有因子")
    return temp1


def factor():
    # <因子> ::= <标识符>|<无符号整数>| ‘(’<表达式>‘)’
    global index, tokens
    if index < len(tokens) and tokens[index][0] == 'ident':  # 标识符
        res = tokens[index][1]
        advance()
    elif index < len(tokens) and tokens[index][0] == 'number':  # 无符号数字
        res0 = tokens[index][1]
        res = newT()
        quadappend("=", res0, " ", res)
        advance()
    elif index < len(tokens) and tokens[index][0] == 'lparen':  # 左括号
        advance()
        try:
            res = expression()
            assert (tokens[index][0] == 'rparen')
            advance()
        except IndexError:
            raise ValueError("括号没有闭合")
    else:
        raise ValueError(
            f"第 {index} - {index+1} 位置的 {tokens[index][1]} 和 {tokens[index+1][1]} 不是符合因子的规则")
    return res


def advance():
    global index, tokens
    index += 1
    try:
        assert (index <= len(tokens))
    except IndexError:
        raise ValueError(f"第{index}位置的{tokens[index - 1][1]}发生越界")


if __name__ == '__main__':
    for j in range(inputNum):
        lexical_analysis(f"input{j + 1}.txt")
