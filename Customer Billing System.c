#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include<ctype.h>
struct node
{
    int ProductCode;
    char ProductName[20];
    int Price;
    int Quntity;
    struct node *next;
    struct node *previous;
};
struct node *head = NULL;

struct customer
{
    int ProductCode;
    char ProductName[20];
    int Price;
    int Quntity;
    struct node *next;
    struct node *previous;
};
struct customer *cst;
void printData()
{
    printf("\t\t**************************************************\n");
    printf("\n\t\t\t\t Main Menu\n\n");
    printf("\t\t***************************************************\n");
    printf("\n\t\t1) Administration.\n\n\t\t2) Customer.\n\n\t\t3) Exit.");
}

void sortList()
{
    struct node *current = NULL, *index = NULL;
    int temp;
    char name[20];
    if (head == NULL)
    {
        return;
    }
    else
    {
        for (current = head; current->next != NULL; current = current->next)
        {
            for (index = current->next; index != NULL; index = index->next)
            {
                if (strcmp(current->ProductName, index->ProductName) > 1)
                {
                    temp = current->ProductCode;
                    current->ProductCode = index->ProductCode;
                    index->ProductCode = temp;

                    temp = current->Price;
                    current->Price = index->Price;
                    index->Price = temp;

                    temp = current->Quntity;
                    current->Quntity = index->Quntity;
                    index->Quntity = temp;

                    strcpy(name, current->ProductName);
                    strcpy(current->ProductName, index->ProductName);
                    strcpy(index->ProductName, name);
                }
            }
        }
    }
}

void sortListforCustomer()
{
    struct customer *current = NULL, *index = NULL;
    int temp;
    char name[20];
    if (head == NULL)
    {
        return;
    }
    else
    {
        for (current = head; current->next != NULL; current = current->next)
        {
            for (index = current->next; index != NULL; index = index->next)
            {
                if (strcmp(current->ProductName, index->ProductName) > 1)
                {
                    temp = current->ProductCode;
                    current->ProductCode = index->ProductCode;
                    index->ProductCode = temp;

                    temp = current->Price;
                    current->Price = index->Price;
                    index->Price = temp;

                    temp = current->Quntity;
                    current->Quntity = index->Quntity;
                    index->Quntity = temp;

                    strcpy(name, current->ProductName);
                    strcpy(current->ProductName, index->ProductName);
                    strcpy(index->ProductName, name);
                }
            }
        }
    }
}

void AddProduct(int PC, char PN[20], int P, int Q)
{
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node));

    newNode->ProductCode = PC;
    strcpy(newNode->ProductName, PN);
    newNode->Price = P;
    newNode->Quntity = Q;
    newNode->next = NULL;

    if (head == NULL)
    {
        newNode->previous = NULL;
        head = newNode;
        printf("\n\n\t\tAdd Succesfully.\n");
    }

    else
    {
        struct node *temp;
        temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
        newNode->previous = temp;
        printf("\n\n\t\tAdd Succesfully.\n");
    }
    sortList();
}

void deleteProduct(int PC)
{
    int flag = 0;
    if (head == NULL)
        printf("\n List is empty. can't delete.");

    else
    {
        struct node *ptr, *temp;
        temp = head;

        while (temp != NULL)
        {
            if (temp->ProductCode == PC)
            {
                flag = 1;
                break;
            }
            temp = temp->next;
        }

        if (flag == 0)
            printf("\n\t\tProduct code dosn.t match with product list.\n\n");

        else
        {
            if (temp->next == NULL && temp->previous == NULL)
            {
                head = NULL;
                free(head);
                printf("No product available here. ");
            }

            else if (temp->previous == NULL)
            {
                temp->next->previous = NULL;
                head = temp->next;
                free(temp);
                printf("Product deletes successfully.");
            }

            else if (temp->next == NULL)
            {
                temp->previous->next = NULL;
                printf("Product deletes successfully.");
            }

            else
            {
                ptr = temp->next;
                ptr->previous = temp->previous->next;
                temp->previous->next = ptr;
                temp = NULL;
                free(temp);
                printf("Product deletes successfully.");
            }
        }
    }
}

void display()
{
    if (head == NULL)
    {

        printf("\n\n\t\tProduct Code\t\t| Product Name\t\t| price\t\t| Quantity.");
        printf("\n\n\t\tThere have no Product.");
    }

    else
    {
        struct node *temporary = head;

        while (temporary != NULL)
        {

            printf("\n\n\t\t%d\t\t| %s\t\t| %d\t\t|%d", temporary->ProductCode, temporary->ProductName, temporary->Price, temporary->Quntity);
            temporary = temporary->next;
        }
    }
}

// Customer section

void buyProduct()
{
    int N, Q, flag = 0;
    struct node *temp = head;
    printf("\n\n\t\tEnter the product code of the product you want to buy: ");
    scanf("%d", &N);
    while (temp != NULL)
    {
        if (temp->ProductCode == N)
        {
            printf("\n\n\t\tEnter Quantity: ");
            scanf("%d", &Q);
            if (temp->Quntity > 0 && temp->Quntity >= Q)
            {

                flag = 1;
                break;
            }
            else
            {
                printf("\n\n\t\tOut of Stock.");
            }
        }
        temp = temp->next;
    }
    struct customer *ptr = cst;
    if (flag == 0)
    {
        printf("\n\n\t\tOops! Product code dosen't match. please Enter correct Product code.");
    }
    else
    {
        struct customer *newnode;
        newnode = (struct customer *)malloc(sizeof(struct customer));
        newnode->ProductCode = temp->ProductCode;
        strcpy(newnode->ProductName, temp->ProductName);
        newnode->Quntity = Q;
        newnode->Price = temp->Price * Q;
        newnode->next = NULL;
        if (ptr == NULL)
        {
            newnode->previous = NULL;
            cst = newnode;
            printf("\n\n\t\tAdd to cart.");
            return;
        }
        else
        {
            while(ptr->next != NULL)
                ptr = ptr->next;
            ptr->next = newnode;
            newnode->previous = ptr;
            ptr = newnode;
            printf("\n\n\t\tAdd to cart.");
            return;
        }
    }
}

