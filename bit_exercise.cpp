#include <stdio.h>
#include <malloc.h>


int bit_memcpy(unsigned char *dst, int dst_bit_idx, unsigned char *src, int src_bit_idx, int bit_size){
    unsigned char tmp1 = 0;
    int tmp1_bit_idx = 0;
    unsigned char tmp2 = 0;
    int tmp2_bit_idx = 0;

    // dst 첫바이트를 넣고, 뒤를 날립니다.
    tmp1 = dst[dst_bit_idx / 8];
    tmp1_bit_idx = dst_bit_idx % 8;
    tmp1 &= ~(0xff >> tmp1_bit_idx);

    // src 첫바이트를 넣고, 앞을 날립니다.
    tmp2 = src[src_bit_idx / 8];
    tmp2_bit_idx = src_bit_idx % 8;
    tmp2 &= (0xff >> tmp1_bit_idx);

    





}


int main(){
    printf("BIT EXERCICSE After Expert exam\n");

    unsigned char *test_buf = (unsigned char *)malloc(100);
    printf("test_buf address : 0x%08x\n", test_buf);
    printf("test_buf+1 address : 0x%08x\n", test_buf+1);
    printf("&test_buf address : 0x%08x\n", &test_buf);

    unsigned int ui_test_buf;
    ui_test_buf = *(unsigned int *)&test_buf;
    printf("ui_test_buf value : 0x%08x\n", ui_test_buf);

    unsigned char *p_test_buf;
    p_test_buf = (unsigned char *)(ui_test_buf + 1);
    printf("p_test_buf address : 0x%08x\n", p_test_buf);

    printf("(0xff >> 5) : 0x%08x\n", (0xff >> 5));
}