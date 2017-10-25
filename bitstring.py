#!/usr/bin/env python3

from itertools import accumulate

def f(ta, n, bits):
  an = []
  for i in ta:
    l = list(accumulate(i[::-1]))[::-1]
    l = l[1::] + [0]
    an.append(l)
  
  ma = []
  for i in range(n):
    for j in range(len(ta[i])):
        t = ta[i][j]
        a = an[i][j]
        v = (2 ** t - 1) << a
        ma.append(v)

  nm = []
  for i in range(n):
    for j in range(len(ta[i])):
        t = ta[i][j]
        a = an[i][j]
        v = (2 ** bits - 1) - ((2 ** t - 1) << a)
        nm.append(v)

  print("TA:", ta)
  print("AN:", an)
  print("MA:", ma)
  print("NM:", nm)

def main():
  # Humano
  ta = [[7, 1], 
        [2, 11, 19], 
        [24, 6, 2]]
  n = 3
  bits = 32
  
  print("Humano:")
  f(ta, n, bits)  


if __name__ == '__main__': main()
