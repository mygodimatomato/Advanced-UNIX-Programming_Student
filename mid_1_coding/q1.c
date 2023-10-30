// uniq -i -u -c
// uniq -iuc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXLEN 4096

int ignore_case = 0;
int unique = 0;
int count = 0;

int mystrcmp(char *str1, char *str2, int nonsensitive)
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	if (len1 != len2)
		return 1; // not same
	int len = len1;
	for (int i = 0; i < len; i++)
	{
		if (!isalnum(str1[i]) || !isalnum(str2[i]))
			continue;
		if (nonsensitive)
		{
			char a = (isupper(str1[i]) ? str1[i] : str1[i] - 32);
			char b = (isupper(str2[i]) ? str2[i] : str2[i] - 32);
			if (a != b)
				return 1;
		}
		else
		{
			if (str1[i] != str2[i])
				return 1;
		}
	}
	return 0;
}
int mycmp(const void *str1, const void *str2)
{
	return strcmp(str1, str2);
}

void printit(char *str, int cnt, int newline)
{
	if (count)
	{
		printf("   %d ", cnt);
	}
	printf("%s", str);
	if (newline)
		printf("\n");
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}
	char filename[MAXLEN];
	strcpy(filename, argv[argc - 1]);
	ignore_case = 0;
	unique = 0;
	count = 0;
	for (int i = 1; i < argc - 1; i++)
	{
		if (argv[i][0] == '-')
		{
			int slen = strlen(argv[i]);
			for (int j = 1; j < slen; j++)
			{
				switch (argv[i][j])
				{
				case 'i':
					ignore_case = 1;
					break;
				case 'u':
					unique = 1;
					break;
				case 'c':
					count = 1;
					break;
				default:
					printf("Usage: %s [-iuc] <filename>\n", argv[0]);
					return 1;
				}
			}
		}
	}

	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("File not found: %s\n", filename);
		return 1;
	}

	char line[MAXLEN];
	char prev[MAXLEN];
	size_t totalline = 0;
	size_t maxlen = 0;

	// count lines and reset seek.
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		totalline = totalline + 1;
		int len = strlen(line);
		if (line[len - 1] == '\n')
		{
			line[len - 1] = '\0';
			len = len - 1;
		}
		if (maxlen < len)
			maxlen = len;
	}
	maxlen = maxlen + 1;
	fseek(fp, SEEK_SET, 0);
#ifdef DEBUG
	printf("total line: %d\n", totalline);
#endif

	// sort items
	char *textraw = (char *)malloc(sizeof(char) * maxlen * totalline);
	char **texts = (char **)malloc(sizeof(char *) * totalline);
	for (size_t i = 0; i < totalline; i++)
	{
		fgets(line, sizeof(line), fp);
		int len = strlen(line);
		if (line[len - 1] == '\n')
		{
			line[len - 1] = '\0';
			len = len - 1;
		}
#ifdef DEBUG
		printf("in %d:%s with len=%d\n", i, line, len);
#endif
		texts[i] = (textraw + i * maxlen);
		strcpy(texts[i], line);
		texts[i][len] = '\0';
	}

#ifdef DEBUG
	printf("before sort\n");
	for (size_t i = 0; i < totalline; i++)
	{
		printf("%d: %s\n", i, texts[i]);
	}
#endif

	qsort(textraw, totalline, sizeof(char) * maxlen, mycmp);
#ifdef DEBUG
	printf("after sort\n");
	for (size_t i = 0; i < totalline; i++)
	{
		printf("%d: %s\n", i, texts[i]);
	}
#endif

	// origin program

	int cnt = 0;
	int first = 1;
	for (size_t i = 0; i < totalline; i++)
	{
		strcpy(line, texts[i]);
		int len = strlen(line);
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (first)
		{
			strcpy(prev, line);
			first = 0;
			cnt = 1;
			continue;
		}
		if (mystrcmp(line, prev, ignore_case) == 0)
		{
			cnt++;
		}
		else
		{
			if (!unique || cnt == 1)
			{
				printit(prev, cnt, 1);
			}
			strcpy(prev, line);
			cnt = 1;
		}
	}

	if (!unique || cnt == 1)
	{
		printit(prev, cnt, 1);
	}
}
