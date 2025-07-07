#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 32768

int main() {
    int n;
    char filename[100];
    float minX, maxX, minY, maxY;

    printf("Enter number of points (e.g., 64, 128, ..., 32768): ");
    scanf("%d", &n);
    if (n < 1 || n > MAX_N) {
        printf("Invalid number of points.\n");
        return 1;
    }

    printf("Enter x-coordinate range (min max): ");
    scanf("%f %f", &minX, &maxX);

    printf("Enter y-coordinate range (min max): ");
    scanf("%f %f", &minY, &maxY);

    printf("Enter output filename (e.g., test-input.txt): ");
    scanf("%s", filename);

    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("Error opening file.\n");
        return 1;
    }

    srand((unsigned int) time(NULL)); // Seed RNG
    fprintf(f, "%d\n", n);

    for (int i = 0; i < n; i++) {
        double x = minX + ((double)rand() / RAND_MAX) * (maxX - minX);
        double y = minY + ((double)rand() / RAND_MAX) * (maxY - minY);
        fprintf(f, "%.6lf %.6lf\n", x, y);
    }

    fclose(f);
    printf("File '%s' with %d points generated successfully.\n", filename, n);
    
    return 0;
}
