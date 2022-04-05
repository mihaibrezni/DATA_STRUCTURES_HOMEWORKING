#ifndef CRY_EVERY_DAY
#define CRY_EVERY_DAY

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct double_nod
{
    int time_stamp;
    double valoareReala;
    struct double_nod *next;
    struct double_nod *prev;
} double_nod;

double_nod *CreateDoubleList(double_nod *head, int n);

void RemoveExceptions(double_nod *head, int *n);

void free_list(double_nod **head);

void PrintList(double_nod *head);

/* =====================E2=====================*/

double_nod *FiltrareMediana(double_nod *head, int *n);

/* +++++++++++++++++++++++++++++E3++++++++++++++++++++++ */

double_nod *FiltrareAritmetica(double_nod *head, int *n);

/* ============================U========================= */
double_nod *UniformizareFrecvente(double_nod *head, int *n);

/* -------------------------C------------------------- */
double_nod *CompletareDate(double_nod *head, int *n);

/* ============================== st ======================== */

double_nod *statistici(double_nod *head, int *n, int interval);

#endif
