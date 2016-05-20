#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

struct book {
    int id;
    char *name;
    char *phone;
};

FILE *book_file;

struct book* porsons;
size_t book_size;
int used[10000000];

char *read_file(void) {
    size_t size = 32;
    char *str = (char *) malloc(sizeof(char) * size);
    int n = 0;

    while (!feof(book_file)) {
        char s = fgetc(book_file);
        if (s == '\n' || s == ' ' || s == EOF) {
            str[n] = '\0';
            return str;
        }
        if (size == n + 1) {
            str = (char*)realloc(str,sizeof(char) * (size *= 2));
        }
        str[n++] = s;

    }
    str[n] = '\0';
    return str;
}

int is_correct_name(char* s) {
    int j = 0;
    while(j < strlen(s)){
        if (!isalpha(s[j++]))
            return 0;
    }
    return 1;
}

char *readString(void) {
    size_t size = 32;
    char *str = (char *) malloc(sizeof(char) * size);
    int n = 0;
    while (1) {
        char s = getchar();
        if (s == '\n' || s == ' ') {
            str[n] = '\0';
            return str;
        }
        if (size == n + 1) {
            str = (char*)realloc(str,sizeof(char) * (size *= 2));
        }
        str[n++] = s;
    }
}

char* clearPhone(char* phone){
    int i = 0,l= 0 ;
    char* ans = (char*)malloc(sizeof(char) * strlen(phone));
    while(i < strlen(phone)){
        if(isdigit(phone[i]))ans[l++] = phone[i];
        i++;
    }
    return ans;

}

char* toLow(char* name){
    int i = 0;
    while(i < strlen(name)){
        name[i] = tolower(name[i]);
        i++;
    }
    return name;

}
int correctPhone(char *s) {
    int b = 0, bb = 0;
    int i = 0;
    while(i < strlen(s)) {
        if (s[i] == '(')
            ++b;
        if (s[i] == ')')
            bb++;
        if (b - bb < 0 || (i != 0 && s[i] == '+') || b > 1 || (s[i] == '-' && s[i + 1] == '-') ||
            (!isdigit(s[i]) && s[i] != '-' && s[i] != '+' && s[i] != '(' && s[i] != ')'))
            return 0;
        i++;
    }
    return 1;
}
void find_name(char *name) {
    name = toLow(name);
    int i = 0;
    while(i < book_size) {
        if (used[i] == 0) {
            i++;
            continue;
        }
        char *curName = porsons[i].name;
        curName = toLow(curName);
        if (strstr(curName, name) != NULL) {
            printf("%d %s %s \n", i, porsons[i].name, porsons[i].phone);
        }
        i++;
    }

}

void create(char *name, char *phone) {
    int i = 0;
    while(i < book_size) {
        if (used[i] == 0) {
            porsons[i].name = name;
            porsons[i].phone = phone;
            used[i] = 1;
            return;
        }
        i++;
    }
    int cur = book_size;
    porsons = (struct book*)realloc(porsons, book_size *= 2);
    porsons[cur].name = name;
    porsons[cur].phone = phone;
    used[cur] = 1;
}

void write(void) {
    int i = 0;
    while(i < book_size) {
        if (used[i] == 1)
            fprintf(book_file, "%d %s %s\n", i, porsons[i].name, porsons[i].phone);
        i++;
    }
}

void read(void) {
    if(fgetc(book_file) == EOF)return;
    while (!feof(book_file)){
        int index = NULL;
        
        fscanf(book_file, "%d", &index);

        while (index >= book_size) {
            porsons = (struct book *) realloc(porsons, book_size *= 2);
        }
        porsons[index].name = read_file();
        porsons[index].phone = read_file();
        used[index] = 1;
    }
}

void find_phone(char *phone) {
    int i = 0;
    while(i < book_size) {
        if (used[i] == 0){
            i++;
            continue;

        }
        phone = clearPhone(phone);
        char *cur = clearPhone(porsons[i].phone);
        if(strcmp(cur, phone) == 0) {
            printf("%d %s %s\n", i, porsons[i].name, porsons[i].phone);
        }
        i++;
    }
}

void free_mem() {
    for (int i = 0; i < book_size; ++i) {
        free(porsons[i].name);
        free(porsons[i].phone);
    }
    free(porsons);
}

int main(int argc, char *argv[]) {

    book_size = 10;
    porsons = (struct book*)malloc(sizeof(struct book) * book_size);

    char* file = argv[1];
    book_file = fopen(file, "r+");
    if (book_file == NULL) {
        book_file = fopen(file, "w+");
    } else {
        read();
    }
    char *command = NULL;
    while(1) {
        if (command != NULL) {
            free(command);
        }
        command = readString();
        if (strcmp(command, "find") == 0) {
            char *str = readString();
            if (isalpha(str[0])) {
                if (!is_correct_name(str)) {
                    free(str);
                    printf("Error, try again \n");
                    continue;
                }
                find_name(str);
            } else {
                if (!correctPhone(str)) {
                    printf("Error, try again \n");
                    free(str);
                    continue;
                }
                find_phone(str);
            }
            free(str);

        }
        if (strcmp(command, "delete") == 0) {
            int index;
            scanf("%d", &index);
            used[index] = 0;
            porsons[index].phone = NULL;
            porsons[index].name = NULL;
        }
        if (strcmp(command, "change") == 0) {
            int index;
            scanf("%d", &index);
            char *string1 = readString();
            if (strcmp(string1, "name") == 0) {
                string1 = readString();
                porsons[index].name = string1;
            } else {
                string1 = readString();
                porsons[index].phone = string1;
            }
        }
        if (strcmp(command, "create") == 0) {
            char *name = readString();
            char *phone = readString();
            if (!is_correct_name(name) || !correctPhone(phone)) {
                free(name);
                free(phone);
                printf("Error, try again \n");
                continue;
            }
            create(name, phone);
        }
        
        fclose(book_file);
        book_file = fopen(file, "w+");
        write();

        if (strcmp(command, "exit") == 0) {
            free_mem();
            fclose(book_file);
            return 0;
        }
        fflush(stdout);
    }
}