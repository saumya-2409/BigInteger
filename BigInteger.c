#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct node{
    int data;
    struct node *next;
};

struct BigInteger{
    struct node *head;
    int len;
    int sign;
    char *ch;
};

struct node *createNode(int data)
{
    struct node *temp =(struct node *)malloc(sizeof(struct node));
    temp->next=NULL;
    temp->data=data;
    return temp;
}

struct BigInteger initialize(char *ch)
{
    struct BigInteger a;
    a.head=NULL;
    a.len = strlen(ch);
    a.sign = 1;
    for(int i = 0;i < strlen(ch); i++)
    {
        if(ch[i]!='-')
        {
            struct node *temp = createNode(ch[i] - '0');
            temp->next = a.head;
            a.head = temp;
        }
        else
            a.sign = -1;
    }
    a.ch=ch;
    return a;
}

void append(struct node **head, int data)
{
    struct node *temp = createNode(data);
    if(*head == NULL)
    {
        *head = temp;
        return;
    }
    temp->next = *head;
    *head = temp;
}

void displayReverse(struct node* current)
{
    if (current == NULL)
    {
        return;
    }
    displayReverse(current->next);
    printf("%d", current->data);
}

void display(struct BigInteger a)
{
    if(a.sign==-1)
        printf("-");
    displayReverse(a.head);
    printf("\n\n");
}

struct node *reverse(struct node *head)
{
    struct node* current = head;
    struct node *prev = NULL, *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    return head;
}

