#include <stdio.h>

// 텍스트 쓰기의 예
/*
int main(int argc, char **argv)
{
	int students, s, sum = 0;
    int score[] = {85, 90, 95, 70, 82, 60, 92, 88};
    double average;
    FILE *fp;
    students = sizeof(score) / sizeof(int);
    
    for (s = 0; s < students; s++)
        sum += score[s];
        
    average = (double)sum / students;
    
    if((fp = fopen("score.txt", "wt")) == NULL) {    // 파일 열기
        printf("Can't not open the File. \n");
        return 1;
    }
    fputs("Exam Result \n", fp);
    fprintf(fp, "Sum : %d \n", sum);
    fprintf(fp, "Average : %0.2f \n", average);
    fclose(fp);
    
    return 0;
}
*/

// 텍스트 쓰기의 예 
#define MAX_INPUT 128

int main(int argc, char **argv) {
    FILE *fp;
    char text[MAX_INPUT];
    int total;
    double average;
    
    if ((fp = fopen("score.txt", "rt")) == NULL) {      // 파일 열기
        printf("Can't not open the File. \n");
        return 1;
    }
    fgets(text, MAX_INPUT, fp);             // 파일 읽기
    printf("%s", text);
    fscanf(fp, "%s %d", text, &total);      // 파일 읽기 
    printf("%s %d \n", text, total);
    fscanf(fp, "%s %lf", text, &average);   // 파일 읽기
    printf("%s %0.2f \n", text, average);
    fclose(fp);                             // 파일 닫기
    
    return 0;
}
