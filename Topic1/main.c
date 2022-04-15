#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#define NAME_LENGTH 30

typedef bool status;

const int INIT_LENGTH = 3;
const int INCREMENT = 2;

typedef struct school
{
    int id;
    int *athletes;
    int athletesCount;
    int totalScore;
    int manScore;
    int womanScore;
    unsigned char name[NAME_LENGTH];
} school;

typedef struct athlete
{
    int id;
    int school;
    int event;
    int score;
    int sex;
    unsigned char name[NAME_LENGTH];
} athlete;

typedef struct event
{
    int id;
    unsigned char name[NAME_LENGTH];
    int *athletes;
    int athletesCount;
    int mode;
} event;

typedef struct schoolList
{
    school *base;
    int length;
    int size;
} schoolList;

typedef struct athleteList
{
    athlete *base;
    int length;
    int size;
} athleteList;

typedef struct eventList
{
    event *base;
    int length;
    int size;
} eventList;

/**
 * @brief 系统数据表初始化
 * @param {schoolList} schools
 * @param {athleteList} athletes
 * @param {eventList} events
 * @return {status} 操作状态
 */
status systemInit(schoolList *schools, athleteList *athletes, eventList *events)
{
    schools->base = (school *)malloc(sizeof(school) * INIT_LENGTH);
    athletes->base = (athlete *)malloc(sizeof(athlete) * INIT_LENGTH);
    events->base = (event *)malloc(sizeof(event) * INIT_LENGTH);
    if (schools->base == NULL || athletes->base == NULL || events->base == NULL)
    {
        return false;
    }
    schools->length = INIT_LENGTH;
    athletes->length = INIT_LENGTH;
    events->length = INIT_LENGTH;
    schools->size = 0;
    athletes->size = 0;
    events->size = 0;
    return true;
}

/**
 * @brief 释放数据表空间
 * @return {status} 操作状态
 */
status systemFree(schoolList *schools, athleteList *athletes, eventList *events)
{
    free(schools->base);
    free(athletes->base);
    free(events->base);
    schools->base = NULL;
    athletes->base = NULL;
    events->base = NULL;
    schools->length = 0;
    athletes->length = 0;
    events->length = 0;
    schools->size = 0;
    athletes->size = 0;
    events->size = 0;
    return true;
}

/**
 * @brief 增加表长
 * @param {int} 表类型(1-schoolList, 2-athleteList, 3-eventList)
 * @return {status} 操作状态
 */
status extendList(int type, ...)
{
    va_list argvList;
    va_start(argvList, type);
    switch (type)
    {
    case 1:
    {
        schoolList *schools = va_arg(argvList, schoolList *);
        schools->base = (school *)realloc(schools->base, sizeof(school) * (schools->length + INCREMENT));
        if (schools->base == NULL)
        {
            return false;
        }
        schools->length += INCREMENT;
        break;
    }
    case 2:
    {
        athleteList *athletes = va_arg(argvList, athleteList *);
        athletes->base = (athlete *)realloc(athletes->base, sizeof(athlete) * (athletes->length + INCREMENT));
        if (athletes->base == NULL)
        {
            return false;
        }
        athletes->length += INCREMENT;
        break;
    }
    case 3:
    {
        eventList *events = va_arg(argvList, eventList *);
        events->base = (event *)realloc(events->base, sizeof(event) * (events->length + INCREMENT));
        if (events->base == NULL)
        {
            return false;
        }
        events->length += INCREMENT;
        break;
    }
    default:
        return false;
    }
    return true;
}

status insertElem(int type, int nth, ...)
{
    va_list argvList;
    va_start(argvList, nth);
    switch (type)
    {
    case 1:
    {
        schoolList *schools = va_arg(argvList, schoolList *);
        if (nth < 1 || nth > schools->size + 1)
        {
            return false;
        }
        if (schools->size >= schools->length && extendList(1, schools) == false)
        {
            return false;
        }
        for (int i = schools->size - 1; i >= nth - 1; i--)
        {
            schools->base[i + 1] = schools->base[i];
        }
        schools->base[nth - 1] = va_arg(argvList, school);
        schools->size++;
        break;
    }
    case 2:
    {
        athleteList *athletes = va_arg(argvList, athleteList *);
        if (nth < 1 || nth > athletes->size + 1)
        {
            return false;
        }
        if (athletes->size >= athletes->length && extendList(2, athletes) == false)
        {
            return false;
        }
        for (int i = athletes->size - 1; i >= nth - 1; i--)
        {
            athletes->base[i + 1] = athletes->base[i];
        }
        athletes->base[nth - 1] = va_arg(argvList, athlete);
        athletes->size++;
        break;
    }
    case 3:
    {
        eventList *events = va_arg(argvList, eventList *);
        if (nth < 1 || nth > events->size + 1)
        {
            return false;
        }
        if (events->size >= events->length && extendList(3, events) == false)
        {
            return false;
        }
        for (int i = events->size - 1; i >= nth - 1; i--)
        {
            events->base[i + 1] = events->base[i];
        }
        events->base[nth - 1] = va_arg(argvList, event);
        events->size++;
        break;
    }
    default:
        return false;
    }
    return true;
}

