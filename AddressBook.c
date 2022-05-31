#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gui_void.h"

// Sort function
void SortAddBook(Addressbook *book)
{
    if (!book || !book->pfnode || !book->plnode)
    {
        printf("通讯录为空或者联系人为空\n");
        return;
    }
    DateNode *pfnode = book->pfnode;
    DateNode *plnode = book->plnode;
    pfnode->numb = 0;
    if (pfnode == plnode)
    {
        return;
    }
    plnode = pfnode->pnext;
    while (pfnode && plnode)
    {
        plnode->numb = pfnode->numb + 1;
        pfnode = pfnode->pnext;
        plnode = plnode->pnext;
    }
    book->Exitnode = book->plnode->numb - book->pfnode->numb + 1;
}

// name
int CheckBookName(Addressbook *book, char *name)
{
    if (!book)
    {
        printf("通讯录为空或者联系人为空\n");
        return Error;
    }
    DateNode *fnode = book->pfnode;
    DateNode *lnode = book->plnode;
    while (fnode && lnode)
    {
        if (strcmp(name, fnode->name) == 0)
        {
            return fnode->numb;
        }
        if (strcmp(name, lnode->name) == 0)
        {
            return lnode->numb;
        }
        fnode = fnode->pnext;
        lnode = lnode->plast;
    }
    return Ok;
}

// phone
int CheckBookPhone(Addressbook *book, char *phone)
{
    if (!book)
    {
        printf("通讯录不存在\n");
        return Error;
    }
    DateNode *fnode = book->pfnode;
    DateNode *lnode = book->plnode;
    while (fnode && lnode)
    {
        if (strcmp(phone, fnode->phone) == 0)
        {
            return fnode->numb;
        }
        if (strcmp(phone, lnode->phone) == 0)
        {
            return lnode->numb;
        }
        fnode = fnode->pnext;
        lnode = lnode->plast;
    }
    return Ok;
}

// Node assignment function
void NodeAssignment(Addressbook *book, DateNode *node)
{
    if (!book || !node)
    {
        printf("通讯录为空或者联系人为空\n");
        return;
    }
    // node assignment
    printf("请输入联系人名字\n");
    scanf("%s", node->name);
    while (CheckBookName(book, node->name) >= 0)
    {
        printf("请重新输入联系人名字\n");
        scanf("%s", node->name);
    }
    printf("请输入联系人性别\n");
    printf("0:未知  1:男  2:女\n");
    scanf("%d", &node->datepointer->sex);
    printf("请输入联系人手机号\n");
    scanf("%s", node->phone);
    while (CheckBookPhone(book, node->phone) >= 0)
    {
        printf("请重新输入联系人手机号\n");
        scanf("%s", node->phone);
    }
    printf("请输入联系人联系人类型\n");
    printf("1:商务类  2:办公类  3:个人类\n");
    scanf("%d", &node->myclass);
    printf("请输入联系人年龄\n");
    scanf("%s", node->datepointer->age);
    printf("请输入联系人邮箱\n");
    scanf("%s", node->email);
    printf("请输入联系人通讯地址\n");
    scanf("%s", node->address);
    printf("请输入联系人公司\n");
    scanf("%s", node->datepointer->company);
    printf("请输入联系人邮编地址\n");
    scanf("%s", node->datepointer->postcode);
}

// Clear
void ClearAddBook(DateNode *pfnode)
{
    if (!pfnode)
    {
        return;
    }
    ClearAddBook(pfnode->pnext);
    free(pfnode->datepointer);
    pfnode->datepointer = NULL;
    free(pfnode);
    pfnode = NULL;
    return;
}

// Doubly linked list structure
Addressbook *CreatAddBook()
{
    Addressbook *book = (Addressbook *)malloc(sizeof(Addressbook));
    // Determine whether the node is open
    if (!book)
    {
        printf("开辟失败，请重新开辟\n");
        return NULL;
    }
    // initialization operation
    memset(book, 0, sizeof(Addressbook));
    book->pfnode = NULL;
    book->plnode = NULL;
    // apply new node
    DateNode *node = (DateNode *)malloc(sizeof(DateNode));
    if (!node)
    {
        printf("开辟失败，请重新开辟\n");
        free(book);
        return NULL;
    }
    memset(node, 0, sizeof(DateNode));
    node->datepointer = NULL;
    node->plast = NULL;
    node->pnext = NULL;
    node->datepointer = (Date *)malloc(sizeof(Date));
    if (!node->datepointer)
    {
        printf("开辟失败，请重新开辟\n");
        free(node);
        free(book);
        node = NULL;
        book = NULL;
        return NULL;
    }
    memset(node->datepointer, 0, sizeof(Date));
    NodeAssignment(book, node);
    book->pfnode = node;
    book->plnode = book->pfnode;
    node = NULL;
    return book;
}

