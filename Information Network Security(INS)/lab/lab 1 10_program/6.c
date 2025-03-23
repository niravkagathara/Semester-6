#include <stdio.h>
#include <string.h>
struct Student {
    int id;
    char name[50];
    float grade;
};
void addStudent(struct Student *s, int id, const char *name, float grade) {
    s->id = id;
    strcpy(s->name, name);
    s->grade = grade;
}
void displayStudent(struct Student s) {
    printf("ID: %d\n", s.id);
    printf("Name: %s\n", s.name);
    printf("Grade: %.2f\n", s.grade);
}
int main() {
    struct Student student1;
    addStudent(&student1, 1, "nirav", 85.5);
    displayStudent(student1);
    return 0;
}
