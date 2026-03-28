// ==========================================================================
// moves_info.h — Unified move data (Phase 5)
// ==========================================================================

// ---------------------------------------------------------------------------
// Section 1: Move Names
// ---------------------------------------------------------------------------

const u8 gMoveNames[MOVES_COUNT][MOVE_NAME_LENGTH + 1] = {
    [MOVE_POUND] = _("POUND"),
    [MOVE_KARATE_CHOP] = _("KARATE CHOP"),
    [MOVE_DOUBLE_SLAP] = _("DOUBLE SLAP"),
    [MOVE_COMET_PUNCH] = _("COMET PUNCH"),
    [MOVE_MEGA_PUNCH] = _("MEGA PUNCH"),
    [MOVE_PAY_DAY] = _("PAY DAY"),
    [MOVE_FIRE_PUNCH] = _("FIRE PUNCH"),
    [MOVE_ICE_PUNCH] = _("ICE PUNCH"),
    [MOVE_THUNDER_PUNCH] = _("THUNDERPUNCH"),
    [MOVE_SCRATCH] = _("SCRATCH"),
    [MOVE_VISE_GRIP] = _("VISE GRIP"),
    [MOVE_GUILLOTINE] = _("GUILLOTINE"),
    [MOVE_RAZOR_WIND] = _("RAZOR WIND"),
    [MOVE_SWORDS_DANCE] = _("SWORDS DANCE"),
    [MOVE_CUT] = _("CUT"),
    [MOVE_GUST] = _("GUST"),
    [MOVE_WING_ATTACK] = _("WING ATTACK"),
    [MOVE_WHIRLWIND] = _("WHIRLWIND"),
    [MOVE_FLY] = _("FLY"),
    [MOVE_BIND] = _("BIND"),
    [MOVE_SLAM] = _("SLAM"),
    [MOVE_VINE_WHIP] = _("VINE WHIP"),
    [MOVE_STOMP] = _("STOMP"),
    [MOVE_DOUBLE_KICK] = _("DOUBLE KICK"),
    [MOVE_MEGA_KICK] = _("MEGA KICK"),
    [MOVE_JUMP_KICK] = _("JUMP KICK"),
    [MOVE_ROLLING_KICK] = _("ROLLING KICK"),
    [MOVE_SAND_ATTACK] = _("SAND ATTACK"),
    [MOVE_HEADBUTT] = _("HEADBUTT"),
    [MOVE_HORN_ATTACK] = _("HORN ATTACK"),
    [MOVE_FURY_ATTACK] = _("FURY ATTACK"),
    [MOVE_HORN_DRILL] = _("HORN DRILL"),
    [MOVE_TACKLE] = _("TACKLE"),
    [MOVE_BODY_SLAM] = _("BODY SLAM"),
    [MOVE_WRAP] = _("WRAP"),
    [MOVE_TAKE_DOWN] = _("TAKE DOWN"),
    [MOVE_THRASH] = _("THRASH"),
    [MOVE_DOUBLE_EDGE] = _("DOUBLE-EDGE"),
    [MOVE_TAIL_WHIP] = _("TAIL WHIP"),
    [MOVE_POISON_STING] = _("POISON STING"),
    [MOVE_TWINEEDLE] = _("TWINEEDLE"),
    [MOVE_PIN_MISSILE] = _("PIN MISSILE"),
    [MOVE_LEER] = _("LEER"),
    [MOVE_BITE] = _("BITE"),
    [MOVE_GROWL] = _("GROWL"),
    [MOVE_ROAR] = _("ROAR"),
    [MOVE_SING] = _("SING"),
    [MOVE_SUPERSONIC] = _("SUPERSONIC"),
    [MOVE_SONIC_BOOM] = _("SONIC BOOM"),
    [MOVE_DISABLE] = _("DISABLE"),
    [MOVE_ACID] = _("ACID"),
    [MOVE_EMBER] = _("EMBER"),
    [MOVE_FLAMETHROWER] = _("FLAMETHROWER"),
    [MOVE_MIST] = _("MIST"),
    [MOVE_WATER_GUN] = _("WATER GUN"),
    [MOVE_HYDRO_PUMP] = _("HYDRO PUMP"),
    [MOVE_SURF] = _("SURF"),
    [MOVE_ICE_BEAM] = _("ICE BEAM"),
    [MOVE_BLIZZARD] = _("BLIZZARD"),
    [MOVE_PSYBEAM] = _("PSYBEAM"),
    [MOVE_BUBBLE_BEAM] = _("BUBBLE BEAM"),
    [MOVE_AURORA_BEAM] = _("AURORA BEAM"),
    [MOVE_HYPER_BEAM] = _("HYPER BEAM"),
    [MOVE_PECK] = _("PECK"),
    [MOVE_DRILL_PECK] = _("DRILL PECK"),
    [MOVE_SUBMISSION] = _("SUBMISSION"),
    [MOVE_LOW_KICK] = _("LOW KICK"),
    [MOVE_COUNTER] = _("COUNTER"),
    [MOVE_SEISMIC_TOSS] = _("SEISMIC TOSS"),
    [MOVE_STRENGTH] = _("STRENGTH"),
    [MOVE_ABSORB] = _("ABSORB"),
    [MOVE_MEGA_DRAIN] = _("MEGA DRAIN"),
    [MOVE_LEECH_SEED] = _("LEECH SEED"),
    [MOVE_GROWTH] = _("GROWTH"),
    [MOVE_RAZOR_LEAF] = _("RAZOR LEAF"),
    [MOVE_SOLAR_BEAM] = _("SOLAR BEAM"),
    [MOVE_POISON_POWDER] = _("POISONPOWDER"),
    [MOVE_STUN_SPORE] = _("STUN SPORE"),
    [MOVE_SLEEP_POWDER] = _("SLEEP POWDER"),
    [MOVE_PETAL_DANCE] = _("PETAL DANCE"),
    [MOVE_STRING_SHOT] = _("STRING SHOT"),
    [MOVE_DRAGON_RAGE] = _("DRAGON RAGE"),
    [MOVE_FIRE_SPIN] = _("FIRE SPIN"),
    [MOVE_THUNDER_SHOCK] = _("THUNDERSHOCK"),
    [MOVE_THUNDERBOLT] = _("THUNDERBOLT"),
    [MOVE_THUNDER_WAVE] = _("THUNDER WAVE"),
    [MOVE_THUNDER] = _("THUNDER"),
    [MOVE_ROCK_THROW] = _("ROCK THROW"),
    [MOVE_EARTHQUAKE] = _("EARTHQUAKE"),
    [MOVE_FISSURE] = _("FISSURE"),
    [MOVE_DIG] = _("DIG"),
    [MOVE_TOXIC] = _("TOXIC"),
    [MOVE_CONFUSION] = _("CONFUSION"),
    [MOVE_PSYCHIC] = _("PSYCHIC"),
    [MOVE_HYPNOSIS] = _("HYPNOSIS"),
    [MOVE_MEDITATE] = _("MEDITATE"),
    [MOVE_AGILITY] = _("AGILITY"),
    [MOVE_QUICK_ATTACK] = _("QUICK ATTACK"),
    [MOVE_RAGE] = _("RAGE"),
    [MOVE_TELEPORT] = _("TELEPORT"),
    [MOVE_NIGHT_SHADE] = _("NIGHT SHADE"),
    [MOVE_MIMIC] = _("MIMIC"),
    [MOVE_SCREECH] = _("SCREECH"),
    [MOVE_DOUBLE_TEAM] = _("DOUBLE TEAM"),
    [MOVE_RECOVER] = _("RECOVER"),
    [MOVE_HARDEN] = _("HARDEN"),
    [MOVE_MINIMIZE] = _("MINIMIZE"),
    [MOVE_SMOKESCREEN] = _("SMOKESCREEN"),
    [MOVE_CONFUSE_RAY] = _("CONFUSE RAY"),
    [MOVE_WITHDRAW] = _("WITHDRAW"),
    [MOVE_DEFENSE_CURL] = _("DEFENSE CURL"),
    [MOVE_BARRIER] = _("BARRIER"),
    [MOVE_LIGHT_SCREEN] = _("LIGHT SCREEN"),
    [MOVE_HAZE] = _("HAZE"),
    [MOVE_REFLECT] = _("REFLECT"),
    [MOVE_FOCUS_ENERGY] = _("FOCUS ENERGY"),
    [MOVE_BIDE] = _("BIDE"),
    [MOVE_METRONOME] = _("METRONOME"),
    [MOVE_MIRROR_MOVE] = _("MIRROR MOVE"),
    [MOVE_SELF_DESTRUCT] = _("SELFDESTRUCT"),
    [MOVE_EGG_BOMB] = _("EGG BOMB"),
    [MOVE_LICK] = _("LICK"),
    [MOVE_SMOG] = _("SMOG"),
    [MOVE_SLUDGE] = _("SLUDGE"),
    [MOVE_BONE_CLUB] = _("BONE CLUB"),
    [MOVE_FIRE_BLAST] = _("FIRE BLAST"),
    [MOVE_WATERFALL] = _("WATERFALL"),
    [MOVE_CLAMP] = _("CLAMP"),
    [MOVE_SWIFT] = _("SWIFT"),
    [MOVE_SKULL_BASH] = _("SKULL BASH"),
    [MOVE_SPIKE_CANNON] = _("SPIKE CANNON"),
    [MOVE_CONSTRICT] = _("CONSTRICT"),
    [MOVE_AMNESIA] = _("AMNESIA"),
    [MOVE_KINESIS] = _("KINESIS"),
    [MOVE_SOFT_BOILED] = _("SOFT-BOILED"),
    [MOVE_HIGH_JUMP_KICK] = _("HIGHJUMPKICK"),
    [MOVE_GLARE] = _("GLARE"),
    [MOVE_DREAM_EATER] = _("DREAM EATER"),
    [MOVE_POISON_GAS] = _("POISON GAS"),
    [MOVE_BARRAGE] = _("BARRAGE"),
    [MOVE_LEECH_LIFE] = _("LEECH LIFE"),
    [MOVE_LOVELY_KISS] = _("LOVELY KISS"),
    [MOVE_SKY_ATTACK] = _("SKY ATTACK"),
    [MOVE_TRANSFORM] = _("TRANSFORM"),
    [MOVE_BUBBLE] = _("BUBBLE"),
    [MOVE_DIZZY_PUNCH] = _("DIZZY PUNCH"),
    [MOVE_SPORE] = _("SPORE"),
    [MOVE_FLASH] = _("FLASH"),
    [MOVE_PSYWAVE] = _("PSYWAVE"),
    [MOVE_SPLASH] = _("SPLASH"),
    [MOVE_ACID_ARMOR] = _("ACID ARMOR"),
    [MOVE_CRABHAMMER] = _("CRABHAMMER"),
    [MOVE_EXPLOSION] = _("EXPLOSION"),
    [MOVE_FURY_SWIPES] = _("FURY SWIPES"),
    [MOVE_BONEMERANG] = _("BONEMERANG"),
    [MOVE_REST] = _("REST"),
    [MOVE_ROCK_SLIDE] = _("ROCK SLIDE"),
    [MOVE_HYPER_FANG] = _("HYPER FANG"),
    [MOVE_SHARPEN] = _("SHARPEN"),
    [MOVE_CONVERSION] = _("CONVERSION"),
    [MOVE_TRI_ATTACK] = _("TRI ATTACK"),
    [MOVE_SUPER_FANG] = _("SUPER FANG"),
    [MOVE_SLASH] = _("SLASH"),
    [MOVE_SUBSTITUTE] = _("SUBSTITUTE"),
    [MOVE_STRUGGLE] = _("STRUGGLE"),
    [MOVE_SKETCH] = _("SKETCH"),
    [MOVE_TRIPLE_KICK] = _("TRIPLE KICK"),
    [MOVE_THIEF] = _("THIEF"),
    [MOVE_SPIDER_WEB] = _("SPIDER WEB"),
    [MOVE_MIND_READER] = _("MIND READER"),
    [MOVE_NIGHTMARE] = _("NIGHTMARE"),
    [MOVE_FLAME_WHEEL] = _("FLAME WHEEL"),
    [MOVE_SNORE] = _("SNORE"),
    [MOVE_CURSE] = _("CURSE"),
    [MOVE_FLAIL] = _("FLAIL"),
    [MOVE_CONVERSION_2] = _("CONVERSION 2"),
    [MOVE_AEROBLAST] = _("AEROBLAST"),
    [MOVE_COTTON_SPORE] = _("COTTON SPORE"),
    [MOVE_REVERSAL] = _("REVERSAL"),
    [MOVE_SPITE] = _("SPITE"),
    [MOVE_POWDER_SNOW] = _("POWDER SNOW"),
    [MOVE_PROTECT] = _("PROTECT"),
    [MOVE_MACH_PUNCH] = _("MACH PUNCH"),
    [MOVE_SCARY_FACE] = _("SCARY FACE"),
    [MOVE_FEINT_ATTACK] = _("FEINT ATTACK"),
    [MOVE_SWEET_KISS] = _("SWEET KISS"),
    [MOVE_BELLY_DRUM] = _("BELLY DRUM"),
    [MOVE_SLUDGE_BOMB] = _("SLUDGE BOMB"),
    [MOVE_MUD_SLAP] = _("MUD-SLAP"),
    [MOVE_OCTAZOOKA] = _("OCTAZOOKA"),
    [MOVE_SPIKES] = _("SPIKES"),
    [MOVE_ZAP_CANNON] = _("ZAP CANNON"),
    [MOVE_FORESIGHT] = _("FORESIGHT"),
    [MOVE_DESTINY_BOND] = _("DESTINY BOND"),
    [MOVE_PERISH_SONG] = _("PERISH SONG"),
    [MOVE_ICY_WIND] = _("ICY WIND"),
    [MOVE_DETECT] = _("DETECT"),
    [MOVE_BONE_RUSH] = _("BONE RUSH"),
    [MOVE_LOCK_ON] = _("LOCK-ON"),
    [MOVE_OUTRAGE] = _("OUTRAGE"),
    [MOVE_SANDSTORM] = _("SANDSTORM"),
    [MOVE_GIGA_DRAIN] = _("GIGA DRAIN"),
    [MOVE_ENDURE] = _("ENDURE"),
    [MOVE_CHARM] = _("CHARM"),
    [MOVE_ROLLOUT] = _("ROLLOUT"),
    [MOVE_FALSE_SWIPE] = _("FALSE SWIPE"),
    [MOVE_SWAGGER] = _("SWAGGER"),
    [MOVE_MILK_DRINK] = _("MILK DRINK"),
    [MOVE_SPARK] = _("SPARK"),
    [MOVE_FURY_CUTTER] = _("FURY CUTTER"),
    [MOVE_STEEL_WING] = _("STEEL WING"),
    [MOVE_MEAN_LOOK] = _("MEAN LOOK"),
    [MOVE_ATTRACT] = _("ATTRACT"),
    [MOVE_SLEEP_TALK] = _("SLEEP TALK"),
    [MOVE_HEAL_BELL] = _("HEAL BELL"),
    [MOVE_RETURN] = _("RETURN"),
    [MOVE_PRESENT] = _("PRESENT"),
    [MOVE_FRUSTRATION] = _("FRUSTRATION"),
    [MOVE_SAFEGUARD] = _("SAFEGUARD"),
    [MOVE_PAIN_SPLIT] = _("PAIN SPLIT"),
    [MOVE_SACRED_FIRE] = _("SACRED FIRE"),
    [MOVE_MAGNITUDE] = _("MAGNITUDE"),
    [MOVE_DYNAMIC_PUNCH] = _("DYNAMICPUNCH"),
    [MOVE_MEGAHORN] = _("MEGAHORN"),
    [MOVE_DRAGON_BREATH] = _("DRAGONBREATH"),
    [MOVE_BATON_PASS] = _("BATON PASS"),
    [MOVE_ENCORE] = _("ENCORE"),
    [MOVE_PURSUIT] = _("PURSUIT"),
    [MOVE_RAPID_SPIN] = _("RAPID SPIN"),
    [MOVE_SWEET_SCENT] = _("SWEET SCENT"),
    [MOVE_IRON_TAIL] = _("IRON TAIL"),
    [MOVE_METAL_CLAW] = _("METAL CLAW"),
    [MOVE_VITAL_THROW] = _("VITAL THROW"),
    [MOVE_MORNING_SUN] = _("MORNING SUN"),
    [MOVE_SYNTHESIS] = _("SYNTHESIS"),
    [MOVE_MOONLIGHT] = _("MOONLIGHT"),
    [MOVE_HIDDEN_POWER] = _("HIDDEN POWER"),
    [MOVE_CROSS_CHOP] = _("CROSS CHOP"),
    [MOVE_TWISTER] = _("TWISTER"),
    [MOVE_RAIN_DANCE] = _("RAIN DANCE"),
    [MOVE_SUNNY_DAY] = _("SUNNY DAY"),
    [MOVE_CRUNCH] = _("CRUNCH"),
    [MOVE_MIRROR_COAT] = _("MIRROR COAT"),
    [MOVE_PSYCH_UP] = _("PSYCH UP"),
    [MOVE_EXTREME_SPEED] = _("EXTREMESPEED"),
    [MOVE_ANCIENT_POWER] = _("ANCIENTPOWER"),
    [MOVE_SHADOW_BALL] = _("SHADOW BALL"),
    [MOVE_FUTURE_SIGHT] = _("FUTURE SIGHT"),
    [MOVE_ROCK_SMASH] = _("ROCK SMASH"),
    [MOVE_WHIRLPOOL] = _("WHIRLPOOL"),
    [MOVE_BEAT_UP] = _("BEAT UP"),
    [MOVE_FAKE_OUT] = _("FAKE OUT"),
    [MOVE_UPROAR] = _("UPROAR"),
    [MOVE_STOCKPILE] = _("STOCKPILE"),
    [MOVE_SPIT_UP] = _("SPIT UP"),
    [MOVE_SWALLOW] = _("SWALLOW"),
    [MOVE_HEAT_WAVE] = _("HEAT WAVE"),
    [MOVE_HAIL] = _("HAIL"),
    [MOVE_TORMENT] = _("TORMENT"),
    [MOVE_FLATTER] = _("FLATTER"),
    [MOVE_WILL_O_WISP] = _("WILL-O-WISP"),
    [MOVE_MEMENTO] = _("MEMENTO"),
    [MOVE_FACADE] = _("FACADE"),
    [MOVE_FOCUS_PUNCH] = _("FOCUS PUNCH"),
    [MOVE_SMELLING_SALTS] = _("SMELLNGSALTS"),
    [MOVE_FOLLOW_ME] = _("FOLLOW ME"),
    [MOVE_NATURE_POWER] = _("NATURE POWER"),
    [MOVE_CHARGE] = _("CHARGE"),
    [MOVE_TAUNT] = _("TAUNT"),
    [MOVE_HELPING_HAND] = _("HELPING HAND"),
    [MOVE_TRICK] = _("TRICK"),
    [MOVE_ROLE_PLAY] = _("ROLE PLAY"),
    [MOVE_WISH] = _("WISH"),
    [MOVE_ASSIST] = _("ASSIST"),
    [MOVE_INGRAIN] = _("INGRAIN"),
    [MOVE_SUPERPOWER] = _("SUPERPOWER"),
    [MOVE_MAGIC_COAT] = _("MAGIC COAT"),
    [MOVE_RECYCLE] = _("RECYCLE"),
    [MOVE_REVENGE] = _("REVENGE"),
    [MOVE_BRICK_BREAK] = _("BRICK BREAK"),
    [MOVE_YAWN] = _("YAWN"),
    [MOVE_KNOCK_OFF] = _("KNOCK OFF"),
    [MOVE_ENDEAVOR] = _("ENDEAVOR"),
    [MOVE_ERUPTION] = _("ERUPTION"),
    [MOVE_SKILL_SWAP] = _("SKILL SWAP"),
    [MOVE_IMPRISON] = _("IMPRISON"),
    [MOVE_REFRESH] = _("REFRESH"),
    [MOVE_GRUDGE] = _("GRUDGE"),
    [MOVE_SNATCH] = _("SNATCH"),
    [MOVE_SECRET_POWER] = _("SECRET POWER"),
    [MOVE_DIVE] = _("DIVE"),
    [MOVE_ARM_THRUST] = _("ARM THRUST"),
    [MOVE_CAMOUFLAGE] = _("CAMOUFLAGE"),
    [MOVE_TAIL_GLOW] = _("TAIL GLOW"),
    [MOVE_LUSTER_PURGE] = _("LUSTER PURGE"),
    [MOVE_MIST_BALL] = _("MIST BALL"),
    [MOVE_FEATHER_DANCE] = _("FEATHERDANCE"),
    [MOVE_TEETER_DANCE] = _("TEETER DANCE"),
    [MOVE_BLAZE_KICK] = _("BLAZE KICK"),
    [MOVE_MUD_SPORT] = _("MUD SPORT"),
    [MOVE_ICE_BALL] = _("ICE BALL"),
    [MOVE_NEEDLE_ARM] = _("NEEDLE ARM"),
    [MOVE_SLACK_OFF] = _("SLACK OFF"),
    [MOVE_HYPER_VOICE] = _("HYPER VOICE"),
    [MOVE_POISON_FANG] = _("POISON FANG"),
    [MOVE_CRUSH_CLAW] = _("CRUSH CLAW"),
    [MOVE_BLAST_BURN] = _("BLAST BURN"),
    [MOVE_HYDRO_CANNON] = _("HYDRO CANNON"),
    [MOVE_METEOR_MASH] = _("METEOR MASH"),
    [MOVE_ASTONISH] = _("ASTONISH"),
    [MOVE_WEATHER_BALL] = _("WEATHER BALL"),
    [MOVE_AROMATHERAPY] = _("AROMATHERAPY"),
    [MOVE_FAKE_TEARS] = _("FAKE TEARS"),
    [MOVE_AIR_CUTTER] = _("AIR CUTTER"),
    [MOVE_OVERHEAT] = _("OVERHEAT"),
    [MOVE_ODOR_SLEUTH] = _("ODOR SLEUTH"),
    [MOVE_ROCK_TOMB] = _("ROCK TOMB"),
    [MOVE_SILVER_WIND] = _("SILVER WIND"),
    [MOVE_METAL_SOUND] = _("METAL SOUND"),
    [MOVE_GRASS_WHISTLE] = _("GRASSWHISTLE"),
    [MOVE_TICKLE] = _("TICKLE"),
    [MOVE_COSMIC_POWER] = _("COSMIC POWER"),
    [MOVE_WATER_SPOUT] = _("WATER SPOUT"),
    [MOVE_SIGNAL_BEAM] = _("SIGNAL BEAM"),
    [MOVE_SHADOW_PUNCH] = _("SHADOW PUNCH"),
    [MOVE_EXTRASENSORY] = _("EXTRASENSORY"),
    [MOVE_SKY_UPPERCUT] = _("SKY UPPERCUT"),
    [MOVE_SAND_TOMB] = _("SAND TOMB"),
    [MOVE_SHEER_COLD] = _("SHEER COLD"),
    [MOVE_MUDDY_WATER] = _("MUDDY WATER"),
    [MOVE_BULLET_SEED] = _("BULLET SEED"),
    [MOVE_AERIAL_ACE] = _("AERIAL ACE"),
    [MOVE_ICICLE_SPEAR] = _("ICICLE SPEAR"),
    [MOVE_IRON_DEFENSE] = _("IRON DEFENSE"),
    [MOVE_BLOCK] = _("BLOCK"),
    [MOVE_HOWL] = _("HOWL"),
    [MOVE_DRAGON_CLAW] = _("DRAGON CLAW"),
    [MOVE_FRENZY_PLANT] = _("FRENZY PLANT"),
    [MOVE_BULK_UP] = _("BULK UP"),
    [MOVE_BOUNCE] = _("BOUNCE"),
    [MOVE_MUD_SHOT] = _("MUD SHOT"),
    [MOVE_POISON_TAIL] = _("POISON TAIL"),
    [MOVE_COVET] = _("COVET"),
    [MOVE_VOLT_TACKLE] = _("VOLT TACKLE"),
    [MOVE_MAGICAL_LEAF] = _("MAGICAL LEAF"),
    [MOVE_WATER_SPORT] = _("WATER SPORT"),
    [MOVE_CALM_MIND] = _("CALM MIND"),
    [MOVE_LEAF_BLADE] = _("LEAF BLADE"),
    [MOVE_DRAGON_DANCE] = _("DRAGON DANCE"),
    [MOVE_ROCK_BLAST] = _("ROCK BLAST"),
    [MOVE_SHOCK_WAVE] = _("SHOCK WAVE"),
    [MOVE_WATER_PULSE] = _("WATER PULSE"),
    [MOVE_DOOM_DESIRE] = _("DOOM DESIRE"),
    [MOVE_PSYCHO_BOOST] = _("PSYCHO BOOST"),
    [MOVE_ROOST] = _("ROOST"),
    [MOVE_GRAVITY] = _("GRAVITY"),
    [MOVE_MIRACLE_EYE] = _("MIRACLE EYE"),
    [MOVE_WAKE_UP_SLAP] = _("WAKE-UP SLAP"),
    [MOVE_HAMMER_ARM] = _("HAMMER ARM"),
    [MOVE_GYRO_BALL] = _("GYRO BALL"),
    [MOVE_HEALING_WISH] = _("HEALING WISH"),
    [MOVE_BRINE] = _("BRINE"),
    [MOVE_NATURAL_GIFT] = _("NATURAL GIFT"),
    [MOVE_FEINT] = _("FEINT"),
    [MOVE_PLUCK] = _("PLUCK"),
    [MOVE_TAILWIND] = _("TAILWIND"),
    [MOVE_ACUPRESSURE] = _("ACUPRESSURE"),
    [MOVE_METAL_BURST] = _("METAL BURST"),
    [MOVE_U_TURN] = _("U-TURN"),
    [MOVE_CLOSE_COMBAT] = _("CLOSE COMBAT"),
    [MOVE_PAYBACK] = _("PAYBACK"),
    [MOVE_ASSURANCE] = _("ASSURANCE"),
    [MOVE_EMBARGO] = _("EMBARGO"),
    [MOVE_FLING] = _("FLING"),
    [MOVE_PSYCHO_SHIFT] = _("PSYCHO SHIFT"),
    [MOVE_TRUMP_CARD] = _("TRUMP CARD"),
    [MOVE_HEAL_BLOCK] = _("HEAL BLOCK"),
    [MOVE_WRING_OUT] = _("WRING OUT"),
    [MOVE_POWER_TRICK] = _("POWER TRICK"),
    [MOVE_GASTRO_ACID] = _("GASTRO ACID"),
    [MOVE_LUCKY_CHANT] = _("LUCKY CHANT"),
    [MOVE_ME_FIRST] = _("ME FIRST"),
    [MOVE_COPYCAT] = _("COPYCAT"),
    [MOVE_POWER_SWAP] = _("POWER SWAP"),
    [MOVE_GUARD_SWAP] = _("GUARD SWAP"),
    [MOVE_PUNISHMENT] = _("PUNISHMENT"),
    [MOVE_LAST_RESORT] = _("LAST RESORT"),
    [MOVE_WORRY_SEED] = _("WORRY SEED"),
    [MOVE_SUCKER_PUNCH] = _("SUCKER PUNCH"),
    [MOVE_TOXIC_SPIKES] = _("TOXIC SPIKES"),
    [MOVE_HEART_SWAP] = _("HEART SWAP"),
    [MOVE_AQUA_RING] = _("AQUA RING"),
    [MOVE_MAGNET_RISE] = _("MAGNET RISE"),
    [MOVE_FLARE_BLITZ] = _("FLARE BLITZ"),
    [MOVE_FORCE_PALM] = _("FORCE PALM"),
    [MOVE_AURA_SPHERE] = _("AURA SPHERE"),
    [MOVE_ROCK_POLISH] = _("ROCK POLISH"),
    [MOVE_POISON_JAB] = _("POISON JAB"),
    [MOVE_DARK_PULSE] = _("DARK PULSE"),
    [MOVE_NIGHT_SLASH] = _("NIGHT SLASH"),
    [MOVE_AQUA_TAIL] = _("AQUA TAIL"),
    [MOVE_SEED_BOMB] = _("SEED BOMB"),
    [MOVE_AIR_SLASH] = _("AIR SLASH"),
    [MOVE_X_SCISSOR] = _("X-SCISSOR"),
    [MOVE_BUG_BUZZ] = _("BUG BUZZ"),
    [MOVE_DRAGON_PULSE] = _("DRAGON PULSE"),
    [MOVE_DRAGON_RUSH] = _("DRAGON RUSH"),
    [MOVE_POWER_GEM] = _("POWER GEM"),
    [MOVE_DRAIN_PUNCH] = _("DRAIN PUNCH"),
    [MOVE_VACUUM_WAVE] = _("VACUUM WAVE"),
    [MOVE_FOCUS_BLAST] = _("FOCUS BLAST"),
    [MOVE_ENERGY_BALL] = _("ENERGY BALL"),
    [MOVE_BRAVE_BIRD] = _("BRAVE BIRD"),
    [MOVE_EARTH_POWER] = _("EARTH POWER"),
    [MOVE_SWITCHEROO] = _("SWITCHEROO"),
    [MOVE_GIGA_IMPACT] = _("GIGA IMPACT"),
    [MOVE_NASTY_PLOT] = _("NASTY PLOT"),
    [MOVE_BULLET_PUNCH] = _("BULLET PUNCH"),
    [MOVE_AVALANCHE] = _("AVALANCHE"),
    [MOVE_ICE_SHARD] = _("ICE SHARD"),
    [MOVE_SHADOW_CLAW] = _("SHADOW CLAW"),
    [MOVE_THUNDER_FANG] = _("THUNDER FANG"),
    [MOVE_ICE_FANG] = _("ICE FANG"),
    [MOVE_FIRE_FANG] = _("FIRE FANG"),
    [MOVE_SHADOW_SNEAK] = _("SHADOW SNEAK"),
    [MOVE_MUD_BOMB] = _("MUD BOMB"),
    [MOVE_PSYCHO_CUT] = _("PSYCHO CUT"),
    [MOVE_ZEN_HEADBUTT] = _("ZEN HEADBUTT"),
    [MOVE_MIRROR_SHOT] = _("MIRROR SHOT"),
    [MOVE_FLASH_CANNON] = _("FLASH CANNON"),
    [MOVE_ROCK_CLIMB] = _("ROCK CLIMB"),
    [MOVE_DEFOG] = _("DEFOG"),
    [MOVE_TRICK_ROOM] = _("TRICK ROOM"),
    [MOVE_DRACO_METEOR] = _("DRACO METEOR"),
    [MOVE_DISCHARGE] = _("DISCHARGE"),
    [MOVE_LAVA_PLUME] = _("LAVA PLUME"),
    [MOVE_LEAF_STORM] = _("LEAF STORM"),
    [MOVE_POWER_WHIP] = _("POWER WHIP"),
    [MOVE_ROCK_WRECKER] = _("ROCK WRECKER"),
    [MOVE_CROSS_POISON] = _("CROSS POISON"),
    [MOVE_GUNK_SHOT] = _("GUNK SHOT"),
    [MOVE_IRON_HEAD] = _("IRON HEAD"),
    [MOVE_MAGNET_BOMB] = _("MAGNET BOMB"),
    [MOVE_STONE_EDGE] = _("STONE EDGE"),
    [MOVE_CAPTIVATE] = _("CAPTIVATE"),
    [MOVE_STEALTH_ROCK] = _("STEALTH ROCK"),
    [MOVE_GRASS_KNOT] = _("GRASS KNOT"),
    [MOVE_CHATTER] = _("CHATTER"),
    [MOVE_JUDGMENT] = _("JUDGMENT"),
    [MOVE_BUG_BITE] = _("BUG BITE"),
    [MOVE_CHARGE_BEAM] = _("CHARGE BEAM"),
    [MOVE_WOOD_HAMMER] = _("WOOD HAMMER"),
    [MOVE_AQUA_JET] = _("AQUA JET"),
    [MOVE_ATTACK_ORDER] = _("ATTACK ORDER"),
    [MOVE_DEFEND_ORDER] = _("DEFEND ORDER"),
    [MOVE_HEAL_ORDER] = _("HEAL ORDER"),
    [MOVE_HEAD_SMASH] = _("HEAD SMASH"),
    [MOVE_DOUBLE_HIT] = _("DOUBLE HIT"),
    [MOVE_ROAR_OF_TIME] = _("ROAR OF TIME"),
    [MOVE_SPACIAL_REND] = _("SPACIAL REND"),
    [MOVE_LUNAR_DANCE] = _("LUNAR DANCE"),
    [MOVE_CRUSH_GRIP] = _("CRUSH GRIP"),
    [MOVE_MAGMA_STORM] = _("MAGMA STORM"),
    [MOVE_DARK_VOID] = _("DARK VOID"),
    [MOVE_SEED_FLARE] = _("SEED FLARE"),
    [MOVE_OMINOUS_WIND] = _("OMINOUS WIND"),
    [MOVE_SHADOW_FORCE] = _("SHADOW FORCE"),
    [MOVE_HONE_CLAWS] = _("HONE CLAWS"),
    [MOVE_WIDE_GUARD] = _("WIDE GUARD"),
    [MOVE_GUARD_SPLIT] = _("GUARD SPLIT"),
    [MOVE_POWER_SPLIT] = _("POWER SPLIT"),
    [MOVE_WONDER_ROOM] = _("WONDER ROOM"),
    [MOVE_PSYSHOCK] = _("PSYSHOCK"),
    [MOVE_VENOSHOCK] = _("VENOSHOCK"),
    [MOVE_AUTOTOMIZE] = _("AUTOTOMIZE"),
    [MOVE_RAGE_POWDER] = _("RAGE POWDER"),
    [MOVE_TELEKINESIS] = _("TELEKINESIS"),
    [MOVE_MAGIC_ROOM] = _("MAGIC ROOM"),
    [MOVE_SMACK_DOWN] = _("SMACK DOWN"),
    [MOVE_STORM_THROW] = _("STORM THROW"),
    [MOVE_FLAME_BURST] = _("FLAME BURST"),
    [MOVE_SLUDGE_WAVE] = _("SLUDGE WAVE"),
    [MOVE_QUIVER_DANCE] = _("QUIVER DANCE"),
    [MOVE_HEAVY_SLAM] = _("HEAVY SLAM"),
    [MOVE_SYNCHRONOISE] = _("SYNCHRONOISE"),
    [MOVE_ELECTRO_BALL] = _("ELECTRO BALL"),
    [MOVE_SOAK] = _("SOAK"),
    [MOVE_FLAME_CHARGE] = _("FLAME CHARGE"),
    [MOVE_COIL] = _("COIL"),
    [MOVE_LOW_SWEEP] = _("LOW SWEEP"),
    [MOVE_ACID_SPRAY] = _("ACID SPRAY"),
    [MOVE_FOUL_PLAY] = _("FOUL PLAY"),
    [MOVE_SIMPLE_BEAM] = _("SIMPLE BEAM"),
    [MOVE_ENTRAINMENT] = _("ENTRAINMENT"),
    [MOVE_AFTER_YOU] = _("AFTER YOU"),
    [MOVE_ROUND] = _("ROUND"),
    [MOVE_ECHOED_VOICE] = _("ECHOED VOICE"),
    [MOVE_CHIP_AWAY] = _("CHIP AWAY"),
    [MOVE_CLEAR_SMOG] = _("CLEAR SMOG"),
    [MOVE_STORED_POWER] = _("STORED POWER"),
    [MOVE_QUICK_GUARD] = _("QUICK GUARD"),
    [MOVE_ALLY_SWITCH] = _("ALLY SWITCH"),
    [MOVE_SCALD] = _("SCALD"),
    [MOVE_SHELL_SMASH] = _("SHELL SMASH"),
    [MOVE_HEAL_PULSE] = _("HEAL PULSE"),
    [MOVE_HEX] = _("HEX"),
    [MOVE_SKY_DROP] = _("SKY DROP"),
    [MOVE_SHIFT_GEAR] = _("SHIFT GEAR"),
    [MOVE_CIRCLE_THROW] = _("CIRCLE THROW"),
    [MOVE_INCINERATE] = _("INCINERATE"),
    [MOVE_QUASH] = _("QUASH"),
    [MOVE_ACROBATICS] = _("ACROBATICS"),
    [MOVE_REFLECT_TYPE] = _("REFLECT TYPE"),
    [MOVE_RETALIATE] = _("RETALIATE"),
    [MOVE_FINAL_GAMBIT] = _("FINAL GAMBIT"),
    [MOVE_BESTOW] = _("BESTOW"),
    [MOVE_INFERNO] = _("INFERNO"),
    [MOVE_WATER_PLEDGE] = _("WATER PLEDGE"),
    [MOVE_FIRE_PLEDGE] = _("FIRE PLEDGE"),
    [MOVE_GRASS_PLEDGE] = _("GRASS PLEDGE"),
    [MOVE_VOLT_SWITCH] = _("VOLT SWITCH"),
    [MOVE_STRUGGLE_BUG] = _("STRUGGLE BUG"),
    [MOVE_BULLDOZE] = _("BULLDOZE"),
    [MOVE_FROST_BREATH] = _("FROST BREATH"),
    [MOVE_DRAGON_TAIL] = _("DRAGON TAIL"),
    [MOVE_WORK_UP] = _("WORK UP"),
    [MOVE_ELECTROWEB] = _("ELECTROWEB"),
    [MOVE_WILD_CHARGE] = _("WILD CHARGE"),
    [MOVE_DRILL_RUN] = _("DRILL RUN"),
    [MOVE_DUAL_CHOP] = _("DUAL CHOP"),
    [MOVE_HEART_STAMP] = _("HEART STAMP"),
    [MOVE_HORN_LEECH] = _("HORN LEECH"),
    [MOVE_SACRED_SWORD] = _("SACRED SWORD"),
    [MOVE_RAZOR_SHELL] = _("RAZOR SHELL"),
    [MOVE_HEAT_CRASH] = _("HEAT CRASH"),
    [MOVE_LEAF_TORNADO] = _("LEAF TORNADO"),
    [MOVE_STEAMROLLER] = _("STEAMROLLER"),
    [MOVE_COTTON_GUARD] = _("COTTON GUARD"),
    [MOVE_NIGHT_DAZE] = _("NIGHT DAZE"),
    [MOVE_PSYSTRIKE] = _("PSYSTRIKE"),
    [MOVE_TAIL_SLAP] = _("TAIL SLAP"),
    [MOVE_HURRICANE] = _("HURRICANE"),
    [MOVE_HEAD_CHARGE] = _("HEAD CHARGE"),
    [MOVE_GEAR_GRIND] = _("GEAR GRIND"),
    [MOVE_SEARING_SHOT] = _("SEARING SHOT"),
    [MOVE_TECHNO_BLAST] = _("TECHNO BLAST"),
    [MOVE_RELIC_SONG] = _("RELIC SONG"),
    [MOVE_SECRET_SWORD] = _("SECRET SWORD"),
    [MOVE_GLACIATE] = _("GLACIATE"),
    [MOVE_BOLT_STRIKE] = _("BOLT STRIKE"),
    [MOVE_BLUE_FLARE] = _("BLUE FLARE"),
    [MOVE_FIERY_DANCE] = _("FIERY DANCE"),
    [MOVE_FREEZE_SHOCK] = _("FREEZE SHOCK"),
    [MOVE_ICE_BURN] = _("ICE BURN"),
    [MOVE_SNARL] = _("SNARL"),
    [MOVE_ICICLE_CRASH] = _("ICICLE CRASH"),
    [MOVE_V_CREATE] = _("V-CREATE"),
    [MOVE_FUSION_FLARE] = _("FUSION FLARE"),
    [MOVE_FUSION_BOLT] = _("FUSION BOLT"),
    [MOVE_FLYING_PRESS] = _("FLYING PRESS"),
    [MOVE_MAT_BLOCK] = _("MAT BLOCK"),
    [MOVE_BELCH] = _("BELCH"),
    [MOVE_ROTOTILLER] = _("ROTOTILLER"),
    [MOVE_STICKY_WEB] = _("STICKY WEB"),
    [MOVE_FELL_STINGER] = _("FELL STINGER"),
    [MOVE_PHANTOM_FORCE] = _("PHANTOMFORCE"),
    [MOVE_TRICK_OR_TREAT] = _("TRICKORTREAT"),
    [MOVE_NOBLE_ROAR] = _("NOBLE ROAR"),
    [MOVE_ION_DELUGE] = _("ION DELUGE"),
    [MOVE_PARABOLIC_CHARGE] = _("PARABOLCCHRG"),
    [MOVE_FORESTS_CURSE] = _("FOREST'SCURS"),
    [MOVE_PETAL_BLIZZARD] = _("PETALBLIZZRD"),
    [MOVE_FREEZE_DRY] = _("FREEZE-DRY"),
    [MOVE_DISARMING_VOICE] = _("DISRMNGVOICE"),
    [MOVE_PARTING_SHOT] = _("PARTING SHOT"),
    [MOVE_TOPSY_TURVY] = _("TOPSY-TURVY"),
    [MOVE_DRAINING_KISS] = _("DRAININGKISS"),
    [MOVE_CRAFTY_SHIELD] = _("CRAFTYSHIELD"),
    [MOVE_FLOWER_SHIELD] = _("FLOWERSHIELD"),
    [MOVE_GRASSY_TERRAIN] = _("GRSSYTERRAIN"),
    [MOVE_MISTY_TERRAIN] = _("MISTYTERRAIN"),
    [MOVE_ELECTRIFY] = _("ELECTRIFY"),
    [MOVE_PLAY_ROUGH] = _("PLAY ROUGH"),
    [MOVE_FAIRY_WIND] = _("FAIRY WIND"),
    [MOVE_MOONBLAST] = _("MOONBLAST"),
    [MOVE_BOOMBURST] = _("BOOMBURST"),
    [MOVE_FAIRY_LOCK] = _("FAIRY LOCK"),
    [MOVE_KINGS_SHIELD] = _("KING'SSHIELD"),
    [MOVE_PLAY_NICE] = _("PLAY NICE"),
    [MOVE_CONFIDE] = _("CONFIDE"),
    [MOVE_DIAMOND_STORM] = _("DIAMONDSTORM"),
    [MOVE_STEAM_ERUPTION] = _("STEAMERPTION"),
    [MOVE_HYPERSPACE_HOLE] = _("HYPRSPCEHOLE"),
    [MOVE_WATER_SHURIKEN] = _("WATRSHURIKEN"),
    [MOVE_MYSTICAL_FIRE] = _("MYSTICALFIRE"),
    [MOVE_SPIKY_SHIELD] = _("SPIKY SHIELD"),
    [MOVE_AROMATIC_MIST] = _("AROMATICMIST"),
    [MOVE_EERIE_IMPULSE] = _("EERIEIMPULSE"),
    [MOVE_VENOM_DRENCH] = _("VENOM DRENCH"),
    [MOVE_POWDER] = _("POWDER"),
    [MOVE_GEOMANCY] = _("GEOMANCY"),
    [MOVE_MAGNETIC_FLUX] = _("MAGNETICFLUX"),
    [MOVE_HAPPY_HOUR] = _("HAPPY HOUR"),
    [MOVE_ELECTRIC_TERRAIN] = _("ELCTRCTRRAIN"),
    [MOVE_DAZZLING_GLEAM] = _("DAZZLNGGLEAM"),
    [MOVE_CELEBRATE] = _("CELEBRATE"),
    [MOVE_HOLD_HANDS] = _("HOLD HANDS"),
    [MOVE_BABY_DOLL_EYES] = _("BABYDOLLEYES"),
    [MOVE_NUZZLE] = _("NUZZLE"),
    [MOVE_HOLD_BACK] = _("HOLD BACK"),
    [MOVE_INFESTATION] = _("INFESTATION"),
    [MOVE_POWER_UP_PUNCH] = _("POWERUPPUNCH"),
    [MOVE_OBLIVION_WING] = _("OBLIVIONWING"),
    [MOVE_THOUSAND_ARROWS] = _("THOUSNDARRWS"),
    [MOVE_THOUSAND_WAVES] = _("THOUSNDWAVES"),
    [MOVE_LANDS_WRATH] = _("LAND'S WRATH"),
    [MOVE_LIGHT_OF_RUIN] = _("LIGHTOFRUIN"),
    [MOVE_ORIGIN_PULSE] = _("ORIGIN PULSE"),
    [MOVE_PRECIPICE_BLADES] = _("PRCIPCEBLDES"),
    [MOVE_DRAGON_ASCENT] = _("DRAGONASCENT"),
    [MOVE_HYPERSPACE_FURY] = _("HYPRSPCEFURY"),
    [MOVE_SHORE_UP] = _("SHORE UP"),
    [MOVE_FIRST_IMPRESSION] = _("FRSTIMPRESSN"),
    [MOVE_BANEFUL_BUNKER] = _("BANEFULBUNKR"),
    [MOVE_SPIRIT_SHACKLE] = _("SPIRITSHACKL"),
    [MOVE_DARKEST_LARIAT] = _("DARKSTLARIAT"),
    [MOVE_SPARKLING_ARIA] = _("SPARKLNGARIA"),
    [MOVE_ICE_HAMMER] = _("ICE HAMMER"),
    [MOVE_FLORAL_HEALING] = _("FLORALHEALNG"),
    [MOVE_HIGH_HORSEPOWER] = _("HIGHHORSEPWR"),
    [MOVE_STRENGTH_SAP] = _("STRENGTH SAP"),
    [MOVE_SOLAR_BLADE] = _("SOLAR BLADE"),
    [MOVE_LEAFAGE] = _("LEAFAGE"),
    [MOVE_SPOTLIGHT] = _("SPOTLIGHT"),
    [MOVE_TOXIC_THREAD] = _("TOXIC THREAD"),
    [MOVE_LASER_FOCUS] = _("LASER FOCUS"),
    [MOVE_GEAR_UP] = _("GEAR UP"),
    [MOVE_THROAT_CHOP] = _("THROAT CHOP"),
    [MOVE_POLLEN_PUFF] = _("POLLEN PUFF"),
    [MOVE_ANCHOR_SHOT] = _("ANCHOR SHOT"),
    [MOVE_PSYCHIC_TERRAIN] = _("PSYCHCTRRAIN"),
    [MOVE_LUNGE] = _("LUNGE"),
    [MOVE_FIRE_LASH] = _("FIRE LASH"),
    [MOVE_POWER_TRIP] = _("POWER TRIP"),
    [MOVE_BURN_UP] = _("BURN UP"),
    [MOVE_SPEED_SWAP] = _("SPEED SWAP"),
    [MOVE_SMART_STRIKE] = _("SMART STRIKE"),
    [MOVE_PURIFY] = _("PURIFY"),
    [MOVE_REVELATION_DANCE] = _("RVLATIONDNCE"),
    [MOVE_CORE_ENFORCER] = _("COREENFORCER"),
    [MOVE_TROP_KICK] = _("TROP KICK"),
    [MOVE_INSTRUCT] = _("INSTRUCT"),
    [MOVE_BEAK_BLAST] = _("BEAK BLAST"),
    [MOVE_CLANGING_SCALES] = _("CLNGNGSCALES"),
    [MOVE_DRAGON_HAMMER] = _("DRAGONHAMMER"),
    [MOVE_BRUTAL_SWING] = _("BRUTAL SWING"),
    [MOVE_AURORA_VEIL] = _("AURORA VEIL"),
    [MOVE_SHELL_TRAP] = _("SHELL TRAP"),
    [MOVE_FLEUR_CANNON] = _("FLEUR CANNON"),
    [MOVE_PSYCHIC_FANGS] = _("PSYCHICFANGS"),
    [MOVE_STOMPING_TANTRUM] = _("STMPNGTANTRM"),
    [MOVE_SHADOW_BONE] = _("SHADOW BONE"),
    [MOVE_ACCELEROCK] = _("ACCELEROCK"),
    [MOVE_LIQUIDATION] = _("LIQUIDATION"),
    [MOVE_PRISMATIC_LASER] = _("PRSMATICLASR"),
    [MOVE_SPECTRAL_THIEF] = _("SPECTRLTHIEF"),
    [MOVE_SUNSTEEL_STRIKE] = _("SNSTEELSTRKE"),
    [MOVE_MOONGEIST_BEAM] = _("MOONGESTBEAM"),
    [MOVE_TEARFUL_LOOK] = _("TEARFUL LOOK"),
    [MOVE_ZING_ZAP] = _("ZING ZAP"),
    [MOVE_NATURES_MADNESS] = _("NATUR'SMADNS"),
    [MOVE_MULTI_ATTACK] = _("MULTI-ATTACK"),
    [MOVE_MIND_BLOWN] = _("MIND BLOWN"),
    [MOVE_PLASMA_FISTS] = _("PLASMA FISTS"),
    [MOVE_PHOTON_GEYSER] = _("PHOTONGEYSER"),
    [MOVE_ZIPPY_ZAP] = _("ZIPPY ZAP"),
    [MOVE_SPLISHY_SPLASH] = _("SPLISHYSPLSH"),
    [MOVE_FLOATY_FALL] = _("FLOATY FALL"),
    [MOVE_PIKA_PAPOW] = _("PIKA PAPOW"),
    [MOVE_BOUNCY_BUBBLE] = _("BOUNCYBUBBLE"),
    [MOVE_BUZZY_BUZZ] = _("BUZZY BUZZ"),
    [MOVE_SIZZLY_SLIDE] = _("SIZZLY SLIDE"),
    [MOVE_GLITZY_GLOW] = _("GLITZY GLOW"),
    [MOVE_BADDY_BAD] = _("BADDY BAD"),
    [MOVE_SAPPY_SEED] = _("SAPPY SEED"),
    [MOVE_FREEZY_FROST] = _("FREEZY FROST"),
    [MOVE_SPARKLY_SWIRL] = _("SPARKLYSWIRL"),
    [MOVE_VEEVEE_VOLLEY] = _("VEEVEEVOLLEY"),
    [MOVE_DOUBLE_IRON_BASH] = _("DUBLIRONBASH"),
    [MOVE_DYNAMAX_CANNON] = _("DYNAMXCANNON"),
    [MOVE_SNIPE_SHOT] = _("SNIPE SHOT"),
    [MOVE_JAW_LOCK] = _("JAW LOCK"),
    [MOVE_STUFF_CHEEKS] = _("STUFF CHEEKS"),
    [MOVE_NO_RETREAT] = _("NO RETREAT"),
    [MOVE_TAR_SHOT] = _("TAR SHOT"),
    [MOVE_MAGIC_POWDER] = _("MAGIC POWDER"),
    [MOVE_DRAGON_DARTS] = _("DRAGON DARTS"),
    [MOVE_TEATIME] = _("TEATIME"),
    [MOVE_OCTOLOCK] = _("OCTOLOCK"),
    [MOVE_BOLT_BEAK] = _("BOLT BEAK"),
    [MOVE_FISHIOUS_REND] = _("FISHIOUSREND"),
    [MOVE_COURT_CHANGE] = _("COURT CHANGE"),
    [MOVE_CLANGOROUS_SOUL] = _("CLNGROUSSOUL"),
    [MOVE_BODY_PRESS] = _("BODY PRESS"),
    [MOVE_DECORATE] = _("DECORATE"),
    [MOVE_DRUM_BEATING] = _("DRUM BEATING"),
    [MOVE_SNAP_TRAP] = _("SNAP TRAP"),
    [MOVE_PYRO_BALL] = _("PYRO BALL"),
    [MOVE_BEHEMOTH_BLADE] = _("BEHEMTHBLADE"),
    [MOVE_BEHEMOTH_BASH] = _("BEHEMOTHBASH"),
    [MOVE_AURA_WHEEL] = _("AURA WHEEL"),
    [MOVE_BREAKING_SWIPE] = _("BREAKNGSWIPE"),
    [MOVE_BRANCH_POKE] = _("BRANCH POKE"),
    [MOVE_OVERDRIVE] = _("OVERDRIVE"),
    [MOVE_APPLE_ACID] = _("APPLE ACID"),
    [MOVE_GRAV_APPLE] = _("GRAV APPLE"),
    [MOVE_SPIRIT_BREAK] = _("SPIRIT BREAK"),
    [MOVE_STRANGE_STEAM] = _("STRANGESTEAM"),
    [MOVE_LIFE_DEW] = _("LIFE DEW"),
    [MOVE_OBSTRUCT] = _("OBSTRUCT"),
    [MOVE_FALSE_SURRENDER] = _("FALSSURRENDR"),
    [MOVE_METEOR_ASSAULT] = _("METEORASSALT"),
    [MOVE_ETERNABEAM] = _("ETERNABEAM"),
    [MOVE_STEEL_BEAM] = _("STEEL BEAM"),
    [MOVE_EXPANDING_FORCE] = _("EXPANDNGFORC"),
    [MOVE_STEEL_ROLLER] = _("STEEL ROLLER"),
    [MOVE_SCALE_SHOT] = _("SCALE SHOT"),
    [MOVE_METEOR_BEAM] = _("METEOR BEAM"),
    [MOVE_SHELL_SIDE_ARM] = _("SHELLSIDEARM"),
    [MOVE_MISTY_EXPLOSION] = _("MSTYEXPLSION"),
    [MOVE_GRASSY_GLIDE] = _("GRASSY GLIDE"),
    [MOVE_RISING_VOLTAGE] = _("RISNGVOLTAGE"),
    [MOVE_TERRAIN_PULSE] = _("TERRAINPULSE"),
    [MOVE_SKITTER_SMACK] = _("SKITTERSMACK"),
    [MOVE_BURNING_JEALOUSY] = _("BRNINGJELOSY"),
    [MOVE_LASH_OUT] = _("LASH OUT"),
    [MOVE_POLTERGEIST] = _("POLTERGEIST"),
    [MOVE_CORROSIVE_GAS] = _("CORROSIVEGAS"),
    [MOVE_COACHING] = _("COACHING"),
    [MOVE_FLIP_TURN] = _("FLIP TURN"),
    [MOVE_TRIPLE_AXEL] = _("TRIPLE AXEL"),
    [MOVE_DUAL_WINGBEAT] = _("DUALWINGBEAT"),
    [MOVE_SCORCHING_SANDS] = _("SCORCHNGSNDS"),
    [MOVE_JUNGLE_HEALING] = _("JUNGLEHEALNG"),
    [MOVE_WICKED_BLOW] = _("WICKED BLOW"),
    [MOVE_SURGING_STRIKES] = _("SURGNGSTRKES"),
    [MOVE_THUNDER_CAGE] = _("THUNDER CAGE"),
    [MOVE_DRAGON_ENERGY] = _("DRAGONENERGY"),
    [MOVE_FREEZING_GLARE] = _("FREEZNGGLARE"),
    [MOVE_FIERY_WRATH] = _("FIERY WRATH"),
    [MOVE_THUNDEROUS_KICK] = _("THNDERUSKICK"),
    [MOVE_GLACIAL_LANCE] = _("GLACIALLANCE"),
    [MOVE_ASTRAL_BARRAGE] = _("ASTRLBARRAGE"),
    [MOVE_EERIE_SPELL] = _("EERIE SPELL"),
    [MOVE_DIRE_CLAW] = _("DIRE CLAW"),
    [MOVE_PSYSHIELD_BASH] = _("PSYSHIELDBSH"),
    [MOVE_POWER_SHIFT] = _("POWER SHIFT"),
    [MOVE_STONE_AXE] = _("STONE AXE"),
    [MOVE_SPRINGTIDE_STORM] = _("SPRNGTDESTRM"),
    [MOVE_MYSTICAL_POWER] = _("MYSTCALPOWER"),
    [MOVE_RAGING_FURY] = _("RAGING FURY"),
    [MOVE_WAVE_CRASH] = _("WAVE CRASH"),
    [MOVE_CHLOROBLAST] = _("CHLOROBLAST"),
    [MOVE_MOUNTAIN_GALE] = _("MOUNTAINGALE"),
    [MOVE_VICTORY_DANCE] = _("VICTORYDANCE"),
    [MOVE_HEADLONG_RUSH] = _("HEADLONGRUSH"),
    [MOVE_BARB_BARRAGE] = _("BARB BARRAGE"),
    [MOVE_ESPER_WING] = _("ESPER WING"),
    [MOVE_BITTER_MALICE] = _("BITTERMALICE"),
    [MOVE_SHELTER] = _("SHELTER"),
    [MOVE_TRIPLE_ARROWS] = _("TRIPLEARROWS"),
    [MOVE_INFERNAL_PARADE] = _("INFRNLPARADE"),
    [MOVE_CEASELESS_EDGE] = _("CEASLESSEDGE"),
    [MOVE_BLEAKWIND_STORM] = _("BLEKWNDSTORM"),
    [MOVE_WILDBOLT_STORM] = _("WILDBLTSTORM"),
    [MOVE_SANDSEAR_STORM] = _("SNDSEARSTORM"),
    [MOVE_LUNAR_BLESSING] = _("LUNARBLESSNG"),
    [MOVE_TAKE_HEART] = _("TAKE HEART"),
    [MOVE_TERA_BLAST] = _("TERA BLAST"),
    [MOVE_SILK_TRAP] = _("SILK TRAP"),
    [MOVE_AXE_KICK] = _("AXE KICK"),
    [MOVE_LAST_RESPECTS] = _("LASTRESPECTS"),
    [MOVE_LUMINA_CRASH] = _("LUMINA CRASH"),
    [MOVE_ORDER_UP] = _("ORDER UP"),
    [MOVE_JET_PUNCH] = _("JET PUNCH"),
    [MOVE_SPICY_EXTRACT] = _("SPICYEXTRACT"),
    [MOVE_SPIN_OUT] = _("SPIN OUT"),
    [MOVE_POPULATION_BOMB] = _("POPLATINBOMB"),
    [MOVE_ICE_SPINNER] = _("ICE SPINNER"),
    [MOVE_GLAIVE_RUSH] = _("GLAIVE RUSH"),
    [MOVE_REVIVAL_BLESSING] = _("REVIVLBLESNG"),
    [MOVE_SALT_CURE] = _("SALT CURE"),
    [MOVE_TRIPLE_DIVE] = _("TRIPLE DIVE"),
    [MOVE_MORTAL_SPIN] = _("MORTAL SPIN"),
    [MOVE_DOODLE] = _("DOODLE"),
    [MOVE_FILLET_AWAY] = _("FILLET AWAY"),
    [MOVE_KOWTOW_CLEAVE] = _("KOWTOWCLEAVE"),
    [MOVE_FLOWER_TRICK] = _("FLOWER TRICK"),
    [MOVE_TORCH_SONG] = _("TORCH SONG"),
    [MOVE_AQUA_STEP] = _("AQUA STEP"),
    [MOVE_RAGING_BULL] = _("RAGING BULL"),
    [MOVE_MAKE_IT_RAIN] = _("MAKE IT RAIN"),
    [MOVE_RUINATION] = _("RUINATION"),
    [MOVE_COLLISION_COURSE] = _("COLISINCOURS"),
    [MOVE_ELECTRO_DRIFT] = _("ELECTRODRIFT"),
    [MOVE_SHED_TAIL] = _("SHED TAIL"),
    [MOVE_CHILLY_RECEPTION] = _("CHILRECEPTIN"),
    [MOVE_TIDY_UP] = _("TIDY UP"),
    [MOVE_SNOWSCAPE] = _("SNOWSCAPE"),
    [MOVE_POUNCE] = _("POUNCE"),
    [MOVE_TRAILBLAZE] = _("TRAILBLAZE"),
    [MOVE_CHILLING_WATER] = _("CHILLINGWATR"),
    [MOVE_HYPER_DRILL] = _("HYPER DRILL"),
    [MOVE_TWIN_BEAM] = _("TWIN BEAM"),
    [MOVE_RAGE_FIST] = _("RAGE FIST"),
    [MOVE_ARMOR_CANNON] = _("ARMOR CANNON"),
    [MOVE_BITTER_BLADE] = _("BITTER BLADE"),
    [MOVE_DOUBLE_SHOCK] = _("DOUBLE SHOCK"),
    [MOVE_GIGATON_HAMMER] = _("GIGATONHAMMR"),
    [MOVE_COMEUPPANCE] = _("COMEUPPANCE"),
    [MOVE_AQUA_CUTTER] = _("AQUA CUTTER"),
    [MOVE_BLAZING_TORQUE] = _("BLAZNGTORQUE"),
    [MOVE_WICKED_TORQUE] = _("WICKEDTORQUE"),
    [MOVE_NOXIOUS_TORQUE] = _("NOXIUSTORQUE"),
    [MOVE_COMBAT_TORQUE] = _("COMBATTORQUE"),
    [MOVE_MAGICAL_TORQUE] = _("MAGICLTORQUE"),
    [MOVE_PSYBLADE] = _("PSYBLADE"),
    [MOVE_HYDRO_STEAM] = _("HYDRO STEAM"),
    [MOVE_BLOOD_MOON] = _("BLOOD MOON"),
    [MOVE_MATCHA_GOTCHA] = _("MATCHAGOTCHA"),
    [MOVE_SYRUP_BOMB] = _("SYRUP BOMB"),
    [MOVE_IVY_CUDGEL] = _("IVY CUDGEL"),
    [MOVE_ELECTRO_SHOT] = _("ELECTRO SHOT"),
    [MOVE_TERA_STARSTORM] = _("TERASTARSTRM"),
    [MOVE_FICKLE_BEAM] = _("FICKLE BEAM"),
    [MOVE_BURNING_BULWARK] = _("BURNNGBULWRK"),
    [MOVE_THUNDERCLAP] = _("THUNDERCLAP"),
    [MOVE_MIGHTY_CLEAVE] = _("MIGHTYCLEAVE"),
    [MOVE_TACHYON_CUTTER] = _("TACHYONCUTTR"),
    [MOVE_HARD_PRESS] = _("HARD PRESS"),
    [MOVE_DRAGON_CHEER] = _("DRAGON CHEER"),
    [MOVE_ALLURING_VOICE] = _("ALLURNGVOICE"),
    [MOVE_TEMPER_FLARE] = _("TEMPER FLARE"),
    [MOVE_SUPERCELL_SLAM] = _("SUPRCELLSLAM"),
    [MOVE_PSYCHIC_NOISE] = _("PSYCHICNOISE"),
    [MOVE_UPPER_HAND] = _("UPPER HAND"),
    [MOVE_MALIGNANT_CHAIN] = _("MALIGNNTCHAN")
};

