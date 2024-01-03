#include <stdio.h>
#include <string.h>
#include <ctype.h>

// 函数用于去除句子中多余的空格
void formatSentence(char* sentence) {
	int i, j;
	int len = strlen(sentence);
	
	// 去除开头的空格
	while (isspace(sentence[0])) {
		for (i = 0; i < len; ++i) {
			sentence[i] = sentence[i + 1];
		}
		len--;
	}
	
	// 去除单词之间多余的空格
	for (i = 0; i < len - 1; ++i) {
		if (isspace(sentence[i]) && isspace(sentence[i + 1])) {
			for (j = i; j < len; ++j) {
				sentence[j] = sentence[j + 1];
			}
			len--;
			i--;  // 重新检查当前位置
		}
	}
	
	// 去除末尾的空格
	while (len > 0 && isspace(sentence[len - 1])) {
		sentence[len - 1] = '\0';
		len--;
	}
}

int main() {
	char inputSentence[100];
	
	// 从键盘输入句子
	printf("请输入一个句子: ");
	fgets(inputSentence, sizeof(inputSentence), stdin);
	
	// 去除多余空格并打印结果
	formatSentence(inputSentence);
	printf("格式化后的句子: %s\n", inputSentence);
	
	return 0;
}

