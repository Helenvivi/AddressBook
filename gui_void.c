#include <stdio.h>
#include <string.h>
#include "gui_void.h"

// gui
void AddBookGui()
{
    printf("--------------------通讯录管理系统-------------------\n");
    printf("-----------------------------------------------------\n");
    printf("---------            1,添加联系人            --------\n");
    printf("---------            2,修改联系人            --------\n");
    printf("---------            3,删除联系人            --------\n");
    printf("---------        4,输出指定序号联系人        --------\n");
    printf("---------        5,输出所有联系人            --------\n");
    printf("---------        6,输出不同类型联系人        --------\n");
    printf("---------             7,保存文件             --------\n");
    printf("---------           8,初始化通讯录           --------\n");
    printf("---------             9,结束程序             --------\n");
    printf("---------            0,回到主界面            --------\n");
    printf("-----------------------------------------------------\n");
}
// delete gui
void DeleteAddGui()
{
    printf("-----------------------------------------------------\n");
    printf("-----------------------------------------------------\n");
    printf("----------                1,序号           ----------\n");
    printf("----------               2,手机号          ----------\n");
    printf("----------                3,姓名           ----------\n");
    printf("-----------------------------------------------------\n");
    printf("-----------------------------------------------------\n");
}
// type gui
void TypeAddGui()
{
    printf("-----------------------------------------------------\n");
    printf("-----------------------------------------------------\n");
    printf("---------               1,商务类             --------\n");
    printf("---------               2,办公类             --------\n");
    printf("---------               3,个人类             --------\n");
    printf("-----------------------------------------------------\n");
    printf("-----------------------------------------------------\n");
}
//----
void AddGui()
{
    printf("-----------------------------------------------------\n");
    printf("-----------------------------------------------------\n");
}

// check gui
void CheckAddGui()
{
    printf("------------------------检查界面---------------------\n");
    printf("-----------------------------------------------------\n");
    printf("---------            1,查重手机号            --------\n");
    printf("---------             2,查重姓名             --------\n");
    printf("-----------------------------------------------------\n");
    printf("-----------------------------------------------------\n");
}

// AddBook Gui
void AddBookNoteGui(DateNode *node)
{
    char *sex[] = {"未知","男性","女性"};
    char *my_class[] = {"未知", "商务类", "办公类","个人类"};
    printf("-------------------这是第%d个联系人--------------------\n",node->numb);
    printf("-----------------------------------------------------\n");
    printf("     姓名 : %s\n", node->name);
    printf("     性别 : %s\n",sex[node->datepointer->sex]);
    printf("     邮箱 : %s\n",node->email);
    printf("     年龄 : %s\n",node->datepointer->age);
    printf(" 联系电话 : %s\n",node->phone);
    printf("     公司 : %s\n",node->datepointer->company);
    printf(" 通讯地址 : %s\n",node->address);
    printf(" 邮箱编码 : %s\n",node->datepointer->postcode);
    printf("联系人类别 :%s\n",my_class[node->myclass]);
    printf("-----------------------------------------------------\n");
    printf("-----------------------------------------------------\n");
}
void AddBookNoteFprintf(FILE *fp,DateNode *node)
{
    char *sex[] = {"未知","男性","女性"};
    char *my_class[] = {"未知", "商务类", "办公类","个人类"};
    fprintf(fp,"-------------------这是第%d个联系人--------------------\n",node->numb);
    fprintf(fp,"-----------------------------------------------------\n");
    fprintf(fp,"      姓名 : %s\n", node->name);
    fprintf(fp,"      性别 : %s\n",sex[node->datepointer->sex]);
    fprintf(fp,"  联系电话 : %s\n",node->phone);
    fprintf(fp,"      年龄 : %s\n",node->datepointer->age);
    fprintf(fp,"      邮箱 : %s\n",node->email);
    fprintf(fp,"      公司 : %s\n",node->datepointer->company);
    fprintf(fp,"  通讯地址 : %s\n",node->address);
    fprintf(fp,"  邮箱编码 : %s\n",node->datepointer->postcode);
    fprintf(fp,"联系人类型 : %s\n",my_class[node->myclass]);
    fprintf(fp,"-----------------------------------------------------\n");
    fprintf(fp,"-----------------------------------------------------\n");
}