// ---------------------------------------------------------------------------
// Section 2: Move Description Strings
// ---------------------------------------------------------------------------

const u8 gMoveDescription_Pound[] = _("Pounds the foe with\nforelegs or tail.");
const u8 gMoveDescription_KarateChop[] = _("A chopping attack with a\nhigh critical-hit ratio.");
const u8 gMoveDescription_DoubleSlap[] = _("Repeatedly slaps the foe\n2 to 5 times.");
const u8 gMoveDescription_CometPunch[] = _("Repeatedly punches the foe\n2 to 5 times.");
const u8 gMoveDescription_MegaPunch[] = _("A strong punch thrown with\nincredible power.");
const u8 gMoveDescription_PayDay[] = _("Throws coins at the foe.\nMoney is recovered after.");
const u8 gMoveDescription_FirePunch[] = _("A fiery punch that may burn\nthe foe.");
const u8 gMoveDescription_IcePunch[] = _("An icy punch that may\nleave the foe with frostbite.");
const u8 gMoveDescription_ThunderPunch[] = _("An electrified punch that\nmay paralyze the foe.");
const u8 gMoveDescription_Scratch[] = _("Scratches the foe with\nsharp claws.");
const u8 gMoveDescription_ViseGrip[] = _("Grips the foe with large and\npowerful pincers.");
const u8 gMoveDescription_Guillotine[] = _("A powerful pincer attack\nthat may cause fainting.");
const u8 gMoveDescription_RazorWind[] = _("A 2-turn move that strikes\nthe foe on the 2nd turn.");
const u8 gMoveDescription_SwordsDance[] = _("A fighting dance that\nsharply raises Attack.");
const u8 gMoveDescription_Cut[] = _("Cuts the foe with sharp\nscythes, claws, etc.");
const u8 gMoveDescription_Gust[] = _("Strikes the foe with a gust\nof wind whipped up by wings.");
const u8 gMoveDescription_WingAttack[] = _("Strikes the foe with wings\nspread wide.");
const u8 gMoveDescription_Whirlwind[] = _("Blows away the foe with\nwind and ends the battle.");
const u8 gMoveDescription_Fly[] = _("Flies up on the first turn,\nthen strikes the next turn.");
const u8 gMoveDescription_Bind[] = _("Binds and squeezes the foe\nfor  turns.");
const u8 gMoveDescription_Slam[] = _("Slams the foe with a long\ntail, vine, etc.");
const u8 gMoveDescription_VineWhip[] = _("Strikes the foe with\nslender, whiplike vines.");
const u8 gMoveDescription_Stomp[] = _("Stomps the enemy with a big\nfoot. May cause flinching.");
const u8 gMoveDescription_DoubleKick[] = _("A double-kicking attack\nthat strikes the foe twice.");
const u8 gMoveDescription_MegaKick[] = _("An extremely powerful kick\nwith intense force.");
const u8 gMoveDescription_JumpKick[] = _("A strong jumping kick. May\nmiss and hurt the kicker.");
const u8 gMoveDescription_RollingKick[] = _("A fast kick delivered from\na rapid spin.");
const u8 gMoveDescription_SandAttack[] = _("Reduces the foe's accuracy\nby hurling sand in its face.");
const u8 gMoveDescription_Headbutt[] = _("A ramming attack that may\ncause flinching.");
const u8 gMoveDescription_HornAttack[] = _("Jabs the foe with sharp\nhorns.");
const u8 gMoveDescription_FuryAttack[] = _("Jabs the foe 2 to 5 times\nwith sharp horns, etc.");
const u8 gMoveDescription_HornDrill[] = _("A one-hit KO attack that\nuses a horn like a drill.");
const u8 gMoveDescription_Tackle[] = _("Charges the foe with a full-\nbody tackle.");
const u8 gMoveDescription_BodySlam[] = _("A full-body slam that may\ncause paralysis.");
const u8 gMoveDescription_Wrap[] = _("Wraps and squeezes the foe\n times with vines, etc.");
const u8 gMoveDescription_TakeDown[] = _("A reckless charge attack\nthat also hurts the user.");
const u8 gMoveDescription_Thrash[] = _("A rampage of 2 to 3 turns\nthat confuses the user.");
const u8 gMoveDescription_DoubleEdge[] = _("A life-risking tackle that\nalso hurts the user.");
const u8 gMoveDescription_TailWhip[] = _("Wags the tail to lower the\nfoe's Defense.");
const u8 gMoveDescription_PoisonSting[] = _("A toxic attack with barbs,\netc., that may poison.");
const u8 gMoveDescription_Twineedle[] = _("Stingers on the forelegs\njab the foe twice.");
const u8 gMoveDescription_PinMissile[] = _("Sharp pins are fired to\nstrike 2 to 5 times.");
const u8 gMoveDescription_Leer[] = _("Frightens the foe with a\nleer to lower Defense.");
const u8 gMoveDescription_Bite[] = _("Bites with vicious fangs.\nMay cause flinching.");
const u8 gMoveDescription_Growl[] = _("Growls cutely to reduce the\nfoe's Attack.");
const u8 gMoveDescription_Roar[] = _("Makes the foe flee to end\nthe battle.");
const u8 gMoveDescription_Sing[] = _("A soothing song lulls the\nfoe into a deep slumber.");
const u8 gMoveDescription_Supersonic[] = _("Emits bizarre sound waves\nthat may confuse the foe.");
const u8 gMoveDescription_SonicBoom[] = _("Launches shock waves that\nalways inflict 20 HP damage.");
const u8 gMoveDescription_Disable[] = _("Psychically disables one of\nthe foe's moves.");
const u8 gMoveDescription_Acid[] = _("Sprays a hide-melting acid.\nMay lower Sp. Def.");
const u8 gMoveDescription_Ember[] = _("A weak fire attack that may\ninflict a burn.");
const u8 gMoveDescription_Flamethrower[] = _("A powerful fire attack that\nmay inflict a burn.");
const u8 gMoveDescription_Mist[] = _("Creates a mist that stops\nreduction of abilities.");
const u8 gMoveDescription_WaterGun[] = _("Squirts water to attack\nthe foe.");
const u8 gMoveDescription_HydroPump[] = _("Blasts water at high power\nto strike the foe.");
const u8 gMoveDescription_Surf[] = _("Creates a huge wave, then\ncrashes it down on the foe.");
const u8 gMoveDescription_IceBeam[] = _("Blasts the foe with an icy\nbeam. May cause frostbite.");
const u8 gMoveDescription_Blizzard[] = _("Hits the foe with an icy\nstorm. May cause frostbite.");
const u8 gMoveDescription_Psybeam[] = _("Fires a peculiar ray that\nmay confuse the foe.");
const u8 gMoveDescription_BubbleBeam[] = _("Forcefully sprays bubbles\nthat may lower Speed.");
const u8 gMoveDescription_AuroraBeam[] = _("Fires a rainbow-colored\nbeam that may lower Attack.");
const u8 gMoveDescription_HyperBeam[] = _("");
const u8 gMoveDescription_Peck[] = _("Attacks the foe with a\njabbing beak, etc.");
const u8 gMoveDescription_DrillPeck[] = _("A corkscrewing attack with\nthe beak acting as a drill.");
const u8 gMoveDescription_Submission[] = _("A reckless body slam that\nalso hurts the user.");
const u8 gMoveDescription_LowKick[] = _("A kick that inflicts more\ndamage on heavier foes.");
const u8 gMoveDescription_Counter[] = _("Retaliates any physical hit\nwith double the power.");
const u8 gMoveDescription_SeismicToss[] = _("Inflicts damage identical\nto the user's level.");
const u8 gMoveDescription_Strength[] = _("Builds enormous power,\nthen slams the foe.");
const u8 gMoveDescription_Absorb[] = _("An attack that absorbs\nhalf the damage inflicted.");
const u8 gMoveDescription_MegaDrain[] = _("");
const u8 gMoveDescription_LeechSeed[] = _("Plants a seed on the foe to\nsteal HP on every turn.");
const u8 gMoveDescription_Growth[] = _("Forces the body to grow,\nraising Attack and Sp. Atk.");
const u8 gMoveDescription_RazorLeaf[] = _("Cuts the enemy with leaves.\nHigh critical-hit ratio.");
const u8 gMoveDescription_SolarBeam[] = _("Absorbs light in one turn,\nthen attacks next turn.");
const u8 gMoveDescription_PoisonPowder[] = _("Scatters a toxic powder\nthat may poison the foe.");
const u8 gMoveDescription_StunSpore[] = _("Scatters a powder that may\nparalyze the foe.");
const u8 gMoveDescription_SleepPowder[] = _("Scatters a powder that may\ncause the foe to sleep.");
const u8 gMoveDescription_PetalDance[] = _("A rampage of 2 to 3 turns\nthat confuses the user.");
const u8 gMoveDescription_StringShot[] = _("Binds the foe with string\nto reduce its Speed.");
const u8 gMoveDescription_DragonRage[] = _("Launches shock waves that\nalways inflict 40 HP damage.");
const u8 gMoveDescription_FireSpin[] = _("Traps the foe in a ring of\nfire for  turns.");
const u8 gMoveDescription_ThunderShock[] = _("An electrical attack that\nmay paralyze the foe.");
const u8 gMoveDescription_Thunderbolt[] = _("A strong electrical attack\nthat may paralyze the foe.");
const u8 gMoveDescription_ThunderWave[] = _("A weak jolt of electricity\nthat paralyzes the foe.");
const u8 gMoveDescription_Thunder[] = _("A lightning attack that may\ncause paralysis.");
const u8 gMoveDescription_RockThrow[] = _("Throws small rocks to\nstrike the foe.");
const u8 gMoveDescription_Earthquake[] = _("A powerful quake, but has\nno effect on flying foes.");
const u8 gMoveDescription_Fissure[] = _("A one-hit KO move that\ndrops the foe in a fissure.");
const u8 gMoveDescription_Dig[] = _("Digs underground the first\nturn and strikes next turn.");
const u8 gMoveDescription_Toxic[] = _("Poisons the foe with an\nintensifying toxin.");
const u8 gMoveDescription_Confusion[] = _("A psychic attack that may\ncause confusion.");
const u8 gMoveDescription_Psychic[] = _("A powerful psychic attack\nthat may lower Sp. Def.");
const u8 gMoveDescription_Hypnosis[] = _("A hypnotizing move that\nmay induce sleep.");
const u8 gMoveDescription_Meditate[] = _("Meditates in a peaceful\nfashion to raise Attack.");
const u8 gMoveDescription_Agility[] = _("Relaxes the body to sharply\nboost Speed.");
const u8 gMoveDescription_QuickAttack[] = _("An extremely fast attack\nthat always strikes first.");
const u8 gMoveDescription_Rage[] = _("Raises the user's Attack\nevery time it is hit.");
const u8 gMoveDescription_Teleport[] = _("A psychic move for fleeing\nfrom battle instantly.");
const u8 gMoveDescription_NightShade[] = _("Inflicts damage identical\nto the user's level.");
const u8 gMoveDescription_Mimic[] = _("Copies a move used by the\nfoe during one battle.");
const u8 gMoveDescription_Screech[] = _("Emits a screech to sharply\nreduce the foe's Defense.");
const u8 gMoveDescription_DoubleTeam[] = _("Creates illusory copies to\nraise evasiveness.");
const u8 gMoveDescription_Recover[] = _("Recovers up to half the\nuser's maximum HP.");
const u8 gMoveDescription_Harden[] = _("Stiffens the body's \nmuscles to raise Defense.");
const u8 gMoveDescription_Minimize[] = _("Minimizes the user's size\nto raise evasiveness.");
const u8 gMoveDescription_Smokescreen[] = _("Lowers the foe's accuracy\nusing smoke, ink, etc.");
const u8 gMoveDescription_ConfuseRay[] = _("A sinister ray that\nconfuses the foe.");
const u8 gMoveDescription_Withdraw[] = _("Withdraws the body into its\nhard shell to raise Defense.");
const u8 gMoveDescription_DefenseCurl[] = _("Curls up to conceal weak\nspots and raise Defense.");
const u8 gMoveDescription_Barrier[] = _("Creates a barrier that\nsharply raises Defense.");
const u8 gMoveDescription_LightScreen[] = _("Creates a wall of light that\nlowers Sp. Atk damage.");
const u8 gMoveDescription_Haze[] = _("Creates a black haze that\neliminates all stat changes.");
const u8 gMoveDescription_Reflect[] = _("Creates a wall of light that\nweakens physical attacks.");
const u8 gMoveDescription_FocusEnergy[] = _("Focuses power to raise the\ncritical-hit ratio.");
const u8 gMoveDescription_Bide[] = _("Endures attack for 2\nturns to retaliate double.");
const u8 gMoveDescription_Metronome[] = _("Waggles a finger to use any\nPokémon move at random.");
const u8 gMoveDescription_MirrorMove[] = _("Counters the foe's attack\nwith the same move.");
const u8 gMoveDescription_SelfDestruct[] = _("Inflicts severe damage but\nmakes the user faint.");
const u8 gMoveDescription_EggBomb[] = _("An egg is forcibly hurled at\nthe foe.");
const u8 gMoveDescription_Lick[] = _("Licks with a long tongue to\ninjure. May also paralyze.");
const u8 gMoveDescription_Smog[] = _("An exhaust-gas attack\nthat may also poison.");
const u8 gMoveDescription_Sludge[] = _("Sludge is hurled to inflict\ndamage. May also poison.");
const u8 gMoveDescription_BoneClub[] = _("Clubs the foe with a bone.\nMay cause flinching.");
const u8 gMoveDescription_FireBlast[] = _("Incinerates everything it\nstrikes. May cause a burn.");
const u8 gMoveDescription_Waterfall[] = _("Charges the foe with speed\nto climb waterfalls.");
const u8 gMoveDescription_Clamp[] = _("Traps and squeezes the\nfoe for  turns.");
const u8 gMoveDescription_Swift[] = _("Sprays star-shaped rays\nthat never miss.");
const u8 gMoveDescription_SkullBash[] = _("Tucks in the head, then\nattacks on the next turn.");
const u8 gMoveDescription_SpikeCannon[] = _("Launches sharp spikes that\nstrike 2 to 5 times.");
const u8 gMoveDescription_Constrict[] = _("Constricts to inflict pain.\nMay lower Speed.");
const u8 gMoveDescription_Amnesia[] = _("Forgets about something\nand sharply raises Sp. Def.");
const u8 gMoveDescription_Kinesis[] = _("Distracts the foe.\nMay lower accuracy.");
const u8 gMoveDescription_SoftBoiled[] = _("Recovers up to half the\nuser's maximum HP.");
const u8 gMoveDescription_HighJumpKick[] = _("A jumping knee kick. If it\nmisses, the user is hurt.");
const u8 gMoveDescription_Glare[] = _("Intimidates and frightens\nthe foe into paralysis.");
const u8 gMoveDescription_DreamEater[] = _("Takes one half the damage\ninflicted on a sleeping foe.");
const u8 gMoveDescription_PoisonGas[] = _("Envelops the foe in a toxic\ngas that may poison.");
const u8 gMoveDescription_Barrage[] = _("Hurls round objects at the\nfoe 2 to 5 times.");
const u8 gMoveDescription_LeechLife[] = _("An attack that steals half\nthe damage inflicted.");
const u8 gMoveDescription_LovelyKiss[] = _("Demands a kiss with a scary\nface that induces sleep.");
const u8 gMoveDescription_SkyAttack[] = _("Searches out weak spots,\nthen strikes the next turn.");
const u8 gMoveDescription_Transform[] = _("Alters the user's cells to\nbecome a copy of the foe.");
const u8 gMoveDescription_Bubble[] = _("An attack using bubbles.\nMay lower the foe's Speed.");
const u8 gMoveDescription_DizzyPunch[] = _("A rhythmic punch that may\nconfuse the foe.");
const u8 gMoveDescription_Spore[] = _("Scatters a cloud of spores\nthat always induce sleep.");
const u8 gMoveDescription_Flash[] = _("Looses a powerful blast of\nlight that cuts accuracy.");
const u8 gMoveDescription_Psywave[] = _("Attacks with a psychic\nwave of varying intensity.");
const u8 gMoveDescription_Splash[] = _("It's just a splash...\nHas no effect whatsoever.");
const u8 gMoveDescription_AcidArmor[] = _("Liquifies the user's body\nto sharply raise Defense.");
const u8 gMoveDescription_Crabhammer[] = _("Hammers with a pincer. Has a\nhigh critical-hit ratio.");
const u8 gMoveDescription_Explosion[] = _("Inflicts severe damage but\nmakes the user faint.");
const u8 gMoveDescription_FurySwipes[] = _("Rakes the foe with sharp\nclaws, etc., 2 to 5 times.");
const u8 gMoveDescription_Bonemerang[] = _("Throws a bone boomerang\nthat strikes twice.");
const u8 gMoveDescription_Rest[] = _("The user sleeps for 2 turns,\nrestoring HP and status.");
const u8 gMoveDescription_RockSlide[] = _("Large boulders are hurled.\nMay cause flinching.");
const u8 gMoveDescription_HyperFang[] = _("Attacks with sharp fangs.\nMay cause flinching.");
const u8 gMoveDescription_Sharpen[] = _("Reduces the polygon count\nand raises Attack.");
const u8 gMoveDescription_Conversion[] = _("Changes the user's type\ninto a known move's type.");
const u8 gMoveDescription_TriAttack[] = _("Fires three types of beams\nat the same time.");
const u8 gMoveDescription_SuperFang[] = _("Attacks with sharp fangs\nand cuts half the foe's HP.");
const u8 gMoveDescription_Slash[] = _("Slashes with claws, etc. Has\na high critical-hit ratio.");
const u8 gMoveDescription_Substitute[] = _("Creates a decoy using 1/4\nof the user's maximum HP.");
const u8 gMoveDescription_Struggle[] = _("Used only if all PP are gone.\nAlso hurts the user a little.");
const u8 gMoveDescription_Sketch[] = _("Copies the foe's last move\npermanently.");
const u8 gMoveDescription_TripleKick[] = _("Kicks the foe 3 times in a\nrow with rising intensity.");
const u8 gMoveDescription_Thief[] = _("While attacking, it may\nsteal the foe's held item.");
const u8 gMoveDescription_SpiderWeb[] = _("Ensnares the foe to stop it\nfrom fleeing or switching.");
const u8 gMoveDescription_MindReader[] = _("Senses the foe's action to\nensure the next move's hit.");
const u8 gMoveDescription_Nightmare[] = _("Inflicts 1/4 damage on a\nsleeping foe every turn.");
const u8 gMoveDescription_FlameWheel[] = _("A fiery charge attack that\nmay inflict a burn.");
const u8 gMoveDescription_Snore[] = _("A loud attack that can be\nused only while asleep.");
const u8 gMoveDescription_Curse[] = _("A move that functions\ndifferently for GHOSTS.");
const u8 gMoveDescription_Flail[] = _("Inflicts more damage when\nthe user's HP is down.");
const u8 gMoveDescription_Conversion2[] = _("Makes the user resistant\nto the last attack's type.");
const u8 gMoveDescription_Aeroblast[] = _("Launches a vacuumed blast.\nHigh critical-hit ratio.");
const u8 gMoveDescription_CottonSpore[] = _("Spores cling to the foe,\nsharply reducing Speed.");
const u8 gMoveDescription_Reversal[] = _("Inflicts more damage when\nthe user's HP is down.");
const u8 gMoveDescription_Spite[] = _("Spitefully cuts the PP\nof the foe's last move.");
const u8 gMoveDescription_PowderSnow[] = _("Blasts the foe with a snowy\ngust. May cause frostbite.");
const u8 gMoveDescription_Protect[] = _("Evades attack, but may fail\nif used in succession.");
const u8 gMoveDescription_MachPunch[] = _("A punch is thrown at wicked\nspeed to strike first.");
const u8 gMoveDescription_ScaryFace[] = _("Frightens with a scary face\nto sharply reduce Speed.");
const u8 gMoveDescription_FeintAttack[] = _("Draws the foe close, then\nstrikes without fail.");
const u8 gMoveDescription_SweetKiss[] = _("Demands a kiss with a cute\nlook. May cause confusion.");
const u8 gMoveDescription_BellyDrum[] = _("Maximizes Attack while\nsacrificing HP.");
const u8 gMoveDescription_SludgeBomb[] = _("Sludge is hurled to inflict\ndamage. May also poison.");
const u8 gMoveDescription_MudSlap[] = _("Hurls mud in the foe's face\nto reduce its accuracy.");
const u8 gMoveDescription_Octazooka[] = _("Fires a lump of ink to\ndamage and cut accuracy.");
const u8 gMoveDescription_Spikes[] = _("Sets spikes that hurt a \nfoe switching in.");
const u8 gMoveDescription_ZapCannon[] = _("Powerful and sure to cause\nparalysis, but inaccurate.");
const u8 gMoveDescription_Foresight[] = _("Negates the foe's efforts\nto heighten evasiveness.");
const u8 gMoveDescription_DestinyBond[] = _("If the user faints, the foe\nis also made to faint.");
const u8 gMoveDescription_PerishSong[] = _("Any Pokémon hearing this\nsong faints in 3 turns.");
const u8 gMoveDescription_IcyWind[] = _("A chilling attack that\nlowers the foe's Speed.");
const u8 gMoveDescription_Detect[] = _("Evades attack, but may fail\nif used in succession.");
const u8 gMoveDescription_BoneRush[] = _("Strikes the foe with a bone\nin hand 2 to 5 times.");
const u8 gMoveDescription_LockOn[] = _("Locks on to the foe to\nensure the next move hits.");
const u8 gMoveDescription_Outrage[] = _("A rampage of 2 to 3 turns\nthat confuses the user.");
const u8 gMoveDescription_Sandstorm[] = _("Causes a sandstorm that\nrages for several turns.");
const u8 gMoveDescription_GigaDrain[] = _("An attack that steals half\nthe damage inflicted.");
const u8 gMoveDescription_Endure[] = _("Endures any attack for\n1 turn, leaving at least 1HP.");
const u8 gMoveDescription_Charm[] = _("Charms the foe and sharply\nreduces its Attack.");
const u8 gMoveDescription_Rollout[] = _("An attack lasting 5 turns\nwith rising intensity.");
const u8 gMoveDescription_FalseSwipe[] = _("");
const u8 gMoveDescription_Swagger[] = _("Confuses the foe, but also\nsharply raises Attack.");
const u8 gMoveDescription_MilkDrink[] = _("Recovers up to half the\nuser's maximum HP.");
const u8 gMoveDescription_Spark[] = _("An electrified tackle that\nmay paralyze the foe.");
const u8 gMoveDescription_FuryCutter[] = _("An attack that intensifies\non each successive hit.");
const u8 gMoveDescription_SteelWing[] = _("Strikes the foe with hard\nwings spread wide.");
const u8 gMoveDescription_MeanLook[] = _("Fixes the foe with a mean\nlook that prevents escape.");
const u8 gMoveDescription_Attract[] = _("Makes the opposite gender\nless likely to attack.");
const u8 gMoveDescription_SleepTalk[] = _("Uses an available move\nrandomly while asleep.");
const u8 gMoveDescription_HealBell[] = _("Chimes soothingly to heal\nall status abnormalities.");
const u8 gMoveDescription_Return[] = _("An attack that increases\nin power with friendship.");
const u8 gMoveDescription_Present[] = _("A gift in the form of a\nbomb. May restore HP.");
const u8 gMoveDescription_Frustration[] = _("An attack that is stronger\nif the Trainer is disliked.");
const u8 gMoveDescription_Safeguard[] = _("A mystical force prevents\nall status problems.");
const u8 gMoveDescription_PainSplit[] = _("Adds the user and foe's HP,\nthen shares them equally.");
const u8 gMoveDescription_SacredFire[] = _("A mystical fire attack that\nmay inflict a burn.");
const u8 gMoveDescription_Magnitude[] = _("A ground-shaking attack\nof random intensity.");
const u8 gMoveDescription_DynamicPunch[] = _("Powerful and sure to cause\nconfusion, but inaccurate.");
const u8 gMoveDescription_Megahorn[] = _("A brutal ramming attack\nusing out-thrust horns.");
const u8 gMoveDescription_DragonBreath[] = _("Strikes the foe with an\nincredible blast of breath.");
const u8 gMoveDescription_BatonPass[] = _("Switches out the user while\nkeeping effects in play.");
const u8 gMoveDescription_Encore[] = _("Makes the foe repeat its\nlast move over 2 to 6 turns.");
const u8 gMoveDescription_Pursuit[] = _("Inflicts bad damage if used\non a foe switching out.");
const u8 gMoveDescription_RapidSpin[] = _("Spins the body at high\nspeed to strike the foe.");
const u8 gMoveDescription_SweetScent[] = _("Allures the foe to reduce\nevasiveness.");
const u8 gMoveDescription_IronTail[] = _("Attacks with a rock-hard\ntail. May lower Defense.");
const u8 gMoveDescription_MetalClaw[] = _("A claw attack that may\nraise the user's Attack.");
const u8 gMoveDescription_VitalThrow[] = _("Makes the user's move last,\nbut it never misses.");
const u8 gMoveDescription_MorningSun[] = _("Restores HP. The amount\nvaries with the weather.");
const u8 gMoveDescription_Synthesis[] = _("Restores HP. The amount\nvaries with the weather.");
const u8 gMoveDescription_Moonlight[] = _("Restores HP. The amount\nvaries with the weather.");
const u8 gMoveDescription_HiddenPower[] = _("The effectiveness varies\nwith the user.");
const u8 gMoveDescription_CrossChop[] = _("A double-chopping attack.\nHigh critical-hit ratio.");
const u8 gMoveDescription_Twister[] = _("Whips up a vicious twister\nto tear at the foe.");
const u8 gMoveDescription_RainDance[] = _("Boosts the power of Water-\ntype moves for 5 turns.");
const u8 gMoveDescription_SunnyDay[] = _("Boosts the power of Fire-\ntype moves for 5 turns.");
const u8 gMoveDescription_Crunch[] = _("Crunches with sharp fangs.\nMay lower Defense.");
const u8 gMoveDescription_MirrorCoat[] = _("Counters the foe's special\nattack at double the power.");
const u8 gMoveDescription_PsychUp[] = _("Copies the foe's effect(s)\nand gives to the user.");
const u8 gMoveDescription_ExtremeSpeed[] = _("An extremely fast and\npowerful attack.");
const u8 gMoveDescription_AncientPower[] = _("An attack that may raise\nall stats.");
const u8 gMoveDescription_ShadowBall[] = _("Hurls a black blob that may\nlower the foe's Sp. Def.");
const u8 gMoveDescription_FutureSight[] = _("Heightens inner power to\nstrike 2 turns later.");
const u8 gMoveDescription_RockSmash[] = _("A rock-crushing attack\nthat may lower Defense.");
const u8 gMoveDescription_Whirlpool[] = _("Traps and hurts the foe in\na whirlpool for  turns.");
const u8 gMoveDescription_BeatUp[] = _("Summons party Pokémon to\njoin in the attack.");
const u8 gMoveDescription_FakeOut[] = _("A 1st-turn, 1st-strike move\nthat causes flinching.");
const u8 gMoveDescription_Uproar[] = _("Causes an uproar for 2 to 5\nCauses an uproar for 3\nturns and prevents sleep.");
const u8 gMoveDescription_Stockpile[] = _("Charges up power for up to\n3 turns.");
const u8 gMoveDescription_SpitUp[] = _("Releases stockpiled power\n(the more the better).");
const u8 gMoveDescription_Swallow[] = _("Absorbs stockpiled power\nand restores HP.");
const u8 gMoveDescription_HeatWave[] = _("Exhales a hot breath on the\nfoe. May inflict a burn.");
const u8 gMoveDescription_Hail[] = _("Summons a hailstorm that\nstrikes every turn.");
const u8 gMoveDescription_Torment[] = _("Torments the foe and stops\nsuccessive use of a move.");
const u8 gMoveDescription_Flatter[] = _("Confuses the foe, but\nraises its Sp. Atk.");
const u8 gMoveDescription_WillOWisp[] = _("Inflicts a burn on the foe\nwith intense fire.");
const u8 gMoveDescription_Memento[] = _("The user faints and lowers\nthe foe's abilities.");
const u8 gMoveDescription_Facade[] = _("Boosts Attack when burned,\nparalyzed, or poisoned.");
const u8 gMoveDescription_FocusPunch[] = _("A powerful loyalty attack.\nThe user flinches if hit.");
const u8 gMoveDescription_SmellingSalts[] = _("Powerful against paralyzed\nfoes, but also heals them.");
const u8 gMoveDescription_FollowMe[] = _("Draws attention to make\nfoes attack only the user.");
const u8 gMoveDescription_NaturePower[] = _("The type of attack varies\ndepending on the location.");
const u8 gMoveDescription_Charge[] = _("Charges power to boost the\nelectric move used next.");
const u8 gMoveDescription_Taunt[] = _("Taunts the foe into only\nusing attack moves.");
const u8 gMoveDescription_HelpingHand[] = _("Boosts the power of the\nrecipient's moves.");
const u8 gMoveDescription_Trick[] = _("Tricks the foe into trading\nheld items.");
const u8 gMoveDescription_RolePlay[] = _("Mimics the target and\ncopies its special ability.");
const u8 gMoveDescription_Wish[] = _("A wish that restores HP.\nIt takes time to work.");
const u8 gMoveDescription_Assist[] = _("Attacks randomly with one\nof the partner's moves.");
const u8 gMoveDescription_Ingrain[] = _("Lays roots that restore HP.\nThe user can't switch out.");
const u8 gMoveDescription_Superpower[] = _("Boosts strength sharply,\nbut lowers abilities.");
const u8 gMoveDescription_MagicCoat[] = _("Reflects special effects\nback to the attacker.");
const u8 gMoveDescription_Recycle[] = _("Recycles a used item for\none more use.");
const u8 gMoveDescription_Revenge[] = _("");
const u8 gMoveDescription_BrickBreak[] = _("Destroys barriers such as\nREFLECT and causes damage.");
const u8 gMoveDescription_Yawn[] = _("Lulls the foe into yawning,\nthen sleeping next turn.");
const u8 gMoveDescription_KnockOff[] = _("Knocks down the foe's held\nitem to prevent its use.");
const u8 gMoveDescription_Endeavor[] = _("Gains power if the user's HP\nis lower than the foe's HP.");
const u8 gMoveDescription_Eruption[] = _("The higher the user's HP,\nthe more damage caused.");
const u8 gMoveDescription_SkillSwap[] = _("The user swaps special\nabilities with the target.");
const u8 gMoveDescription_Imprison[] = _("Prevents foes from using\nmoves known by the user.");
const u8 gMoveDescription_Refresh[] = _("Heals poisoning, paralysis,\nor a burn.");
const u8 gMoveDescription_Grudge[] = _("If the user faints, deletes\nall PP of foe's last move.");
const u8 gMoveDescription_Snatch[] = _("Steals the effects of the\nmove the target uses next.");
const u8 gMoveDescription_SecretPower[] = _("An attack with effects\nthat vary by location.");
const u8 gMoveDescription_Dive[] = _("Dives underwater the first\nturn and strikes next turn.");
const u8 gMoveDescription_ArmThrust[] = _("Straight-arm punches that\nstrike the foe 2 to 5 times.");
const u8 gMoveDescription_Camouflage[] = _("Alters the Pokémon's type\ndepending on the location.");
const u8 gMoveDescription_TailGlow[] = _("Flashes a light that sharply\nraises Sp. Atk.");
const u8 gMoveDescription_LusterPurge[] = _("Attacks with a burst of\nlight. May lower Sp. Def.");
const u8 gMoveDescription_MistBall[] = _("Attacks with a flurry of\ndown. May lower Sp. Atk.");
const u8 gMoveDescription_FeatherDance[] = _("Envelops the foe with down\nto sharply reduce Attack.");
const u8 gMoveDescription_TeeterDance[] = _("Confuses all Pokémon on\nthe scene.");
const u8 gMoveDescription_BlazeKick[] = _("A kick with a high critical-\nhit ratio. May cause a burn.");
const u8 gMoveDescription_MudSport[] = _("Covers the user in mud to\nraise electrical resistance.");
const u8 gMoveDescription_IceBall[] = _("A 5-turn attack that gains\npower on successive hits.");
const u8 gMoveDescription_NeedleArm[] = _("Attacks with thorny arms.\nMay cause flinching.");
const u8 gMoveDescription_SlackOff[] = _("Slacks off and restores\nhalf the maximum HP.");
const u8 gMoveDescription_HyperVoice[] = _("A loud attack that uses\nsound waves to injure.");
const u8 gMoveDescription_PoisonFang[] = _("A sharp-fanged attack.\nMay badly poison the foe.");
const u8 gMoveDescription_CrushClaw[] = _("Tears at the foe with sharp\nclaws. May lower Defense.");
const u8 gMoveDescription_BlastBurn[] = _("Powerful, but leaves the\nuser immobile the next turn.");
const u8 gMoveDescription_HydroCannon[] = _("Powerful, but leaves the\nuser immobile the next turn.");
const u8 gMoveDescription_MeteorMash[] = _("Fires a meteor-like punch.\nMay raise Attack.");
const u8 gMoveDescription_Astonish[] = _("An attack that may shock\nthe foe into flinching.");
const u8 gMoveDescription_WeatherBall[] = _("The move's type and power\nchange with the weather.");
const u8 gMoveDescription_Aromatherapy[] = _("Heals all status problems\nwith a soothing scent.");
const u8 gMoveDescription_FakeTears[] = _("Feigns crying to sharply\nlower the foe's Sp. Def.");
const u8 gMoveDescription_AirCutter[] = _("Hacks with razorlike wind.\nHigh critical-hit ratio.");
const u8 gMoveDescription_Overheat[] = _("Allows a full-power attack,\nbut sharply lowers Sp. Atk.");
const u8 gMoveDescription_OdorSleuth[] = _("Negates the foe's efforts\nto heighten evasiveness.");
const u8 gMoveDescription_RockTomb[] = _("Stops the foe from moving\nwith rocks and cuts Speed.");
const u8 gMoveDescription_SilverWind[] = _("A powdery attack that may\nraise abilities.");
const u8 gMoveDescription_MetalSound[] = _("Emits a horrible screech\nthat sharply lowers Sp. Def.");
const u8 gMoveDescription_GrassWhistle[] = _("Lulls the foe into sleep\nwith a pleasant melody.");
const u8 gMoveDescription_Tickle[] = _("Makes the foe laugh to\nlower Attack and Defense.");
const u8 gMoveDescription_CosmicPower[] = _("Raises Defense and Sp. Def\nwith a mystic power.");
const u8 gMoveDescription_WaterSpout[] = _("Inflicts more damage if the\nuser's HP is high.");
const u8 gMoveDescription_SignalBeam[] = _("A strange beam attack that\nmay confuse the foe.");
const u8 gMoveDescription_ShadowPunch[] = _("An unavoidable punch that\nis thrown from shadows.");
const u8 gMoveDescription_Extrasensory[] = _("Attacks with a peculiar\npower. May cause flinching.");
const u8 gMoveDescription_SkyUppercut[] = _("An uppercut thrown as if\nleaping into the sky.");
const u8 gMoveDescription_SandTomb[] = _("Traps and hurts the foe in\nquicksand for  turns.");
const u8 gMoveDescription_SheerCold[] = _("A chilling attack that\ncauses fainting if it hits.");
const u8 gMoveDescription_MuddyWater[] = _("Attacks with muddy water.\nMay lower accuracy.");
const u8 gMoveDescription_BulletSeed[] = _("Shoots 2 to 5 seeds in a row\nto strike the foe.");
const u8 gMoveDescription_AerialAce[] = _("An extremely speedy and\nunavoidable attack.");
const u8 gMoveDescription_IcicleSpear[] = _("Attacks the foe by firing\n2 to 5 icicles in a row.");
const u8 gMoveDescription_IronDefense[] = _("Hardens the body's surface\nto sharply raise Defense.");
const u8 gMoveDescription_Block[] = _("Blocks the foe's way to\nprevent escape.");
const u8 gMoveDescription_Howl[] = _("Howls to raise the spirit\nand boosts Attack.");
const u8 gMoveDescription_DragonClaw[] = _("Slashes the foe with sharp\nclaws.");
const u8 gMoveDescription_FrenzyPlant[] = _("Powerful, but leaves the\nuser immobile the next turn.");
const u8 gMoveDescription_BulkUp[] = _("Bulks up the body to boost\nboth Attack and Defense.");
const u8 gMoveDescription_Bounce[] = _("Bounces up, then down the\nnext turn. May paralyze.");
const u8 gMoveDescription_MudShot[] = _("Hurls mud at the foe and\nreduces Speed.");
const u8 gMoveDescription_PoisonTail[] = _("Has a high critical-hit\nratio. May also poison.");
const u8 gMoveDescription_Covet[] = _("Cutely begs to obtain an\nitem held by the foe.");
const u8 gMoveDescription_VoltTackle[] = _("A life-risking tackle that\nslightly hurts the user.");
const u8 gMoveDescription_MagicalLeaf[] = _("Attacks with a strange leaf\nthat cannot be evaded.");
const u8 gMoveDescription_WaterSport[] = _("The user becomes soaked to\nraise resistance to fire.");
const u8 gMoveDescription_CalmMind[] = _("Raises Sp. Atk and Sp. Def\nby focusing the mind.");
const u8 gMoveDescription_LeafBlade[] = _("Slashes with a sharp leaf.\nHigh critical-hit ratio.");
const u8 gMoveDescription_DragonDance[] = _("A mystical dance that ups\nAttack and Speed.");
const u8 gMoveDescription_RockBlast[] = _("Hurls boulders at the foe\n2 to 5 times in a row.");
const u8 gMoveDescription_ShockWave[] = _("A fast and unavoidable\nelectric attack.");
const u8 gMoveDescription_WaterPulse[] = _("Attacks with ultrasonic\nwaves. May confuse the foe.");
const u8 gMoveDescription_DoomDesire[] = _("Summons strong sunlight to\nattack 2 turns later.");
const u8 gMoveDescription_PsychoBoost[] = _("Allows a full-power attack,\nbut sharply lowers Sp. Atk.");
const u8 gMoveDescription_Roost[] = _("Restores the user's HP by\nhalf of its max HP.");
const u8 gMoveDescription_Gravity[] = _("Gravity is intensified\nnegating levitation.");
const u8 gMoveDescription_MiracleEye[] = _("Negate evasiveness and\nDark-type's immunities.");
const u8 gMoveDescription_WakeUpSlap[] = _("Powerful against sleeping\nfoes, but also heals them.");
const u8 gMoveDescription_HammerArm[] = _("A swinging fist attack\nthat also lowers Speed.");
const u8 gMoveDescription_GyroBall[] = _("A high-speed spin that does\nmore damage to faster foes.");
const u8 gMoveDescription_HealingWish[] = _("");
const u8 gMoveDescription_Brine[] = _("Does double damage to foes\nwith half HP.");
const u8 gMoveDescription_NaturalGift[] = _("The effectiveness varies\nwith the held Berry.");
const u8 gMoveDescription_Feint[] = _("");
const u8 gMoveDescription_Pluck[] = _("");
const u8 gMoveDescription_Tailwind[] = _("Whips up a turbulent breeze\nthat raises Speed.");
const u8 gMoveDescription_Acupressure[] = _("The user sharply raises\none of its stats.");
const u8 gMoveDescription_MetalBurst[] = _("Retaliates any hit with\ngreater power.");
const u8 gMoveDescription_UTurn[] = _("");
const u8 gMoveDescription_CloseCombat[] = _("");
const u8 gMoveDescription_Payback[] = _("An attack that gains power\nif the user moves last.");
const u8 gMoveDescription_Assurance[] = _("An attack that gains power\nif the foe has been hurt.");
const u8 gMoveDescription_Embargo[] = _("Prevents the foe from\nusing any items.");
const u8 gMoveDescription_Fling[] = _("The effectiveness varies\nwith the held item.");
const u8 gMoveDescription_PsychoShift[] = _("Transfers status problems\nto the foe.");
const u8 gMoveDescription_TrumpCard[] = _("The less PP the move has\nthe more damage it does.");
const u8 gMoveDescription_HealBlock[] = _("Prevents the foe from\nrecovering any HP.");
const u8 gMoveDescription_WringOut[] = _("");
const u8 gMoveDescription_PowerTrick[] = _("The user swaps its Attack\nand Defense stats.");
const u8 gMoveDescription_GastroAcid[] = _("Stomach acid suppresses\nthe foe's ability.");
const u8 gMoveDescription_LuckyChant[] = _("Prevents the foe from\nlanding critical hits.");
const u8 gMoveDescription_MeFirst[] = _("Executes the foe's attack\nwith greater power.");
const u8 gMoveDescription_Copycat[] = _("The user mimics the last\nmove used by a foe.");
const u8 gMoveDescription_PowerSwap[] = _("Swaps changes to Attack\nand Sp. Atk with the foe.");
const u8 gMoveDescription_GuardSwap[] = _("Swaps changes to Defense\nand Sp. Def with the foe.");
const u8 gMoveDescription_Punishment[] = _("Does more damage if the\nfoe has powered up.");
const u8 gMoveDescription_LastResort[] = _("Can only be used if every\nother move has been used.");
const u8 gMoveDescription_WorrySeed[] = _("Plants a seed on the foe\ngiving it Insomnia.");
const u8 gMoveDescription_SuckerPunch[] = _("");
const u8 gMoveDescription_ToxicSpikes[] = _("Sets spikes that poison a\nfoe switching in.");
const u8 gMoveDescription_HeartSwap[] = _("Swaps any stat changes\nwith the foe.");
const u8 gMoveDescription_AquaRing[] = _("Forms a veil of water\nthat restores HP.");
const u8 gMoveDescription_MagnetRise[] = _("The user levitates with\nelectromagnetism.");
const u8 gMoveDescription_FlareBlitz[] = _("A charge that may burn the\nfoe. Also hurts the user.");
const u8 gMoveDescription_ForcePalm[] = _("A shock wave attack that\nmay paralyze the foe.");
const u8 gMoveDescription_AuraSphere[] = _("Attacks with an aura blast\nthat cannot be evaded.");
const u8 gMoveDescription_RockPolish[] = _("Polishes the body to\nsharply raise Speed.");
const u8 gMoveDescription_PoisonJab[] = _("A stabbing attack that\nmay poison the foe.");
const u8 gMoveDescription_DarkPulse[] = _("Attacks with a horrible\naura. May cause flinching.");
const u8 gMoveDescription_NightSlash[] = _("Hits as soon as possible.\nHigh critical-hit ratio.");
const u8 gMoveDescription_AquaTail[] = _("The user swings its tail\nlike a wave to attack.");
const u8 gMoveDescription_SeedBomb[] = _("A barrage of hard seeds\nis fired at the foe.");
const u8 gMoveDescription_AirSlash[] = _("Attacks with a blade of\nair. May cause flinching.");
const u8 gMoveDescription_XScissor[] = _("Slashes the foe with crossed\nscythes, claws, etc.");
const u8 gMoveDescription_BugBuzz[] = _("A damaging sound wave that\nmay lower Sp. Def.");
const u8 gMoveDescription_DragonPulse[] = _("Generates a shock wave to\ndamage the foe.");
const u8 gMoveDescription_DragonRush[] = _("Tackles the foe with menace.\nMay cause flinching.");
const u8 gMoveDescription_PowerGem[] = _("Attacks with rays of light\nthat sparkle like diamonds.");
const u8 gMoveDescription_DrainPunch[] = _("");
const u8 gMoveDescription_VacuumWave[] = _("Whirls its fists to send\na wave that strikes first.");
const u8 gMoveDescription_FocusBlast[] = _("Attacks at full power.\nMay lower Sp. Def.");
const u8 gMoveDescription_EnergyBall[] = _("Draws power from nature to\nattack. May lower Sp. Def.");
const u8 gMoveDescription_BraveBird[] = _("A low altitude charge that\nalso hurts the user.");
const u8 gMoveDescription_EarthPower[] = _("Makes the ground erupt with\npower. May lower Sp. Def.");
const u8 gMoveDescription_Switcheroo[] = _("Swaps items with the foe\nfaster than the eye can see.");
const u8 gMoveDescription_GigaImpact[] = _("");
const u8 gMoveDescription_NastyPlot[] = _("Thinks bad thoughts to\nsharply boost Sp. Atk.");
const u8 gMoveDescription_BulletPunch[] = _("Punches as fast as a bul-\nlet. It always hits first.");
const u8 gMoveDescription_Avalanche[] = _("");
const u8 gMoveDescription_IceShard[] = _("Hurls a chunk of ice that\nalways strike first.");
const u8 gMoveDescription_ShadowClaw[] = _("Strikes with a shadow claw.\nHigh critical-hit ratio.");
const u8 gMoveDescription_ThunderFang[] = _("May cause flinching or\nleave the foe paralyzed.");
const u8 gMoveDescription_IceFang[] = _("May cause flinching or\nleave the foe with frostbite.");
const u8 gMoveDescription_FireFang[] = _("May cause flinching or\nleave the foe with a burn.");
const u8 gMoveDescription_ShadowSneak[] = _("Extends the user's shadow\nto strike first.");
const u8 gMoveDescription_MudBomb[] = _("Throws a blob of mud to\ndamage and cut accuracy.");
const u8 gMoveDescription_PsychoCut[] = _("Tears with psychic blades.\nHigh critical-hit ratio.");
const u8 gMoveDescription_ZenHeadbutt[] = _("Hits with a strong head-\nbutt. May cause flinching.");
const u8 gMoveDescription_MirrorShot[] = _("Emits a flash of energy to\ndamage and cut accuracy.");
const u8 gMoveDescription_FlashCannon[] = _("Releases a blast of light\nthat may lower Sp. Def.");
const u8 gMoveDescription_RockClimb[] = _("A charging attack that may\nconfuse the foe.");
const u8 gMoveDescription_Defog[] = _("Removes obstacles and\nlowers evasion.");
const u8 gMoveDescription_TrickRoom[] = _("Slower Pokémon get to move\nfirst for 5 turns.");
const u8 gMoveDescription_DracoMeteor[] = _("Casts comets onto the foe.\nHarshly lowers the Sp. Atk.");
const u8 gMoveDescription_Discharge[] = _("Zaps the foes with electri-\ncity. May paralyze them.");
const u8 gMoveDescription_LavaPlume[] = _("");
const u8 gMoveDescription_LeafStorm[] = _("Whips up a storm of leaves.\nHarshly lowers the Sp. Atk.");
const u8 gMoveDescription_PowerWhip[] = _("Violently lashes the foe\nwith vines or tentacles.");
const u8 gMoveDescription_RockWrecker[] = _("");
const u8 gMoveDescription_CrossPoison[] = _("A slash that may poison a\nfoe and do critical damage.");
const u8 gMoveDescription_GunkShot[] = _("Shoots filthy garbage at\nthe foe. May also poison.");
const u8 gMoveDescription_IronHead[] = _("Slams the foe with a hard\nhead. May cause flinching.");
const u8 gMoveDescription_MagnetBomb[] = _("Launches a magnet that\nstrikes without fail.");
const u8 gMoveDescription_StoneEdge[] = _("Stabs the foe with stones.\nHigh critical-hit ratio.");
const u8 gMoveDescription_Captivate[] = _("Makes the opposite gender\nsharply reduce its Sp. Atk.");
const u8 gMoveDescription_StealthRock[] = _("Sets floating stones that\nhurt a foe switching in.");
const u8 gMoveDescription_GrassKnot[] = _("A snare attack that does\nmore damage to heavier foes.");
const u8 gMoveDescription_Chatter[] = _("Attacks with a sound wave\nthat causes confusion.");
const u8 gMoveDescription_Judgment[] = _("The type varies with the\nkind of Plate held.");
const u8 gMoveDescription_BugBite[] = _("");
const u8 gMoveDescription_ChargeBeam[] = _("Fires a beam of electricity.\nMay raise Sp. Atk.");
const u8 gMoveDescription_WoodHammer[] = _("Slams the body into a foe.\nThe user gets hurt too.");
const u8 gMoveDescription_AquaJet[] = _("Strikes first by dashing\nat the foe at a high speed.");
const u8 gMoveDescription_AttackOrder[] = _("Underlings pummel the foe.\nHigh critical-hit ratio.");
const u8 gMoveDescription_DefendOrder[] = _("Raises Defense and Sp. Def\nwith a living shield.");
const u8 gMoveDescription_HealOrder[] = _("The user's underlings show\nup to heal half its max HP.");
const u8 gMoveDescription_HeadSmash[] = _("A life-risking headbutt that\nseriously hurts the user.");
const u8 gMoveDescription_DoubleHit[] = _("Slams the foe with a tail\netc. Strikes twice.");
const u8 gMoveDescription_RoarOfTime[] = _("Powerful, but leaves the\nuser immobile the next turn.");
const u8 gMoveDescription_SpacialRend[] = _("Tears the foe, and space.\nHigh critical-hit ratio.");
const u8 gMoveDescription_LunarDance[] = _("");
const u8 gMoveDescription_CrushGrip[] = _("");
const u8 gMoveDescription_MagmaStorm[] = _("Traps the foe in a vortex\nof fire for  turns.");
const u8 gMoveDescription_DarkVoid[] = _("Drags the foe into total\ndarkness, inducing Sleep.");
const u8 gMoveDescription_SeedFlare[] = _("Generates a shock wave that\nsharply reduces Sp. Def.");
const u8 gMoveDescription_OminousWind[] = _("A repulsive attack that may\nraise all stats.");
const u8 gMoveDescription_ShadowForce[] = _("");
const u8 gMoveDescription_HoneClaws[] = _("Sharpens its claws to raise\nAttack and Accuracy.");
const u8 gMoveDescription_WideGuard[] = _("Evades wide-ranging attacks\nfor one turn.");
const u8 gMoveDescription_GuardSplit[] = _("Averages changes to Defense\nand Sp. Def with the foe.");
const u8 gMoveDescription_PowerSplit[] = _("Averages changes to Attack\nand Sp. Atk with the foe.");
const u8 gMoveDescription_WonderRoom[] = _("Defense and Sp. Def stats\nare swapped for 5 turns.");
const u8 gMoveDescription_Psyshock[] = _("");
const u8 gMoveDescription_Venoshock[] = _("Does double damage if the\nfoe is poisoned.");
const u8 gMoveDescription_Autotomize[] = _("Sheds additional weight to\nsharply boost Speed.");
const u8 gMoveDescription_RagePowder[] = _("Scatters powder to make\nfoes attack only the user.");
const u8 gMoveDescription_Telekinesis[] = _("Makes the foe float. It is\neasier to hit for 3 turns.");
const u8 gMoveDescription_MagicRoom[] = _("Hold items lose their\neffects for 5 turns.");
const u8 gMoveDescription_SmackDown[] = _("Throws a rock to knock the\nfoe down to the ground.");
const u8 gMoveDescription_StormThrow[] = _("");
const u8 gMoveDescription_FlameBurst[] = _("A bursting flame that does\ndamage to all foes.");
const u8 gMoveDescription_SludgeWave[] = _("Swamps the foe with a wave\nof sludge. May also poison.");
const u8 gMoveDescription_QuiverDance[] = _("Dances to raise Sp. Atk\nSp. Def and Speed.");
const u8 gMoveDescription_HeavySlam[] = _("");
const u8 gMoveDescription_Synchronoise[] = _("An odd shock wave that only\ndamages same-type foes.");
const u8 gMoveDescription_ElectroBall[] = _("Hurls an orb that does more\ndamage to slower foes.");
const u8 gMoveDescription_Soak[] = _("Sprays water at the foe\nmaking it Water-type.");
const u8 gMoveDescription_FlameCharge[] = _("Attacks in a cloak of\nflames. Raises Speed.");
const u8 gMoveDescription_Coil[] = _("Coils up to raise Attack\nDefense and Accuracy.");
const u8 gMoveDescription_LowSweep[] = _("Attacks the foe's legs\nlowering its Speed.");
const u8 gMoveDescription_AcidSpray[] = _("Sprays a hide-melting acid.\nSharply reduces Sp. Def.");
const u8 gMoveDescription_FoulPlay[] = _("The higher the foe's Attack\nthe more damage caused.");
const u8 gMoveDescription_SimpleBeam[] = _("A beam that changes the\nfoe's ability to Simple.");
const u8 gMoveDescription_Entrainment[] = _("Makes the foe mimic the\nuser, gaining its ability.");
const u8 gMoveDescription_AfterYou[] = _("Helps out the foe, letting\nit move next.");
const u8 gMoveDescription_Round[] = _("A song that inflicts damage.\nOthers can join in too.");
const u8 gMoveDescription_EchoedVoice[] = _("Does more damage every turn\nit is used.");
const u8 gMoveDescription_ChipAway[] = _("");
const u8 gMoveDescription_ClearSmog[] = _("Attacks with white haze that\neliminates all stat changes.");
const u8 gMoveDescription_StoredPower[] = _("The higher the user's stats\nthe more damage caused.");
const u8 gMoveDescription_QuickGuard[] = _("Evades priority attacks\nfor one turn.");
const u8 gMoveDescription_AllySwitch[] = _("The user switches places\nwith its partner.");
const u8 gMoveDescription_Scald[] = _("Shoots boiling water at the\nfoe. May inflict a burn.");
const u8 gMoveDescription_ShellSmash[] = _("Raises offensive stats, but\nlowers defensive stats.");
const u8 gMoveDescription_HealPulse[] = _("Recovers up to half the\ntarget's maximum HP.");
const u8 gMoveDescription_Hex[] = _("Does double damage if the\nfoe has a status problem.");
const u8 gMoveDescription_SkyDrop[] = _("Takes the foe into the sky\nthen drops it the next turn.");
const u8 gMoveDescription_ShiftGear[] = _("Rotates its gears to raise\nAttack and Speed.");
const u8 gMoveDescription_CircleThrow[] = _("");
const u8 gMoveDescription_Incinerate[] = _("Burns up Berries and Gems\npreventing their use.");
const u8 gMoveDescription_Quash[] = _("Suppresses the foe, making\nit move last.");
const u8 gMoveDescription_Acrobatics[] = _("Does double damage if the\nuser has no item.");
const u8 gMoveDescription_ReflectType[] = _("The user reflects the foe's\ntype, copying it.");
const u8 gMoveDescription_Retaliate[] = _("An attack that does more\ndamage if an ally fainted.");
const u8 gMoveDescription_FinalGambit[] = _("The user faints to damage\nthe foe equal to its HP.");
const u8 gMoveDescription_Bestow[] = _("The user gives its held\nitem to the foe.");
const u8 gMoveDescription_Inferno[] = _("Powerful and sure to inflict\na burn, but inaccurate.");
const u8 gMoveDescription_WaterPledge[] = _("Attacks with a column of\nwater. May make a rainbow.");
const u8 gMoveDescription_FirePledge[] = _("Attacks with a column of\nfire. May burn the grass.");
const u8 gMoveDescription_GrassPledge[] = _("Attacks with a column of\ngrass. May create a swamp.");
const u8 gMoveDescription_VoltSwitch[] = _("");
const u8 gMoveDescription_StruggleBug[] = _("Resisting, the user attacks\nthe foe. Lowers Sp. Atk.");
const u8 gMoveDescription_Bulldoze[] = _("Stomps down on the ground.\nLowers Speed.");
const u8 gMoveDescription_FrostBreath[] = _("");
const u8 gMoveDescription_DragonTail[] = _("");
const u8 gMoveDescription_WorkUp[] = _("The user is roused.\nUps Attack and Sp. Atk.");
const u8 gMoveDescription_Electroweb[] = _("Snares the foe with an\nelectric net. Lowers Speed.");
const u8 gMoveDescription_WildCharge[] = _("An electrical tackle that\nalso hurts the user.");
const u8 gMoveDescription_DrillRun[] = _("Spins its body like a drill.\nHigh critical-hit ratio.");
const u8 gMoveDescription_DualChop[] = _("Attacks with brutal hits\nthat strike twice.");
const u8 gMoveDescription_HeartStamp[] = _("A sudden blow after a cute\nact. May cause flinching.");
const u8 gMoveDescription_HornLeech[] = _("");
const u8 gMoveDescription_SacredSword[] = _("");
const u8 gMoveDescription_RazorShell[] = _("Tears at the foe with sharp\nshells. May lower Defense.");
const u8 gMoveDescription_HeatCrash[] = _("");
const u8 gMoveDescription_LeafTornado[] = _("Circles the foe with leaves\nto damage and cut accuracy.");
const u8 gMoveDescription_Steamroller[] = _("Crushes the foe with its\nbody. May cause flinching.");
const u8 gMoveDescription_CottonGuard[] = _("Wraps its body in cotton.\nDrastically raises Defense.");
const u8 gMoveDescription_NightDaze[] = _("Looses a pitch-black shock\nwave. May lower accuracy.");
const u8 gMoveDescription_Psystrike[] = _("");
const u8 gMoveDescription_TailSlap[] = _("Strikes the foe with its\ntail 2 to 5 times.");
const u8 gMoveDescription_Hurricane[] = _("Traps the foe in a fierce\nwind. May cause confusion.");
const u8 gMoveDescription_HeadCharge[] = _("A charge using guard hair.\nIt hurts the user a little.");
const u8 gMoveDescription_GearGrind[] = _("Throws two steel gears\nthat strike twice.");
const u8 gMoveDescription_SearingShot[] = _("");
const u8 gMoveDescription_TechnoBlast[] = _("The type varies with the\nkind of Drive held.");
const u8 gMoveDescription_RelicSong[] = _("Attacks with an ancient\nsong. May induce sleep.");
const u8 gMoveDescription_SecretSword[] = _("Cuts with a long horn that\ndoes physical damage.");
const u8 gMoveDescription_Glaciate[] = _("Blows very cold air at the\nfoe. It lowers their Speed.");
const u8 gMoveDescription_BoltStrike[] = _("Strikes with a great amount\nof lightning. May paralyze.");
const u8 gMoveDescription_BlueFlare[] = _("Engulfs the foe in a blue\nflame. May inflict a burn.");
const u8 gMoveDescription_FieryDance[] = _("Dances cloaked in flames.\nMay raise Sp. Atk.");
const u8 gMoveDescription_FreezeShock[] = _("A powerful 2-turn move that\nmay paralyze the foe.");
const u8 gMoveDescription_IceBurn[] = _("A powerful 2-turn move that\nmay inflict a burn.");
const u8 gMoveDescription_Snarl[] = _("Yells and rants at the foe\nlowering its Sp. Atk.");
const u8 gMoveDescription_IcicleCrash[] = _("Drops large icicles on the\nfoe. May cause flinching.");
const u8 gMoveDescription_VCreate[] = _("Very powerful, but lowers\nDefense, Sp. Def and Speed.");
const u8 gMoveDescription_FusionFlare[] = _("Summons a fireball. Works\nwell with a thunderbolt.");
const u8 gMoveDescription_FusionBolt[] = _("Summons a thunderbolt.\nWorks well with a fireball.");
const u8 gMoveDescription_FlyingPress[] = _("This attack does Fighting\nand Flying-type damage.");
const u8 gMoveDescription_MatBlock[] = _("Evades damaging moves\nfor one turn.");
const u8 gMoveDescription_Belch[] = _("Lets out a loud belch.\nMust eat a Berry to use it.");
const u8 gMoveDescription_Rototiller[] = _("Ups the Attack and Sp. Atk\nof Grass-type Pokémon.");
const u8 gMoveDescription_StickyWeb[] = _("Weaves a sticky net that\nslows foes switching in.");
const u8 gMoveDescription_FellStinger[] = _("If it knocks out a foe\nthe Attack stat is raised.");
const u8 gMoveDescription_PhantomForce[] = _("");
const u8 gMoveDescription_TrickOrTreat[] = _("Goes trick-or-treating\nmaking the foe Ghost-type.");
const u8 gMoveDescription_NobleRoar[] = _("Intimidates the foe, to cut\nAttack and Sp. Atk.");
const u8 gMoveDescription_IonDeluge[] = _("Electrifies Normal-type\nmoves with charged atoms.");
const u8 gMoveDescription_ParabolicCharge[] = _("Damages adjacent Pokémon and\nheals up by half of it.");
const u8 gMoveDescription_ForestsCurse[] = _("Puts a curse on the foe\nmaking the foe Grass-type.");
const u8 gMoveDescription_PetalBlizzard[] = _("Stirs up a violent storm\nof petals to attack.");
const u8 gMoveDescription_FreezeDry[] = _("Super effective on Water-\ntypes. May cause frostbite.");
const u8 gMoveDescription_DisarmingVoice[] = _("Lets out a charming cry\nthat cannot be evaded.");
const u8 gMoveDescription_PartingShot[] = _("Lowers the foe's Attack and\nSp. Atk, then switches out.");
const u8 gMoveDescription_TopsyTurvy[] = _("Swaps all stat changes that\naffect the target.");
const u8 gMoveDescription_DrainingKiss[] = _("");
const u8 gMoveDescription_CraftyShield[] = _("Evades status moves for\none turn.");
const u8 gMoveDescription_FlowerShield[] = _("Raises the Defense of\nGrass-type Pokémon.");
const u8 gMoveDescription_GrassyTerrain[] = _("The ground turns to grass\nfor 5 turns. Restores HP.");
const u8 gMoveDescription_MistyTerrain[] = _("Covers the ground with mist\nfor 5 turns. Blocks status.");
const u8 gMoveDescription_Electrify[] = _("Electrifies the foe, making\nits next move Electric-type.");
const u8 gMoveDescription_PlayRough[] = _("Plays rough with the foe.\nMay lower Attack.");
const u8 gMoveDescription_FairyWind[] = _("Stirs up a fairy wind to\nstrike the foe.");
const u8 gMoveDescription_Moonblast[] = _("Attacks with the power of\nthe moon. May lower Sp. Atk.");
const u8 gMoveDescription_Boomburst[] = _("Attacks everything with a\ndestructive sound wave.");
const u8 gMoveDescription_FairyLock[] = _("Locks down the battlefield\npreventing escape next turn.");
const u8 gMoveDescription_KingsShield[] = _("Evades damage, and sharply\nreduces Attack if struck.");
const u8 gMoveDescription_PlayNice[] = _("Befriend the foe, lowering\nits Attack without fail.");
const u8 gMoveDescription_Confide[] = _("Shares a secret with the\nfoe, lowering Sp. Atk.");
const u8 gMoveDescription_DiamondStorm[] = _("Whips up a storm of\ndiamonds. May up Defense.");
const u8 gMoveDescription_SteamEruption[] = _("Immerses the foe in heated\nsteam. May inflict a burn.");
const u8 gMoveDescription_HyperspaceHole[] = _("");
const u8 gMoveDescription_WaterShuriken[] = _("Throws 2 to 5 stars that\nare sure to strike first.");
const u8 gMoveDescription_MysticalFire[] = _("Breathes a special, hot\nfire. Lowers Sp. Atk.");
const u8 gMoveDescription_SpikyShield[] = _("Evades attack, and damages\nthe foe if struck.");
const u8 gMoveDescription_AromaticMist[] = _("Raises the Sp. Def of a\npartner Pokémon.");
const u8 gMoveDescription_EerieImpulse[] = _("Exposes the foe to a pulse\nthat sharply cuts Sp. Atk.");
const u8 gMoveDescription_VenomDrench[] = _("Lowers the Attack, Sp. Atk\nand Speed of a poisoned foe.");
const u8 gMoveDescription_Powder[] = _("Damages the foe if it uses\na Fire-type move.");
const u8 gMoveDescription_Geomancy[] = _("Raises Sp. Atk, Sp. Def and\nSpeed on the 2nd turn.");
const u8 gMoveDescription_MagneticFlux[] = _("Boosts the defenses of\nthose with Plus or Minus.");
const u8 gMoveDescription_HappyHour[] = _("Doubles the amount of\nPrize Money received.");
const u8 gMoveDescription_ElectricTerrain[] = _("Electrifies the ground for\n5 turns. Prevents sleep.");
const u8 gMoveDescription_DazzlingGleam[] = _("Damages foes by emitting\na bright flash.");
const u8 gMoveDescription_Celebrate[] = _("Congratulates you on your\nspecial day.");
const u8 gMoveDescription_HoldHands[] = _("The user and ally hold hands\nmaking them happy.");
const u8 gMoveDescription_BabyDollEyes[] = _("Lowers the foe's Attack\nbefore it can move.");
const u8 gMoveDescription_Nuzzle[] = _("Rubs its cheecks against\nthe foe, paralyzing it.");
const u8 gMoveDescription_HoldBack[] = _("");
const u8 gMoveDescription_Infestation[] = _("The foe is infested and\nattacked for  turns.");
const u8 gMoveDescription_PowerUpPunch[] = _("A hard punch that raises\nthe user's Attack.");
const u8 gMoveDescription_OblivionWing[] = _("");
const u8 gMoveDescription_ThousandArrows[] = _("Can hit Flying foes, then\nknocks them to the ground.");
const u8 gMoveDescription_ThousandWaves[] = _("Those hit by the wave can\nno longer escape.");
const u8 gMoveDescription_LandsWrath[] = _("Gathers the energy of the\nland to attack every foe.");
const u8 gMoveDescription_LightOfRuin[] = _("Fires a great beam of light\nthat also hurts the user.");
const u8 gMoveDescription_OriginPulse[] = _("Beams of glowing blue light\nblast both foes.");
const u8 gMoveDescription_PrecipiceBlades[] = _("Fearsome blades of stone\nattack both foes.");
const u8 gMoveDescription_DragonAscent[] = _("");
const u8 gMoveDescription_HyperspaceFury[] = _("");
const u8 gMoveDescription_ShoreUp[] = _("Restores the user's HP.\nMore HP in a sandstorm.");
const u8 gMoveDescription_FirstImpression[] = _("Hits hard and first.\nOnly works first turn.");
const u8 gMoveDescription_BanefulBunker[] = _("Protects user and poisons\nfoes on contact.");
const u8 gMoveDescription_SpiritShackle[] = _("After being hit, foes can\nno longer escape.");
const u8 gMoveDescription_DarkestLariat[] = _("Swings the arms to strike\nIt ignores stat changes.");
const u8 gMoveDescription_SparklingAria[] = _("Sings with bubbles. Cures\nburns on contact.");
const u8 gMoveDescription_IceHammer[] = _("Swings the fist to strike.\nLowers the user's Speed.");
const u8 gMoveDescription_FloralHealing[] = _("Restores an ally's HP.\nHeals more on grass.");
const u8 gMoveDescription_HighHorsepower[] = _("Slams hard into the foe with\nits entire body.");
const u8 gMoveDescription_StrengthSap[] = _("Saps the foe's Attack to\nheal HP, then drops Attack.");
const u8 gMoveDescription_SolarBlade[] = _("Charges first turn, then\nchops with a blade of light.");
const u8 gMoveDescription_Leafage[] = _("Attacks with a flurry of\nsmall leaves.");
const u8 gMoveDescription_Spotlight[] = _("Makes the foe attack the\nspotlighted Pokémon.");
const u8 gMoveDescription_ToxicThread[] = _("Attacks with a thread that\npoisons and drops Speed.");
const u8 gMoveDescription_LaserFocus[] = _("Guarantees the next move\nwill be a critical hit.");
const u8 gMoveDescription_GearUp[] = _("Boosts the attacks of\nthose with Plus or Minus.");
const u8 gMoveDescription_ThroatChop[] = _("Chops the throat to disable\nsound moves for a while.");
const u8 gMoveDescription_PollenPuff[] = _("Explodes on foes, but\nrestores ally's HP.");
const u8 gMoveDescription_AnchorShot[] = _("Strangles the foe with a\nchain. The foe can't escape.");
const u8 gMoveDescription_PsychicTerrain[] = _("The ground turns weird for\n5 turns. Blocks priority.");
const u8 gMoveDescription_Lunge[] = _("Lunges at the foe to lower\nits Attack stat.");
const u8 gMoveDescription_FireLash[] = _("Whips the foe with fire\nlowering its Defense.");
const u8 gMoveDescription_PowerTrip[] = _("It hits harder the more\nstat boosts the user has.");
const u8 gMoveDescription_BurnUp[] = _("Burns out the user fully\nremoving the Fire type.");
const u8 gMoveDescription_SpeedSwap[] = _("Swaps user's Speed with\nthe target's.");
const u8 gMoveDescription_SmartStrike[] = _("Hits with an accurate\nhorn that never misses.");
const u8 gMoveDescription_Purify[] = _("Cures the foe's status\nto restore HP.");
const u8 gMoveDescription_RevelationDance[] = _("Dances with mystical power.\nMatches user's first type.");
const u8 gMoveDescription_CoreEnforcer[] = _("Hits with a ray that\nnullifies the foe's ability.");
const u8 gMoveDescription_TropKick[] = _("An intense kick from the\ntropics. Lowers Attack.");
const u8 gMoveDescription_Instruct[] = _("Orders the target to use\nits last move again.");
const u8 gMoveDescription_BeakBlast[] = _("Heats up beak to attack.\nBurns foe on contact.");
const u8 gMoveDescription_ClangingScales[] = _("Makes a big noise with\nits scales. Drops Defense.");
const u8 gMoveDescription_DragonHammer[] = _("Swings its whole body\nlike a hammer to damage.");
const u8 gMoveDescription_BrutalSwing[] = _("Violently swings around\nto hurt everyone nearby.");
const u8 gMoveDescription_AuroraVeil[] = _("Weakens all attacks, but\nonly usable with hail.");
const u8 gMoveDescription_ShellTrap[] = _("Sets a shell trap that\ndamages on contact.");
const u8 gMoveDescription_FleurCannon[] = _("A strong ray that harshly\nlowers Sp. Attack.");
const u8 gMoveDescription_PsychicFangs[] = _("Chomps with psychic fangs.\nDestroys any barriers.");
const u8 gMoveDescription_StompingTantrum[] = _("Stomps around angrily.\nStronger after a failure.");
const u8 gMoveDescription_ShadowBone[] = _("Strikes with a haunted\nbone. Might drop Defense.");
const u8 gMoveDescription_Accelerock[] = _("Hits with a high-speed\nrock that always goes first.");
const u8 gMoveDescription_Liquidation[] = _("Slams the foe with water.\nCan lower Defense.");
const u8 gMoveDescription_PrismaticLaser[] = _("A high power laser that\nforces recharge next turn.");
const u8 gMoveDescription_SpectralThief[] = _("Steals the target's stat\nboosts, then attacks.");
const u8 gMoveDescription_SunsteelStrike[] = _("A sun-fueled strike that\nignores abilities.");
const u8 gMoveDescription_MoongeistBeam[] = _("A moon-powered beam that\nignores abilities.");
const u8 gMoveDescription_TearfulLook[] = _("The user tears up, dropping\nAttack and Sp. Attack.");
const u8 gMoveDescription_ZingZap[] = _("An electrified impact that\ncan cause flinching.");
const u8 gMoveDescription_NaturesMadness[] = _("Halves the foe's HP with\nthe power of nature.");
const u8 gMoveDescription_MultiAttack[] = _("An attack that changes\nwith Memories.");
const u8 gMoveDescription_MindBlown[] = _("It explodes the user's head\nto damage everything around.");
const u8 gMoveDescription_PlasmaFists[] = _("Hits with electrical fists.\nNormal moves become Electric.");
const u8 gMoveDescription_PhotonGeyser[] = _("User's highest attack stat\ndetermines its category.");
const u8 gMoveDescription_ZippyZap[] = _("Electric bursts always go\nfirst and land a critical hit.");
const u8 gMoveDescription_SplishySplash[] = _("A huge electrified wave that\nmay paralyze the foe.");
const u8 gMoveDescription_FloatyFall[] = _("Floats in air and dives at\nangle. May cause flinching.");
const u8 gMoveDescription_PikaPapow[] = _("Pikachu's love increases its\npower. It never misses.");
const u8 gMoveDescription_BouncyBubble[] = _("An attack that absorbs\nall the damage inflicted.");
const u8 gMoveDescription_BuzzyBuzz[] = _("Shoots a jolt of electricity\nthat always paralyzes.");
const u8 gMoveDescription_SizzlySlide[] = _("User cloaked in fire charges.\nLeaves the foe with a burn.");
const u8 gMoveDescription_GlitzyGlow[] = _("Telekinetic force that sets\nwall, lowering Sp. Atk damage.");
const u8 gMoveDescription_BaddyBad[] = _("Acting badly, attacks. Sets\nwall, lowering Attack damage.");
const u8 gMoveDescription_SappySeed[] = _("Giant stalk scatters seeds\nthat drain HP every turn.");
const u8 gMoveDescription_FreezyFrost[] = _("Crystal from cold haze hits.\nEliminates all stat changes.");
const u8 gMoveDescription_SparklySwirl[] = _("Wrap foe with whirlwind of\nscent. Heals party's status.");
const u8 gMoveDescription_VeeveeVolley[] = _("Eevee's love increases its\npower. It never misses.");
const u8 gMoveDescription_DoubleIronBash[] = _("The user spins and hits with\nits arms. May cause flinch.");
const u8 gMoveDescription_DynamaxCannon[] = _("Fires a strong beam. Deals\n2x damage to Dynamaxed foes.");
const u8 gMoveDescription_SnipeShot[] = _("The user ignores effects\nthat draw in moves.");
const u8 gMoveDescription_JawLock[] = _("Prevents the user and\nthe target from escaping.");
const u8 gMoveDescription_StuffCheeks[] = _("Consumes the user's Berry,\nthen sharply raises Def.");
const u8 gMoveDescription_NoRetreat[] = _("Raises all of the user's\nstats but prevents escape.");
const u8 gMoveDescription_TarShot[] = _("Lowers the foe's Speed and\nmakes it weak to Fire.");
const u8 gMoveDescription_MagicPowder[] = _("Magic powder changes the\ntarget into a Psychic-type.");
const u8 gMoveDescription_DragonDarts[] = _("The user attacks twice. Two\ntargets are hit once each.");
const u8 gMoveDescription_Teatime[] = _("All Pokémon have teatime\nand eat their Berries.");
const u8 gMoveDescription_Octolock[] = _("Traps the foe to lower Def\nand Sp. Def fall each turn.");
const u8 gMoveDescription_BoltBeak[] = _("Double power if the user\nmoves before the target.");
const u8 gMoveDescription_FishiousRend[] = _("Double power if the user\nmoves before the target.");
const u8 gMoveDescription_CourtChange[] = _("The user swaps effects on\neither side of the field.");
const u8 gMoveDescription_ClangorousSoul[] = _("The user uses some of its\nHP to raise all its stats.");
const u8 gMoveDescription_BodyPress[] = _("Does more damage the\nhigher the user's Def.");
const u8 gMoveDescription_Decorate[] = _("The user sharply raises\nthe target's Atk and Sp.Atk.");
const u8 gMoveDescription_DrumBeating[] = _("Plays a drum to attack.\nThe foe's Speed is lowered.");
const u8 gMoveDescription_SnapTrap[] = _("Snares the target in a snap\ntrap for four to five turns.");
const u8 gMoveDescription_PyroBall[] = _("Launches a fiery ball at the\ntarget. It may cause a burn.");
const u8 gMoveDescription_BehemothBlade[] = _("Strikes as a sword. Deals 2x\ndamage to Dynamaxed foes.");
const u8 gMoveDescription_BehemothBash[] = _("Attacks as a shield. Deals 2x\ndamage to Dynamaxed foes.");
const u8 gMoveDescription_AuraWheel[] = _("Raises Speed to attack. The\nType is based on its form.");
const u8 gMoveDescription_BreakingSwipe[] = _("Swings its tail to attack.\nLowers the Atk of those hit.");
const u8 gMoveDescription_BranchPoke[] = _("The user pokes the target\nwith a pointed branch.");
const u8 gMoveDescription_Overdrive[] = _("The user twangs its guitar,\ncausing strong vibrations.");
const u8 gMoveDescription_AppleAcid[] = _("Attacks with tart apple acid\nto lower the foe's Sp. Def.");
const u8 gMoveDescription_GravApple[] = _("Drops an apple from above.\nLowers the foe's Defense.");
const u8 gMoveDescription_SpiritBreak[] = _("Attacks with spirit-breaking\nforce. Lowers Sp. Atk.");
const u8 gMoveDescription_StrangeSteam[] = _("Emits a strange steam to\npotentially confuse the foe.");
const u8 gMoveDescription_LifeDew[] = _("Scatters water to restore\nthe HP of itself and allies.");
const u8 gMoveDescription_Obstruct[] = _("Protects itself, harshly\nlowering Def on contact.");
const u8 gMoveDescription_FalseSurrender[] = _("Bows to stab the foe\nwith hair. It never misses.");
const u8 gMoveDescription_MeteorAssault[] = _("Attacks with a thick leek.\nThe user must then rest.");
const u8 gMoveDescription_Eternabeam[] = _("Eternatus' strongest move.\nThe user rests next turn.");
const u8 gMoveDescription_SteelBeam[] = _("Fires a beam of steel from\nits body. It hurts the user.");
const u8 gMoveDescription_ExpandingForce[] = _("Power goes up and damages\nall foes on Psychic Terrain.");
const u8 gMoveDescription_SteelRoller[] = _("Destroys terrain. Fails if\nground isn't terrain.");
const u8 gMoveDescription_ScaleShot[] = _("Shoots scales 2 to 5 times.\nUps Speed, lowers defense.");
const u8 gMoveDescription_MeteorBeam[] = _("A 2-turn move that raises\nSp. Attack before attacking.");
const u8 gMoveDescription_ShellSideArm[] = _("Deals better of physical and\nspecial damage. May poison.");
const u8 gMoveDescription_MistyExplosion[] = _("Hit everything and faint.\nPowers up on Misty Terrain.");
const u8 gMoveDescription_GrassyGlide[] = _("Gliding on ground, hits. Goes\nfirst on Grassy Terrain.");
const u8 gMoveDescription_RisingVoltage[] = _("This move's power doubles\nwhen on Electric Terrain.");
const u8 gMoveDescription_TerrainPulse[] = _("Type and power changes\ndepending on the terrain.");
const u8 gMoveDescription_SkitterSmack[] = _("User skitters behind foe to\nattack. Lowers foe's Sp. Atk.");
const u8 gMoveDescription_BurningJealousy[] = _("Foes that have stats upped\nduring the turn get burned.");
const u8 gMoveDescription_LashOut[] = _("If stats lowered during this\nturn, power is doubled.");
const u8 gMoveDescription_Poltergeist[] = _("Control foe's item to attack.\nFails if foe has no item.");
const u8 gMoveDescription_CorrosiveGas[] = _("Highly acidic gas melts items\nheld by surrounding Pokémon.");
const u8 gMoveDescription_Coaching[] = _("Properly coaches allies to\nup their Attack and Defense.");
const u8 gMoveDescription_FlipTurn[] = _("Attacks and rushes back to\nswitch with a party Pokémon.");
const u8 gMoveDescription_TripleAxel[] = _("A 3-kick attack that gets\nmore powerful with each hit.");
const u8 gMoveDescription_DualWingbeat[] = _("User slams the target with\nwings and hits twice in a row.");
const u8 gMoveDescription_ScorchingSands[] = _("Throws scorching sand at\nthe target. May leave a burn.");
const u8 gMoveDescription_JungleHealing[] = _("Heals HP and status of\nitself and allies in battle.");
const u8 gMoveDescription_WickedBlow[] = _("Mastering the Dark style,\nstrikes with a critical hit.");
const u8 gMoveDescription_SurgingStrikes[] = _("Mastering the Water style,\nstrikes with 3 critical hits.");
const u8 gMoveDescription_ThunderCage[] = _("Traps the foe in a cage of\nelectricity for  turns.");
const u8 gMoveDescription_DragonEnergy[] = _("The higher the user's HP\nthe more damage caused.");
const u8 gMoveDescription_FreezingGlare[] = _("Shoots psychic power from\nthe eyes. May frostbite.");
const u8 gMoveDescription_FieryWrath[] = _("An attack fueled by your\nwrath. May cause flinching.");
const u8 gMoveDescription_ThunderousKick[] = _("Uses a lightning-like kick\nto hit. Lowers foe's Defense.");
const u8 gMoveDescription_GlacialLance[] = _("Strikes by hurling a blizzard-\ncloaked icicle lance at foes.");
const u8 gMoveDescription_AstralBarrage[] = _("Strikes by sending a frightful\namount of ghosts at foes.");
const u8 gMoveDescription_EerieSpell[] = _("Attacks with psychic power.\nFoe's last move has 3 PP cut.");
const u8 gMoveDescription_DireClaw[] = _("High critical hit chance. May\nparalyze, poison or drowse.");
const u8 gMoveDescription_PsyshieldBash[] = _("Hits a foe with psychic\nenergy. May raise Defense.");
const u8 gMoveDescription_PowerShift[] = _("The user swaps its Attack\nand Defense stats.");
const u8 gMoveDescription_StoneAxe[] = _("High critical hit ratio. Sets\nSplinters that hurt the foe.");
const u8 gMoveDescription_SpringtideStorm[] = _("Wraps a foe in fierce winds.\nVaries with the user's form.");
const u8 gMoveDescription_MysticalPower[] = _("A mysterious power strikes,\nraising the user's Sp. Atk.");
const u8 gMoveDescription_RagingFury[] = _("A rampage of 2 to 3 turns\nthat confuses the user.");
const u8 gMoveDescription_WaveCrash[] = _("A slam shrouded in water.\nIt also hurts the user.");
const u8 gMoveDescription_Chloroblast[] = _("A user-hurting blast of\namassed chlorophyll.");
const u8 gMoveDescription_MountainGale[] = _("Giant chunks of ice damage\nthe foe. It may flinch.");
const u8 gMoveDescription_VictoryDance[] = _("Dances to raise Attack,\nDefense and Speed.");
const u8 gMoveDescription_HeadlongRush[] = _("Hits with a full-body tackle.\nLowers the users's defenses.");
const u8 gMoveDescription_BarbBarrage[] = _("Can poison on impact. Powers\nup against poisoned foes.");
const u8 gMoveDescription_EsperWing[] = _("High critical hit ratio.\nUps the user's Speed.");
const u8 gMoveDescription_BitterMalice[] = _("A spine-chilling resentment.\nLowers the foe's Attack.");
const u8 gMoveDescription_Shelter[] = _("The user hardens their skin,\nsharply raising its Defense.");
const u8 gMoveDescription_TripleArrows[] = _("High critical hit ratio.\nMay lower Defense or flinch.");
const u8 gMoveDescription_InfernalParade[] = _("Hurts a foe harder if it has\nan ailment. May leave a burn.");
const u8 gMoveDescription_CeaselessEdge[] = _("High critical hit ratio. Sets\nSplinters that hurt the foe.");
const u8 gMoveDescription_BleakwindStorm[] = _("Hits with brutal, cold winds.\nMay lower the foe's Speed.");
const u8 gMoveDescription_WildboltStorm[] = _("Hits with a brutal tempest.\nMay inflict paralysis.");
const u8 gMoveDescription_SandsearStorm[] = _("Hits with brutally hot sand.\nMay inflict a burn.");
const u8 gMoveDescription_LunarBlessing[] = _("The user heals and cures\nitself and its ally.");
const u8 gMoveDescription_TakeHeart[] = _("The user lifts its spirits to\nheal and strengthen itself.");
const u8 gMoveDescription_TeraBlast[] = _("If the user's Terastallized,\nit hits with its Tera-type.");
const u8 gMoveDescription_SilkTrap[] = _("Protects itself, lowering\nSpeed on contact.");
const u8 gMoveDescription_AxeKick[] = _("May miss and hurt the kicker.\nMay cause confusion.");
const u8 gMoveDescription_LastRespects[] = _("This move deals more damage\nfor each defeated ally.");
const u8 gMoveDescription_LuminaCrash[] = _("A mind-affecting light\nharshly lowers Sp. Def.");
const u8 gMoveDescription_OrderUp[] = _("Boosts a user's stats\ndepending on Tatsugiri.");
const u8 gMoveDescription_JetPunch[] = _("A punch is thrown at blinding\nspeed to strike first.");
const u8 gMoveDescription_SpicyExtract[] = _("Sharply ups target's Attack,\nharshly lowers its Defense.");
const u8 gMoveDescription_SpinOut[] = _("Furiously strains its legs.\nHarshly lowers user's Speed.");
const u8 gMoveDescription_PopulationBomb[] = _("The user's fellows hit one\nto ten times in a row.");
const u8 gMoveDescription_IceSpinner[] = _("Ice-covered feet hit a foe\nand destroy the terrain.");
const u8 gMoveDescription_GlaiveRush[] = _("Foe attacks next turn can't\nmiss and do double damage.");
const u8 gMoveDescription_RevivalBlessing[] = _("Revives a fainted party {PKMN}\nand restores half of its HP.");
const u8 gMoveDescription_SaltCure[] = _("Hurts foe every turn. Double\ndamage to Steel and Water.");
const u8 gMoveDescription_TripleDive[] = _("Hits target with splashes\nof water 3 times in a row.");
const u8 gMoveDescription_MortalSpin[] = _("Erases trap moves and Leech\nSeed. Poisons adjacent foes.");
const u8 gMoveDescription_Doodle[] = _("Changes user's and ally's\nAbility into the target's.");
const u8 gMoveDescription_FilletAway[] = _("Sharply boosts offenses and\nSpeed by using its own HP.");
const u8 gMoveDescription_KowtowCleave[] = _("User slashes the foe after\nkowtowing. It never misses.");
const u8 gMoveDescription_FlowerTrick[] = _("Rigged bouquet. Always gets\na critical hit, never missing.");
const u8 gMoveDescription_TorchSong[] = _("Flames scorch the target.\nBoosts the user's Sp. Atk.");
const u8 gMoveDescription_AquaStep[] = _("Hits with light, fluid dance\nsteps. Ups the user's Speed.");
const u8 gMoveDescription_RagingBull[] = _("Tackle that breaks barriers.\nUser's form determines type.");
const u8 gMoveDescription_MakeItRain[] = _("Lowers the user's Sp. Atk.\nMoney is recovered after.");
const u8 gMoveDescription_Ruination[] = _("Summons a ruinous disaster\nand cuts half the foe's HP.");
const u8 gMoveDescription_CollisionCourse[] = _("Prehistoric explosion that's\nstronger if super effective.");
const u8 gMoveDescription_ElectroDrift[] = _("Futuristic electricity. It's\nstronger if super effective.");
const u8 gMoveDescription_ShedTail[] = _("Creates a Substitute for\nitself before switching out.");
const u8 gMoveDescription_ChillyReception[] = _("Bad joke summons snowstorm.\nThe user also switches out.");
const u8 gMoveDescription_TidyUp[] = _("User tidies up hazards and\nraises its Attack and Speed.");
const u8 gMoveDescription_Snowscape[] = _("Summons a snowstorm that\nlasts for five turns.");
const u8 gMoveDescription_Pounce[] = _("The user pounces on the foe,\nlowering its Speed.");
const u8 gMoveDescription_Trailblaze[] = _("The user attacks suddenly,\nraising its Speed.");
const u8 gMoveDescription_ChillingWater[] = _("A shower with ice-cold water\nlowers the target's Attack.");
const u8 gMoveDescription_HyperDrill[] = _("A spinning pointed part\nbypasses a foe's Protect.");
const u8 gMoveDescription_TwinBeam[] = _("Mystical eye-beams that hit\nthe target twice in a row.");
const u8 gMoveDescription_RageFist[] = _("The more the user has been\nhit, the stronger the move.");
const u8 gMoveDescription_ArmorCannon[] = _("A strong attack but lowers\nthe defensive stats.");
const u8 gMoveDescription_BitterBlade[] = _("An attack that absorbs\nhalf the damage inflicted.");
const u8 gMoveDescription_DoubleShock[] = _("Discharges all electricity,\nlosing the Electric type.");
const u8 gMoveDescription_GigatonHammer[] = _("Swings a huge hammer. Can't\nbe used twice in a row.");
const u8 gMoveDescription_Comeuppance[] = _("Retaliates strongly against\nwho last hurt the user.");
const u8 gMoveDescription_AquaCutter[] = _("Pressurized water cut with a\nhigh critical-hit ratio.");
const u8 gMoveDescription_BlazingTorque[] = _("---");
const u8 gMoveDescription_WickedTorque[] = _("---");
const u8 gMoveDescription_NoxiousTorque[] = _("---");
const u8 gMoveDescription_CombatTorque[] = _("---");
const u8 gMoveDescription_MagicalTorque[] = _("---");
const u8 gMoveDescription_Psyblade[] = _("This move's power increases\nwhen on Electric Terrain.");
const u8 gMoveDescription_HydroSteam[] = _("This move's power increases\nunder harsh sunlight.");
const u8 gMoveDescription_BloodMoon[] = _("Unleashes the blood moon.\nCan't be used twice in a row.");
const u8 gMoveDescription_MatchaGotcha[] = _("Absorbs half the damage\ninflicted. May cause a burn.");
const u8 gMoveDescription_SyrupBomb[] = _("Lowers the foe's speed\neach turn for 3 turns.");
const u8 gMoveDescription_IvyCudgel[] = _("Type changes with held mask.\nHigh critical-hit ratio.");
const u8 gMoveDescription_ElectroShot[] = _("Absorbs electricity in one turn,\nthen attacks next turn.");
const u8 gMoveDescription_TeraStarstorm[] = _("Damages all opponents if user is\nStellar form Terapagos.");
const u8 gMoveDescription_FickleBeam[] = _("Shoots a beam of light.\nSometimes twice as strong.");
const u8 gMoveDescription_BurningBulwark[] = _("Evades attack, and burns\nthe foe if struck.");
const u8 gMoveDescription_Thunderclap[] = _("");
const u8 gMoveDescription_MightyCleave[] = _("");
const u8 gMoveDescription_TachyonCutter[] = _("Launches particle blades at\nthe target. Strikes twice.");
const u8 gMoveDescription_HardPress[] = _("");
const u8 gMoveDescription_DragonCheer[] = _("Increases allies' critical hit\nratio, especially if Dragons.");
const u8 gMoveDescription_AlluringVoice[] = _("Confuses the target if their\nstats were boosted this turn.");
const u8 gMoveDescription_TemperFlare[] = _("A desperation attack. Power\ndoubles if last move failed.");
const u8 gMoveDescription_SupercellSlam[] = _("An electrified slam. If it\nmisses, the user is hurt.");
const u8 gMoveDescription_PsychicNoise[] = _("Unpleasant sound waves that\ndamage and prevent healing.");
const u8 gMoveDescription_UpperHand[] = _("Makes the target flinch if\nreadying a priority move.");
const u8 gMoveDescription_MalignantChain[] = _("A corrosive chain attack\nthat may badly poison.");

