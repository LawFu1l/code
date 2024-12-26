#!/usr/bin/env ruby


def fib(n)
  return 1 if n == 0
  return 1 if n == 1
  return fib(n-1) + fib(n-2)
end

def fib_new(n)
  cache = [1, 1]
  return 1 if n < 2
  for i in 2..n
    cache.append(cache[i-1] + cache[i-2])
  end

  cache[n]
end

for i in 1..4000
   puts "fib #{i} = #{fib_new(i)}"
end

