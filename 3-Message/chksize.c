#include<stdio.h>


struct money2{
    int deposit;
    unsigned short numDeps;
    int withdraw;
    unsigned short numWithdraw;
};

struct money3{
    int deposit;
    int withdraw;
    unsigned short numDeps;
    unsigned short numWithdraw;
};

struct money4{
    int deposit;
    unsigned short numDeps;
    unsigned short numWithdraw;
};


int main(int argc,char *argv[]){
    printf("int:%luバイト\n",sizeof(int));
    printf("double:%luバイト\n",sizeof(double));
    printf("unsigned short:%luバイト\n",sizeof(unsigned short));
    printf("unsigned long:%luバイト\n",sizeof(unsigned long));
    printf("unsigned char:%luバイト\n",sizeof(unsigned char));
    printf("money2:%luバイト\n",sizeof(struct money2));
    printf("money3:%luバイト\n",sizeof(struct money3));
    printf("money4:%luバイト\n",sizeof(struct money4));
    return 0;
}
/*実行結果は後期中間テストにでる*/