#include "eliminare.h"

double_nod *CreateDoubleList(double_nod *head, int n)
{
    // create first Node
    if (head == NULL)
    {
        head = (double_nod *)calloc(1, sizeof(double_nod));
        scanf("%d", &head->time_stamp);
        scanf("%lf", &head->valoareReala);
        head->prev = NULL;
        head->next = NULL;
    }
    // keep the head;
    double_nod *initial_head = head;

    // create the rest of the nodes
    for (int i = 1; i < n; i++)
    {
        head->next = (double_nod *)calloc(1, sizeof(double_nod));
        scanf("%d", &head->next->time_stamp);
        scanf("%lf", &head->next->valoareReala);
        head->next->prev = head;
        head->next->next = NULL;
        head = head->next;
    }
    return initial_head;
}

void PrintList(double_nod *head)
{
    while (head != NULL)
    {
        printf("%d ", head->time_stamp);
        printf("%.2lf\n", head->valoareReala);
        head = head->next;
    }
}

double medie(double_nod *head)
{
    double s_left = head->prev->prev->valoareReala + head->prev->valoareReala;
    double s_right = head->next->valoareReala + head->next->next->valoareReala;
    double s = (s_left + s_right + head->valoareReala) / 5;
    return s;
}

double putere(double n)
{
    return n * n;
}

double deviatie(double_nod *head, double medie_valori)
{
    double s_left = putere(head->prev->prev->valoareReala - medie_valori) + putere(head->prev->valoareReala - medie_valori);
    double s_right = putere(head->next->valoareReala - medie_valori) + putere(head->next->next->valoareReala - medie_valori);
    double s = s_left + s_right + putere(head->valoareReala - medie_valori);
    return sqrt(s / 5);
}

void EliminateNode(double *v, int to_eliminate, double_nod *head)
{
    // PrintList(head);
    for (int i = 0; i < to_eliminate; i++)
    {
        // find the value in node to take_out
        while (head->valoareReala != v[i])
            head = head->next;

        // eliminate node from list
        double_nod *store_next = head->next;
        double_nod *store_prev = head->prev;
        store_next->prev = store_prev;
        store_prev->next = store_next;

        // free memory and go to the next node
        double_nod *to_free = head;
        head = head->next;
        free(to_free);
    }
}

void RemoveExceptions(double_nod *head, int *n)
{
    double_nod *initial_head = head;
    head = head->next->next;

    int count = 3, to_eliminate = 0;
    double *v = (double *)calloc(10000, sizeof(double));

    // find how many numbers to eliminate
    while (count <= *n - 2)
    {
        double medie_valori = medie(head);

        double dev_stan = deviatie(head, medie_valori);
        double left_margin = medie_valori - dev_stan;
        double right_margin = medie_valori + dev_stan;

        // check intervals
        if (head->valoareReala < left_margin || head->valoareReala > right_margin)
        {
            // store the valoareReala to eliminate
            v[to_eliminate++] = head->valoareReala;
        }
        head = head->next;
        count++;
    }

    EliminateNode(v, to_eliminate, initial_head);
    *n = *n - to_eliminate;
    free(v);
}

/* *********************************************E2******************************************* */

void swap(double *xp, double *yp)
{
    double temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(double arr[], int n)
{
    int i, j;
    // bool swapped;
    for (i = 0; i < n - 1; i++)
    {
        bool swapped = true;
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] - arr[j + 1] > 0.001)
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = false;
            }
        }

        // IF no two elements were swapped by inner loop, then break
        if (swapped == true)
            return;
    }
}

double_nod *aux_list(int time, double median, double_nod *aux_nod)
{

    if (aux_nod == NULL)
    {
        aux_nod = (double_nod *)calloc(1, sizeof(double_nod));
        aux_nod->prev = NULL;
        aux_nod->time_stamp = time;
        aux_nod->valoareReala = median;
        aux_nod->next = NULL;

        return aux_nod;
    }
    else
    {
        double_nod *initial_head = aux_nod;

        while (aux_nod->next != NULL)
            aux_nod = aux_nod->next;

        aux_nod->next = (double_nod *)calloc(1, sizeof(double_nod));
        aux_nod->next->time_stamp = time;
        aux_nod->next->valoareReala = median;

        aux_nod->next->next = NULL;
        aux_nod->next->prev = aux_nod;

        return initial_head;
    }
}

double_nod *FiltrareMediana(double_nod *head, int *n)
{
    double_nod *initial_head = head;
    head = head->next->next;
    double *v = (double *)calloc(6, sizeof(double));

    double_nod *aux_nod = NULL;

    while (head->next->next != NULL)
    {
        // create the list of elements
        v[0] = head->prev->prev->valoareReala;
        v[1] = head->prev->valoareReala;
        v[2] = head->valoareReala;
        v[3] = head->next->valoareReala;
        v[4] = head->next->next->valoareReala;

        sort(v, 5);
        aux_nod = aux_list(head->time_stamp, v[2], aux_nod);

        head = head->next;
    }

    free(v);
    *n -= 4;
    free_list(&initial_head);
    return aux_nod;
}
/* &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&--------------E3-------&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& */

