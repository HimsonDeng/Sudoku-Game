#include "def.h"
int boolnum = 0, clsnum = 0;                        // 变元个数，子句个数
char filename[MaxLength];                           // 文件名数组
status createClause(ClsLists &cnf, char FileName[]) // 生成子句
{
    char c;
    FILE *fp;
    fp = fopen(FileName, "r"); // 打开文件

    if (fp)
    {
        while ((c = getc(fp)) == 'c') // 过滤前面多余的文字
        {
            while ((c = getc(fp)) != '\n')
                ;
        }
        // 过滤掉cnf
        for (int i = 1; i <= 4; i++) // 过滤前面多余的文字
        {
            c = getc(fp);
        }
        fscanf(fp, "%d", &boolnum);
        fscanf(fp, "%d", &clsnum);
        // 初始化链表
        cnf = (ClsLists)malloc(sizeof(ClsList));
        cnf->phead = (ClsNodes)malloc(sizeof(ClsNode));
        cnf->phead->words = 0;
        cnf->phead->pnext = NULL;
        cnf->pnext = NULL;
        // 初始化链表
        ClsLists cnf_temp = cnf;
        ClsNodes phead_temp = cnf->phead;
        ClsNodes pre;
        ElemType number;
        for (int i = 1; i <= clsnum; i++) // 读取子句
        {
            while (fscanf(fp, "%d", &number)) // 读取每一个数字
            {
                if (number == 0)
                {
                    pre->pnext = NULL;
                    free(phead_temp);
                    phead_temp = NULL;
                    break;
                }
                // 新建一个空间保存
                phead_temp->words = number;
                phead_temp->pnext = (ClsNodes)malloc(sizeof(ClsNode));
                pre = phead_temp;
                phead_temp = phead_temp->pnext;
            }
            if (i == clsnum) // 如果是最后一个子句的话
            {
                cnf_temp->pnext = NULL;
                break;
            }
            // 读取下个单词
            cnf_temp->pnext = (ClsLists)malloc(sizeof(ClsList));
            cnf_temp->pnext->phead = (ClsNodes)malloc(sizeof(ClsNode));
            cnf_temp = cnf_temp->pnext;
            phead_temp = cnf_temp->phead;
        }
        // #test printf("hello\n");
        fclose(fp); // 关闭文件
        return OK;
    }
    else
    {
        printf("The File cannot open!\n");
        return ERROR;
    }
}

status destroyClause(ClsLists &cnf) // 销毁子句
{
    // 初始化
    ClsLists p = cnf, ptemp = NULL;
    ClsNodes q = NULL, qtemp = NULL;
    for (; p != NULL; p = ptemp)
    {
        q = p->phead;
        ptemp = p->pnext; // 先存下一个
        for (; q != NULL; q = qtemp)
        {
            qtemp = q->pnext;
            free(q); // 释放空间
        }
        free(p); // 释放空间
    }
    cnf = NULL;
    return OK;
}

status addClause(ClsLists cnf, ClsLists &cnf_first) // 在链表中添加指定的子句
{
    if (cnf != NULL)
    {
        cnf->pnext = cnf_first; // 采用头插法，节省插入时间
        cnf_first = cnf;
        return OK;
    }
    else
    {
        return ERROR;
    }
}

status removeNode(ClsNodes &cnf, ClsNodes &_head) // 在指定的子句中删除指定的文字
{
    ClsNodes temp = _head;
    if (cnf == _head) // 如果删除的是子句中的第一个文字
    {
        _head = _head->pnext;
        free(cnf);
    }
    else // 其他
    {
        while (temp != NULL && temp->pnext != cnf) // 一直往下找
        {
            temp = temp->pnext;
        }
        temp->pnext = temp->pnext->pnext;
        free(cnf); // 释放空间
    }
    cnf = NULL;
    return OK;
}

