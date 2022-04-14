#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

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
    unsigned char name[30];
} school;

typedef struct athlete
{
    int id;
    int school;
    int event;
    int score;
    int sex;
    unsigned char name[30];
} athlete;

typedef struct event
{
    int id;
    unsigned char name[30];
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

void showSubMenu(int sel)
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
        printf("          2. 录入运动员\n");
        printf("          3. 录入比赛成绩\n");
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
        else if (a == 3)
        {
            printf("sel3");
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
void showMenu()
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
        showSubMenu(a);
    }
}

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

status insertElem(int type, ...)
{
    va_list argvList;
    va_start(argvList, type);
    switch (type)
    {
    case 1:
    {
        schoolList *schools = va_arg(argvList, schoolList *);
        if (schools->size == schools->length && extendList(1, schools) == false)
        {
            return false;
        }
        schools->base[schools->size++] = va_arg(argvList, school);
        break;
    }
    case 2:
    {
        athleteList *athletes = va_arg(argvList, athleteList *);
        if (athletes->size == athletes->length && extendList(2, athletes) == false)
        {
            return false;
        }
        athletes->base[athletes->size++] = va_arg(argvList, athlete);
        break;
    }
    case 3:
    {
        eventList *events = va_arg(argvList, eventList *);
        if (events->size == events->length && extendList(3, events) == false)
        {
            return false;
        }
        events->base[events->size++] = va_arg(argvList, event);
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

int main()
{
    schoolList schools;
    athleteList athletes;
    eventList events;

    if (systemInit(&schools, &athletes, &events))
    {
        showMenu();
    }
    else
    {
        printf("系统初始化失败！\n");
    }
    systemFree(&schools, &athletes, &events);
    return 0;
}