#ifndef HANIDOKU_CPP
#define HANIDOKU_CPP
#include "def.h"

#define N 9
#define HanidokuMax 999
int abs(int x) // 求绝对值
{
    if (x >= 0)
        return x;
    else
        return -x;
}
status printrules(int i, int len, int key, FILE *fp) // 打印规则
{
    for (int j = 1; j <= len; j++)
    {
        fprintf(fp, "%d ", i * 100 + j * 10 + key); // 填key
    }
}
status rules_1(int i, FILE *fp) // i:行数
{
    int len = 9 - abs(5 - i); // len:本行长度
    for (int k = 5 - (len - 5); k <= 5 + (len - 5); k++)
    {
        for (int j = 1; j <= len; j++)
        {
            fprintf(fp, "%d ", i * 100 + j * 10 + k);
        }
        fprintf(fp, "0\n");
    }
}
status rules_2(int i, FILE *fp) // 打印规则
{
    int len = 9 - abs(5 - i); // len:本行长度
    for (int j = 1; j <= len; j++)
    {
        for (int k = 1; k <= N; k++)
        {
            for (int l = j + 1; l <= len; l++)
            {
                fprintf(fp, "%d %d 0\n", -(i * 100 + j * 10 + k), -(i * 100 + l * 10 + k));
            }
        }
    }
}
status rules_3(int i, FILE *fp) // i:行数
{
    int len = 9 - abs(5 - i); // len:长度
    if (len == 9)             // 根据长度生成规则
        return OK;
    // 选填1或9
    else if (len == 8) // 8
    {
        printrules(i, len, 1, fp);
        printrules(i, len, 9, fp);
        fprintf(fp, "0\n");
    }
    // 81+82+92
    else if (len == 7) // 7
    {
        printrules(i, len, 1, fp);
        printrules(i, len, 8, fp);
        fprintf(fp, "0\n");
        printrules(i, len, 2, fp);
        printrules(i, len, 8, fp);
        fprintf(fp, "0\n");
        printrules(i, len, 2, fp);
        printrules(i, len, 9, fp);
        fprintf(fp, "0\n");
    }
    // 71+72+73+83+82+93
    else if (len == 6) // 6
    {
        printrules(i, len, 7, fp);
        printrules(i, len, 1, fp);
        fprintf(fp, "0\n");
        printrules(i, len, 7, fp);
        printrules(i, len, 2, fp);
        fprintf(fp, "0\n");
        printrules(i, len, 7, fp);
        printrules(i, len, 3, fp);
        fprintf(fp, "0\n");
        printrules(i, len, 8, fp);
        printrules(i, len, 3, fp);
        fprintf(fp, "0\n");
        printrules(i, len, 8, fp);
        printrules(i, len, 2, fp);
        fprintf(fp, "0\n");
        printrules(i, len, 9, fp);
        printrules(i, len, 3, fp);
        fprintf(fp, "0\n");
    }
    // 选填12346789，然而可选的是一个析取范式1234v2346v3467v4678v6789
    // 61+62+63+64+72+73+74+83+84+94
    else if (len == 5) // 5
    {
        printrules(i, len, 6, fp);
        printrules(i, len, 1, fp);
        fprintf(fp, "0\n");
        printrules(i, len, 6, fp);
        printrules(i, len, 2, fp);
        fprintf(fp, "0\n");
        printrules(i, len, 6, fp);
        printrules(i, len, 3, fp);
        fprintf(fp, "0\n");
        printrules(i, len, 6, fp);
        printrules(i, len, 4, fp);
        fprintf(fp, "0\n");
        printrules(i, len, 7, fp);
        printrules(i, len, 2, fp);
        fprintf(fp, "0\n");
        printrules(i, len, 7, fp);
        printrules(i, len, 3, fp);
        fprintf(fp, "0\n");
        printrules(i, len, 7, fp);
        printrules(i, len, 4, fp);
        fprintf(fp, "0\n");
        printrules(i, len, 8, fp);
        printrules(i, len, 3, fp);
        fprintf(fp, "0\n");
        printrules(i, len, 8, fp);
        printrules(i, len, 4, fp);
        fprintf(fp, "0\n");
        printrules(i, len, 9, fp);
        printrules(i, len, 4, fp);
        fprintf(fp, "0\n");
    }
}