status removeClause(ClsLists &cnf_del, ClsLists &cnf_first) // 在链表中删除指定的子句
{
    ClsLists temp = cnf_first;
    if (cnf_del == cnf_first) // 如果删除的是第一个子句
    {
        cnf_first = cnf_first->pnext; // 替换
        ClsNodes temp3 = NULL;
        for (ClsNodes temp2 = cnf_del->phead; temp2 != NULL; temp2 = temp3) // 删除文字
        {
            temp3 = temp2->pnext;
            free(temp2);
        }
    }
    else
    {
        while (temp != NULL && temp->pnext != cnf_del) // 在链表中找到子句
        {
            temp = temp->pnext;
        }
        temp->pnext = temp->pnext->pnext; // 从字句集中删除该子句
        ClsNodes temp3 = NULL;
        for (ClsNodes temp2 = cnf_del->phead; temp2 != NULL; temp2 = temp3)
        {
            temp3 = temp2->pnext;
            free(temp2);
        }
    }
    free(cnf_del); // 释放空间
    cnf_del = NULL;
    return OK;
}

status isUnitClause(ClsNodes cnf) // 判断给定句子是否为单子句
{
    if (cnf != NULL)
    {
        if (cnf->pnext == NULL)
        {
            return TRUE;
        }
    }
    return FALSE;
}

status isEmptyClause(ClsLists cnf) // 判断是否含有空子句
{
    ClsLists temp = cnf;
    while (temp != NULL)
    {
        if (temp->phead == NULL)
            return TRUE; // 有空句
        temp = temp->pnext;
    }
    return FALSE; // 整个子句集无空句
}

status evaluateClause(ClsNodes cnf, int visit[]) // 评估子句的真假
{
    ClsNodes temp = cnf;
    while (temp != NULL) // 在当前子句中读取整个子句的单词
    {
        int num = temp->words;
        if ((num > 0 && visit[num] == 1) || (num < 0 && visit[-num] == 0)) // 有一个为真，返回真
        {
            return TRUE;
        }
        temp = temp->pnext;
    }
    return FALSE; // 否则，返回假
}

status copyClause(ClsLists &cpy, ClsLists &ori) // ori:来源  cpy:复制到
{
    ClsLists p1, p2;
    ClsNodes q1, q2;
    cpy = (ClsLists)malloc(sizeof(ClsList)); // 初始化
    cpy->pnext = NULL;
    cpy->phead = (ClsNodes)malloc(sizeof(ClsNode));
    cpy->phead->pnext = NULL;
    p1 = cpy;
    p2 = ori;
    // 开始逐个句子复制
    while (p2 != NULL)
    {
        // 双指针
        q1 = p1->phead;
        q2 = p2->phead;
        while (q2 != NULL)
        {
            q1->words = q2->words;
            q2 = q2->pnext;
            if (q2 == NULL)
            {
                q1->pnext = NULL;
            }
            else // 复制子句
            {
                q1->pnext = (ClsNodes)malloc(sizeof(ClsNode));
                q1 = q1->pnext;
                q1->pnext = NULL;
            }
        }
        p2 = p2->pnext;
        if (p2 == NULL)
        {
            p1->pnext = NULL;
        }
        else // 复制子句
        {
            p1->pnext = (ClsLists)malloc(sizeof(ClsList));
            p1 = p1->pnext;
            p1->pnext = NULL;
            p1->phead = (ClsNodes)malloc(sizeof(ClsNode));
            p1->phead->pnext = NULL;
        }
    }
    return OK;
}

