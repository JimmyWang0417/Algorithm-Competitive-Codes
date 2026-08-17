# Template Naming Migration And String Hash Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Complete the approved conservative naming migration across `Templates` and add the QOJ-derived `Hash<mod>` string-hash template.

**Architecture:** First move every approved directory and file to its clean-break final path, then rename only approved multiword types and their references. Add the hash implementation directly under the final string-algorithm directory, then regenerate the repository README and verify paths, declarations, compilation, and hash behavior.

**Tech Stack:** C++23, GNU g++, Git, Python 3, `rg`, `lsd`, `tokei`.

## Global Constraints

- Multiword directories and files use `snake_case`; multiword `class` and `struct` types use `PascalCase`.
- Single-word directories, files, and types remain unchanged.
- Functions, variables, fields, macros, namespaces, algorithms, data layouts, and public method signatures remain unchanged.
- This is a clean break: do not add forwarding headers, type aliases, compatibility namespaces, or duplicate old paths.
- Keep `lichao`, `min25`, `acam`, `exkmp`, and `exsam` unchanged.
- Keep the namespace spellings `dataStructure`, `stringAlgorithm`, and `networkFlow` unchanged.
- Do not modify the source QOJ solution.
- The new string hash uses `base = 13331`, adds `s[i]` directly, and does not cast to `unsigned char`.

---

### Task 1: Normalize Template Directory And File Paths

**Files:**
- Rename: `Templates/dataStructure` to `Templates/data_structure`
- Rename: `Templates/stringAlgorithm` to `Templates/string_algorithm`
- Rename: `Templates/initialization & misc` to `Templates/initialization_misc`
- Rename: `Templates/graph/networkFlow` to `Templates/graph/network_flow`
- Rename: every multiword file listed in the approved design document
- Modify: `Templates/data_structure/segment_tree_beats.hpp`
- Modify: `Templates/math/polynomial.hpp`

**Interfaces:**
- Consumes: the exact path mapping in `docs/superpowers/specs/2026-08-17-template-naming-migration-design.md`
- Produces: final include paths used by Tasks 2-4

- [ ] **Step 1: Verify the migration starts from the old paths**

Run:

```bash
test -d Templates/dataStructure
test -d Templates/stringAlgorithm
test -d 'Templates/initialization & misc'
test -d Templates/graph/networkFlow
test ! -e Templates/data_structure
test ! -e Templates/string_algorithm
test ! -e Templates/initialization_misc
test ! -e Templates/graph/network_flow
```

Expected: all commands exit successfully.

- [ ] **Step 2: Rename the four directories**

Run:

```bash
git mv Templates/dataStructure Templates/data_structure
git mv Templates/stringAlgorithm Templates/string_algorithm
git mv 'Templates/initialization & misc' Templates/initialization_misc
git mv Templates/graph/networkFlow Templates/graph/network_flow
```

- [ ] **Step 3: Rename the approved multiword files**

Run:

