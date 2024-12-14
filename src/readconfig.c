#include <ctype.h>
#include "readconfig.h"

static int arr_curr_ind = 0;
static struct ConfigStruct ArrayConfig[CONFIGSTRUCTSIZE];

// Rtrim: 去除字符串右侧的空白字符
char *Rtrim_t(char *str) {
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }
    *(end + 1) = '\0';
    return str;
}

// Ltrim: 去除字符串左侧的空白字符
char *Ltrim_t(char *str) {
    char *start = str;
    while (isspace((unsigned char)*start)) {
        start++;
    }
    memmove(str, start, strlen(start) + 1);
    return str;
}
#if 0
static void rtrim(char *sstring)
{
	size_t len = 0;
	if (sstring == NULL)
		return;
	len = strlen(sstring);
	while (len > 0 && sstring[len - 1] == ' ')//位置换一下
		sstring[--len] = 0;
}

//截取字符串首部空格
static void ltrim(char *sstring)
{
	size_t len = 0;
	if (sstring == NULL)
		return;
	char *p_tmp = sstring;  //此时p_tmp指向了sstring
	if ((*p_tmp) != ' ')
		return;  //不是以空格开头

	//找到第一个不为空格的位置
	while ((*p_tmp) != '\0')
	{
		if ((*p_tmp) == ' ')
			p_tmp++;
		else
			break;
	}
	if ((*p_tmp) == '\0') //全是空格
	{
		*sstring = '\0';
		return;
	}
	char *p_tmp2 = sstring;  //此时 p_tmp2 指向了 sstring
	while ((*p_tmp) != '\0')
	{
		(*p_tmp2) = (*p_tmp);
		p_tmp++;
		p_tmp2++;
	}
	(*p_tmp2) = '\0';  //空格处理完毕，记得在末尾添加一个'\0' 表示字符串结尾
	return;
}
#endif
//比较str1和str2两个字符串内容是否一样，忽略大小写的比较
int StrcaseCmp(const char* str1, const char* str2)
{
	if (str1 == NULL || str2 == NULL)
		return false;
	size_t strLen1 = strlen(str1);
	size_t strLen2 = strlen(str2);
	if (strLen1 != strLen2)
		return false;
	// char *str = new char[strLen2]; 
    char *str = (char*)malloc(strLen2);
	strcpy(str, str2); //把str2的内容拷贝到str中
	StringCase(str);  //把str中的所有内容转成大写字母
	while ((*str) != '\0')
	{
		if ((*str1) > 90)
		{
			if (((*str1) - 32) == (*str))
			{
				++str1;
				++str;
			}
			else {
				return false;
			}
		}
		else {
			if ((*str1) == (*str))
			{
				++str1;
				++str;
			}
			else {
				return false;
			}
		}
	}
    free(str);
	return true;
}

//把str中所有的小写字母变成大写
void StringCase(char* str)
{
	if (str == NULL)
		return ;
	if (strlen(str) <= 0)
		return ;
	int strLen = strlen(str);
	char *ptmp = str;
	while ((*ptmp) != '\0')
	{
		if ((97 <= (*ptmp)) && ((*ptmp) <= 122))
		{
			(*ptmp) -= 32;
		}
		++ptmp;
	}
	return;
}

