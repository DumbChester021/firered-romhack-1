# New Moves List

This document tracks all Generation 4+ moves that have been fully ported into the Engine.

| Move ID (Dec) | Move Name | Type | Category | PP | Power | Acc | Included Features & Notes | Link to Implementation Commit |
|---|---|---|---|---|---|---|---|---|
| 355 | **Roost** | Flying | Status | 10 | — | — | Fully dynamic Type-Strip engine ported from RHH. Heals 50% max HP. Ground/Fighting Type effectiveness updates correctly for the remainder of the turn. | TBD |
| 356 | **Flare Blitz** | Fire | Physical | 15 | 120 | 100 | Ported stats, 33% recoil, 10% burn. No unique effect needed. Animation ported. | TBD |
| 357 | **Brave Bird** | Flying | Physical | 15 | 120 | 100 | Ported stats, 33% recoil. No unique effect needed. Animation ported. | TBD |
| 358 | **Earth Power** | Ground | Special | 10 | 90 | 100 | Ported stats, 10% Sp.Def drop. No unique effect needed. Animation ported. | TBD |
| 359 | **Bug Buzz** | Bug | Special | 10 | 90 | 100 | Ported stats, 10% Sp.Def drop. No unique effect needed. Animation ported. | TBD |
| 360 | **Dark Pulse** | Dark | Special | 15 | 80 | 100 | Ported stats, 20% flinch. No unique effect needed. Animation ported. | TBD |
| 361 | **Energy Ball** | Grass | Special | 10 | 90 | 100 | Ported stats, 10% Sp.Def drop. No unique effect needed. Animation ported. | TBD |
| 362 | **Seed Bomb** | Grass | Physical | 15 | 80 | 100 | Ported stats. No unique effect needed. Animation ported. | TBD |
| 363 | **X-Scissor** | Bug | Physical | 15 | 80 | 100 | Ported stats. No unique effect needed. Animation ported. | TBD |
| 364 | **Poison Jab** | Poison | Physical | 20 | 80 | 100 | Ported stats, 30% poison. No unique effect needed. Animation ported. | TBD |
| 416 | **Giga Impact** | Normal | Physical | 5 | 150 | 90 | Ported stats, requires recharge (EFFECT_HIT with MOVE_EFFECT_RECHARGE). Animation ported correctly mapping to Hyper Beam's engine handling. | TBD |
| 445 | **Captivate** | Normal | Status | 20 | — | 100 | New Battle Effect ported: `EFFECT_CAPTIVATE`. Properly checks gender and Oblivious. Handled with AI gender checks. Animation ported. | TBD |
| 496 | **Round** | Normal | Special | 15 | 60 | 100 | Uses `EFFECT_ROUND` primary effect and `TryUpdateRoundTurnOrder`. Animation `Move_ROUND` ported. | TBD |
| 590 | **Confide** | Normal | Status | 20 | — | — | Uses `EFFECT_SPECIAL_ATTACK_DOWN`. Animation `Move_CONFIDE` ported. | TBD |
| 779 | **Tera Blast** | Normal | Special | 10 | 80 | 100 | Uses `EFFECT_TERA_BLAST`. Fallbacks to `Move_HIDDEN_POWER` animation to avoid massive engine bloat from Terastallization branches. | TBD |
| 428 | **Zen Headbutt** | Psychic | Physical | 15 | 80 | 90 | Uses `EFFECT_HIT` with additionalEffect for flinch. Assumes `Move_HEADBUTT` animation. | TBD |
| 523 | **Bulldoze** | Ground | Physical | 20 | 60 | 100 | Uses `EFFECT_EARTHQUAKE`. Lowers speed via additionalEffect. Assumes `Move_EARTHQUAKE` animation. | TBD |
| 526 | **Work Up** | Normal | Status | 30 | — | — | Uses `EFFECT_ATTACK_SPATK_UP`. Assumes `Move_HOWL` animation. | TBD |
| 612 | **Power-Up Punch** | Fighting | Physical | 20 | 40 | 100 | Uses `EFFECT_HIT` with additionalEffect for attack up. Assumes `Move_MACH_PUNCH` animation. | TBD |
| 811 | **Trailblaze** | Grass | Physical | 20 | 50 | 100 | Uses `EFFECT_HIT` with additionalEffect for speed up. Assumes `Move_BULLET_SEED` animation. | TBD |

***Note:** All moves from Gen 4 to Gen 9 have been ported into the `moves_info.h` table and their `MOVE_` constants defined in `include/constants/moves.h` to align perfectly with `pokeemerald-expansion`. Unimplemented moves are functionally stubbed as 0-power `EFFECT_HIT` moves with `Move_NONE` animations.*

---

## Porting Checklist for New Moves

Adding a new move requires touching multiple systems. See `docs/research/adding_new_moves_workflow.md` for technical deep-dives, but the high-level checklist is:

1. **Constants:** Define `MOVE_X` in `include/constants/moves.h` and bump `MOVES_COUNT`.
2. **Move Data (The Big One):** Add the name, description string, description pointer, and battle stats struct to the respective 4 sections in `src/data/moves_info.h`.
3. **Animations:** Add the script to `data/battle_anim_scripts.s` using the RHH macro opcodes, and register it in `gBattleAnims_Moves`.
4. **Battle Script Engine:** If the move introduces a new `EFFECT_X`, add it to `include/constants/battle_move_effects.h`, write the C handler in `src/battle_script_commands.c`, and write the ASM macro logic in `data/battle_scripts_1.s`.
5. **AI Integration:** Add the new effect evaluation to `src/battle_ai_main.c` (and/or `src/battle_ai_util.c`) so the AI knows how to properly use or counter the move.
