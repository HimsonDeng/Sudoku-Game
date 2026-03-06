#include "SAT.h"
#include "HaniDoku.h"
int main()
{
    system("color B");          // 换颜色
    int op = 1;                 // 选择
    ClsLists cnf = NULL;        // 新建一个
    int HaniDoku[10][10] = {0}; // 蜂窝数独数组
    while (op)
    {
        system("cls"); // 清屏
        printf("                SAT and Hanidoku Slover\n");
        printf("----------------------------------------------------------------------\n");
        printf("                        SAT\n");
        printf("        1.read cnf       2.print cnf      3.DPLL        4.DPLL_pre\n");
        printf("\n");
        // printf("----------------------------------------------------------------------\n");
        printf("                        Hanidoku\n");
        printf("        5.createHan       6.solveHan      7.showHan     8.query\n");
        printf("----------------------------------------------------------------------\n");
        printf("                        0.exit\n");
        printf("select an option[0-8]:\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
        {
            printf("please input your filename:\n");
            scanf("%s", filename); // 读入名字
            // printf("\n%s", filename);
            createClause(cnf, filename); // 生成子句
            // destroyClause(cnf);
            printf("cnf file has been successfully loaded!\n");
            getchar();
            getchar();
            break;
        }
        case 2:
        {
            if (cnf != NULL)
            {
                ClsLists cnf_temp = cnf;
                ClsNodes phead_temp = cnf->phead;

                while (cnf_temp != NULL) // 遍历子句
                {
                    while (phead_temp != NULL)
                    {
                        printf("%d ", phead_temp->words); // 打印子句
                        phead_temp = phead_temp->pnext;
                    }
                    // if (phead_temp == NULL)
                    //  printf("OK\n");
                    printf("\n");
                    if (cnf_temp->pnext == NULL)
                        break;
                    cnf_temp = cnf_temp->pnext;
                    phead_temp = cnf_temp->phead;
                }
            }
            else
            {
                printf("No cnf file!\n");
            }
            // if (cnf_temp->pnext == NULL)
            // printf("OK\n");
            getchar();
            getchar();
            break;
        }
        case 3:
        {
            // printf("%d ", boolnum);
            if (cnf != NULL)
            {
                int *val = (int *)malloc((boolnum + 1) * sizeof(int)); // 生成标记数组
                for (int i = 1; i <= boolnum; i++)
                {
                    val[i] = 1;
                }
                clock_t begin, end;
                begin = clock(); // 开始计时

                status final_result = DPLL(cnf, val);

                end = clock(); // 结束计时
                printf("s %d\n", final_result);
                // 按照规范打印文件
                if (final_result == TRUE)
                {
                    printf("v ");
                    for (int i = 1; i <= boolnum; i++) // 输出变元取值情况
                    {
                        if (val[i] == TRUE)
                        {
                            printf("%d ", i);
                        }
                        else
                        {
                            printf("%d ", -i);
                        }
                    }
                    printf("\n");
                }
                double time = (double)(end - begin) / CLOCKS_PER_SEC; // 计算时间
                printf("t %.0lf", time * 1000);
                SaveResult(time, final_result, val); // 保存文件
                printf("\nThe result has been saved!\n");
                free(val);
            }
            else
            {
                printf("No cnf file!\n");
            }
            getchar();
            getchar();
            break;
        }
        case 4:
        {
            // printf("%d ", boolnum);
            if (cnf != NULL)
            {
                int *val = (int *)malloc((boolnum + 1) * sizeof(int)); // 生成标记数组
                for (int i = 1; i <= boolnum; i++)
                {
                    val[i] = 1;
                }
                clock_t begin, end;
                begin = clock(); // 开始计时

                status final_result = DPLL_prev2(cnf, val);

                end = clock(); // 结束计时
                printf("s %d\n", final_result);

                if (final_result == TRUE)
                {
                    printf("v ");
                    for (int i = 1; i <= boolnum; i++) // 输出变元取值情况
                    {
                        if (val[i] == TRUE)
                        {
                            printf("%d ", i);
                        }
                        else
                        {
                            printf("%d ", -i);
                        }
                    }
                    printf("\n");
                }
                double time = (double)(end - begin) / CLOCKS_PER_SEC; // 计算时间
                printf("t %.0lf", time * 1000);
                SaveResult(time, final_result, val); // 保存文件
                printf("\nThe result has been saved!\n");
                free(val);
            }
            else
            {
                printf("No cnf file!\n");
            }
            getchar();
            getchar();
            break;
        }
        case 5:
        {
            // 初始化蜂窝数独数组
            for (int i = 1; i <= 9; i++)
            {
                for (int j = 1; j <= 9; j++)
                {
                    HaniDoku[i][j] = 0;
                }
            }
            createHanidoku(filename, HaniDoku); // 生成蜂窝数独
            transrules(cnf, filename);          // 生成各种子句
            getchar();
            getchar();
            break;
        }
        case 6:
        {
            // 调用dpll过程
            createClause(cnf, filename);
            if (cnf != NULL)
            {
                printf("bollnum:%d\n", boolnum);
                int *val = (int *)malloc((boolnum + 1) * sizeof(int)); // 生成标记数组
                for (int i = 1; i <= boolnum; i++)
                {
                    val[i] = 1;
                }
                clock_t begin, end;
                begin = clock(); // 开始计时

                status final_result = DPLL(cnf, val);

                end = clock(); // 结束计时
                printf("s %d\n", final_result);

                if (final_result == TRUE)
                {
                    printf("v ");
                    for (int i = 1; i <= boolnum; i++) // 输出变元取值情况
                    {
                        if (val[i] == TRUE)
                        {
                            printf("%d ", i);
                        }
                        else
                        {
                            printf("%d ", -i);
                        }
                    }
                    printf("\n");
                }
                double time = (double)(end - begin) / CLOCKS_PER_SEC; // 计算时间
                // printf("t %.0lf", time * 1000);
                SaveResult(time, final_result, val); // 保存文件
                printf("\nThe result has been saved!\n");
                free(val);
                go_over_result(filename, HaniDoku);
            }
            else
            {
                printf("No cnf file!\n");
            }
            getchar();
            getchar();
            break;
        }
        case 7:
        {
            go_over_result(filename, HaniDoku); // 把求解结果转化为数独结果
            printf("              HaniDoku:\n");
            showHanidoku(HaniDoku); // 打印蜂巢数独
            getchar();
            getchar();
            break;
        }
        case 8:
        {
            printf("Please input your answer(format: row    col     value) :\n"); // 用户可以验证自己某一格填的对不对
            int row, col, value;
            scanf("%d %d %d", &row, &col, &value);       // 读取数据
            int result = ask(HaniDoku, row, col, value); // 返回结果
            if (result == TRUE)
            {
                printf("Your answer is correct!\n");
            }
            else // 返回答案
            {
                printf("Your answer is incorrect!\n");
                printf("The correct answer for row %d col %d is : %d\n", row, col, HaniDoku[row][col]);
            }
            getchar();
            getchar();
            break;
        }
        case 0:
        {
            break;
        }
        }
    }
    printf("See you next time!\n");
    return 0;
}