status go_over_result(char filename[], int HaniDoku[][10]) // 把结果处理一下
{
    /*
    filename[4] = 'r';
    filename[5] = 'e';
    filename[6] = 's';
    */
    char c;
    /// int HaniDoku[10][10] = {0};
    FILE *fp;
    fp = fopen(filename, "r"); // 打开文件
    if (fp)
    {
        while ((c = getc(fp)) != 'v')
            ;
        int res[1000];
        for (int i = 1; i <= 959; i++)
        {
            fscanf(fp, "%d ", &res[i]);
        }
        // #test printf("%d\n", res[959]);
        int size[] = {0, 5, 6, 7, 8, 9, 8, 7, 6, 5};                    // 每行变元个数
        int start[] = {0, 111, 211, 311, 411, 511, 611, 711, 811, 911}; // 开始位置
        int final_answer[1000] = {0};                                   // 结果数组
        int count = 0;
        for (int i = 1; i <= 9; i++)
        {
            for (int j = start[i]; j <= (start[i] + (size[i] - 1) * 10 + 8) && j <= 959; j++)
            {
                if (res[j] > 0 && j % 10 != 0)
                    final_answer[++count] = res[j];
            }
        }
        /*
        for (int i = 1; i <= count; i++)
            printf("%d ", final_answer[i]);
        printf("\n%d\n", count);*/
        // 转化为数独表示
        // memset(HaniDoku, 0, sizeof(HaniDoku));
        for (int i = 1; i <= count; i++) // 保存结果到数独数组里面
        {
            int number = final_answer[i];
            int x = number / 100, y = number / 10 % 10, z = number % 10; // 提取各位数字
            HaniDoku[x][y] = z;
        }
        fclose(fp);

        return OK;
    }
    else
    {
        return ERROR;
    }
}

status showHanidoku(int HaniDoku[][10]) // 打印蜂窝数独
{
    int size[] = {0, 5, 6, 7, 8, 9, 8, 7, 6, 5}; // 长度数组
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= abs(i - 5); j++)
        {
            printf("  ");
        }
        for (int j = 1; j <= size[i]; j++)
        {
            printf(" / \\");
        }
        printf("\n");
        for (int j = 1; j <= abs(i - 5); j++)
        {
            printf("  ");
        }
        printf("| ");
        for (int j = 1; j <= size[i]; j++)
        {
            if (HaniDoku[i][j])
            {
                printf("%d | ", HaniDoku[i][j]); // 打印结果
            }
            else
            {
                printf(". | ");
            }
        }
        printf("\n");
    }
}
status createHanidoku(char filename[], int HaniDoku[][10]) // 生成数独
{
    srand(time(0));
    int number1 = rand() % RandN + 1;
    // memset(HaniDoku, 0, sizeof(HaniDoku));
    int x = 0;
    //      //
    filename[x++] = 'h';
    filename[x++] = (number1 / 10) + 48;
    filename[x++] = (number1 % 10) + 48;
    filename[x++] = '.', filename[x++] = 'c', filename[x++] = 'n', filename[x++] = 'f';
    filename[x++] = '\0';

    char c;
    FILE *fp;
    fp = fopen(filename, "r"); // 打开文件
    // printf("%d \n", number1);
    //  printf("%d\n", );
    if (fp)
    {
        while ((c = getc(fp)) == 'c')
        {
            while ((c = getc(fp)) != '\n')
                ;
        }
        // 过滤掉cnf
        for (int i = 1; i <= 4; i++)
        {
            c = getc(fp);
        }
        int boolnum, clsnum;
        Sleep(MaxLength * 2);
        fscanf(fp, "%d", &boolnum);
        fscanf(fp, "%d", &clsnum);
        int d, e;
        for (int i = 1; i <= 8 * RandN; i++) // 读取初始条件
        {
            fscanf(fp, "%d ", &d);
            fscanf(fp, "%d ", &e);
            if (e != 0)
            {
                break;
            }
            int x = d / 100, y = d / 10 % 10, z = d % 10; // 分离数字
            HaniDoku[x][y] = z;
        }
    }
    fclose(fp);                                  // 记得关闭文件
    int size[] = {0, 5, 6, 7, 8, 9, 8, 7, 6, 5}; // 长度数组
    printf("              HaniDoku:\n");
    showHanidoku(HaniDoku); // 查看数独
    return OK;
}

/*
int main()
{
}
*/

status transrules(ClsLists &cnf, char FileName[]) // 转换规则
{
    FILE *fp;
    fp = fopen(FileName, "w");
    if (fp)
    {
        fprintf(fp, "p cnf %d %d\n", MaxLength, MaxLength * N);
        for (int i = 1; i <= N; i++) // 枚举
        {
            rules_1(i, fp); // 规则1
            rules_2(i, fp); // 规则2
        }
        // #test printf("%d ",rules_1(2));
        for (int i = 1; i <= N; i++)
        {
            rules_3(i, fp); // 规则3
        }
        return OK;
    }
    else
    {
        return ERROR;
    }
}

status ask(int HaniDoku[][10], int x, int y, int value) // 询问功能
{
    if (HaniDoku[x][y] == value)
    {
        return TRUE;
    }
    return FALSE;
}

#endif