Addressbook *AddBookInsert(Addressbook *book)
{
    if (!book || !book->pfnode || !book->plnode)
    {
        printf("通讯录为空,正在初始化通讯录\n");
        if (book)
        {
            free(book);
            book = NULL;
        }
        book = CreatAddBook();
        return book;
    }
    // Apply for a new node
    DateNode *node = (DateNode *)malloc(sizeof(DateNode));
    if (!node)
    {
        return AddBookInsert(book);
    }
    memset(node, 0, sizeof(DateNode));
    node->datepointer = NULL;
    node->plast = NULL;
    node->pnext = NULL;
    node->datepointer = (Date *)malloc(sizeof(Date));
    if (!node->datepointer)
    {
        free(node);
        node = NULL;
        return AddBookInsert(book);
    }
    memset(node->datepointer, 0, sizeof(Date));
    // nodeassignment
    NodeAssignment(book, node);
    // link new node
    DateNode *plnode = book->plnode;
    plnode->pnext = node;
    node->plast = plnode;

    // Move the tail pointer to the end
    plnode = node;
    book->plnode = plnode;
    plnode = NULL;
    SortAddBook(book);
    return book;
}

// deletenode
void DeleNodeAddBook(Addressbook *book)
{
    if (!book || !book->pfnode || !book->plnode)
    {
        printf("没有数据可以删除\n");
        return;
    }
    if (book->plnode->numb - book->pfnode->numb + 1 == 15)
    {
        printf("通讯录已满\n");
        return;
    }
    int i = 0;
    printf("请选择删除功能\n");
    scanf("%d", &i);
    DateNode *pfnode = book->pfnode;
    DateNode *plnode = book->plnode;
    switch (i)
    {
    // delete the specified node
    case 1:
        printf("请输入一个数字删除\n");
        int numb;
        scanf("%d", &numb);
        // abnormal judgment
        while (numb > plnode->numb || numb < pfnode->numb)
        {
            printf("请重新输入\n");
            scanf("%d", &numb);
        }
        // head
        if (numb == pfnode->numb)
        {
            book->pfnode = book->pfnode->pnext;
            free(pfnode->datepointer);
            free(pfnode);
            pfnode->datepointer = NULL;
            pfnode = NULL;
            SortAddBook(book);
            return;
        }
        // tail
        if (numb == plnode->numb)
        {
            book->plnode = book->plnode->plast;
            free(plnode->datepointer);
            free(plnode);
            plnode->datepointer = NULL;
            plnode = NULL;
            SortAddBook(book);
            return;
        }
        // middle
        for (int i = 0; i < numb; i++)
        {
            pfnode = pfnode->pnext;
        }
        // plnode is delete node
        plnode = pfnode;
        pfnode = plnode->plast;
        // pointer movement
        pfnode->pnext = plnode->pnext;
        plnode->pnext->plast = pfnode;
        // pointer to null
        // release node
        free(plnode->datepointer);
        free(plnode);
        plnode->datepointer = NULL;
        plnode = NULL;
        SortAddBook(book);
        break;
    // Delete the specified number contact
    case 2:
        printf("请输入要删除的手机号\n");
        char phone[20];
        scanf("%s", phone);
        if (CheckBookPhone(book, phone) >= 0)
        {
            if (strcmp(pfnode->phone, phone) == 0)
            {
                book->pfnode = book->pfnode->pnext;
                free(pfnode->datepointer);
                free(pfnode);
                pfnode->datepointer = NULL;
                pfnode = NULL;
                SortAddBook(book);
                return;
            }
            if (strcmp(plnode->phone, phone) == 0)
            {
                book->plnode = book->plnode->plast;
                free(plnode->datepointer);
                free(plnode);
                plnode->datepointer = NULL;
                plnode = NULL;
                SortAddBook(book);
                return;
            }
            for (int i = 0; i < CheckBookPhone(book, phone); i++)
            {
                pfnode = pfnode->pnext;
            }
            if (!pfnode)
            {
                printf("没有数据可以删除\n");
                return;
            }
            // plnode is delete node
            pfnode = pfnode->plast;
            plnode = pfnode->pnext;
            // move the pointer
            pfnode->pnext = plnode->pnext;
            plnode->pnext->plast = pfnode;
            // pointer to null
            plnode->pnext = NULL;
            plnode->plast = NULL;
            // release node
            free(plnode->datepointer);
            free(plnode);
            plnode->datepointer = NULL;
            plnode = NULL;
            SortAddBook(book);
        }
        else
        {
            printf("没有找到对应手机号\n");
        }
        break;
    // delete specified contact
    case 3:
        printf("请输入要删除的姓名\n");
        char name[20];
        scanf("%s", name);
        if (CheckBookPhone(book, name) >= 0)
        {
            if (strcmp(pfnode->name, name) == 0)
            {
                book->pfnode = book->pfnode->pnext;
                free(pfnode->datepointer);
                free(pfnode);
                pfnode->datepointer = NULL;
                pfnode = NULL;
                SortAddBook(book);
                return;
            }
            if (strcmp(plnode->name, name) == 0)
            {
                book->plnode = book->plnode->plast;
                free(plnode->datepointer);
                free(plnode);
                plnode->datepointer = NULL;
                plnode = NULL;
                SortAddBook(book);
                return;
            }
            for (int i = 0; i < CheckBookPhone(book, name); i++)
            {
                pfnode = pfnode->pnext;
            }
            if (!pfnode)
            {
                printf("没有数据可以删除\n");
                return;
            }
            // plnode is delete node
            pfnode = pfnode->plast;
            plnode = pfnode->pnext;
            // move the pointer
            pfnode->pnext = plnode->pnext;
            plnode->pnext->plast = pfnode;
            // pointer to null
            plnode->pnext = NULL;
            plnode->plast = NULL;
            // release node
            free(plnode->datepointer);
            free(plnode);
            plnode->datepointer = NULL;
            plnode = NULL;
            SortAddBook(book);
        }
        else
        {
            printf("没有找到对应姓名\n");
        }
        break;
    // error
    default:
        printf("无效选择,正在回到主界面！\n");
        return;
    }
}