status deleteElem(int type, int nth, ...)
{
    va_list argvList;
    va_start(argvList, nth);
    switch (type)
    {
    case 1:
    {
        schoolList *schools = va_arg(argvList, schoolList *);
        if (nth > schools->size || nth < 1)
        {
            return false;
        }
        for (int i = nth - 1; i < schools->size - 1; i++)
        {
            schools->base[i] = schools->base[i + 1];
        }
        schools->size--;
        break;
    }
    case 2:
    {
        athleteList *athletes = va_arg(argvList, athleteList *);
        if (nth > athletes->size || nth < 1)
        {
            return false;
        }
        for (int i = nth - 1; i < athletes->size - 1; i++)
        {
            athletes->base[i] = athletes->base[i + 1];
        }
        athletes->size--;
        break;
    }
    case 3:
    {
        eventList *events = va_arg(argvList, eventList *);
        if (nth > events->size || nth < 1)
        {
            return false;
        }
        for (int i = nth - 1; i < events->size - 1; i++)
        {
            events->base[i] = events->base[i + 1];
        }
        events->size--;
        break;
    }
    default:
        return false;
    }
    return true;
}

int compareSchoolById(const void *a, const void *b)

{
    return ((school *)a)->id - ((school *)b)->id;
}

int compareAthleteById(const void *a, const void *b)

{
    return ((athlete *)a)->id - ((athlete *)b)->id;
}

int compareEventById(const void *a, const void *b)

{
    return ((event *)a)->id - ((event *)b)->id;
}

status sortById(int type, ...)
{
    va_list argvList;
    va_start(argvList, type);
    switch (type)
    {
    case 1:
    {
        schoolList *schools = va_arg(argvList, schoolList *);
        qsort(schools->base, schools->size, sizeof(school), compareSchoolById);
        break;
    }
    case 2:
    {
        athleteList *athletes = va_arg(argvList, athleteList *);
        qsort(athletes->base, athletes->size, sizeof(athlete), compareAthleteById);
        break;
    }
    case 3:
    {
        eventList *events = va_arg(argvList, eventList *);
        qsort(events->base, events->size, sizeof(event), compareEventById);
        break;
    }
    default:
        return false;
    }
    return true;
}

/**
 * @brief 清空屏幕
 */
void clearScreen()
{
    printf("\033c");
}

int input()
{
    char input = '\n';
    while (input == '\n')
    {
        fflush(stdin);
        scanf("%c", &input);
    }
    return input - '0';
}

status traverse(int type, ...)
{
    va_list argvList;
    va_start(argvList, type);
    switch (type)
    {
    case 1:
    {
        schoolList *schools = va_arg(argvList, schoolList *);
        for (int i = 0; i < schools->size; i++)
        {
            printf("%d\t%s\n", schools->base[i].id, schools->base[i].name);
        }
        break;
    }
    case 2:
    {
        athleteList *athletes = va_arg(argvList, athleteList *);
        for (int i = 0; i < athletes->size; i++)
        {
            printf("%d\t%s\n", athletes->base[i].id, athletes->base[i].name);
        }
        break;
    }
    case 3:
    {
        eventList *events = va_arg(argvList, eventList *);
        for (int i = 0; i < events->size; i++)
        {
            printf("%d\t%s\n", events->base[i].id, events->base[i].name);
        }
        break;
    }
    default:
        return false;
    }
    return true;
}

int findNthBySchoolId(schoolList schools, int id){
    for (int i = 0; i < schools.size; i++)
    {
        if (schools.base[i].id == id)
        {
            return i+1;
        }
    }
    return -1;
}

