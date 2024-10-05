#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* trim_spaces(char* str)
{
	char* end = NULL;

	while (isspace((unsigned char)*str))
		str++;

	if (*str == 0)
		return str;

	end = str + strlen(str) - 1;

	while (end > str && isspace((unsigned char)*end))
		end--;

	*(end + 1) = '\0';

	return str;
}

char* str_split(char** stringp, const char* delim)
{

	if (!stringp || !*stringp)
		return NULL;

	char* start = *stringp;
	char* end = NULL;

	end = strchr(start, *delim);

	if (end) {
		*end = '\0';
		*stringp = end + 1;
	} else {
		*stringp = start + strlen(start);
	}

	if (start == *stringp)
		return NULL;

	return trim_spaces(start);
}

int main()
{
	char str[] = "   ,Hello,, ,World,     How , are,you,   "; // 测试字符串
	char* token[20] = { NULL };
	char* rest = str;
	int i = 0;

	while ((token[i] = str_split(&rest, ",")) != NULL) {
		printf("[%04d] %ld %ld\n", i, strlen(token[i]), sizeof(token[i]));
		if (!strlen(token[i]))
			token[i] = NULL;
		i++;
	}

	for (i = 0; i < 20; i++)
		printf("[%02d] %d %s \n", i, token[i] == NULL, token[i]);

	return 0;
}
