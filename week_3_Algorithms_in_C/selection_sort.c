/*
Sorting avarage temperture with selection sort algorithm
*/

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
}
avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities_select_sort(void);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities_select_sort();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// Sort cities by temperature in ascending order
// with selection sort algorithm
void sort_cities_select_sort(void)
{
    // iterate the whole unsorted array
    for (int i = 0; i < NUM_CITIES - 1; i++)
    {
        // find min in unsorted array
        int min_index = i;
        for (int j = i + 1; j < NUM_CITIES; j++)
        {
            if (temps[j].temp < temps[min_index].temp)
                min_index = j;
        }

        // swap the found min with the
        // first element in the unsorted part
        avg_temp temps_swap = temps[min_index];
        temps[min_index] = temps[i];
        temps[i] = temps_swap;
    }
}

