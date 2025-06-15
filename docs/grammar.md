$$

\begin{align}
[\text{prog}] &\to [\text{stmt}]^*
\\
[\text{stmt}] &\to
    \begin{cases}
        [\text{exit}([{\text{expr}}]);
        \\
        let\space \text{ident} = [\text{expr}];
    \end{cases}  
\\

\\
[\text{expr}] &\to \text{int\_lit}
\end{align}
$$