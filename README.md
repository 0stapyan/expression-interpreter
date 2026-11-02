# Expression Interpreter

A small interpreter for arithmetic expressions, written in C++. It reads expressions from a REPL, supports variables and built-in functions, and evaluates them with correct operator precedence. The parser is a hand-written recursive-descent parser — no parser generator or library.

## What it does

```
> var x = 5 + 2
7
> x * 3
21
> max(min(10, 4), 2)
4
> (1 + 2) * pow(2, 3)
24
> 10 / 0
Error: Division by zero
```

- **Arithmetic** with `+`, `-`, `*`, `/` and parentheses, with the usual precedence (`*` and `/` bind tighter than `+` and `-`).
- **Variables** — `var name = expression` stores a value; the name can then be used in later expressions.
- **Built-in functions** — `max`, `min`, `pow` (two arguments) and `abs` (one argument).
- **Errors** are reported for division by zero, unknown identifiers and functions, wrong argument counts, and malformed input, without crashing the REPL.

## Grammar

The parser implements this grammar, with one method per rule. Precedence falls out of the nesting: `expression` handles `+`/`-`, `term` handles `*`/`/`, and `factor` handles the atoms, so lower-precedence operators sit higher in the call tree.

```
statement   = "var" identifier "=" expression
            | expression
expression  = term { ("+" | "-") term }
term        = factor { ("*" | "/") factor }
factor      = "(" expression ")"
            | identifier [ "(" arguments ")" ]   // variable or function call
            | number
arguments   = expression { "," expression }
```

## Design

| Part | Responsibility |
| --- | --- |
| `Parser` | Tokenises and evaluates an expression in one pass via recursive descent; also holds the table of built-in functions |
| `Environment` | Stores variables and looks them up, raising an error for undefined names |
| `Interpreter` | Ties them together: one `Environment` persists across lines, each line gets a fresh `Parser` |
| `main` | The read-eval-print loop |

The parser evaluates as it parses (a tree-walking evaluator without building an explicit AST), which keeps it compact while still honouring precedence and associativity.

## Build and run

```bash
make            # builds ./interpreter
./interpreter   # starts the REPL; Ctrl+D to exit
```

## Tests

```bash
make test
```

The tests (`tests/test_interpreter.py`) drive the compiled interpreter as a subprocess and check its output against expected results, covering precedence, parentheses, each built-in function, and variable definitions.

## License

[MIT](LICENSE)
