# [DAY 13](https://adventofcode.com/2024/day/13)
$
\begin{bmatrix}
a_1 & b_1\\
a_2 & b_2\end{bmatrix}
\begin{bmatrix}
x\\y\end{bmatrix}=
\begin{bmatrix}
c_1\\c_2\end{bmatrix}$

$x_0 =\frac{
\begin{vmatrix}
c_1 & b_1 \\
c_2 & b_2
\end{vmatrix}}{
\begin{vmatrix}
a_1 & b_1 \\
a_2 & b_2
\end{vmatrix}} = \frac{c_1b_2-b_1c_2}{a_1b_2-b_1a_2}$

$y_0 =\frac{
\begin{vmatrix}
a_1 & c_1 \\
a_2 & c_2
\end{vmatrix}}{
\begin{vmatrix}
a_1 & b_1 \\
a_2 & b_2
\end{vmatrix}} = \frac{a_1c_2-c_1a_2}{a_1b_2-b_1a_2}$

The solution lies at $(x_0,y_0)$, as long as it satisfies both price conditions
