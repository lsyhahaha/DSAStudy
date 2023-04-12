typedef struct StringNode
{
    // 每个结点8个字符
    // 不这样做的话就会是一个很蠢的方案，
    // 因为char只占1字节，而指针在32位下要占用4B。
    // 存储密度很低。
    char ch[8];
    struct StringNode *next;
} StringNode, *String;