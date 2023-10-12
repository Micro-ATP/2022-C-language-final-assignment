#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_STUDENTS 1000
#define FILENAME "grades.txt"

typedef struct {
    char id[50];
    char name[50];
    float math;
    float english;
    float physics;
    float average;
    int rank;
} Student;

void saveStudentsToFile(Student students[], int count) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("�޷����ļ���\n");
        return;
    }

    fprintf(file, "ѧ��\t\t\t����\t\t�ߵ���ѧ\t\tӢ��\t\t����\t\tƽ���ɼ�\t\t����\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\t\t%s\t\t%.2f\t\t\t%.2f\t\t%.2f\t\t%.2f\t\t\t%d\n",
                students[i].id, students[i].name, students[i].math, students[i].english,
                students[i].physics, students[i].average, students[i].rank);
    }

    fclose(file);
}

void insertStudent(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("�ɼ����������޷������¼�¼��\n");
        return;
    }

    Student student;

    printf("������ѧ����ѧ�ţ�");
    scanf(" %[^\n]1", student.id);

     // ���ѧ�����Ƿ���ڿո�
    for (int i = 0; i < strlen(student.id); i++) {
        if (student.id[i] == ' ') {
            printf("�����й���ý��ѧ������ѧ������涨��ѧ���в��ܰ����ո����������롣\n");
            return;
        }
    }

    // ���ѧ���Ƿ��Ѵ���
    for (int i = 0; i < *count; i++) {
        if (strcmp(students[i].id, student.id) == 0) {
            printf("�����й���ý��ѧ������ѧ������涨��ѧ���Ѵ��ڣ����������롣\n");
            return;
        }
    }
    printf("������ѧ����������");
    scanf(" %[^\n]", student.name);  // ʹ�ô��ո�ĸ�ʽ�ַ�����ȡ����

    // ����������Ƿ���ڿո�
    for (int i = 0; i < strlen(student.name); i++) {
        if (student.name[i] == ' ') {
            printf("�����й���ý��ѧ������ѧ������涨�������в��ܰ����ո����������롣\n");
            return;
        }
    }

   do {
    printf("������ѧ���ĸߵ���ѧ�ɼ���");
    if (scanf("%f", &student.math) != 1) {
        printf("�����й���ý��ѧ����ѧ���γ̳ɼ�����취���޶������ɼ�����Ϊ���֣�������Ч���������������֡�\n");
        while (getchar() != '\n'); // ������뻺����
        continue;
    }
    if (student.math < 0 || student.math > 100) {
        printf("�����й���ý��ѧ����ѧ���γ̳ɼ�����취���޶������ɼ�������0��100֮�䣬���������롣\n");
    }
} while (student.math < 0 || student.math > 100);

do {
    printf("������ѧ����Ӣ��ɼ���");
    if (scanf("%f", &student.english) != 1) {
        printf("�����й���ý��ѧ����ѧ���γ̳ɼ�����취���޶������ɼ�����Ϊ���֣�������Ч���������������֡�\n");
        while (getchar() != '\n'); // ������뻺����
        continue;
    }
    if (student.english < 0 || student.english > 100) {
        printf("�����й���ý��ѧ����ѧ���γ̳ɼ�����취���޶������ɼ�������0��100֮�䣬���������롣\n");
    }
} while (student.english < 0 || student.english > 100);

do {
    printf("������ѧ��������ɼ���");
    if (scanf("%f", &student.physics) != 1) {
        printf("�����й���ý��ѧ����ѧ���γ̳ɼ�����취���޶������ɼ�����Ϊ���֣�������Ч���������������֡�\n");
        while (getchar() != '\n'); // ������뻺����
        continue;
    }
    if (student.physics < 0 || student.physics > 100) {
        printf("�����й���ý��ѧ����ѧ���γ̳ɼ�����취���޶������ɼ�������0��100֮�䣬���������롣\n");
    }
} while (student.physics < 0 || student.physics > 100);


    student.average = (student.math + student.english + student.physics) / 3.0;
    student.rank = 0;

    students[*count] = student;
    (*count)++;

    printf("ѧ����Ϣ����ɹ���\n");

    saveStudentsToFile(students, *count);
}

void deleteStudent(Student students[], int *count) {
    char id[50];
    printf("������Ҫɾ����ѧ��ѧ�ţ�");
    scanf("%s", id);

    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            found = 1;
            printf("ѧ����Ϣɾ���ɹ���\n");
            break;
        }
    }

    if (!found) {
        printf("δ�ҵ���Ӧѧ�ŵ�ѧ����\n");
    }

    saveStudentsToFile(students, *count);
}

