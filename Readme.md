# Armazenar e consultar dados

Um arquivo chamado "matriculas.txt" contém uma relação de números de matrícula e nome de estudantes. Cada linha desse arquivo tem este formato:

```
numero,Nome de Uma Pessoa
```

Escreva um programa que leia os dados desse arquivo e os armazene em uma árvore de pesquisa binária. Em seguida, seu programa deve entrar em um loop. Em cada ciclo do loop o programa apresenta este prompt:

```
Digite matricula>
```

... e aguardar que seja fornecido um número de matrícula pelo teclado. Ao ler a matrícula, deve-se apresentar na tela o nome do estudante neste formato:

```
Estudante: Um Nome de Um Estudante
```

Se em vez de uma matrícula for teclado ENTER, o programa deve terminar. Se uma matrícula desconhecida for digitada, seu programa deve apresentar esta mensagem:

```
Matricula MATRICULA_DIGITADA desconhecida
```

Seu programa será testado com diferentes números de consultas.