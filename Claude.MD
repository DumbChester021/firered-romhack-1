PROJECT OPERATING PROMPT — PRET / POKEFIRERED PROJECT (RHH-FAITHFUL, NO-ASSUMPTION)

---

PROJECT CONTEXT

This project is a PRET-based Pokémon FireRed decompilation modification project.

Primary reference implementation:
* /mnt/data/Github/prototype/pokeemerald-expansion

This repository represents the feature baseline and architectural reference target.
Behavior, architecture patterns, file organization, naming conventions, and feature implementation style should follow the reference repository as closely as possible unless explicitly instructed otherwise.

This project must remain RHH-faithful:
* Port natively rather than writing hacky fallbacks.
* If a C dependency (e.g., `SpriteTemplate`, callback function, or macro) is missing in FireRed, DO NOT fallback. Extrapolate and natively port that missing dependency from the reference repo into FireRed.
* Simple & Practical
* Minimal abstractions (Convention over configuration)
* No unnecessary architecture or speculative systems
* Direct, readable C code
* Match existing engine patterns

When uncertain about implementation:
→ Check reference repo behavior
→ Match their implementation style
→ Do not invent new patterns

---

MANDATORY NO-ASSUMPTION RULE

The model must NEVER assume:
* Function behavior, Struct layouts, Memory layout
* Engine systems, Feature flags, Build system behavior
* Script engine behavior, Battle engine behavior
* Save structure, Repo structure
* Existing helper functions, Macro behavior

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
1. `docs/CONTINUATION_GUIDE.md` (PRIMARY STATE FILE)
2. `docs/research/' and 'docs/` folder (Specific workflows like `adding_new_moves_workflow.md`)
3. Project Source Code (`firered-romhack-1/`)
4. pokeemerald-expansion Reference Repo
5. `README.md`
6. Only then implement changes.

The Continuation Document is the single source of truth. Always update it after:
* Completing a feature
* Fixing a bug
* Changing architecture
* Adding systems
* Making decisions affecting future work

Purpose: The next no-context LLM session must be able to resume work without repeating work.

---

WORKFLOW RULES

Before starting any task:
1. Read Continuation Document & relevant workflow docs (e.g., `adding_new_moves_workflow.md`).
2. Identify current task & verify it's not already completed.
3. Check reference repo implementation for exactly how they did it.
4. Locate relevant files in project.
5. Plan modification.
6. Implement minimal change. Port missing dependencies 1:1 if necessary.
7. Clean build artifacts: `make clean`.
8. Verify build logic (`make -j$(nproc)`).
9. Verify data integrity (`python3 tools/verify_data.py`).
10. Update Continuation Document & Docs.
11. Commit & Push changes (only when told to).

Never start coding without checking the Continuation Document first.

---

IMPLEMENTATION RULES (IMPORTANT)

When adding features:
* Follow existing file structure and naming conventions.
* Reuse existing systems. Do not duplicate systems.
* Match reference repo patterns perfectly.
* Missing macro? Port it from `asm/macros/`
* Missing C struct (e.g., SpriteTemplate)? Port it from `src/battle_anim_*.c` to `src/battle_anim_new.c`.
* The `preproc` compiler supports native Python kwargs (e.g., `x=0, y=0`), enabling perfectly 1:1 ASM ports. USE THIS. Do not invent legacy fallbacks. 
* Avoid global state unless the engine already uses it.
* Do not refactor unrelated code or redesign architecture.
* Keep commits logically grouped. One feature per commit group.

Think like maintaining a legacy C engine, not building a new engine.

---

ANTI-REPEAT PROTECTION RULE

Before implementing anything, always verify:
* Does this system already exist?
* Was this already implemented?
* Is this already in Continuation Doc?
* Are we duplicating functionality?

If unsure → search first, implement second.

---

TASK EXECUTION PROTOCOL

1. Read Continuation Doc & `docs/research/` guides.
2. Define task.
3. Locate related code in `firered-romhack-1`.
4. Locate reference code in `pokeemerald-expansion`.
5. Port code 1:1 exactly. Include missing sub-dependencies natively.
6. Build (`make -j$(nproc)`) and Verify (`python3 tools/verify_data.py`).
7. Update Continuation Doc.
8. Commit and provide next steps.

---

OUTPUT STYLE FOR THIS PROJECT

Responses should be:
* Direct, Technical, File & Function-oriented.
* Minimal explanation. Focus on implementation steps.
* Avoid long theory explanations and speculative redesigns.

Preferred response structure:
1. Current Task
2. Files Involved
3. What To Change
4. Implementation Steps
5. Build Verification
6. Documentation Update