void updateStudent(Student students[], int count) {
    char id[50];
    printf("������Ҫ�޸ĵ�ѧ��ѧ�ţ�");
    scanf("%s", id);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            do {
                printf("������ѧ���ĸߵ���ѧ�ɼ���");
                if (scanf("%f", &students[i].math) != 1) {
                    printf("�����й���ý��ѧ����ѧ���γ̳ɼ�����취���޶������ɼ�����Ϊ���֣�������Ч���������������֡�\n");
                    while (getchar() != '\n'); // ������뻺����
                    continue;
                }
                if (students[i].math < 0 || students[i].math > 100) {
                    printf("�����й���ý��ѧ����ѧ���γ̳ɼ�����취���޶������ɼ�������0��100֮�䣬���������롣\n");
                }
            } while (students[i].math < 0 || students[i].math > 100);

            do {
                printf("������ѧ����Ӣ��ɼ���");
                if (scanf("%f", &students[i].english) != 1) {
                    printf("�����й���ý��ѧ����ѧ���γ̳ɼ�����취���޶������ɼ�����Ϊ���֣�������Ч���������������֡�\n");
                    while (getchar() != '\n'); // ������뻺����
                    continue;
                }
                if (students[i].english < 0 || students[i].english > 100) {
                    printf("�����й���ý��ѧ����ѧ���γ̳ɼ�����취���޶������ɼ�������0��100֮�䣬���������롣\n");
                }
            } while (students[i].english < 0 || students[i].english > 100);

            do {
                printf("������ѧ��������ɼ���");
                if (scanf("%f", &students[i].physics) != 1) {
                    printf("�����й���ý��ѧ����ѧ���γ̳ɼ�����취���޶������ɼ�����Ϊ���֣�������Ч���������������֡�\n");
                    while (getchar() != '\n'); // ������뻺����
                    continue;
                }
                if (students[i].physics < 0 || students[i].physics > 100) {
                    printf("�����й���ý��ѧ����ѧ���γ̳ɼ�����취���޶������ɼ�������0��100֮�䣬���������롣\n");
                }
            } while (students[i].physics < 0 || students[i].physics > 100);

            students[i].average = (students[i].math + students[i].english + students[i].physics) / 3.0;

            printf("ѧ����Ϣ�޸ĳɹ���\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("δ�ҵ���Ӧѧ�ŵ�ѧ����\n");
    }

    saveStudentsToFile(students, count);
}


/*int compareByMath(const void *a, const void *b) {
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;

    if (studentA->math < studentB->math) {
        return -1;
    } else if (studentA->math > studentB->math) {
        return 1;
    } else {
        return 0;
    }
}

void sortByMath(Student students[], int count) {
    qsort(students, count, sizeof(Student), compareByMath);
}*/

void calculateAverage(Student students[], int count) {
    for (int i = 0; i < count; i++) {
        students[i].average = (students[i].math + students[i].english + students[i].physics) / 3.0;
    }
}

int compareByAverage(const void *a, const void *b) {
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;

    if (studentA->average < studentB->average) {
        return 1;
    } else if (studentA->average > studentB->average) {
        return -1;
    } else {
        return 0;
    }
}

void sortByAverage(Student students[], int count) {
    qsort(students, count, sizeof(Student), compareByAverage);
}

void assignRanks(Student students[], int count) {
    int rank = 1;
    students[0].rank = rank;

    for (int i = 1; i < count; i++) {
        if (students[i].average == students[i - 1].average) {
            students[i].rank = rank;
        } else {
            students[i].rank = ++rank;
        }
    }
}

void printStudents(Student students[], int count) {
    printf("ѧ��\t\t\t����\t\t�ߵ���ѧ\t\tӢ��\t\t����\t\tƽ���ɼ�\t\t����\n");
    for (int i = 0; i < count; i++) {
        printf("%13s\t\t%s\t\t%.2f\t\t\t%.2f\t\t%.2f\t\t%.2f\t\t\t%d\n",
               students[i].id, students[i].name, students[i].math, students[i].english,
               students[i].physics, students[i].average, students[i].rank);
    }
}

void readStudentsFromFile(Student students[], int *count) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("�޷����ļ���\n");
        return;
    }

    fscanf(file, "%*[^\n]\n");  // ������ͷ

    while (fscanf(file, "%s %s %f %f %f %f %d",
                  students[*count].id, students[*count].name, &students[*count].math,
                  &students[*count].english, &students[*count].physics,
                  &students[*count].average, &students[*count].rank) == 7) {
        (*count)++;
    }

    fclose(file);
}

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;

    readStudentsFromFile(students, &count);

    char choice;
    do {
        printf("\n�ɼ��������\n");
        printf("1. ����ѧ����¼\n");
        printf("2. ɾ��ѧ����¼\n");
        printf("3. �޸�ѧ����¼\n");
        printf("4. ������,�޷�ʹ��\n");
        printf("5. ����ÿ��ѧ����ƽ���ɼ���������ɼ���\n");
        printf("0. �˳�����\n");
        printf("������ѡ�ֻ�����������֣��������Ը�����");
        scanf("%c", &choice);

        switch (choice) {
            case '1':
                insertStudent(students, &count);
                break;
            case '2':
                deleteStudent(students, &count);
                break;
            case '3':
                updateStudent(students, count);
                break;
            /*case 4:
                sortByMath(students, count);
                break;*/
            case '5':
                calculateAverage(students, count);
                sortByAverage(students, count);
                assignRanks(students, count);
                printStudents(students, count);
                saveStudentsToFile(students, count);
                break;
            case '0':
                printf("�������˳���\n");
                break;
            default:
                printf("��Ч��ѡ�\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
