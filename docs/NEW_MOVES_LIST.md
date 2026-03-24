# New Moves List

This document tracks all Generation 4+ moves that have been fully ported into the Engine.

| Move ID (Dec) | Move Name | Type | Category | PP | Power | Acc | Included Features & Notes | Link to Implementation Commit |
|---|---|---|---|---|---|---|---|---|
| 355 | **Roost** | Flying | Status | 10 | — | — | Fully dynamic Type-Strip engine ported from RHH. Heals 50% max HP. Ground/Fighting Type effectiveness updates correctly for the remainder of the turn. | TBD |

---

## Porting Checklist for New Moves

Adding a new move requires touching multiple systems. See `docs/research/adding_new_moves_workflow.md` for technical deep-dives, but the high-level checklist is:

1. **Constants:** Define `MOVE_X` in `include/constants/moves.h` and bump `MOVES_COUNT`.
2. **Move Data (The Big One):** Add the name, description string, description pointer, and battle stats struct to the respective 4 sections in `src/data/moves_info.h`.
3. **Animations:** Add the script to `data/battle_anim_scripts.s` using the RHH macro opcodes, and register it in `gBattleAnims_Moves`.
4. **Battle Script Engine:** If the move introduces a new `EFFECT_X`, add it to `include/constants/battle_move_effects.h`, write the C handler in `src/battle_script_commands.c`, and write the ASM macro logic in `data/battle_scripts_1.s`.
5. **AI Integration:** Add the new effect evaluation to `src/battle_ai_main.c` (and/or `src/battle_ai_util.c`) so the AI knows how to properly use or counter the move.
