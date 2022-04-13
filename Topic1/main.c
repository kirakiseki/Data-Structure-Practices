#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef bool status;

const int INIT_LENGTH = 10;
const int INCREMENT = 5;

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

school *schools;
athlete *athletes;
event *events;
int schoolsCount, athletesCount, eventsCount, schoolsLength, athletesLength, eventsLength;

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
 * @return {status} 操作状态
 */
status systemInit()
{
    schools = (school *)malloc(sizeof(school) * INIT_LENGTH);
    athletes = (athlete *)malloc(sizeof(athlete) * INIT_LENGTH);
    events = (event *)malloc(sizeof(event) * INIT_LENGTH);
    if (schools == NULL || athletes == NULL || events == NULL)
    {
        return false;
    }
    schoolsCount = 0;
    athletesCount = 0;
    eventsCount = 0;
    schoolsLength = INIT_LENGTH;
    athletesLength = INIT_LENGTH;
    eventsLength = INIT_LENGTH;
    return true;
}

/**
 * @brief 释放数据表空间
 * @return {status} 操作状态
 */
status systemFree()
{
    free(schools);
    free(athletes);
    free(events);
    schoolsCount = 0;
    athletesCount = 0;
    eventsCount = 0;
    schoolsLength = 0;
    athletesLength = 0;
    eventsLength = 0;
    return true;
}

/**
 * @brief 增加表长
 * @param {void *} 表基址
 * @param {int} 表元素类型(1-school, 2-athlete, 3-event)
 * @param {int} 表长度
 * @return {status} 操作状态
 */
status extendList(void *ptr, int type, int *length)
{
    int size;
    void *newPtr;
    switch (type)
    {
    case 1:
    { /* school type */
        newPtr = (school *)realloc(ptr, sizeof(school) * (*length + INCREMENT));
        break;
    }
    case 2:
    { /* athlete type */
        newPtr = (athlete *)realloc(ptr, sizeof(athlete) * (*length + INCREMENT));
        break;
    }
    case 3:
    { /* event type */
        newPtr = (event *)realloc(ptr, sizeof(event) * (*length + INCREMENT));
        break;
    }
    }
    if (newPtr == NULL)
    {
        return false;
    }
    *length += INCREMENT;
    ptr = newPtr;
    return true;
}

int main()
{
    return 0;
}