status DPLL(ClsLists &cnf, int val[]) // 主要的函数
{
    ClsLists p1, p2, p3;
    ClsNodes q1;
    int *count = (int *)malloc((boolnum * 2 + 1) * sizeof(ElemType));
    int ans;
    // 不断找出子句集中的单子句
    p1 = cnf;
    while (p1 != NULL) // 有单子句
    {
        while (p1 != NULL && isUnitClause(p1->phead) == FALSE)
            p1 = p1->pnext;
        if (p1 == NULL)
            break;
        else
        {
            ans = p1->phead->words;
            if (ans > 0)
            {
                val[ans] = TRUE;
            }
            else
            {
                val[-ans] = FALSE;
            }
            for (p2 = cnf; p2 != NULL; p2 = p3) // 在子句集中查找所有包含这个文字的句子
            {
                p3 = p2->pnext; // 存下一个句子
                q1 = p2->phead;
                // 单子句规则
                for (; q1 != NULL; q1 = q1->pnext)
                {
                    if (q1->words == ans) // S中删除所有包含L的子句，得到子句集S1
                    {
                        removeClause(p2, cnf);
                        break;
                    }
                    if (q1->words == -ans) // 从该子句中去掉这个文字
                    {
                        removeNode(q1, p2->phead);
                        break;
                    }
                }
            }
            // 检查
            if (cnf == NULL) // 如果子句集空了，说明满足
            {
                free(count);
                return TRUE;
            }
            else if (isEmptyClause(cnf) == TRUE) // 如果有空子句，说明不满足
            {
                free(count);
                destroyClause(cnf);
                return FALSE;
            }
        }
        p1 = cnf; // 继续找
    }
    // 改动
    for (int i = 0; i <= 2 * boolnum; i++)
    {
        count[i] = 0;
    }
    // 统计文字出现次数，用这个作为选取变元策略
    p2 = cnf;
    for (; p2 != NULL; p2 = p2->pnext)
    {
        q1 = p2->phead;
        for (; q1 != NULL; q1 = q1->pnext)
        {
            if (q1->words > 0)
            {
                count[q1->words] = count[q1->words] + 1;
            }
            else
            {
                count[boolnum - q1->words] = count[boolnum - q1->words] + 1;
            }
        }
    }
    int maxi = 0, pos = 0;
    // 正文字

    // for (int i = 1; i <= boolnum; i++)
    //  printf("%d:%d\n", i, count[i]);

    /*for (int i = boolnum + 1; i <= 2 * boolnum; i++)
    {
        printf("%d:%d\n", i, count[i]);
    }*/

    for (int i = 1; i <= boolnum; i++)
    {
        if (count[i] > maxi)
        {
            maxi = count[i];
            pos = i;
        }
    }
    if (maxi == 0) // 没有出现正文字
    {
        for (int i = boolnum + 1; i <= 2 * boolnum; i++)
        {
            if (count[i] > maxi)
            {
                maxi = count[i];
                pos = boolnum - i;
                // if(pos==-1451)
                // printf("%d\n ", i);
            }
        }
    }
    // printf("%d\n", pos);
    free(count); // 释放空间
    // 假设该变元是真，先搜索第一分支
    p2 = (ClsLists)malloc(sizeof(ClsList));
    p2->pnext = NULL;
    p2->phead = (ClsNodes)malloc(sizeof(ClsNode));
    p2->phead->pnext = NULL;
    p2->phead->words = pos;
    copyClause(p1, cnf);
    addClause(p2, p1);
    if (DPLL(p1, val) == TRUE) // 在第一分支中搜索
    {
        return TRUE;
    }
    // 回溯
    destroyClause(p1);
    // 该变元为假，搜索第二分支
    p2 = (ClsLists)malloc(sizeof(ClsList));
    p2->pnext = NULL;
    p2->phead = (ClsNodes)malloc(sizeof(ClsNode));
    p2->phead->pnext = NULL;
    p2->phead->words = -pos;
    addClause(p2, cnf);
    ans = DPLL(cnf, val); // 在另一分支中搜索
    destroyClause(cnf);
    return ans;
}