status inputSchool(schoolList *schools, int cnt)
{
    printf("请输入学校信息：编号 名称\n");
    school inputSchool={0,NULL,0,0,0,0};
    while (cnt--)
    {
        char name[NAME_LENGTH];
        scanf("%d %s", &inputSchool.id, name);
        strcpy(inputSchool.name, name);
        if (insertElem(1, schools->size + 1, schools, inputSchool) == false)
        {
            printf("输入错误，请重新输入\n");
            cnt++;
        }
    }
}

status deleteSchool(schoolList *schools, int cnt)
{
    printf("请输入待删除学校：编号\n");
    while (cnt--)
    {
        int id;
        scanf("%d", &id);
        if (deleteElem(1, findNthBySchoolId(*schools,id), schools) == false)
        {
            printf("输入错误，请重新输入\n");
            cnt++;
        }
    }
}

void showSubMenu(int sel, schoolList *schools, athleteList *athletes, eventList *events)
{
    int a = 0;
    clearScreen();
    switch (sel)
    {
    case 1:
    {
        printf("============ 信息录入 ============\n");
        printf("\n");
        printf("          1. 录入学校信息\n");
        printf("          2. 录入运动员信息\n");
        printf("          3. 录入比赛项目\n");
        printf("          4. 录入比赛成绩\n");
        printf("\n");
        printf("   按数字键选择功能，任意键返回。  \n");
        a = input();
        if (a == 1)
        {
            clearScreen();
            printf("现有学校: %d 个\n", schools->size);
            if (schools->size == 0)
            {
                printf("没有学校信息，请先录入学校信息。\n");
            }
            else
            {
                printf("学校信息如下：\n");
                traverse(1, schools);
            }
            printf("\n");
            printf("请输入录入学校数目：(正数增加，负数删除,0返回)  ");
            int cnt;
            scanf("%d", &cnt);
            if (cnt == 0)
            {
                return;
            }
            else if (cnt > 0)
            {
                inputSchool(schools, cnt);
            }
            else if (cnt < 0)
            {
                deleteSchool(schools, -cnt);
            }
            printf("\n");
            printf("学校信息如下：\n");
            sortById(1, schools);
            traverse(1, schools);
            printf("\n");
            printf("按q返回。\n");
            char input = 0;
            while (input = getchar(), input != 'q')
            {
                continue;
            }
        }
        else if (a == 2)
        {
            printf("sel2");
        }
        else if (a == 3)
        {
            printf("sel3");
        }
        else if (a == 4)
        {
            printf("sel4");
        }
        break;
    }
    case 2:
    {
        printf("============ 成绩查询 ============\n");
        printf("\n");
        printf("          1. 查询学校信息\n");
        printf("          2. 查询运动员\n");
        printf("          3. 查询比赛信息\n");
        printf("\n");
        printf("   按数字键选择功能，任意键返回。  \n");
        a = input();
        if (a == 1)
        {
            printf("sel1");
        }
        else if (a == 2)
        {
            printf("sel2");
        }
        break;
    }
    default:
        break;
    }
}

/**
 * @brief 显示菜单
 */
void showMenu(schoolList *schools, athleteList *athletes, eventList *events)
{
    while (1)
    {
        clearScreen();
        printf("===== 课题1 - 运动会分数统计 =====\n");
        printf("\n");
        printf("          1. 信息录入\n");
        printf("          2. 成绩查询\n");
        printf("\n");
        printf("   按数字键选择功能，任意键退出。  \n");
        int a = input();
        if (a != 1 && a != 2)
        {
            break;
        }
        fflush(stdin);
        showSubMenu(a, schools, athletes, events);
    }
}

int main()
{
    schoolList schools;
    athleteList athletes;
    eventList events;

    if (systemInit(&schools, &athletes, &events))
    {
        showMenu(&schools, &athletes, &events);
        // school school1;
        // school1.id = 1;
        // strcpy(school1.name, "北京大学");
        // insertElem(1, 1, &schools, school1);
        // school1.id = 7;
        // insertElem(1, 2, &schools, school1);
        // school1.id = 5;
        // insertElem(1, 3, &schools, school1);
        // traverse(1, &schools);
        // printf("\n");
        // deleteElem(1, 2, &schools);
        // deleteElem(1, 1, &schools);
        // traverse(1, &schools);
        
    }
    else
    {
        printf("系统初始化失败！\n");
    }
    systemFree(&schools, &athletes, &events);
    return 0;
}