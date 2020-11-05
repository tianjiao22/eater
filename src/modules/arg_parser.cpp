#include "modules/arg_parser.h"
#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#define MAX_IP 15;
char *paddr = NULL;
int Ipflag =0,Portflag =0;

unsigned portnum=0;
int arg_parse(int argc, const char **argv)
{
	// TODO
    if (argv == NULL) {
        return 1; //若addr为空
    }

    int len =argc;
    int i = 0;

    //printf("len:%d\n",len);
    if (len <2) {
        return 1;
    }
    for (i; i <len ; i++) {
	if (  strcmp(*(argv + i) ,"--ip") == 0) {
		//printf("argv:%si=%d\n",*(argv + i+1),i);
                int  iplen = strlen(argv [i+1]);
                if (iplen>15) {
                    iplen = 15;
                }

                paddr = new char[iplen+1];
                //printf("iplen:%d\n",iplen);
		memcpy( ( char*)paddr , *(argv + i+1),iplen);
                paddr[iplen]= '\0';
                Ipflag = 1;
	}
       if ( (strcmp(*(argv + i) ,"--port") == 0)  && (i +1 <len)){
            //printf("Port:%s\n",*(argv + i+1));
                int  portlen = strlen(argv [i+1]);
                char Port[portlen] = {"0"};
                portnum = atoi(argv [i+1]);
                Portflag = 1;
        }
    }
    if (!Ipflag) {
        return 1;
    }

	return 0;
}


int get_ip(uint32_t &addr) {
	// TODO
   int n=0,num=0,i=0;
   char cIP[4];
   int sumbuf[20] = {0};
   uint32_t ip;
    if (!paddr) {
         goto ERR;
    }

    while (*paddr!= '\0') {
        if (*paddr == ' ' || *paddr<'0' || *paddr>'9') {
             goto ERR;
        }
        cIP[n++] = *paddr; //保存每个子段的第一个字符，用于之后判断该子段是否为0开头
        int sum = 0;  //sum为每一子段的数值，应在0到255之间

        while (*paddr != '.'&&*paddr != '\0')
        {
          if (*paddr== ' ' || *paddr<'0' || *paddr>'9') {
               goto ERR;
          }
          sum = sum * 10 + *paddr-48;  //每一子段字符串转化为整数
          paddr++;
        }
        if (*paddr == '.') {
	/*判断"."前后是否有数字，若无，则为无效IP，如“1.1.127.”  */
            if ((*(paddr - 1) >= '0'&&*(paddr - 1) <= '9') && (*(paddr + 1) >= '0'&&*(paddr + 1) <= '9')) {
                num++;  //记录“.”出现的次数，不能大于3
            }
            else {
               goto ERR;

            }
        }
        /* 若子段的值>255或为0开头的非0子段或“.”的数目>3，则为无效IP  */
        if ((sum > 255) || (sum > 0 && cIP[0] =='0')||num>3) {
             goto ERR;
        }

        if (*paddr != '\0') {
            paddr++;
        }
        n = 0;
       sumbuf[i] = sum ;
       i++;
    }
    if (num != 3) {
        return 1;
    }
        addr = ( sumbuf[0]  << 24)+ ( sumbuf[1]  << 16) + ( sumbuf[2]  << 8) +  ( sumbuf[3]  << 0);
        paddr = NULL;
        delete  paddr;
	return 0;
    ERR:{
        paddr = NULL;
        delete  paddr;
        return 1;
    }
}

int get_port(uint32_t &port)
{
	// TODO
        int sum =0;
        if ( Portflag== 0 ) {
            //printf("potr null\n");
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
