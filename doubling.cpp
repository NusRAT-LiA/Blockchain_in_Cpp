// Define prime field modulus
const int p = ...;

double y1, y2, m, yint;
double x3, y3;

// Calculate corresponding y1 and y2
double x1_cubed = fmod(pow(x1, 3) + a*x1 + b, p);
double x2_cubed = fmod(pow(x2, 3) + a*x2 + b, p);
y1 = fmod(sqrt(x1_cubed), p);
y2 = fmod(sqrt(x2_cubed), p);

// Calculate slope and y-intercept of line
if (x1 == x2) {
    // If P and Q are the same point, use tangent line approximation
    double numerator = 3*pow(x1,2)+a;
    double denominator = 2*y1;
    denominator = fmod(denominator, p);
    double inverse = modularInverse(denominator, p);
    m = fmod(numerator * inverse, p);
} else {
    // Otherwise, use standard formula
    double numerator = y2-y1;
    double denominator = x2-x1;
    denominator = fmod(denominator, p);
    double inverse = modularInverse(denominator, p);
    m = fmod(numerator * inverse, p);
}

yint = fmod(y1 - (m*x1), p);

// Calculate x3 and y3
x3 = fmod(pow(m,2) - x1 - x2, p);
double x3_cubed = fmod(pow(x3, 3) + a*x3 + b, p);
y3 = fmod(sqrt(x3_cubed), p);

// Adjust y3 to ensure it lies on the line
if (fmod(y3, p) != fmod(m*x3 + yint, p)) {
    y3 = fmod(-y3, p);
}
