#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

typedef bool status;

const int INIT_LENGTH = 10;
const int INCREMENT = 2;

typedef struct
{
    int id;
    int *athletes;
    int athletesCount;
    int totalScore;
    int manScore;
    int womanScore;
} school;

typedef struct
{
    int number;
    int school;
    int score;
    int sex;
    unsigned char name[20];
} athlete;

typedef struct
{
    int id;
    unsigned char name[20];
    int *athletes;
    int athletesCount;
    int mode;
} event;

typedef struct
{
    school *base;
    int length;
    int size;
} schoolList;

typedef struct
{
    athlete *base;
    int length;
    int size;
} athleteList;

typedef struct
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

/**
 * @brief 显示菜单
 */
void showMenu()
{
    // TODO
    clearScreen();
    printf("===== 课题1 - 运动会分数统计 =====\n");
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
 * @param {int} 表类型(1-schoolList, 2-athleteList, 3-evenList)
 * @param {int *} 表长度
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



int main()
{
    schoolList schools;
    athleteList athletes;
    eventList events;
    systemInit(&schools, &athletes, &events);
    printf("%d %d %d\n", schools.length, athletes.length, events.length);
    extendList(1, &schools);
    printf("%d %d %d\n", schools.length, athletes.length, events.length);
    systemFree(&schools, &athletes, &events);
    return 0;
}