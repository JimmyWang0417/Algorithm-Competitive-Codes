# Template Naming Migration And String Hash Design

## Goal

Normalize multiword directory names, file names, and class-type names under `Templates` while preserving algorithms and the established competitive-programming implementation style. At the same time, extract the reusable string-hash implementation from the recent QOJ solution into the string-algorithm templates.

## Scope

This is a clean-break migration across the complete `Templates` tree.

- Rename multiword directories to `snake_case`.
- Rename multiword files to `snake_case` while preserving their extensions.
- Rename multiword `class` and `struct` types to `PascalCase`.
- Treat acronyms as PascalCase words, so `fhqTreap` becomes `FhqTreap`.
- Update constructors, inheritance clauses, type references, and internal relative includes required by those renames.
- Add the approved string-hash template directly at its final post-migration path.
- Regenerate the README directory tree after all paths are final.

The migration does not preserve old paths, forwarding headers, type aliases, or compatibility namespaces.

## Exclusions

- Do not rename one-word directories, files, or types.
- Do not rename functions, variables, fields, macros, or namespaces.
- Do not expand competitive-programming abbreviations such as `seg`, `persist`, `rt`, `pre`, or `sze`.
- Do not change algorithms, data layouts, default template arguments, public method signatures, or runtime behavior.
- Do not modify the source QOJ solution while extracting its reusable hash implementation.
- Do not rename semantic multiword terms whose current identifier is treated as one token and was not included in the approved mapping, including `lichao`, `min25`, `acam`, `exkmp`, and `exsam`.

## Directory Mapping

| Current path | New path |
| --- | --- |
| `Templates/dataStructure` | `Templates/data_structure` |
| `Templates/stringAlgorithm` | `Templates/string_algorithm` |
| `Templates/initialization & misc` | `Templates/initialization_misc` |
| `Templates/graph/networkFlow` | `Templates/graph/network_flow` |

All other directories remain unchanged.

## File Mapping

### Data Structure

| Current file | New file |
| --- | --- |
| `cartesianTree.hpp` | `cartesian_tree.hpp` |
| `decompTree.hpp` | `decomp_tree.hpp` |
| `dynamicSeg.hpp` | `dynamic_seg.hpp` |
| `fhqTreap.hpp` | `fhq_treap.hpp` |
| `implicitTreap.hpp` | `implicit_treap.hpp` |
| `linkCutTree.hpp` | `link_cut_tree.hpp` |
| `persistImplicitTreap.hpp` | `persist_implicit_treap.hpp` |
| `persistSeg.hpp` | `persist_seg.hpp` |
| `persistTreap.hpp` | `persist_treap.hpp` |
| `scanlineSeg.hpp` | `scanline_seg.hpp` |
| `segBeats.hpp` | `seg_beats.hpp` |
| `segDivide.hpp` | `seg_divide.hpp` |
| `segTree.hpp` | `seg_tree.hpp` |
| `segmentTreeBeats.hpp` | `segment_tree_beats.hpp` |
| `topTree.hpp` | `top_tree.hpp` |

### Graph

| Current file | New file |
| --- | --- |
| `blockForest.hpp` | `block_forest.hpp` |
| `eulerTour.hpp` | `euler_tour.hpp` |
| `minCycle.hpp` | `min_cycle.hpp` |
| `ringCount.hpp` | `ring_count.hpp` |
| `steinerTree.hpp` | `steiner_tree.hpp` |
| `stoerWagner.hpp` | `stoer_wagner.hpp` |
| `networkFlow.hpp` | `network_flow.hpp` |
| `minCostFlow.hpp` | `min_cost_flow.hpp` |

### Math

| Current file | New file |
| --- | --- |
| `berlekampMassey.hpp` | `berlekamp_massey.hpp` |
| `duSieve.hpp` | `du_sieve.hpp` |
| `linearBasis.hpp` | `linear_basis.hpp` |
| `numberTheory.hpp` | `number_theory.hpp` |
| `schreierSims.hpp` | `schreier_sims.hpp` |
| `setPowerSeries.hpp` | `set_power_series.hpp` |
| `polynomial/linearRecurrence.hpp` | `polynomial/linear_recurrence.hpp` |

### String, Geometry, And Miscellaneous

| Current file | New file |
| --- | --- |
| `stringAlgorithm/minRep.hpp` | `string_algorithm/min_rep.hpp` |
| `geometry/nearestPoints.cpp` | `geometry/nearest_points.cpp` |
| `initialization & misc/hashTable.hpp` | `initialization_misc/hash_table.hpp` |

