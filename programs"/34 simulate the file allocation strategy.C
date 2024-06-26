#include <stdio.h>
#include <stdlib.h>

// Structure to represent a record
struct Record {
    int recordNumber;
    char data[256]; // Adjust the size as needed for your records
};

int main() {
    FILE *file;
    struct Record record;
    int recordNumber;

    // Open or create a file in write mode (for writing records)
    file = fopen("record_file.txt", "w");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Write records
    printf("Enter records (Enter '0' as record number to exit):\n");
    while (1) {
        printf("Record Number: ");
        scanf("%d", &record.recordNumber);
        if (record.recordNumber == 0) {
            break;
        }
        printf("Data: ");
        scanf(" %[^\n]", record.data);
        fwrite(&record, sizeof(struct Record), 1, file);
    }

    fclose(file); // Close the file after writing

    // Reopen the file in read mode (for reading records)
    file = fopen("record_file.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Read a specific record from the file
    printf("Enter the record number to read (0 to exit): ");
    while (1) {
        scanf("%d", &recordNumber);
        if (recordNumber == 0) {
            break;
        }

        rewind(file); // Move the file pointer to the beginning

        while (fread(&record, sizeof(struct Record), 1, file)) {
            if (record.recordNumber == recordNumber) {
                printf("Record Number: %d\n", record.recordNumber);
                printf("Data: %s\n", record.data);
                break;
            }
        }

        if (feof(file)) {
            printf("Record not found.\n");
        }
    }

    fclose(file); // Close the file after reading
    return 0;
}

