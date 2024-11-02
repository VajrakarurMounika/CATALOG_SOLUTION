#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Function to convert a number from any base to decimal
int convertToDecimal(char* value, int base) {
    int decimalValue = 0;
    int power = 1;  // Initialize power of base (base^0)
    int len = strlen(value);

    // Process each digit from right to left
    for (int i = len - 1; i >= 0; i--) {
        int digit;
        if (value[i] >= '0' && value[i] <= '9') {
            digit = value[i] - '0';
        } else if (value[i] >= 'A' && value[i] <= 'F') {
            digit = value[i] - 'A' + 10;
        } else if (value[i] >= 'a' && value[i] <= 'f') {
            digit = value[i] - 'a' + 10;
        } else {
            printf("Invalid character in number\n");
            exit(1);
        }

        if (digit >= base) {
            printf("Invalid digit for the given base\n");
            exit(1);
        }

        decimalValue += digit * power;
        power *= base;
    }
    return decimalValue;
}

// Function to perform Lagrange interpolation at x = 0
double lagrangeInterpolation(int x[], int y[], int k) {
    double result = 0.0;
    for (int i = 0; i < k; i++) {
        double term = y[i];
        for (int j = 0; j < k; j++) {
            if (i != j) {
                term *= (0.0 - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }
    return result;
}

int main() {
    int n, k;

    printf("Enter the total number of points (n): ");
    scanf("%d", &n);
    printf("Enter the minimum number of points required (k): ");
    scanf("%d", &k);

    int x[n];
    int y[n];

    // Reading points dynamically
    for (int i = 0; i < n; i++) {
        printf("Enter x value for point %d: ", i + 1);
        scanf("%d", &x[i]);

        int base;
        printf("Enter base for y value for point %d: ", i + 1);
        scanf("%d", &base);

        char value[256];
        printf("Enter y value in base %d for point %d: ", base, i + 1);
        scanf("%s", value);

        // Convert y value from specified base to decimal
        y[i] = convertToDecimal(value, base);
    }

    // Perform Lagrange interpolation at x = 0 to find the constant term
    double constantTerm = lagrangeInterpolation(x, y, k);
    printf("The constant term (secret) is: %.0f\n", constantTerm);

    return 0;
}
