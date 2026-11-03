# include <stdio.h>
# include <string.h>
# define MAX_LENGTH 256 

int main(int argc, char *argv[]) {
    // While running ex1.exe, the user must provide two files as command line arguments: the input text file and the synonyms file. Otherwise, the program will print an error message and exit with a non-zero status code.
    if (argc != 3) {
        printf("Error: Expected 2 files\n");
        return 1;
    }

    // Open the input file for reading
    FILE *input=fopen(argv[1], "r");
    // Check if the input file was opened successfully
    if (input==NULL) {
        printf("Error: Could not open input file\n");
        return 2;
    }
    // Open the synonyms file for reading
    FILE *synonyms=fopen(argv[2], "r");
    // Check if the synonyms file was opened successfully
    if (synonyms==NULL) {
        printf("Error: Could not open synonyms file\n");
        // Close the input file before exiting
        fclose(input);
        return 3;
    }
    // Open the output file for writing
    FILE *output=fopen("output.txt", "w");
    // Check if the output file was opened successfully
    if (output == NULL) {
        printf("Error: Could not open output file\n");
        // Close the input and synonyms files before exiting
        fclose(input);
        fclose(synonyms);
        return 4;
    }
    // Declare variables for processing the input and synonyms files
    char line[MAX_LENGTH];
    char word[MAX_LENGTH];
    char new_word[MAX_LENGTH];
    int flag;
    int char_holder;
    char s_line[MAX_LENGTH];
    char s_word[MAX_LENGTH];
    int i, j, k, w;
    // Each iteration of the loop reads a new line from the input file
    while (fgets(line, MAX_LENGTH, input) != NULL) {
        // Initialize the index for the current position in the line
        i=0;
        // While the line has not reached the end of the string
        while (line[i] != '\0') {
            // Initialize the index for the current position in the word from the line
            j=0;
            // Start detecting a word from the line until reaching a non-alphabetic character or the end of the line
            while ((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z')) {
                word[j]=line[i];
                i++;
                j++;
            }
            // Null-terminate the word string
            word[j]='\0';
            // If no word was detected (j == 0), print the current character and write it to the output file, then continue to the next character in the line
            if (j == 0) {
                printf("%c", line[i]);
                fputc(line[i], output);
                i++;
                continue;
            }
            // If a word was detected, check if there is a character following the word in the line (like " ")
            if (line[i] != '\0') {
                char_holder=line[i];
                i++;
            }
            // If there is no character following the word, set char_holder to '\0' (end of line)
            else {
                char_holder='\0';
            }
            // Reset the flag to 0 before searching for synonyms
            flag=0;
            rewind(synonyms); // Reset the synonyms file pointer to the beginning
            // Read each line from the synonyms file to find a matching word
            while (fgets(s_line, MAX_LENGTH, synonyms) != NULL) {
                // Reset the index for the current position in the synonyms line
                k=0;
                // Extract the word from the synonyms line until reaching a colon
                while (s_line[k] != ':') {
                    s_word[k]=s_line[k];
                    k++;
                }
                // Null-terminate the extracted word string
                s_word[k]='\0';
                // If there is a character following the colon in the synonyms line, skip it (usually a space), or jupd the start of the synonym word
                if (s_line[k] != '\0') {
                    k+=2;
                }
                // Compare the detected word from the input line with the extracted word from the synonyms line
                if (strcmp(word, s_word) == 0) {
                    // If a match is found, set the flag to 1 and extract the synonym word from the synonyms line
                    flag=1;
                    w=0;
                    while ((s_line[k] >= 'a' && s_line[k] <= 'z') || (s_line[k] >= 'A' && s_line[k] <= 'Z')) {
                        new_word[w]=s_line[k];
                        k++;
                        w++;
                    }
                    // Null-terminate the new_word string
                    new_word[w]='\0';
                    // Break the loop since a match has been found
                    break;
                }
            }
            // After checking all synonyms, print the appropriate word (either the original or the synonym) and write it to the output file. If there was a character following the word, print and write that character as well.
            if (flag) {
                printf("%s", new_word);
                fputs(new_word, output);
            }
            else {
                printf("%s", word);
                fputs(word, output);
            }
            if (char_holder != '\0') {
                printf("%c", char_holder);
                fputc(char_holder, output);
            }
        }
    }
    // Close all opened files before exiting the program
    fclose(input);
    fclose(synonyms);
    fclose(output);
    return 0;
}