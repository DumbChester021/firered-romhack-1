---
description: Workflow Upgrade for this Pokemon Firered Decomp in C Rom Hack
---

PROJECT OPERATING PROMPT — PRET / POKEFIRERED PROJECT (RHH-FAITHFUL, NO-ASSUMPTION)

---

PROJECT CONTEXT

This project is a PRET-based Pokémon FireRed decompilation modification project.

Primary reference implementation:

* /mnt/data/Github/prototype/pokeemerald-expansion

This repository represents the feature baseline and architectural reference target.
Behavior, architecture patterns, file organization, naming conventions, and feature implementation style should follow the reference repository as closely as possible unless explicitly instructed otherwise.

This project must remain RHH-faithful:

* Simple
* Practical
* Minimal abstractions
* Convention over configuration
* No unnecessary architecture
* No premature optimization
* No overengineering
* No speculative systems
* Direct, readable C code
* Match existing engine patterns

When uncertain about implementation:
→ Check reference repo behavior
→ Match their implementation style
→ Do not invent new patterns

---

MANDATORY NO-ASSUMPTION RULE

The model must NEVER assume:

* Function behavior
* Struct layouts
* Memory layout
* Engine systems
* Feature flags
* Build system behavior
* Script engine behavior
* Battle engine behavior
* Save structure
* Repo structure
* Existing helper functions
* Macro behavior

If something is unknown:
→ Search project files
→ Search Docs folder
→ Search Continuation Doc
→ Search reference repository
→ If still unknown: state "Insufficient information"

Do NOT fabricate code to fill gaps.

---

DOCUMENTATION PRIORITY ORDER

When working on tasks, always consult in this order:

1. Continuation Document (PRIMARY STATE FILE)
2. Docs Folder (Design, Research, Workflow)
3. Project Source Code
4. pokeemerald-expansion Reference Repo
5. README
6. Only then implement changes

The Continuation Document is the single source of truth for:

* Current progress
* Completed features
* Pending tasks
* Current branch work
* Implementation notes
* Decisions made
* Known issues
* Next tasks

Always update the Continuation Document after:

* Completing a feature
* Fixing a bug
* Changing architecture
* Adding systems
* Discovering engine behavior
* Making decisions affecting future work

Purpose:
Next no-context LLM session must be able to resume work without repeating work.

---

WORKFLOW RULES

Before starting any task:

1. Read Continuation Document
2. Identify current task
3. Verify task not already completed
4. Check Docs folder for design/spec
5. Check reference repo implementation
6. Locate relevant files in project
7. Plan modification
8. Implement minimal change
9. Verify build logic
10. Update Continuation Document

Never start coding without checking Continuation Document first.

---

IMPLEMENTATION RULES (IMPORTANT)

When adding features:

* Follow existing file structure
* Follow existing naming conventions
* Reuse existing systems
* Do not duplicate systems
* Do not create new managers/controllers unless necessary
* Do not introduce new architecture layers
* Prefer modifying existing systems
* Keep functions small and simple
* Match reference repo patterns
* Prefer static functions where appropriate
* Avoid global state unless engine already uses it
* Avoid macros unless project already uses similar ones
* Do not refactor unrelated code
* Do not move files unless necessary
* Do not rename large systems
* Make minimal diffs

Think like maintaining a legacy C engine, not building a new engine.

---

BRANCH SAFETY RULE

We are working in a feature branch.

This means:

* Safe to modify
* Safe to experiment
* Still avoid unnecessary large refactors
* Keep commits logically grouped
* One feature per commit group
* Update Continuation Doc per feature

---

TASK EXECUTION PROTOCOL

For every task:

1. Read Continuation Doc
2. Define task
3. Locate related code
4. Check reference repo implementation
5. Identify minimal change needed
6. Plan steps
7. Modify code
8. Ensure no duplicate systems created
9. Ensure style matches existing code
10. Update Continuation Doc
11. List next steps

---

ANTI-REPEAT PROTECTION RULE

Before implementing anything, always verify:

* Does this system already exist?
* Was this already implemented?
* Is this already in Continuation Doc?
* Is this already in reference repo?
* Are we duplicating functionality?
* Are we redoing completed work?

If unsure → search first, implement second.

---

OUTPUT STYLE FOR THIS PROJECT

When assisting with this project, responses should be:

* Direct
* Technical
* File-oriented
* Function-oriented
* Minimal explanation
* Focus on implementation steps
* Reference files and functions
* Avoid long theory explanations
* Avoid unrelated improvements
* Avoid architecture redesign unless requested

Preferred response structure:

1. Current Task
2. Files Involved
3. Functions Involved
4. What To Change
5. Implementation Steps
6. Risks / Engine Constraints
7. Update Continuation Doc Note

---

PRIMARY PROJECT GOALS

High-level goal:
Bring PokéFireRed toward feature parity / architecture similarity with pokeemerald-expansion where feasible, while maintaining FireRed base compatibility and PRET-style codebase integrity.

Key philosophy:
Not rewrite.
Not redesign.
Incrementally expand.
Match reference behavior.
Maintain engine stability.

---

END OF PROJECT OPERATING PROMPT
