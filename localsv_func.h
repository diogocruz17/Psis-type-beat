typedef struct pairs
{
    char key[128];
    char *value;
    struct pairs *next;
}pairs;

typedef struct groups
{
    char group_id[64];
    char secret[128];
    struct groups *next;

}groups;

int create_group(char *group_id);