# Minimum Representation Template Design

## Goal

Add a reusable minimum-representation template that follows the existing `Templates/stringAlgorithm` code and naming style.

## Scope

- Keep `Templates/dataStructure/dynamicSeg.hpp` unchanged because it already provides segment-tree merge and split operations.
- Keep `Templates/dataStructure/segDivide.hpp` unchanged because it already provides segment-tree divide and conquer.
- Add `Templates/stringAlgorithm/minRep.hpp` for minimum representation.
- Do not add a string-hash template in this change.
- Do not modify the standalone solution `洛谷/P13270 【模板】最小表示法.cpp`.

## Interface

The new header defines `stringAlgorithm::minRep`, matching the namespace and lower-camel-case struct naming used by the other string templates.

It exposes one stateless entry point:

```cpp
static auto solve(const string &s)
```

`solve` returns the zero-based starting position of the lexicographically smallest cyclic rotation of `s`. For an empty string, it returns `0`.

## Algorithm

Use the same Booth-style two-candidate scan as the standalone solution. Maintain candidate starts `i` and `j` and their current common-prefix length `k`. When the compared characters differ, discard the larger candidate together with the already matched prefix, keep the two candidates distinct, and restart comparison with `k = 0`.

The implementation runs in $O(n)$ time and uses $O(1)$ auxiliary space, where $n = s.size()$ is the string length.

## Style

- Use `namespace stringAlgorithm` and `struct minRep`.
- Use `static auto` for the stateless operation, consistent with `lyndon::duval`.
- Use `const string &s`, local variables `i`, `j`, `k`, and explicit `(int)s.size()` conversion, consistent with nearby string templates.
- Do not add unrelated includes, comments, overloads, aliases, or helper abstractions.

## Verification

- Compile a small translation unit that includes the new header after `<bits/stdc++.h>`.
- Check fixed cases covering an empty string, a one-character string, equal characters, periodic strings, and rotations whose minimum begins near the end.
- Randomly compare `minRep::solve` against exhaustive rotation enumeration for short strings.
- Confirm `git diff` contains no changes to the existing line-segment-tree templates or the standalone solution.