Files such as `sa.hpp`, `kmp.hpp`, `fenwick.hpp`, `treap.hpp`, `Simpson.hpp`, `min25.hpp`, `2d.hpp`, and `3d.hpp` retain their current names.

## String Hash Template

The implementation source is `Qingyu Online Judge/The 4th Universal Cup. Extra Stage 7: Hubei/L. String Matching.cpp`. The solution file remains unchanged.

Add `Templates/string_algorithm/hash.hpp` with the following established interface and behavior:

- Place the template in the existing `stringAlgorithm` namespace.
- Preserve `template <int mod> struct Hash : vector<i64>` rather than introducing a double-hash wrapper or renaming the type to `StringHash`.
- Define `base` as `13331` in the `stringAlgorithm` namespace. The original value `31` is not retained because the template hashes direct character values rather than lowercase alphabet indices.
- Build the prefix hash with `s[i]` directly. Do not subtract `'a'` and do not cast to `unsigned char`.
- Preserve the shared `static inline vector<int> power{1}` table and the on-demand `ensure(int n)` extension method.
- Preserve `calc(int l, int r)` as an inclusive, zero-indexed substring query.
- Preserve the source implementation's preconditions: callers provide a nonempty string when querying and valid indices satisfying `0 <= l <= r < s.size()`.
- Do not add reverse hashing, automatic double hashing, bounds checks, alternate character encodings, or configurable bases.

`Hash` is a single-word type and therefore does not require a naming-migration change.

## Type Mapping

| Current type | New type |
| --- | --- |
| `cartesianTree` | `CartesianTree` |
| `decompTree` | `DecompTree` |
| `dynamicSeg` | `DynamicSeg` |
| `fhqTreap` | `FhqTreap` |
| `implicitTreap` | `ImplicitTreap` |
| `linkCutTree` | `LinkCutTree` |
| `persistImplicitTreap` | `PersistImplicitTreap` |
| `persistSeg` | `PersistSeg` |
| `persistTreap` | `PersistTreap` |
| `scanlineSeg` | `ScanlineSeg` |
| `segBeats` | `SegBeats` |
| `segDivide` | `SegDivide` |
| `segTree` | `SegTree` |
| `blockForest` | `BlockForest` |
| `eulerTour` | `EulerTour` |
| `minCostFlow` | `MinCostFlow` |
| `networkFlow` | `NetworkFlow` |
| `ringCount` | `RingCount` |
| `stoerWagner` | `StoerWagner` |
| `duSieve` | `DuSieve` |
| `duSieveMuPhi` | `DuSieveMuPhi` |
| `linearBasis` | `LinearBasis` |
| `numberTheory` | `NumberTheory` |
| `schreierSims` | `SchreierSims` |
| `setPowerSeries` | `SetPowerSeries` |
| `hashTableBase` | `HashTableBase` |
| `hashTable` | `HashTable` |
| `suffixArray` | `SuffixArray` |
| `minRep` | `MinRep` |

Already-conforming multiword types such as `SteinerTree` remain unchanged. One-word types such as `fenwick`, `treap`, `kmp`, `sam`, `Node`, `Line`, `Point`, `Comb`, and `Simpson` remain unchanged.

## Reference Updates

- Update each renamed type's constructors to the new type spelling.
- Update base classes and dependent type references, including `HashTableBase` inside `HashTable`.
- Update `segment_tree_beats.hpp` to include `seg_beats.hpp`.
- Update `math/polynomial.hpp` to include `polynomial/linear_recurrence.hpp`.
- Leave namespaces such as `dataStructure`, `stringAlgorithm`, `networkFlow`, `twoDimension`, and `threeDimension` unchanged.
- Regenerate README rather than editing its generated directory tree manually.

## Verification

- Search the complete repository for every removed path and renamed type spelling.
- Verify no old path, forwarding header, compatibility alias, or stale internal include remains.
- Verify every approved new path and type declaration exists exactly once where expected.
- Compile representative translation units covering renamed data-structure, string, graph, math, polynomial, and miscellaneous headers.
- Run the existing minimum-representation differential test with the new include path and `MinRep` type.
- Compile the new `string_algorithm/hash.hpp` template with both moduli used by the source solution.
- Compare every substring hash against a direct polynomial-hash calculation on deterministic cases and randomized strings, including letters, digits, punctuation, and spaces.
- Verify that multiple `Hash<mod>` objects correctly share and extend the static power table.
- Run `Generator.py` twice and require the second output to be byte-for-byte stable.
- Inspect `git diff --check`; pre-existing upstream whitespace outside the migration is not reformatted.
- Confirm the final diff changes names and required references only, apart from the generated README update and migration documentation.
