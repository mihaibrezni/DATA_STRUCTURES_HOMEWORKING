#include "eliminare.h"

int main(int argc, char **argv)
{
    double_nod *head = NULL;
    int n;
    scanf("%d", &n);
    head = CreateDoubleList(head, n);

    int ok = 1;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp("--e1", argv[i]) == 0 || strcmp("e1", argv[i]) == 0)
        {
            RemoveExceptions(head, &n);
        }
        else if (strcmp("--e2", argv[i]) == 0 || strcmp("e2", argv[i]) == 0)
        {
            head = FiltrareMediana(head, &n);
        }
        else if (strcmp("--e3", argv[i]) == 0 || strcmp("e3", argv[i]) == 0)
        {
            head = FiltrareAritmetica(head, &n);
            // PrintList(head);
        }
        else if (strcmp("--u", argv[i]) == 0 || strcmp("u", argv[i]) == 0)
        {
            head = UniformizareFrecvente(head, &n);
        }
        else if ((strcmp("--c", argv[i]) == 0) || (strcmp("c", argv[i]) == 0))
        {
            head = CompletareDate(head, &n);
        }
        else
        {
            int interval;
            if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == 's' && argv[i][3] == 't')
            {
                char *temp_string = (char *)calloc(strlen(argv[i]), sizeof(char));
                strcpy(temp_string, argv[i] + 4);
                interval = atoi(temp_string);
                free(temp_string);
                ok = 0;
            }
            else if (argv[i][0] == 's' && argv[i][1] == 't')
            {
                char *temp_string = (char *)calloc(strlen(argv[i]), sizeof(char));
                strcpy(temp_string, argv[i] + 2);
                interval = atoi(temp_string);
                free(temp_string);
                ok = 0;
            }
            head = statistici(head, &n, interval);
        }
    }

    // on last task you wont have to print the list
    if (ok == 1)
    {
        printf("%d\n", n);
        PrintList(head);
    }

    free_list(&head);
    return 0;
}