```bash
git mv Templates/data_structure/cartesianTree.hpp Templates/data_structure/cartesian_tree.hpp
git mv Templates/data_structure/decompTree.hpp Templates/data_structure/decomp_tree.hpp
git mv Templates/data_structure/dynamicSeg.hpp Templates/data_structure/dynamic_seg.hpp
git mv Templates/data_structure/fhqTreap.hpp Templates/data_structure/fhq_treap.hpp
git mv Templates/data_structure/implicitTreap.hpp Templates/data_structure/implicit_treap.hpp
git mv Templates/data_structure/linkCutTree.hpp Templates/data_structure/link_cut_tree.hpp
git mv Templates/data_structure/persistImplicitTreap.hpp Templates/data_structure/persist_implicit_treap.hpp
git mv Templates/data_structure/persistSeg.hpp Templates/data_structure/persist_seg.hpp
git mv Templates/data_structure/persistTreap.hpp Templates/data_structure/persist_treap.hpp
git mv Templates/data_structure/scanlineSeg.hpp Templates/data_structure/scanline_seg.hpp
git mv Templates/data_structure/segBeats.hpp Templates/data_structure/seg_beats.hpp
git mv Templates/data_structure/segDivide.hpp Templates/data_structure/seg_divide.hpp
git mv Templates/data_structure/segTree.hpp Templates/data_structure/seg_tree.hpp
git mv Templates/data_structure/segmentTreeBeats.hpp Templates/data_structure/segment_tree_beats.hpp
git mv Templates/data_structure/topTree.hpp Templates/data_structure/top_tree.hpp
git mv Templates/graph/blockForest.hpp Templates/graph/block_forest.hpp
git mv Templates/graph/eulerTour.hpp Templates/graph/euler_tour.hpp
git mv Templates/graph/minCycle.hpp Templates/graph/min_cycle.hpp
git mv Templates/graph/ringCount.hpp Templates/graph/ring_count.hpp
git mv Templates/graph/steinerTree.hpp Templates/graph/steiner_tree.hpp
git mv Templates/graph/stoerWagner.hpp Templates/graph/stoer_wagner.hpp
git mv Templates/graph/network_flow/networkFlow.hpp Templates/graph/network_flow/network_flow.hpp
git mv Templates/graph/network_flow/minCostFlow.hpp Templates/graph/network_flow/min_cost_flow.hpp
git mv Templates/math/berlekampMassey.hpp Templates/math/berlekamp_massey.hpp
git mv Templates/math/duSieve.hpp Templates/math/du_sieve.hpp
git mv Templates/math/linearBasis.hpp Templates/math/linear_basis.hpp
git mv Templates/math/numberTheory.hpp Templates/math/number_theory.hpp
git mv Templates/math/schreierSims.hpp Templates/math/schreier_sims.hpp
git mv Templates/math/setPowerSeries.hpp Templates/math/set_power_series.hpp
git mv Templates/math/polynomial/linearRecurrence.hpp Templates/math/polynomial/linear_recurrence.hpp
git mv Templates/string_algorithm/minRep.hpp Templates/string_algorithm/min_rep.hpp
git mv Templates/geometry/nearestPoints.cpp Templates/geometry/nearest_points.cpp
git mv Templates/initialization_misc/hashTable.hpp Templates/initialization_misc/hash_table.hpp
```

- [ ] **Step 4: Update the two internal includes**

Change `Templates/data_structure/segment_tree_beats.hpp` to:

```cpp
#pragma once
#include "seg_beats.hpp"
```

Change `Templates/math/polynomial.hpp` to:

```cpp
#pragma once
#include "polynomial/linear_recurrence.hpp"
```

- [ ] **Step 5: Verify every final path and removed path**

Run `find Templates -type f | sort` and compare it with the approved mapping. Then run:

```bash
rg -n 'dataStructure/|stringAlgorithm/|initialization & misc|networkFlow/|segBeats\.hpp|linearRecurrence\.hpp' . --glob '!README.md' --glob '!docs/**'
```

Expected: no output. Namespace identifiers without a slash are allowed to remain.

- [ ] **Step 6: Commit the path migration**

```bash
git add Templates
git commit -m "refactor: normalize template paths"
```

### Task 2: Rename Approved Multiword Types

**Files:**
- Modify: renamed headers under `Templates/data_structure`, `Templates/graph`, `Templates/math`, `Templates/string_algorithm`, and `Templates/initialization_misc`

**Interfaces:**
- Consumes: final paths from Task 1
- Produces: the exact PascalCase type names from the design document

- [ ] **Step 1: Confirm old declarations still exist before the edit**

Run:

```bash
rg -n 'struct (cartesianTree|decompTree|dynamicSeg|fhqTreap|implicitTreap|linkCutTree|persistImplicitTreap|persistSeg|persistTreap|scanlineSeg|segBeats|segDivide|segTree|blockForest|eulerTour|minCostFlow|networkFlow|ringCount|stoerWagner|duSieve|duSieveMuPhi|linearBasis|numberTheory|schreierSims|setPowerSeries|hashTableBase|hashTable|suffixArray|minRep)\b' Templates
```

Expected: declarations from the approved mapping are reported.

- [ ] **Step 2: Apply file-local mechanical type replacements**

