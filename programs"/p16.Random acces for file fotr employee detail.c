#include <stdio.h>
#include <stdlib.h>

struct employee {
    int id;
    char name[20];
    float salary;
};

void add_employee(FILE* file, struct employee* emp) {
    fseek(file, 0, SEEK_END);
    fwrite(emp, sizeof(struct employee), 1, file);
}

void get_employee(FILE* file, int id) {
    struct employee emp;
    fseek(file, (id - 1) * sizeof(struct employee), SEEK_SET);
    fread(&emp, sizeof(struct employee), 1, file);
    printf("ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
}

int main() {
    FILE* file = fopen("employees.dat", "w+b");
    if (!file) {
        perror("fopen");
        return 1;
    }
    
    struct employee e1 = {1, "Alice", 500
