#!/Library/Frameworks/Python.framework/Versions/3.11/bin/python3

"""
Local testing tool for Homework Help.

Note: This tool is intended to help with debugging interaction.
It is *not* the same code used to test your solution when it
is submitted. For example, the tool *does not* apply the time
and memory limits that are applied to submitted solutions,
and there may be other differences, especially if your solution
exhibits incorrect behavior.

To run the testing tool, run::

    pypy3 testing_tool.py <filename> <program> <arguments>

where `arguments` are optional arguments to the program to run. The following
show examples for different languages:

    pypy3 testing_tool.py 1.in ./myprogram
    pypy3 testing_tool.py 1.in java -cp . MyProgram
    pypy3 testing_tool.py 1.in pypy3 myprogram.py

The file referenced in `filename` should contain two lines.
The first line should contain an integer n, the length of the permutation.
The second line should contain n integers, the permutation.
"""

import argparse
import subprocess
import sys
from typing import TextIO



class WrongAnswer(RuntimeError):
    """Raised whenever an incorrect answer is received."""
    pass

def vprint(*args, verbose: bool, file: TextIO, **kwargs) -> None:
    """Print to `file`, and also to stdout if `verbose is true."""
    if verbose:
        print('< ', end='')
        print(*args, **kwargs)
        sys.stdout.flush()
    print(*args, file=file, **kwargs)


def vreadline(data: TextIO, verbose: bool) -> str:
    """Read a line from `data`, and also log it to stdout if `verbose` is true."""
    line = data.readline()
    if verbose and line:
        print('>', line.rstrip('\n'))
    return line


def answer_query(process: subprocess.Popen, l: list[int], must_lis: bool) -> None:
    """Handle one query."""
    line = vreadline(process.stdout, True)
    if line == '':
        raise WrongAnswer('End of file received from team program')
    tokens = line.split()
    if tokens[0] == '!':
        try:
            if len(tokens) != 2:
                raise WrongAnswer("incorrect number of tokens in query")
            return int(tokens[1])
        except ValueError:
            raise WrongAnswer('Question contains non-integer tokens')
    if must_lis:
        raise WrongAnswer('tried to exceed n queries')
    if tokens[0] == '?':
        try:
            if len(tokens) != 3:
                raise WrongAnswer("incorrect number of tokens in query")
            lhs = int(tokens[1])
            rhs = int(tokens[2])
            lhs -= 1
            rhs -= 1
            if lhs > rhs or lhs < 0 or rhs >= len(l):
                raise WrongAnswer("Invalid query")
            numInversions = 0
            for i in range(lhs, rhs+1):
                for j in range(i+1, rhs+1):
                    if l[i] > l[j]:
                        numInversions += 1
            vprint(str(numInversions), file=process.stdin, flush=True, verbose=True)
            return None
        except ValueError:
            raise WrongAnswer('Question contains non-integer tokens')
    raise WrongAnswer('Invalid query format')

def check_done(process: subprocess.Popen) -> None:
    """Check for extra output from program."""
    line = vreadline(process.stdout, True)
    if line != '':
        raise WrongAnswer('Program gave extra output')


def main() -> int:
    parser = argparse.ArgumentParser(usage='%(prog)s [-h] filename program [args...]')
    parser.add_argument('filename', type=str, help='filename containing input')
    parser.add_argument('program', nargs=argparse.REMAINDER)

    args = parser.parse_args()
    if not args.program:
        parser.error('Must specify program to run')

    with open(args.filename, "r") as f:
        filelines = f.readlines()
        try:
            n = int(filelines[0])
            l = [int(x) for x in filelines[1].split()]
            assert len(l) == n, "second line does not contain n integers"
            for x in range(1, n+1):
                assert x in l, "{} not found in permutation".format(x)
        except Exception as e:
            print("ERROR: %s" % e)
            return 1

    process = subprocess.Popen(args.program, stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                               encoding='utf-8', errors='surrogateescape')
    
    try:
        vprint(str(n), file=process.stdin, flush=True, verbose=True)
        for i in range(n+1):
            lis_length = answer_query(process, l, i == n)
            if lis_length is not None:
                print("Your program asserts the length of the longest increasing subsequence is {}.".format(lis_length))
                break
        check_done(process)
    except WrongAnswer as e:
        print('ERROR: %s' % e)
        vprint("-1", file=process.stdin, flush=True, verbose=True)
        return 1
    except BrokenPipeError:
        print('ERROR: error when communicating with program - exited prematurely?')
        return 2
    
    return 0


if __name__ == '__main__':
    sys.exit(main())