from fractions import Fraction

T = int(input())

for _ in range(T):
    x = Fraction(int(input()))

    x += x * Fraction(8, 10) * Fraction(3, 4)
    x += x * Fraction(3, 10) * Fraction(5, 6)

    print(round(x))
