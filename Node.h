typedef struct Node {
    struct Node *next;
    int count;
    int first_seen;
    int last_seen;
    int vowel_count;
    char *name;
}Node;