# Local Codex Instructions

- For debugging competitive-programming solutions, do not modify source files unless the user explicitly asks for code edits.
- Prefer finding and explaining counterexamples. Put generated counterexamples in the location specified by the user.
- If the user asks to debug but does not specify where to place counterexamples, ask for the target location before creating files.
- It is OK to compile and run programs, inspect statements, and compare against brute force or checkers, as long as source files are left unchanged.
- Preserve the user's own debugging practice: explain the failing condition and the minimal counterexample, but avoid applying the fix directly.
- Do not point out where the code is wrong, identify buggy lines, or explain the root cause unless the user explicitly asks for that level of diagnosis.

## Chinese Mathematical Tutorial Style

These rules apply to 杨表详细教程.md and similar Chinese mathematical tutorials in this repository.

- Write for an algorithm-competition participant who may be new to the mathematical topic. Connect abstract objects to arrays, coordinates, state transitions, invariants, recurrences, and constructive algorithms when helpful.
- Define every symbol before its first substantive use. Explicitly distinguish shapes, cells, coordinates, tableau entries, labels, random variables, probabilities, and algorithms.
- State genuinely immediate facts directly so the reader does not have to decode an unnecessarily formal derivation. If a step is not evidently rigorous, follow it with a concrete, accessible proof; do not substitute intuition for proof.
- Prefer elementary local, constructive, inductive, or invariant-based proofs over highly abstract proofs when they establish the same claim cleanly.
- Include the prerequisites, properties, and theorems needed by later arguments. State hypotheses, conventions, equality conditions, and the exact scope of each result.
- Make every construction fully explicit: coordinate orientation, index ranges, scan order, reading direction, tie-breaking rules, boundary ownership, initial state, transition rule, and stopping condition.
- For growth diagrams and RSK, always identify where $P$ and $Q$ are recovered, which boundary shape chain is being read, in which direction it is read, and whether a symbol denotes a shape or a filled tableau.
- Use “$...$” for inline mathematics and “$$...$$” for display mathematics. Do not use “\(...\)” or “\[...\]”.
- Do not use ASCII art for Young diagrams or tableaux. Use renderable HTML grids/tables or another proper visual format.
- Do not use the phrases “无歧异”, “歧异”, or “歧义” in tutorial prose. Replace them with the exact convention, direction, condition, or rule that resolves the issue.
- When the user says an explanation is only for the conversation and should not be added to the tutorial, do not modify the tutorial for that explanation.
- Preserve the tutorial's established notation and terminology unless correcting a demonstrated error. After edits, check math delimiters, HTML structure, section numbering, cross-references, and worked examples.
