import math

def est_divisible_par(n, k):
    if(n%k == 0):
        return True
    return False

def est_paire(q):
    return est_divisible_par(q, 2)

def est_compris_dans(a, b, c):
    return (b < a < c or c < a < b)
