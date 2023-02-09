#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <stdio.h>

#define OPEN_ERROR -1

int main()
{
    FILE* fp;;
    if ((fp = fopen("test.txt", "r")) == NULL)
    {
        printf("Cannot open file.\n");
        return OPEN_ERROR;
    }

    int n = 0;
    fscanf(fp, "%d", &n);
    std::vector<int> as(200001, -1);

    for (int i = 0; i < n; i += 1) 
    {
        int idx = 0;
        fscanf(fp, "%d", &idx);
        as[idx] = n - i - 1;
    }

    std::cout << std::distance(as.begin(),
        std::max_element(as.begin(), as.end())) << "\n";

    fclose(fp);
}
