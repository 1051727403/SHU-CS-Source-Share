import re

inputNum = 10
index = 0
tokens = []

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
    parse()


def parse():
    # <条件表达式> ::= <表达式>{<条件判断符号> <表达式>}
    # <表达式> ::= [+|-]<项>{<加法运算符> <项>}
    global index, tokens
    try:
        index = 0
        condition_expression()
        if index < len(tokens):
            raise ValueError(f"第{index}-{index + 1}位置的{tokens[index - 1][1]}和{tokens[index][1]}语法不正确")
        print("语法正确")
    except ValueError as error:
        print(f"语法错误: {error}")


def condition_expression():
    # <条件表达式> ::= <表达式>{<条件判断符号> <表达式>}
    global index, tokens
    expression()
    if index < len(tokens) and (tokens[index][0] in ["lss", "leq", "gtr", "geq", "eql", "neq"]):
        index += 1
        expression()
    if index < len(tokens) and (tokens[index][0] in ["lss", "leq", "gtr", "geq", "eql", "neq"]):
        raise ValueError("条件表达式只能有一个判断符号")


def expression():
    # <表达式> ::= [+|-]<项>{<加法运算符> <项>}
    global index, tokens
    # 首先判断是否有正负号
    if index < len(tokens):
        if tokens[index][0] == 'plus' or tokens[index][0] == 'minus':
            index += 1
            term()
        # 没有正负号，则直接处理项
        else:
            term()
    else:
        raise ValueError(f"第{index}位置的{tokens[index - 1][1]}语法不正确")
    # 处理可能的重复项
    while index < len(tokens) and (tokens[index][0] == 'plus' or tokens[index][0] == 'minus'):
        index += 1
        term()


def term():
    # <项> ::= <因子>{<乘法运算符> <因子>}
    global index, tokens
    factor()
    while index < len(tokens) and (tokens[index][0] == 'times' or tokens[index][0] == 'slash'):
        index += 1
        factor()


def factor():
    # <因子> ::= <标识符>|<无符号整数>| ‘(’<表达式>‘)’
    global index, tokens
    if index < len(tokens) and tokens[index][0] == 'ident':
        index += 1
    elif index < len(tokens) and tokens[index][0] == 'number':
        index += 1
    elif index < len(tokens) and tokens[index][0] == 'lparen':
        index += 1
        expression()
        if index < len(tokens) and tokens[index][0] == 'rparen':
            index += 1
        else:
            raise ValueError("括号没有闭合")
    else:
        raise ValueError(
            f"第{index}-{index + 1}位置的{tokens[index - 1][1]}和{tokens[index][1]}语法不正确")


if __name__ == '__main__':
    for j in range(inputNum):
        lexical_analysis(f"input{j + 1}.txt")