double_nod *FiltrareAritmetica(double_nod *head, int *n)
{
    double_nod *initial_head = head;
    head = head->next->next;
    double *v = (double *)calloc(6, sizeof(double));

    double_nod *aux_nod = NULL;

    while (head->next->next != NULL)
    {
        // create the list of elements
        v[0] = head->prev->prev->valoareReala;
        v[1] = head->prev->valoareReala;
        v[2] = head->valoareReala;
        v[3] = head->next->valoareReala;
        v[4] = head->next->next->valoareReala;

        double medie_valori = v[0] + v[1] + v[2] + v[3] + v[4] + v[5];
        // create the new list;
        aux_nod = aux_list(head->time_stamp, medie_valori / 5, aux_nod);

        head = head->next;
    }

    free(v);
    *n -= 4;
    free_list(&initial_head);
    return aux_nod;
}

/* ...........................................uuu........................................... */

double_nod *UniformizareFrecvente(double_nod *head, int *n)
{
    double_nod *initial_head = head;
    // go to the second node in list;
    head = head->next;
    while (head != NULL)
    {
        double diff = head->time_stamp - head->prev->time_stamp;
        if (diff >= 100.0 && diff <= 1000.0)
        {
            int new_time = (head->time_stamp + head->prev->time_stamp) / 2.0;
            double new_valoareReala = (head->valoareReala + head->prev->valoareReala) / 2.0;
            head->time_stamp = new_time;
            head->valoareReala = new_valoareReala;
        }
        head = head->next;
    }

    return initial_head;
}

/* ====================================================== C ====================================================== */

double f_scalare(double time_stamp, double left, double right)
{
    double numitor = right - left;
    double factor_c = (time_stamp - left) / numitor;
    return (double)factor_c;
}

double numarator(int n)
{
    return ((((double)n * n) / 4.0) * 0.9 + 0.1);
}

double raportul(int i)
{
    double num = numarator(i);
    double numitor = 0.0;
    i = 0;
    while (i < 3)
    {
        numitor = numitor + numarator(i);
        i++;
    }
    return (double)(num / numitor);
}

double f(double C, double *w, double_nod *start_head, double_nod *end_head)
{
    // take every sum
    double suma_left = start_head->valoareReala * w[2] + start_head->prev->valoareReala * w[1] +
                       start_head->prev->prev->valoareReala * w[0];

    double suma_right = end_head->valoareReala * w[2] + end_head->next->valoareReala * w[1] +
                        end_head->next->next->valoareReala * w[0];

    // calculate after formula
    double suma = (1.0 - C) * suma_left + (double)C * suma_right;

    return suma;
}

double_nod *CompletareDate(double_nod *head, int *n)
{
    double_nod *initial_head = head;
    // go to the third element
    head = head->next->next;

    // keep how many dates do you add
    int add = 0;
    // check condition
    while (head->next->next->next != NULL)
    {
        if (head->next->time_stamp - head->time_stamp > 1000)
        {
            // keep left anf right value
            double left = head->time_stamp;
            double right = head->next->time_stamp;

            // keep also start and end head
            double_nod *start_head = head;
            double_nod *end_head = head->next;

            double w[3];
            for (int i = 0; i < 3; i++)
            {
                w[i] = raportul(i);
            }

            double factor_c = f_scalare(head->time_stamp + 200.0, left, right);

            // break conection with list to creates and add new nodes
            head->next->prev = NULL;
            head->next = NULL;

            while (head->time_stamp + 200.0 < right)
            {
                add++;

                // create nod , make conection add dates in it
                head->next = (double_nod *)calloc(1, sizeof(double_nod));
                head->next->next = NULL;
                head->next->prev = head;
                head->next->time_stamp = head->time_stamp + 200.0;
                head->next->valoareReala = f(factor_c, w, start_head, end_head);

                // go to the next node and find the new factor to scale
                head = head->next;
                factor_c = f_scalare(head->time_stamp + 200.0, left, right);
            }
            head->next = end_head;
            end_head->prev = head;
        }
        head = head->next;
    }

    *n += add;
    return initial_head;
}

/*  ======================================== st ============================ */

// sort list to know the intervals
void bubbleSort(double_nod *start)
{
    int swapped;
    double_nod *ptr1;
    double_nod *lptr = NULL;

    /* Checking for empty list */
    if (start == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr)
        {
            if (ptr1->valoareReala > ptr1->next->valoareReala)
            {
                swap(&ptr1->valoareReala, &ptr1->next->valoareReala);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

double_nod *statistici(double_nod *head, int *n, int delta)
{
    bubbleSort(head);
    double_nod *initial_head = head;
    int interval;
    // find the start point of interval
    if ((int)head->valoareReala > head->valoareReala)
    {
        interval = head->valoareReala - 1;
    }
    else
    {
        interval = (int)head->valoareReala;
    }

    int count = 0;
    // count every number in interval
    while (head != NULL)
    {
        count = 0;
        while (head != NULL && head->valoareReala < interval + delta)
        {
            count++;
            head = head->next;
        }
        if (count != 0)
        {
            printf("[%d, %d] %d\n", interval, interval + delta, count);
        }
        interval += delta;
    }
    return initial_head;
}

// release the memory -- hard job here :)
void free_list(double_nod **head)
{
    while ((*head)->next != NULL)
    {
        double_nod *t = *head;
        *head = (*head)->next;
        free(t);
    }

    free(*head);
}