Replace every whole-word spelling below in its owning header, including constructors, inheritance, return types, local objects, and self-references:

```text
cartesianTree -> CartesianTree
decompTree -> DecompTree
dynamicSeg -> DynamicSeg
fhqTreap -> FhqTreap
implicitTreap -> ImplicitTreap
linkCutTree -> LinkCutTree
persistImplicitTreap -> PersistImplicitTreap
persistSeg -> PersistSeg
persistTreap -> PersistTreap
scanlineSeg -> ScanlineSeg
segBeats -> SegBeats
segDivide -> SegDivide
segTree -> SegTree
blockForest -> BlockForest
eulerTour -> EulerTour
minCostFlow -> MinCostFlow
ringCount -> RingCount
stoerWagner -> StoerWagner
duSieveMuPhi -> DuSieveMuPhi
duSieve -> DuSieve
linearBasis -> LinearBasis
numberTheory -> NumberTheory
schreierSims -> SchreierSims
setPowerSeries -> SetPowerSeries
hashTableBase -> HashTableBase
hashTable -> HashTable
suffixArray -> SuffixArray
minRep -> MinRep
```

In `Templates/graph/network_flow/network_flow.hpp`, change only `struct networkFlow` to `struct NetworkFlow`; keep `namespace networkFlow` unchanged.

- [ ] **Step 3: Verify declarations and namespaces**

Run:

```bash
rg -n 'struct (cartesianTree|decompTree|dynamicSeg|fhqTreap|implicitTreap|linkCutTree|persistImplicitTreap|persistSeg|persistTreap|scanlineSeg|segBeats|segDivide|segTree|blockForest|eulerTour|minCostFlow|networkFlow|ringCount|stoerWagner|duSieve|duSieveMuPhi|linearBasis|numberTheory|schreierSims|setPowerSeries|hashTableBase|hashTable|suffixArray|minRep)\b' Templates
rg -n '^namespace (dataStructure|stringAlgorithm|networkFlow)$' Templates
```

Expected: the first command has no output; the second still reports the established namespaces.

- [ ] **Step 4: Compile representative renamed headers**

Create `/tmp/template_compile.cpp` with:

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using ll = long long;
using i64 = int64_t;
using u64 = uint64_t;
#include TEMPLATE_HEADER

int main()
{
}
```

Compile this source once for each header in the following list:

```text
Templates/data_structure/cartesian_tree.hpp
Templates/data_structure/link_cut_tree.hpp
Templates/data_structure/segment_tree_beats.hpp
Templates/graph/euler_tour.hpp
Templates/graph/network_flow/network_flow.hpp
Templates/graph/network_flow/min_cost_flow.hpp
Templates/math/du_sieve.hpp
Templates/math/linear_basis.hpp
Templates/math/set_power_series.hpp
Templates/string_algorithm/sa.hpp
Templates/string_algorithm/min_rep.hpp
Templates/initialization_misc/hash_table.hpp
```

Run:

```bash
for header in \
    Templates/data_structure/cartesian_tree.hpp \
    Templates/data_structure/link_cut_tree.hpp \
    Templates/data_structure/segment_tree_beats.hpp \
    Templates/graph/euler_tour.hpp \
    Templates/graph/network_flow/network_flow.hpp \
    Templates/graph/network_flow/min_cost_flow.hpp \
    Templates/math/du_sieve.hpp \
    Templates/math/linear_basis.hpp \
    Templates/math/set_power_series.hpp \
    Templates/string_algorithm/sa.hpp \
    Templates/string_algorithm/min_rep.hpp \
    Templates/initialization_misc/hash_table.hpp
do
    g++ -std=gnu++23 -Wall -Wextra -pedantic -I. \
        -DTEMPLATE_HEADER=\"$header\" \
        /tmp/template_compile.cpp -o /tmp/template_compile || exit 1
