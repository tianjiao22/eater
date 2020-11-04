#include "modules/arg_parser.h"
#include<stdio.h>
#include <string.h>
#include<stdlib.h>
char *paddr = nullptr;
char *pPort = nullptr;
 int Ipflag =0,Portflag =0;
int portnum = 0;
int arg_parse(int argc, const char **argv)
{
	// TODO
    if (argv == NULL) {
        return 1; //若addr为空
    }

    int len =argc;
    char IP1[50][10] ;
    char Port[20][10]  ;
    int i = 0;

    printf("len%d:\n",len);
    if (len <2) {
        return 1;
    }
    for (i; i <len ; i++)
    {
	if ( strcmp(*(argv + i) ,"--ip") == 0) {
		//printf("argv:%s\n",*(argv1 + i+1));
		strcpy( ( char*)IP1 , *(argv + i+1));
                Ipflag = 1;
	}
        if (strcmp(*(argv + i) ,"--port") == 0) {
           // printf("Port:%s\n",*(argv1 + i+1));
		strcpy((char*)Port , *(argv + i+1));
                Portflag = 1;
                portnum = atoi(*Port);
        }

    }

    if (!IP1 ) {
        return 1;
    }

    paddr = (char *)*IP1;
    pPort = (char *)*Port;
    return 0;
}


int get_ip(uint32_t &addr) {
	// TODO
   int n=0,num=0,i=0;
   char *p = paddr;
   char cIP[4];
   int sumbuf[20] = {0};
   uint32_t ip;
    if (!paddr) {
        return 1;
    }
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
            return 1;
        }

        if (*p != '\0') {
            p++;
        }
        n = 0;
       sumbuf[i] = sum;
       i++;
       // printf ("sum:%d\n",sum);
    }
    if (num != 3) {
        return 1;
    }
    addr = ( sumbuf[0]  << 24)+ ( sumbuf[1]  << 16) + ( sumbuf[2]  << 8) +  ( sumbuf[3]  << 0);
        //addr =  (uint32_t)*paddr (s1 << 24) + (s2 << 8) + (s3 << 0);
        //printf("addr:%x\n",addr);
	return 0;
}

int get_port(uint32_t &port)
{
	// TODO
        char *p = pPort;
        int sum =0;
        if ( Portflag== 0 ) {
            printf("potr null");
            return 1;
        }
        if (!portnum){
            return 1;
        }else {
           // sum = atoi(p);
            if ((portnum > 1) && (portnum < 65535)) {
                port =  (uint32_t)portnum;
            }
            else {
               return 1;
            }
        }
       //printf("getport%d : ",portnum);
	return 0;
}
