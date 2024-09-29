#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 32 // 假设最大的token数量

void print_binary(uint32_t number) {
    for (int i = MAX_TOKENS - 1; i >= 0; --i) {
        printf("%c", (number & (1U << i)) ? '1' : '0');
    }
    printf("\n");
}

char *my_strtok(char *str, const char *delim, char **saveptr) {
    if (str != NULL) {
        // 跳过前面的空白字符
        while (*str && isspace((unsigned char)*str)) str++;
    } else {
        // 如果传入NULL，则从上次结束的地方开始
        str = *saveptr;
    }

    if (*str == '\0') {
        *saveptr = str;
        return NULL; // 没有更多的token了
    }
    
    // 记录token的开始位置
    char *start = str;

    // 查找delim中的任何字符
    while (*str && strchr(delim, *str) == NULL) {
        str++;
    }

    if (*str == '\0') {
        *saveptr = str;
    } else {
        // 在非空白字符后关闭token
        *str = '\0';
        str++;
        // 跳过后面的空白字符
        while (*str && isspace((unsigned char)*str)) str++;
        *saveptr = str;
    }

    // 处理字符串末尾的连续分隔符，产生空token
    if (*saveptr != start && **saveptr == '\0' && strchr(delim, *(start - 1))) {
        return (char *)"";
    }

    return start;
}



int main() {
    const char *delim = ",";
    char input[] = " , one , , two ,, , three , ,"; // 字符串以分隔符结尾
    char *next_ptr;
    char *token;
    uint32_t token_bits = 0; // 初始化bit位记录器
    int bit_index = 0;       // 用于设置token_bits中的位
    char *tokens[MAX_TOKENS] = {0}; // 存储tokens的数组

    token = my_strtok(input, delim, &next_ptr);
    while (token != NULL && bit_index < MAX_TOKENS) {
        tokens[bit_index] = token; // 保存token到数组中

        if (token[0] != '\0') { // 如果token不为空字符串
            token_bits |= (1U << bit_index); // 设置bit位为1
        }

        bit_index++; // 移动到下一个bit位
        token = my_strtok(NULL, delim, &next_ptr);
    }

    // 检查最后一个token是否为空（即input以分隔符结尾）
    if (bit_index > 0 && tokens[bit_index - 1][0] == '\0') {
        tokens[bit_index++] = NULL; // 添加一个空token
    }

    printf("Token bits: ");
    print_binary(token_bits);

    // 打印tokens数组
    printf("Tokens:\n");
    for (int i = 0; i < bit_index; ++i) {
        if (tokens[i] == NULL || tokens[i][0] == '\0') { // 如果token为空字符串，则表示它是NULL
            printf("(NULL)\n");
        } else {
            printf("%s\n", tokens[i]);
        }
    }

    return 0;
}
