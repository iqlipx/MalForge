#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define ELF_HEADER_SIZE 64

// Function to corrupt ELF header with random bytes or nullify specific fields
void corrupt_elf_header(const char *file_path) {
    FILE *file = fopen(file_path, "r+");
    if (!file) {
        perror("Error opening file");
        return;
    }

    srand(time(NULL));  // Seed random number generator

    // Random corruption of ELF magic bytes
    fseek(file, 1, SEEK_SET);
    int random_byte = rand() % 256;
    fputc(random_byte, file);

    // Nullify section header table offset (random number of bytes nullified)
    fseek(file, 0x28, SEEK_SET);
    for (int i = 0; i < (rand() % 8 + 1); i++) {  // Corrupt up to 8 bytes
        fputc(0x00, file);
    }

    fclose(file);
    printf("[*] ELF header corrupted with random modifications.\n");
}

// Function to overwrite section headers (random and partial)
void overwrite_section_headers(const char *file_path) {
    FILE *file = fopen(file_path, "r+");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0x40, SEEK_SET);
    int overwrite_length = rand() % 256 + 64;  // Randomize overwrite length
    for (int i = 0; i < overwrite_length; i++) {
        fputc(rand() % 256, file);  // Random byte overwrite
    }

    fclose(file);
    printf("[*] Section headers overwritten (partial & random).\n");
}

// Function to remove the symbol table using XOR encryption
void remove_symbol_table(const char *file_path) {
    FILE *file = fopen(file_path, "r+");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0x50, SEEK_SET);
    char key = 0x5A;  // Simple XOR key
    for (int i = 0; i < 256; i++) {
        int byte = fgetc(file);
        if (byte == EOF) break;
        fseek(file, -1, SEEK_CUR);
        fputc(byte ^ key, file);  // XOR encryption
    }

    fclose(file);
    printf("[*] Symbol table encrypted using XOR.\n");
}

// Function to add decoy sections with random junk data
void add_decoy_section(const char *file_path) {
    FILE *file = fopen(file_path, "r+");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0x200, SEEK_SET);  // Arbitrary offset for the decoy section
    for (int i = 0; i < 64; i++) {
        fputc(rand() % 256, file);  // Random junk data
    }

    fclose(file);
    printf("[*] Decoy section added.\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <elf_binary>\n", argv[0]);
        return 1;
    }

    printf("[*] Processing ELF: %s\n", argv[1]);

    // Apply all corruption methods in sequence
    corrupt_elf_header(argv[1]);
    overwrite_section_headers(argv[1]);
    remove_symbol_table(argv[1]);
    add_decoy_section(argv[1]);

    printf("[*] Binary modification complete!\n");
    return 0;
}