done
```

Expected: every representative translation unit compiles.

- [ ] **Step 5: Commit the type migration**

```bash
git add Templates
git commit -m "refactor: normalize template type names"
```

### Task 3: Add The QOJ-Derived String Hash Template

**Files:**
- Create: `Templates/string_algorithm/hash.hpp`
- Test: `/tmp/template_hash_test.cpp`
- Preserve: `Qingyu Online Judge/The 4th Universal Cup. Extra Stage 7: Hubei/L. String Matching.cpp`

**Interfaces:**
- Consumes: `std::string`, `std::vector`, and the repository alias `i64`
- Produces: `stringAlgorithm::Hash<mod>`, `Hash<mod>::ensure(int)`, and inclusive `Hash<mod>::calc(int, int)`

- [ ] **Step 1: Write the hash differential test**

Create `/tmp/template_hash_test.cpp` with:

```cpp
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using i64 = int64_t;
#include "Templates/string_algorithm/hash.hpp"

template <int mod>
void check(const string &s)
{
    stringAlgorithm::Hash<mod> h(s);
    for (int l = 0; l < (int)s.size(); ++l)
        for (int r = l; r < (int)s.size(); ++r)
        {
            i64 expected = 0;
            for (int i = l; i <= r; ++i)
                expected = (expected * stringAlgorithm::base + s[i]) % mod;
            assert(h.calc(l, r) == expected);
        }
}

int main()
{
    vector<string> cases{"a", "Hash13331", "a b!~", "0123456789"};
    for (const auto &s : cases)
        check<998244353>(s), check<1000000007>(s);

    mt19937 rng(712367821);
    for (int t = 0; t < 5000; ++t)
    {
        int n = rng() % 40 + 1;
        string s(n, ' ');
        for (auto &c : s)
            c = char(rng() % 95 + 32);
        check<998244353>(s), check<1000000007>(s);
    }

    stringAlgorithm::Hash<998244353> shortHash("x");
    auto oldSize = stringAlgorithm::Hash<998244353>::power.size();
    stringAlgorithm::Hash<998244353> longHash(string(200, 'y'));
    longHash.calc(0, 199);
    assert(stringAlgorithm::Hash<998244353>::power.size() > oldSize);
}
```

- [ ] **Step 2: Compile the test and verify the missing header failure**

Run:

```bash
g++ -std=gnu++23 -O2 -Wall -Wextra -I. /tmp/template_hash_test.cpp -o /tmp/template_hash_test
```

Expected: compilation fails because `Templates/string_algorithm/hash.hpp` does not exist.

- [ ] **Step 3: Add the minimal approved implementation**

Create `Templates/string_algorithm/hash.hpp` with:

```cpp
namespace stringAlgorithm
{
    constexpr int base = 13331;
    template <int mod>
    struct Hash : vector<i64>
    {
        using vector<i64>::vector;
        static inline std::vector<int> power{1};
        static void ensure(int n)
        {
            while ((int)power.size() <= n)
                power.push_back((int)((i64)power.back() * base % mod));
        }
        Hash(const string &s)
        {
            resize(s.size());
            for (int i = 0; i < (int)s.size(); ++i)
                at(i) = ((i ? at(i - 1) : 0) * base + s[i]) % mod;
        }
        auto calc(int l, int r)
        {
            ensure(r - l + 1);
            return (at(r) - (l > 0 ? at(l - 1) * power[r - l + 1] % mod : 0) + mod) % mod;
        }
    };
}
```

- [ ] **Step 4: Run the deterministic and randomized differential test**

Run:

```bash
g++ -std=gnu++23 -O2 -Wall -Wextra -I. /tmp/template_hash_test.cpp -o /tmp/template_hash_test
/tmp/template_hash_test
```

Expected: exit code 0 with no assertion failure.

- [ ] **Step 5: Verify the QOJ source is unchanged**

Run:

```bash
git diff --exit-code -- 'Qingyu Online Judge/The 4th Universal Cup. Extra Stage 7: Hubei/L. String Matching.cpp'
```

Expected: no output and exit code 0.

- [ ] **Step 6: Commit the hash template**

```bash
git add Templates/string_algorithm/hash.hpp
git commit -m "feat: add string hash template"
```

### Task 4: Regenerate Documentation And Run Final Verification

**Files:**
- Modify: `README.md` through `Generator.py`
- Verify: complete `Templates` tree and all implementation commits

**Interfaces:**
- Consumes: final paths and declarations from Tasks 1-3
- Produces: stable generated documentation and a clean, verified migration

- [ ] **Step 1: Regenerate README twice and require stability**

Run:

```bash
python3 Generator.py
cp README.md /tmp/README.template-migration.first
python3 Generator.py
cmp README.md /tmp/README.template-migration.first
```

Expected: `cmp` exits successfully with no output.

- [ ] **Step 2: Verify removed paths and declarations are absent**

Run:

```bash
rg -n 'dataStructure/|stringAlgorithm/|initialization & misc|networkFlow/|cartesianTree\.hpp|decompTree\.hpp|dynamicSeg\.hpp|fhqTreap\.hpp|implicitTreap\.hpp|linkCutTree\.hpp|persistImplicitTreap\.hpp|persistSeg\.hpp|persistTreap\.hpp|scanlineSeg\.hpp|segBeats\.hpp|segDivide\.hpp|segTree\.hpp|segmentTreeBeats\.hpp|topTree\.hpp|blockForest\.hpp|eulerTour\.hpp|minCycle\.hpp|ringCount\.hpp|steinerTree\.hpp|stoerWagner\.hpp|minCostFlow\.hpp|networkFlow\.hpp|berlekampMassey\.hpp|duSieve\.hpp|linearBasis\.hpp|numberTheory\.hpp|schreierSims\.hpp|setPowerSeries\.hpp|linearRecurrence\.hpp|minRep\.hpp|nearestPoints\.cpp|hashTable\.hpp' . --glob '!docs/**'
rg -n 'struct (cartesianTree|decompTree|dynamicSeg|fhqTreap|implicitTreap|linkCutTree|persistImplicitTreap|persistSeg|persistTreap|scanlineSeg|segBeats|segDivide|segTree|blockForest|eulerTour|minCostFlow|networkFlow|ringCount|stoerWagner|duSieve|duSieveMuPhi|linearBasis|numberTheory|schreierSims|setPowerSeries|hashTableBase|hashTable|suffixArray|minRep)\b' Templates
```

Expected: no output. Generated README must also contain the final paths and no old paths.

- [ ] **Step 3: Re-run focused behavior checks**

Run:

```bash
/tmp/template_hash_test
```

Create `/tmp/template_min_rep_test.cpp` with:

```cpp
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#include "Templates/string_algorithm/min_rep.hpp"

