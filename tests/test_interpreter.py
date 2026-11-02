import subprocess

import sys

INTERPRETER_BINARY = "../interpreter"

def run_interpreter(input_data: str) -> str:
    process = subprocess.Popen(
        [INTERPRETER_BINARY],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    stdout, stderr = process.communicate(input_data)
    return stdout.strip(), stderr.strip()

def clean_output(output: str) -> str:

    lines = output.splitlines()
    cleaned = []
    for line in lines:
        line = line.strip()
        if line.startswith('> '):
            line = line[2:].strip()
        elif line == '>':
            continue
        if line:
            cleaned.append(line)
    return "\n".join(cleaned)

def test_interpreter():
    tests = [
        {
            "input": "5 + 3 * 2\n",
            "expected_output": "11"
        },
        {
            "input": "(5 + 3) * 2\n",
            "expected_output": "16"
        },
        {
            "input": "max(5, 2)\n",
            "expected_output": "5"
        },
        {
            "input": "min(3, 4)\n",
            "expected_output": "3"
        },
        {
            "input": "pow(2, 4)\n",
            "expected_output": "16"
        },
        {
            "input": "abs(-7)\n",
            "expected_output": "7"
        },
        {
            "input": "var a = 5 + 2\n",
            "expected_output": "7"
        },
        {
            "input": "var a = max(min(3 * 2, 2), 2)\n a + 3\n",
            "expected_output": "2\n5"
        }
    ]

    passed = 0
    for i, test in enumerate(tests, 1):
        raw_output, error = run_interpreter(test["input"])
        cleaned_output = clean_output(raw_output)

        if not error and cleaned_output == test["expected_output"].strip():
            print(f"[pass] test {i}")
            passed += 1
        else:
            print(f"[FAIL] test {i}")
            if error:
                print(f"  error: {error}")
            else:
                print(f"  expected: {test['expected_output']!r}")
                print(f"  got:      {cleaned_output!r}")

    print(f"\n{passed} of {len(tests)} tests passed.")
    sys.exit(0 if passed == len(tests) else 1)

if __name__ == "__main__":
    test_interpreter()