// change the data
void ChangeAddBookDate(Addressbook *book)
{
    if (!book || !book->pfnode || !book->plnode)
    {
        printf("通讯录为空,没有数据可以修改\n");
        return;
    }
    DateNode *pfnode = book->pfnode;
    DateNode *plnode = book->plnode;
    int numb = -1;
    char date[20] = {0};
    CheckAddGui();
    scanf("%d", &numb);
    switch (numb)
    {
    case 1:
        printf("请输入要查找的数据\n");
        scanf("%s", date);
        AddGui();
        numb = CheckBookPhone(book, date);
        if (numb < 0)
        {
            printf("通讯录无法找到数据,正在回到主界面\n");
            return;
        }
        else
        {
            DateNode *node = (DateNode *)malloc(sizeof(DateNode));
            if (!node)
            {
                printf("开辟内存失败！请重新再试\n");
                return;
            }
            memset(node, 0, sizeof(DateNode));
            node->datepointer = NULL;
            node->plast = NULL;
            node->pnext = NULL;
            node->datepointer = (Date *)malloc(sizeof(Date));
            if (!node)
            {
                printf("开辟内存失败！请重新再试\n");
                return;
            }
            memset(node->datepointer, 0, sizeof(Date));
            NodeAssignment(book, node);
            for (int i = 0; i < numb; i++)
            {
                pfnode = pfnode->pnext;
            }
            for (int i = 0; i < 20; i++)
            {
                pfnode->address[i] = node->address[i];
                pfnode->email[i] = node->email[i];
                pfnode->name[i] = node->name[i];
                pfnode->phone[i] = node->phone[i];
                pfnode->datepointer->age[i] = node->datepointer->age[i];
                pfnode->datepointer->company[i] = node->datepointer->company[i];
                pfnode->datepointer->postcode[i] = node->datepointer->postcode[i];
            }
            pfnode->myclass = node->myclass;
            pfnode->datepointer->sex = node->datepointer->sex;
            free(node);
            node = NULL;
        }
        break;
    case 2:
        printf("请输入要查找的数据\n");
        scanf("%s", date);
        AddGui();
        numb = CheckBookName(book, date);
        if (numb < 0)
        {
            printf("通讯录无法找到数据,正在回到主界面\n");
            return;
        }
        else
        {
            DateNode *node = (DateNode *)malloc(sizeof(DateNode));
            if (!node)
            {
                printf("开辟内存失败！请重新再试\n");
                return;
            }
            memset(node, 0, sizeof(DateNode));
            node->datepointer = NULL;
            node->plast = NULL;
            node->pnext = NULL;
            node->datepointer = (Date *)malloc(sizeof(Date));
            if (!node)
            {
                printf("开辟内存失败！请重新再试\n");
                return;
            }
            memset(node->datepointer, 0, sizeof(Date));
            NodeAssignment(book, node);
            for (int i = 0; i < numb; i++)
            {
                pfnode = pfnode->pnext;
            }
            for (int i = 0; i < 20; i++)
            {
                pfnode->address[i] = node->address[i];
                pfnode->email[i] = node->email[i];
                pfnode->name[i] = node->name[i];
                pfnode->phone[i] = node->phone[i];
                pfnode->datepointer->age[i] = node->datepointer->age[i];
                pfnode->datepointer->company[i] = node->datepointer->company[i];
                pfnode->datepointer->postcode[i] = node->datepointer->postcode[i];
            }
            pfnode->myclass = node->myclass;
            pfnode->datepointer->sex = node->datepointer->sex;
            free(node);
            node = NULL;
        }
        break;
    default:
        return;
    }
    SortAddBook(book);
}

