import re

inputNum = 5

lexical_dict = {
    "begin": "beginsym",
    "call": "callsym",
    "const": "constsym",
    "do": "dosym",
    "end": "endsym",
    "if": "ifsym",
    "odd": "oddsym",
    "procedure": "proceduresym",
    "read": "readsym",
    "then": "thensym",
    "var": "varsym",
    "while": "whilesym",
    "write": "writesym",
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


def lexical_analysis(fileName, outputName):
    # 读入源程序文件
    with open(fileName, encoding="utf-8") as file:
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

    with open(outputName, "w", encoding="utf-8") as file:
        for item in token:
            if lexical_dict.get(item, None) is not None:
                file.write(f"({lexical_dict[item]}, {item})" + "\n")
            elif item.isdigit():
                file.write(f"(number, {item})" + "\n")
            elif re.match(r"[a-z]+[0-9]*[a-z|0-9]*", item):
                file.write(f"(ident, {item})" + "\n")


if __name__ == '__main__':
    for i in range(inputNum):
        lexical_analysis(f"input{i + 1}.txt", f"output{i + 1}.txt")
