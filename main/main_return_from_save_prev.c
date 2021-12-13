#include "../get_next_line.h"
#include <stdio.h>

// Comment everything except strdup, strchr and return_from_save_prev
// gccc main/main_return_from_save_prev.c get_next_line.c && ./a.out
// gccc -fsanitize=address -g3 main/main_return_from_save_prev.c get_next_line.c && ./a.out
int main()
{
	char *save_prev = ft_strdup("Hello\nCa va ?\nBien et toi ?\nTop!");
	printf("%s\n\n==========\n", save_prev);
	char *out = return_from_save_prev(&save_prev);
	printf("%s--\n", out);
	printf("%s\n\n==========\n", save_prev);
	free(out);

	out = return_from_save_prev(&save_prev);
	printf("%s--\n", out);
	printf("%s\n\n==========\n", save_prev);
	free(out);

	out = return_from_save_prev(&save_prev);
	printf("%s--\n", out);
	printf("%s\n\n==========\n", save_prev);
	free(out);

	system("leaks a.out");
}