void OutputAll(Addressbook *book)
{
    // null pointer is not exist
    if (!book || !book->pfnode || !book->plnode)
    {
        printf("通讯录为空\n");
        return;
    }
    SortAddBook(book);
    DateNode *pfnode = book->pfnode;
    DateNode *plnode = book->plnode;
    if (pfnode == plnode)
    {
        AddBookNoteGui(pfnode);
        return;
    }
    while (pfnode != NULL)
    {
        AddBookNoteGui(pfnode);
        pfnode = pfnode->pnext;
    }
}

// save to file
void SaveAddBook(Addressbook *book)
{
    if (!book || !book->pfnode || !book->plnode)
    {
        printf("通讯录为空\n");
        return;
    }
    FILE *fp = NULL;
    fp = fopen("./AddressBook.json", "w+");
    if (!fp)
    {
        printf("文件打开失败\n");
        SaveAddBook(book);
    }
    // moving the file pointer end
    if (fseek(fp, 0, SEEK_END) < 0)
    {
        printf("文件指针移动失败\n");
        exit(0);
    }
    DateNode *pfnode = book->pfnode;
    while (pfnode)
    {
        AddBookNoteFprintf(fp, pfnode);
        pfnode = pfnode->pnext;
    }
    fclose(fp);
    fp = NULL;
}

// output the specified contact
void SpecifiAddBook(Addressbook *book, int value)
{
    if (!book || !book->pfnode || !book->plnode)
    {
        printf("通讯录为空\n");
        return;
    }
    DateNode *pfnode = book->pfnode;
    DateNode *plnode = book->plnode;
    if (value < pfnode->numb || value > plnode->numb)
    {
        printf("输入数字错误,正在回到主界面\n");
        return;
    }
    if (pfnode == plnode)
    {
        AddBookNoteGui(pfnode);
        return;
    }
    while (pfnode->numb != value)
    {
        pfnode = pfnode->pnext;
    }
    AddBookNoteGui(pfnode);
}

// Export different types of contacts
void ExportTypeAdd(Addressbook *book, int class)
{
    if (!book || !book->pfnode || !book->plnode)
    {
        printf("通讯录为空\n");
        return;
    }
    DateNode *pfnode = book->pfnode;
    DateNode *plnode = book->plnode;

    while (pfnode != NULL)
    {
        if (pfnode->myclass == class)
        {
            AddBookNoteGui(pfnode);
        }
        pfnode = pfnode->pnext;
    }
}


int main()
{
    Addressbook *book = CreatAddBook();
    while (1)
    {
        char op = -1;
        AddBookGui();
        printf("请选择一个功能\n");
        scanf("%s", &op);
        int value = op - '0';
        value = value%10;
        switch (value)
        {
        case 1:
            AddGui();
            book = AddBookInsert(book);
            printf("添加结束\n");
            break;
        case 2:
            AddGui();
            ChangeAddBookDate(book);
            printf("修改结束\n");
            break;
        case 3:
            DeleteAddGui();
            DeleNodeAddBook(book);
            printf("删除结束\n");
            break;
        case 4:
            AddGui();
            printf("请输入联系人序号\n");
            AddGui();
            int value = -1;
            scanf("%d", &value);
            SpecifiAddBook(book, value);
            AddGui();
            printf("输出结束\n");
            AddGui();
            break;
        case 5:
            AddGui();
            OutputAll(book);
            printf("所有联系人已经输出\n");
            AddGui();
            break;
        case 6:
            TypeAddGui();
            int my_class = 0;
            scanf("%d", &my_class);
            ExportTypeAdd(book, my_class);
            printf("不同类型联系人已经输出\n");
            AddGui();
            break;
        case 7:
            AddGui();
            SaveAddBook(book);
            printf("文件保存完毕\n");
            AddGui();
            break;
        case 8:
            AddGui();
            ClearAddBook(book->pfnode);
            free(book);
            book = CreatAddBook();
            printf("初始化结束\n");
            AddGui();
            break;
        case 9:
            AddGui();
            ClearAddBook(book->pfnode);
            free(book);
            printf("程序已经结束,正在清空联系人\n");
            AddGui();
            exit(0);
        default:
            AddGui();
            AddBookGui();
            printf("功能选择错误,请重新输入\n");
            AddGui();
            break;
        }
    }
    return Error;
}