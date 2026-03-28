PROJECT OPERATING PROMPT — PRET / POKEFIRERED PROJECT (RHH-CONVERGENCE, NO-ASSUMPTION)

---

PROJECT CONTEXT

This project is a PRET-based Pokémon FireRed decompilation modification project.

Primary reference implementation:
* /mnt/data/Github/prototype/pokeemerald-expansion (LOCAL — do NOT fetch from GitHub)

This repository represents the feature baseline and architectural reference target.
The long-term goal is FULL CONVERGENCE with RHH: identical struct names, field names,
function signatures, and engine patterns. Not "adapted for FireRed" — identical to RHH
where possible, so eventually the codebase is essentially a copy.

---

RHH CONVERGENCE RULES (CRITICAL)

1. NO ADAPTATIONS. NO NAME MAPPINGS. Port code exactly as RHH has it.
2. If a struct/field/function name differs from RHH, RENAME IT to match RHH.
   - Example: if RHH uses `gMovesInfo`, rename our `gBattleMoves` to `gMovesInfo`.
   - Example: if RHH uses `DAMAGE_CATEGORY_PHYSICAL`, rename our `SPLIT_PHYSICAL`.
   - Propagate renames across the entire codebase.
3. If a struct layout differs, RESTRUCTURE IT to match RHH.
4. If RHH has a function we lack, PORT IT verbatim.
5. If RHH has a field/flag we lack, ADD IT with the same name and type.
6. Gimmick systems (Tera, Mega, Z-Moves, Dynamax) are not yet implemented,
   but their data (ban flags, structural stubs, no-op handlers) MUST be present
   matching RHH so the data layer is ready when they are.
7. Every touch point is an opportunity to converge. When modifying any file,
   check if it matches RHH. If not, converge it.

---

TOKEN EFFICIENCY FOR LARGE PORTS

For large functions (500+ lines) or large files, DO NOT read them fully into LLM context.
Instead:
1. Build a Python porting tool that reads RHH source, extracts functions by brace-depth parsing.
2. Since we converge (no name mappings), the tool mostly just copies + resolves missing deps.
3. Write output directly to the target file.
4. Only bring small targeted snippets into LLM for logic review or conflict resolution.
5. Create research docs (`docs/research/`) explaining the port plan so future sessions
   can resume without re-reading everything.

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
* Follow RHH naming conventions. If our names differ, rename to match RHH.
* Reuse existing systems. Do not duplicate systems.
* Match reference repo patterns EXACTLY — same names, same signatures, same logic.
* Missing macro? Port it from RHH `asm/macros/`
* Missing C struct? Port it from RHH with the SAME name.
* Missing function? Port it from RHH with the SAME name and signature.
* The `preproc` compiler supports native Python kwargs (e.g., `x=0, y=0`), enabling perfectly 1:1 ASM ports. USE THIS. Do not invent legacy fallbacks.
* Avoid global state unless the engine already uses it.
* Do not refactor unrelated code or redesign architecture.
* Keep commits logically grouped. One feature per commit group.

Think like converging toward RHH, not maintaining a separate fork.

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
5. Port code 1:1 exactly. Use same names. Include missing sub-dependencies natively.
6. Build (`make -j$(nproc)`) and Verify (`python3 tools/verify_data.py`).
7. Update Continuation Doc.
8. Commit and provide next steps.

---

CURRENT ACTIVE WORK (as of 2026-03-29)

Active task: Porting AI additionalEffects scoring from RHH (Session B next).
* Research doc: `docs/research/ai_additional_effects_port_plan.md`
* Python extraction tool: `tools/port_ai_scoring.py` (run with `--check-deps`)
* Staging area: `tools/staging/ai_port/` (12 extracted RHH functions ready)
* Tier A DONE (commit d06c38e95): speed infrastructure — GetBattlerTotalSpeedStat,
  GetBattleMovePriority, AI_WhoStrikesFirst, AI_IsFaster/IsSlower 5-param, SetBattlerAiData
* Next (Session B): Tiers B+D — GetMovesArray, HasMoveWithEffect, HasMoveThatChangesKOThreshold,
  GetStatBeingChanged, GetStagesOfStatChange
* Continuation guide section: "RHH Convergence Tracker" in `docs/CONTINUATION_GUIDE.md`

EWRAM usage is at 98.87% — be very careful about adding EWRAM_DATA globals.
Use heap allocation (AllocZeroed) for new large structs, like gAiLogicData does.

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
