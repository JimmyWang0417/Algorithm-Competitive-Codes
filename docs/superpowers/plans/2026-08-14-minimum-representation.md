# Minimum Representation Template Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add a reusable $O(n)$ minimum-representation template that returns the zero-based start of a string's lexicographically smallest cyclic rotation.

**Architecture:** Add one stateless `stringAlgorithm::minRep` struct beside the existing string templates. Its static `solve` operation adapts the already validated Booth-style scan from the standalone solution without changing the two existing segment-tree templates.

**Tech Stack:** C++23, standard library, `g++`, randomized differential testing

## Global Constraints

- Keep `Templates/dataStructure/dynamicSeg.hpp` unchanged.
- Keep `Templates/dataStructure/segDivide.hpp` unchanged.
- Keep `洛谷/P13270 【模板】最小表示法.cpp` unchanged and untracked.
- Do not add a string-hash template.
- Match the namespace, lower-camel-case type name, `static auto` interface, indentation, braces, and local-variable naming used by `Templates/stringAlgorithm/lyndon.hpp`.
- Return a zero-based starting position and return `0` for the empty string.
- Add no unrelated includes, comments, overloads, aliases, or helper abstractions.

---

### Task 1: Minimum Representation Header

**Files:**
- Create: `Templates/stringAlgorithm/minRep.hpp`
- Test: `/tmp/min_rep_test.cpp`
- Verify unchanged: `Templates/dataStructure/dynamicSeg.hpp`
- Verify unchanged: `Templates/dataStructure/segDivide.hpp`
- Verify unchanged: `洛谷/P13270 【模板】最小表示法.cpp`

**Interfaces:**
- Consumes: `const string &s`, with `string` supplied by the including competitive-programming translation unit, matching neighboring string headers.
- Produces: `static auto stringAlgorithm::minRep::solve(const string &s)`, returning the zero-based `int` start of the lexicographically smallest cyclic rotation.

- [x] **Step 1: Write the failing fixed-case and differential test**

Create `/tmp/min_rep_test.cpp` with:

```cpp
#include <bits/stdc++.h>
#include <cassert>
using namespace std;

#include "Templates/stringAlgorithm/minRep.hpp"

auto brute(const string &s)
{
    if (s.empty())
        return 0;
    int ans = 0;
    for (int i = 1; i < (int)s.size(); ++i)
    {
        string lhs = s.substr(i) + s.substr(0, i);
        string rhs = s.substr(ans) + s.substr(0, ans);
        if (lhs < rhs)
            ans = i;
    }
    return ans;
}

signed main()
{
    vector<pair<string, int>> fixed = {
        {"", 0},
        {"a", 0},
        {"aaaa", 0},
        {"abab", 0},
        {"baca", 3},
        {"caba", 1},
        {"baaa", 1},
        {"bba", 2},
    };
    for (const auto &[s, expected] : fixed)
        assert(stringAlgorithm::minRep::solve(s) == expected);

    mt19937 rnd(712367821);
    for (int n = 0; n <= 10; ++n)
        for (int test = 0; test < 10000; ++test)
        {
            string s(n, 'a');
            for (auto &c : s)
                c = (char)('a' + rnd() % 3);
            assert(stringAlgorithm::minRep::solve(s) == brute(s));
        }
}
```

- [x] **Step 2: Run the test to verify the template is missing**

Run:

```bash
g++ -std=c++23 -O2 -Wall -Wextra -pedantic -I. /tmp/min_rep_test.cpp -o /tmp/min_rep_test
```

Expected: compilation fails with `Templates/stringAlgorithm/minRep.hpp: No such file or directory`.

- [x] **Step 3: Implement the minimal style-compatible header**

Create `Templates/stringAlgorithm/minRep.hpp` with:

```cpp
namespace stringAlgorithm
{
    struct minRep
    {
        static auto solve(const string &s)
        {
            int n = (int)s.size();
            int i = 0, j = 1, k = 0;
            while (i < n && j < n && k < n)
            {
                if (s[(i + k) % n] == s[(j + k) % n])
                    ++k;
                else
                {
                    if (s[(i + k) % n] > s[(j + k) % n])
                        i += k + 1;
                    else
                        j += k + 1;
                    if (i == j)
                        ++j;
                    k = 0;
                }
            }
            return min(i, j);
        }
    };
}
```

- [x] **Step 4: Compile and run the fixed-case and randomized tests**

Run:

```bash
g++ -std=c++23 -O2 -Wall -Wextra -pedantic -I. /tmp/min_rep_test.cpp -o /tmp/min_rep_test
/tmp/min_rep_test
```

Expected: compilation succeeds with no warnings and the executable exits with status `0` and no output.

- [x] **Step 5: Verify scope and formatting**

Run:

```bash
git diff --check
git diff -- Templates/stringAlgorithm/minRep.hpp
git diff --exit-code HEAD -- Templates/dataStructure/dynamicSeg.hpp Templates/dataStructure/segDivide.hpp
git status --short
```

Expected: no whitespace errors; the only implementation diff is the new `minRep.hpp`; both existing segment-tree headers have no diff; the standalone solution remains an untracked file.

- [x] **Step 6: Commit the implementation and plan**

```bash
git add Templates/stringAlgorithm/minRep.hpp docs/superpowers/plans/2026-08-14-minimum-representation.md
git commit -m "feat: add minimum representation template"
```

Expected: the commit contains exactly the new template header and this implementation plan.
