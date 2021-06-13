## glib
用鏈結串列時，已經不需要再自己對指標(Pointer)做許多低階的處理
範例程式 glist.c
```
/* Compile with:
export CFLAGS="`pkg-config --cflags glib-2.0` -g -Wall -std=gnu11 -O3"
export LDLIBS="`pkg-config --libs   glib-2.0`"
make glist
*/
#include <stdio.h>
#include <glib.h>

GList *list;

int main(){
    list = g_list_append(list, "a");
    list = g_list_append(list, "b");
    list = g_list_append(list, "c");
    printf("The list is now %d items long\n", g_list_length(list));

    for ( ; list!= NULL; list=list->next)
        printf("%s\n", (char*)list->data);

    printf("The list is now %d items long\n", g_list_length(list));
}
```

## pkg-config
pkg-config 是一個在原始碼編譯時查詢已安裝的函式庫的使用介面的電腦工具軟體。
C/C++編譯器需要的輸入參數
連結器需要的輸入參數
已安裝軟體包的版本資訊
## POSIX (Portable Operating System Interface)(可移植作業系統介面)
IEEE為要在各種UNIX作業系統上執行軟體，而定義API的一系列互相關聯的標準的總稱。
正式稱呼為IEEE Std 1003，而國際標準名稱為ISO/IEC 9945。