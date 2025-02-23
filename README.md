# TIMES
### **Processor:** [Intel® Core™ i5-10400](https://www.intel.com/content/www/us/en/products/sku/199271/intel-core-i510400-processor-12m-cache-up-to-4-30-ghz/specifications.html)
#### average execution time, n = 5
#### O2 / O3
|Puzzle|Time|Time Complexity|
|---|---|---|
|1-1|0.001 s|$O(n\ \log{n})$|
|1-2|0.001 s|$O(n^2)$|
|2-1|0.001 s|$O(n)$|
|2-2|0.001 s|$O(n^3)$|
|3-1|0.001 s|$O(n)$|
|3-2|0.001 s|$O(n)$|
|4-1|0.001 s|$O(n^2)$|
|4-2|0.001 s|$O(n^2)$|
|5-1|0.002 s|$O(n)$|
|5-2|0.002 s|$O(n^2)$|
|6-1|0.001 s|$O(n^2)$|
|6-2|0.243 s|$O(n^3)$|
|7-1|0.011 s|$O(nk^{n})$|
|7-2|11.168 s|$O(nk^{n})$|
|8-1|0.002 s|$O(n^2)$|
|8-2|0.001 s|$O(n^3)$|
|9-1|0.047 s|$O(n)$|
|9-2|0.136 s|$O(n^2)$|
|10-1|0.013 s|$O(n^2)$|
|10-2|0.002 s|$O(n^2)$|
|11-1|0.002 s|$O(\log(biggest stone)^2)$|
|11-2|0.031 s|$O(\log(biggest stone)^2)$|
|12-1|0.005 s|$O(n)$|
|12-2|0.002 s|$O(n)$|
|13-1|0.002 s|$O(n)$|
|13-2|0.004 s|$O(n)$|
|14-1|0.002 s|$O(n)$|
|14-2|#####[^1] s|$O(nt)$| 
|15-1|0.002 s|$O(kn)$|
|15-2|0.002 s|$O(kn)$|
|16-1|0.006 s|$O(n\log{n})$|
|16-2|0.005 s|$O(n\log{n})$|
|17-1|0.002 s|$O(n)$|
|17-2|0.005 s|$O(n)$|
|18-1|0.012 s|$O(V+E(\log(V))$|
|18-2|5.630 s|$O(n(V+E(\log(V)))$|
|19-1|0.053 s|$O(DP^n)$[^2]$|
|19-2|0.134 s|$O(nDP^n)$|
|20-1|1.277 s|$O((nm)^2 \log{nm})$|
|20-2|0.065 s|$O((nm)^2)$|
|21-1|~12 hours [^3]|$O(\text{idk})$|
|21-2|UNFINISHED|
|22-1|0.013 s|$O(n)$|
|22-2|0.020 s|$O(n)$|
|23-1|0.015 s|$O(n^3)$|
|23-2|0.417 s|$O(3^{\frac{n}{3}})$|
|24-1|0.015 s[^4]|$O(n^2)$|
|24-2|0.016 s|$O(n^2)$|
|25-1|0.004 s|$O(n^2)$|

[^1]: The execution time in ms is the solution.
[^2]: D is the number of designs, P is the number of patterns, n is the length of the patterns
[^3]: In hindsight, I don't really know what I was thinking.
[^4]: Works on g++ 14
