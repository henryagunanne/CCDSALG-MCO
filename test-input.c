#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 32768

int main() {
    int n;
    char filename[100];

    printf("Enter number of points (e.g., 64, 128, ..., 32768): ");
    scanf("%d", &n);
    if (n < 1 || n > MAX_N) {
        printf("Invalid number of points.\n");
        return 1;
    }

    printf("Enter output filename (e.g., test-input.txt): ");
    scanf("%s", filename);

    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("Error opening file.\n");
        return 1;
    }

    srand(time(NULL));
    fprintf(f, "%d\n", n);

    for (int i = 0; i < n; i++) {
        double x = ((double)rand() / RAND_MAX) * 1000.0;
        double y = ((double)rand() / RAND_MAX) * 1000.0;
        fprintf(f, "%.6lf %.6lf\n", x, y);
    }

    fclose(f);
    printf("File '%s' with %d points generated successfully.\n", filename, n);
    return 0;
}
