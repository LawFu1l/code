#!/usr/bin/env python3

# fib (n) 은 배열의 n번째 인덱스를 반환한다.배열의 크기는 n + 1

def fib(n):
    num_list = [1, 1]
        # 3을 받았다고 치자.
    if n < 0:
        raise IndexError("음수 인덱스 불가")
    if n < 2:
        return num_list[n]

    for i in range(2, n+1):
        num_list.append(num_list[i-1] + num_list[i -2])

    return num_list[i]

a = int(input())
result = fib(a)
print(result)