int brute(const string &s)
{
    if (s.empty())
        return 0;
    string best = s;
    int ans = 0;
    for (int i = 1; i < (int)s.size(); ++i)
    {
        string t = s.substr(i) + s.substr(0, i);
        if (t < best)
            best = t, ans = i;
    }
    return ans;
}

int main()
{
    vector<string> cases{"", "a", "aaaa", "baca", "caba", "abab", "baaa"};
    for (const auto &s : cases)
        assert(stringAlgorithm::MinRep::solve(s) == brute(s));

    mt19937 rng(19260817);
    for (int t = 0; t < 110000; ++t)
    {
        int n = rng() % 30;
        string s(n, 'a');
        for (auto &c : s)
            c = char('a' + rng() % 5);
        assert(stringAlgorithm::MinRep::solve(s) == brute(s));
    }
}
```

Run:

```bash
g++ -std=gnu++23 -O2 -Wall -Wextra -I. /tmp/template_min_rep_test.cpp -o /tmp/template_min_rep_test
/tmp/template_min_rep_test
```

Expected: all hash checks and all minimum-representation comparisons pass.

- [ ] **Step 4: Inspect the final diff**

Run:

```bash
git diff --check
git status --short
git diff --stat HEAD~3..HEAD
git log --oneline -6
```

Expected: no whitespace errors; only the generated README remains to commit; the QOJ source is unchanged.

- [ ] **Step 5: Commit generated documentation**

```bash
git add README.md
git commit -m "docs: regenerate template directory tree"
```

- [ ] **Step 6: Final clean-state verification**

Run:

```bash
git status --short
git diff --check HEAD~4..HEAD
```

Expected: clean worktree and no whitespace errors in the migration commits.