struct BigInteger subb(struct BigInteger a, struct BigInteger b)
{
    struct node *head = NULL;
    struct node *p1 = NULL;
    struct node *p2 = NULL;
    struct BigInteger c;
    p1 = a.head;
    p2 = b.head;
    int borrow = 0, diff = 0 ,x, y;
    while(p1 || p2)
    {
        if(p1)
            x = p1->data;
        else
            x = 0;
        if(p2)
            y = p2->data;
        else
            y = 0;
        diff = x - y - borrow;
        if(diff < 0)
        {
            diff = diff+10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        append(&head, diff%10);
        if(p1)
            p1 = p1->next;
        if(p2)
            p2 = p2->next;
    }
    if(borrow)
    {
        append(&head, borrow);
    }
    while (head != NULL && head->data == 0)
    {
        struct node *temp = head;
        head = head->next;
        free(temp);
    }
    c.head = reverse(head);
    return c;
}

struct BigInteger add(struct BigInteger a, struct BigInteger b)
{
    struct node *head = NULL;
    struct node *p1 = a.head;
    struct node *p2 = b.head;
    struct BigInteger c;
    if(a.sign ==-1 && b.sign == 1)
    {
        if(a.sign*atoi(a.ch) == b.sign*atoi(b.ch))
        {
            c.head = createNode(0);
            return c;
        }
        a.sign=1;
        if(-1*atoi(a.ch)>= atoi(b.ch))
        {
            c = subb(a, b);
            c.sign=-1;
        }
        else
        {
            c = subb(b, a);
            c.sign=1;
        }
        a.sign=-1;
        return c;
    }
    if(a.sign ==1 && b.sign == -1)
    {
        if(a.sign*atoi(a.ch) == b.sign*atoi(b.ch))
        {
            c.head = createNode(0);
            return c;
        }
        b.sign=1;
        if(atoi(a.ch)> -1*atoi(b.ch))
        {
            c = subb(a, b);
            c.sign=1;
        }
        else
        {
            c = subb(b, a);
            c.sign=-1;
        }
        b.sign=-1;
        return c;
    }
    if(a.sign == -1 && b.sign == -1)
        c.sign=-1;
    else
        c.sign=1;
    int carry = 0, sum = 0, x, y;
    while(p1 || p2)
    {
        if(p1)
        {
            x = p1->data;
            p1 = p1->next;
        }
        else
            x = 0;
        if(p2)
        {
            y = p2->data;
            p2 = p2->next;
        }
        else
            y = 0;
        sum = x + y + carry;
        carry = sum/10;
        append(&head, sum%10);
    }
    if(carry > 0)
        append(&head, carry);
    c.head = reverse(head);
    return c;
}

struct BigInteger sub(struct BigInteger a, struct BigInteger b)
{
    struct node *head = NULL;
    struct node *p1 = NULL;
    struct node *p2 = NULL;
    struct BigInteger c;
    if(a.sign==-1&&b.sign==1)
    {
        b.sign=-1;
        c=add(a,b);
        c.sign=-1;
        b.sign=1;
        return c;
    }
    if(a.sign==1&&b.sign==-1)
    {
        a.sign=-1;
        c=add(a,b);
        c.sign=1;
        a.sign=1;
        return c;
    }
    if(a.sign*atoi(a.ch) == a.sign*atoi(b.ch))
    {
        c.head = createNode(0);
        return c;
    }
    if(a.sign*atoi(a.ch) > a.sign*atoi(b.ch))
    {
        p1 = a.head;
        p2 = b.head;
        if(a.sign==-1&&b.sign==-1)
            c.sign = -1;
        else
            c.sign=1;
    }
    else
    {
        p1 = b.head;
        p2 = a.head;
        if(a.sign==-1&&b.sign==-1)
            c.sign = 1;
        if(a.sign==1&&b.sign==1)
            c.sign=-1;
    }
    int borrow = 0, diff = 0 ,x, y;
    while(p1 || p2)
    {
        if(p1)
            x = p1->data;
        else
            x = 0;
        if(p2)
            y = p2->data;
        else
            y = 0;
        diff = x - y - borrow;
        if(diff < 0)
        {
            diff = diff+10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        append(&head, diff%10);
        if(p1)
            p1 = p1->next;
        if(p2)
            p2 = p2->next;
    }
    if(borrow)
    {
        append(&head, borrow);
    }
    while (head != NULL && head->data == 0)
    {
        struct node *temp = head;
        head = head->next;
        free(temp);
    }
    c.head = reverse(head);
    return c;
}

struct node *mulAdd(struct node *result, struct node *temp)
{
    struct node *head = NULL;
    result = reverse(result);
    temp = reverse(temp);
    int carry = 0, sum = 0, x, y;
    while(result || temp)
    {
        if(result)
            x = result->data;
        else
            x = 0;
        if(temp)
            y = temp->data;
        else
            y = 0;
        sum = x + y + carry;
        carry = sum/10;
        append(&head, sum%10);
        if(result)
            result = result->next;
        if(temp)
            temp = temp->next;
    }
    if(carry > 0)
        append(&head, carry);
    return head;
}


struct BigInteger mul(struct BigInteger a, struct BigInteger b)
{
    struct node *p1 = a.head;
    struct node *p = p1;
    struct node *p2 = b.head;
    struct node *result = NULL;
    int mul, pos=0;
    while(p2)
    {
        struct node *head = NULL;
        int carry = 0;
        for(int i=0;i<pos;i++)
            append(&head, 0);
        while(p1)
        {
            mul = ((p1->data) * (p2->data)) + carry;
            carry=mul/10;
            append(&head, mul%10);
            p1 = p1->next;
        }
        while(carry!=0)
        {
            append(&head, carry%10);
            carry/=10;
        }
        p2 = p2->next;
        pos++;
        result = mulAdd(result, head);
        p1 = p;
    }
    struct BigInteger c;
    c.head= reverse(result);
    c.sign=a.sign*b.sign;
    return c;
}

int length (struct node *head)
{
    int i = 0;
    while(head)
    {
        i++;
        head = head->next;
    }
    return i;
}


struct node* diff (struct node *itr1, struct node *itr2)
{
    struct node *head=NULL,*l2=itr2, *l1=NULL;
    while(itr1)
    {
        struct node *n = createNode(itr1->data);
        n->next = l1;
        l1 = n;
        itr1 = itr1->next;
    }
    l1 = reverse(l1);
    int diff = 0;
    while(l1 && l2)
    {
        if((l1->data)<(l2->data))
        {
            if(l1->next)
            {
                l1->data += 10;
                l1->next->data--;
            }
            else
            {
                return NULL;
            }
        }
        diff = l1->data - l2->data;
        append(&head, diff);
        l1 = l1 -> next;
        l2 = l2 -> next;
    }
    while(l1)
    {
        if(l1->data<0)
        {
            if(l1->next)
            {
                l1->data += 10;
                l1->next->data--;
            }
            else
            {
                return  NULL;
            }
        }
        append(&head, l1->data);
        l1 = l1 -> next;
    }
    head= reverse(head);
    return head;
}