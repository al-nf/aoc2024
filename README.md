# TIMES
### **Processor:** [Intel® Core™ i5-10400](https://www.intel.com/content/www/us/en/products/sku/199271/intel-core-i510400-processor-12m-cache-up-to-4-30-ghz/specifications.html)
#### average execution time, n = 5
#### no extra compiler optimisations
|Puzzle|Time|Time Complexity|
|---|---|---|
|1-1|0.001 s|$O(n\ \log{n})$|
|1-2|0.011 s|$O(n^2)$|
|2-1|0.003 s|$O(n)$|
|2-2|0.001 s|$O(n^3)$|
|3-1|0.001 s|$O(n)$|
|3-2|0.001 s|$O(n)$|
|4-1|0.001 s|$O(n^2)$|
|4-2|0.001 s|$O(n^2)$|
|5-1|0.007 s|$O(n)$|
|5-2|0.003 s|$O(n^2)$|
|6-1|0.004 s|$O(n^2)$|
|6-2|0.669 s|$O(n^3)$|
|7-1|0.026 s|$O(nk^{n})$|
|7-2|28.802 s|$O(nk^{n})$|
|8-1|0.007 s|$O(n^2)$|
|8-2|0.007 s|$O(n^3)$|
|9-1|0.071 s|$O(n)$|
|9-2|1.585 s|$O(n^2)$|
|10-1|0.069 s|$O(n^2)$|
|10-2|0.005 s|$O(n^2)$|
|11-1|0.004 s|$O(\log(biggest stone)^2)$|
|11-2|0.117 s|$O(\log(biggest stone)^2)$|
|12-1|0.032 s|$O(n)$|
|12-2|0.018 s|$O(n)$|
|13-1|0.030 s|$O(n)$|
|13-2|0.012 s|$O(n)$|
|14-1|0.005 s|$O(n)$|
|14-2|#####[^1] s|$O(nt)$| 
|15-1|0.009 s|$O(kn)$|
|15-2|0.004 s|$O(kn)$|
|16-1|0.068 s|$O(n\log{n})$|
|16-2|0.030 s|$O(n\log{n})$|
|17-1|0.005 s|$O(n)$|
|17-2|0.007 s|$O(n)$|
|18-1|0.030 s|$O(V+E(\log(V))$|
|18-2|5.669 s|$O(n(V+E(\log(V)))$|
|19-1|0.087 s|$O(DP^n)[^2]$|
|19-2|0.307 s|$O(nDP^n)[^2]$|

[^1]: The execution time is the solution.
[^2]: D is the number of designs, P is the number of patterns, n is the length of the patterns