// ---------------------------------------------------------------------------
// Section 3: Move Description Pointer Table
// ---------------------------------------------------------------------------

const u8 *const gMoveDescriptionPointers[MOVES_COUNT - 1] = {
    [MOVE_POUND               - 1] = gMoveDescription_Pound,
    [MOVE_KARATE_CHOP         - 1] = gMoveDescription_KarateChop,
    [MOVE_DOUBLE_SLAP         - 1] = gMoveDescription_DoubleSlap,
    [MOVE_COMET_PUNCH         - 1] = gMoveDescription_CometPunch,
    [MOVE_MEGA_PUNCH          - 1] = gMoveDescription_MegaPunch,
    [MOVE_PAY_DAY             - 1] = gMoveDescription_PayDay,
    [MOVE_FIRE_PUNCH          - 1] = gMoveDescription_FirePunch,
    [MOVE_ICE_PUNCH           - 1] = gMoveDescription_IcePunch,
    [MOVE_THUNDER_PUNCH       - 1] = gMoveDescription_ThunderPunch,
    [MOVE_SCRATCH             - 1] = gMoveDescription_Scratch,
    [MOVE_VISE_GRIP           - 1] = gMoveDescription_ViseGrip,
    [MOVE_GUILLOTINE          - 1] = gMoveDescription_Guillotine,
    [MOVE_RAZOR_WIND          - 1] = gMoveDescription_RazorWind,
    [MOVE_SWORDS_DANCE        - 1] = gMoveDescription_SwordsDance,
    [MOVE_CUT                 - 1] = gMoveDescription_Cut,
    [MOVE_GUST                - 1] = gMoveDescription_Gust,
    [MOVE_WING_ATTACK         - 1] = gMoveDescription_WingAttack,
    [MOVE_WHIRLWIND           - 1] = gMoveDescription_Whirlwind,
    [MOVE_FLY                 - 1] = gMoveDescription_Fly,
    [MOVE_BIND                - 1] = gMoveDescription_Bind,
    [MOVE_SLAM                - 1] = gMoveDescription_Slam,
    [MOVE_VINE_WHIP           - 1] = gMoveDescription_VineWhip,
    [MOVE_STOMP               - 1] = gMoveDescription_Stomp,
    [MOVE_DOUBLE_KICK         - 1] = gMoveDescription_DoubleKick,
    [MOVE_MEGA_KICK           - 1] = gMoveDescription_MegaKick,
    [MOVE_JUMP_KICK           - 1] = gMoveDescription_JumpKick,
    [MOVE_ROLLING_KICK        - 1] = gMoveDescription_RollingKick,
    [MOVE_SAND_ATTACK         - 1] = gMoveDescription_SandAttack,
    [MOVE_HEADBUTT            - 1] = gMoveDescription_Headbutt,
    [MOVE_HORN_ATTACK         - 1] = gMoveDescription_HornAttack,
    [MOVE_FURY_ATTACK         - 1] = gMoveDescription_FuryAttack,
    [MOVE_HORN_DRILL          - 1] = gMoveDescription_HornDrill,
    [MOVE_TACKLE              - 1] = gMoveDescription_Tackle,
    [MOVE_BODY_SLAM           - 1] = gMoveDescription_BodySlam,
    [MOVE_WRAP                - 1] = gMoveDescription_Wrap,
    [MOVE_TAKE_DOWN           - 1] = gMoveDescription_TakeDown,
    [MOVE_THRASH              - 1] = gMoveDescription_Thrash,
    [MOVE_DOUBLE_EDGE         - 1] = gMoveDescription_DoubleEdge,
    [MOVE_TAIL_WHIP           - 1] = gMoveDescription_TailWhip,
    [MOVE_POISON_STING        - 1] = gMoveDescription_PoisonSting,
    [MOVE_TWINEEDLE           - 1] = gMoveDescription_Twineedle,
    [MOVE_PIN_MISSILE         - 1] = gMoveDescription_PinMissile,
    [MOVE_LEER                - 1] = gMoveDescription_Leer,
    [MOVE_BITE                - 1] = gMoveDescription_Bite,
    [MOVE_GROWL               - 1] = gMoveDescription_Growl,
    [MOVE_ROAR                - 1] = gMoveDescription_Roar,
    [MOVE_SING                - 1] = gMoveDescription_Sing,
    [MOVE_SUPERSONIC          - 1] = gMoveDescription_Supersonic,
    [MOVE_SONIC_BOOM          - 1] = gMoveDescription_SonicBoom,
    [MOVE_DISABLE             - 1] = gMoveDescription_Disable,
    [MOVE_ACID                - 1] = gMoveDescription_Acid,
    [MOVE_EMBER               - 1] = gMoveDescription_Ember,
    [MOVE_FLAMETHROWER        - 1] = gMoveDescription_Flamethrower,
    [MOVE_MIST                - 1] = gMoveDescription_Mist,
    [MOVE_WATER_GUN           - 1] = gMoveDescription_WaterGun,
    [MOVE_HYDRO_PUMP          - 1] = gMoveDescription_HydroPump,
    [MOVE_SURF                - 1] = gMoveDescription_Surf,
    [MOVE_ICE_BEAM            - 1] = gMoveDescription_IceBeam,
    [MOVE_BLIZZARD            - 1] = gMoveDescription_Blizzard,
    [MOVE_PSYBEAM             - 1] = gMoveDescription_Psybeam,
    [MOVE_BUBBLE_BEAM         - 1] = gMoveDescription_BubbleBeam,
    [MOVE_AURORA_BEAM         - 1] = gMoveDescription_AuroraBeam,
    [MOVE_HYPER_BEAM          - 1] = gMoveDescription_HyperBeam,
    [MOVE_PECK                - 1] = gMoveDescription_Peck,
    [MOVE_DRILL_PECK          - 1] = gMoveDescription_DrillPeck,
    [MOVE_SUBMISSION          - 1] = gMoveDescription_Submission,
    [MOVE_LOW_KICK            - 1] = gMoveDescription_LowKick,
    [MOVE_COUNTER             - 1] = gMoveDescription_Counter,
    [MOVE_SEISMIC_TOSS        - 1] = gMoveDescription_SeismicToss,
    [MOVE_STRENGTH            - 1] = gMoveDescription_Strength,
    [MOVE_ABSORB              - 1] = gMoveDescription_Absorb,
    [MOVE_MEGA_DRAIN          - 1] = gMoveDescription_MegaDrain,
    [MOVE_LEECH_SEED          - 1] = gMoveDescription_LeechSeed,
    [MOVE_GROWTH              - 1] = gMoveDescription_Growth,
    [MOVE_RAZOR_LEAF          - 1] = gMoveDescription_RazorLeaf,
    [MOVE_SOLAR_BEAM          - 1] = gMoveDescription_SolarBeam,
    [MOVE_POISON_POWDER       - 1] = gMoveDescription_PoisonPowder,
    [MOVE_STUN_SPORE          - 1] = gMoveDescription_StunSpore,
    [MOVE_SLEEP_POWDER        - 1] = gMoveDescription_SleepPowder,
    [MOVE_PETAL_DANCE         - 1] = gMoveDescription_PetalDance,
    [MOVE_STRING_SHOT         - 1] = gMoveDescription_StringShot,
    [MOVE_DRAGON_RAGE         - 1] = gMoveDescription_DragonRage,
    [MOVE_FIRE_SPIN           - 1] = gMoveDescription_FireSpin,
    [MOVE_THUNDER_SHOCK       - 1] = gMoveDescription_ThunderShock,
    [MOVE_THUNDERBOLT         - 1] = gMoveDescription_Thunderbolt,
    [MOVE_THUNDER_WAVE        - 1] = gMoveDescription_ThunderWave,
    [MOVE_THUNDER             - 1] = gMoveDescription_Thunder,
    [MOVE_ROCK_THROW          - 1] = gMoveDescription_RockThrow,
    [MOVE_EARTHQUAKE          - 1] = gMoveDescription_Earthquake,
    [MOVE_FISSURE             - 1] = gMoveDescription_Fissure,
    [MOVE_DIG                 - 1] = gMoveDescription_Dig,
    [MOVE_TOXIC               - 1] = gMoveDescription_Toxic,
    [MOVE_CONFUSION           - 1] = gMoveDescription_Confusion,
    [MOVE_PSYCHIC             - 1] = gMoveDescription_Psychic,
    [MOVE_HYPNOSIS            - 1] = gMoveDescription_Hypnosis,
    [MOVE_MEDITATE            - 1] = gMoveDescription_Meditate,
    [MOVE_AGILITY             - 1] = gMoveDescription_Agility,
    [MOVE_QUICK_ATTACK        - 1] = gMoveDescription_QuickAttack,
    [MOVE_RAGE                - 1] = gMoveDescription_Rage,
    [MOVE_TELEPORT            - 1] = gMoveDescription_Teleport,
    [MOVE_NIGHT_SHADE         - 1] = gMoveDescription_NightShade,
    [MOVE_MIMIC               - 1] = gMoveDescription_Mimic,
    [MOVE_SCREECH             - 1] = gMoveDescription_Screech,
    [MOVE_DOUBLE_TEAM         - 1] = gMoveDescription_DoubleTeam,
    [MOVE_RECOVER             - 1] = gMoveDescription_Recover,
    [MOVE_HARDEN              - 1] = gMoveDescription_Harden,
    [MOVE_MINIMIZE            - 1] = gMoveDescription_Minimize,
    [MOVE_SMOKESCREEN         - 1] = gMoveDescription_Smokescreen,
    [MOVE_CONFUSE_RAY         - 1] = gMoveDescription_ConfuseRay,
    [MOVE_WITHDRAW            - 1] = gMoveDescription_Withdraw,
    [MOVE_DEFENSE_CURL        - 1] = gMoveDescription_DefenseCurl,
    [MOVE_BARRIER             - 1] = gMoveDescription_Barrier,
    [MOVE_LIGHT_SCREEN        - 1] = gMoveDescription_LightScreen,
    [MOVE_HAZE                - 1] = gMoveDescription_Haze,
    [MOVE_REFLECT             - 1] = gMoveDescription_Reflect,
    [MOVE_FOCUS_ENERGY        - 1] = gMoveDescription_FocusEnergy,
    [MOVE_BIDE                - 1] = gMoveDescription_Bide,
    [MOVE_METRONOME           - 1] = gMoveDescription_Metronome,
    [MOVE_MIRROR_MOVE         - 1] = gMoveDescription_MirrorMove,
    [MOVE_SELF_DESTRUCT       - 1] = gMoveDescription_SelfDestruct,
    [MOVE_EGG_BOMB            - 1] = gMoveDescription_EggBomb,
    [MOVE_LICK                - 1] = gMoveDescription_Lick,
    [MOVE_SMOG                - 1] = gMoveDescription_Smog,
    [MOVE_SLUDGE              - 1] = gMoveDescription_Sludge,
    [MOVE_BONE_CLUB           - 1] = gMoveDescription_BoneClub,
    [MOVE_FIRE_BLAST          - 1] = gMoveDescription_FireBlast,
    [MOVE_WATERFALL           - 1] = gMoveDescription_Waterfall,
    [MOVE_CLAMP               - 1] = gMoveDescription_Clamp,
    [MOVE_SWIFT               - 1] = gMoveDescription_Swift,
    [MOVE_SKULL_BASH          - 1] = gMoveDescription_SkullBash,
    [MOVE_SPIKE_CANNON        - 1] = gMoveDescription_SpikeCannon,
    [MOVE_CONSTRICT           - 1] = gMoveDescription_Constrict,
    [MOVE_AMNESIA             - 1] = gMoveDescription_Amnesia,
    [MOVE_KINESIS             - 1] = gMoveDescription_Kinesis,
    [MOVE_SOFT_BOILED         - 1] = gMoveDescription_SoftBoiled,
    [MOVE_HIGH_JUMP_KICK      - 1] = gMoveDescription_HighJumpKick,
    [MOVE_GLARE               - 1] = gMoveDescription_Glare,
    [MOVE_DREAM_EATER         - 1] = gMoveDescription_DreamEater,
    [MOVE_POISON_GAS          - 1] = gMoveDescription_PoisonGas,
    [MOVE_BARRAGE             - 1] = gMoveDescription_Barrage,
    [MOVE_LEECH_LIFE          - 1] = gMoveDescription_LeechLife,
    [MOVE_LOVELY_KISS         - 1] = gMoveDescription_LovelyKiss,
    [MOVE_SKY_ATTACK          - 1] = gMoveDescription_SkyAttack,
    [MOVE_TRANSFORM           - 1] = gMoveDescription_Transform,
    [MOVE_BUBBLE              - 1] = gMoveDescription_Bubble,
    [MOVE_DIZZY_PUNCH         - 1] = gMoveDescription_DizzyPunch,
    [MOVE_SPORE               - 1] = gMoveDescription_Spore,
    [MOVE_FLASH               - 1] = gMoveDescription_Flash,
    [MOVE_PSYWAVE             - 1] = gMoveDescription_Psywave,
    [MOVE_SPLASH              - 1] = gMoveDescription_Splash,
    [MOVE_ACID_ARMOR          - 1] = gMoveDescription_AcidArmor,
    [MOVE_CRABHAMMER          - 1] = gMoveDescription_Crabhammer,
    [MOVE_EXPLOSION           - 1] = gMoveDescription_Explosion,
    [MOVE_FURY_SWIPES         - 1] = gMoveDescription_FurySwipes,
    [MOVE_BONEMERANG          - 1] = gMoveDescription_Bonemerang,
    [MOVE_REST                - 1] = gMoveDescription_Rest,
    [MOVE_ROCK_SLIDE          - 1] = gMoveDescription_RockSlide,
    [MOVE_HYPER_FANG          - 1] = gMoveDescription_HyperFang,
    [MOVE_SHARPEN             - 1] = gMoveDescription_Sharpen,
    [MOVE_CONVERSION          - 1] = gMoveDescription_Conversion,
    [MOVE_TRI_ATTACK          - 1] = gMoveDescription_TriAttack,
    [MOVE_SUPER_FANG          - 1] = gMoveDescription_SuperFang,
    [MOVE_SLASH               - 1] = gMoveDescription_Slash,
    [MOVE_SUBSTITUTE          - 1] = gMoveDescription_Substitute,
    [MOVE_STRUGGLE            - 1] = gMoveDescription_Struggle,
    [MOVE_SKETCH              - 1] = gMoveDescription_Sketch,
    [MOVE_TRIPLE_KICK         - 1] = gMoveDescription_TripleKick,
    [MOVE_THIEF               - 1] = gMoveDescription_Thief,
    [MOVE_SPIDER_WEB          - 1] = gMoveDescription_SpiderWeb,
    [MOVE_MIND_READER         - 1] = gMoveDescription_MindReader,
    [MOVE_NIGHTMARE           - 1] = gMoveDescription_Nightmare,
    [MOVE_FLAME_WHEEL         - 1] = gMoveDescription_FlameWheel,
    [MOVE_SNORE               - 1] = gMoveDescription_Snore,
    [MOVE_CURSE               - 1] = gMoveDescription_Curse,
    [MOVE_FLAIL               - 1] = gMoveDescription_Flail,
    [MOVE_CONVERSION_2        - 1] = gMoveDescription_Conversion2,
    [MOVE_AEROBLAST           - 1] = gMoveDescription_Aeroblast,
    [MOVE_COTTON_SPORE        - 1] = gMoveDescription_CottonSpore,
    [MOVE_REVERSAL            - 1] = gMoveDescription_Reversal,
    [MOVE_SPITE               - 1] = gMoveDescription_Spite,
    [MOVE_POWDER_SNOW         - 1] = gMoveDescription_PowderSnow,
    [MOVE_PROTECT             - 1] = gMoveDescription_Protect,
    [MOVE_MACH_PUNCH          - 1] = gMoveDescription_MachPunch,
    [MOVE_SCARY_FACE          - 1] = gMoveDescription_ScaryFace,
    [MOVE_FEINT_ATTACK        - 1] = gMoveDescription_FeintAttack,
    [MOVE_SWEET_KISS          - 1] = gMoveDescription_SweetKiss,
    [MOVE_BELLY_DRUM          - 1] = gMoveDescription_BellyDrum,
    [MOVE_SLUDGE_BOMB         - 1] = gMoveDescription_SludgeBomb,
    [MOVE_MUD_SLAP            - 1] = gMoveDescription_MudSlap,
    [MOVE_OCTAZOOKA           - 1] = gMoveDescription_Octazooka,
    [MOVE_SPIKES              - 1] = gMoveDescription_Spikes,
    [MOVE_ZAP_CANNON          - 1] = gMoveDescription_ZapCannon,
    [MOVE_FORESIGHT           - 1] = gMoveDescription_Foresight,
    [MOVE_DESTINY_BOND        - 1] = gMoveDescription_DestinyBond,
    [MOVE_PERISH_SONG         - 1] = gMoveDescription_PerishSong,
    [MOVE_ICY_WIND            - 1] = gMoveDescription_IcyWind,
    [MOVE_DETECT              - 1] = gMoveDescription_Detect,
    [MOVE_BONE_RUSH           - 1] = gMoveDescription_BoneRush,
    [MOVE_LOCK_ON             - 1] = gMoveDescription_LockOn,
    [MOVE_OUTRAGE             - 1] = gMoveDescription_Outrage,
    [MOVE_SANDSTORM           - 1] = gMoveDescription_Sandstorm,
    [MOVE_GIGA_DRAIN          - 1] = gMoveDescription_GigaDrain,
    [MOVE_ENDURE              - 1] = gMoveDescription_Endure,
    [MOVE_CHARM               - 1] = gMoveDescription_Charm,
    [MOVE_ROLLOUT             - 1] = gMoveDescription_Rollout,
    [MOVE_FALSE_SWIPE         - 1] = gMoveDescription_FalseSwipe,
    [MOVE_SWAGGER             - 1] = gMoveDescription_Swagger,
    [MOVE_MILK_DRINK          - 1] = gMoveDescription_MilkDrink,
    [MOVE_SPARK               - 1] = gMoveDescription_Spark,
    [MOVE_FURY_CUTTER         - 1] = gMoveDescription_FuryCutter,
    [MOVE_STEEL_WING          - 1] = gMoveDescription_SteelWing,
    [MOVE_MEAN_LOOK           - 1] = gMoveDescription_MeanLook,
    [MOVE_ATTRACT             - 1] = gMoveDescription_Attract,
    [MOVE_SLEEP_TALK          - 1] = gMoveDescription_SleepTalk,
    [MOVE_HEAL_BELL           - 1] = gMoveDescription_HealBell,
    [MOVE_RETURN              - 1] = gMoveDescription_Return,
    [MOVE_PRESENT             - 1] = gMoveDescription_Present,
    [MOVE_FRUSTRATION         - 1] = gMoveDescription_Frustration,
    [MOVE_SAFEGUARD           - 1] = gMoveDescription_Safeguard,
    [MOVE_PAIN_SPLIT          - 1] = gMoveDescription_PainSplit,
    [MOVE_SACRED_FIRE         - 1] = gMoveDescription_SacredFire,
    [MOVE_MAGNITUDE           - 1] = gMoveDescription_Magnitude,
    [MOVE_DYNAMIC_PUNCH       - 1] = gMoveDescription_DynamicPunch,
    [MOVE_MEGAHORN            - 1] = gMoveDescription_Megahorn,
    [MOVE_DRAGON_BREATH       - 1] = gMoveDescription_DragonBreath,
    [MOVE_BATON_PASS          - 1] = gMoveDescription_BatonPass,
    [MOVE_ENCORE              - 1] = gMoveDescription_Encore,
    [MOVE_PURSUIT             - 1] = gMoveDescription_Pursuit,
    [MOVE_RAPID_SPIN          - 1] = gMoveDescription_RapidSpin,
    [MOVE_SWEET_SCENT         - 1] = gMoveDescription_SweetScent,
    [MOVE_IRON_TAIL           - 1] = gMoveDescription_IronTail,
    [MOVE_METAL_CLAW          - 1] = gMoveDescription_MetalClaw,
    [MOVE_VITAL_THROW         - 1] = gMoveDescription_VitalThrow,
    [MOVE_MORNING_SUN         - 1] = gMoveDescription_MorningSun,
    [MOVE_SYNTHESIS           - 1] = gMoveDescription_Synthesis,
    [MOVE_MOONLIGHT           - 1] = gMoveDescription_Moonlight,
    [MOVE_HIDDEN_POWER        - 1] = gMoveDescription_HiddenPower,
    [MOVE_CROSS_CHOP          - 1] = gMoveDescription_CrossChop,
    [MOVE_TWISTER             - 1] = gMoveDescription_Twister,
    [MOVE_RAIN_DANCE          - 1] = gMoveDescription_RainDance,
    [MOVE_SUNNY_DAY           - 1] = gMoveDescription_SunnyDay,
    [MOVE_CRUNCH              - 1] = gMoveDescription_Crunch,
    [MOVE_MIRROR_COAT         - 1] = gMoveDescription_MirrorCoat,
    [MOVE_PSYCH_UP            - 1] = gMoveDescription_PsychUp,
    [MOVE_EXTREME_SPEED       - 1] = gMoveDescription_ExtremeSpeed,
    [MOVE_ANCIENT_POWER       - 1] = gMoveDescription_AncientPower,
    [MOVE_SHADOW_BALL         - 1] = gMoveDescription_ShadowBall,
    [MOVE_FUTURE_SIGHT        - 1] = gMoveDescription_FutureSight,
    [MOVE_ROCK_SMASH          - 1] = gMoveDescription_RockSmash,
    [MOVE_WHIRLPOOL           - 1] = gMoveDescription_Whirlpool,
    [MOVE_BEAT_UP             - 1] = gMoveDescription_BeatUp,
    [MOVE_FAKE_OUT            - 1] = gMoveDescription_FakeOut,
    [MOVE_UPROAR              - 1] = gMoveDescription_Uproar,
    [MOVE_STOCKPILE           - 1] = gMoveDescription_Stockpile,
    [MOVE_SPIT_UP             - 1] = gMoveDescription_SpitUp,
    [MOVE_SWALLOW             - 1] = gMoveDescription_Swallow,
    [MOVE_HEAT_WAVE           - 1] = gMoveDescription_HeatWave,
    [MOVE_HAIL                - 1] = gMoveDescription_Hail,
    [MOVE_TORMENT             - 1] = gMoveDescription_Torment,
    [MOVE_FLATTER             - 1] = gMoveDescription_Flatter,
    [MOVE_WILL_O_WISP         - 1] = gMoveDescription_WillOWisp,
    [MOVE_MEMENTO             - 1] = gMoveDescription_Memento,
    [MOVE_FACADE              - 1] = gMoveDescription_Facade,
    [MOVE_FOCUS_PUNCH         - 1] = gMoveDescription_FocusPunch,
    [MOVE_SMELLING_SALTS      - 1] = gMoveDescription_SmellingSalts,
    [MOVE_FOLLOW_ME           - 1] = gMoveDescription_FollowMe,
    [MOVE_NATURE_POWER        - 1] = gMoveDescription_NaturePower,
    [MOVE_CHARGE              - 1] = gMoveDescription_Charge,
    [MOVE_TAUNT               - 1] = gMoveDescription_Taunt,
    [MOVE_HELPING_HAND        - 1] = gMoveDescription_HelpingHand,
    [MOVE_TRICK               - 1] = gMoveDescription_Trick,
    [MOVE_ROLE_PLAY           - 1] = gMoveDescription_RolePlay,
    [MOVE_WISH                - 1] = gMoveDescription_Wish,
    [MOVE_ASSIST              - 1] = gMoveDescription_Assist,
    [MOVE_INGRAIN             - 1] = gMoveDescription_Ingrain,
    [MOVE_SUPERPOWER          - 1] = gMoveDescription_Superpower,
    [MOVE_MAGIC_COAT          - 1] = gMoveDescription_MagicCoat,
    [MOVE_RECYCLE             - 1] = gMoveDescription_Recycle,
    [MOVE_REVENGE             - 1] = gMoveDescription_Revenge,
    [MOVE_BRICK_BREAK         - 1] = gMoveDescription_BrickBreak,
    [MOVE_YAWN                - 1] = gMoveDescription_Yawn,
    [MOVE_KNOCK_OFF           - 1] = gMoveDescription_KnockOff,
    [MOVE_ENDEAVOR            - 1] = gMoveDescription_Endeavor,
    [MOVE_ERUPTION            - 1] = gMoveDescription_Eruption,
    [MOVE_SKILL_SWAP          - 1] = gMoveDescription_SkillSwap,
    [MOVE_IMPRISON            - 1] = gMoveDescription_Imprison,
    [MOVE_REFRESH             - 1] = gMoveDescription_Refresh,
    [MOVE_GRUDGE              - 1] = gMoveDescription_Grudge,
    [MOVE_SNATCH              - 1] = gMoveDescription_Snatch,
    [MOVE_SECRET_POWER        - 1] = gMoveDescription_SecretPower,
    [MOVE_DIVE                - 1] = gMoveDescription_Dive,
    [MOVE_ARM_THRUST          - 1] = gMoveDescription_ArmThrust,
    [MOVE_CAMOUFLAGE          - 1] = gMoveDescription_Camouflage,
    [MOVE_TAIL_GLOW           - 1] = gMoveDescription_TailGlow,
    [MOVE_LUSTER_PURGE        - 1] = gMoveDescription_LusterPurge,
    [MOVE_MIST_BALL           - 1] = gMoveDescription_MistBall,
    [MOVE_FEATHER_DANCE       - 1] = gMoveDescription_FeatherDance,
    [MOVE_TEETER_DANCE        - 1] = gMoveDescription_TeeterDance,
    [MOVE_BLAZE_KICK          - 1] = gMoveDescription_BlazeKick,
    [MOVE_MUD_SPORT           - 1] = gMoveDescription_MudSport,
    [MOVE_ICE_BALL            - 1] = gMoveDescription_IceBall,
    [MOVE_NEEDLE_ARM          - 1] = gMoveDescription_NeedleArm,
    [MOVE_SLACK_OFF           - 1] = gMoveDescription_SlackOff,
    [MOVE_HYPER_VOICE         - 1] = gMoveDescription_HyperVoice,
    [MOVE_POISON_FANG         - 1] = gMoveDescription_PoisonFang,
    [MOVE_CRUSH_CLAW          - 1] = gMoveDescription_CrushClaw,
    [MOVE_BLAST_BURN          - 1] = gMoveDescription_BlastBurn,
    [MOVE_HYDRO_CANNON        - 1] = gMoveDescription_HydroCannon,
    [MOVE_METEOR_MASH         - 1] = gMoveDescription_MeteorMash,
    [MOVE_ASTONISH            - 1] = gMoveDescription_Astonish,
    [MOVE_WEATHER_BALL        - 1] = gMoveDescription_WeatherBall,
    [MOVE_AROMATHERAPY        - 1] = gMoveDescription_Aromatherapy,
    [MOVE_FAKE_TEARS          - 1] = gMoveDescription_FakeTears,
    [MOVE_AIR_CUTTER          - 1] = gMoveDescription_AirCutter,
    [MOVE_OVERHEAT            - 1] = gMoveDescription_Overheat,
    [MOVE_ODOR_SLEUTH         - 1] = gMoveDescription_OdorSleuth,
    [MOVE_ROCK_TOMB           - 1] = gMoveDescription_RockTomb,
    [MOVE_SILVER_WIND         - 1] = gMoveDescription_SilverWind,
    [MOVE_METAL_SOUND         - 1] = gMoveDescription_MetalSound,
    [MOVE_GRASS_WHISTLE       - 1] = gMoveDescription_GrassWhistle,
    [MOVE_TICKLE              - 1] = gMoveDescription_Tickle,
    [MOVE_COSMIC_POWER        - 1] = gMoveDescription_CosmicPower,
    [MOVE_WATER_SPOUT         - 1] = gMoveDescription_WaterSpout,
    [MOVE_SIGNAL_BEAM         - 1] = gMoveDescription_SignalBeam,
    [MOVE_SHADOW_PUNCH        - 1] = gMoveDescription_ShadowPunch,
    [MOVE_EXTRASENSORY        - 1] = gMoveDescription_Extrasensory,
    [MOVE_SKY_UPPERCUT        - 1] = gMoveDescription_SkyUppercut,
    [MOVE_SAND_TOMB           - 1] = gMoveDescription_SandTomb,
    [MOVE_SHEER_COLD          - 1] = gMoveDescription_SheerCold,
    [MOVE_MUDDY_WATER         - 1] = gMoveDescription_MuddyWater,
    [MOVE_BULLET_SEED         - 1] = gMoveDescription_BulletSeed,
    [MOVE_AERIAL_ACE          - 1] = gMoveDescription_AerialAce,
    [MOVE_ICICLE_SPEAR        - 1] = gMoveDescription_IcicleSpear,
    [MOVE_IRON_DEFENSE        - 1] = gMoveDescription_IronDefense,
    [MOVE_BLOCK               - 1] = gMoveDescription_Block,
    [MOVE_HOWL                - 1] = gMoveDescription_Howl,
    [MOVE_DRAGON_CLAW         - 1] = gMoveDescription_DragonClaw,
    [MOVE_FRENZY_PLANT        - 1] = gMoveDescription_FrenzyPlant,
    [MOVE_BULK_UP             - 1] = gMoveDescription_BulkUp,
    [MOVE_BOUNCE              - 1] = gMoveDescription_Bounce,
    [MOVE_MUD_SHOT            - 1] = gMoveDescription_MudShot,
    [MOVE_POISON_TAIL         - 1] = gMoveDescription_PoisonTail,
    [MOVE_COVET               - 1] = gMoveDescription_Covet,
    [MOVE_VOLT_TACKLE         - 1] = gMoveDescription_VoltTackle,
    [MOVE_MAGICAL_LEAF        - 1] = gMoveDescription_MagicalLeaf,
    [MOVE_WATER_SPORT         - 1] = gMoveDescription_WaterSport,
    [MOVE_CALM_MIND           - 1] = gMoveDescription_CalmMind,
    [MOVE_LEAF_BLADE          - 1] = gMoveDescription_LeafBlade,
    [MOVE_DRAGON_DANCE        - 1] = gMoveDescription_DragonDance,
    [MOVE_ROCK_BLAST          - 1] = gMoveDescription_RockBlast,
    [MOVE_SHOCK_WAVE          - 1] = gMoveDescription_ShockWave,
    [MOVE_WATER_PULSE         - 1] = gMoveDescription_WaterPulse,
    [MOVE_DOOM_DESIRE         - 1] = gMoveDescription_DoomDesire,
    [MOVE_PSYCHO_BOOST        - 1] = gMoveDescription_PsychoBoost,
    [MOVE_ROOST               - 1] = gMoveDescription_Roost,
    [MOVE_GRAVITY             - 1] = gMoveDescription_Gravity,
    [MOVE_MIRACLE_EYE         - 1] = gMoveDescription_MiracleEye,
    [MOVE_WAKE_UP_SLAP        - 1] = gMoveDescription_WakeUpSlap,
    [MOVE_HAMMER_ARM          - 1] = gMoveDescription_HammerArm,
    [MOVE_GYRO_BALL           - 1] = gMoveDescription_GyroBall,
    [MOVE_HEALING_WISH        - 1] = gMoveDescription_HealingWish,
    [MOVE_BRINE               - 1] = gMoveDescription_Brine,
    [MOVE_NATURAL_GIFT        - 1] = gMoveDescription_NaturalGift,
    [MOVE_FEINT               - 1] = gMoveDescription_Feint,
    [MOVE_PLUCK               - 1] = gMoveDescription_Pluck,
    [MOVE_TAILWIND            - 1] = gMoveDescription_Tailwind,
    [MOVE_ACUPRESSURE         - 1] = gMoveDescription_Acupressure,
    [MOVE_METAL_BURST         - 1] = gMoveDescription_MetalBurst,
    [MOVE_U_TURN              - 1] = gMoveDescription_UTurn,
    [MOVE_CLOSE_COMBAT        - 1] = gMoveDescription_CloseCombat,
    [MOVE_PAYBACK             - 1] = gMoveDescription_Payback,
    [MOVE_ASSURANCE           - 1] = gMoveDescription_Assurance,
    [MOVE_EMBARGO             - 1] = gMoveDescription_Embargo,
    [MOVE_FLING               - 1] = gMoveDescription_Fling,
    [MOVE_PSYCHO_SHIFT        - 1] = gMoveDescription_PsychoShift,
    [MOVE_TRUMP_CARD          - 1] = gMoveDescription_TrumpCard,
    [MOVE_HEAL_BLOCK          - 1] = gMoveDescription_HealBlock,
    [MOVE_WRING_OUT           - 1] = gMoveDescription_WringOut,
    [MOVE_POWER_TRICK         - 1] = gMoveDescription_PowerTrick,
    [MOVE_GASTRO_ACID         - 1] = gMoveDescription_GastroAcid,
    [MOVE_LUCKY_CHANT         - 1] = gMoveDescription_LuckyChant,
    [MOVE_ME_FIRST            - 1] = gMoveDescription_MeFirst,
    [MOVE_COPYCAT             - 1] = gMoveDescription_Copycat,
    [MOVE_POWER_SWAP          - 1] = gMoveDescription_PowerSwap,
    [MOVE_GUARD_SWAP          - 1] = gMoveDescription_GuardSwap,
    [MOVE_PUNISHMENT          - 1] = gMoveDescription_Punishment,
    [MOVE_LAST_RESORT         - 1] = gMoveDescription_LastResort,
    [MOVE_WORRY_SEED          - 1] = gMoveDescription_WorrySeed,
    [MOVE_SUCKER_PUNCH        - 1] = gMoveDescription_SuckerPunch,
    [MOVE_TOXIC_SPIKES        - 1] = gMoveDescription_ToxicSpikes,
    [MOVE_HEART_SWAP          - 1] = gMoveDescription_HeartSwap,
    [MOVE_AQUA_RING           - 1] = gMoveDescription_AquaRing,
    [MOVE_MAGNET_RISE         - 1] = gMoveDescription_MagnetRise,
    [MOVE_FLARE_BLITZ         - 1] = gMoveDescription_FlareBlitz,
    [MOVE_FORCE_PALM          - 1] = gMoveDescription_ForcePalm,
    [MOVE_AURA_SPHERE         - 1] = gMoveDescription_AuraSphere,
    [MOVE_ROCK_POLISH         - 1] = gMoveDescription_RockPolish,
    [MOVE_POISON_JAB          - 1] = gMoveDescription_PoisonJab,
    [MOVE_DARK_PULSE          - 1] = gMoveDescription_DarkPulse,
    [MOVE_NIGHT_SLASH         - 1] = gMoveDescription_NightSlash,
    [MOVE_AQUA_TAIL           - 1] = gMoveDescription_AquaTail,
    [MOVE_SEED_BOMB           - 1] = gMoveDescription_SeedBomb,
    [MOVE_AIR_SLASH           - 1] = gMoveDescription_AirSlash,
    [MOVE_X_SCISSOR           - 1] = gMoveDescription_XScissor,
    [MOVE_BUG_BUZZ            - 1] = gMoveDescription_BugBuzz,
    [MOVE_DRAGON_PULSE        - 1] = gMoveDescription_DragonPulse,
    [MOVE_DRAGON_RUSH         - 1] = gMoveDescription_DragonRush,
    [MOVE_POWER_GEM           - 1] = gMoveDescription_PowerGem,
    [MOVE_DRAIN_PUNCH         - 1] = gMoveDescription_DrainPunch,
    [MOVE_VACUUM_WAVE         - 1] = gMoveDescription_VacuumWave,
    [MOVE_FOCUS_BLAST         - 1] = gMoveDescription_FocusBlast,
    [MOVE_ENERGY_BALL         - 1] = gMoveDescription_EnergyBall,
    [MOVE_BRAVE_BIRD          - 1] = gMoveDescription_BraveBird,
    [MOVE_EARTH_POWER         - 1] = gMoveDescription_EarthPower,
    [MOVE_SWITCHEROO          - 1] = gMoveDescription_Switcheroo,
    [MOVE_GIGA_IMPACT         - 1] = gMoveDescription_GigaImpact,
    [MOVE_NASTY_PLOT          - 1] = gMoveDescription_NastyPlot,
    [MOVE_BULLET_PUNCH        - 1] = gMoveDescription_BulletPunch,
    [MOVE_AVALANCHE           - 1] = gMoveDescription_Avalanche,
    [MOVE_ICE_SHARD           - 1] = gMoveDescription_IceShard,
    [MOVE_SHADOW_CLAW         - 1] = gMoveDescription_ShadowClaw,
    [MOVE_THUNDER_FANG        - 1] = gMoveDescription_ThunderFang,
    [MOVE_ICE_FANG            - 1] = gMoveDescription_IceFang,
    [MOVE_FIRE_FANG           - 1] = gMoveDescription_FireFang,
    [MOVE_SHADOW_SNEAK        - 1] = gMoveDescription_ShadowSneak,
    [MOVE_MUD_BOMB            - 1] = gMoveDescription_MudBomb,
    [MOVE_PSYCHO_CUT          - 1] = gMoveDescription_PsychoCut,
    [MOVE_ZEN_HEADBUTT        - 1] = gMoveDescription_ZenHeadbutt,
    [MOVE_MIRROR_SHOT         - 1] = gMoveDescription_MirrorShot,
    [MOVE_FLASH_CANNON        - 1] = gMoveDescription_FlashCannon,
    [MOVE_ROCK_CLIMB          - 1] = gMoveDescription_RockClimb,
    [MOVE_DEFOG               - 1] = gMoveDescription_Defog,
    [MOVE_TRICK_ROOM          - 1] = gMoveDescription_TrickRoom,
    [MOVE_DRACO_METEOR        - 1] = gMoveDescription_DracoMeteor,
    [MOVE_DISCHARGE           - 1] = gMoveDescription_Discharge,
    [MOVE_LAVA_PLUME          - 1] = gMoveDescription_LavaPlume,
    [MOVE_LEAF_STORM          - 1] = gMoveDescription_LeafStorm,
    [MOVE_POWER_WHIP          - 1] = gMoveDescription_PowerWhip,
    [MOVE_ROCK_WRECKER        - 1] = gMoveDescription_RockWrecker,
    [MOVE_CROSS_POISON        - 1] = gMoveDescription_CrossPoison,
    [MOVE_GUNK_SHOT           - 1] = gMoveDescription_GunkShot,
    [MOVE_IRON_HEAD           - 1] = gMoveDescription_IronHead,
    [MOVE_MAGNET_BOMB         - 1] = gMoveDescription_MagnetBomb,
    [MOVE_STONE_EDGE          - 1] = gMoveDescription_StoneEdge,
    [MOVE_CAPTIVATE           - 1] = gMoveDescription_Captivate,
    [MOVE_STEALTH_ROCK        - 1] = gMoveDescription_StealthRock,
    [MOVE_GRASS_KNOT          - 1] = gMoveDescription_GrassKnot,
    [MOVE_CHATTER             - 1] = gMoveDescription_Chatter,
    [MOVE_JUDGMENT            - 1] = gMoveDescription_Judgment,
    [MOVE_BUG_BITE            - 1] = gMoveDescription_BugBite,
    [MOVE_CHARGE_BEAM         - 1] = gMoveDescription_ChargeBeam,
    [MOVE_WOOD_HAMMER         - 1] = gMoveDescription_WoodHammer,
    [MOVE_AQUA_JET            - 1] = gMoveDescription_AquaJet,
    [MOVE_ATTACK_ORDER        - 1] = gMoveDescription_AttackOrder,
    [MOVE_DEFEND_ORDER        - 1] = gMoveDescription_DefendOrder,
    [MOVE_HEAL_ORDER          - 1] = gMoveDescription_HealOrder,
    [MOVE_HEAD_SMASH          - 1] = gMoveDescription_HeadSmash,
    [MOVE_DOUBLE_HIT          - 1] = gMoveDescription_DoubleHit,
    [MOVE_ROAR_OF_TIME        - 1] = gMoveDescription_RoarOfTime,
    [MOVE_SPACIAL_REND        - 1] = gMoveDescription_SpacialRend,
    [MOVE_LUNAR_DANCE         - 1] = gMoveDescription_LunarDance,
    [MOVE_CRUSH_GRIP          - 1] = gMoveDescription_CrushGrip,
    [MOVE_MAGMA_STORM         - 1] = gMoveDescription_MagmaStorm,
    [MOVE_DARK_VOID           - 1] = gMoveDescription_DarkVoid,
    [MOVE_SEED_FLARE          - 1] = gMoveDescription_SeedFlare,
    [MOVE_OMINOUS_WIND        - 1] = gMoveDescription_OminousWind,
    [MOVE_SHADOW_FORCE        - 1] = gMoveDescription_ShadowForce,
    [MOVE_HONE_CLAWS          - 1] = gMoveDescription_HoneClaws,
    [MOVE_WIDE_GUARD          - 1] = gMoveDescription_WideGuard,
    [MOVE_GUARD_SPLIT         - 1] = gMoveDescription_GuardSplit,
    [MOVE_POWER_SPLIT         - 1] = gMoveDescription_PowerSplit,
    [MOVE_WONDER_ROOM         - 1] = gMoveDescription_WonderRoom,
    [MOVE_PSYSHOCK            - 1] = gMoveDescription_Psyshock,
    [MOVE_VENOSHOCK           - 1] = gMoveDescription_Venoshock,
    [MOVE_AUTOTOMIZE          - 1] = gMoveDescription_Autotomize,
    [MOVE_RAGE_POWDER         - 1] = gMoveDescription_RagePowder,
    [MOVE_TELEKINESIS         - 1] = gMoveDescription_Telekinesis,
    [MOVE_MAGIC_ROOM          - 1] = gMoveDescription_MagicRoom,
    [MOVE_SMACK_DOWN          - 1] = gMoveDescription_SmackDown,
    [MOVE_STORM_THROW         - 1] = gMoveDescription_StormThrow,
    [MOVE_FLAME_BURST         - 1] = gMoveDescription_FlameBurst,
    [MOVE_SLUDGE_WAVE         - 1] = gMoveDescription_SludgeWave,
    [MOVE_QUIVER_DANCE        - 1] = gMoveDescription_QuiverDance,
    [MOVE_HEAVY_SLAM          - 1] = gMoveDescription_HeavySlam,
    [MOVE_SYNCHRONOISE        - 1] = gMoveDescription_Synchronoise,
    [MOVE_ELECTRO_BALL        - 1] = gMoveDescription_ElectroBall,
    [MOVE_SOAK                - 1] = gMoveDescription_Soak,
    [MOVE_FLAME_CHARGE        - 1] = gMoveDescription_FlameCharge,
    [MOVE_COIL                - 1] = gMoveDescription_Coil,
    [MOVE_LOW_SWEEP           - 1] = gMoveDescription_LowSweep,
    [MOVE_ACID_SPRAY          - 1] = gMoveDescription_AcidSpray,
    [MOVE_FOUL_PLAY           - 1] = gMoveDescription_FoulPlay,
    [MOVE_SIMPLE_BEAM         - 1] = gMoveDescription_SimpleBeam,
    [MOVE_ENTRAINMENT         - 1] = gMoveDescription_Entrainment,
    [MOVE_AFTER_YOU           - 1] = gMoveDescription_AfterYou,
    [MOVE_ROUND               - 1] = gMoveDescription_Round,
    [MOVE_ECHOED_VOICE        - 1] = gMoveDescription_EchoedVoice,
    [MOVE_CHIP_AWAY           - 1] = gMoveDescription_ChipAway,
    [MOVE_CLEAR_SMOG          - 1] = gMoveDescription_ClearSmog,
    [MOVE_STORED_POWER        - 1] = gMoveDescription_StoredPower,
    [MOVE_QUICK_GUARD         - 1] = gMoveDescription_QuickGuard,
    [MOVE_ALLY_SWITCH         - 1] = gMoveDescription_AllySwitch,
    [MOVE_SCALD               - 1] = gMoveDescription_Scald,
    [MOVE_SHELL_SMASH         - 1] = gMoveDescription_ShellSmash,
    [MOVE_HEAL_PULSE          - 1] = gMoveDescription_HealPulse,
    [MOVE_HEX                 - 1] = gMoveDescription_Hex,
    [MOVE_SKY_DROP            - 1] = gMoveDescription_SkyDrop,
    [MOVE_SHIFT_GEAR          - 1] = gMoveDescription_ShiftGear,
    [MOVE_CIRCLE_THROW        - 1] = gMoveDescription_CircleThrow,
    [MOVE_INCINERATE          - 1] = gMoveDescription_Incinerate,
    [MOVE_QUASH               - 1] = gMoveDescription_Quash,
    [MOVE_ACROBATICS          - 1] = gMoveDescription_Acrobatics,
    [MOVE_REFLECT_TYPE        - 1] = gMoveDescription_ReflectType,
    [MOVE_RETALIATE           - 1] = gMoveDescription_Retaliate,
    [MOVE_FINAL_GAMBIT        - 1] = gMoveDescription_FinalGambit,
    [MOVE_BESTOW              - 1] = gMoveDescription_Bestow,
    [MOVE_INFERNO             - 1] = gMoveDescription_Inferno,
    [MOVE_WATER_PLEDGE        - 1] = gMoveDescription_WaterPledge,
    [MOVE_FIRE_PLEDGE         - 1] = gMoveDescription_FirePledge,
    [MOVE_GRASS_PLEDGE        - 1] = gMoveDescription_GrassPledge,
    [MOVE_VOLT_SWITCH         - 1] = gMoveDescription_VoltSwitch,
    [MOVE_STRUGGLE_BUG        - 1] = gMoveDescription_StruggleBug,
    [MOVE_BULLDOZE            - 1] = gMoveDescription_Bulldoze,
    [MOVE_FROST_BREATH        - 1] = gMoveDescription_FrostBreath,
    [MOVE_DRAGON_TAIL         - 1] = gMoveDescription_DragonTail,
    [MOVE_WORK_UP             - 1] = gMoveDescription_WorkUp,
    [MOVE_ELECTROWEB          - 1] = gMoveDescription_Electroweb,
    [MOVE_WILD_CHARGE         - 1] = gMoveDescription_WildCharge,
    [MOVE_DRILL_RUN           - 1] = gMoveDescription_DrillRun,
    [MOVE_DUAL_CHOP           - 1] = gMoveDescription_DualChop,
    [MOVE_HEART_STAMP         - 1] = gMoveDescription_HeartStamp,
    [MOVE_HORN_LEECH          - 1] = gMoveDescription_HornLeech,
    [MOVE_SACRED_SWORD        - 1] = gMoveDescription_SacredSword,
    [MOVE_RAZOR_SHELL         - 1] = gMoveDescription_RazorShell,
    [MOVE_HEAT_CRASH          - 1] = gMoveDescription_HeatCrash,
    [MOVE_LEAF_TORNADO        - 1] = gMoveDescription_LeafTornado,
    [MOVE_STEAMROLLER         - 1] = gMoveDescription_Steamroller,
    [MOVE_COTTON_GUARD        - 1] = gMoveDescription_CottonGuard,
    [MOVE_NIGHT_DAZE          - 1] = gMoveDescription_NightDaze,
    [MOVE_PSYSTRIKE           - 1] = gMoveDescription_Psystrike,
    [MOVE_TAIL_SLAP           - 1] = gMoveDescription_TailSlap,
    [MOVE_HURRICANE           - 1] = gMoveDescription_Hurricane,
    [MOVE_HEAD_CHARGE         - 1] = gMoveDescription_HeadCharge,
    [MOVE_GEAR_GRIND          - 1] = gMoveDescription_GearGrind,
    [MOVE_SEARING_SHOT        - 1] = gMoveDescription_SearingShot,
    [MOVE_TECHNO_BLAST        - 1] = gMoveDescription_TechnoBlast,
    [MOVE_RELIC_SONG          - 1] = gMoveDescription_RelicSong,
    [MOVE_SECRET_SWORD        - 1] = gMoveDescription_SecretSword,
    [MOVE_GLACIATE            - 1] = gMoveDescription_Glaciate,
    [MOVE_BOLT_STRIKE         - 1] = gMoveDescription_BoltStrike,
    [MOVE_BLUE_FLARE          - 1] = gMoveDescription_BlueFlare,
    [MOVE_FIERY_DANCE         - 1] = gMoveDescription_FieryDance,
    [MOVE_FREEZE_SHOCK        - 1] = gMoveDescription_FreezeShock,
    [MOVE_ICE_BURN            - 1] = gMoveDescription_IceBurn,
    [MOVE_SNARL               - 1] = gMoveDescription_Snarl,
    [MOVE_ICICLE_CRASH        - 1] = gMoveDescription_IcicleCrash,
    [MOVE_V_CREATE            - 1] = gMoveDescription_VCreate,
    [MOVE_FUSION_FLARE        - 1] = gMoveDescription_FusionFlare,
    [MOVE_FUSION_BOLT         - 1] = gMoveDescription_FusionBolt,
    [MOVE_FLYING_PRESS        - 1] = gMoveDescription_FlyingPress,
    [MOVE_MAT_BLOCK           - 1] = gMoveDescription_MatBlock,
    [MOVE_BELCH               - 1] = gMoveDescription_Belch,
    [MOVE_ROTOTILLER          - 1] = gMoveDescription_Rototiller,
    [MOVE_STICKY_WEB          - 1] = gMoveDescription_StickyWeb,
    [MOVE_FELL_STINGER        - 1] = gMoveDescription_FellStinger,
    [MOVE_PHANTOM_FORCE       - 1] = gMoveDescription_PhantomForce,
    [MOVE_TRICK_OR_TREAT      - 1] = gMoveDescription_TrickOrTreat,
    [MOVE_NOBLE_ROAR          - 1] = gMoveDescription_NobleRoar,
    [MOVE_ION_DELUGE          - 1] = gMoveDescription_IonDeluge,
    [MOVE_PARABOLIC_CHARGE    - 1] = gMoveDescription_ParabolicCharge,
    [MOVE_FORESTS_CURSE       - 1] = gMoveDescription_ForestsCurse,
    [MOVE_PETAL_BLIZZARD      - 1] = gMoveDescription_PetalBlizzard,
    [MOVE_FREEZE_DRY          - 1] = gMoveDescription_FreezeDry,
    [MOVE_DISARMING_VOICE     - 1] = gMoveDescription_DisarmingVoice,
    [MOVE_PARTING_SHOT        - 1] = gMoveDescription_PartingShot,
    [MOVE_TOPSY_TURVY         - 1] = gMoveDescription_TopsyTurvy,
    [MOVE_DRAINING_KISS       - 1] = gMoveDescription_DrainingKiss,
    [MOVE_CRAFTY_SHIELD       - 1] = gMoveDescription_CraftyShield,
    [MOVE_FLOWER_SHIELD       - 1] = gMoveDescription_FlowerShield,
    [MOVE_GRASSY_TERRAIN      - 1] = gMoveDescription_GrassyTerrain,
    [MOVE_MISTY_TERRAIN       - 1] = gMoveDescription_MistyTerrain,
    [MOVE_ELECTRIFY           - 1] = gMoveDescription_Electrify,
    [MOVE_PLAY_ROUGH          - 1] = gMoveDescription_PlayRough,
    [MOVE_FAIRY_WIND          - 1] = gMoveDescription_FairyWind,
    [MOVE_MOONBLAST           - 1] = gMoveDescription_Moonblast,
    [MOVE_BOOMBURST           - 1] = gMoveDescription_Boomburst,
    [MOVE_FAIRY_LOCK          - 1] = gMoveDescription_FairyLock,
    [MOVE_KINGS_SHIELD        - 1] = gMoveDescription_KingsShield,
    [MOVE_PLAY_NICE           - 1] = gMoveDescription_PlayNice,
    [MOVE_CONFIDE             - 1] = gMoveDescription_Confide,
    [MOVE_DIAMOND_STORM       - 1] = gMoveDescription_DiamondStorm,
    [MOVE_STEAM_ERUPTION      - 1] = gMoveDescription_SteamEruption,
    [MOVE_HYPERSPACE_HOLE     - 1] = gMoveDescription_HyperspaceHole,
    [MOVE_WATER_SHURIKEN      - 1] = gMoveDescription_WaterShuriken,
    [MOVE_MYSTICAL_FIRE       - 1] = gMoveDescription_MysticalFire,
    [MOVE_SPIKY_SHIELD        - 1] = gMoveDescription_SpikyShield,
    [MOVE_AROMATIC_MIST       - 1] = gMoveDescription_AromaticMist,
    [MOVE_EERIE_IMPULSE       - 1] = gMoveDescription_EerieImpulse,
    [MOVE_VENOM_DRENCH        - 1] = gMoveDescription_VenomDrench,
    [MOVE_POWDER              - 1] = gMoveDescription_Powder,
    [MOVE_GEOMANCY            - 1] = gMoveDescription_Geomancy,
    [MOVE_MAGNETIC_FLUX       - 1] = gMoveDescription_MagneticFlux,
    [MOVE_HAPPY_HOUR          - 1] = gMoveDescription_HappyHour,
    [MOVE_ELECTRIC_TERRAIN    - 1] = gMoveDescription_ElectricTerrain,
    [MOVE_DAZZLING_GLEAM      - 1] = gMoveDescription_DazzlingGleam,
    [MOVE_CELEBRATE           - 1] = gMoveDescription_Celebrate,
    [MOVE_HOLD_HANDS          - 1] = gMoveDescription_HoldHands,
    [MOVE_BABY_DOLL_EYES      - 1] = gMoveDescription_BabyDollEyes,
    [MOVE_NUZZLE              - 1] = gMoveDescription_Nuzzle,
    [MOVE_HOLD_BACK           - 1] = gMoveDescription_HoldBack,
    [MOVE_INFESTATION         - 1] = gMoveDescription_Infestation,
    [MOVE_POWER_UP_PUNCH      - 1] = gMoveDescription_PowerUpPunch,
    [MOVE_OBLIVION_WING       - 1] = gMoveDescription_OblivionWing,
    [MOVE_THOUSAND_ARROWS     - 1] = gMoveDescription_ThousandArrows,
    [MOVE_THOUSAND_WAVES      - 1] = gMoveDescription_ThousandWaves,
    [MOVE_LANDS_WRATH         - 1] = gMoveDescription_LandsWrath,
    [MOVE_LIGHT_OF_RUIN       - 1] = gMoveDescription_LightOfRuin,
    [MOVE_ORIGIN_PULSE        - 1] = gMoveDescription_OriginPulse,
    [MOVE_PRECIPICE_BLADES    - 1] = gMoveDescription_PrecipiceBlades,
    [MOVE_DRAGON_ASCENT       - 1] = gMoveDescription_DragonAscent,
    [MOVE_HYPERSPACE_FURY     - 1] = gMoveDescription_HyperspaceFury,
    [MOVE_SHORE_UP            - 1] = gMoveDescription_ShoreUp,
    [MOVE_FIRST_IMPRESSION    - 1] = gMoveDescription_FirstImpression,
    [MOVE_BANEFUL_BUNKER      - 1] = gMoveDescription_BanefulBunker,
    [MOVE_SPIRIT_SHACKLE      - 1] = gMoveDescription_SpiritShackle,
    [MOVE_DARKEST_LARIAT      - 1] = gMoveDescription_DarkestLariat,
    [MOVE_SPARKLING_ARIA      - 1] = gMoveDescription_SparklingAria,
    [MOVE_ICE_HAMMER          - 1] = gMoveDescription_IceHammer,
    [MOVE_FLORAL_HEALING      - 1] = gMoveDescription_FloralHealing,
    [MOVE_HIGH_HORSEPOWER     - 1] = gMoveDescription_HighHorsepower,
    [MOVE_STRENGTH_SAP        - 1] = gMoveDescription_StrengthSap,
    [MOVE_SOLAR_BLADE         - 1] = gMoveDescription_SolarBlade,
    [MOVE_LEAFAGE             - 1] = gMoveDescription_Leafage,
    [MOVE_SPOTLIGHT           - 1] = gMoveDescription_Spotlight,
    [MOVE_TOXIC_THREAD        - 1] = gMoveDescription_ToxicThread,
    [MOVE_LASER_FOCUS         - 1] = gMoveDescription_LaserFocus,
    [MOVE_GEAR_UP             - 1] = gMoveDescription_GearUp,
    [MOVE_THROAT_CHOP         - 1] = gMoveDescription_ThroatChop,
    [MOVE_POLLEN_PUFF         - 1] = gMoveDescription_PollenPuff,
    [MOVE_ANCHOR_SHOT         - 1] = gMoveDescription_AnchorShot,
    [MOVE_PSYCHIC_TERRAIN     - 1] = gMoveDescription_PsychicTerrain,
    [MOVE_LUNGE               - 1] = gMoveDescription_Lunge,
    [MOVE_FIRE_LASH           - 1] = gMoveDescription_FireLash,
    [MOVE_POWER_TRIP          - 1] = gMoveDescription_PowerTrip,
    [MOVE_BURN_UP             - 1] = gMoveDescription_BurnUp,
    [MOVE_SPEED_SWAP          - 1] = gMoveDescription_SpeedSwap,
    [MOVE_SMART_STRIKE        - 1] = gMoveDescription_SmartStrike,
    [MOVE_PURIFY              - 1] = gMoveDescription_Purify,
    [MOVE_REVELATION_DANCE    - 1] = gMoveDescription_RevelationDance,
    [MOVE_CORE_ENFORCER       - 1] = gMoveDescription_CoreEnforcer,
    [MOVE_TROP_KICK           - 1] = gMoveDescription_TropKick,
    [MOVE_INSTRUCT            - 1] = gMoveDescription_Instruct,
    [MOVE_BEAK_BLAST          - 1] = gMoveDescription_BeakBlast,
    [MOVE_CLANGING_SCALES     - 1] = gMoveDescription_ClangingScales,
    [MOVE_DRAGON_HAMMER       - 1] = gMoveDescription_DragonHammer,
    [MOVE_BRUTAL_SWING        - 1] = gMoveDescription_BrutalSwing,
    [MOVE_AURORA_VEIL         - 1] = gMoveDescription_AuroraVeil,
    [MOVE_SHELL_TRAP          - 1] = gMoveDescription_ShellTrap,
    [MOVE_FLEUR_CANNON        - 1] = gMoveDescription_FleurCannon,
    [MOVE_PSYCHIC_FANGS       - 1] = gMoveDescription_PsychicFangs,
    [MOVE_STOMPING_TANTRUM    - 1] = gMoveDescription_StompingTantrum,
    [MOVE_SHADOW_BONE         - 1] = gMoveDescription_ShadowBone,
    [MOVE_ACCELEROCK          - 1] = gMoveDescription_Accelerock,
    [MOVE_LIQUIDATION         - 1] = gMoveDescription_Liquidation,
    [MOVE_PRISMATIC_LASER     - 1] = gMoveDescription_PrismaticLaser,
    [MOVE_SPECTRAL_THIEF      - 1] = gMoveDescription_SpectralThief,
    [MOVE_SUNSTEEL_STRIKE     - 1] = gMoveDescription_SunsteelStrike,
    [MOVE_MOONGEIST_BEAM      - 1] = gMoveDescription_MoongeistBeam,
    [MOVE_TEARFUL_LOOK        - 1] = gMoveDescription_TearfulLook,
    [MOVE_ZING_ZAP            - 1] = gMoveDescription_ZingZap,
    [MOVE_NATURES_MADNESS     - 1] = gMoveDescription_NaturesMadness,
    [MOVE_MULTI_ATTACK        - 1] = gMoveDescription_MultiAttack,
    [MOVE_MIND_BLOWN          - 1] = gMoveDescription_MindBlown,
    [MOVE_PLASMA_FISTS        - 1] = gMoveDescription_PlasmaFists,
    [MOVE_PHOTON_GEYSER       - 1] = gMoveDescription_PhotonGeyser,
    [MOVE_ZIPPY_ZAP           - 1] = gMoveDescription_ZippyZap,
    [MOVE_SPLISHY_SPLASH      - 1] = gMoveDescription_SplishySplash,
    [MOVE_FLOATY_FALL         - 1] = gMoveDescription_FloatyFall,
    [MOVE_PIKA_PAPOW          - 1] = gMoveDescription_PikaPapow,
    [MOVE_BOUNCY_BUBBLE       - 1] = gMoveDescription_BouncyBubble,
    [MOVE_BUZZY_BUZZ          - 1] = gMoveDescription_BuzzyBuzz,
    [MOVE_SIZZLY_SLIDE        - 1] = gMoveDescription_SizzlySlide,
    [MOVE_GLITZY_GLOW         - 1] = gMoveDescription_GlitzyGlow,
    [MOVE_BADDY_BAD           - 1] = gMoveDescription_BaddyBad,
    [MOVE_SAPPY_SEED          - 1] = gMoveDescription_SappySeed,
    [MOVE_FREEZY_FROST        - 1] = gMoveDescription_FreezyFrost,
    [MOVE_SPARKLY_SWIRL       - 1] = gMoveDescription_SparklySwirl,
    [MOVE_VEEVEE_VOLLEY       - 1] = gMoveDescription_VeeveeVolley,
    [MOVE_DOUBLE_IRON_BASH    - 1] = gMoveDescription_DoubleIronBash,
    [MOVE_DYNAMAX_CANNON      - 1] = gMoveDescription_DynamaxCannon,
    [MOVE_SNIPE_SHOT          - 1] = gMoveDescription_SnipeShot,
    [MOVE_JAW_LOCK            - 1] = gMoveDescription_JawLock,
    [MOVE_STUFF_CHEEKS        - 1] = gMoveDescription_StuffCheeks,
    [MOVE_NO_RETREAT          - 1] = gMoveDescription_NoRetreat,
    [MOVE_TAR_SHOT            - 1] = gMoveDescription_TarShot,
    [MOVE_MAGIC_POWDER        - 1] = gMoveDescription_MagicPowder,
    [MOVE_DRAGON_DARTS        - 1] = gMoveDescription_DragonDarts,
    [MOVE_TEATIME             - 1] = gMoveDescription_Teatime,
    [MOVE_OCTOLOCK            - 1] = gMoveDescription_Octolock,
    [MOVE_BOLT_BEAK           - 1] = gMoveDescription_BoltBeak,
    [MOVE_FISHIOUS_REND       - 1] = gMoveDescription_FishiousRend,
    [MOVE_COURT_CHANGE        - 1] = gMoveDescription_CourtChange,
    [MOVE_CLANGOROUS_SOUL     - 1] = gMoveDescription_ClangorousSoul,
    [MOVE_BODY_PRESS          - 1] = gMoveDescription_BodyPress,
    [MOVE_DECORATE            - 1] = gMoveDescription_Decorate,
    [MOVE_DRUM_BEATING        - 1] = gMoveDescription_DrumBeating,
    [MOVE_SNAP_TRAP           - 1] = gMoveDescription_SnapTrap,
    [MOVE_PYRO_BALL           - 1] = gMoveDescription_PyroBall,
    [MOVE_BEHEMOTH_BLADE      - 1] = gMoveDescription_BehemothBlade,
    [MOVE_BEHEMOTH_BASH       - 1] = gMoveDescription_BehemothBash,
    [MOVE_AURA_WHEEL          - 1] = gMoveDescription_AuraWheel,
    [MOVE_BREAKING_SWIPE      - 1] = gMoveDescription_BreakingSwipe,
    [MOVE_BRANCH_POKE         - 1] = gMoveDescription_BranchPoke,
    [MOVE_OVERDRIVE           - 1] = gMoveDescription_Overdrive,
    [MOVE_APPLE_ACID          - 1] = gMoveDescription_AppleAcid,
    [MOVE_GRAV_APPLE          - 1] = gMoveDescription_GravApple,
    [MOVE_SPIRIT_BREAK        - 1] = gMoveDescription_SpiritBreak,
    [MOVE_STRANGE_STEAM       - 1] = gMoveDescription_StrangeSteam,
    [MOVE_LIFE_DEW            - 1] = gMoveDescription_LifeDew,
    [MOVE_OBSTRUCT            - 1] = gMoveDescription_Obstruct,
    [MOVE_FALSE_SURRENDER     - 1] = gMoveDescription_FalseSurrender,
    [MOVE_METEOR_ASSAULT      - 1] = gMoveDescription_MeteorAssault,
    [MOVE_ETERNABEAM          - 1] = gMoveDescription_Eternabeam,
    [MOVE_STEEL_BEAM          - 1] = gMoveDescription_SteelBeam,
    [MOVE_EXPANDING_FORCE     - 1] = gMoveDescription_ExpandingForce,
    [MOVE_STEEL_ROLLER        - 1] = gMoveDescription_SteelRoller,
    [MOVE_SCALE_SHOT          - 1] = gMoveDescription_ScaleShot,
    [MOVE_METEOR_BEAM         - 1] = gMoveDescription_MeteorBeam,
    [MOVE_SHELL_SIDE_ARM      - 1] = gMoveDescription_ShellSideArm,
    [MOVE_MISTY_EXPLOSION     - 1] = gMoveDescription_MistyExplosion,
    [MOVE_GRASSY_GLIDE        - 1] = gMoveDescription_GrassyGlide,
    [MOVE_RISING_VOLTAGE      - 1] = gMoveDescription_RisingVoltage,
    [MOVE_TERRAIN_PULSE       - 1] = gMoveDescription_TerrainPulse,
    [MOVE_SKITTER_SMACK       - 1] = gMoveDescription_SkitterSmack,
    [MOVE_BURNING_JEALOUSY    - 1] = gMoveDescription_BurningJealousy,
    [MOVE_LASH_OUT            - 1] = gMoveDescription_LashOut,
    [MOVE_POLTERGEIST         - 1] = gMoveDescription_Poltergeist,
    [MOVE_CORROSIVE_GAS       - 1] = gMoveDescription_CorrosiveGas,
    [MOVE_COACHING            - 1] = gMoveDescription_Coaching,
    [MOVE_FLIP_TURN           - 1] = gMoveDescription_FlipTurn,
    [MOVE_TRIPLE_AXEL         - 1] = gMoveDescription_TripleAxel,
    [MOVE_DUAL_WINGBEAT       - 1] = gMoveDescription_DualWingbeat,
    [MOVE_SCORCHING_SANDS     - 1] = gMoveDescription_ScorchingSands,
    [MOVE_JUNGLE_HEALING      - 1] = gMoveDescription_JungleHealing,
    [MOVE_WICKED_BLOW         - 1] = gMoveDescription_WickedBlow,
    [MOVE_SURGING_STRIKES     - 1] = gMoveDescription_SurgingStrikes,
    [MOVE_THUNDER_CAGE        - 1] = gMoveDescription_ThunderCage,
    [MOVE_DRAGON_ENERGY       - 1] = gMoveDescription_DragonEnergy,
    [MOVE_FREEZING_GLARE      - 1] = gMoveDescription_FreezingGlare,
    [MOVE_FIERY_WRATH         - 1] = gMoveDescription_FieryWrath,
    [MOVE_THUNDEROUS_KICK     - 1] = gMoveDescription_ThunderousKick,
    [MOVE_GLACIAL_LANCE       - 1] = gMoveDescription_GlacialLance,
    [MOVE_ASTRAL_BARRAGE      - 1] = gMoveDescription_AstralBarrage,
    [MOVE_EERIE_SPELL         - 1] = gMoveDescription_EerieSpell,
    [MOVE_DIRE_CLAW           - 1] = gMoveDescription_DireClaw,
    [MOVE_PSYSHIELD_BASH      - 1] = gMoveDescription_PsyshieldBash,
    [MOVE_POWER_SHIFT         - 1] = gMoveDescription_PowerShift,
    [MOVE_STONE_AXE           - 1] = gMoveDescription_StoneAxe,
    [MOVE_SPRINGTIDE_STORM    - 1] = gMoveDescription_SpringtideStorm,
    [MOVE_MYSTICAL_POWER      - 1] = gMoveDescription_MysticalPower,
    [MOVE_RAGING_FURY         - 1] = gMoveDescription_RagingFury,
    [MOVE_WAVE_CRASH          - 1] = gMoveDescription_WaveCrash,
    [MOVE_CHLOROBLAST         - 1] = gMoveDescription_Chloroblast,
    [MOVE_MOUNTAIN_GALE       - 1] = gMoveDescription_MountainGale,
    [MOVE_VICTORY_DANCE       - 1] = gMoveDescription_VictoryDance,
    [MOVE_HEADLONG_RUSH       - 1] = gMoveDescription_HeadlongRush,
    [MOVE_BARB_BARRAGE        - 1] = gMoveDescription_BarbBarrage,
    [MOVE_ESPER_WING          - 1] = gMoveDescription_EsperWing,
    [MOVE_BITTER_MALICE       - 1] = gMoveDescription_BitterMalice,
    [MOVE_SHELTER             - 1] = gMoveDescription_Shelter,
    [MOVE_TRIPLE_ARROWS       - 1] = gMoveDescription_TripleArrows,
    [MOVE_INFERNAL_PARADE     - 1] = gMoveDescription_InfernalParade,
    [MOVE_CEASELESS_EDGE      - 1] = gMoveDescription_CeaselessEdge,
    [MOVE_BLEAKWIND_STORM     - 1] = gMoveDescription_BleakwindStorm,
    [MOVE_WILDBOLT_STORM      - 1] = gMoveDescription_WildboltStorm,
    [MOVE_SANDSEAR_STORM      - 1] = gMoveDescription_SandsearStorm,
    [MOVE_LUNAR_BLESSING      - 1] = gMoveDescription_LunarBlessing,
    [MOVE_TAKE_HEART          - 1] = gMoveDescription_TakeHeart,
    [MOVE_TERA_BLAST          - 1] = gMoveDescription_TeraBlast,
    [MOVE_SILK_TRAP           - 1] = gMoveDescription_SilkTrap,
    [MOVE_AXE_KICK            - 1] = gMoveDescription_AxeKick,
    [MOVE_LAST_RESPECTS       - 1] = gMoveDescription_LastRespects,
    [MOVE_LUMINA_CRASH        - 1] = gMoveDescription_LuminaCrash,
    [MOVE_ORDER_UP            - 1] = gMoveDescription_OrderUp,
    [MOVE_JET_PUNCH           - 1] = gMoveDescription_JetPunch,
    [MOVE_SPICY_EXTRACT       - 1] = gMoveDescription_SpicyExtract,
    [MOVE_SPIN_OUT            - 1] = gMoveDescription_SpinOut,
    [MOVE_POPULATION_BOMB     - 1] = gMoveDescription_PopulationBomb,
    [MOVE_ICE_SPINNER         - 1] = gMoveDescription_IceSpinner,
    [MOVE_GLAIVE_RUSH         - 1] = gMoveDescription_GlaiveRush,
    [MOVE_REVIVAL_BLESSING    - 1] = gMoveDescription_RevivalBlessing,
    [MOVE_SALT_CURE           - 1] = gMoveDescription_SaltCure,
    [MOVE_TRIPLE_DIVE         - 1] = gMoveDescription_TripleDive,
    [MOVE_MORTAL_SPIN         - 1] = gMoveDescription_MortalSpin,
    [MOVE_DOODLE              - 1] = gMoveDescription_Doodle,
    [MOVE_FILLET_AWAY         - 1] = gMoveDescription_FilletAway,
    [MOVE_KOWTOW_CLEAVE       - 1] = gMoveDescription_KowtowCleave,
    [MOVE_FLOWER_TRICK        - 1] = gMoveDescription_FlowerTrick,
    [MOVE_TORCH_SONG          - 1] = gMoveDescription_TorchSong,
    [MOVE_AQUA_STEP           - 1] = gMoveDescription_AquaStep,
    [MOVE_RAGING_BULL         - 1] = gMoveDescription_RagingBull,
    [MOVE_MAKE_IT_RAIN        - 1] = gMoveDescription_MakeItRain,
    [MOVE_RUINATION           - 1] = gMoveDescription_Ruination,
    [MOVE_COLLISION_COURSE    - 1] = gMoveDescription_CollisionCourse,
    [MOVE_ELECTRO_DRIFT       - 1] = gMoveDescription_ElectroDrift,
    [MOVE_SHED_TAIL           - 1] = gMoveDescription_ShedTail,
    [MOVE_CHILLY_RECEPTION    - 1] = gMoveDescription_ChillyReception,
    [MOVE_TIDY_UP             - 1] = gMoveDescription_TidyUp,
    [MOVE_SNOWSCAPE           - 1] = gMoveDescription_Snowscape,
    [MOVE_POUNCE              - 1] = gMoveDescription_Pounce,
    [MOVE_TRAILBLAZE          - 1] = gMoveDescription_Trailblaze,
    [MOVE_CHILLING_WATER      - 1] = gMoveDescription_ChillingWater,
    [MOVE_HYPER_DRILL         - 1] = gMoveDescription_HyperDrill,
    [MOVE_TWIN_BEAM           - 1] = gMoveDescription_TwinBeam,
    [MOVE_RAGE_FIST           - 1] = gMoveDescription_RageFist,
    [MOVE_ARMOR_CANNON        - 1] = gMoveDescription_ArmorCannon,
    [MOVE_BITTER_BLADE        - 1] = gMoveDescription_BitterBlade,
    [MOVE_DOUBLE_SHOCK        - 1] = gMoveDescription_DoubleShock,
    [MOVE_GIGATON_HAMMER      - 1] = gMoveDescription_GigatonHammer,
    [MOVE_COMEUPPANCE         - 1] = gMoveDescription_Comeuppance,
    [MOVE_AQUA_CUTTER         - 1] = gMoveDescription_AquaCutter,
    [MOVE_BLAZING_TORQUE      - 1] = gMoveDescription_BlazingTorque,
    [MOVE_WICKED_TORQUE       - 1] = gMoveDescription_WickedTorque,
    [MOVE_NOXIOUS_TORQUE      - 1] = gMoveDescription_NoxiousTorque,
    [MOVE_COMBAT_TORQUE       - 1] = gMoveDescription_CombatTorque,
    [MOVE_MAGICAL_TORQUE      - 1] = gMoveDescription_MagicalTorque,
    [MOVE_PSYBLADE            - 1] = gMoveDescription_Psyblade,
    [MOVE_HYDRO_STEAM         - 1] = gMoveDescription_HydroSteam,
    [MOVE_BLOOD_MOON          - 1] = gMoveDescription_BloodMoon,
    [MOVE_MATCHA_GOTCHA       - 1] = gMoveDescription_MatchaGotcha,
    [MOVE_SYRUP_BOMB          - 1] = gMoveDescription_SyrupBomb,
    [MOVE_IVY_CUDGEL          - 1] = gMoveDescription_IvyCudgel,
    [MOVE_ELECTRO_SHOT        - 1] = gMoveDescription_ElectroShot,
    [MOVE_TERA_STARSTORM      - 1] = gMoveDescription_TeraStarstorm,
    [MOVE_FICKLE_BEAM         - 1] = gMoveDescription_FickleBeam,
    [MOVE_BURNING_BULWARK     - 1] = gMoveDescription_BurningBulwark,
    [MOVE_THUNDERCLAP         - 1] = gMoveDescription_Thunderclap,
    [MOVE_MIGHTY_CLEAVE       - 1] = gMoveDescription_MightyCleave,
    [MOVE_TACHYON_CUTTER      - 1] = gMoveDescription_TachyonCutter,
    [MOVE_HARD_PRESS          - 1] = gMoveDescription_HardPress,
    [MOVE_DRAGON_CHEER        - 1] = gMoveDescription_DragonCheer,
    [MOVE_ALLURING_VOICE      - 1] = gMoveDescription_AlluringVoice,
    [MOVE_TEMPER_FLARE        - 1] = gMoveDescription_TemperFlare,
    [MOVE_SUPERCELL_SLAM      - 1] = gMoveDescription_SupercellSlam,
    [MOVE_PSYCHIC_NOISE       - 1] = gMoveDescription_PsychicNoise,
    [MOVE_UPPER_HAND          - 1] = gMoveDescription_UpperHand,
    [MOVE_MALIGNANT_CHAIN     - 1] = gMoveDescription_MalignantChain
};