int LoadConfigFile(const char* pconfName)
{
    if(arr_curr_ind > 0){
        return 0;
    }
    FILE *fp;
    fp = fopen(pconfName, "r");
    if(fp == NULL)
        return false;

    // 每一行配置文件读取出来放到这里
    unsigned int linebuf_size = CONFIGCONTENTSIZE + 1 + CONFIGNAMESIZE + 1 + 1;
    char linebuf[linebuf_size];  // 128+1 结尾为结束符
    memset(linebuf, 0, sizeof(linebuf));
    while(!feof(fp))
    {
        if(fgets(linebuf, linebuf_size, fp) == NULL)
            continue;
        if(linebuf[0] == 0)
            continue;
        if(*linebuf == ';' || *linebuf == ' ' || *linebuf == '#' || *linebuf == '\t' || *linebuf == '\n')
            continue;

        // 去除字符串中的 \r \n 以及空格' '
    lblprocstring:
        if(strlen(linebuf) > 0)
        {
            if(linebuf[strlen(linebuf) - 1] == 10 || linebuf[strlen(linebuf) - 1] == 13 || linebuf[strlen(linebuf) - 1] == 32 )
            {
                linebuf[strlen(linebuf) - 1] = 0;
                goto lblprocstring;
            }
        }
        if(linebuf[0] == 0)
            continue;

        if(*linebuf == '[')  // [ 开头的注释，也保存，方便以后写文件时写回去
        {
            if(arr_curr_ind < CONFIGSTRUCTSIZE)
            {
                strcpy(ArrayConfig[arr_curr_ind].ItemName, linebuf);
                strcpy(ArrayConfig[arr_curr_ind].ItemContent, " ");
                // ArrayConfig[arr_curr_ind] = p_configitem;
                arr_curr_ind += 1;
            }
            else
            {
                // ERROR
            }
            continue;
        }

        // 到这里，都是合法的配置项
        char *ptmp = strchr(linebuf, '=');
        if(ptmp != NULL)
        {
            if(arr_curr_ind < CONFIGSTRUCTSIZE)
            {
                strncpy(ArrayConfig[arr_curr_ind].ItemName, linebuf, (int)(ptmp-linebuf));
                strcpy(ArrayConfig[arr_curr_ind].ItemContent, ptmp+1);
                Rtrim_t(ArrayConfig[arr_curr_ind].ItemName);
                Ltrim_t(ArrayConfig[arr_curr_ind].ItemName);
                Rtrim_t(ArrayConfig[arr_curr_ind].ItemContent);
                Ltrim_t(ArrayConfig[arr_curr_ind].ItemContent);
                arr_curr_ind += 1;
            }
            else
            {
                // ERROR
            }
        } // end if
    } // end while
    fclose(fp);
    return 1;
}

const char* GetConfigFromString(const char* p_itemname)
{
    int i = 0;
    for(i = 0; i < arr_curr_ind; i++)
    {
        if(strcmp(p_itemname, ArrayConfig[i].ItemName) == 0)
        {
            return ArrayConfig[i].ItemContent;
        }
    }
    return NULL;
}

int GetConfigIntDefault(const char* p_itemname, const int def)
{
    int i;
    for(i = 0; i < arr_curr_ind; i++)
    {
        if(strcmp(p_itemname, ArrayConfig[i].ItemName) == 0)
        {
            return atoi(ArrayConfig[i].ItemContent);
        }
    }
    return def;
}


int ModifyConfigItemContent(const char* p_itemName, const char* p_itemContent)
{
    if (!p_itemName || !p_itemContent)
        return 0;
    int ret_res = 0;
    int i = 0;
    for(i = 0; i < arr_curr_ind; i++)
    {
        if(strcmp(p_itemName, ArrayConfig[i].ItemName) == 0)
        {
            strcpy(ArrayConfig[i].ItemContent, p_itemContent);
            ret_res = 1;
        }
    }
    return ret_res;
}

int AddConfigItem(const char*p_itemName, const char* p_itemContent)
{
    if (!p_itemName || !p_itemContent)
        return 0;
    int i;
    int ret_res = 0;
    for(i=0; i<arr_curr_ind; ++i)
    {
        ret_res = ModifyConfigItemContent(p_itemName, p_itemContent);
        if(ret_res == 1)
            return ret_res;
    }
    ret_res = 0;
    if(arr_curr_ind < CONFIGSTRUCTSIZE)
    {
        strcpy(ArrayConfig[arr_curr_ind].ItemName, p_itemName);
        strcpy(ArrayConfig[arr_curr_ind].ItemContent, p_itemContent);
        arr_curr_ind += 1;
        ret_res = 1;
    }
    else
    {
        ret_res = 0;
    }
    return ret_res;
}

int WriteNewConfigFile(const char*pconfName)
{
    if(!pconfName)
        return 0;
    int new_fd;
    if(-1 == (new_fd = open(pconfName,O_RDWR|O_CREAT|O_TRUNC,0664)))
    {
        return 0;
    }
    int i = 0;
    char line_buf[32+128+1] = "\0";
    char equal_char = '=';
    for(i=0; i < arr_curr_ind; i++)
    {
        if(*(ArrayConfig[i].ItemName) == '[')
            equal_char = ' ';
        else
            equal_char = '=';
        sprintf(line_buf, "%s%c%s\n", ArrayConfig[i].ItemName, equal_char, ArrayConfig[i].ItemContent);
        write(new_fd, line_buf, strlen(line_buf));
        memset(line_buf, 0, sizeof(line_buf));
    }
    close(new_fd);
    return 1;
}