status SaveResult(double time, int ans, int val[]) // 保存结果
{
    FILE *fp;
    int i = 0;
    // 把后缀改一下
    while (filename[i] != '.' && filename[i + 4] != '\0')
    {
        i++;
    }
    filename[i + 1] = 'r';
    filename[i + 2] = 'e';
    filename[i + 3] = 's';
    fp = fopen(filename, "w");
    if (fp)
    {
        fprintf(fp, "s %d\n", ans); // 保存答案
        if (ans == TRUE)
        {
            fprintf(fp, "v ");
            for (int i = 1; i <= boolnum; i++) // 逐个保存
            {
                if (val[i] == TRUE)
                {
                    fprintf(fp, "%d ", i);
                }
                else
                {
                    fprintf(fp, "%d ", -i);
                }
            }
            fprintf(fp, "\n");
        }
        fprintf(fp, "t %lf", time * 1000); // 保存时间
        fclose(fp);
        return OK;
    }
    else
    {
        printf("The File cannot open!\n");
        return ERROR;
    }
}

status DPLL_prev(ClsLists &cnf, int val[]) // 优化前
{
    ClsLists p1, p2, p3;
    ClsNodes q1;
    int *count = (int *)malloc((boolnum * 2 + 1) * sizeof(ElemType));
    int ans;
    // 不断找出子句集中的单子句
    p1 = cnf;
    while (p1 != NULL) // 有单子句
    {
        while (p1 != NULL && isUnitClause(p1->phead) == FALSE)
            p1 = p1->pnext;
        if (p1 == NULL)
            break;
        else
        {
            ans = p1->phead->words;
            if (ans > 0)
            {
                val[ans] = TRUE;
            }
            else
            {
                val[-ans] = FALSE;
            }
            for (p2 = cnf; p2 != NULL; p2 = p3) // 在子句集中查找所有包含这个文字的句子
            {
                p3 = p2->pnext; // 存下一个句子
                q1 = p2->phead;
                // 单子句规则
                for (; q1 != NULL; q1 = q1->pnext)
                {
                    if (q1->words == ans) // S中删除所有包含L的子句，得到子句集S1
                    {
                        removeClause(p2, cnf);
                        break;
                    }
                    if (q1->words == -ans) // 从该子句中去掉这个文字
                    {
                        removeNode(q1, p2->phead);
                        break;
                    }
                }
            }
            // 检查
            if (cnf == NULL) // 如果子句集空了，说明满足
            {
                free(count);
                return TRUE;
            }
            else if (isEmptyClause(cnf) == TRUE) // 如果有空子句，说明不满足
            {
                free(count);
                destroyClause(cnf);
                return FALSE;
            }
        }
        p1 = cnf; // 继续找
    }
    // 改动！！！！！！！！！
    for (int i = 0; i <= 2 * boolnum; i++)
    {
        count[i] = 0;
    }
    // 统计文字出现次数，用这个作为选取变元策略
    p2 = cnf;
    for (; p2 != NULL; p2 = p2->pnext)
    {
        q1 = p2->phead;
        for (; q1 != NULL; q1 = q1->pnext)
        {
            if (q1->words > 0)
            {
                count[q1->words] = count[q1->words] + 1;
            }
            else
            {
                count[boolnum - q1->words] = count[boolnum - q1->words] + 1;
            }
        }
    }
    int maxi = 0, pos = 0;
    // 正文字

    // for (int i = 1; i <= boolnum; i++)
    //  printf("%d:%d\n", i, count[i]);

    /*for (int i = boolnum + 1; i <= 2 * boolnum; i++)
    {
        printf("%d:%d\n", i, count[i]);
    }*/

    for (int i = 1; i <= 2 * boolnum; i++)
    {
        if (count[i] > maxi)
        {
            maxi = count[i];
            pos = i;
        }
    }
    if (pos > boolnum)
    {
        pos = boolnum - pos;
    }
    free(count); // 释放空间
    // 假设该变元是真，先搜索第一分支
    p2 = (ClsLists)malloc(sizeof(ClsList));
    p2->pnext = NULL;
    p2->phead = (ClsNodes)malloc(sizeof(ClsNode));
    p2->phead->pnext = NULL;
    p2->phead->words = pos;
    copyClause(p1, cnf);
    addClause(p2, p1);
    if (DPLL(p1, val) == TRUE) // 在第一分支中搜索
    {
        return TRUE;
    }
    // 回溯
    destroyClause(p1);
    // 该变元为假，搜索第二分支
    p2 = (ClsLists)malloc(sizeof(ClsList));
    p2->pnext = NULL;
    p2->phead = (ClsNodes)malloc(sizeof(ClsNode));
    p2->phead->pnext = NULL;
    p2->phead->words = -pos;
    addClause(p2, cnf);
    ans = DPLL(cnf, val); // 在另一分支中搜索
    destroyClause(cnf);
    return ans;
}

