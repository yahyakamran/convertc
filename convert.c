#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int str_len(char *input_file) {
  int i;
  for (i = 0; input_file[i] != '\0'; ++i)
    ;
  return i;
}

void remove_extention(char string[], char substr[]) {
  int i = 0;
  int string_length = str_len(string);
  int substr_length = str_len(substr);
  while (i < string_length) {
    if (strstr(&string[i], substr) == &string[i]) {
      string_length -= substr_length;
      for (int j = i; j < string_length; j++)
        string[j] = string[j + substr_length];
    } else
      i++;
  }
  string[i] = '\0';
}
char *convert_to_html(char *input_file_name, char *input_file,
                      char *output_file_name) {
  int length = str_len(input_file);
  FILE *file;
  if ((file = fopen(output_file_name, "w")) == NULL) {
    return NULL;
  }
  remove_extention(input_file_name, ".txt");
  for (int i = 0; i < length; i++) {
    char current_char = input_file[i];
    if (0 == i || 10 == input_file[(i - 1)]) {
      if (0 == i) {
        fputs("<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta "
              "charset=\"UTF-8\">\n<meta name=\"viewport\" "
              "content=\"width=device-width, initial-scale=1.0\">\n<meta "
              "http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">\n"
              "<title>",
              file);
        fputs(input_file_name, file);
        fputs("</title>\n</head>\n<body>\n", file);
      }
      fputs("<p>", file);
      fputc(input_file[i], file);
      continue;
    }
    if (current_char == 10) {
      fputs("</p>", file);
      if (i != (length - 1)) {
        fputs("</br>", file);
      }else {
        fputs("\n</body>\n</html>\n",file);
      }
    }
    fputc(input_file[i], file);
  }
  return input_file;
}

char *read_file(char *file_name) {
  FILE *file;
  if ((file = fopen(file_name, "r")) == NULL) {
    return NULL;
  }
  fseek(file, 0, SEEK_END);
  int length = ftell(file);
  fseek(file, 0, SEEK_SET);
  char *string = malloc((sizeof(char)) * (length + 1));
  int i = 0;
  char c;
  while ((c = fgetc(file)) != EOF) {
    string[i] = c;
    i++;
  }
  string[i] = '\0';
  fclose(file);
  return string;
}

int main(int argv , char *argc[]) {
    printf("%d\n",argv);
    char *file_name = argc[1];
    char *content = read_file(file_name);
    if (NULL == content) {
    printf("An Error occured while opening the file");
    return 1;
    }
    convert_to_html(file_name, content,argc[2]);
    free(content);
    return 0;
}
