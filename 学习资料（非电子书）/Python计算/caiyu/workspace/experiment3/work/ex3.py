import random
import time

from nltk.tokenize import sent_tokenize


def process_word(word: str) -> str:
    """
    去除连在单词前的奇怪字符,例如将 ******The  --> The
    :param word: 待处理的单词
    :return: 处理后的单词
    """
    return word.strip(r'"#$%&' r"'()*+-/:;<=>@[\]^_`{|}~")  # 去除标点符号


class Markov:
    def __is_end_word(self, word: str) -> bool:
        """
        判断词单词是否为一句话之中最后的单词
        :param word: 待判断的单词
        :return: true or false
        """
        return word in self.end_words_set


    def __get_first_prefix(self) -> list:
        """
        返回随机的一个前缀
        :return: list
        """
        return list(random.choice(self.start_prefixes))  # 开头前缀的随机一项


    def __get_next_word(self, prefix: tuple) -> str:
        """
        接收一个前缀tuple,从chain字典之中,以prefix为键,返回马尔可夫链中限一个单词
        :param prefix: 前缀tuple
        :return: 下一个单词
        """
        seq = self.chain[prefix]  # seq为list
        return random.choice(list(seq))


    def __init__(self, fp, n: int = 1):
        self.chain = {}  # 构造的马尔可夫字典 key为prefix, value为存储过的单词
        self.start_prefixes_set = set()  # 存句子输入的第一个单词
        self.end_words_set = set()  # 一句话结束的单词
        self.n = n  # 马尔科夫分析的前缀阶数
        fp.seek(0)
        text = ' '.join(line.strip() for line in fp)  # 源文本
        for sentence in sent_tokenize(text):
            process_word_list = [process_word(word=word) for word in sentence.split()]  # 处理后新的句子

            sentence_length = len(process_word_list)  # 句子长度
            if self.n >= sentence_length:
                continue
            if process_word_list[0]:
                if not process_word_list[0][0].isupper():  # 对于未正确切分的单词进行处理
                    continue
            self.start_prefixes_set.add(tuple(process_word_list[0:n]))
            self.end_words_set.add(process_word_list[-1])

            for index in range(sentence_length - self.n):
                key = tuple(process_word_list[index:index + n])
                word = process_word_list[index + n]
                if key in self.chain:  # 如果马尔科夫链中已经有此key值
                    self.chain[key].add(word)
                else:
                    self.chain[key] = {word}

        self.start_prefixes = list(self.start_prefixes_set)  # 设置方便random


    def generate(self, n: int):
        while True:
            words = self.__get_first_prefix()  # 最终返回的语句,不断往此列表中添加单词
            pos = 0
            count = 0
            appeared_first_prefix = set()
            while True:
                try:
                    prefix = tuple(words[-self.n:])
                    word = self.__get_next_word(prefix)
                    words.append(word)
                    pos += 1
                    if pos == self.n:
                        if prefix in appeared_first_prefix:
                            words = words[:-self.n]
                            break
                        else:
                            appeared_first_prefix.add(prefix)
                    if word == '':
                        break
                    elif self.__is_end_word(word):
                        if count == n:
                            break
                        count += 1
                        pos = 0
                except KeyError:
                    break
            if not self.__is_end_word(words[-1]):
                continue
            return ' '.join(words)


def generate_sentence(m: int, n: int):
    time_1 = time.time()
    with open("emma.txt") as f:
        markov = Markov(f, n)
    time_2 = time.time()
    print("*" * 50)
    print("n = {}  马尔可夫链构建用时".format(n), time_2 - time_1, "s", sep='')
    print("*" * 50)
    text_list = []
    for i in range(m):
        text = markov.generate(n)
        text_list.append(text)
    print(*text_list, sep='\n')


def main():
    # generate_sentence(10, 1)
    generate_sentence(10, 3)
    generate_sentence(10, 5)
    generate_sentence(10, 20)


if __name__ == '__main__':
    main()