status DPLL_prev2(ClsLists &cnf, int val[]) // 优化前_2
{
    ClsLists p1, p2, p3;
    ClsNodes q1;
    // int count = (int *)malloc((boolnum * 2 + 1) * sizeof(ElemType));
    int ans;
    // 不断找出子句集中的单子句
    p1 = cnf;
    while (p1 != NULL) // 有单子句
    {
        while (p1 != NULL && isUnitClause(p1->phead) == FALSE)
            p1 = p1->pnext;
        if (p1 == NULL)
            break;
        else
        {
            ans = p1->phead->words;
            if (ans > 0)
            {
                val[ans] = TRUE;
            }
            else
            {
                val[-ans] = FALSE;
            }
            for (p2 = cnf; p2 != NULL; p2 = p3) // 在子句集中查找所有包含这个文字的句子
            {
                p3 = p2->pnext; // 存下一个句子
                q1 = p2->phead;
                // 单子句规则
                for (; q1 != NULL; q1 = q1->pnext)
                {
                    if (q1->words == ans) // S中删除所有包含L的子句，得到子句集S1
                    {
                        removeClause(p2, cnf);
                        break;
                    }
                    if (q1->words == -ans) // 从该子句中去掉这个文字
                    {
                        removeNode(q1, p2->phead);
                        break;
                    }
                }
            }
            // 检查
            if (cnf == NULL) // 如果子句集空了，说明满足
            {
                // free(count);
                return TRUE;
            }
            else if (isEmptyClause(cnf) == TRUE) // 如果有空子句，说明不满足
            {
                // free(count);
                destroyClause(cnf);
                return FALSE;
            }
        }
        p1 = cnf; // 继续找
    }
    // 改动！！！！！！！！！
    int maxi = 0, pos = 0;
    // 正文字

    // for (int i = 1; i <= boolnum; i++)
    //  printf("%d:%d\n", i, count[i]);

    /*for (int i = boolnum + 1; i <= 2 * boolnum; i++)
    {
        printf("%d:%d\n", i, count[i]);
    }*/
    if (cnf != NULL)
    {
        p1 = cnf;
        while (p1->pnext != NULL)
            p1 = p1->pnext;
        pos = p1->phead->words;
    }
    //  free(count);
    //  假设该变元是真，先搜索第一分支
    p2 = (ClsLists)malloc(sizeof(ClsList));
    p2->pnext = NULL;
    p2->phead = (ClsNodes)malloc(sizeof(ClsNode));
    p2->phead->pnext = NULL;
    p2->phead->words = pos;
    copyClause(p1, cnf);
    addClause(p2, p1);
    if (DPLL(p1, val) == TRUE) // 在第一分支中搜索
    {
        return TRUE;
    }
    // 回溯
    destroyClause(p1);
    // 该变元为假，搜索第二分支
    p2 = (ClsLists)malloc(sizeof(ClsList));
    p2->pnext = NULL;
    p2->phead = (ClsNodes)malloc(sizeof(ClsNode));
    p2->phead->pnext = NULL;
    p2->phead->words = -pos;
    addClause(p2, cnf);
    ans = DPLL(cnf, val); // 在另一分支中搜索
    destroyClause(cnf);
    return ans;
}