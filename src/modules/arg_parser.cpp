#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdint.h>
#include <stdlib.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*x))
#define MAX_IP 16
#define MIN_IP 7
#define MAX_PORT_LEN 5
using namespace std;
char *paddr = NULL;
int ip_flag = 0,port_flag = 0,ip_len = 0;
unsigned port_num = 0;

int arg_parse(int argc, const char **argv) {
	// TODO
    if (argv == NULL) {
        return 1; //若addr为空
    }

    int len = argc;
    int i = 0;

    if (len < 2) {
        return 1;
    }
    for (i; i < len; i++) {
	if ( (strcmp(argv[i] , "--ip") == 0) && (i + 1 < len) ) {
                ip_len = strlen(argv [i+1]);
                paddr = new char [MAX_IP];
                //printf("iplen:%d\n",iplen);
		memcpy((char*)paddr , ( char*)argv[i + 1],ip_len);
                paddr[ip_len] = '\0';
                ip_flag = 1;
	}
       if ((strcmp(argv[i] ,"--port") == 0)  && (i + 1 < len)){
            //printf("Port:%s\n",*(argv + i+1));
                int  port_len = strlen(argv [i + 1]);
                if ( port_len <= MAX_PORT_LEN ) {
                    port_num = atoi(argv [i + 1]);
                }
                port_flag = 1;
        }
    }

    if (!ip_flag) {
        return 1;
    }

	return 0;
}


int get_ip(uint32_t &addr) {
	// TODO
   int n = 0,dot_num = 0,i = 0;
   char cIP[4];
   char *p = paddr;
   int sum_buf[4] = {0};
   uint32_t ip;
    if (ip_len > MAX_IP || ip_len < MIN_IP) {
         goto ERR;
    }

    while (*p != '\0') {
        if (*p == ' ' || *p < '0' || *p > '9') {
             goto ERR;
        }
        cIP[n++] = *p; //保存每个子段的第一个字符，用于之后判断该子段是否为0开头
        int sum = 0;  //sum为每一子段的数值，应在0到255之间

        while (*p != '.'&& *p != '\0')
        {
          if (*p== ' ' || *p < '0' || *p > '9') {
               goto ERR;
          }
          sum = sum * 10 + *p-48;  //每一子段字符串转化为整数
          p++;
        }
        if (*p == '.') {
	/*判断"."前后是否有数字，若无，则为无效IP，如“1.1.127.”  */
            if ((*(p - 1) >= '0' && *(p - 1) <= '9') && ( *(p + 1) >= '0' && *(p + 1) <= '9')) {
                dot_num++;  //记录“.”出现的次数，不能大于3
            }
            else {
               goto ERR;

            }
        }
        /* 若子段的值>255或为0开头的非0子段或“.”的数目>3，则为无效IP  */
        if ((sum > 255) || (sum > 0 && cIP[0] == '0') || dot_num > 3) {
             goto ERR;
        }

        if (*p != '\0') {
            p++;
        }
        n = 0;
       sum_buf[i] = sum ;
       i++;
    }

    if (dot_num != 3) {
        return 1;
    }
    addr = ( sum_buf[0]  << 24)+ ( sum_buf[1]  << 16) + ( sum_buf[2]  << 8) +  ( sum_buf[3]  << 0);

        //delete  p;
	return 0;

    ERR:{
        //delete  p;
        return 1;
    }
}

int get_port(uint32_t &port) {
	// TODO
    if ( port_flag== 0 ) {
        return 1;
    }
    if (!port_num){
        return 1;
    }else {
        if ((port_num > 1) && (port_num < 65535)) {
                port =  (uint32_t)port_num;
        }
        else {
            return 1;
        }
    }
	return 0;
}
