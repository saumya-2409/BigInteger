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
struct BigInteger initialize(char *ch);
void display(struct BigInteger a);
struct BigInteger add(struct BigInteger a, struct BigInteger b);
struct BigInteger sub(struct BigInteger a, struct BigInteger b);
struct BigInteger mul(struct BigInteger a, struct BigInteger b);
