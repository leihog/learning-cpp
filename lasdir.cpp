#include <dirent.h>
#include <stdio.h>
#include <iostream>

int main ()  {
    struct dirent **namelist;
    int n;

    n = scandir(".", &namelist, 0, alphasort);
    if (n < 0)
        cout << "no files in directory" << endl;
    else
        while(n--) printf("%s\n", namelist[n]->d_name);

} 
