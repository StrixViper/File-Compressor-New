#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to compress the file using Run-Length Encoding (RLE)
void compressFile(const char *inputFilename, const char *outputFilename) {
    FILE *inputFile = fopen(inputFilename, "r");
    if (!inputFile) {
        printf("Could not open input file.\n");
        return;
    }

    FILE *outputFile = fopen(outputFilename, "w");
    if (!outputFile) {
        printf("Could not open output file.\n");
        fclose(inputFile);
        return;
    }

    char currentChar, previousChar;
    int count = 1;

    previousChar = fgetc(inputFile);
    if (previousChar == EOF) {
        printf("Empty file, nothing to compress.\n");
        fclose(inputFile);
        fclose(outputFile);
        return;
    }

    while ((currentChar = fgetc(inputFile)) != EOF) {
        if (currentChar == previousChar) {
            count++;
        } else {
            // Write the count and the character to the output file
            fprintf(outputFile, "%d%c", count, previousChar);
            count = 1;
            previousChar = currentChar;
        }
    }
    // Write the last sequence
    fprintf(outputFile, "%d%c", count, previousChar);

    printf("File compressed successfully!\n");

    fclose(inputFile);
    fclose(outputFile);
}

// Function to decompress the file that was compressed using RLE
void decompressFile(const char *inputFilename, const char *outputFilename) {
    FILE *inputFile = fopen(inputFilename, "r");
    if (!inputFile) {
        printf("Could not open input file.\n");
        return;
    }

    FILE *outputFile = fopen(outputFilename, "w");
    if (!outputFile) {
        printf("Could not open output file.\n");
        fclose(inputFile);
        return;
    }

    int count;
    char character;

    // Read the compressed file and decompress it
    while (fscanf(inputFile, "%d%c", &count, &character) == 2) {
        for (int i = 0; i < count; i++) {
            fputc(character, outputFile);
        }
    }

    printf("File decompressed successfully!\n");

    fclose(inputFile);
    fclose(outputFile);
}

// Function to display a menu and call the appropriate functions
void displayMenu() {
    int choice;
    char inputFilename[100], outputFilename[100];

    do {
        printf("\n--- File Compressor/Decompressor ---\n");
        printf("1. Compress File\n");
        printf("2. Decompress File\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter input file name to compress: ");
                scanf("%s", inputFilename);
                printf("Enter output file name to save compressed data: ");
                scanf("%s", outputFilename);
                compressFile(inputFilename, outputFilename);
                break;
            case 2:
                printf("Enter input file name to decompress: ");
                scanf("%s", inputFilename);
                printf("Enter output file name to save decompressed data: ");
                scanf("%s", outputFilename);
                decompressFile(inputFilename, outputFilename);
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Please select a valid option.\n");
        }
    } while (choice != 3);
}

// Main function to start the program
int main() {
    displayMenu();
    return 0;
}
