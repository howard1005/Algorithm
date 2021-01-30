#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


int bit_memcpy(unsigned char *dst, int dst_bit_idx, unsigned char *src, int src_bit_idx, int bit_size){
    unsigned char tmp1 = 0;
    int tmp1_bit_idx = 0;
    int tmp1_space = 0;
    unsigned char tmp2 = 0;
    int tmp2_bit_idx = 0;
    int tmp2_space = 0;

    int remain_size = 0;
    int cpy_size = 0;

    while(cpy_size < bit_size){
        // dst의 현재 1바이트를 넣고, 뒤를 날립니다.
        tmp1 = dst[dst_bit_idx / 8];
        tmp1_bit_idx = dst_bit_idx % 8;
        tmp1 &= ~(0xff >> tmp1_bit_idx);

        // src의 현재 1바이트를 넣고, 앞을 날립니다.
        tmp2 = src[src_bit_idx / 8];
        tmp2_bit_idx = src_bit_idx % 8;
        tmp2 &= (0xff >> tmp1_bit_idx);

        // dst 현재 바이트의 빈공간 크기 계산
        tmp1_space = 8 - tmp1_bit_idx;
        // src 현재 바이트에 복사할 크기 계산
        tmp2_space = 8 - tmp2_bit_idx;
        if(tmp2_space > (bit_size - cpy_size)){// 남은 복사해야할 크기보다 src 남은 크기가 크면 줄이기
            tmp2 >>= (tmp2_space - (bit_size - cpy_size));
            tmp2_space = (bit_size - cpy_size);
        }
        // src가 dst에 복사 되고 dst에 남는공간
        remain_size = tmp1_space - tmp2_space;

        if(remain_size >= 0){// 다 들어감
            tmp1 |= (tmp2 << remain_size);
            dst[dst_bit_idx / 8] = tmp1;
            dst_bit_idx += tmp2_space;
            src_bit_idx += tmp2_space;
            cpy_size += tmp2_space;
        }
        else{// 초과됨
            tmp1 |= (tmp2 >> -remain_size);
            dst[dst_bit_idx / 8] = tmp1;
            dst_bit_idx += (tmp2_space + remain_size);
            src_bit_idx += (tmp2_space + remain_size);
            cpy_size += (tmp2_space + remain_size);
        }
        
    }
    return cpy_size;
}

void print_hex(unsigned char *buf, int buf_size){
    for (int i = 0; i < buf_size; i++){
        printf("%x", buf[i]);
    }
    printf("\n");
}


int main(){
    printf("BIT EXERCICSE After Expert exam\n");

    unsigned char *test_buf = (unsigned char *)malloc(100);
    for (int i = 0; i < 100; i++){
        test_buf[i] = 0;
    }
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

    unsigned char *test_buf2 = (unsigned char *)malloc(100);
    for (int i = 0; i < 100; i++){
        test_buf2[i] = rand() % 128;
    }
    bit_memcpy(test_buf, 1, test_buf2, 0, 21);
    print_hex(test_buf, 100);
}