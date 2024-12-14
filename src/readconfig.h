#ifndef READCONFIG_H
#define READCONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
// item数组的大小，也是配置文件中有效的item项目的最大值
#define false 0
#define true 1
#define CONFIGSTRUCTSIZE 80
#define CONFIGNAMESIZE 32
#define CONFIGCONTENTSIZE 512

void Rtrim(char* sstring);
void Ltrim(char* sstring);

//比较str1和str2两个字符串内容是否一样，忽略大小写的比较
int StrcaseCmp(const char* str1, const char* str2);
//把str全都变成大写
void StringCase(char* str);

struct ConfigStruct{
    char ItemName[CONFIGNAMESIZE];
    char ItemContent[CONFIGCONTENTSIZE];
};

// 加载配置文件
int LoadConfigFile(const char* pconfName);
// 通过item名字获取item的内容
const char* GetConfigFromString(const char* p_itemname);
// 通过item名字获取item内容，整型，获取不到返回默认值
int GetConfigIntDefault(const char* p_itemname, const int def);

// // 释放内存
// void FreeConfigItem();
// 写配置文件
// 通过item名字修改item内容
int ModifyConfigItemContent(const char* p_itemName, const char* p_itemContent);
// 通过item名字和内容 添加新的item项目
int AddConfigItem(const char*p_itemName, const char* p_itemContent);
// 把加载进来的、或者有修改过了、增加过的 item数组写到指定的文件
int WriteNewConfigFile(const char*pconfName);

#endif /* READCONFIG_H */
