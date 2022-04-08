#include "linkedlist.h"

int main()
{
    /* Declare and initialize LL */
    t_ll ll;
    ll_create(&ll);

    /* Example of data insertion using LL */
    for(int i = 0; i < 50; i++)
        ll_insert(&ll, i, ASCENDING);

    /* Examples of data extraction using LL */
    for(int i = 21; i < 31; i++)
    {
        ll_extract(&ll, i, SEARCH_KEY);
    }
    for(int i = 0; i < 10; i++)
    {
        ll_extract(&ll, NO_KEY, POP);
        ll_extract(&ll, NO_KEY, EXTRACT_TAIL);
    }

    /* Shows size and elements inside LL */
    ll_print(&ll);

    /* Frees memory - avoid leaks */
    ll_destroy(&ll);

    return 0;
}