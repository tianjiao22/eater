#include "modules/arg_parser.h"

int arg_parse(int argc, const char **argv)
{
	// TODO
    if (argv == NULL) {
        return 1; //若addr为空
    }

    int len = strlen(*argv1);
    char IP1[50][10],cIP[4];
    int i = 0,j=len-1;
    int k, m = 0,n=0,num=0;

    printf("len%d:\n",len);
    for (i; i <len-1; i++)
    {

	if (strcmp(*(argv1 + i) ,"--ip") == 0)
	{
		//printf("argv1:%s\n",*(argv1 + i+1));
		strcpy((char*)IP1 , *(argv1 + i+1))
	}

    }
    int IPlen = strlen(*IP1);
    for(int c=0;c<IPlen;c++){
       // printf("IP1%d:%c\n",c,IP1[0][c]);
    }
    char *p = (char *)IP1;

    while (*p!= '\0')
    {
        if (*p == ' ' || *p<'0' || *p>'9') {
            return 1;
        }
        cIP[n++] = *p; //保存每个子段的第一个字符，用于之后判断该子段是否为0开头
        int sum = 0;  //sum为每一子段的数值，应在0到255之间
        while (*p != '.'&&*p != '\0')
        {
          if (*p == ' ' || *p<'0' || *p>'9') {
              return 1;
          }
          sum = sum * 10 + *p-48;  //每一子段字符串转化为整数
          p++;
        }
        if (*p == '.') {
	/*判断"."前后是否有数字，若无，则为无效IP，如“1.1.127.”  */
            if ((*(p - 1) >= '0'&&*(p - 1) <= '9') && (*(p + 1) >= '0'&&*(p + 1) <= '9')) {
                num++;  //记录“.”出现的次数，不能大于3
            }
            else {
                return 1;
            }
        };
        /* 若子段的值>255或为0开头的非0子段或“.”的数目>3，则为无效IP  */
        if ((sum > 255) || (sum > 0 && cIP[0] =='0')||num>3) {
            return -1;
        }

        if (*p != '\0') {
            p++;
        }
        n = 0;
    }
    if (num != 3) {
        return 1;
   }
	return 0;
}


int get_ip(uint32_t &addr)
{
	// TODO
	return 0;
}

int get_port(uint32_t &port)
{
	// TODO
	return 0;
}
