def is_prime(n):
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6
    return True

def print_prime_numbers(limit):
    if limit < 2:
        print("There are no prime numbers up to", limit)
    else:
        print("Prime numbers up to", limit, "are:")
        for num in range(2, limit + 1):
            if is_prime(num):
                print(num, end=" ")

limit = int(input("Enter the limit for prime numbers: "))
print_prime_numbers(limit)



o/p:
Enter the limit for prime numbers: 50
Prime numbers up to 50 are:
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47