// ---------------------------------------------------------------------------
// Section 4: Move Battle Stats
// ---------------------------------------------------------------------------

const struct BattleMove gBattleMoves[MOVES_COUNT] =
{
    [MOVE_POUND] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_KARATE_CHOP] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .criticalHitStage = 1,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_DOUBLE_SLAP] =
    {
        .effect = EFFECT_MULTI_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_COMET_PUNCH] =
    {
        .effect = EFFECT_MULTI_HIT,
        .power = 18,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_MEGA_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_PAY_DAY] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PAYDAY,
            .chance = 0,
        }),
    },

    [MOVE_FIRE_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
    },

    [MOVE_ICE_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_THUNDER_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 10,
        }),
    },

    [MOVE_SCRATCH] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_VISE_GRIP] =
    {
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_GUILLOTINE] =
    {
        .effect = EFFECT_OHKO,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 30,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_RAZOR_WIND] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .windMove = TRUE,
        .criticalHitStage = 1,
        .category = SPLIT_SPECIAL,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_SWORDS_DANCE] =
    {
        .effect = EFFECT_ATTACK_UP_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .danceMove = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_CUT] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 95,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_GUST] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .windMove = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_WING_ATTACK] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_WHIRLWIND] =
    {
        .effect = EFFECT_ROAR,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = -6,
        .ignoresProtect = TRUE,
        .magicCoatAffected = TRUE,
        .windMove = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_FLY] =
    {
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = 90,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .gravityBanned = TRUE,
    },

    [MOVE_BIND] =
    {
        .effect = EFFECT_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .chance = 0,
        }),
    },

    [MOVE_SLAM] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .skyBattleBanned = TRUE,
    },

    [MOVE_VINE_WHIP] =
    {
        .effect = EFFECT_HIT,
        .power = 45,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_STOMP] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .skyBattleBanned = TRUE,
    },

    [MOVE_DOUBLE_KICK] =
    {
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .strikeCount = 2,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_MEGA_KICK] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_JUMP_KICK] =
    {
        .effect = EFFECT_RECOIL_IF_MISS,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .gravityBanned = TRUE,
    },

    [MOVE_ROLLING_KICK] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
    },

    [MOVE_SAND_ATTACK] =
    {
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_HEADBUTT] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
    },

    [MOVE_HORN_ATTACK] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_FURY_ATTACK] =
    {
        .effect = EFFECT_MULTI_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_HORN_DRILL] =
    {
        .effect = EFFECT_OHKO,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 30,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_TACKLE] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_BODY_SLAM] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .skyBattleBanned = TRUE,
    },

    [MOVE_WRAP] =
    {
        .effect = EFFECT_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .chance = 0,
        }),
    },

    [MOVE_TAKE_DOWN] =
    {
        .effect = EFFECT_RECOIL,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .recoil = 25,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_THRASH] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_THRASH,
            .self = TRUE,
            .chance = 0,
        }),
        .instructBanned = TRUE,
    },

    [MOVE_DOUBLE_EDGE] =
    {
        .effect = EFFECT_RECOIL,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .recoil = 33,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_TAIL_WHIP] =
    {
        .effect = EFFECT_DEFENSE_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_POISON_STING] =
    {
        .effect = EFFECT_HIT,
        .power = 15,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),
    },

    [MOVE_TWINEEDLE] =
    {
        .effect = EFFECT_HIT,
        .power = 25,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .strikeCount = 2,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 20,
        }),
    },

    [MOVE_PIN_MISSILE] =
    {
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_BUG,
        .accuracy = 95,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_LEER] =
    {
        .effect = EFFECT_DEFENSE_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_BITE] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
    },

    [MOVE_GROWL] =
    {
        .effect = EFFECT_ATTACK_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_ROAR] =
    {
        .effect = EFFECT_ROAR,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = -6,
        .ignoresProtect = TRUE,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SING] =
    {
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 55,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SUPERSONIC] =
    {
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 55,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SONIC_BOOM] =
    {
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_DISABLE] =
    {
        .effect = EFFECT_DISABLE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_ACID] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_EMBER] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
    },

    [MOVE_FLAMETHROWER] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
    },

    [MOVE_MIST] =
    {
        .effect = EFFECT_MIST,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_WATER_GUN] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_HYDRO_PUMP] =
    {
        .effect = EFFECT_HIT,
        .power = 110,
        .type = TYPE_WATER,
        .accuracy = 80,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_SURF] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .skyBattleBanned = TRUE,
    },

    [MOVE_ICE_BEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_BLIZZARD] =
    {
        .effect = EFFECT_HIT,
        .power = 110,
        .type = TYPE_ICE,
        .accuracy = 70,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .windMove = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_PSYBEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 10,
        }),
    },

    [MOVE_BUBBLE_BEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 10,
        }),
    },

    [MOVE_AURORA_BEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 10,
        }),
    },

    [MOVE_HYPER_BEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
            .chance = 0,
        }),
    },

    [MOVE_PECK] =
    {
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_DRILL_PECK] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SUBMISSION] =
    {
        .effect = EFFECT_RECOIL,
        .power = 80,
        .type = TYPE_FIGHTING,
        .accuracy = 80,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .recoil = 25,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_LOW_KICK] =
    {
        .effect = EFFECT_LOW_KICK,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_COUNTER] =
    {
        .effect = EFFECT_COUNTER,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = -5,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .meFirstBanned = TRUE,
    },

    [MOVE_SEISMIC_TOSS] =
    {
        .effect = EFFECT_LEVEL_DAMAGE,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .skyBattleBanned = TRUE,
    },

    [MOVE_STRENGTH] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_ABSORB] =
    {
        .effect = EFFECT_ABSORB,
        .power = 20,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .healingMove = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_MEGA_DRAIN] =
    {
        .effect = EFFECT_ABSORB,
        .power = 40,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .healingMove = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_LEECH_SEED] =
    {
        .effect = EFFECT_LEECH_SEED,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_GROWTH] =
    {
        .effect = EFFECT_GROWTH,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_RAZOR_LEAF] =
    {
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_GRASS,
        .accuracy = 95,
        .pp = 25,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .slicingMove = TRUE,
        .criticalHitStage = 1,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SOLAR_BEAM] =
    {
        .effect = EFFECT_SOLAR_BEAM,
        .power = 120,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_POISON_POWDER] =
    {
        .effect = EFFECT_POISON,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 75,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_STUN_SPORE] =
    {
        .effect = EFFECT_PARALYZE,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 75,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SLEEP_POWDER] =
    {
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 75,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_PETAL_DANCE] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .makesContact = TRUE,
        .danceMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_THRASH,
            .self = TRUE,
            .chance = 0,
        }),
        .instructBanned = TRUE,
    },

    [MOVE_STRING_SHOT] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 95,
        .pp = 40,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_DRAGON_RAGE] =
    {
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_FIRE_SPIN] =
    {
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_FIRE,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .chance = 0,
        }),
    },

    [MOVE_THUNDER_SHOCK] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 10,
        }),
    },

    [MOVE_THUNDERBOLT] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 10,
        }),
    },

    [MOVE_THUNDER_WAVE] =
    {
        .effect = EFFECT_PARALYZE,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_THUNDER] =
    {
        .effect = EFFECT_THUNDER,
        .power = 110,
        .type = TYPE_ELECTRIC,
        .accuracy = 70,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
    },

    [MOVE_ROCK_THROW] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_EARTHQUAKE] =
    {
        .effect = EFFECT_EARTHQUAKE,
        .power = 100,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .skyBattleBanned = TRUE,
    },

    [MOVE_FISSURE] =
    {
        .effect = EFFECT_OHKO,
        .power = 1,
        .type = TYPE_GROUND,
        .accuracy = 30,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .skyBattleBanned = TRUE,
    },

    [MOVE_DIG] =
    {
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = 80,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .skyBattleBanned = TRUE,
    },

    [MOVE_TOXIC] =
    {
        .effect = EFFECT_TOXIC,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_CONFUSION] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 10,
        }),
    },

    [MOVE_PSYCHIC] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 10,
        }),
    },

    [MOVE_HYPNOSIS] =
    {
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 60,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_MEDITATE] =
    {
        .effect = EFFECT_ATTACK_UP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_AGILITY] =
    {
        .effect = EFFECT_SPEED_UP_2,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_QUICK_ATTACK] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_RAGE] =
    {
        .effect = EFFECT_RAGE,
        .power = 20,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_TELEPORT] =
    {
        .effect = EFFECT_TELEPORT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = -6,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_NIGHT_SHADE] =
    {
        .effect = EFFECT_LEVEL_DAMAGE,
        .power = 1,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_MIMIC] =
    {
        .effect = EFFECT_MIMIC,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
    },

    [MOVE_SCREECH] =
    {
        .effect = EFFECT_DEFENSE_DOWN_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_DOUBLE_TEAM] =
    {
        .effect = EFFECT_EVASION_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_RECOVER] =
    {
        .effect = EFFECT_RESTORE_HP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_HARDEN] =
    {
        .effect = EFFECT_DEFENSE_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_MINIMIZE] =
    {
        .effect = EFFECT_MINIMIZE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SMOKESCREEN] =
    {
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_CONFUSE_RAY] =
    {
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_WITHDRAW] =
    {
        .effect = EFFECT_DEFENSE_UP,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_DEFENSE_CURL] =
    {
        .effect = EFFECT_DEFENSE_CURL,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_BARRIER] =
    {
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_LIGHT_SCREEN] =
    {
        .effect = EFFECT_LIGHT_SCREEN,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_HAZE] =
    {
        .effect = EFFECT_HAZE,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_REFLECT] =
    {
        .effect = EFFECT_REFLECT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_FOCUS_ENERGY] =
    {
        .effect = EFFECT_FOCUS_ENERGY,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_BIDE] =
    {
        .effect = EFFECT_BIDE,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .makesContact = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_PHYSICAL,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_METRONOME] =
    {
        .effect = EFFECT_METRONOME,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_MIRROR_MOVE] =
    {
        .effect = EFFECT_MIRROR_MOVE,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
    },

    [MOVE_SELF_DESTRUCT] =
    {
        .effect = EFFECT_EXPLOSION,
        .power = 200,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .parentalBondBanned = TRUE,
        .dampBanned = TRUE,
    },

    [MOVE_EGG_BOMB] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_LICK] =
    {
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
    },

    [MOVE_SMOG] =
    {
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_POISON,
        .accuracy = 70,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 40,
        }),
    },

    [MOVE_SLUDGE] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),
    },

    [MOVE_BONE_CLUB] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_GROUND,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),
    },

    [MOVE_FIRE_BLAST] =
    {
        .effect = EFFECT_HIT,
        .power = 110,
        .type = TYPE_FIRE,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
    },

    [MOVE_WATERFALL] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),
    },

    [MOVE_CLAMP] =
    {
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_WATER,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .chance = 0,
        }),
    },

    [MOVE_SWIFT] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_SKULL_BASH] =
    {
        .effect = EFFECT_HIT,
        .power = 130,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_PLUS_1,
            .self = TRUE,
            .chance = 0,
        }),
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_SPIKE_CANNON] =
    {
        .effect = EFFECT_MULTI_HIT,
        .power = 20,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_CONSTRICT] =
    {
        .effect = EFFECT_HIT,
        .power = 10,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 10,
        }),
    },

    [MOVE_AMNESIA] =
    {
        .effect = EFFECT_SPECIAL_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_KINESIS] =
    {
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 80,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SOFT_BOILED] =
    {
        .effect = EFFECT_SOFTBOILED,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_HIGH_JUMP_KICK] =
    {
        .effect = EFFECT_RECOIL_IF_MISS,
        .power = 130,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .gravityBanned = TRUE,
    },

    [MOVE_GLARE] =
    {
        .effect = EFFECT_PARALYZE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_DREAM_EATER] =
    {
        .effect = EFFECT_DREAM_EATER,
        .power = 100,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .healingMove = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_POISON_GAS] =
    {
        .effect = EFFECT_POISON,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 90,
        .pp = 40,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_BARRAGE] =
    {
        .effect = EFFECT_MULTI_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_LEECH_LIFE] =
    {
        .effect = EFFECT_ABSORB,
        .power = 80,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .healingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_LOVELY_KISS] =
    {
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SKY_ATTACK] =
    {
        .effect = EFFECT_HIT,
        .power = 140,
        .type = TYPE_FLYING,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_TRANSFORM] =
    {
        .effect = EFFECT_TRANSFORM,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
    },

    [MOVE_BUBBLE] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 10,
        }),
    },

    [MOVE_DIZZY_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 20,
        }),
    },

    [MOVE_SPORE] =
    {
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_FLASH] =
    {
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_PSYWAVE] =
    {
        .effect = EFFECT_PSYWAVE,
        .power = 1,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_SPLASH] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .gravityBanned = TRUE,
    },

    [MOVE_ACID_ARMOR] =
    {
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_CRABHAMMER] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_WATER,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .criticalHitStage = 1,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_EXPLOSION] =
    {
        .effect = EFFECT_EXPLOSION,
        .power = 250,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .parentalBondBanned = TRUE,
        .dampBanned = TRUE,
    },

    [MOVE_FURY_SWIPES] =
    {
        .effect = EFFECT_MULTI_HIT,
        .power = 18,
        .type = TYPE_NORMAL,
        .accuracy = 80,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_BONEMERANG] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_GROUND,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .strikeCount = 2,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_REST] =
    {
        .effect = EFFECT_REST,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_ROCK_SLIDE] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
    },

    [MOVE_HYPER_FANG] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),
    },

    [MOVE_SHARPEN] =
    {
        .effect = EFFECT_ATTACK_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_CONVERSION] =
    {
        .effect = EFFECT_CONVERSION,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_TRI_ATTACK] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_TRI_ATTACK,
            .chance = 20,
        }),
    },

    [MOVE_SUPER_FANG] =
    {
        .effect = EFFECT_SUPER_FANG,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SLASH] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .criticalHitStage = 1,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SUBSTITUTE] =
    {
        .effect = EFFECT_SUBSTITUTE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .skyBattleBanned = TRUE,
    },

    [MOVE_STRUGGLE] =
    {
        .effect = EFFECT_STRUGGLE,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECOIL_HP_25,
            .self = TRUE,
        }),
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .meFirstBanned = TRUE,
        .sketchBanned = TRUE,
    },

    [MOVE_SKETCH] =
    {
        .effect = EFFECT_SKETCH,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .sketchBanned = TRUE,
    },

    [MOVE_TRIPLE_KICK] =
    {
        .effect = EFFECT_TRIPLE_KICK,
        .power = 10,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .strikeCount = 3,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_THIEF] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_STEAL_ITEM,
            .chance = 0,
        }),
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .meFirstBanned = TRUE,
    },

    [MOVE_SPIDER_WEB] =
    {
        .effect = EFFECT_MEAN_LOOK,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_MIND_READER] =
    {
        .effect = EFFECT_LOCK_ON,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_STATUS,
    },

    [MOVE_NIGHTMARE] =
    {
        .effect = EFFECT_NIGHTMARE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_STATUS,
    },

    [MOVE_FLAME_WHEEL] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .thawsUser = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
    },

    [MOVE_SNORE] =
    {
        .effect = EFFECT_SNORE,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_CURSE] =
    {
        .effect = EFFECT_CURSE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_FLAIL] =
    {
        .effect = EFFECT_FLAIL,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_CONVERSION_2] =
    {
        .effect = EFFECT_CONVERSION_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_AEROBLAST] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .windMove = TRUE,
        .criticalHitStage = 1,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_COTTON_SPORE] =
    {
        .effect = EFFECT_SPEED_DOWN_2,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_REVERSAL] =
    {
        .effect = EFFECT_FLAIL,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SPITE] =
    {
        .effect = EFFECT_SPITE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_POWDER_SNOW] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_PROTECT] =
    {
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
    },

    [MOVE_MACH_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SCARY_FACE] =
    {
        .effect = EFFECT_SPEED_DOWN_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_FEINT_ATTACK] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SWEET_KISS] =
    {
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 75,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_BELLY_DRUM] =
    {
        .effect = EFFECT_BELLY_DRUM,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SLUDGE_BOMB] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),
    },

    [MOVE_MUD_SLAP] =
    {
        .effect = EFFECT_HIT,
        .power = 20,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 100,
        }),
    },

    [MOVE_OCTAZOOKA] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_WATER,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 50,
        }),
    },

    [MOVE_SPIKES] =
    {
        .effect = EFFECT_SPIKES,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_OPPONENTS_FIELD,
        .priority = 0,
        .ignoresProtect = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .skyBattleBanned = TRUE,
        .forcePressure = TRUE,
    },

    [MOVE_ZAP_CANNON] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_ELECTRIC,
        .accuracy = 50,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 100,
        }),
    },

    [MOVE_FORESIGHT] =
    {
        .effect = EFFECT_FORESIGHT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_DESTINY_BOND] =
    {
        .effect = EFFECT_DESTINY_BOND,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
    },

    [MOVE_PERISH_SONG] =
    {
        .effect = EFFECT_PERISH_SONG,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_ICY_WIND] =
    {
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_ICE,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .windMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
    },

    [MOVE_DETECT] =
    {
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
    },

    [MOVE_BONE_RUSH] =
    {
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_GROUND,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_LOCK_ON] =
    {
        .effect = EFFECT_LOCK_ON,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_STATUS,
    },

    [MOVE_OUTRAGE] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_THRASH,
            .self = TRUE,
            .chance = 0,
        }),
        .instructBanned = TRUE,
    },

    [MOVE_SANDSTORM] =
    {
        .effect = EFFECT_SANDSTORM,
        .power = 0,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .windMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_GIGA_DRAIN] =
    {
        .effect = EFFECT_ABSORB,
        .power = 75,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .healingMove = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_ENDURE] =
    {
        .effect = EFFECT_ENDURE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
    },

    [MOVE_CHARM] =
    {
        .effect = EFFECT_ATTACK_DOWN_2,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_ROLLOUT] =
    {
        .effect = EFFECT_ROLLOUT,
        .power = 30,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .instructBanned = TRUE,
        .parentalBondBanned = TRUE,
    },

    [MOVE_FALSE_SWIPE] =
    {
        .effect = EFFECT_FALSE_SWIPE,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SWAGGER] =
    {
        .effect = EFFECT_SWAGGER,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_MILK_DRINK] =
    {
        .effect = EFFECT_SOFTBOILED,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SPARK] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
    },

    [MOVE_FURY_CUTTER] =
    {
        .effect = EFFECT_FURY_CUTTER,
        .power = 40,
        .type = TYPE_BUG,
        .accuracy = 95,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_STEEL_WING] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_STEEL,
        .accuracy = 90,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_PLUS_1,
            .self = TRUE,
            .chance = 10,
        }),
    },

    [MOVE_MEAN_LOOK] =
    {
        .effect = EFFECT_MEAN_LOOK,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_ATTRACT] =
    {
        .effect = EFFECT_ATTRACT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SLEEP_TALK] =
    {
        .effect = EFFECT_SLEEP_TALK,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_HEAL_BELL] =
    {
        .effect = EFFECT_HEAL_BELL,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_RETURN] =
    {
        .effect = EFFECT_RETURN,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_PRESENT] =
    {
        .effect = EFFECT_PRESENT,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_FRUSTRATION] =
    {
        .effect = EFFECT_FRUSTRATION,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SAFEGUARD] =
    {
        .effect = EFFECT_SAFEGUARD,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 25,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_PAIN_SPLIT] =
    {
        .effect = EFFECT_PAIN_SPLIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_STATUS,
    },

    [MOVE_SACRED_FIRE] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIRE,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .thawsUser = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 50,
        }),
    },

    [MOVE_MAGNITUDE] =
    {
        .effect = EFFECT_MAGNITUDE,
        .power = 1,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .skyBattleBanned = TRUE,
    },

    [MOVE_DYNAMIC_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 50,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 100,
        }),
    },

    [MOVE_MEGAHORN] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_BUG,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_DRAGON_BREATH] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
    },

    [MOVE_BATON_PASS] =
    {
        .effect = EFFECT_BATON_PASS,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_ENCORE] =
    {
        .effect = EFFECT_ENCORE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
        .encoreBanned = TRUE,
    },

    [MOVE_PURSUIT] =
    {
        .effect = EFFECT_PURSUIT,
        .power = 40,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_RAPID_SPIN] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SWEET_SCENT] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_IRON_TAIL] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 75,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 30,
        }),
    },

    [MOVE_METAL_CLAW] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_STEEL,
        .accuracy = 95,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_PLUS_1,
            .self = TRUE,
            .chance = 10,
        }),
    },

    [MOVE_VITAL_THROW] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = -1,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_MORNING_SUN] =
    {
        .effect = EFFECT_MORNING_SUN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SYNTHESIS] =
    {
        .effect = EFFECT_SYNTHESIS,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_MOONLIGHT] =
    {
        .effect = EFFECT_MOONLIGHT,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_HIDDEN_POWER] =
    {
        .effect = EFFECT_HIDDEN_POWER,
        .power = 60,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_CROSS_CHOP] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 80,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .criticalHitStage = 1,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_TWISTER] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .windMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),
    },

    [MOVE_RAIN_DANCE] =
    {
        .effect = EFFECT_RAIN_DANCE,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SUNNY_DAY] =
    {
        .effect = EFFECT_SUNNY_DAY,
        .power = 0,
        .type = TYPE_FIRE,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_CRUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 0,
        }),
    },

    [MOVE_MIRROR_COAT] =
    {
        .effect = EFFECT_MIRROR_COAT,
        .power = 1,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = -5,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        .assistBanned = TRUE,
        .meFirstBanned = TRUE,
    },

    [MOVE_PSYCH_UP] =
    {
        .effect = EFFECT_PSYCH_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_EXTREME_SPEED] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 2,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_ANCIENT_POWER] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ALL_STATS_UP,
            .self = TRUE,
            .chance = 10,
        }),
    },

    [MOVE_SHADOW_BALL] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 20,
        }),
    },

    [MOVE_FUTURE_SIGHT] =
    {
        .effect = EFFECT_FUTURE_SIGHT,
        .power = 120,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_ROCK_SMASH] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 50,
        }),
    },

    [MOVE_WHIRLPOOL] =
    {
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_WATER,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .chance = 0,
        }),
    },

    [MOVE_BEAT_UP] =
    {
        .effect = EFFECT_BEAT_UP,
        .power = 1,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_FAKE_OUT] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 3,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 100,
        }),
    },

    [MOVE_UPROAR] =
    {
        .effect = EFFECT_UPROAR,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_UPROAR,
            .self = TRUE,
            .chance = 0,
        }),
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_STOCKPILE] =
    {
        .effect = EFFECT_STOCKPILE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SPIT_UP] =
    {
        .effect = EFFECT_SPIT_UP,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_SWALLOW] =
    {
        .effect = EFFECT_SWALLOW,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_HEAT_WAVE] =
    {
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .windMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
    },

    [MOVE_HAIL] =
    {
        .effect = EFFECT_HAIL,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_TORMENT] =
    {
        .effect = EFFECT_TORMENT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_FLATTER] =
    {
        .effect = EFFECT_FLATTER,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_WILL_O_WISP] =
    {
        .effect = EFFECT_WILL_O_WISP,
        .power = 0,
        .type = TYPE_FIRE,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_MEMENTO] =
    {
        .effect = EFFECT_MEMENTO,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_STATUS,
    },

    [MOVE_FACADE] =
    {
        .effect = EFFECT_FACADE,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_FOCUS_PUNCH] =
    {
        .effect = EFFECT_FOCUS_PUNCH,
        .power = 150,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = -3,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .meFirstBanned = TRUE,
    },

    [MOVE_SMELLING_SALTS] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_FOLLOW_ME] =
    {
        .effect = EFFECT_FOLLOW_ME,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 2,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
    },

    [MOVE_NATURE_POWER] =
    {
        .effect = EFFECT_NATURE_POWER,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_CHARGE] =
    {
        .effect = EFFECT_CHARGE,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_TAUNT] =
    {
        .effect = EFFECT_TAUNT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_HELPING_HAND] =
    {
        .effect = EFFECT_HELPING_HAND,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_ALLY,
        .priority = 5,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
    },

    [MOVE_TRICK] =
    {
        .effect = EFFECT_TRICK,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
    },

    [MOVE_ROLE_PLAY] =
    {
        .effect = EFFECT_ROLE_PLAY,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_WISH] =
    {
        .effect = EFFECT_WISH,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_ASSIST] =
    {
        .effect = EFFECT_ASSIST,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
    },

    [MOVE_INGRAIN] =
    {
        .effect = EFFECT_INGRAIN,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .skyBattleBanned = TRUE,
    },

    [MOVE_SUPERPOWER] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_DEF_DOWN,
            .self = TRUE,
            .chance = 0,
        }),
    },

    [MOVE_MAGIC_COAT] =
    {
        .effect = EFFECT_MAGIC_COAT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 4,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_RECYCLE] =
    {
        .effect = EFFECT_RECYCLE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_REVENGE] =
    {
        .effect = EFFECT_REVENGE,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = -4,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_BRICK_BREAK] =
    {
        .effect = EFFECT_BRICK_BREAK,
        .power = 75,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_YAWN] =
    {
        .effect = EFFECT_YAWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_KNOCK_OFF] =
    {
        .effect = EFFECT_KNOCK_OFF,
        .power = 65,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_KNOCK_OFF,
            .chance = 0,
        }),
    },

    [MOVE_ENDEAVOR] =
    {
        .effect = EFFECT_ENDEAVOR,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .parentalBondBanned = TRUE,
    },

    [MOVE_ERUPTION] =
    {
        .effect = EFFECT_ERUPTION,
        .power = 150,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_SKILL_SWAP] =
    {
        .effect = EFFECT_SKILL_SWAP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_STATUS,
    },

    [MOVE_IMPRISON] =
    {
        .effect = EFFECT_IMPRISON,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .forcePressure = TRUE,
    },

    [MOVE_REFRESH] =
    {
        .effect = EFFECT_REFRESH,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_GRUDGE] =
    {
        .effect = EFFECT_GRUDGE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SNATCH] =
    {
        .effect = EFFECT_SNATCH,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 4,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .forcePressure = TRUE,
    },

    [MOVE_SECRET_POWER] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_DIVE] =
    {
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .skyBattleBanned = TRUE,
    },

    [MOVE_ARM_THRUST] =
    {
        .effect = EFFECT_MULTI_HIT,
        .power = 15,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_CAMOUFLAGE] =
    {
        .effect = EFFECT_CAMOUFLAGE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_TAIL_GLOW] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_LUSTER_PURGE] =
    {
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 50,
        }),
    },

    [MOVE_MIST_BALL] =
    {
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 50,
        }),
    },

    [MOVE_FEATHER_DANCE] =
    {
        .effect = EFFECT_ATTACK_DOWN_2,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .danceMove = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_TEETER_DANCE] =
    {
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .danceMove = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_BLAZE_KICK] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .criticalHitStage = 1,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
    },

    [MOVE_MUD_SPORT] =
    {
        .effect = EFFECT_MUD_SPORT,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .skyBattleBanned = TRUE,
    },

    [MOVE_ICE_BALL] =
    {
        .effect = EFFECT_ROLLOUT,
        .power = 30,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .ballisticMove = TRUE,
        .category = SPLIT_PHYSICAL,
        .instructBanned = TRUE,
        .parentalBondBanned = TRUE,
    },

    [MOVE_NEEDLE_ARM] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
    },

    [MOVE_SLACK_OFF] =
    {
        .effect = EFFECT_RESTORE_HP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_HYPER_VOICE] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_POISON_FANG] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_TOXIC,
            .chance = 0,
        }),
    },

    [MOVE_CRUSH_CLAW] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_NORMAL,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 50,
        }),
    },

    [MOVE_BLAST_BURN] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
            .chance = 0,
        }),
    },

    [MOVE_HYDRO_CANNON] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_WATER,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
            .chance = 0,
        }),
    },

    [MOVE_METEOR_MASH] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_STEEL,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_PLUS_1,
            .self = TRUE,
            .chance = 20,
        }),
    },

    [MOVE_ASTONISH] =
    {
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
    },

    [MOVE_WEATHER_BALL] =
    {
        .effect = EFFECT_WEATHER_BALL,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_AROMATHERAPY] =
    {
        .effect = EFFECT_HEAL_BELL,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_FAKE_TEARS] =
    {
        .effect = EFFECT_SPECIAL_DEFENSE_DOWN_2,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_AIR_CUTTER] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .pp = 25,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .slicingMove = TRUE,
        .windMove = TRUE,
        .criticalHitStage = 1,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_OVERHEAT] =
    {
        .effect = EFFECT_HIT,
        .power = 130,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_2,
            .self = TRUE,
            .chance = 0,
        }),
    },

    [MOVE_ODOR_SLEUTH] =
    {
        .effect = EFFECT_FORESIGHT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_ROCK_TOMB] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_ROCK,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
    },

    [MOVE_SILVER_WIND] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .windMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ALL_STATS_UP,
            .self = TRUE,
            .chance = 10,
        }),
    },

    [MOVE_METAL_SOUND] =
    {
        .effect = EFFECT_SPECIAL_DEFENSE_DOWN_2,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 85,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_GRASS_WHISTLE] =
    {
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 55,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_TICKLE] =
    {
        .effect = EFFECT_TICKLE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_COSMIC_POWER] =
    {
        .effect = EFFECT_COSMIC_POWER,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_WATER_SPOUT] =
    {
        .effect = EFFECT_ERUPTION,
        .power = 150,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_SIGNAL_BEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 10,
        }),
    },

    [MOVE_SHADOW_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_GHOST,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_EXTRASENSORY] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),
    },

    [MOVE_SKY_UPPERCUT] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SAND_TOMB] =
    {
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_GROUND,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .chance = 0,
        }),
    },

    [MOVE_SHEER_COLD] =
    {
        .effect = EFFECT_OHKO,
        .power = 1,
        .type = TYPE_ICE,
        .accuracy = 30,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_MUDDY_WATER] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_WATER,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 30,
        }),
        .skyBattleBanned = TRUE,
    },

    [MOVE_BULLET_SEED] =
    {
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_AERIAL_ACE] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_ICICLE_SPEAR] =
    {
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_IRON_DEFENSE] =
    {
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_BLOCK] =
    {
        .effect = EFFECT_MEAN_LOOK,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_HOWL] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_DRAGON_CLAW] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_FRENZY_PLANT] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
            .chance = 0,
        }),
        .skyBattleBanned = TRUE,
    },

    [MOVE_BULK_UP] =
    {
        .effect = EFFECT_BULK_UP,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_BOUNCE] =
    {
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = 85,
        .type = TYPE_FLYING,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .gravityBanned = TRUE,
    },

    [MOVE_MUD_SHOT] =
    {
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_GROUND,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
    },

    [MOVE_POISON_TAIL] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .criticalHitStage = 1,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 10,
        }),
    },

    [MOVE_COVET] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_STEAL_ITEM,
            .chance = 0,
        }),
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .meFirstBanned = TRUE,
    },

    [MOVE_VOLT_TACKLE] =
    {
        .effect = EFFECT_RECOIL,
        .power = 120,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .recoil = 33,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 10,
        }),
    },

    [MOVE_MAGICAL_LEAF] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_WATER_SPORT] =
    {
        .effect = EFFECT_WATER_SPORT,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .skyBattleBanned = TRUE,
    },

    [MOVE_CALM_MIND] =
    {
        .effect = EFFECT_CALM_MIND,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_LEAF_BLADE] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .criticalHitStage = 1,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_DRAGON_DANCE] =
    {
        .effect = EFFECT_DRAGON_DANCE,
        .power = 0,
        .type = TYPE_DRAGON,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .danceMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_ROCK_BLAST] =
    {
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SHOCK_WAVE] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_WATER_PULSE] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .pulseMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 20,
        }),
    },

    [MOVE_DOOM_DESIRE] =
    {
        .effect = EFFECT_FUTURE_SIGHT,
        .power = 140,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_PSYCHO_BOOST] =
    {
        .effect = EFFECT_HIT,
        .power = 140,
        .type = TYPE_PSYCHIC,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_2,
            .self = TRUE,
            .chance = 0,
        }),
    },

    [MOVE_ROOST] =
    {
        .effect = EFFECT_ROOST,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_GRAVITY] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .skyBattleBanned = TRUE,
    },

    [MOVE_MIRACLE_EYE] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_WAKE_UP_SLAP] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_HAMMER_ARM] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .self = TRUE,
            .chance = 0,
        }),
    },

    [MOVE_GYRO_BALL] =
    {
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .ballisticMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_HEALING_WISH] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_BRINE] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_NATURAL_GIFT] =
    {
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_FEINT] =
    {
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 2,
        .ignoresProtect = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
    },

    [MOVE_PLUCK] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_TAILWIND] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .windMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_ACUPRESSURE] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER | MOVE_TARGET_ALLY,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_METAL_BURST] =
    {
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .meFirstBanned = TRUE,
    },

    [MOVE_U_TURN] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_CLOSE_COMBAT] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_PAYBACK] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_ASSURANCE] =
    {
        .effect = EFFECT_ASSURANCE,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .makesContact = TRUE,
    },

    [MOVE_EMBARGO] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_FLING] =
    {
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .parentalBondBanned = TRUE,
    },

    [MOVE_PSYCHO_SHIFT] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_STATUS,
    },

    [MOVE_TRUMP_CARD] =
    {
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_HEAL_BLOCK] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_WRING_OUT] =
    {
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_POWER_TRICK] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_GASTRO_ACID] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_LUCKY_CHANT] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_ME_FIRST] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .meFirstBanned = TRUE,
    },

    [MOVE_COPYCAT] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_POWER_SWAP] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_STATUS,
    },

    [MOVE_GUARD_SWAP] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_STATUS,
    },

    [MOVE_PUNISHMENT] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_LAST_RESORT] =
    {
        .effect = EFFECT_HIT,
        .power = 140,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_WORRY_SEED] =
    {
        .effect = EFFECT_WORRY_SEED,
        .argument = ABILITY_INSOMNIA,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SUCKER_PUNCH] =
    {
        .effect = EFFECT_SUCKER_PUNCH,
        .power = 70,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = SPLIT_PHYSICAL,
        .makesContact = TRUE,
    },

    [MOVE_TOXIC_SPIKES] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_OPPONENTS_FIELD,
        .priority = 0,
        .ignoresProtect = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .skyBattleBanned = TRUE,
        .forcePressure = TRUE,
    },

    [MOVE_HEART_SWAP] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_STATUS,
    },

    [MOVE_AQUA_RING] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_MAGNET_RISE] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .gravityBanned = TRUE,
    },

    [MOVE_FLARE_BLITZ] =
    {
        .effect = EFFECT_RECOIL,
        .power = 120,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .thawsUser = TRUE,
        .recoil = 33,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
    },

    [MOVE_FORCE_PALM] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
    },

    [MOVE_AURA_SPHERE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .pulseMove = TRUE,
        .ballisticMove = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_ROCK_POLISH] =
    {
        .effect = EFFECT_SPEED_UP_2,
        .power = 0,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
    },

    [MOVE_POISON_JAB] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),
    },

    [MOVE_DARK_PULSE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .pulseMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),
    },

    [MOVE_NIGHT_SLASH] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .criticalHitStage = 1,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_AQUA_TAIL] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_WATER,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SEED_BOMB] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_AIR_SLASH] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .slicingMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
    },

    [MOVE_X_SCISSOR] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_BUG_BUZZ] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 10,
        }),
    },

    [MOVE_DRAGON_PULSE] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .pulseMove = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_DRAGON_RUSH] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_DRAGON,
        .accuracy = 75,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),
    },

    [MOVE_POWER_GEM] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_DRAIN_PUNCH] =
    {
        .effect = EFFECT_ABSORB,
        .power = 75,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .healingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_VACUUM_WAVE] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_FOCUS_BLAST] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FIGHTING,
        .accuracy = 70,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 10,
        }),
    },

    [MOVE_ENERGY_BALL] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 10,
        }),
    },

    [MOVE_BRAVE_BIRD] =
    {
        .effect = EFFECT_RECOIL,
        .power = 120,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .recoil = 33,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_EARTH_POWER] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 10,
        }),
        .skyBattleBanned = TRUE,
    },

    [MOVE_SWITCHEROO] =
    {
        .effect = EFFECT_TRICK,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
    },

    [MOVE_GIGA_IMPACT] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),
    },

    [MOVE_NASTY_PLOT] =
    {
        .effect = EFFECT_SPECIAL_ATTACK_UP_2,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_BULLET_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_AVALANCHE] =
    {
        .effect = EFFECT_REVENGE,
        .power = 60,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = -4,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_ICE_SHARD] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SHADOW_CLAW] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .criticalHitStage = 1,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_THUNDER_FANG] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_ELECTRIC,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 10,
        }),
    },

    [MOVE_ICE_FANG] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_ICE,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_FIRE_FANG] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_FIRE,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        },
        {
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),
    },

    [MOVE_SHADOW_SNEAK] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_MUD_BOMB] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_GROUND,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 30,
        }),
    },

    [MOVE_PSYCHO_CUT] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .slicingMove = TRUE,
        .criticalHitStage = 1,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_ZEN_HEADBUTT] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),
    },

    [MOVE_MIRROR_SHOT] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_STEEL,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 30,
        }),
    },

    [MOVE_FLASH_CANNON] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 10,
        }),
    },

    [MOVE_ROCK_CLIMB] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 20,
        }),
    },

    [MOVE_DEFOG] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_TRICK_ROOM] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = -7,
        .ignoresProtect = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_DRACO_METEOR] =
    {
        .effect = EFFECT_HIT,
        .power = 130,
        .type = TYPE_DRAGON,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_2,
            .self = TRUE,
            .chance = 0,
        }),
    },

    [MOVE_DISCHARGE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
    },

    [MOVE_LAVA_PLUME] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),
    },

    [MOVE_LEAF_STORM] =
    {
        .effect = EFFECT_HIT,
        .power = 130,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_2,
            .self = TRUE,
            .chance = 0,
        }),
    },

    [MOVE_POWER_WHIP] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_GRASS,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_ROCK_WRECKER] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
            .chance = 0,
        }),
    },

    [MOVE_CROSS_POISON] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .criticalHitStage = 1,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 10,
        }),
    },

    [MOVE_GUNK_SHOT] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_POISON,
        .accuracy = 80,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),
    },

    [MOVE_IRON_HEAD] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
    },

    [MOVE_MAGNET_BOMB] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_STONE_EDGE] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_ROCK,
        .accuracy = 80,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .criticalHitStage = 1,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_CAPTIVATE] =
    {
        .effect = EFFECT_CAPTIVATE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_STEALTH_ROCK] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_OPPONENTS_FIELD,
        .priority = 0,
        .ignoresProtect = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .forcePressure = TRUE,
    },

    [MOVE_GRASS_KNOT] =
    {
        .effect = EFFECT_LOW_KICK,
        .power = 1,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_SPECIAL,
        .skyBattleBanned = TRUE,
    },

    [MOVE_CHATTER] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 100,
        }),
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .sketchBanned = TRUE,
    },

    [MOVE_JUDGMENT] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_BUG_BITE] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BUG_BITE,
        }),
    },

    [MOVE_CHARGE_BEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_ELECTRIC,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_PLUS_1,
            .self = TRUE,
            .chance = 70,
        }),
    },

    [MOVE_WOOD_HAMMER] =
    {
        .effect = EFFECT_RECOIL,
        .power = 120,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .recoil = 33,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_AQUA_JET] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_ATTACK_ORDER] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .criticalHitStage = 1,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_DEFEND_ORDER] =
    {
        .effect = EFFECT_COSMIC_POWER,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_HEAL_ORDER] =
    {
        .effect = EFFECT_RESTORE_HP,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_HEAD_SMASH] =
    {
        .effect = EFFECT_RECOIL,
        .power = 150,
        .type = TYPE_ROCK,
        .accuracy = 80,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .recoil = 50,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_DOUBLE_HIT] =
    {
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .strikeCount = 2,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_ROAR_OF_TIME] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_DRAGON,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
            .chance = 0,
        }),
    },

    [MOVE_SPACIAL_REND] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_DRAGON,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .criticalHitStage = 1,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_LUNAR_DANCE] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .danceMove = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_CRUSH_GRIP] =
    {
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_MAGMA_STORM] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIRE,
        .accuracy = 75,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .chance = 0,
        }),
    },

    [MOVE_DARK_VOID] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 50,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SEED_FLARE] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_GRASS,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_2,
            .chance = 40,
        }),
    },

    [MOVE_OMINOUS_WIND] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .windMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ALL_STATS_UP,
            .self = TRUE,
            .chance = 10,
        }),
    },

    [MOVE_SHADOW_FORCE] =
    {
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = 120,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .ignoresProtect = TRUE,
        .category = SPLIT_PHYSICAL,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_HONE_CLAWS] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_WIDE_GUARD] =
    {
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 3,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
    },

    [MOVE_GUARD_SPLIT] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_POWER_SPLIT] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_WONDER_ROOM] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_PSYSHOCK] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_VENOSHOCK] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_AUTOTOMIZE] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_RAGE_POWDER] =
    {
        .effect = EFFECT_FOLLOW_ME,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 2,
        .ignoresProtect = TRUE,
        .powderMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
    },

    [MOVE_TELEKINESIS] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
        .gravityBanned = TRUE,
    },

    [MOVE_MAGIC_ROOM] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SMACK_DOWN] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .skyBattleBanned = TRUE,
    },

    [MOVE_STORM_THROW] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_FLAME_BURST] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_SLUDGE_WAVE] =
    {
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 10,
        }),
    },

    [MOVE_QUIVER_DANCE] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .danceMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_HEAVY_SLAM] =
    {
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .skyBattleBanned = TRUE,
    },

    [MOVE_SYNCHRONOISE] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_ELECTRO_BALL] =
    {
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_SOAK] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_FLAME_CHARGE] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
    },

    [MOVE_COIL] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_LOW_SWEEP] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
    },

    [MOVE_ACID_SPRAY] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_2,
            .chance = 100,
        }),
    },

    [MOVE_FOUL_PLAY] =
    {
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SIMPLE_BEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_ENTRAINMENT] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_AFTER_YOU] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
    },

    [MOVE_ROUND] =
    {
        .effect = EFFECT_ROUND,
        .power = 60,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ROUND,
        }),
    },

    [MOVE_ECHOED_VOICE] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_CHIP_AWAY] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_CLEAR_SMOG] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_STORED_POWER] =
    {
        .effect = EFFECT_HIT,
        .power = 20,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_QUICK_GUARD] =
    {
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 3,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
    },

    [MOVE_ALLY_SWITCH] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 2,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SCALD] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .thawsUser = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),
    },

    [MOVE_SHELL_SMASH] =
    {
        .effect = EFFECT_SHELL_SMASH,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_HEAL_PULSE] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .pulseMove = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_HEX] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_SKY_DROP] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .gravityBanned = TRUE,
    },

    [MOVE_SHIFT_GEAR] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_CIRCLE_THROW] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = -6,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
    },

    [MOVE_INCINERATE] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_QUASH] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
    },

    [MOVE_ACROBATICS] =
    {
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_REFLECT_TYPE] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_RETALIATE] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_FINAL_GAMBIT] =
    {
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_SPECIAL,
        .parentalBondBanned = TRUE,
    },

    [MOVE_BESTOW] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
    },

    [MOVE_INFERNO] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIRE,
        .accuracy = 50,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 100,
        }),
    },

    [MOVE_WATER_PLEDGE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .skyBattleBanned = TRUE,
    },

    [MOVE_FIRE_PLEDGE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .skyBattleBanned = TRUE,
    },

    [MOVE_GRASS_PLEDGE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .skyBattleBanned = TRUE,
    },

    [MOVE_VOLT_SWITCH] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_STRUGGLE_BUG] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 100,
        }),
    },

    [MOVE_BULLDOZE] =
    {
        .effect = EFFECT_EARTHQUAKE,
        .power = 60,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
        .skyBattleBanned = TRUE,
    },

    [MOVE_FROST_BREATH] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_DRAGON_TAIL] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_DRAGON,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = -6,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
    },

    [MOVE_WORK_UP] =
    {
        .effect = EFFECT_ATTACK_SPATK_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_ELECTROWEB] =
    {
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_ELECTRIC,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
    },

    [MOVE_WILD_CHARGE] =
    {
        .effect = EFFECT_RECOIL,
        .power = 90,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .recoil = 25,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_DRILL_RUN] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GROUND,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .criticalHitStage = 1,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_DUAL_CHOP] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_DRAGON,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .strikeCount = 2,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_HEART_STAMP] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
    },

    [MOVE_HORN_LEECH] =
    {
        .effect = EFFECT_ABSORB,
        .power = 75,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .healingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SACRED_SWORD] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_RAZOR_SHELL] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_WATER,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 50,
        }),
    },

    [MOVE_HEAT_CRASH] =
    {
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_LEAF_TORNADO] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .windMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 50,
        }),
    },

    [MOVE_STEAMROLLER] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
    },

    [MOVE_COTTON_GUARD] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_NIGHT_DAZE] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_DARK,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 40,
        }),
    },

    [MOVE_PSYSTRIKE] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_TAIL_SLAP] =
    {
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_HURRICANE] =
    {
        .effect = EFFECT_THUNDER,
        .power = 110,
        .type = TYPE_FLYING,
        .accuracy = 70,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .windMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 30,
        }),
    },

    [MOVE_HEAD_CHARGE] =
    {
        .effect = EFFECT_RECOIL,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .recoil = 25,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_GEAR_GRIND] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_STEEL,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .strikeCount = 2,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SEARING_SHOT] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),
    },

    [MOVE_TECHNO_BLAST] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_RELIC_SONG] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SLEEP,
            .chance = 10,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_SECRET_SWORD] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .slicingMove = TRUE,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_GLACIATE] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_ICE,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
    },

    [MOVE_BOLT_STRIKE] =
    {
        .effect = EFFECT_HIT,
        .power = 130,
        .type = TYPE_ELECTRIC,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 20,
        }),
    },

    [MOVE_BLUE_FLARE] =
    {
        .effect = EFFECT_HIT,
        .power = 130,
        .type = TYPE_FIRE,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 20,
        }),
    },

    [MOVE_FIERY_DANCE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .danceMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_PLUS_1,
            .self = TRUE,
            .chance = 50,
        }),
    },

    [MOVE_FREEZE_SHOCK] =
    {
        .effect = EFFECT_HIT,
        .power = 140,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .metronomeBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_ICE_BURN] =
    {
        .effect = EFFECT_HIT,
        .power = 140,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),
        .metronomeBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_SNARL] =
    {
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_DARK,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 100,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_ICICLE_CRASH] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
    },

    [MOVE_V_CREATE] =
    {
        .effect = EFFECT_HIT,
        .power = 180,
        .type = TYPE_FIRE,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_FUSION_FLARE] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .thawsUser = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_FUSION_BOLT] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_FLYING_PRESS] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .gravityBanned = TRUE,
        .skyBattleBanned = TRUE,
    },

    [MOVE_MAT_BLOCK] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .skyBattleBanned = TRUE,
    },

    [MOVE_BELCH] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_POISON,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .meFirstBanned = TRUE,
    },

    [MOVE_ROTOTILLER] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .skyBattleBanned = TRUE,
    },

    [MOVE_STICKY_WEB] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_OPPONENTS_FIELD,
        .priority = 0,
        .ignoresProtect = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .skyBattleBanned = TRUE,
    },

    [MOVE_FELL_STINGER] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_PHANTOM_FORCE] =
    {
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = 90,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .ignoresProtect = TRUE,
        .category = SPLIT_PHYSICAL,
        .assistBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_TRICK_OR_TREAT] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_NOBLE_ROAR] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_ION_DELUGE] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 25,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 1,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_PARABOLIC_CHARGE] =
    {
        .effect = EFFECT_ABSORB,
        .power = 65,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .healingMove = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_FORESTS_CURSE] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_PETAL_BLIZZARD] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .windMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_FREEZE_DRY] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_DISARMING_VOICE] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
    },

    [MOVE_PARTING_SHOT] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_TOPSY_TURVY] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_DRAINING_KISS] =
    {
        .effect = EFFECT_ABSORB,
        .power = 50,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .healingMove = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_CRAFTY_SHIELD] =
    {
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 3,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
    },

    [MOVE_FLOWER_SHIELD] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_GRASSY_TERRAIN] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .skyBattleBanned = TRUE,
    },

    [MOVE_MISTY_TERRAIN] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .skyBattleBanned = TRUE,
    },

    [MOVE_ELECTRIFY] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_STATUS,
    },

    [MOVE_PLAY_ROUGH] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_FAIRY,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 10,
        }),
    },

    [MOVE_FAIRY_WIND] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .windMove = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_MOONBLAST] =
    {
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 30,
        }),
    },

    [MOVE_BOOMBURST] =
    {
        .effect = EFFECT_HIT,
        .power = 140,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_FAIRY_LOCK] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_KINGS_SHIELD] =
    {
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_PLAY_NICE] =
    {
        .effect = EFFECT_ATTACK_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_CONFIDE] =
    {
        .effect = EFFECT_SPECIAL_ATTACK_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_DIAMOND_STORM] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_ROCK,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_STEAM_ERUPTION] =
    {
        .effect = EFFECT_HIT,
        .power = 110,
        .type = TYPE_WATER,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .thawsUser = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_HYPERSPACE_HOLE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_WATER_SHURIKEN] =
    {
        .effect = EFFECT_MULTI_HIT,
        .power = 15,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_MYSTICAL_FIRE] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 100,
        }),
    },

    [MOVE_SPIKY_SHIELD] =
    {
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
    },

    [MOVE_AROMATIC_MIST] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_ALLY,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_EERIE_IMPULSE] =
    {
        .effect = EFFECT_SPECIAL_ATTACK_DOWN_2,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_VENOM_DRENCH] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_POWDER] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_GEOMANCY] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = SPLIT_STATUS,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .skyBattleBanned = TRUE,
    },

    [MOVE_MAGNETIC_FLUX] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_HAPPY_HOUR] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_ELECTRIC_TERRAIN] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .skyBattleBanned = TRUE,
    },

    [MOVE_DAZZLING_GLEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_CELEBRATE] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_HOLD_HANDS] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_ALLY,
        .priority = 0,
        .ignoresProtect = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_BABY_DOLL_EYES] =
    {
        .effect = EFFECT_ATTACK_DOWN,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_NUZZLE] =
    {
        .effect = EFFECT_HIT,
        .power = 20,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 100,
        }),
    },

    [MOVE_HOLD_BACK] =
    {
        .effect = EFFECT_FALSE_SWIPE,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_INFESTATION] =
    {
        .effect = EFFECT_HIT,
        .power = 20,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .chance = 0,
        }),
    },

    [MOVE_POWER_UP_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
    },

    [MOVE_OBLIVION_WING] =
    {
        .effect = EFFECT_ABSORB,
        .power = 80,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .healingMove = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_THOUSAND_ARROWS] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        .skyBattleBanned = TRUE,
    },

    [MOVE_THOUSAND_WAVES] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PREVENT_ESCAPE,
            .chance = 0,
        }),
        .metronomeBanned = TRUE,
        .skyBattleBanned = TRUE,
    },

    [MOVE_LANDS_WRATH] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .skyBattleBanned = TRUE,
    },

    [MOVE_LIGHT_OF_RUIN] =
    {
        .effect = EFFECT_RECOIL,
        .power = 140,
        .type = TYPE_FAIRY,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .recoil = 50,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_ORIGIN_PULSE] =
    {
        .effect = EFFECT_HIT,
        .power = 110,
        .type = TYPE_WATER,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .pulseMove = TRUE,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_PRECIPICE_BLADES] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_GROUND,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        .skyBattleBanned = TRUE,
    },

    [MOVE_DRAGON_ASCENT] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_HYPERSPACE_FURY] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .self = TRUE,
            .chance = 0,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_SHORE_UP] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_FIRST_IMPRESSION] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 2,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_BANEFUL_BUNKER] =
    {
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
    },

    [MOVE_SPIRIT_SHACKLE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PREVENT_ESCAPE,
            .chance = 100,
        }),
    },

    [MOVE_DARKEST_LARIAT] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SPARKLING_ARIA] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_ICE_HAMMER] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .self = TRUE,
            .chance = 0,
        }),
    },

    [MOVE_FLORAL_HEALING] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_HIGH_HORSEPOWER] =
    {
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_GROUND,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_STRENGTH_SAP] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .healingMove = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SOLAR_BLADE] =
    {
        .effect = EFFECT_SOLAR_BEAM,
        .power = 125,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_LEAFAGE] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SPOTLIGHT] =
    {
        .effect = EFFECT_FOLLOW_ME,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 3,
        .magicCoatAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
    },

    [MOVE_TOXIC_THREAD] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_LASER_FOCUS] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_GEAR_UP] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_THROAT_CHOP] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_POLLEN_PUFF] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_ANCHOR_SHOT] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PREVENT_ESCAPE,
            .chance = 100,
        }),
    },

    [MOVE_PSYCHIC_TERRAIN] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .skyBattleBanned = TRUE,
    },

    [MOVE_LUNGE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 100,
        }),
    },

    [MOVE_FIRE_LASH] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 100,
        }),
    },

    [MOVE_POWER_TRIP] =
    {
        .effect = EFFECT_HIT,
        .power = 20,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_BURN_UP] =
    {
        .effect = EFFECT_HIT,
        .power = 130,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .thawsUser = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_SPEED_SWAP] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_STATUS,
    },

    [MOVE_SMART_STRIKE] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_PURIFY] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_REVELATION_DANCE] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .danceMove = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_CORE_ENFORCER] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_TROP_KICK] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 100,
        }),
    },

    [MOVE_INSTRUCT] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_BEAK_BLAST] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = -3,
        .ballisticMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .meFirstBanned = TRUE,
    },

    [MOVE_CLANGING_SCALES] =
    {
        .effect = EFFECT_HIT,
        .power = 110,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .self = TRUE,
            .chance = 0,
        }),
    },

    [MOVE_DRAGON_HAMMER] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_BRUTAL_SWING] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_AURORA_VEIL] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_SHELL_TRAP] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = -3,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .meFirstBanned = TRUE,
    },

    [MOVE_FLEUR_CANNON] =
    {
        .effect = EFFECT_HIT,
        .power = 130,
        .type = TYPE_FAIRY,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_2,
            .self = TRUE,
            .chance = 0,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_PSYCHIC_FANGS] =
    {
        .effect = EFFECT_BRICK_BREAK,
        .power = 85,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_STOMPING_TANTRUM] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SHADOW_BONE] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 20,
        }),
    },

    [MOVE_ACCELEROCK] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_LIQUIDATION] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 20,
        }),
    },

    [MOVE_PRISMATIC_LASER] =
    {
        .effect = EFFECT_HIT,
        .power = 160,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
            .chance = 0,
        }),
    },

    [MOVE_SPECTRAL_THIEF] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_SUNSTEEL_STRIKE] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_MOONGEIST_BEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_TEARFUL_LOOK] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_ZING_ZAP] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
    },

    [MOVE_NATURES_MADNESS] =
    {
        .effect = EFFECT_SUPER_FANG,
        .power = 1,
        .type = TYPE_FAIRY,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_MULTI_ATTACK] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_MIND_BLOWN] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        .dampBanned = TRUE,
    },

    [MOVE_PLASMA_FISTS] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_PHOTON_GEYSER] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_ZIPPY_ZAP] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 2,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_EVS_PLUS_1,
            .chance = 100,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_SPLISHY_SPLASH] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_FLOATY_FALL] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .metronomeBanned = TRUE,
        .gravityBanned = TRUE,
    },

    [MOVE_PIKA_PAPOW] =
    {
        .effect = EFFECT_RETURN,
        .power = 1,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_BOUNCY_BUBBLE] =
    {
        .effect = EFFECT_ABSORB,
        .power = 60,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .healingMove = TRUE,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_BUZZY_BUZZ] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 100,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_SIZZLY_SLIDE] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .thawsUser = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 100,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_GLITZY_GLOW] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_BADDY_BAD] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_SAPPY_SEED] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_FREEZY_FROST] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_SPARKLY_SWIRL] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FAIRY,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_VEEVEE_VOLLEY] =
    {
        .effect = EFFECT_RETURN,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_DOUBLE_IRON_BASH] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .strikeCount = 2,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_DYNAMAX_CANNON] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .parentalBondBanned = TRUE,
    },

    [MOVE_SNIPE_SHOT] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .criticalHitStage = 1,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_JAW_LOCK] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_STUFF_CHEEKS] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_NO_RETREAT] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_TAR_SHOT] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_MAGIC_POWDER] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_DRAGON_DARTS] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .strikeCount = 2,
        .category = SPLIT_PHYSICAL,
        .parentalBondBanned = TRUE,
    },

    [MOVE_TEATIME] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_OCTOLOCK] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_STATUS,
    },

    [MOVE_BOLT_BEAK] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_FISHIOUS_REND] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_COURT_CHANGE] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_CLANGOROUS_SOUL] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .snatchAffected = TRUE,
        .danceMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
    },

    [MOVE_BODY_PRESS] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_DECORATE] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
    },

    [MOVE_DRUM_BEATING] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_SNAP_TRAP] =
    {
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .chance = 0,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_PYRO_BALL] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .thawsUser = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_BEHEMOTH_BLADE] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
    },

    [MOVE_BEHEMOTH_BASH] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
    },

    [MOVE_AURA_WHEEL] =
    {
        .effect = EFFECT_HIT,
        .power = 110,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_BREAKING_SWIPE] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 100,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_BRANCH_POKE] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_OVERDRIVE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_APPLE_ACID] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 100,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_GRAV_APPLE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 100,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_SPIRIT_BREAK] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 100,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_STRANGE_STEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_FAIRY,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 20,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_LIFE_DEW] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
    },

    [MOVE_OBSTRUCT] =
    {
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_FALSE_SURRENDER] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_METEOR_ASSAULT] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
            .chance = 0,
        }),
        .metronomeBanned = TRUE,
        .instructBanned = TRUE,
    },

    [MOVE_ETERNABEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 160,
        .type = TYPE_DRAGON,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
            .chance = 0,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_STEEL_BEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 140,
        .type = TYPE_STEEL,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_EXPANDING_FORCE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_STEEL_ROLLER] =
    {
        .effect = EFFECT_HIT,
        .power = 130,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .skyBattleBanned = TRUE,
    },

    [MOVE_SCALE_SHOT] =
    {
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_DRAGON,
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_METEOR_BEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_PLUS_1,
            .self = TRUE,
            .chance = 0,
        }),
        .instructBanned = TRUE,
    },

    [MOVE_SHELL_SIDE_ARM] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 20,
        }),
    },

    [MOVE_MISTY_EXPLOSION] =
    {
        .effect = EFFECT_EXPLOSION,
        .power = 100,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .dampBanned = TRUE,
    },

    [MOVE_GRASSY_GLIDE] =
    {
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_RISING_VOLTAGE] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_TERRAIN_PULSE] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .pulseMove = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_SKITTER_SMACK] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_BUG,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 100,
        }),
    },

    [MOVE_BURNING_JEALOUSY] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 100,
        }),
    },

    [MOVE_LASH_OUT] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_POLTERGEIST] =
    {
        .effect = EFFECT_HIT,
        .power = 110,
        .type = TYPE_GHOST,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_CORROSIVE_GAS] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_COACHING] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALLY,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_FLIP_TURN] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_TRIPLE_AXEL] =
    {
        .effect = EFFECT_TRIPLE_KICK,
        .power = 20,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .strikeCount = 3,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_DUAL_WINGBEAT] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FLYING,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .strikeCount = 2,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SCORCHING_SANDS] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .thawsUser = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),
    },

    [MOVE_JUNGLE_HEALING] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
    },

    [MOVE_WICKED_BLOW] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_SURGING_STRIKES] =
    {
        .effect = EFFECT_HIT,
        .power = 25,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .strikeCount = 3,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_THUNDER_CAGE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_ELECTRIC,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .chance = 0,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_DRAGON_ENERGY] =
    {
        .effect = EFFECT_ERUPTION,
        .power = 150,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_FREEZING_GLARE] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_FIERY_WRATH] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_THUNDEROUS_KICK] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 100,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_GLACIAL_LANCE] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_ASTRAL_BARRAGE] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_EERIE_SPELL] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_DIRE_CLAW] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_PSYSHIELD_BASH] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_PSYCHIC,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
    },

    [MOVE_POWER_SHIFT] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
    },

    [MOVE_STONE_AXE] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SPRINGTIDE_STORM] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FAIRY,
        .accuracy = 80,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .windMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 30,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_MYSTICAL_POWER] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_PSYCHIC,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
    },

    [MOVE_RAGING_FURY] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_THRASH,
            .self = TRUE,
            .chance = 0,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_WAVE_CRASH] =
    {
        .effect = EFFECT_RECOIL,
        .power = 120,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .recoil = 33,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_CHLOROBLAST] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_GRASS,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_MOUNTAIN_GALE] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_ICE,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
    },

    [MOVE_VICTORY_DANCE] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .danceMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_HEADLONG_RUSH] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_BARB_BARRAGE] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 50,
        }),
    },

    [MOVE_ESPER_WING] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .criticalHitStage = 1,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
    },

    [MOVE_BITTER_MALICE] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 100,
        }),
    },

    [MOVE_SHELTER] =
    {
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_TRIPLE_ARROWS] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .criticalHitStage = 1,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 50,
        }),
    },

    [MOVE_INFERNAL_PARADE] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),
    },

    [MOVE_CEASELESS_EDGE] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_DARK,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_BLEAKWIND_STORM] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FLYING,
        .accuracy = 80,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .windMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 30,
        }),
    },

    [MOVE_WILDBOLT_STORM] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_ELECTRIC,
        .accuracy = 80,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .windMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 20,
        }),
    },

    [MOVE_SANDSEAR_STORM] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_GROUND,
        .accuracy = 80,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .windMove = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 20,
        }),
    },

    [MOVE_LUNAR_BLESSING] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_TAKE_HEART] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
    },

    [MOVE_TERA_BLAST] =
    {
        .effect = EFFECT_TERA_BLAST,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_TERA_BLAST,
            .self = TRUE,
        }),
        .forcePressure = TRUE,
    },

    [MOVE_SILK_TRAP] =
    {
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
    },

    [MOVE_AXE_KICK] =
    {
        .effect = EFFECT_RECOIL_IF_MISS,
        .power = 120,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 30,
        }),
    },

    [MOVE_LAST_RESPECTS] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_LUMINA_CRASH] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_2,
            .chance = 100,
        }),
    },

    [MOVE_ORDER_UP] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_JET_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_SPICY_EXTRACT] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .magicCoatAffected = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
    },

    [MOVE_SPIN_OUT] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_2,
            .self = TRUE,
            .chance = 0,
        }),
    },

    [MOVE_POPULATION_BOMB] =
    {
        .effect = EFFECT_HIT,
        .power = 20,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .strikeCount = 10,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_ICE_SPINNER] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_GLAIVE_RUSH] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_REVIVAL_BLESSING] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .healingMove = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
    },

    [MOVE_SALT_CURE] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_TRIPLE_DIVE] =
    {
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_WATER,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .strikeCount = 3,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_MORTAL_SPIN] =
    {
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_DOODLE] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
    },

    [MOVE_FILLET_AWAY] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .snatchAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
    },

    [MOVE_KOWTOW_CLEAVE] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_FLOWER_TRICK] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_TORCH_SONG] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
    },

    [MOVE_AQUA_STEP] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .danceMove = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
    },

    [MOVE_RAGING_BULL] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_MAKE_IT_RAIN] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PAYDAY,
            .chance = 0,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_RUINATION] =
    {
        .effect = EFFECT_SUPER_FANG,
        .power = 1,
        .type = TYPE_DARK,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_COLLISION_COURSE] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_ELECTRO_DRIFT] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_SHED_TAIL] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
    },

    [MOVE_CHILLY_RECEPTION] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
    },

    [MOVE_TIDY_UP] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
    },

    [MOVE_SNOWSCAPE] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .metronomeBanned = TRUE,
    },

    [MOVE_POUNCE] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_TRAILBLAZE] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_CHILLING_WATER] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 100,
        }),
        .metronomeBanned = TRUE,
    },

    [MOVE_HYPER_DRILL] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .ignoresProtect = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_TWIN_BEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .strikeCount = 2,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_RAGE_FIST] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_ARMOR_CANNON] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_BITTER_BLADE] =
    {
        .effect = EFFECT_ABSORB,
        .power = 90,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .healingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_DOUBLE_SHOCK] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
    },

    [MOVE_GIGATON_HAMMER] =
    {
        .effect = EFFECT_HIT,
        .power = 160,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_COMEUPPANCE] =
    {
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        .meFirstBanned = TRUE,
    },

    [MOVE_AQUA_CUTTER] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .slicingMove = TRUE,
        .criticalHitStage = 1,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_BLAZING_TORQUE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .meFirstBanned = TRUE,
    },

    [MOVE_WICKED_TORQUE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SLEEP,
            .chance = 10,
        }),
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .meFirstBanned = TRUE,
    },

    [MOVE_NOXIOUS_TORQUE] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .meFirstBanned = TRUE,
    },

    [MOVE_COMBAT_TORQUE] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .meFirstBanned = TRUE,
    },

    [MOVE_MAGICAL_TORQUE] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 30,
        }),
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .meFirstBanned = TRUE,
    },

    [MOVE_PSYBLADE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_HYDRO_STEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .thawsUser = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_BLOOD_MOON] =
    {
        .effect = EFFECT_HIT,
        .power = 140,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_MATCHA_GOTCHA] =
    {
        .effect = EFFECT_ABSORB,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .healingMove = TRUE,
        .thawsUser = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 20,
        }),
    },

    [MOVE_SYRUP_BOMB] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_GRASS,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .ballisticMove = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_IVY_CUDGEL] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .criticalHitStage = 1,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_ELECTRO_SHOT] =
    {
        .effect = EFFECT_HIT,
        .power = 130,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_PLUS_1,
            .self = TRUE,
            .chance = 0,
        }),
    },

    [MOVE_TERA_STARSTORM] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
    },

    [MOVE_FICKLE_BEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_BURNING_BULWARK] =
    {
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_FIRE,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .category = SPLIT_STATUS,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
    },

    [MOVE_THUNDERCLAP] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_MIGHTY_CLEAVE] =
    {
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .ignoresProtect = TRUE,
        .slicingMove = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_TACHYON_CUTTER] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .slicingMove = TRUE,
        .strikeCount = 2,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_HARD_PRESS] =
    {
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_DRAGON_CHEER] =
    {
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_DRAGON,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_ALLY,
        .priority = 0,
        .category = SPLIT_STATUS,
    },

    [MOVE_ALLURING_VOICE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 100,
        }),
    },

    [MOVE_TEMPER_FLARE] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_SUPERCELL_SLAM] =
    {
        .effect = EFFECT_RECOIL_IF_MISS,
        .power = 100,
        .type = TYPE_ELECTRIC,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
    },

    [MOVE_PSYCHIC_NOISE] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .category = SPLIT_SPECIAL,
    },

    [MOVE_UPPER_HAND] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 3,
        .makesContact = TRUE,
        .category = SPLIT_PHYSICAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 100,
        }),
    },

    [MOVE_MALIGNANT_CHAIN] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_TOXIC,
            .chance = 50,
        }),
    },

};
