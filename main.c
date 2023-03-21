#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * https://phenix3443.github.io/notebook/software-engineering/debug/valgrind-practices.html
 */

/**
 * 使用未初始化的内存
==58721== Conditional jump or move depends on uninitialised value(s)
==58721==    at 0x109179: test1 (main.c:18)
==58721==    by 0x1091B2: main (main.c:191)
 * @return
 */
int test1(){
    int x;
    if(x == 0) {
        printf("X is zero");
    }
    return 0;
}

/**
 * 内存读写越界
==61836== Invalid write of size 4
==61836==    at 0x109284: test2 (main.c:52)
==61836==    by 0x1094A3: main (main.c:187)
==61836==  Address 0x4aab494 is 0 bytes after a block of size 20 alloc'd
==61836==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==61836==    by 0x109259: test2 (main.c:48)
==61836==    by 0x1094A3: main (main.c:187)
==61836==
==61836== Invalid read of size 4
==61836==    at 0x10928E: test2 (main.c:53)
==61836==    by 0x1094A3: main (main.c:187)
==61836==  Address 0x4aab494 is 0 bytes after a block of size 20 alloc'd
==61836==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==61836==    by 0x109259: test2 (main.c:48)
==61836==    by 0x1094A3: main (main.c:191)
 * @return
 */
int test2(){
    int len=5;
    int i;
    int *pt=(int*)malloc(len*sizeof(int));
    int *p=pt;
    for(i=0;i<len;i++)
    {p++;}
    *p=5;
    printf("%d",*p);
}

/**
 * src 和 dst 内存覆盖s
 * 无内存泄漏
 * @return
 */
int test3(){
    char x[50];
    int i;
    for(i=0;i<50;i++){
        x[i]=i;
    }
    strncpy(x+20,x,20); //Good
    strncpy(x+20,x,21); //Overlap
    x[39]='\0';
    strcpy(x,x+20); //Good
    x[39]=40;
    x[40]='\0';
    strcpy(x,x+20); //Overlap
}

///**
// * 内存动态管理中常见的错误
// * @return
// */
//int test4(){
//    char *p=(char*)malloc(10);
//    char *pt=p;
//    int i;
//    for(i=0;i<10;i++)
//    {
//        p[i]='z';
//    }
//    delete p;
//    p[1]='a';
//    free(pt);
//}

/**
 * 内存泄漏
==61983== Invalid free() / delete / delete[] / realloc()
==61983==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==61983==    by 0x1093B5: test5 (main.c:113)
==61983==    by 0x1094A3: main (main.c:188)
==61983==  Address 0x4aab4e0 is 0 bytes inside a block of size 20 free'd
==61983==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==61983==    by 0x1093A9: test5 (main.c:112)
==61983==    by 0x1094A3: main (main.c:188)
==61983==  Block was alloc'd at
==61983==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==61983==    by 0x109391: test5 (main.c:110)
==61983==    by 0x1094A3: main (main.c:191)
==61983==
 * @return
 */
int test5(){
    char *x = (char*)malloc(20);
    char *y = (char*)malloc(20);
    x=y;
    free(x);
    free(y);
}

/**
 * 非法读写
 *
==62036== Invalid write of size 4
==62036==    at 0x1093F3: test6 (main.c:134)
==62036==    by 0x1094A3: main (main.c:189)
==62036==  Address 0x4aab4a8 is 0 bytes after a block of size 40 alloc'd
==62036==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==62036==    by 0x1093CE: test6 (main.c:132)
==62036==    by 0x1094A3: main (main.c:191)
==62036==
s *
 * @return
 */
int test6(){
    int i, *x;
    x = (int *)malloc(10*sizeof(int));
    for (i=0; i<11; i++)
        x[i] = i;
    free(x);
    return 0;
}

/**
 * 无效指针
 *
==62099== Invalid write of size 1
==62099==    at 0x109434: test7 (main.c:154)
==62099==    by 0x1094A3: main (main.c:190)
==62099==  Address 0x4aab48a is 0 bytes after a block of size 10 alloc'd
==62099==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==62099==    by 0x109427: test7 (main.c:153)
==62099==    by 0x1094A3: main (main.c:191)
==62099==
 * @return
 */
int test7(){
    char *x = malloc(10);
    x[10] = 'a';
    free(x);
    return 0;
}

/**
 * 重复释放
 *
==62158== Invalid free() / delete / delete[] / realloc()
==62158==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==62158==    by 0x10947B: test8 (main.c:180)
==62158==    by 0x1094A3: main (main.c:191)
==62158==  Address 0x4aab480 is 0 bytes inside a block of size 10 free'd
==62158==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==62158==    by 0x10946F: test8 (main.c:179)
==62158==    by 0x1094A3: main (main.c:191)
==62158==  Block was alloc'd at
==62158==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==62158==    by 0x10945F: test8 (main.c:178)
==62158==    by 0x1094A3: main (main.c:191)
==62158==
 * @return
 */
int test8(){
    char *x = malloc(10);
    free(x);
    free(x);
    return 0;
}
int main() {
    printf("\n开始分析\n");
//    test1();
//    test2();
//    test3();
//    test5();
//    test6();
//    test7();
    test8();
    printf("\n分析结束\n");
    return 0;
}