void myCart()
{
    int total = 0;
    if (cst != NULL)
    {

        printf("\n\n\t\tProduct Code\t\t| Product Name\t\t| price\t\t| Quantity.");
        printf("\n\n\t\tThere have no Product.");
    }

    else
    {
        struct customer *temporary = cst;

        while (temporary != NULL)
        {
            printf("\n\n\t\tProduct Code\t\t| Product Name\t\t| price\t\t| Quantity.");
            total = total + temporary->Price;
            printf("\n\n\t\t%d\t\t|", temporary->ProductCode);
            printf(" %s\t\t|", temporary->ProductName);
            printf(" %d\t\t|", temporary->Price);
            printf(" %d", temporary->Quntity);
            temporary = temporary->next;
        }
    }

    printf("\n\n\t\t--------------------------Payable amount: %d TK", total);

    printf("\n\t\tThanks for shopping.");
}

void deleteCartProduct(int PC)
{
    int flag = 0;
    if (head == NULL)
        printf("\n\t\t List is empty. can't delete.");

    else
    {
        struct node *ptr, *temp;
        temp = cst;

        while (temp != NULL)
        {
            if (temp->ProductCode == PC)
            {
                flag = 1;
                break;
            }
            temp = temp->next;
        }

        if (flag == 0)
            printf("\n\t\tProduct code dosn.t match with product list.\n\n");

        else
        {
            if (temp->next == NULL && temp->previous == NULL)
            {
                cst = NULL;
                free(cst);
                printf("\n\t\tNo product available here. ");
            }

            else if (temp->previous == NULL)
            {
                temp->next->previous = NULL;
                head = temp->next;
                free(temp);
                printf("\n\t\tProduct deletes successfully.");
            }

            else if (temp->next == NULL)
            {
                temp->previous->next = NULL;
                printf("\n\t\tProduct deletes successfully.");
            }

            else
            {
                ptr = temp->next;
                ptr->previous = temp->previous->next;
                temp->previous->next = ptr;
                temp = NULL;
                free(temp);
                printf("\n\t\tProduct deletes successfully.");
            }
        }
    }
}


int main()
{
    int choice1,
        choice2;

menu:
    printData();
    printf("\n\n\t\tEnter choice an option: ");
    scanf("%d", &choice1);

    switch (choice1)
    {
    case 1:
        system("clear");
    SubMenu1:
        printf("\n\t\t1) Add New Product.\n\n\t\t2) Delete Product.\n\n\t\t3) Display.\n\n\t\t4) Main Menu.\n\n\t\t5) exit.\n");

        printf("\n\n\t\tEnter choice an option: ");
        scanf("%d", &choice2);

        switch (choice2)
        {
        case 1:
            system("clear");
            char name[20], c;
            int PC, P, Q;
            printf("\n\n\t\tEnter Poduct code: ");
            scanf("%d", &PC);
            printf("\n\n\t\tEnter Product Name: ");
            scanf("\n\t\t");
            fgets(name, 20, stdin);

            printf("\n\n\t\tEnter Poduct price: ");
            scanf("%d", &P);

            printf("\n\n\t\tEnter Poduct Quantity: ");
            scanf("%d", &Q);

            AddProduct(PC, name, P, Q);

            goto SubMenu1;
            break;

        case 2:
            system("clear");
            printf("\n\t\tEnter product code which do you want to delete: ");
            scanf("%d", &PC);
            deleteProduct(PC);
            display();

            goto SubMenu1;

        case 3:
            system("clear");
            display();
            goto SubMenu1;
            break;

        case 4:
            system("clear");
            goto menu;
            break;

        case 5:
            exit(0);
            break;

        default:
            printf("\n\t\tInvalid option. Please input right Item.\n");
            goto SubMenu1;
            break;
        }

        break;

    case 2:
        system("clear");
    SubMenu2:
        printf("\n\t\t1) Buy Product. \n\n\t\t2) My cart.\n\n\t\t3) Delete Selected Product.\n\n\t\t4) Main Menu.\n\n\t\t5) exit.\n");

        printf("\n\n\t\tEnter choice an option: ");
        scanf("%d", &choice2);

        switch (choice2)
        {
        case 1:
            system("clear");
            display();
            buyProduct();
            goto SubMenu2;
            break;
        case 2:
            system("clear");
            myCart();
            goto SubMenu2;
            break;
        case 3:
            int crtproduct;
            printf("\n\n\t\tEnter Product code what you need to delete from cart: ");
            scanf("%d", &crtproduct);
            deleteCartProduct(crtproduct);
            goto SubMenu2;
            break;
        case 4:
            system("clear");
            goto menu;
            break;
        case 5:
            exit(0);
            break;

        default:
            printf("\n\t\tInvalid option. Please input right Item.\n");
            goto SubMenu2;
            break;
        }

        break;

    default:
        printf("\n\t\tInvalid option. Please input right Item.\n");
        goto menu;
        break;
    }
}
