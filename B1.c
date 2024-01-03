#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b) {
	return a < b ? a : b;
}

char* preprocessString(char* s) {
	int len = strlen(s);
	char* new_str = (char*)malloc(2 * len + 3);
	new_str[0] = '#';
	int j = 1;
	for (int i = 0; i < len; i++) {
		new_str[j++] = s[i];
		new_str[j++] = '#';
	}
	new_str[j] = '\0';
	return new_str;
}

char* longestPalindromeManacher(char* s) {
	int len = strlen(s);
	if (len <= 1) {
		return s;
	}
	
	char* new_str = preprocessString(s);
	len = 2 * len + 2;
	
	int* P = (int*)malloc(len * sizeof(int));
	int center = 0, right_boundary = 0;
	
	for (int i = 0; i < len; i++) {
		int mirror = 2 * center - i;
		if (i < right_boundary) {
			P[i] = min(right_boundary - i, P[mirror]);
		} else {
			P[i] = 0;
		}
		
		while (new_str[i + 1 + P[i]] == new_str[i - 1 - P[i]]) {
			P[i]++;
		}
		
		if (i + P[i] > right_boundary) {
			center = i;
			right_boundary = i + P[i];
		}
	}
	
	int max_len = 0, center_index = 0;
	for (int i = 0; i < len; i++) {
		if (P[i] > max_len) {
			max_len = P[i];
			center_index = i;
		}
	}
	
	free(new_str);
	free(P);
	
	int start = (center_index - max_len) / 2;
	char* result = (char*)malloc(max_len + 1);
	strncpy(result, s + start, max_len);
	result[max_len] = '\0';
	
	return result;
}

char* longestPalindromeBruteforce(char* s) {
	int len = strlen(s);
	if (len <= 1) {
		return s;
	}
	
	int max_len = 1, start = 0;
	
	for (int i = 0; i < len; i++) {
		for (int j = i + 1; j < len; j++) {
			int isPalindromic = 1;
			for (int k = i; k <= (i + j) / 2; k++) {
				if (s[k] != s[j - k + i]) {
					isPalindromic = 0;
					break;
				}
			}
			if (isPalindromic && j - i + 1 > max_len) {
				start = i;
				max_len = j - i + 1;
			}
		}
	}
	
	char* result = (char*)malloc(max_len + 1);
	strncpy(result, s + start, max_len);
	result[max_len] = '\0';
	
	return result;
}

int main() {
	char s[] = "ABCDDCBA";
	
	char* resultManacher = longestPalindromeManacher(s);
	printf("Manacher算法 - 最长回文子序列：%s\n", resultManacher);
	free(resultManacher);
	
	char* resultBruteforce = longestPalindromeBruteforce(s);
	printf("暴力匹配算法 - 最长回文子序列：%s\n", resultBruteforce);
	free(resultBruteforce);
	
	return 0;
}

