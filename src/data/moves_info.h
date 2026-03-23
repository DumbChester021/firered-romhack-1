// ==========================================================================
// moves_info.h — Unified move data (Phase 5)
//
// Single source of truth for: move names, descriptions, and battle stats.
// When adding a new move, add entries to all 4 arrays below.
//
// Merged from:
//   src/data/text/move_names.h    -> gMoveNames
//   src/move_descriptions.c       -> description strings + gMoveDescriptionPointers
//   src/data/battle_moves.h       -> gBattleMoves
// ==========================================================================

// ---------------------------------------------------------------------------
// Section 1: Move Names
// ---------------------------------------------------------------------------

const u8 gMoveNames[MOVES_COUNT][MOVE_NAME_LENGTH + 1] = {
    [MOVE_NONE]          = _("-$$$$$$"),
    [MOVE_POUND]         = _("POUND"),
    [MOVE_KARATE_CHOP]   = _("KARATE CHOP"),
    [MOVE_DOUBLE_SLAP]   = _("DOUBLESLAP"),
    [MOVE_COMET_PUNCH]   = _("COMET PUNCH"),
    [MOVE_MEGA_PUNCH]    = _("MEGA PUNCH"),
    [MOVE_PAY_DAY]       = _("PAY DAY"),
    [MOVE_FIRE_PUNCH]    = _("FIRE PUNCH"),
    [MOVE_ICE_PUNCH]     = _("ICE PUNCH"),
    [MOVE_THUNDER_PUNCH] = _("THUNDERPUNCH"),
    [MOVE_SCRATCH]       = _("SCRATCH"),
    [MOVE_VICE_GRIP]     = _("VISE GRIP"),
    [MOVE_GUILLOTINE]    = _("GUILLOTINE"),
    [MOVE_RAZOR_WIND]    = _("RAZOR WIND"),
    [MOVE_SWORDS_DANCE]  = _("SWORDS DANCE"),
    [MOVE_CUT]           = _("CUT"),
    [MOVE_GUST]          = _("GUST"),
    [MOVE_WING_ATTACK]   = _("WING ATTACK"),
    [MOVE_WHIRLWIND]     = _("WHIRLWIND"),
    [MOVE_FLY]           = _("FLY"),
    [MOVE_BIND]          = _("BIND"),
    [MOVE_SLAM]          = _("SLAM"),
    [MOVE_VINE_WHIP]     = _("VINE WHIP"),
    [MOVE_STOMP]         = _("STOMP"),
    [MOVE_DOUBLE_KICK]   = _("DOUBLE KICK"),
    [MOVE_MEGA_KICK]     = _("MEGA KICK"),
    [MOVE_JUMP_KICK]     = _("JUMP KICK"),
    [MOVE_ROLLING_KICK]  = _("ROLLING KICK"),
    [MOVE_SAND_ATTACK]   = _("SAND-ATTACK"),
    [MOVE_HEADBUTT]      = _("HEADBUTT"),
    [MOVE_HORN_ATTACK]   = _("HORN ATTACK"),
    [MOVE_FURY_ATTACK]   = _("FURY ATTACK"),
    [MOVE_HORN_DRILL]    = _("HORN DRILL"),
    [MOVE_TACKLE]        = _("TACKLE"),
    [MOVE_BODY_SLAM]     = _("BODY SLAM"),
    [MOVE_WRAP]          = _("WRAP"),
    [MOVE_TAKE_DOWN]     = _("TAKE DOWN"),
    [MOVE_THRASH]        = _("THRASH"),
    [MOVE_DOUBLE_EDGE]   = _("DOUBLE-EDGE"),
    [MOVE_TAIL_WHIP]     = _("TAIL WHIP"),
    [MOVE_POISON_STING]  = _("POISON STING"),
    [MOVE_TWINEEDLE]     = _("TWINEEDLE"),
    [MOVE_PIN_MISSILE]   = _("PIN MISSILE"),
    [MOVE_LEER]          = _("LEER"),
    [MOVE_BITE]          = _("BITE"),
    [MOVE_GROWL]         = _("GROWL"),
    [MOVE_ROAR]          = _("ROAR"),
    [MOVE_SING]          = _("SING"),
    [MOVE_SUPERSONIC]    = _("SUPERSONIC"),
    [MOVE_SONIC_BOOM]    = _("SONICBOOM"),
    [MOVE_DISABLE]       = _("DISABLE"),
    [MOVE_ACID]          = _("ACID"),
    [MOVE_EMBER]         = _("EMBER"),
    [MOVE_FLAMETHROWER]  = _("FLAMETHROWER"),
    [MOVE_MIST]          = _("MIST"),
    [MOVE_WATER_GUN]     = _("WATER GUN"),
    [MOVE_HYDRO_PUMP]    = _("HYDRO PUMP"),
    [MOVE_SURF]          = _("SURF"),
    [MOVE_ICE_BEAM]      = _("ICE BEAM"),
    [MOVE_BLIZZARD]      = _("BLIZZARD"),
    [MOVE_PSYBEAM]       = _("PSYBEAM"),
    [MOVE_BUBBLE_BEAM]   = _("BUBBLE BEAM"),
    [MOVE_AURORA_BEAM]   = _("AURORA BEAM"),
    [MOVE_HYPER_BEAM]    = _("HYPER BEAM"),
    [MOVE_PECK]          = _("PECK"),
    [MOVE_DRILL_PECK]    = _("DRILL PECK"),
    [MOVE_SUBMISSION]    = _("SUBMISSION"),
    [MOVE_LOW_KICK]      = _("LOW KICK"),
    [MOVE_COUNTER]       = _("COUNTER"),
    [MOVE_SEISMIC_TOSS]  = _("SEISMIC TOSS"),
    [MOVE_STRENGTH]      = _("STRENGTH"),
    [MOVE_ABSORB]        = _("ABSORB"),
    [MOVE_MEGA_DRAIN]    = _("MEGA DRAIN"),
    [MOVE_LEECH_SEED]    = _("LEECH SEED"),
    [MOVE_GROWTH]        = _("GROWTH"),
    [MOVE_RAZOR_LEAF]    = _("RAZOR LEAF"),
    [MOVE_SOLAR_BEAM]    = _("SOLARBEAM"),
    [MOVE_POISON_POWDER] = _("POISON POWDER"),
    [MOVE_STUN_SPORE]    = _("STUN SPORE"),
    [MOVE_SLEEP_POWDER]  = _("SLEEP POWDER"),
    [MOVE_PETAL_DANCE]   = _("PETAL DANCE"),
    [MOVE_STRING_SHOT]   = _("STRING SHOT"),
    [MOVE_DRAGON_RAGE]   = _("DRAGON RAGE"),
    [MOVE_FIRE_SPIN]     = _("FIRE SPIN"),
    [MOVE_THUNDER_SHOCK] = _("THUNDERSHOCK"),
    [MOVE_THUNDERBOLT]   = _("THUNDERBOLT"),
    [MOVE_THUNDER_WAVE]  = _("THUNDER WAVE"),
    [MOVE_THUNDER]       = _("THUNDER"),
    [MOVE_ROCK_THROW]    = _("ROCK THROW"),
    [MOVE_EARTHQUAKE]    = _("EARTHQUAKE"),
    [MOVE_FISSURE]       = _("FISSURE"),
    [MOVE_DIG]           = _("DIG"),
    [MOVE_TOXIC]         = _("TOXIC"),
    [MOVE_CONFUSION]     = _("CONFUSION"),
    [MOVE_PSYCHIC]       = _("PSYCHIC"),
    [MOVE_HYPNOSIS]      = _("HYPNOSIS"),
    [MOVE_MEDITATE]      = _("MEDITATE"),
    [MOVE_AGILITY]       = _("AGILITY"),
    [MOVE_QUICK_ATTACK]  = _("QUICK ATTACK"),
    [MOVE_RAGE]          = _("RAGE"),
    [MOVE_TELEPORT]      = _("TELEPORT"),
    [MOVE_NIGHT_SHADE]   = _("NIGHT SHADE"),
    [MOVE_MIMIC]         = _("MIMIC"),
    [MOVE_SCREECH]       = _("SCREECH"),
    [MOVE_DOUBLE_TEAM]   = _("DOUBLE TEAM"),
    [MOVE_RECOVER]       = _("RECOVER"),
    [MOVE_HARDEN]        = _("HARDEN"),
    [MOVE_MINIMIZE]      = _("MINIMIZE"),
    [MOVE_SMOKESCREEN]   = _("SMOKESCREEN"),
    [MOVE_CONFUSE_RAY]   = _("CONFUSE RAY"),
    [MOVE_WITHDRAW]      = _("WITHDRAW"),
    [MOVE_DEFENSE_CURL]  = _("DEFENSE CURL"),
    [MOVE_BARRIER]       = _("BARRIER"),
    [MOVE_LIGHT_SCREEN]  = _("LIGHT SCREEN"),
    [MOVE_HAZE]          = _("HAZE"),
    [MOVE_REFLECT]       = _("REFLECT"),
    [MOVE_FOCUS_ENERGY]  = _("FOCUS ENERGY"),
    [MOVE_BIDE]          = _("BIDE"),
    [MOVE_METRONOME]     = _("METRONOME"),
    [MOVE_MIRROR_MOVE]   = _("MIRROR MOVE"),
    [MOVE_SELF_DESTRUCT] = _("SELFDESTRUCT"),
    [MOVE_EGG_BOMB]      = _("EGG BOMB"),
    [MOVE_LICK]          = _("LICK"),
    [MOVE_SMOG]          = _("SMOG"),
    [MOVE_SLUDGE]        = _("SLUDGE"),
    [MOVE_BONE_CLUB]     = _("BONE CLUB"),
    [MOVE_FIRE_BLAST]    = _("FIRE BLAST"),
    [MOVE_WATERFALL]     = _("WATERFALL"),
    [MOVE_CLAMP]         = _("CLAMP"),
    [MOVE_SWIFT]         = _("SWIFT"),
    [MOVE_SKULL_BASH]    = _("SKULL BASH"),
    [MOVE_SPIKE_CANNON]  = _("SPIKE CANNON"),
    [MOVE_CONSTRICT]     = _("CONSTRICT"),
    [MOVE_AMNESIA]       = _("AMNESIA"),
    [MOVE_KINESIS]       = _("KINESIS"),
    [MOVE_SOFT_BOILED]   = _("SOFTBOILED"),
    [MOVE_HI_JUMP_KICK]  = _("HI JUMP KICK"),
    [MOVE_GLARE]         = _("GLARE"),
    [MOVE_DREAM_EATER]   = _("DREAM EATER"),
    [MOVE_POISON_GAS]    = _("POISON GAS"),
    [MOVE_BARRAGE]       = _("BARRAGE"),
    [MOVE_LEECH_LIFE]    = _("LEECH LIFE"),
    [MOVE_LOVELY_KISS]   = _("LOVELY KISS"),
    [MOVE_SKY_ATTACK]    = _("SKY ATTACK"),
    [MOVE_TRANSFORM]     = _("TRANSFORM"),
    [MOVE_BUBBLE]        = _("BUBBLE"),
    [MOVE_DIZZY_PUNCH]   = _("DIZZY PUNCH"),
    [MOVE_SPORE]         = _("SPORE"),
    [MOVE_FLASH]         = _("FLASH"),
    [MOVE_PSYWAVE]       = _("PSYWAVE"),
    [MOVE_SPLASH]        = _("SPLASH"),
    [MOVE_ACID_ARMOR]    = _("ACID ARMOR"),
    [MOVE_CRABHAMMER]    = _("CRABHAMMER"),
    [MOVE_EXPLOSION]     = _("EXPLOSION"),
    [MOVE_FURY_SWIPES]   = _("FURY SWIPES"),
    [MOVE_BONEMERANG]    = _("BONEMERANG"),
    [MOVE_REST]          = _("REST"),
    [MOVE_ROCK_SLIDE]    = _("ROCK SLIDE"),
    [MOVE_HYPER_FANG]    = _("HYPER FANG"),
    [MOVE_SHARPEN]       = _("SHARPEN"),
    [MOVE_CONVERSION]    = _("CONVERSION"),
    [MOVE_TRI_ATTACK]    = _("TRI ATTACK"),
    [MOVE_SUPER_FANG]    = _("SUPER FANG"),
    [MOVE_SLASH]         = _("SLASH"),
    [MOVE_SUBSTITUTE]    = _("SUBSTITUTE"),
    [MOVE_STRUGGLE]      = _("STRUGGLE"),
    [MOVE_SKETCH]        = _("SKETCH"),
    [MOVE_TRIPLE_KICK]   = _("TRIPLE KICK"),
    [MOVE_THIEF]         = _("THIEF"),
    [MOVE_SPIDER_WEB]    = _("SPIDER WEB"),
    [MOVE_MIND_READER]   = _("MIND READER"),
    [MOVE_NIGHTMARE]     = _("NIGHTMARE"),
    [MOVE_FLAME_WHEEL]   = _("FLAME WHEEL"),
    [MOVE_SNORE]         = _("SNORE"),
    [MOVE_CURSE]         = _("CURSE"),
    [MOVE_FLAIL]         = _("FLAIL"),
    [MOVE_CONVERSION_2]  = _("CONVERSION 2"),
    [MOVE_AEROBLAST]     = _("AEROBLAST"),
    [MOVE_COTTON_SPORE]  = _("COTTON SPORE"),
    [MOVE_REVERSAL]      = _("REVERSAL"),
    [MOVE_SPITE]         = _("SPITE"),
    [MOVE_POWDER_SNOW]   = _("POWDER SNOW"),
    [MOVE_PROTECT]       = _("PROTECT"),
    [MOVE_MACH_PUNCH]    = _("MACH PUNCH"),
    [MOVE_SCARY_FACE]    = _("SCARY FACE"),
    [MOVE_FEINT_ATTACK]  = _("FEINT ATTACK"),
    [MOVE_SWEET_KISS]    = _("SWEET KISS"),
    [MOVE_BELLY_DRUM]    = _("BELLY DRUM"),
    [MOVE_SLUDGE_BOMB]   = _("SLUDGE BOMB"),
    [MOVE_MUD_SLAP]      = _("MUD-SLAP"),
    [MOVE_OCTAZOOKA]     = _("OCTAZOOKA"),
    [MOVE_SPIKES]        = _("SPIKES"),
    [MOVE_ZAP_CANNON]    = _("ZAP CANNON"),
    [MOVE_FORESIGHT]     = _("FORESIGHT"),
    [MOVE_DESTINY_BOND]  = _("DESTINY BOND"),
    [MOVE_PERISH_SONG]   = _("PERISH SONG"),
    [MOVE_ICY_WIND]      = _("ICY WIND"),
    [MOVE_DETECT]        = _("DETECT"),
    [MOVE_BONE_RUSH]     = _("BONE RUSH"),
    [MOVE_LOCK_ON]       = _("LOCK-ON"),
    [MOVE_OUTRAGE]       = _("OUTRAGE"),
    [MOVE_SANDSTORM]     = _("SANDSTORM"),
    [MOVE_GIGA_DRAIN]    = _("GIGA DRAIN"),
    [MOVE_ENDURE]        = _("ENDURE"),
    [MOVE_CHARM]         = _("CHARM"),
    [MOVE_ROLLOUT]       = _("ROLLOUT"),
    [MOVE_FALSE_SWIPE]   = _("FALSE SWIPE"),
    [MOVE_SWAGGER]       = _("SWAGGER"),
    [MOVE_MILK_DRINK]    = _("MILK DRINK"),
    [MOVE_SPARK]         = _("SPARK"),
    [MOVE_FURY_CUTTER]   = _("FURY CUTTER"),
    [MOVE_STEEL_WING]    = _("STEEL WING"),
    [MOVE_MEAN_LOOK]     = _("MEAN LOOK"),
    [MOVE_ATTRACT]       = _("ATTRACT"),
    [MOVE_SLEEP_TALK]    = _("SLEEP TALK"),
    [MOVE_HEAL_BELL]     = _("HEAL BELL"),
    [MOVE_RETURN]        = _("RETURN"),
    [MOVE_PRESENT]       = _("PRESENT"),
    [MOVE_FRUSTRATION]   = _("FRUSTRATION"),
    [MOVE_SAFEGUARD]     = _("SAFEGUARD"),
    [MOVE_PAIN_SPLIT]    = _("PAIN SPLIT"),
    [MOVE_SACRED_FIRE]   = _("SACRED FIRE"),
    [MOVE_MAGNITUDE]     = _("MAGNITUDE"),
    [MOVE_DYNAMIC_PUNCH] = _("DYNAMICPUNCH"),
    [MOVE_MEGAHORN]      = _("MEGAHORN"),
    [MOVE_DRAGON_BREATH] = _("DRAGON BREATH"),
    [MOVE_BATON_PASS]    = _("BATON PASS"),
    [MOVE_ENCORE]        = _("ENCORE"),
    [MOVE_PURSUIT]       = _("PURSUIT"),
    [MOVE_RAPID_SPIN]    = _("RAPID SPIN"),
    [MOVE_SWEET_SCENT]   = _("SWEET SCENT"),
    [MOVE_IRON_TAIL]     = _("IRON TAIL"),
    [MOVE_METAL_CLAW]    = _("METAL CLAW"),
    [MOVE_VITAL_THROW]   = _("VITAL THROW"),
    [MOVE_MORNING_SUN]   = _("MORNING SUN"),
    [MOVE_SYNTHESIS]     = _("SYNTHESIS"),
    [MOVE_MOONLIGHT]     = _("MOONLIGHT"),
    [MOVE_HIDDEN_POWER]  = _("HIDDEN POWER"),
    [MOVE_CROSS_CHOP]    = _("CROSS CHOP"),
    [MOVE_TWISTER]       = _("TWISTER"),
    [MOVE_RAIN_DANCE]    = _("RAIN DANCE"),
    [MOVE_SUNNY_DAY]     = _("SUNNY DAY"),
    [MOVE_CRUNCH]        = _("CRUNCH"),
    [MOVE_MIRROR_COAT]   = _("MIRROR COAT"),
    [MOVE_PSYCH_UP]      = _("PSYCH UP"),
    [MOVE_EXTREME_SPEED] = _("EXTREMESPEED"),
    [MOVE_ANCIENT_POWER] = _("ANCIENT POWER"),
    [MOVE_SHADOW_BALL]   = _("SHADOW BALL"),
    [MOVE_FUTURE_SIGHT]  = _("FUTURE SIGHT"),
    [MOVE_ROCK_SMASH]    = _("ROCK SMASH"),
    [MOVE_WHIRLPOOL]     = _("WHIRLPOOL"),
    [MOVE_BEAT_UP]       = _("BEAT UP"),
    [MOVE_FAKE_OUT]      = _("FAKE OUT"),
    [MOVE_UPROAR]        = _("UPROAR"),
    [MOVE_STOCKPILE]     = _("STOCKPILE"),
    [MOVE_SPIT_UP]       = _("SPIT UP"),
    [MOVE_SWALLOW]       = _("SWALLOW"),
    [MOVE_HEAT_WAVE]     = _("HEAT WAVE"),
    [MOVE_HAIL]          = _("HAIL"),
    [MOVE_TORMENT]       = _("TORMENT"),
    [MOVE_FLATTER]       = _("FLATTER"),
    [MOVE_WILL_O_WISP]   = _("WILL-O-WISP"),
    [MOVE_MEMENTO]       = _("MEMENTO"),
    [MOVE_FACADE]        = _("FACADE"),
    [MOVE_FOCUS_PUNCH]   = _("FOCUS PUNCH"),
    [MOVE_SMELLING_SALT] = _("SMELLING SALT"),
    [MOVE_FOLLOW_ME]     = _("FOLLOW ME"),
    [MOVE_NATURE_POWER]  = _("NATURE POWER"),
    [MOVE_CHARGE]        = _("CHARGE"),
    [MOVE_TAUNT]         = _("TAUNT"),
    [MOVE_HELPING_HAND]  = _("HELPING HAND"),
    [MOVE_TRICK]         = _("TRICK"),
    [MOVE_ROLE_PLAY]     = _("ROLE PLAY"),
    [MOVE_WISH]          = _("WISH"),
    [MOVE_ASSIST]        = _("ASSIST"),
    [MOVE_INGRAIN]       = _("INGRAIN"),
    [MOVE_SUPERPOWER]    = _("SUPERPOWER"),
    [MOVE_MAGIC_COAT]    = _("MAGIC COAT"),
    [MOVE_RECYCLE]       = _("RECYCLE"),
    [MOVE_REVENGE]       = _("REVENGE"),
    [MOVE_BRICK_BREAK]   = _("BRICK BREAK"),
    [MOVE_YAWN]          = _("YAWN"),
    [MOVE_KNOCK_OFF]     = _("KNOCK OFF"),
    [MOVE_ENDEAVOR]      = _("ENDEAVOR"),
    [MOVE_ERUPTION]      = _("ERUPTION"),
    [MOVE_SKILL_SWAP]    = _("SKILL SWAP"),
    [MOVE_IMPRISON]      = _("IMPRISON"),
    [MOVE_REFRESH]       = _("REFRESH"),
    [MOVE_GRUDGE]        = _("GRUDGE"),
    [MOVE_SNATCH]        = _("SNATCH"),
    [MOVE_SECRET_POWER]  = _("SECRET POWER"),
    [MOVE_DIVE]          = _("DIVE"),
    [MOVE_ARM_THRUST]    = _("ARM THRUST"),
    [MOVE_CAMOUFLAGE]    = _("CAMOUFLAGE"),
    [MOVE_TAIL_GLOW]     = _("TAIL GLOW"),
    [MOVE_LUSTER_PURGE]  = _("LUSTER PURGE"),
    [MOVE_MIST_BALL]     = _("MIST BALL"),
    [MOVE_FEATHER_DANCE] = _("FEATHER DANCE"),
    [MOVE_TEETER_DANCE]  = _("TEETER DANCE"),
    [MOVE_BLAZE_KICK]    = _("BLAZE KICK"),
    [MOVE_MUD_SPORT]     = _("MUD SPORT"),
    [MOVE_ICE_BALL]      = _("ICE BALL"),
    [MOVE_NEEDLE_ARM]    = _("NEEDLE ARM"),
    [MOVE_SLACK_OFF]     = _("SLACK OFF"),
    [MOVE_HYPER_VOICE]   = _("HYPER VOICE"),
    [MOVE_POISON_FANG]   = _("POISON FANG"),
    [MOVE_CRUSH_CLAW]    = _("CRUSH CLAW"),
    [MOVE_BLAST_BURN]    = _("BLAST BURN"),
    [MOVE_HYDRO_CANNON]  = _("HYDRO CANNON"),
    [MOVE_METEOR_MASH]   = _("METEOR MASH"),
    [MOVE_ASTONISH]      = _("ASTONISH"),
    [MOVE_WEATHER_BALL]  = _("WEATHER BALL"),
    [MOVE_AROMATHERAPY]  = _("AROMATHERAPY"),
    [MOVE_FAKE_TEARS]    = _("FAKE TEARS"),
    [MOVE_AIR_CUTTER]    = _("AIR CUTTER"),
    [MOVE_OVERHEAT]      = _("OVERHEAT"),
    [MOVE_ODOR_SLEUTH]   = _("ODOR SLEUTH"),
    [MOVE_ROCK_TOMB]     = _("ROCK TOMB"),
    [MOVE_SILVER_WIND]   = _("SILVER WIND"),
    [MOVE_METAL_SOUND]   = _("METAL SOUND"),
    [MOVE_GRASS_WHISTLE] = _("GRASSWHISTLE"),
    [MOVE_TICKLE]        = _("TICKLE"),
    [MOVE_COSMIC_POWER]  = _("COSMIC POWER"),
    [MOVE_WATER_SPOUT]   = _("WATER SPOUT"),
    [MOVE_SIGNAL_BEAM]   = _("SIGNAL BEAM"),
    [MOVE_SHADOW_PUNCH]  = _("SHADOW PUNCH"),
    [MOVE_EXTRASENSORY]  = _("EXTRASENSORY"),
    [MOVE_SKY_UPPERCUT]  = _("SKY UPPERCUT"),
    [MOVE_SAND_TOMB]     = _("SAND TOMB"),
    [MOVE_SHEER_COLD]    = _("SHEER COLD"),
    [MOVE_MUDDY_WATER]   = _("MUDDY WATER"),
    [MOVE_BULLET_SEED]   = _("BULLET SEED"),
    [MOVE_AERIAL_ACE]    = _("AERIAL ACE"),
    [MOVE_ICICLE_SPEAR]  = _("ICICLE SPEAR"),
    [MOVE_IRON_DEFENSE]  = _("IRON DEFENSE"),
    [MOVE_BLOCK]         = _("BLOCK"),
    [MOVE_HOWL]          = _("HOWL"),
    [MOVE_DRAGON_CLAW]   = _("DRAGON CLAW"),
    [MOVE_FRENZY_PLANT]  = _("FRENZY PLANT"),
    [MOVE_BULK_UP]       = _("BULK UP"),
    [MOVE_BOUNCE]        = _("BOUNCE"),
    [MOVE_MUD_SHOT]      = _("MUD SHOT"),
    [MOVE_POISON_TAIL]   = _("POISON TAIL"),
    [MOVE_COVET]         = _("COVET"),
    [MOVE_VOLT_TACKLE]   = _("VOLT TACKLE"),
    [MOVE_MAGICAL_LEAF]  = _("MAGICAL LEAF"),
    [MOVE_WATER_SPORT]   = _("WATER SPORT"),
    [MOVE_CALM_MIND]     = _("CALM MIND"),
    [MOVE_LEAF_BLADE]    = _("LEAF BLADE"),
    [MOVE_DRAGON_DANCE]  = _("DRAGON DANCE"),
    [MOVE_ROCK_BLAST]    = _("ROCK BLAST"),
    [MOVE_SHOCK_WAVE]    = _("SHOCK WAVE"),
    [MOVE_WATER_PULSE]   = _("WATER PULSE"),
    [MOVE_DOOM_DESIRE]   = _("DOOM DESIRE"),
    [MOVE_PSYCHO_BOOST]  = _("PSYCHO BOOST")
};

// ---------------------------------------------------------------------------
// Section 2: Move Description Strings
// ---------------------------------------------------------------------------

const u8 gMoveDescription_Pound[] = _("A physical attack\ndelivered with a\nlong tail or a\nforeleg, etc.");
const u8 gMoveDescription_KarateChop[] = _("The foe is attacked\nwith a sharp chop.\nIt has a high\ncritical-hit ratio.");
const u8 gMoveDescription_DoubleSlap[] = _("The foe is slapped\nrepeatedly, back\nand forth, two to\nfive times.");
const u8 gMoveDescription_CometPunch[] = _("The foe is hit with\na flurry of punches\nthat strike two to\nfive times.");
const u8 gMoveDescription_MegaPunch[] = _("The foe is slugged\nby a punch thrown\nwith muscle-packed\npower.");
const u8 gMoveDescription_PayDay[] = _("Numerous coins are\nhurled at the foe.\nMoney is earned\nafter battle.");
const u8 gMoveDescription_FirePunch[] = _("The foe is punched\nwith a fiery fist.\nIt may leave the\nfoe with a burn.");
const u8 gMoveDescription_IcePunch[] = _("The foe is punched\nwith an icy fist.\nIt may leave the\nfoe frozen.");
const u8 gMoveDescription_ThunderPunch[] = _("The foe is punched\nwith an electrified\nfist. It may leave\nthe foe paralyzed.");
const u8 gMoveDescription_Scratch[] = _("Hard, pointed, and\nsharp claws rake\nthe foe.");
const u8 gMoveDescription_ViceGrip[] = _("Huge, impressive\npincers grip and\nsqueeze the foe.");
const u8 gMoveDescription_Guillotine[] = _("A vicious tearing\nattack with pincers.\nThe foe will faint\nif it hits.");
const u8 gMoveDescription_RazorWind[] = _("Blades of wind hit\nthe foe on the 2nd\nturn. It has a high\ncritical-hit ratio.");
const u8 gMoveDescription_SwordsDance[] = _("A frenetic dance of\nfighting. It sharply\nraises the ATTACK\nstat.");
const u8 gMoveDescription_Cut[] = _("A basic attack.\nIt can be used to\ncut down thin trees\nand grass.");
const u8 gMoveDescription_Gust[] = _("Strikes the foe\nwith a gust of wind\nwhipped up by\nwings.");
const u8 gMoveDescription_WingAttack[] = _("The foe is struck\nwith large, imposing\nwings spread wide.");
const u8 gMoveDescription_Whirlwind[] = _("The foe is made to\nswitch out with an\nally. In the wild,\nthe battle ends.");
const u8 gMoveDescription_Fly[] = _("A 2-turn move that\nhits on the 2nd\nturn. Use it to fly\nto any known town.");
const u8 gMoveDescription_Bind[] = _("A long body or\ntentacles are used\nto bind the foe for\ntwo to five turns.");
const u8 gMoveDescription_Slam[] = _("The foe is struck\nwith a long tail,\nvines, etc.");
const u8 gMoveDescription_VineWhip[] = _("The foe is struck\nwith slender, whip-\nlike vines.");
const u8 gMoveDescription_Stomp[] = _("The foe is stomped\nwith a big foot.\nIt may make the\nfoe flinch.");
const u8 gMoveDescription_DoubleKick[] = _("Two legs are used\nto quickly kick the\nfoe twice in one\nturn.");
const u8 gMoveDescription_MegaKick[] = _("The foe is attacked\nby a kick fired\nwith muscle-packed\npower.");
const u8 gMoveDescription_JumpKick[] = _("The user jumps up\nhigh, then kicks.\nIf it misses, the\nuser hurts itself.");
const u8 gMoveDescription_RollingKick[] = _("A quick kick from a\nrolling spin.\nIt may make the\nfoe flinch.");
const u8 gMoveDescription_SandAttack[] = _("A lot of sand is\nhurled in the foe's\nface, reducing its\naccuracy.");
const u8 gMoveDescription_Headbutt[] = _("The user sticks its\nhead out and rams.\nIt may make the\nfoe flinch.");
const u8 gMoveDescription_HornAttack[] = _("The foe is jabbed\nwith a sharply\npointed horn to\ninflict damage.");
const u8 gMoveDescription_FuryAttack[] = _("The foe is jabbed\nrepeatedly with a\nhorn or beak two to\nfive times.");
const u8 gMoveDescription_HornDrill[] = _("The horn is rotated\nlike a drill to ram.\nThe foe will faint\nif it hits.");
const u8 gMoveDescription_Tackle[] = _("A physical attack\nin which the user\ncharges, full body,\ninto the foe.");
const u8 gMoveDescription_BodySlam[] = _("The user drops its\nfull body on the\nfoe. It may leave\nthe foe paralyzed.");
const u8 gMoveDescription_Wrap[] = _("A long body or\nvines are used to\nwrap the foe for\ntwo to five turns.");
const u8 gMoveDescription_TakeDown[] = _("A reckless, full-\nbody charge attack\nthat also hurts the\nuser a little.");
const u8 gMoveDescription_Thrash[] = _("The user rampages\nabout for two to\nthree turns, then\nbecomes confused.");
const u8 gMoveDescription_DoubleEdge[] = _("A reckless, life-\nrisking tackle that\nalso hurts the user\na little.");
const u8 gMoveDescription_TailWhip[] = _("The user wags its\ntail cutely, making\nthe foe lower its\nDEFENSE stat.");
const u8 gMoveDescription_PoisonSting[] = _("The foe is stabbed\nwith a toxic barb,\netc. It may poison\nthe foe.");
const u8 gMoveDescription_Twineedle[] = _("The foe is stabbed\ntwice with foreleg\nstingers. It may\npoison the foe.");
const u8 gMoveDescription_PinMissile[] = _("Sharp pins are shot\nat the foe and hit\ntwo to five times\nat once.");
const u8 gMoveDescription_Leer[] = _("The foe is given an\nintimidating look\nthat lowers its\nDEFENSE stat.");
const u8 gMoveDescription_Bite[] = _("The user bites with\nvicious fangs.\nIt may make the\nfoe flinch.");
const u8 gMoveDescription_Growl[] = _("The user growls in\na cute way, making\nthe foe lower its\nATTACK stat.");
const u8 gMoveDescription_Roar[] = _("The foe is made to\nswitch out with an\nally. In the wild,\nthe battle ends.");
const u8 gMoveDescription_Sing[] = _("A soothing song\nin a calming voice\nlulls the foe into\na deep slumber.");
const u8 gMoveDescription_Supersonic[] = _("The user generates\nodd sound waves.\nIt may confuse the\nfoe.");
const u8 gMoveDescription_SonicBoom[] = _("The foe is hit with\na shock wave that\nalways inflicts 20-\nHP damage.");
const u8 gMoveDescription_Disable[] = _("For a few turns,\nit prevents the foe\nfrom using the move\nit last used.");
const u8 gMoveDescription_Acid[] = _("The foe is sprayed\nwith a harsh, hide-\nmelting acid that\nmay lower DEFENSE.");
const u8 gMoveDescription_Ember[] = _("The foe is attacked\nwith small flames.\nThe foe may suffer\na burn.");
const u8 gMoveDescription_Flamethrower[] = _("The foe is scorched\nwith intense flames.\nThe foe may suffer\na burn.");
const u8 gMoveDescription_Mist[] = _("The ally party is\nprotected by a\nmist that prevents\nstat reductions.");
const u8 gMoveDescription_WaterGun[] = _("The foe is struck\nwith a lot of water\nexpelled forcibly\nfrom the mouth.");
const u8 gMoveDescription_HydroPump[] = _("A high volume of\nwater is blasted at\nthe foe under great\npressure.");
const u8 gMoveDescription_Surf[] = _("A big wave crashes\ndown on the foe.\nCan also be used\nfor crossing water.");
const u8 gMoveDescription_IceBeam[] = _("The foe is struck\nwith an icy beam.\nIt may freeze the\nfoe solid.");
const u8 gMoveDescription_Blizzard[] = _("The foe is blasted\nwith a blizzard.\nIt may freeze the\nfoe solid.");
const u8 gMoveDescription_Psybeam[] = _("A peculiar ray is\nshot at the foe.\nIt may leave the\nfoe confused.");
const u8 gMoveDescription_BubbleBeam[] = _("A spray of bubbles\nstrikes the foe.\nIt may lower the\nfoe's SPEED stat.");
const u8 gMoveDescription_AuroraBeam[] = _("A rainbow-colored\nattack beam.\nIt may lower the\nfoe's ATTACK stat.");
const u8 gMoveDescription_HyperBeam[] = _("A severely damaging\nattack that makes\nthe user rest on\nthe next turn.");
const u8 gMoveDescription_Peck[] = _("The foe is jabbed\nwith a sharply\npointed beak or\nhorn.");
const u8 gMoveDescription_DrillPeck[] = _("A corkscrewing\nattack with the\nsharp beak acting\nas a drill.");
const u8 gMoveDescription_Submission[] = _("A reckless, full-\nbody throw attack\nthat also hurts the\nuser a little.");
const u8 gMoveDescription_LowKick[] = _("A low, tripping kick\nthat inflicts more\ndamage on heavier\nfoes.");
const u8 gMoveDescription_Counter[] = _("A retaliation move\nthat counters any\nphysical hit with\ndouble the damage.");
const u8 gMoveDescription_SeismicToss[] = _("A gravity-fed throw\nthat causes damage\nmatching the user's\nlevel.");
const u8 gMoveDescription_Strength[] = _("The foe is slugged\nat maximum power.\nCan also be used\nto move boulders.");
const u8 gMoveDescription_Absorb[] = _("An attack that\nabsorbs half the\ndamage it inflicted\nto restore HP.");
const u8 gMoveDescription_MegaDrain[] = _("A tough attack that\ndrains half the\ndamage it inflicted\nto restore HP.");
const u8 gMoveDescription_LeechSeed[] = _("A seed is planted\non the foe to steal\nsome HP for the \nuser on every turn.");
const u8 gMoveDescription_Growth[] = _("The user's body is\nforced to grow,\nraising the SP.\nATK stat.");
const u8 gMoveDescription_RazorLeaf[] = _("The foe is hit with\na cutting leaf.\nIt has a high\ncritical-hit ratio.");
const u8 gMoveDescription_SolarBeam[] = _("A 2-turn move that\nblasts the foe with\nabsorbed energy in\nthe 2nd turn.");
const u8 gMoveDescription_PoisonPowder[] = _("A cloud of toxic\ndust is scattered.\nIt may poison the\nfoe.");
const u8 gMoveDescription_StunSpore[] = _("Paralyzing dust is\nscattered wildly.\nIt may paralyze\nthe foe.");
const u8 gMoveDescription_SleepPowder[] = _("A sleep-inducing\ndust is scattered\nin high volume\naround a foe.");
const u8 gMoveDescription_PetalDance[] = _("The user attacks\nwith petals for two\nto three turns,\nthen gets confused.");
const u8 gMoveDescription_StringShot[] = _("The foe is bound\nwith strings shot\nfrom the mouth to\nreduce its SPEED.");
const u8 gMoveDescription_DragonRage[] = _("The foe is hit with\na shock wave that\nalways inflicts 40-\nHP damage.");
const u8 gMoveDescription_FireSpin[] = _("The foe is trapped\nin an intense spiral\nof fire that rages\ntwo to five turns.");
const u8 gMoveDescription_ThunderShock[] = _("An electric shock\nattack that may\nalso leave the foe\nparalyzed.");
const u8 gMoveDescription_Thunderbolt[] = _("A strong electrical\nattack that may\nalso leave the foe\nparalyzed.");
const u8 gMoveDescription_ThunderWave[] = _("A weak electric\nshock that is sure\nto cause paralysis\nif it hits.");
const u8 gMoveDescription_Thunder[] = _("A brutal lightning\nattack that may\nalso leave the foe\nparalyzed.");
const u8 gMoveDescription_RockThrow[] = _("The foe is attacked\nwith a shower of\nsmall, easily\nthrown rocks.");
const u8 gMoveDescription_Earthquake[] = _("An earthquake that\nstrikes all POKéMON\nin battle excluding\nthe user.");
const u8 gMoveDescription_Fissure[] = _("The foe is dropped\ninto a fissure.\nThe foe faints if it\nhits.");
const u8 gMoveDescription_Dig[] = _("An attack that hits\non the 2nd turn.\nCan also be used\nto exit dungeons.");
const u8 gMoveDescription_Toxic[] = _("A move that badly\npoisons the foe.\nIts poison damage\nworsens every turn.");
const u8 gMoveDescription_Confusion[] = _("A weak telekinetic\nattack that may\nalso leave the foe\nconfused.");
const u8 gMoveDescription_Psychic[] = _("A strong telekinetic\nattack. It may also\nlower the foe's\nSP. DEF stat.");
const u8 gMoveDescription_Hypnosis[] = _("Hypnotic suggestion\nis used to make the\nfoe fall into a\ndeep sleep.");
const u8 gMoveDescription_Meditate[] = _("The user meditates\nto awaken its power\nand raise its\nATTACK stat.");
const u8 gMoveDescription_Agility[] = _("The user relaxes\nand lightens its\nbody to sharply\nboost its SPEED.");
const u8 gMoveDescription_QuickAttack[] = _("An almost invisibly\nfast attack that\nis certain to strike\nfirst.");
const u8 gMoveDescription_Rage[] = _("An attack that\nbecomes stronger\neach time the user\nis hit in battle.");
const u8 gMoveDescription_Teleport[] = _("Use it to flee from\nany wild POKéMON.\nAlso warps to the\nlast POKé CENTER.");
const u8 gMoveDescription_NightShade[] = _("An attack with a\nmirage that inflicts\ndamage matching\nthe user's level.");
const u8 gMoveDescription_Mimic[] = _("The user copies the\nmove last used by\nthe foe for the\nrest of the battle.");
const u8 gMoveDescription_Screech[] = _("An ear-splitting\nscreech is emitted\nto sharply reduce\nthe foe's DEFENSE.");
const u8 gMoveDescription_DoubleTeam[] = _("The user creates\nillusory copies of\nitself to raise its\nevasiveness.");
const u8 gMoveDescription_Recover[] = _("A self-healing move\nthat restores HP by\nup to half of the\nuser's maximum HP.");
const u8 gMoveDescription_Harden[] = _("The user stiffens\nall the muscles in\nits body to raise\nits DEFENSE stat.");
const u8 gMoveDescription_Minimize[] = _("The user compresses\nall the cells in its\nbody to raise its\nevasiveness.");
const u8 gMoveDescription_Smokescreen[] = _("An obscuring cloud\nof smoke or ink\nreduces the foe's\naccuracy.");
const u8 gMoveDescription_ConfuseRay[] = _("The foe is exposed\nto a sinister ray\nthat triggers\nconfusion.");
const u8 gMoveDescription_Withdraw[] = _("The user withdraws\nits body in its hard\nshell, raising its\nDEFENSE stat.");
const u8 gMoveDescription_DefenseCurl[] = _("The user curls up\nto conceal weak\nspots and raise its\nDEFENSE stat.");
const u8 gMoveDescription_Barrier[] = _("The user creates a\nsturdy wall that\nsharply raises its\nDEFENSE stat.");
const u8 gMoveDescription_LightScreen[] = _("A wall of light\ncuts damage from\nSP. ATK attacks\nfor five turns.");
const u8 gMoveDescription_Haze[] = _("Eliminates all stat\nchanges among all\nPOKéMON engaged in\nbattle.");
const u8 gMoveDescription_Reflect[] = _("A wall of light\ncuts damage from\nphysical attacks\nfor five turns.");
const u8 gMoveDescription_FocusEnergy[] = _("The user takes a\ndeep breath and\nfocuses to raise its\ncritical-hit ratio.");
const u8 gMoveDescription_Bide[] = _("The user endures\nattacks for two\nturns, then strikes\nback double.");
const u8 gMoveDescription_Metronome[] = _("Waggles a finger\nand stimulates the\nbrain into using any\nmove at random.");
const u8 gMoveDescription_MirrorMove[] = _("The user counters\nthe move last used\nby the foe with the\nsame move.");
const u8 gMoveDescription_SelfDestruct[] = _("The user blows up\nto inflict severe\ndamage, even\nmaking itself faint.");
const u8 gMoveDescription_EggBomb[] = _("A large egg is\nhurled with great\nforce at the foe to\ninflict damage.");
const u8 gMoveDescription_Lick[] = _("The foe is licked\nand hit with a long\ntongue. It may\nalso paralyze.");
const u8 gMoveDescription_Smog[] = _("The foe is attacked\nwith exhaust gases.\nIt may also poison\nthe foe.");
const u8 gMoveDescription_Sludge[] = _("Toxic sludge is\nhurled at the foe.\nIt may poison the\ntarget.");
const u8 gMoveDescription_BoneClub[] = _("The foe is clubbed\nwith a bone held in\nhand. It may make\nthe foe flinch.");
const u8 gMoveDescription_FireBlast[] = _("The foe is hit with\nan intense flame.\nIt may leave the\ntarget with a burn.");
const u8 gMoveDescription_Waterfall[] = _("A powerful charge\nattack. It can also\nbe used to climb\na waterfall.");
const u8 gMoveDescription_Clamp[] = _("The foe is clamped\nand squeezed by\nthe user's shell for\ntwo to five turns.");
const u8 gMoveDescription_Swift[] = _("Star-shaped rays\nthat never miss are\nfired at all foes in\nbattle.");
const u8 gMoveDescription_SkullBash[] = _("The user raises its\nDEFENSE in the 1st\nturn, then attacks\nin the 2nd turn.");
const u8 gMoveDescription_SpikeCannon[] = _("Sharp spikes are\nfired at the foe to\nstrike two to five\ntimes.");
const u8 gMoveDescription_Constrict[] = _("The foe is attacked\nwith long tentacles\nor vines. It may\nlower SPEED.");
const u8 gMoveDescription_Amnesia[] = _("Forgets about\nsomething and\nsharply raises\nSP. DEF.");
const u8 gMoveDescription_Kinesis[] = _("The user distracts\nthe foe by bending\na spoon. It may\nlower accuracy.");
const u8 gMoveDescription_SoftBoiled[] = _("Heals the user by\nup to half its full\nHP. It can be used\nto heal an ally.");
const u8 gMoveDescription_HiJumpKick[] = _("A strong jumping\nknee kick. If it\nmisses, the user is\nhurt.");
const u8 gMoveDescription_Glare[] = _("The user intimidates\nthe foe with the\ndesign on its belly\nto cause paralysis.");
const u8 gMoveDescription_DreamEater[] = _("Absorbs half the\ndamage it inflicted\non a sleeping foe\nto restore HP.");
const u8 gMoveDescription_PoisonGas[] = _("The foe is sprayed\nwith a cloud of\ntoxic gas that may\npoison the foe.");
const u8 gMoveDescription_Barrage[] = _("Round objects are\nhurled at the foe\nto strike two to\nfive times.");
const u8 gMoveDescription_LeechLife[] = _("An attack that\nabsorbs half the\ndamage it inflicted\nto restore HP.");
const u8 gMoveDescription_LovelyKiss[] = _("The user forces a\nkiss on the foe\nwith a scary face\nthat induces sleep.");
const u8 gMoveDescription_SkyAttack[] = _("A 2nd-turn attack\nmove with a high\ncritical-hit ratio.\nThe foe may flinch.");
const u8 gMoveDescription_Transform[] = _("The user transforms\ninto a copy of the\nfoe with even the\nsame move set.");
const u8 gMoveDescription_Bubble[] = _("A spray of bubbles\nhits the foe.\nIt may lower the\nfoe's SPEED stat.");
const u8 gMoveDescription_DizzyPunch[] = _("The foe is hit with\na rhythmic punch\nthat may leave it\nconfused.");
const u8 gMoveDescription_Spore[] = _("The user scatters\nbursts of fine\nspores that induce\nsleep.");
const u8 gMoveDescription_Flash[] = _("A blast of light\nthat cuts the foe's\naccuracy. It also\nilluminates caves.");
const u8 gMoveDescription_Psywave[] = _("The foe is attacked\nwith an odd, hot\nenergy wave that\nvaries in intensity.");
const u8 gMoveDescription_Splash[] = _("The user just flops\nand splashes around\nwithout having any\neffect.");
const u8 gMoveDescription_AcidArmor[] = _("The user alters its\ncells to liquefy\nitself and sharply\nraise DEFENSE.");
const u8 gMoveDescription_Crabhammer[] = _("A large pincer is\nused to hammer the\nfoe. It has a high\ncritical-hit ratio.");
const u8 gMoveDescription_Explosion[] = _("The user explodes\nto inflict terrible\ndamage even while\nfainting itself.");
const u8 gMoveDescription_FurySwipes[] = _("The foe is raked\nwith sharp claws or\nscythes two to five\ntimes.");
const u8 gMoveDescription_Bonemerang[] = _("The user throws a\nbone that hits the\nfoe once, then once\nagain on return.");
const u8 gMoveDescription_Rest[] = _("The user sleeps for\ntwo turns to fully\nrestore HP and heal\nany status problem.");
const u8 gMoveDescription_RockSlide[] = _("Large boulders are\nhurled at the foe.\nIt may make the\nfoe flinch.");
const u8 gMoveDescription_HyperFang[] = _("The foe is attacked\nwith sharp fangs.\nIt may make the\nfoe flinch.");
const u8 gMoveDescription_Sharpen[] = _("The user reduces\nits polygon count\nto sharpen edges\nand raise ATTACK.");
const u8 gMoveDescription_Conversion[] = _("The user changes\nits type to match\nthe type of one of\nits moves.");
const u8 gMoveDescription_TriAttack[] = _("A simultaneous\n3-beam attack that\nmay paralyze, burn,\nor freeze the foe.");
const u8 gMoveDescription_SuperFang[] = _("The user attacks\nwith sharp fangs\nand halves the\nfoe's HP.");
const u8 gMoveDescription_Slash[] = _("The foe is slashed\nwith claws, etc.\nIt has a high\ncritical-hit ratio.");
const u8 gMoveDescription_Substitute[] = _("The user creates a\ndecoy using one-\nquarter of its full\nHP.");
const u8 gMoveDescription_Struggle[] = _("An attack that is\nused only if there\nis no PP. It also\nhurts the user.");
const u8 gMoveDescription_Sketch[] = _("This move copies\nthe move last used\nby the foe, then\ndisappears.");
const u8 gMoveDescription_TripleKick[] = _("A 3-kick attack\nthat becomes more\npowerful with each\nsuccessive hit.");
const u8 gMoveDescription_Thief[] = _("An attack that may\ntake the foe's held\nitem if the user\nisn't holding one.");
const u8 gMoveDescription_SpiderWeb[] = _("Ensnares the foe \nwith sticky string\nso it doesn't flee\nor switch out.");
const u8 gMoveDescription_MindReader[] = _("The user predicts\nthe foe's action to\nensure its next\nattack hits.");
const u8 gMoveDescription_Nightmare[] = _("A sleeping foe is\nshown a nightmare\nthat inflicts some\ndamage every turn.");
const u8 gMoveDescription_FlameWheel[] = _("The user makes a\nfiery charge at the\nfoe. It may cause\na burn.");
const u8 gMoveDescription_Snore[] = _("An attack that can\nbe used only while\nasleep. It may\ncause flinching.");
const u8 gMoveDescription_Curse[] = _("A move that works\ndifferently for the\nGHOST-type and all\nthe other types.");
const u8 gMoveDescription_Flail[] = _("A desperate attack\nthat becomes more\npowerful the less\nHP the user has.");
const u8 gMoveDescription_Conversion2[] = _("The user changes\ntype to make itself\nresistant to the\nlast attack it took.");
const u8 gMoveDescription_Aeroblast[] = _("A vortex of air is\nshot at the foe.\nIt has a high\ncritical-hit ratio.");
const u8 gMoveDescription_CottonSpore[] = _("Cotton-like spores\ncling to the foe,\nsharply reducing\nits SPEED stat.");
const u8 gMoveDescription_Reversal[] = _("An all-out attack\nthat becomes more\npowerful the less\nHP the user has.");
const u8 gMoveDescription_Spite[] = _("A move that cuts\n2 to 5 PP from the\nmove last used by\nthe foe.");
const u8 gMoveDescription_PowderSnow[] = _("Blasts the foe with\na snowy gust.\nIt may cause\nfreezing.");
const u8 gMoveDescription_Protect[] = _("Enables the user to\nevade all attacks.\nIt may fail if used\nin succession.");
const u8 gMoveDescription_MachPunch[] = _("A punch thrown at\nblinding speed.\nIt is certain to\nstrike first.");
const u8 gMoveDescription_ScaryFace[] = _("Frightens the foe\nwith a scary face\nto sharply reduce\nits SPEED.");
const u8 gMoveDescription_FeintAttack[] = _("The user draws up\nclose to the foe\ndisarmingly, then\nhits without fail.");
const u8 gMoveDescription_SweetKiss[] = _("The user kisses\nthe foe with sweet\ncuteness that\ncauses confusion.");
const u8 gMoveDescription_BellyDrum[] = _("The user maximizes\nits ATTACK stat at\nthe cost of half\nits full HP.");
const u8 gMoveDescription_SludgeBomb[] = _("Filthy sludge is\nhurled at the foe.\nIt may poison the\ntarget.");
const u8 gMoveDescription_MudSlap[] = _("Mud is hurled in\nthe foe's face to\ninflict damage and\nlower its accuracy.");
const u8 gMoveDescription_Octazooka[] = _("Ink is blasted in\nthe foe's face or\neyes to damage and\nlower accuracy.");
const u8 gMoveDescription_Spikes[] = _("A trap of spikes is\nlaid around the\nfoe's party to hurt\nfoes switching in.");
const u8 gMoveDescription_ZapCannon[] = _("An electric blast is\nfired like a cannon\nto inflict damage\nand paralyze.");
const u8 gMoveDescription_Foresight[] = _("Completely negates\nthe foe's efforts to\nheighten its ability\nto evade.");
const u8 gMoveDescription_DestinyBond[] = _("If the user faints,\nthe foe delivering\nthe final hit also\nfaints.");
const u8 gMoveDescription_PerishSong[] = _("Any battler that\nhears this faints\nin three turns\nunless it switches.");
const u8 gMoveDescription_IcyWind[] = _("A chilling wind is\nused to attack.\nIt also lowers the\nSPEED stat.");
const u8 gMoveDescription_Detect[] = _("Enables the user to\nevade all attacks.\nIt may fail if used\nin succession.");
const u8 gMoveDescription_BoneRush[] = _("The user strikes\nthe foe with a bone\nin hand two to five\ntimes.");
const u8 gMoveDescription_LockOn[] = _("The user locks on\nto the foe, making\nthe next move sure\nto hit.");
const u8 gMoveDescription_Outrage[] = _("The user thrashes\nabout for two to\nthree turns, then\nbecomes confused.");
const u8 gMoveDescription_Sandstorm[] = _("A 5-turn sandstorm\nthat damages all\ntypes except ROCK,\nGROUND, and STEEL.");
const u8 gMoveDescription_GigaDrain[] = _("A harsh attack that\nabsorbs half the\ndamage it inflicted\nto restore HP.");
const u8 gMoveDescription_Endure[] = _("The user endures\nany hit with 1 HP\nleft. It may fail if\nused in succession.");
const u8 gMoveDescription_Charm[] = _("The foe is charmed\nby the user's cute\nappeals, sharply\ncutting its ATTACK.");
const u8 gMoveDescription_Rollout[] = _("A 5-turn rolling\nattack that becomes\nstronger each time\nit hits.");
const u8 gMoveDescription_FalseSwipe[] = _("A restrained attack\nthat always leaves\nthe foe with at\nleast 1 HP.");
const u8 gMoveDescription_Swagger[] = _("A move that makes\nthe foe confused,\nbut also sharply\nraises its ATTACK.");
const u8 gMoveDescription_MilkDrink[] = _("Heals the user by\nup to half its full\nHP. It can be used\nto heal an ally.");
const u8 gMoveDescription_Spark[] = _("An electrically\ncharged tackle that\nmay also paralyze\nthe foe.");
const u8 gMoveDescription_FuryCutter[] = _("An attack that\ngrows stronger on\neach successive\nhit.");
const u8 gMoveDescription_SteelWing[] = _("The foe is hit with\nwings of steel.\nIt may also raise\nthe user's DEFENSE.");
const u8 gMoveDescription_MeanLook[] = _("The foe is fixed\nwith a mean look\nthat prevents it\nfrom escaping.");
const u8 gMoveDescription_Attract[] = _("If it is the other\ngender, the foe is\nmade infatuated and\nunlikely to attack.");
const u8 gMoveDescription_SleepTalk[] = _("While asleep, the\nuser randomly uses\none of the moves it\nknows.");
const u8 gMoveDescription_HealBell[] = _("A soothing bell\nchimes to heal the\nstatus problems of\nall allies.");
const u8 gMoveDescription_Return[] = _("This attack move\ngrows more powerful\nthe more the user\nlikes its TRAINER.");
const u8 gMoveDescription_Present[] = _("The foe is given a\nbooby-trapped gift.\nIt restores HP\nsometimes, however.");
const u8 gMoveDescription_Frustration[] = _("This attack move\ngrows more powerful\nthe less the user\nlikes its TRAINER.");
const u8 gMoveDescription_Safeguard[] = _("It protects the\nuser's party from\nall status problems\nfor five turns.");
const u8 gMoveDescription_PainSplit[] = _("The user adds its\nHP to the foe's HP,\nthen equally shares\nthe total HP.");
const u8 gMoveDescription_SacredFire[] = _("A mystical and\npowerful fire\nattack that may\ninflict a burn.");
const u8 gMoveDescription_Magnitude[] = _("A ground-shaking\nattack against all\nstanding POKéMON.\nIts power varies.");
const u8 gMoveDescription_DynamicPunch[] = _("The foe is punched\nwith the user's full\npower. It confuses\nthe foe if it hits.");
const u8 gMoveDescription_Megahorn[] = _("A brutal ramming\nattack delivered\nwith a tough and\nimpressive horn.");
const u8 gMoveDescription_DragonBreath[] = _("The foe is hit with\nan incredible blast\nof breath that may\nalso paralyze.");
const u8 gMoveDescription_BatonPass[] = _("The user switches\nout, passing along\nany stat changes\nto the new battler.");
const u8 gMoveDescription_Encore[] = _("Makes the foe use\nthe move it last\nused repeatedly for\ntwo to six turns.");
const u8 gMoveDescription_Pursuit[] = _("An attack move that\nworks especially\nwell on a foe that\nis switching out.");
const u8 gMoveDescription_RapidSpin[] = _("An attack that\nfrees the user from\nBIND, WRAP, LEECH\nSEED, and SPIKES.");
const u8 gMoveDescription_SweetScent[] = _("Allures the foe to\nreduce evasiveness.\nIt also attracts\nwild POKéMON.");
const u8 gMoveDescription_IronTail[] = _("An attack with a\nsteel-hard tail.\nIt may lower the\nfoe's DEFENSE stat.");
const u8 gMoveDescription_MetalClaw[] = _("The foe is attacked\nwith steel claws.\nIt may also raise\nthe user's ATTACK.");
const u8 gMoveDescription_VitalThrow[] = _("Makes the user\nattack after the\nfoe. In return,\nit will not miss.");
const u8 gMoveDescription_MorningSun[] = _("Restores the user's\nHP. The amount of\nHP regained varies\nwith the weather.");
const u8 gMoveDescription_Synthesis[] = _("Restores the user's\nHP. The amount of\nHP regained varies\nwith the weather.");
const u8 gMoveDescription_Moonlight[] = _("Restores the user's\nHP. The amount of\nHP regained varies\nwith the weather.");
const u8 gMoveDescription_HiddenPower[] = _("An attack that\nvaries in type and\nintensity depending\non the user.");
const u8 gMoveDescription_CrossChop[] = _("The foe is hit with\ndouble chops.\nIt has a high\ncritical-hit ratio.");
const u8 gMoveDescription_Twister[] = _("A vicious twister\nattacks the foe.\nIt may make the\nfoe flinch.");
const u8 gMoveDescription_RainDance[] = _("A heavy rain falls\nfor five turns,\npowering up WATER-\ntype moves.");
const u8 gMoveDescription_SunnyDay[] = _("The sun blazes for\nfive turns, powering\nup FIRE-type\nmoves.");
const u8 gMoveDescription_Crunch[] = _("The foe is crunched\nwith sharp fangs.\nIt may lower the\nfoe's SP. DEF.");
const u8 gMoveDescription_MirrorCoat[] = _("A retaliation move\nthat pays back the\nfoe's special attack\ndouble.");
const u8 gMoveDescription_PsychUp[] = _("The user hypnotizes\nitself into copying\nany stat change\nmade by the foe.");
const u8 gMoveDescription_ExtremeSpeed[] = _("A blindingly speedy\ncharge attack that\nalways goes before\nany other.");
const u8 gMoveDescription_AncientPower[] = _("An ancient power is\nused to attack. It\nmay also raise all\nthe user's stats.");
const u8 gMoveDescription_ShadowBall[] = _("A shadowy blob is\nhurled at the foe.\nMay also lower the\nfoe's SP. DEF.");
const u8 gMoveDescription_FutureSight[] = _("Two turns after\nthis move is used,\nthe foe is attacked\npsychically.");
const u8 gMoveDescription_RockSmash[] = _("An attack that may\nalso cut DEFENSE.\nIt can also smash\ncracked boulders.");
const u8 gMoveDescription_Whirlpool[] = _("The foe is trapped\nin a fast, vicious\nwhirlpool for two\nto five turns.");
const u8 gMoveDescription_BeatUp[] = _("All party POKéMON\njoin in the attack.\nThe more allies,\nthe more damage.");
const u8 gMoveDescription_FakeOut[] = _("An attack that hits\nfirst and causes\nflinching. Usable\nonly on 1st turn.");
const u8 gMoveDescription_Uproar[] = _("The user attacks in\nan uproar that\nprevents sleep for\ntwo to five turns.");
const u8 gMoveDescription_Stockpile[] = _("The user charges\nup power for use\nlater. It can be\nused three times.");
const u8 gMoveDescription_SpitUp[] = _("The power built\nusing STOCKPILE is\nreleased at once\nfor attack.");
const u8 gMoveDescription_Swallow[] = _("The energy it built\nusing STOCKPILE is\nabsorbed to restore\nHP.");
const u8 gMoveDescription_HeatWave[] = _("The user exhales a\nheated breath to\nattack. It may also\ninflict a burn.");
const u8 gMoveDescription_Hail[] = _("A hailstorm lasting\nfive turns damages\nall POKéMON except\nthe ICE-type.");
const u8 gMoveDescription_Torment[] = _("It enrages the foe,\nmaking it incapable\nof using the same\nmove successively.");
const u8 gMoveDescription_Flatter[] = _("Flattery is used to\nconfuse the foe,\nbut its SP. ATK\nalso rises.");
const u8 gMoveDescription_WillOWisp[] = _("A sinister, bluish\nwhite flame is shot\nat the foe to\ninflict a burn.");
const u8 gMoveDescription_Memento[] = _("The user faints,\nbut sharply lowers\nthe foe's ATTACK\nand SP. ATK.");
const u8 gMoveDescription_Facade[] = _("An attack that is\nboosted if user is\nburned, poisoned,\nor paralyzed.");
const u8 gMoveDescription_FocusPunch[] = _("An attack that is\nexecuted last.\nThe user flinches\nif hit beforehand.");
const u8 gMoveDescription_SmellingSalt[] = _("Doubly effective on\na paralyzed foe,\nbut it also cures\nthe foe's paralysis.");
const u8 gMoveDescription_FollowMe[] = _("The user draws\nattention to itself,\nmaking foes attack\nonly the user.");
const u8 gMoveDescription_NaturePower[] = _("An attack that\nchanges type\ndepending on the\nuser's location.");
const u8 gMoveDescription_Charge[] = _("The user charges\npower to boost the\nELECTRIC move it\nuses next.");
const u8 gMoveDescription_Taunt[] = _("The foe is taunted\ninto a rage that\nallows it to use\nonly attack moves.");
const u8 gMoveDescription_HelpingHand[] = _("A move that boosts\nthe power of the\nally's attack in a\nbattle.");
const u8 gMoveDescription_Trick[] = _("A move that tricks\nthe foe into\ntrading held items\nwith the user.");
const u8 gMoveDescription_RolePlay[] = _("The user mimics the\nfoe completely and\ncopies the foe's\nability.");
const u8 gMoveDescription_Wish[] = _("A self-healing move\nthat restores half\nthe full HP on the\nnext turn.");
const u8 gMoveDescription_Assist[] = _("The user randomly\npicks and uses a\nmove of an allied\nPOKéMON.");
const u8 gMoveDescription_Ingrain[] = _("The user lays roots\nthat restore HP on\nevery turn.\nIt can't switch out.");
const u8 gMoveDescription_Superpower[] = _("A powerful attack,\nbut it also lowers\nthe user's ATTACK\nand DEFENSE stats.");
const u8 gMoveDescription_MagicCoat[] = _("Reflects back the\nfoe's LEECH SEED\nand any status-\ndamaging move.");
const u8 gMoveDescription_Recycle[] = _("A move that\nrecycles a used\nitem for use once\nmore.");
const u8 gMoveDescription_Revenge[] = _("An attack move that\ngains in intensity if\nthe target has hurt\nthe user.");
const u8 gMoveDescription_BrickBreak[] = _("An attack that also\nbreaks any barrier\nlike LIGHT SCREEN\nand REFLECT.");
const u8 gMoveDescription_Yawn[] = _("A huge yawn lulls\nthe foe into falling\nasleep on the next\nturn.");
const u8 gMoveDescription_KnockOff[] = _("Knocks down the\nfoe's held item to\nprevent its use\nduring the battle.");
const u8 gMoveDescription_Endeavor[] = _("Gains power the\nfewer HP the user\nhas compared with\nthe foe.");
const u8 gMoveDescription_Eruption[] = _("The higher the\nuser's HP, the more\npowerful this\nattack becomes.");
const u8 gMoveDescription_SkillSwap[] = _("The user employs\nits psychic power\nto swap abilities\nwith the foe.");
const u8 gMoveDescription_Imprison[] = _("Prevents foes from\nusing any move\nthat is also known\nby the user.");
const u8 gMoveDescription_Refresh[] = _("A self-healing move\nthat cures the user\nof a poisoning,\nburn, or paralysis.");
const u8 gMoveDescription_Grudge[] = _("If the user faints,\nthis move deletes\nthe PP of the move\nthat finished it.");
const u8 gMoveDescription_Snatch[] = _("Steals the effects\nof the foe's\nhealing or status-\nchanging move.");
const u8 gMoveDescription_SecretPower[] = _("An attack that may\nhave an additional\neffect that varies\nwith the terrain.");
const u8 gMoveDescription_Dive[] = _("The user dives\nunderwater on the\nfirst turn and\nstrikes next turn.");
const u8 gMoveDescription_ArmThrust[] = _("A quick flurry of\nstraight-arm\npunches that hit\ntwo to five times.");
const u8 gMoveDescription_Camouflage[] = _("Alters the user's\ntype depending on\nthe location's\nterrain.");
const u8 gMoveDescription_TailGlow[] = _("The user flashes a\nlight that sharply\nraises its SP. ATK\nstat.");
const u8 gMoveDescription_LusterPurge[] = _("A burst of light\ninjures the foe. It\nmay also lower the\nfoe's SP. DEF.");
const u8 gMoveDescription_MistBall[] = _("A flurry of down\nhits the foe. It\nmay also lower the\nfoe's SP. ATK.");
const u8 gMoveDescription_FeatherDance[] = _("The foe is covered\nwith a mass of down\nthat sharply cuts\nthe ATTACK stat.");
const u8 gMoveDescription_TeeterDance[] = _("A wobbly dance\nthat confuses all\nthe POKéMON in\nbattle.");
const u8 gMoveDescription_BlazeKick[] = _("A fiery kick with a\nhigh critical-hit\nratio. It may also\nburn the foe.");
const u8 gMoveDescription_MudSport[] = _("Weakens ELECTRIC-\ntype attacks while\nthe user is in the\nbattle.");
const u8 gMoveDescription_IceBall[] = _("A 5-turn rolling\nattack that becomes\nstronger each time\nit rolls.");
const u8 gMoveDescription_NeedleArm[] = _("An attack using\nthorny arms.\nIt may make the\nfoe flinch.");
const u8 gMoveDescription_SlackOff[] = _("The user slacks off\nand restores its HP\nby half its full\nHP.");
const u8 gMoveDescription_HyperVoice[] = _("The user lets loose\na horribly loud\nshout with the\npower to damage.");
const u8 gMoveDescription_PoisonFang[] = _("The foe is bitten\nwith toxic fangs.\nIt may also badly\npoison the foe.");
const u8 gMoveDescription_CrushClaw[] = _("The foe is attacked\nwith sharp claws.\nIt may also lower\nthe foe's DEFENSE.");
const u8 gMoveDescription_BlastBurn[] = _("The foe is hit with\na huge explosion.\nThe user can't move\non the next turn.");
const u8 gMoveDescription_HydroCannon[] = _("The foe is hit with\na watery cannon.\nThe user can't move\non the next turn.");
const u8 gMoveDescription_MeteorMash[] = _("The foe is hit with\na hard, fast punch.\nIt may also raise\nthe user's ATTACK.");
const u8 gMoveDescription_Astonish[] = _("An attack using a\nstartling shout.\nIt also may make\nthe foe flinch.");
const u8 gMoveDescription_WeatherBall[] = _("An attack that\nvaries in power and\ntype depending on\nthe weather.");
const u8 gMoveDescription_Aromatherapy[] = _("A soothing scent is\nreleased to heal\nall status problems\nin the user's party.");
const u8 gMoveDescription_FakeTears[] = _("The user feigns\ncrying to sharply\nlower the foe's\nSP. DEF stat.");
const u8 gMoveDescription_AirCutter[] = _("The foe is hit with\nrazor-like wind.\nIt has a high\ncritical-hit ratio.");
const u8 gMoveDescription_Overheat[] = _("An intense attack\nthat also sharply\nreduces the user's\nSP. ATK stat.");
const u8 gMoveDescription_OdorSleuth[] = _("Completely negates\nthe foe's efforts to\nheighten its ability\nto evade.");
const u8 gMoveDescription_RockTomb[] = _("Boulders are hurled\nat the foe. It also\nlowers the foe's\nSPEED if it hits.");
const u8 gMoveDescription_SilverWind[] = _("The foe is attacked\nwith a silver dust.\nIt may raise all\nthe user's stats.");
const u8 gMoveDescription_MetalSound[] = _("A horrible metallic\nscreech is used to\nsharply lower the\nfoe's SP. DEF.");
const u8 gMoveDescription_GrassWhistle[] = _("A pleasant melody\nis played to lull\nthe foe into a deep\nsleep.");
const u8 gMoveDescription_Tickle[] = _("The foe is made to\nlaugh, reducing its\nATTACK and DEFENSE\nstats.");
const u8 gMoveDescription_CosmicPower[] = _("The user absorbs a\nmystic power to\nraise its DEFENSE\nand SP. DEF.");
const u8 gMoveDescription_WaterSpout[] = _("The higher the\nuser's HP, the more\npowerful this\nattack becomes.");
const u8 gMoveDescription_SignalBeam[] = _("The foe is hit with\na flashing beam\nthat may also\ncause confusion.");
const u8 gMoveDescription_ShadowPunch[] = _("The user throws a\npunch from the\nshadows. It cannot\nbe evaded.");
const u8 gMoveDescription_Extrasensory[] = _("The user attacks\nwith an odd power\nthat may make the\nfoe flinch.");
const u8 gMoveDescription_SkyUppercut[] = _("The user attacks\nwith an uppercut\nthrown skywards\nwith force.");
const u8 gMoveDescription_SandTomb[] = _("The foe is trapped\ninside a painful\nsandstorm for two\nto five turns.");
const u8 gMoveDescription_SheerCold[] = _("The foe is attacked\nwith ultimate cold\nthat causes fainting\nif it hits.");
const u8 gMoveDescription_MuddyWater[] = _("The user attacks\nwith muddy water.\nIt may also lower\nthe foe's accuracy.");
const u8 gMoveDescription_BulletSeed[] = _("The user shoots\nseeds at the foe.\nTwo to five seeds\nare shot at once.");
const u8 gMoveDescription_AerialAce[] = _("An extremely fast\nattack against one\ntarget. It can't be\nevaded.");
const u8 gMoveDescription_IcicleSpear[] = _("Sharp icicles are\nfired at the foe.\nIt strikes two to\nfive times.");
const u8 gMoveDescription_IronDefense[] = _("The user hardens\nits body's surface\nto sharply raise its\nDEFENSE stat.");
const u8 gMoveDescription_Block[] = _("The user blocks the\nfoe's way with arms\nspread wide to\nprevent escape.");
const u8 gMoveDescription_Howl[] = _("The user howls to\nraise its spirit and\nboost its ATTACK\nstat.");
const u8 gMoveDescription_DragonClaw[] = _("Sharp, huge claws\nhook and slash the\nfoe quickly and\nwith great power.");
const u8 gMoveDescription_FrenzyPlant[] = _("The foe is hit with\nan enormous branch.\nThe user can't move\non the next turn.");
const u8 gMoveDescription_BulkUp[] = _("The user bulks up\nits body to boost\nboth its ATTACK and\nDEFENSE stats.");
const u8 gMoveDescription_Bounce[] = _("The user bounces\non the foe on the\n2nd turn. It may\nparalyze the foe.");
const u8 gMoveDescription_MudShot[] = _("The user attacks by\nhurling mud.\nIt also reduces the\nfoe's SPEED.");
const u8 gMoveDescription_PoisonTail[] = _("An attack with a\nhigh critical-hit\nratio. It may also\npoison the foe.");
const u8 gMoveDescription_Covet[] = _("A cutely executed\nattack that also\nsteals the foe's\nhold item.");
const u8 gMoveDescription_VoltTackle[] = _("The user throws an\nelectrified tackle.\nIt hurts the user\na little.");
const u8 gMoveDescription_MagicalLeaf[] = _("The foe is attacked\nwith a strange leaf\nthat cannot be\nevaded.");
const u8 gMoveDescription_WaterSport[] = _("Weakens FIRE-type\nattacks while the\nuser is in the\nbattle.");
const u8 gMoveDescription_CalmMind[] = _("The user focuses\nits mind to raise\nthe SP. ATK and\nSP. DEF stats.");
const u8 gMoveDescription_LeafBlade[] = _("The foe is slashed\nwith a sharp leaf.\nIt has a high\ncritical-hit ratio.");
const u8 gMoveDescription_DragonDance[] = _("A mystic, powerful\ndance that boosts\nthe user's ATTACK\nand SPEED stats.");
const u8 gMoveDescription_RockBlast[] = _("The user hurls two\nto five hard rocks\nat the foe to\nattack.");
const u8 gMoveDescription_ShockWave[] = _("A rapid jolt of\nelectricity strikes\nthe foe. It can't\nbe evaded.");
const u8 gMoveDescription_WaterPulse[] = _("An attack with a\npulsing blast of\nwater. It may also\nconfuse the foe.");
const u8 gMoveDescription_DoomDesire[] = _("A move that attacks\nthe foe with a\nblast of light two\nturns after use.");
const u8 gMoveDescription_PsychoBoost[] = _("An intense attack\nthat also sharply\nreduces the user's\nSP. ATK stat.");

// ---------------------------------------------------------------------------
// Section 3: Move Description Pointer Table
// ---------------------------------------------------------------------------

const u8 *const gMoveDescriptionPointers[MOVES_COUNT - 1] = {
    [MOVE_POUND         - 1] = gMoveDescription_Pound,
    [MOVE_KARATE_CHOP   - 1] = gMoveDescription_KarateChop,
    [MOVE_DOUBLE_SLAP   - 1] = gMoveDescription_DoubleSlap,
    [MOVE_COMET_PUNCH   - 1] = gMoveDescription_CometPunch,
    [MOVE_MEGA_PUNCH    - 1] = gMoveDescription_MegaPunch,
    [MOVE_PAY_DAY       - 1] = gMoveDescription_PayDay,
    [MOVE_FIRE_PUNCH    - 1] = gMoveDescription_FirePunch,
    [MOVE_ICE_PUNCH     - 1] = gMoveDescription_IcePunch,
    [MOVE_THUNDER_PUNCH - 1] = gMoveDescription_ThunderPunch,
    [MOVE_SCRATCH       - 1] = gMoveDescription_Scratch,
    [MOVE_VICE_GRIP     - 1] = gMoveDescription_ViceGrip,
    [MOVE_GUILLOTINE    - 1] = gMoveDescription_Guillotine,
    [MOVE_RAZOR_WIND    - 1] = gMoveDescription_RazorWind,
    [MOVE_SWORDS_DANCE  - 1] = gMoveDescription_SwordsDance,
    [MOVE_CUT           - 1] = gMoveDescription_Cut,
    [MOVE_GUST          - 1] = gMoveDescription_Gust,
    [MOVE_WING_ATTACK   - 1] = gMoveDescription_WingAttack,
    [MOVE_WHIRLWIND     - 1] = gMoveDescription_Whirlwind,
    [MOVE_FLY           - 1] = gMoveDescription_Fly,
    [MOVE_BIND          - 1] = gMoveDescription_Bind,
    [MOVE_SLAM          - 1] = gMoveDescription_Slam,
    [MOVE_VINE_WHIP     - 1] = gMoveDescription_VineWhip,
    [MOVE_STOMP         - 1] = gMoveDescription_Stomp,
    [MOVE_DOUBLE_KICK   - 1] = gMoveDescription_DoubleKick,
    [MOVE_MEGA_KICK     - 1] = gMoveDescription_MegaKick,
    [MOVE_JUMP_KICK     - 1] = gMoveDescription_JumpKick,
    [MOVE_ROLLING_KICK  - 1] = gMoveDescription_RollingKick,
    [MOVE_SAND_ATTACK   - 1] = gMoveDescription_SandAttack,
    [MOVE_HEADBUTT      - 1] = gMoveDescription_Headbutt,
    [MOVE_HORN_ATTACK   - 1] = gMoveDescription_HornAttack,
    [MOVE_FURY_ATTACK   - 1] = gMoveDescription_FuryAttack,
    [MOVE_HORN_DRILL    - 1] = gMoveDescription_HornDrill,
    [MOVE_TACKLE        - 1] = gMoveDescription_Tackle,
    [MOVE_BODY_SLAM     - 1] = gMoveDescription_BodySlam,
    [MOVE_WRAP          - 1] = gMoveDescription_Wrap,
    [MOVE_TAKE_DOWN     - 1] = gMoveDescription_TakeDown,
    [MOVE_THRASH        - 1] = gMoveDescription_Thrash,
    [MOVE_DOUBLE_EDGE   - 1] = gMoveDescription_DoubleEdge,
    [MOVE_TAIL_WHIP     - 1] = gMoveDescription_TailWhip,
    [MOVE_POISON_STING  - 1] = gMoveDescription_PoisonSting,
    [MOVE_TWINEEDLE     - 1] = gMoveDescription_Twineedle,
    [MOVE_PIN_MISSILE   - 1] = gMoveDescription_PinMissile,
    [MOVE_LEER          - 1] = gMoveDescription_Leer,
    [MOVE_BITE          - 1] = gMoveDescription_Bite,
    [MOVE_GROWL         - 1] = gMoveDescription_Growl,
    [MOVE_ROAR          - 1] = gMoveDescription_Roar,
    [MOVE_SING          - 1] = gMoveDescription_Sing,
    [MOVE_SUPERSONIC    - 1] = gMoveDescription_Supersonic,
    [MOVE_SONIC_BOOM    - 1] = gMoveDescription_SonicBoom,
    [MOVE_DISABLE       - 1] = gMoveDescription_Disable,
    [MOVE_ACID          - 1] = gMoveDescription_Acid,
    [MOVE_EMBER         - 1] = gMoveDescription_Ember,
    [MOVE_FLAMETHROWER  - 1] = gMoveDescription_Flamethrower,
    [MOVE_MIST          - 1] = gMoveDescription_Mist,
    [MOVE_WATER_GUN     - 1] = gMoveDescription_WaterGun,
    [MOVE_HYDRO_PUMP    - 1] = gMoveDescription_HydroPump,
    [MOVE_SURF          - 1] = gMoveDescription_Surf,
    [MOVE_ICE_BEAM      - 1] = gMoveDescription_IceBeam,
    [MOVE_BLIZZARD      - 1] = gMoveDescription_Blizzard,
    [MOVE_PSYBEAM       - 1] = gMoveDescription_Psybeam,
    [MOVE_BUBBLE_BEAM   - 1] = gMoveDescription_BubbleBeam,
    [MOVE_AURORA_BEAM   - 1] = gMoveDescription_AuroraBeam,
    [MOVE_HYPER_BEAM    - 1] = gMoveDescription_HyperBeam,
    [MOVE_PECK          - 1] = gMoveDescription_Peck,
    [MOVE_DRILL_PECK    - 1] = gMoveDescription_DrillPeck,
    [MOVE_SUBMISSION    - 1] = gMoveDescription_Submission,
    [MOVE_LOW_KICK      - 1] = gMoveDescription_LowKick,
    [MOVE_COUNTER       - 1] = gMoveDescription_Counter,
    [MOVE_SEISMIC_TOSS  - 1] = gMoveDescription_SeismicToss,
    [MOVE_STRENGTH      - 1] = gMoveDescription_Strength,
    [MOVE_ABSORB        - 1] = gMoveDescription_Absorb,
    [MOVE_MEGA_DRAIN    - 1] = gMoveDescription_MegaDrain,
    [MOVE_LEECH_SEED    - 1] = gMoveDescription_LeechSeed,
    [MOVE_GROWTH        - 1] = gMoveDescription_Growth,
    [MOVE_RAZOR_LEAF    - 1] = gMoveDescription_RazorLeaf,
    [MOVE_SOLAR_BEAM    - 1] = gMoveDescription_SolarBeam,
    [MOVE_POISON_POWDER - 1] = gMoveDescription_PoisonPowder,
    [MOVE_STUN_SPORE    - 1] = gMoveDescription_StunSpore,
    [MOVE_SLEEP_POWDER  - 1] = gMoveDescription_SleepPowder,
    [MOVE_PETAL_DANCE   - 1] = gMoveDescription_PetalDance,
    [MOVE_STRING_SHOT   - 1] = gMoveDescription_StringShot,
    [MOVE_DRAGON_RAGE   - 1] = gMoveDescription_DragonRage,
    [MOVE_FIRE_SPIN     - 1] = gMoveDescription_FireSpin,
    [MOVE_THUNDER_SHOCK - 1] = gMoveDescription_ThunderShock,
    [MOVE_THUNDERBOLT   - 1] = gMoveDescription_Thunderbolt,
    [MOVE_THUNDER_WAVE  - 1] = gMoveDescription_ThunderWave,
    [MOVE_THUNDER       - 1] = gMoveDescription_Thunder,
    [MOVE_ROCK_THROW    - 1] = gMoveDescription_RockThrow,
    [MOVE_EARTHQUAKE    - 1] = gMoveDescription_Earthquake,
    [MOVE_FISSURE       - 1] = gMoveDescription_Fissure,
    [MOVE_DIG           - 1] = gMoveDescription_Dig,
    [MOVE_TOXIC         - 1] = gMoveDescription_Toxic,
    [MOVE_CONFUSION     - 1] = gMoveDescription_Confusion,
    [MOVE_PSYCHIC       - 1] = gMoveDescription_Psychic,
    [MOVE_HYPNOSIS      - 1] = gMoveDescription_Hypnosis,
    [MOVE_MEDITATE      - 1] = gMoveDescription_Meditate,
    [MOVE_AGILITY       - 1] = gMoveDescription_Agility,
    [MOVE_QUICK_ATTACK  - 1] = gMoveDescription_QuickAttack,
    [MOVE_RAGE          - 1] = gMoveDescription_Rage,
    [MOVE_TELEPORT      - 1] = gMoveDescription_Teleport,
    [MOVE_NIGHT_SHADE   - 1] = gMoveDescription_NightShade,
    [MOVE_MIMIC         - 1] = gMoveDescription_Mimic,
    [MOVE_SCREECH       - 1] = gMoveDescription_Screech,
    [MOVE_DOUBLE_TEAM   - 1] = gMoveDescription_DoubleTeam,
    [MOVE_RECOVER       - 1] = gMoveDescription_Recover,
    [MOVE_HARDEN        - 1] = gMoveDescription_Harden,
    [MOVE_MINIMIZE      - 1] = gMoveDescription_Minimize,
    [MOVE_SMOKESCREEN   - 1] = gMoveDescription_Smokescreen,
    [MOVE_CONFUSE_RAY   - 1] = gMoveDescription_ConfuseRay,
    [MOVE_WITHDRAW      - 1] = gMoveDescription_Withdraw,
    [MOVE_DEFENSE_CURL  - 1] = gMoveDescription_DefenseCurl,
    [MOVE_BARRIER       - 1] = gMoveDescription_Barrier,
    [MOVE_LIGHT_SCREEN  - 1] = gMoveDescription_LightScreen,
    [MOVE_HAZE          - 1] = gMoveDescription_Haze,
    [MOVE_REFLECT       - 1] = gMoveDescription_Reflect,
    [MOVE_FOCUS_ENERGY  - 1] = gMoveDescription_FocusEnergy,
    [MOVE_BIDE          - 1] = gMoveDescription_Bide,
    [MOVE_METRONOME     - 1] = gMoveDescription_Metronome,
    [MOVE_MIRROR_MOVE   - 1] = gMoveDescription_MirrorMove,
    [MOVE_SELF_DESTRUCT - 1] = gMoveDescription_SelfDestruct,
    [MOVE_EGG_BOMB      - 1] = gMoveDescription_EggBomb,
    [MOVE_LICK          - 1] = gMoveDescription_Lick,
    [MOVE_SMOG          - 1] = gMoveDescription_Smog,
    [MOVE_SLUDGE        - 1] = gMoveDescription_Sludge,
    [MOVE_BONE_CLUB     - 1] = gMoveDescription_BoneClub,
    [MOVE_FIRE_BLAST    - 1] = gMoveDescription_FireBlast,
    [MOVE_WATERFALL     - 1] = gMoveDescription_Waterfall,
    [MOVE_CLAMP         - 1] = gMoveDescription_Clamp,
    [MOVE_SWIFT         - 1] = gMoveDescription_Swift,
    [MOVE_SKULL_BASH    - 1] = gMoveDescription_SkullBash,
    [MOVE_SPIKE_CANNON  - 1] = gMoveDescription_SpikeCannon,
    [MOVE_CONSTRICT     - 1] = gMoveDescription_Constrict,
    [MOVE_AMNESIA       - 1] = gMoveDescription_Amnesia,
    [MOVE_KINESIS       - 1] = gMoveDescription_Kinesis,
    [MOVE_SOFT_BOILED   - 1] = gMoveDescription_SoftBoiled,
    [MOVE_HI_JUMP_KICK  - 1] = gMoveDescription_HiJumpKick,
    [MOVE_GLARE         - 1] = gMoveDescription_Glare,
    [MOVE_DREAM_EATER   - 1] = gMoveDescription_DreamEater,
    [MOVE_POISON_GAS    - 1] = gMoveDescription_PoisonGas,
    [MOVE_BARRAGE       - 1] = gMoveDescription_Barrage,
    [MOVE_LEECH_LIFE    - 1] = gMoveDescription_LeechLife,
    [MOVE_LOVELY_KISS   - 1] = gMoveDescription_LovelyKiss,
    [MOVE_SKY_ATTACK    - 1] = gMoveDescription_SkyAttack,
    [MOVE_TRANSFORM     - 1] = gMoveDescription_Transform,
    [MOVE_BUBBLE        - 1] = gMoveDescription_Bubble,
    [MOVE_DIZZY_PUNCH   - 1] = gMoveDescription_DizzyPunch,
    [MOVE_SPORE         - 1] = gMoveDescription_Spore,
    [MOVE_FLASH         - 1] = gMoveDescription_Flash,
    [MOVE_PSYWAVE       - 1] = gMoveDescription_Psywave,
    [MOVE_SPLASH        - 1] = gMoveDescription_Splash,
    [MOVE_ACID_ARMOR    - 1] = gMoveDescription_AcidArmor,
    [MOVE_CRABHAMMER    - 1] = gMoveDescription_Crabhammer,
    [MOVE_EXPLOSION     - 1] = gMoveDescription_Explosion,
    [MOVE_FURY_SWIPES   - 1] = gMoveDescription_FurySwipes,
    [MOVE_BONEMERANG    - 1] = gMoveDescription_Bonemerang,
    [MOVE_REST          - 1] = gMoveDescription_Rest,
    [MOVE_ROCK_SLIDE    - 1] = gMoveDescription_RockSlide,
    [MOVE_HYPER_FANG    - 1] = gMoveDescription_HyperFang,
    [MOVE_SHARPEN       - 1] = gMoveDescription_Sharpen,
    [MOVE_CONVERSION    - 1] = gMoveDescription_Conversion,
    [MOVE_TRI_ATTACK    - 1] = gMoveDescription_TriAttack,
    [MOVE_SUPER_FANG    - 1] = gMoveDescription_SuperFang,
    [MOVE_SLASH         - 1] = gMoveDescription_Slash,
    [MOVE_SUBSTITUTE    - 1] = gMoveDescription_Substitute,
    [MOVE_STRUGGLE      - 1] = gMoveDescription_Struggle,
    [MOVE_SKETCH        - 1] = gMoveDescription_Sketch,
    [MOVE_TRIPLE_KICK   - 1] = gMoveDescription_TripleKick,
    [MOVE_THIEF         - 1] = gMoveDescription_Thief,
    [MOVE_SPIDER_WEB    - 1] = gMoveDescription_SpiderWeb,
    [MOVE_MIND_READER   - 1] = gMoveDescription_MindReader,
    [MOVE_NIGHTMARE     - 1] = gMoveDescription_Nightmare,
    [MOVE_FLAME_WHEEL   - 1] = gMoveDescription_FlameWheel,
    [MOVE_SNORE         - 1] = gMoveDescription_Snore,
    [MOVE_CURSE         - 1] = gMoveDescription_Curse,
    [MOVE_FLAIL         - 1] = gMoveDescription_Flail,
    [MOVE_CONVERSION_2  - 1] = gMoveDescription_Conversion2,
    [MOVE_AEROBLAST     - 1] = gMoveDescription_Aeroblast,
    [MOVE_COTTON_SPORE  - 1] = gMoveDescription_CottonSpore,
    [MOVE_REVERSAL      - 1] = gMoveDescription_Reversal,
    [MOVE_SPITE         - 1] = gMoveDescription_Spite,
    [MOVE_POWDER_SNOW   - 1] = gMoveDescription_PowderSnow,
    [MOVE_PROTECT       - 1] = gMoveDescription_Protect,
    [MOVE_MACH_PUNCH    - 1] = gMoveDescription_MachPunch,
    [MOVE_SCARY_FACE    - 1] = gMoveDescription_ScaryFace,
    [MOVE_FEINT_ATTACK  - 1] = gMoveDescription_FeintAttack,
    [MOVE_SWEET_KISS    - 1] = gMoveDescription_SweetKiss,
    [MOVE_BELLY_DRUM    - 1] = gMoveDescription_BellyDrum,
    [MOVE_SLUDGE_BOMB   - 1] = gMoveDescription_SludgeBomb,
    [MOVE_MUD_SLAP      - 1] = gMoveDescription_MudSlap,
    [MOVE_OCTAZOOKA     - 1] = gMoveDescription_Octazooka,
    [MOVE_SPIKES        - 1] = gMoveDescription_Spikes,
    [MOVE_ZAP_CANNON    - 1] = gMoveDescription_ZapCannon,
    [MOVE_FORESIGHT     - 1] = gMoveDescription_Foresight,
    [MOVE_DESTINY_BOND  - 1] = gMoveDescription_DestinyBond,
    [MOVE_PERISH_SONG   - 1] = gMoveDescription_PerishSong,
    [MOVE_ICY_WIND      - 1] = gMoveDescription_IcyWind,
    [MOVE_DETECT        - 1] = gMoveDescription_Detect,
    [MOVE_BONE_RUSH     - 1] = gMoveDescription_BoneRush,
    [MOVE_LOCK_ON       - 1] = gMoveDescription_LockOn,
    [MOVE_OUTRAGE       - 1] = gMoveDescription_Outrage,
    [MOVE_SANDSTORM     - 1] = gMoveDescription_Sandstorm,
    [MOVE_GIGA_DRAIN    - 1] = gMoveDescription_GigaDrain,
    [MOVE_ENDURE        - 1] = gMoveDescription_Endure,
    [MOVE_CHARM         - 1] = gMoveDescription_Charm,
    [MOVE_ROLLOUT       - 1] = gMoveDescription_Rollout,
    [MOVE_FALSE_SWIPE   - 1] = gMoveDescription_FalseSwipe,
    [MOVE_SWAGGER       - 1] = gMoveDescription_Swagger,
    [MOVE_MILK_DRINK    - 1] = gMoveDescription_MilkDrink,
    [MOVE_SPARK         - 1] = gMoveDescription_Spark,
    [MOVE_FURY_CUTTER   - 1] = gMoveDescription_FuryCutter,
    [MOVE_STEEL_WING    - 1] = gMoveDescription_SteelWing,
    [MOVE_MEAN_LOOK     - 1] = gMoveDescription_MeanLook,
    [MOVE_ATTRACT       - 1] = gMoveDescription_Attract,
    [MOVE_SLEEP_TALK    - 1] = gMoveDescription_SleepTalk,
    [MOVE_HEAL_BELL     - 1] = gMoveDescription_HealBell,
    [MOVE_RETURN        - 1] = gMoveDescription_Return,
    [MOVE_PRESENT       - 1] = gMoveDescription_Present,
    [MOVE_FRUSTRATION   - 1] = gMoveDescription_Frustration,
    [MOVE_SAFEGUARD     - 1] = gMoveDescription_Safeguard,
    [MOVE_PAIN_SPLIT    - 1] = gMoveDescription_PainSplit,
    [MOVE_SACRED_FIRE   - 1] = gMoveDescription_SacredFire,
    [MOVE_MAGNITUDE     - 1] = gMoveDescription_Magnitude,
    [MOVE_DYNAMIC_PUNCH - 1] = gMoveDescription_DynamicPunch,
    [MOVE_MEGAHORN      - 1] = gMoveDescription_Megahorn,
    [MOVE_DRAGON_BREATH - 1] = gMoveDescription_DragonBreath,
    [MOVE_BATON_PASS    - 1] = gMoveDescription_BatonPass,
    [MOVE_ENCORE        - 1] = gMoveDescription_Encore,
    [MOVE_PURSUIT       - 1] = gMoveDescription_Pursuit,
    [MOVE_RAPID_SPIN    - 1] = gMoveDescription_RapidSpin,
    [MOVE_SWEET_SCENT   - 1] = gMoveDescription_SweetScent,
    [MOVE_IRON_TAIL     - 1] = gMoveDescription_IronTail,
    [MOVE_METAL_CLAW    - 1] = gMoveDescription_MetalClaw,
    [MOVE_VITAL_THROW   - 1] = gMoveDescription_VitalThrow,
    [MOVE_MORNING_SUN   - 1] = gMoveDescription_MorningSun,
    [MOVE_SYNTHESIS     - 1] = gMoveDescription_Synthesis,
    [MOVE_MOONLIGHT     - 1] = gMoveDescription_Moonlight,
    [MOVE_HIDDEN_POWER  - 1] = gMoveDescription_HiddenPower,
    [MOVE_CROSS_CHOP    - 1] = gMoveDescription_CrossChop,
    [MOVE_TWISTER       - 1] = gMoveDescription_Twister,
    [MOVE_RAIN_DANCE    - 1] = gMoveDescription_RainDance,
    [MOVE_SUNNY_DAY     - 1] = gMoveDescription_SunnyDay,
    [MOVE_CRUNCH        - 1] = gMoveDescription_Crunch,
    [MOVE_MIRROR_COAT   - 1] = gMoveDescription_MirrorCoat,
    [MOVE_PSYCH_UP      - 1] = gMoveDescription_PsychUp,
    [MOVE_EXTREME_SPEED - 1] = gMoveDescription_ExtremeSpeed,
    [MOVE_ANCIENT_POWER - 1] = gMoveDescription_AncientPower,
    [MOVE_SHADOW_BALL   - 1] = gMoveDescription_ShadowBall,
    [MOVE_FUTURE_SIGHT  - 1] = gMoveDescription_FutureSight,
    [MOVE_ROCK_SMASH    - 1] = gMoveDescription_RockSmash,
    [MOVE_WHIRLPOOL     - 1] = gMoveDescription_Whirlpool,
    [MOVE_BEAT_UP       - 1] = gMoveDescription_BeatUp,
    [MOVE_FAKE_OUT      - 1] = gMoveDescription_FakeOut,
    [MOVE_UPROAR        - 1] = gMoveDescription_Uproar,
    [MOVE_STOCKPILE     - 1] = gMoveDescription_Stockpile,
    [MOVE_SPIT_UP       - 1] = gMoveDescription_SpitUp,
    [MOVE_SWALLOW       - 1] = gMoveDescription_Swallow,
    [MOVE_HEAT_WAVE     - 1] = gMoveDescription_HeatWave,
    [MOVE_HAIL          - 1] = gMoveDescription_Hail,
    [MOVE_TORMENT       - 1] = gMoveDescription_Torment,
    [MOVE_FLATTER       - 1] = gMoveDescription_Flatter,
    [MOVE_WILL_O_WISP   - 1] = gMoveDescription_WillOWisp,
    [MOVE_MEMENTO       - 1] = gMoveDescription_Memento,
    [MOVE_FACADE        - 1] = gMoveDescription_Facade,
    [MOVE_FOCUS_PUNCH   - 1] = gMoveDescription_FocusPunch,
    [MOVE_SMELLING_SALT - 1] = gMoveDescription_SmellingSalt,
    [MOVE_FOLLOW_ME     - 1] = gMoveDescription_FollowMe,
    [MOVE_NATURE_POWER  - 1] = gMoveDescription_NaturePower,
    [MOVE_CHARGE        - 1] = gMoveDescription_Charge,
    [MOVE_TAUNT         - 1] = gMoveDescription_Taunt,
    [MOVE_HELPING_HAND  - 1] = gMoveDescription_HelpingHand,
    [MOVE_TRICK         - 1] = gMoveDescription_Trick,
    [MOVE_ROLE_PLAY     - 1] = gMoveDescription_RolePlay,
    [MOVE_WISH          - 1] = gMoveDescription_Wish,
    [MOVE_ASSIST        - 1] = gMoveDescription_Assist,
    [MOVE_INGRAIN       - 1] = gMoveDescription_Ingrain,
    [MOVE_SUPERPOWER    - 1] = gMoveDescription_Superpower,
    [MOVE_MAGIC_COAT    - 1] = gMoveDescription_MagicCoat,
    [MOVE_RECYCLE       - 1] = gMoveDescription_Recycle,
    [MOVE_REVENGE       - 1] = gMoveDescription_Revenge,
    [MOVE_BRICK_BREAK   - 1] = gMoveDescription_BrickBreak,
    [MOVE_YAWN          - 1] = gMoveDescription_Yawn,
    [MOVE_KNOCK_OFF     - 1] = gMoveDescription_KnockOff,
    [MOVE_ENDEAVOR      - 1] = gMoveDescription_Endeavor,
    [MOVE_ERUPTION      - 1] = gMoveDescription_Eruption,
    [MOVE_SKILL_SWAP    - 1] = gMoveDescription_SkillSwap,
    [MOVE_IMPRISON      - 1] = gMoveDescription_Imprison,
    [MOVE_REFRESH       - 1] = gMoveDescription_Refresh,
    [MOVE_GRUDGE        - 1] = gMoveDescription_Grudge,
    [MOVE_SNATCH        - 1] = gMoveDescription_Snatch,
    [MOVE_SECRET_POWER  - 1] = gMoveDescription_SecretPower,
    [MOVE_DIVE          - 1] = gMoveDescription_Dive,
    [MOVE_ARM_THRUST    - 1] = gMoveDescription_ArmThrust,
    [MOVE_CAMOUFLAGE    - 1] = gMoveDescription_Camouflage,
    [MOVE_TAIL_GLOW     - 1] = gMoveDescription_TailGlow,
    [MOVE_LUSTER_PURGE  - 1] = gMoveDescription_LusterPurge,
    [MOVE_MIST_BALL     - 1] = gMoveDescription_MistBall,
    [MOVE_FEATHER_DANCE - 1] = gMoveDescription_FeatherDance,
    [MOVE_TEETER_DANCE  - 1] = gMoveDescription_TeeterDance,
    [MOVE_BLAZE_KICK    - 1] = gMoveDescription_BlazeKick,
    [MOVE_MUD_SPORT     - 1] = gMoveDescription_MudSport,
    [MOVE_ICE_BALL      - 1] = gMoveDescription_IceBall,
    [MOVE_NEEDLE_ARM    - 1] = gMoveDescription_NeedleArm,
    [MOVE_SLACK_OFF     - 1] = gMoveDescription_SlackOff,
    [MOVE_HYPER_VOICE   - 1] = gMoveDescription_HyperVoice,
    [MOVE_POISON_FANG   - 1] = gMoveDescription_PoisonFang,
    [MOVE_CRUSH_CLAW    - 1] = gMoveDescription_CrushClaw,
    [MOVE_BLAST_BURN    - 1] = gMoveDescription_BlastBurn,
    [MOVE_HYDRO_CANNON  - 1] = gMoveDescription_HydroCannon,
    [MOVE_METEOR_MASH   - 1] = gMoveDescription_MeteorMash,
    [MOVE_ASTONISH      - 1] = gMoveDescription_Astonish,
    [MOVE_WEATHER_BALL  - 1] = gMoveDescription_WeatherBall,
    [MOVE_AROMATHERAPY  - 1] = gMoveDescription_Aromatherapy,
    [MOVE_FAKE_TEARS    - 1] = gMoveDescription_FakeTears,
    [MOVE_AIR_CUTTER    - 1] = gMoveDescription_AirCutter,
    [MOVE_OVERHEAT      - 1] = gMoveDescription_Overheat,
    [MOVE_ODOR_SLEUTH   - 1] = gMoveDescription_OdorSleuth,
    [MOVE_ROCK_TOMB     - 1] = gMoveDescription_RockTomb,
    [MOVE_SILVER_WIND   - 1] = gMoveDescription_SilverWind,
    [MOVE_METAL_SOUND   - 1] = gMoveDescription_MetalSound,
    [MOVE_GRASS_WHISTLE - 1] = gMoveDescription_GrassWhistle,
    [MOVE_TICKLE        - 1] = gMoveDescription_Tickle,
    [MOVE_COSMIC_POWER  - 1] = gMoveDescription_CosmicPower,
    [MOVE_WATER_SPOUT   - 1] = gMoveDescription_WaterSpout,
    [MOVE_SIGNAL_BEAM   - 1] = gMoveDescription_SignalBeam,
    [MOVE_SHADOW_PUNCH  - 1] = gMoveDescription_ShadowPunch,
    [MOVE_EXTRASENSORY  - 1] = gMoveDescription_Extrasensory,
    [MOVE_SKY_UPPERCUT  - 1] = gMoveDescription_SkyUppercut,
    [MOVE_SAND_TOMB     - 1] = gMoveDescription_SandTomb,
    [MOVE_SHEER_COLD    - 1] = gMoveDescription_SheerCold,
    [MOVE_MUDDY_WATER   - 1] = gMoveDescription_MuddyWater,
    [MOVE_BULLET_SEED   - 1] = gMoveDescription_BulletSeed,
    [MOVE_AERIAL_ACE    - 1] = gMoveDescription_AerialAce,
    [MOVE_ICICLE_SPEAR  - 1] = gMoveDescription_IcicleSpear,
    [MOVE_IRON_DEFENSE  - 1] = gMoveDescription_IronDefense,
    [MOVE_BLOCK         - 1] = gMoveDescription_Block,
    [MOVE_HOWL          - 1] = gMoveDescription_Howl,
    [MOVE_DRAGON_CLAW   - 1] = gMoveDescription_DragonClaw,
    [MOVE_FRENZY_PLANT  - 1] = gMoveDescription_FrenzyPlant,
    [MOVE_BULK_UP       - 1] = gMoveDescription_BulkUp,
    [MOVE_BOUNCE        - 1] = gMoveDescription_Bounce,
    [MOVE_MUD_SHOT      - 1] = gMoveDescription_MudShot,
    [MOVE_POISON_TAIL   - 1] = gMoveDescription_PoisonTail,
    [MOVE_COVET         - 1] = gMoveDescription_Covet,
    [MOVE_VOLT_TACKLE   - 1] = gMoveDescription_VoltTackle,
    [MOVE_MAGICAL_LEAF  - 1] = gMoveDescription_MagicalLeaf,
    [MOVE_WATER_SPORT   - 1] = gMoveDescription_WaterSport,
    [MOVE_CALM_MIND     - 1] = gMoveDescription_CalmMind,
    [MOVE_LEAF_BLADE    - 1] = gMoveDescription_LeafBlade,
    [MOVE_DRAGON_DANCE  - 1] = gMoveDescription_DragonDance,
    [MOVE_ROCK_BLAST    - 1] = gMoveDescription_RockBlast,
    [MOVE_SHOCK_WAVE    - 1] = gMoveDescription_ShockWave,
    [MOVE_WATER_PULSE   - 1] = gMoveDescription_WaterPulse,
    [MOVE_DOOM_DESIRE   - 1] = gMoveDescription_DoomDesire,
    [MOVE_PSYCHO_BOOST  - 1] = gMoveDescription_PsychoBoost,
};

// ---------------------------------------------------------------------------
// Section 4: Move Stats (gBattleMoves)
// ---------------------------------------------------------------------------

const struct BattleMove gBattleMoves[MOVES_COUNT] =
    {
        [MOVE_NONE] =
            {
                .effect = EFFECT_HIT,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 0,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_POUND] =
            {
                .effect = EFFECT_HIT,
                .power = 40,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 35,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_KARATE_CHOP] =
            {
                .effect = EFFECT_HIGH_CRITICAL,
                .power = 50,
                .type = TYPE_FIGHTING,
                .accuracy = 100,
                .pp = 25,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_DOUBLE_SLAP] =
            {
                .effect = EFFECT_MULTI_HIT,
                .power = 15,
                .type = TYPE_NORMAL,
                .accuracy = 85,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_COMET_PUNCH] =
            {
                .effect = EFFECT_MULTI_HIT,
                .power = 18,
                .type = TYPE_NORMAL,
                .accuracy = 85,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_MEGA_PUNCH] =
            {
                .effect = EFFECT_HIT,
                .power = 80,
                .type = TYPE_NORMAL,
                .accuracy = 85,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_PAY_DAY] =
            {
                .effect = EFFECT_PAY_DAY,
                .power = 40,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_FIRE_PUNCH] =
            {
                .effect = EFFECT_BURN_HIT,
                .power = 75,
                .type = TYPE_FIRE,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_ICE_PUNCH] =
            {
                .effect = EFFECT_FREEZE_HIT,
                .power = 75,
                .type = TYPE_ICE,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_THUNDER_PUNCH] =
            {
                .effect = EFFECT_PARALYZE_HIT,
                .power = 75,
                .type = TYPE_ELECTRIC,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SCRATCH] =
            {
                .effect = EFFECT_HIT,
                .power = 40,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 35,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_VICE_GRIP] =
            {
                .effect = EFFECT_HIT,
                .power = 55,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_GUILLOTINE] =
            {
                .effect = EFFECT_OHKO,
                .power = 1,
                .type = TYPE_NORMAL,
                .accuracy = 30,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_RAZOR_WIND] =
            {
                .effect = EFFECT_RAZOR_WIND,
                .power = 80,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_SWORDS_DANCE] =
            {
                .effect = EFFECT_ATTACK_UP_2,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_CUT] =
            {
                .effect = EFFECT_HIT,
                .power = 50,
                .type = TYPE_NORMAL,
                .accuracy = 95,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_GUST] =
            {
                .effect = EFFECT_GUST,
                .power = 40,
                .type = TYPE_FLYING,
                .accuracy = 100,
                .pp = 35,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_WING_ATTACK] =
            {
                .effect = EFFECT_HIT,
                .power = 60,
                .type = TYPE_FLYING,
                .accuracy = 100,
                .pp = 35,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_WHIRLWIND] =
            {
                .effect = EFFECT_ROAR,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = -6,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_FLY] =
            {
                .effect = EFFECT_SEMI_INVULNERABLE,
                .power = 70,
                .type = TYPE_FLYING,
                .accuracy = 95,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_BIND] =
            {
                .effect = EFFECT_TRAP,
                .power = 15,
                .type = TYPE_NORMAL,
                .accuracy = 75,
                .pp = 20,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SLAM] =
            {
                .effect = EFFECT_HIT,
                .power = 80,
                .type = TYPE_NORMAL,
                .accuracy = 75,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_VINE_WHIP] =
            {
                .effect = EFFECT_HIT,
                .power = 35,
                .type = TYPE_GRASS,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_STOMP] =
            {
                .effect = EFFECT_FLINCH_MINIMIZE_HIT,
                .power = 65,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_DOUBLE_KICK] =
            {
                .effect = EFFECT_DOUBLE_HIT,
                .power = 30,
                .type = TYPE_FIGHTING,
                .accuracy = 100,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_MEGA_KICK] =
            {
                .effect = EFFECT_HIT,
                .power = 120,
                .type = TYPE_NORMAL,
                .accuracy = 75,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_JUMP_KICK] =
            {
                .effect = EFFECT_RECOIL_IF_MISS,
                .power = 70,
                .type = TYPE_FIGHTING,
                .accuracy = 95,
                .pp = 25,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_ROLLING_KICK] =
            {
                .effect = EFFECT_FLINCH_HIT,
                .power = 60,
                .type = TYPE_FIGHTING,
                .accuracy = 85,
                .pp = 15,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SAND_ATTACK] =
            {
                .effect = EFFECT_ACCURACY_DOWN,
                .power = 0,
                .type = TYPE_GROUND,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_HEADBUTT] =
            {
                .effect = EFFECT_FLINCH_HIT,
                .power = 70,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_HORN_ATTACK] =
            {
                .effect = EFFECT_HIT,
                .power = 65,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 25,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_FURY_ATTACK] =
            {
                .effect = EFFECT_MULTI_HIT,
                .power = 15,
                .type = TYPE_NORMAL,
                .accuracy = 85,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_HORN_DRILL] =
            {
                .effect = EFFECT_OHKO,
                .power = 1,
                .type = TYPE_NORMAL,
                .accuracy = 30,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_TACKLE] =
            {
                .effect = EFFECT_HIT,
                .power = 35,
                .type = TYPE_NORMAL,
                .accuracy = 95,
                .pp = 35,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_BODY_SLAM] =
            {
                .effect = EFFECT_PARALYZE_HIT,
                .power = 85,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_WRAP] =
            {
                .effect = EFFECT_TRAP,
                .power = 15,
                .type = TYPE_NORMAL,
                .accuracy = 85,
                .pp = 20,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_TAKE_DOWN] =
            {
                .effect = EFFECT_RECOIL,
                .power = 90,
                .type = TYPE_NORMAL,
                .accuracy = 85,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_THRASH] =
            {
                .effect = EFFECT_RAMPAGE,
                .power = 90,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_RANDOM,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_DOUBLE_EDGE] =
            {
                .effect = EFFECT_DOUBLE_EDGE,
                .power = 120,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_TAIL_WHIP] =
            {
                .effect = EFFECT_DEFENSE_DOWN,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_POISON_STING] =
            {
                .effect = EFFECT_POISON_HIT,
                .power = 15,
                .type = TYPE_POISON,
                .accuracy = 100,
                .pp = 35,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_TWINEEDLE] =
            {
                .effect = EFFECT_TWINEEDLE,
                .power = 25,
                .type = TYPE_BUG,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 20,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_PIN_MISSILE] =
            {
                .effect = EFFECT_MULTI_HIT,
                .power = 14,
                .type = TYPE_BUG,
                .accuracy = 85,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_LEER] =
            {
                .effect = EFFECT_DEFENSE_DOWN,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_BITE] =
            {
                .effect = EFFECT_FLINCH_HIT,
                .power = 60,
                .type = TYPE_DARK,
                .accuracy = 100,
                .pp = 25,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_GROWL] =
            {
                .effect = EFFECT_ATTACK_DOWN,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 40,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_ROAR] =
            {
                .effect = EFFECT_ROAR,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = -6,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_SING] =
            {
                .effect = EFFECT_SLEEP,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 55,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
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
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_SONIC_BOOM] =
            {
                .effect = EFFECT_SONICBOOM,
                .power = 1,
                .type = TYPE_NORMAL,
                .accuracy = 90,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_DISABLE] =
            {
                .effect = EFFECT_DISABLE,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 55,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_ACID] =
            {
                .effect = EFFECT_DEFENSE_DOWN_HIT,
                .power = 40,
                .type = TYPE_POISON,
                .accuracy = 100,
                .pp = 30,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_EMBER] =
            {
                .effect = EFFECT_BURN_HIT,
                .power = 40,
                .type = TYPE_FIRE,
                .accuracy = 100,
                .pp = 25,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_FLAMETHROWER] =
            {
                .effect = EFFECT_BURN_HIT,
                .power = 95,
                .type = TYPE_FIRE,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_MIST] =
            {
                .effect = EFFECT_MIST,
                .power = 0,
                .type = TYPE_ICE,
                .accuracy = 0,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_WATER_GUN] =
            {
                .effect = EFFECT_HIT,
                .power = 40,
                .type = TYPE_WATER,
                .accuracy = 100,
                .pp = 25,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_HYDRO_PUMP] =
            {
                .effect = EFFECT_HIT,
                .power = 120,
                .type = TYPE_WATER,
                .accuracy = 80,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_SURF] =
            {
                .effect = EFFECT_HIT,
                .power = 95,
                .type = TYPE_WATER,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_ICE_BEAM] =
            {
                .effect = EFFECT_FREEZE_HIT,
                .power = 95,
                .type = TYPE_ICE,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_BLIZZARD] =
            {
                .effect = EFFECT_FREEZE_HIT,
                .power = 120,
                .type = TYPE_ICE,
                .accuracy = 70,
                .pp = 5,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_PSYBEAM] =
            {
                .effect = EFFECT_CONFUSE_HIT,
                .power = 65,
                .type = TYPE_PSYCHIC,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_BUBBLE_BEAM] =
            {
                .effect = EFFECT_SPEED_DOWN_HIT,
                .power = 65,
                .type = TYPE_WATER,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_AURORA_BEAM] =
            {
                .effect = EFFECT_ATTACK_DOWN_HIT,
                .power = 65,
                .type = TYPE_ICE,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_HYPER_BEAM] =
            {
                .effect = EFFECT_RECHARGE,
                .power = 150,
                .type = TYPE_NORMAL,
                .accuracy = 90,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_PECK] =
            {
                .effect = EFFECT_HIT,
                .power = 35,
                .type = TYPE_FLYING,
                .accuracy = 100,
                .pp = 35,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_DRILL_PECK] =
            {
                .effect = EFFECT_HIT,
                .power = 80,
                .type = TYPE_FLYING,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SUBMISSION] =
            {
                .effect = EFFECT_RECOIL,
                .power = 80,
                .type = TYPE_FIGHTING,
                .accuracy = 80,
                .pp = 25,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_LOW_KICK] =
            {
                .effect = EFFECT_LOW_KICK,
                .power = 1,
                .type = TYPE_FIGHTING,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_COUNTER] =
            {
                .effect = EFFECT_COUNTER,
                .power = 1,
                .type = TYPE_FIGHTING,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_DEPENDS,
                .priority = -5,
                .makesContact = TRUE,
                .ignoresProtect = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SEISMIC_TOSS] =
            {
                .effect = EFFECT_LEVEL_DAMAGE,
                .power = 1,
                .type = TYPE_FIGHTING,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_STRENGTH] =
            {
                .effect = EFFECT_HIT,
                .power = 80,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_ABSORB] =
            {
                .effect = EFFECT_ABSORB,
                .power = 20,
                .type = TYPE_GRASS,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_MEGA_DRAIN] =
            {
                .effect = EFFECT_ABSORB,
                .power = 40,
                .type = TYPE_GRASS,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_LEECH_SEED] =
            {
                .effect = EFFECT_LEECH_SEED,
                .power = 0,
                .type = TYPE_GRASS,
                .accuracy = 90,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_GROWTH] =
            {
                .effect = EFFECT_SPECIAL_ATTACK_UP,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 40,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_RAZOR_LEAF] =
            {
                .effect = EFFECT_HIGH_CRITICAL,
                .power = 55,
                .type = TYPE_GRASS,
                .accuracy = 95,
                .pp = 25,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SOLAR_BEAM] =
            {
                .effect = EFFECT_SOLAR_BEAM,
                .power = 120,
                .type = TYPE_GRASS,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_POISON_POWDER] =
            {
                .effect = EFFECT_POISON,
                .power = 0,
                .type = TYPE_POISON,
                .accuracy = 75,
                .pp = 35,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_STUN_SPORE] =
            {
                .effect = EFFECT_PARALYZE,
                .power = 0,
                .type = TYPE_GRASS,
                .accuracy = 75,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_SLEEP_POWDER] =
            {
                .effect = EFFECT_SLEEP,
                .power = 0,
                .type = TYPE_GRASS,
                .accuracy = 75,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_PETAL_DANCE] =
            {
                .effect = EFFECT_RAMPAGE,
                .power = 70,
                .type = TYPE_GRASS,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_RANDOM,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_STRING_SHOT] =
            {
                .effect = EFFECT_SPEED_DOWN,
                .power = 0,
                .type = TYPE_BUG,
                .accuracy = 95,
                .pp = 40,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_DRAGON_RAGE] =
            {
                .effect = EFFECT_DRAGON_RAGE,
                .power = 1,
                .type = TYPE_DRAGON,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_FIRE_SPIN] =
            {
                .effect = EFFECT_TRAP,
                .power = 15,
                .type = TYPE_FIRE,
                .accuracy = 70,
                .pp = 15,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_THUNDER_SHOCK] =
            {
                .effect = EFFECT_PARALYZE_HIT,
                .power = 40,
                .type = TYPE_ELECTRIC,
                .accuracy = 100,
                .pp = 30,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_THUNDERBOLT] =
            {
                .effect = EFFECT_PARALYZE_HIT,
                .power = 95,
                .type = TYPE_ELECTRIC,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_THUNDER_WAVE] =
            {
                .effect = EFFECT_PARALYZE,
                .power = 0,
                .type = TYPE_ELECTRIC,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_THUNDER] =
            {
                .effect = EFFECT_THUNDER,
                .power = 120,
                .type = TYPE_ELECTRIC,
                .accuracy = 70,
                .pp = 10,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_ROCK_THROW] =
            {
                .effect = EFFECT_HIT,
                .power = 50,
                .type = TYPE_ROCK,
                .accuracy = 90,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_EARTHQUAKE] =
            {
                .effect = EFFECT_EARTHQUAKE,
                .power = 100,
                .type = TYPE_GROUND,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_FOES_AND_ALLY,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_FISSURE] =
            {
                .effect = EFFECT_OHKO,
                .power = 1,
                .type = TYPE_GROUND,
                .accuracy = 30,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_DIG] =
            {
                .effect = EFFECT_SEMI_INVULNERABLE,
                .power = 60,
                .type = TYPE_GROUND,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_TOXIC] =
            {
                .effect = EFFECT_TOXIC,
                .power = 0,
                .type = TYPE_POISON,
                .accuracy = 85,
                .pp = 10,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_CONFUSION] =
            {
                .effect = EFFECT_CONFUSE_HIT,
                .power = 50,
                .type = TYPE_PSYCHIC,
                .accuracy = 100,
                .pp = 25,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_PSYCHIC] =
            {
                .effect = EFFECT_SPECIAL_DEFENSE_DOWN_HIT,
                .power = 90,
                .type = TYPE_PSYCHIC,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_HYPNOSIS] =
            {
                .effect = EFFECT_SLEEP,
                .power = 0,
                .type = TYPE_PSYCHIC,
                .accuracy = 60,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
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
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_AGILITY] =
            {
                .effect = EFFECT_SPEED_UP_2,
                .power = 0,
                .type = TYPE_PSYCHIC,
                .accuracy = 0,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_QUICK_ATTACK] =
            {
                .effect = EFFECT_QUICK_ATTACK,
                .power = 40,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 1,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_RAGE] =
            {
                .effect = EFFECT_RAGE,
                .power = 20,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_TELEPORT] =
            {
                .effect = EFFECT_TELEPORT,
                .power = 0,
                .type = TYPE_PSYCHIC,
                .accuracy = 0,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_NIGHT_SHADE] =
            {
                .effect = EFFECT_LEVEL_DAMAGE,
                .power = 1,
                .type = TYPE_GHOST,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_MIMIC] =
            {
                .effect = EFFECT_MIMIC,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_SCREECH] =
            {
                .effect = EFFECT_DEFENSE_DOWN_2,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 85,
                .pp = 40,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
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
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_RECOVER] =
            {
                .effect = EFFECT_RESTORE_HP,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_HARDEN] =
            {
                .effect = EFFECT_DEFENSE_UP,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_MINIMIZE] =
            {
                .effect = EFFECT_MINIMIZE,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_SMOKESCREEN] =
            {
                .effect = EFFECT_ACCURACY_DOWN,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
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
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
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
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_DEFENSE_CURL] =
            {
                .effect = EFFECT_DEFENSE_CURL,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 40,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_BARRIER] =
            {
                .effect = EFFECT_DEFENSE_UP_2,
                .power = 0,
                .type = TYPE_PSYCHIC,
                .accuracy = 0,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_LIGHT_SCREEN] =
            {
                .effect = EFFECT_LIGHT_SCREEN,
                .power = 0,
                .type = TYPE_PSYCHIC,
                .accuracy = 0,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_HAZE] =
            {
                .effect = EFFECT_HAZE,
                .power = 0,
                .type = TYPE_ICE,
                .accuracy = 0,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_REFLECT] =
            {
                .effect = EFFECT_REFLECT,
                .power = 0,
                .type = TYPE_PSYCHIC,
                .accuracy = 0,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_FOCUS_ENERGY] =
            {
                .effect = EFFECT_FOCUS_ENERGY,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_BIDE] =
            {
                .effect = EFFECT_BIDE,
                .power = 1,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .makesContact = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_METRONOME] =
            {
                .effect = EFFECT_METRONOME,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_DEPENDS,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_MIRROR_MOVE] =
            {
                .effect = EFFECT_MIRROR_MOVE,
                .power = 0,
                .type = TYPE_FLYING,
                .accuracy = 0,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_DEPENDS,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_SELF_DESTRUCT] =
            {
                .effect = EFFECT_EXPLOSION,
                .power = 200,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_FOES_AND_ALLY,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_EGG_BOMB] =
            {
                .effect = EFFECT_HIT,
                .power = 100,
                .type = TYPE_NORMAL,
                .accuracy = 75,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_LICK] =
            {
                .effect = EFFECT_PARALYZE_HIT,
                .power = 20,
                .type = TYPE_GHOST,
                .accuracy = 100,
                .pp = 30,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SMOG] =
            {
                .effect = EFFECT_POISON_HIT,
                .power = 20,
                .type = TYPE_POISON,
                .accuracy = 70,
                .pp = 20,
                .secondaryEffectChance = 40,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_SLUDGE] =
            {
                .effect = EFFECT_POISON_HIT,
                .power = 65,
                .type = TYPE_POISON,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_BONE_CLUB] =
            {
                .effect = EFFECT_FLINCH_HIT,
                .power = 65,
                .type = TYPE_GROUND,
                .accuracy = 85,
                .pp = 20,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_FIRE_BLAST] =
            {
                .effect = EFFECT_BURN_HIT,
                .power = 120,
                .type = TYPE_FIRE,
                .accuracy = 85,
                .pp = 5,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_WATERFALL] =
            {
                .effect = EFFECT_HIT,
                .power = 80,
                .type = TYPE_WATER,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_CLAMP] =
            {
                .effect = EFFECT_TRAP,
                .power = 35,
                .type = TYPE_WATER,
                .accuracy = 75,
                .pp = 10,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SWIFT] =
            {
                .effect = EFFECT_ALWAYS_HIT,
                .power = 60,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_SKULL_BASH] =
            {
                .effect = EFFECT_SKULL_BASH,
                .power = 100,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SPIKE_CANNON] =
            {
                .effect = EFFECT_MULTI_HIT,
                .power = 20,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_CONSTRICT] =
            {
                .effect = EFFECT_SPEED_DOWN_HIT,
                .power = 10,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 35,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_AMNESIA] =
            {
                .effect = EFFECT_SPECIAL_DEFENSE_UP_2,
                .power = 0,
                .type = TYPE_PSYCHIC,
                .accuracy = 0,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_KINESIS] =
            {
                .effect = EFFECT_ACCURACY_DOWN,
                .power = 0,
                .type = TYPE_PSYCHIC,
                .accuracy = 80,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_SOFT_BOILED] =
            {
                .effect = EFFECT_SOFTBOILED,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_HI_JUMP_KICK] =
            {
                .effect = EFFECT_RECOIL_IF_MISS,
                .power = 85,
                .type = TYPE_FIGHTING,
                .accuracy = 90,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_GLARE] =
            {
                .effect = EFFECT_PARALYZE,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 75,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
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
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_POISON_GAS] =
            {
                .effect = EFFECT_POISON,
                .power = 0,
                .type = TYPE_POISON,
                .accuracy = 55,
                .pp = 40,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
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
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_LEECH_LIFE] =
            {
                .effect = EFFECT_ABSORB,
                .power = 20,
                .type = TYPE_BUG,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_LOVELY_KISS] =
            {
                .effect = EFFECT_SLEEP,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 75,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_SKY_ATTACK] =
            {
                .effect = EFFECT_SKY_ATTACK,
                .power = 140,
                .type = TYPE_FLYING,
                .accuracy = 90,
                .pp = 5,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_TRANSFORM] =
            {
                .effect = EFFECT_TRANSFORM,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_BUBBLE] =
            {
                .effect = EFFECT_SPEED_DOWN_HIT,
                .power = 20,
                .type = TYPE_WATER,
                .accuracy = 100,
                .pp = 30,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_DIZZY_PUNCH] =
            {
                .effect = EFFECT_CONFUSE_HIT,
                .power = 70,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 20,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SPORE] =
            {
                .effect = EFFECT_SLEEP,
                .power = 0,
                .type = TYPE_GRASS,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_FLASH] =
            {
                .effect = EFFECT_ACCURACY_DOWN,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 70,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_PSYWAVE] =
            {
                .effect = EFFECT_PSYWAVE,
                .power = 1,
                .type = TYPE_PSYCHIC,
                .accuracy = 80,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_SPLASH] =
            {
                .effect = EFFECT_SPLASH,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 40,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_ACID_ARMOR] =
            {
                .effect = EFFECT_DEFENSE_UP_2,
                .power = 0,
                .type = TYPE_POISON,
                .accuracy = 0,
                .pp = 40,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_CRABHAMMER] =
            {
                .effect = EFFECT_HIGH_CRITICAL,
                .power = 90,
                .type = TYPE_WATER,
                .accuracy = 85,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_EXPLOSION] =
            {
                .effect = EFFECT_EXPLOSION,
                .power = 250,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_FOES_AND_ALLY,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_FURY_SWIPES] =
            {
                .effect = EFFECT_MULTI_HIT,
                .power = 18,
                .type = TYPE_NORMAL,
                .accuracy = 80,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_BONEMERANG] =
            {
                .effect = EFFECT_DOUBLE_HIT,
                .power = 50,
                .type = TYPE_GROUND,
                .accuracy = 90,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_REST] =
            {
                .effect = EFFECT_REST,
                .power = 0,
                .type = TYPE_PSYCHIC,
                .accuracy = 0,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_ROCK_SLIDE] =
            {
                .effect = EFFECT_FLINCH_HIT,
                .power = 75,
                .type = TYPE_ROCK,
                .accuracy = 90,
                .pp = 10,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_HYPER_FANG] =
            {
                .effect = EFFECT_FLINCH_HIT,
                .power = 80,
                .type = TYPE_NORMAL,
                .accuracy = 90,
                .pp = 15,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SHARPEN] =
            {
                .effect = EFFECT_ATTACK_UP,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_CONVERSION] =
            {
                .effect = EFFECT_CONVERSION,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_TRI_ATTACK] =
            {
                .effect = EFFECT_TRI_ATTACK,
                .power = 80,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 20,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_SUPER_FANG] =
            {
                .effect = EFFECT_SUPER_FANG,
                .power = 1,
                .type = TYPE_NORMAL,
                .accuracy = 90,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SLASH] =
            {
                .effect = EFFECT_HIGH_CRITICAL,
                .power = 70,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SUBSTITUTE] =
            {
                .effect = EFFECT_SUBSTITUTE,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_STRUGGLE] =
            {
                .effect = EFFECT_RECOIL,
                .power = 50,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 1,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SKETCH] =
            {
                .effect = EFFECT_SKETCH,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 1,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_TRIPLE_KICK] =
            {
                .effect = EFFECT_TRIPLE_KICK,
                .power = 10,
                .type = TYPE_FIGHTING,
                .accuracy = 90,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_THIEF] =
            {
                .effect = EFFECT_THIEF,
                .power = 40,
                .type = TYPE_DARK,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SPIDER_WEB] =
            {
                .effect = EFFECT_MEAN_LOOK,
                .power = 0,
                .type = TYPE_BUG,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_MIND_READER] =
            {
                .effect = EFFECT_LOCK_ON,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_NIGHTMARE] =
            {
                .effect = EFFECT_NIGHTMARE,
                .power = 0,
                .type = TYPE_GHOST,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_FLAME_WHEEL] =
            {
                .effect = EFFECT_THAW_HIT,
                .power = 60,
                .type = TYPE_FIRE,
                .accuracy = 100,
                .pp = 25,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SNORE] =
            {
                .effect = EFFECT_SNORE,
                .power = 40,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_CURSE] =
            {
                .effect = EFFECT_CURSE,
                .power = 0,
                .type = TYPE_MYSTERY,
                .accuracy = 0,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_FLAIL] =
            {
                .effect = EFFECT_FLAIL,
                .power = 1,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_CONVERSION_2] =
            {
                .effect = EFFECT_CONVERSION_2,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_AEROBLAST] =
            {
                .effect = EFFECT_HIGH_CRITICAL,
                .power = 100,
                .type = TYPE_FLYING,
                .accuracy = 95,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_COTTON_SPORE] =
            {
                .effect = EFFECT_SPEED_DOWN_2,
                .power = 0,
                .type = TYPE_GRASS,
                .accuracy = 85,
                .pp = 40,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_REVERSAL] =
            {
                .effect = EFFECT_FLAIL,
                .power = 1,
                .type = TYPE_FIGHTING,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SPITE] =
            {
                .effect = EFFECT_SPITE,
                .power = 0,
                .type = TYPE_GHOST,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_POWDER_SNOW] =
            {
                .effect = EFFECT_FREEZE_HIT,
                .power = 40,
                .type = TYPE_ICE,
                .accuracy = 100,
                .pp = 25,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_PROTECT] =
            {
                .effect = EFFECT_PROTECT,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 3,
                .category = SPLIT_STATUS,
            },

        [MOVE_MACH_PUNCH] =
            {
                .effect = EFFECT_QUICK_ATTACK,
                .power = 40,
                .type = TYPE_FIGHTING,
                .accuracy = 100,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 1,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SCARY_FACE] =
            {
                .effect = EFFECT_SPEED_DOWN_2,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 90,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_FEINT_ATTACK] =
            {
                .effect = EFFECT_ALWAYS_HIT,
                .power = 60,
                .type = TYPE_DARK,
                .accuracy = 0,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SWEET_KISS] =
            {
                .effect = EFFECT_CONFUSE,
                .power = 0,
                .type = TYPE_FAIRY,
                .accuracy = 75,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
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
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_SLUDGE_BOMB] =
            {
                .effect = EFFECT_POISON_HIT,
                .power = 90,
                .type = TYPE_POISON,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_MUD_SLAP] =
            {
                .effect = EFFECT_ACCURACY_DOWN_HIT,
                .power = 20,
                .type = TYPE_GROUND,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_OCTAZOOKA] =
            {
                .effect = EFFECT_ACCURACY_DOWN_HIT,
                .power = 65,
                .type = TYPE_WATER,
                .accuracy = 85,
                .pp = 10,
                .secondaryEffectChance = 50,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_SPIKES] =
            {
                .effect = EFFECT_SPIKES,
                .power = 0,
                .type = TYPE_GROUND,
                .accuracy = 0,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_OPPONENTS_FIELD,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_ZAP_CANNON] =
            {
                .effect = EFFECT_PARALYZE_HIT,
                .power = 100,
                .type = TYPE_ELECTRIC,
                .accuracy = 50,
                .pp = 5,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_FORESIGHT] =
            {
                .effect = EFFECT_FORESIGHT,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 40,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_DESTINY_BOND] =
            {
                .effect = EFFECT_DESTINY_BOND,
                .power = 0,
                .type = TYPE_GHOST,
                .accuracy = 0,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_PERISH_SONG] =
            {
                .effect = EFFECT_PERISH_SONG,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_ICY_WIND] =
            {
                .effect = EFFECT_SPEED_DOWN_HIT,
                .power = 55,
                .type = TYPE_ICE,
                .accuracy = 95,
                .pp = 15,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_DETECT] =
            {
                .effect = EFFECT_PROTECT,
                .power = 0,
                .type = TYPE_FIGHTING,
                .accuracy = 0,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 3,
                .category = SPLIT_STATUS,
            },

        [MOVE_BONE_RUSH] =
            {
                .effect = EFFECT_MULTI_HIT,
                .power = 25,
                .type = TYPE_GROUND,
                .accuracy = 80,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_LOCK_ON] =
            {
                .effect = EFFECT_LOCK_ON,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_OUTRAGE] =
            {
                .effect = EFFECT_RAMPAGE,
                .power = 90,
                .type = TYPE_DRAGON,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_RANDOM,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SANDSTORM] =
            {
                .effect = EFFECT_SANDSTORM,
                .power = 0,
                .type = TYPE_ROCK,
                .accuracy = 0,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_GIGA_DRAIN] =
            {
                .effect = EFFECT_ABSORB,
                .power = 60,
                .type = TYPE_GRASS,
                .accuracy = 100,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_ENDURE] =
            {
                .effect = EFFECT_ENDURE,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 3,
                .category = SPLIT_STATUS,
            },

        [MOVE_CHARM] =
            {
                .effect = EFFECT_ATTACK_DOWN_2,
                .power = 0,
                .type = TYPE_FAIRY,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
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
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_FALSE_SWIPE] =
            {
                .effect = EFFECT_FALSE_SWIPE,
                .power = 40,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 40,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SWAGGER] =
            {
                .effect = EFFECT_SWAGGER,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 90,
                .pp = 15,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_MILK_DRINK] =
            {
                .effect = EFFECT_SOFTBOILED,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_SPARK] =
            {
                .effect = EFFECT_PARALYZE_HIT,
                .power = 65,
                .type = TYPE_ELECTRIC,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_FURY_CUTTER] =
            {
                .effect = EFFECT_FURY_CUTTER,
                .power = 10,
                .type = TYPE_BUG,
                .accuracy = 95,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_STEEL_WING] =
            {
                .effect = EFFECT_DEFENSE_UP_HIT,
                .power = 70,
                .type = TYPE_STEEL,
                .accuracy = 90,
                .pp = 25,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_MEAN_LOOK] =
            {
                .effect = EFFECT_MEAN_LOOK,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
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
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
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
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_DEPENDS,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_HEAL_BELL] =
            {
                .effect = EFFECT_HEAL_BELL,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_RETURN] =
            {
                .effect = EFFECT_RETURN,
                .power = 1,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_PRESENT] =
            {
                .effect = EFFECT_PRESENT,
                .power = 1,
                .type = TYPE_NORMAL,
                .accuracy = 90,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_FRUSTRATION] =
            {
                .effect = EFFECT_FRUSTRATION,
                .power = 1,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SAFEGUARD] =
            {
                .effect = EFFECT_SAFEGUARD,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 25,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_PAIN_SPLIT] =
            {
                .effect = EFFECT_PAIN_SPLIT,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_SACRED_FIRE] =
            {
                .effect = EFFECT_THAW_HIT,
                .power = 100,
                .type = TYPE_FIRE,
                .accuracy = 95,
                .pp = 5,
                .secondaryEffectChance = 50,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_MAGNITUDE] =
            {
                .effect = EFFECT_MAGNITUDE,
                .power = 1,
                .type = TYPE_GROUND,
                .accuracy = 100,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_FOES_AND_ALLY,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_DYNAMIC_PUNCH] =
            {
                .effect = EFFECT_CONFUSE_HIT,
                .power = 100,
                .type = TYPE_FIGHTING,
                .accuracy = 50,
                .pp = 5,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_MEGAHORN] =
            {
                .effect = EFFECT_HIT,
                .power = 120,
                .type = TYPE_BUG,
                .accuracy = 85,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_DRAGON_BREATH] =
            {
                .effect = EFFECT_PARALYZE_HIT,
                .power = 60,
                .type = TYPE_DRAGON,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_BATON_PASS] =
            {
                .effect = EFFECT_BATON_PASS,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 40,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_ENCORE] =
            {
                .effect = EFFECT_ENCORE,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_PURSUIT] =
            {
                .effect = EFFECT_PURSUIT,
                .power = 40,
                .type = TYPE_DARK,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_RAPID_SPIN] =
            {
                .effect = EFFECT_RAPID_SPIN,
                .power = 20,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 40,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SWEET_SCENT] =
            {
                .effect = EFFECT_EVASION_DOWN,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_IRON_TAIL] =
            {
                .effect = EFFECT_DEFENSE_DOWN_HIT,
                .power = 100,
                .type = TYPE_STEEL,
                .accuracy = 75,
                .pp = 15,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_METAL_CLAW] =
            {
                .effect = EFFECT_ATTACK_UP_HIT,
                .power = 50,
                .type = TYPE_STEEL,
                .accuracy = 95,
                .pp = 35,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_VITAL_THROW] =
            {
                .effect = EFFECT_VITAL_THROW,
                .power = 70,
                .type = TYPE_FIGHTING,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = -1,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_MORNING_SUN] =
            {
                .effect = EFFECT_MORNING_SUN,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_SYNTHESIS] =
            {
                .effect = EFFECT_SYNTHESIS,
                .power = 0,
                .type = TYPE_GRASS,
                .accuracy = 0,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_MOONLIGHT] =
            {
                .effect = EFFECT_MOONLIGHT,
                .power = 0,
                .type = TYPE_FAIRY,
                .accuracy = 0,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_HIDDEN_POWER] =
            {
                .effect = EFFECT_HIDDEN_POWER,
                .power = 1,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_CROSS_CHOP] =
            {
                .effect = EFFECT_HIGH_CRITICAL,
                .power = 100,
                .type = TYPE_FIGHTING,
                .accuracy = 80,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_TWISTER] =
            {
                .effect = EFFECT_TWISTER,
                .power = 40,
                .type = TYPE_DRAGON,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 20,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_RAIN_DANCE] =
            {
                .effect = EFFECT_RAIN_DANCE,
                .power = 0,
                .type = TYPE_WATER,
                .accuracy = 0,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_SUNNY_DAY] =
            {
                .effect = EFFECT_SUNNY_DAY,
                .power = 0,
                .type = TYPE_FIRE,
                .accuracy = 0,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_CRUNCH] =
            {
                .effect = EFFECT_SPECIAL_DEFENSE_DOWN_HIT,
                .power = 80,
                .type = TYPE_DARK,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 20,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_MIRROR_COAT] =
            {
                .effect = EFFECT_MIRROR_COAT,
                .power = 1,
                .type = TYPE_PSYCHIC,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_DEPENDS,
                .priority = -5,
                .ignoresProtect = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_PSYCH_UP] =
            {
                .effect = EFFECT_PSYCH_UP,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_EXTREME_SPEED] =
            {
                .effect = EFFECT_QUICK_ATTACK,
                .power = 80,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 1,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_ANCIENT_POWER] =
            {
                .effect = EFFECT_ALL_STATS_UP_HIT,
                .power = 60,
                .type = TYPE_ROCK,
                .accuracy = 100,
                .pp = 5,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_SHADOW_BALL] =
            {
                .effect = EFFECT_SPECIAL_DEFENSE_DOWN_HIT,
                .power = 80,
                .type = TYPE_GHOST,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 20,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_FUTURE_SIGHT] =
            {
                .effect = EFFECT_FUTURE_SIGHT,
                .power = 80,
                .type = TYPE_PSYCHIC,
                .accuracy = 90,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_ROCK_SMASH] =
            {
                .effect = EFFECT_DEFENSE_DOWN_HIT,
                .power = 20,
                .type = TYPE_FIGHTING,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 50,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_WHIRLPOOL] =
            {
                .effect = EFFECT_TRAP,
                .power = 15,
                .type = TYPE_WATER,
                .accuracy = 70,
                .pp = 15,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_BEAT_UP] =
            {
                .effect = EFFECT_BEAT_UP,
                .power = 10,
                .type = TYPE_DARK,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_FAKE_OUT] =
            {
                .effect = EFFECT_FAKE_OUT,
                .power = 40,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 1,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_UPROAR] =
            {
                .effect = EFFECT_UPROAR,
                .power = 50,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_RANDOM,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_STOCKPILE] =
            {
                .effect = EFFECT_STOCKPILE,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_SPIT_UP] =
            {
                .effect = EFFECT_SPIT_UP,
                .power = 100,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_SWALLOW] =
            {
                .effect = EFFECT_SWALLOW,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_HEAT_WAVE] =
            {
                .effect = EFFECT_BURN_HIT,
                .power = 100,
                .type = TYPE_FIRE,
                .accuracy = 90,
                .pp = 10,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_HAIL] =
            {
                .effect = EFFECT_HAIL,
                .power = 0,
                .type = TYPE_ICE,
                .accuracy = 0,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_TORMENT] =
            {
                .effect = EFFECT_TORMENT,
                .power = 0,
                .type = TYPE_DARK,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_FLATTER] =
            {
                .effect = EFFECT_FLATTER,
                .power = 0,
                .type = TYPE_DARK,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_WILL_O_WISP] =
            {
                .effect = EFFECT_WILL_O_WISP,
                .power = 0,
                .type = TYPE_FIRE,
                .accuracy = 75,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
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
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_FACADE] =
            {
                .effect = EFFECT_FACADE,
                .power = 70,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_FOCUS_PUNCH] =
            {
                .effect = EFFECT_FOCUS_PUNCH,
                .power = 150,
                .type = TYPE_FIGHTING,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = -3,
                .makesContact = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SMELLING_SALT] =
            {
                .effect = EFFECT_SMELLINGSALT,
                .power = 60,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_FOLLOW_ME] =
            {
                .effect = EFFECT_FOLLOW_ME,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 3,
                .category = SPLIT_STATUS,
            },

        [MOVE_NATURE_POWER] =
            {
                .effect = EFFECT_NATURE_POWER,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_DEPENDS,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_CHARGE] =
            {
                .effect = EFFECT_CHARGE,
                .power = 0,
                .type = TYPE_ELECTRIC,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_TAUNT] =
            {
                .effect = EFFECT_TAUNT,
                .power = 0,
                .type = TYPE_DARK,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_HELPING_HAND] =
            {
                .effect = EFFECT_HELPING_HAND,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 5,
                .category = SPLIT_STATUS,
            },

        [MOVE_TRICK] =
            {
                .effect = EFFECT_TRICK,
                .power = 0,
                .type = TYPE_PSYCHIC,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_ROLE_PLAY] =
            {
                .effect = EFFECT_ROLE_PLAY,
                .power = 0,
                .type = TYPE_PSYCHIC,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_WISH] =
            {
                .effect = EFFECT_WISH,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_ASSIST] =
            {
                .effect = EFFECT_ASSIST,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_DEPENDS,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_INGRAIN] =
            {
                .effect = EFFECT_INGRAIN,
                .power = 0,
                .type = TYPE_GRASS,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_SUPERPOWER] =
            {
                .effect = EFFECT_SUPERPOWER,
                .power = 120,
                .type = TYPE_FIGHTING,
                .accuracy = 100,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_MAGIC_COAT] =
            {
                .effect = EFFECT_MAGIC_COAT,
                .power = 0,
                .type = TYPE_PSYCHIC,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_DEPENDS,
                .priority = 4,
                .category = SPLIT_STATUS,
            },

        [MOVE_RECYCLE] =
            {
                .effect = EFFECT_RECYCLE,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_REVENGE] =
            {
                .effect = EFFECT_REVENGE,
                .power = 60,
                .type = TYPE_FIGHTING,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = -4,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_BRICK_BREAK] =
            {
                .effect = EFFECT_BRICK_BREAK,
                .power = 75,
                .type = TYPE_FIGHTING,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_YAWN] =
            {
                .effect = EFFECT_YAWN,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_KNOCK_OFF] =
            {
                .effect = EFFECT_KNOCK_OFF,
                .power = 20,
                .type = TYPE_DARK,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_ENDEAVOR] =
            {
                .effect = EFFECT_ENDEAVOR,
                .power = 1,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_ERUPTION] =
            {
                .effect = EFFECT_ERUPTION,
                .power = 150,
                .type = TYPE_FIRE,
                .accuracy = 100,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_SKILL_SWAP] =
            {
                .effect = EFFECT_SKILL_SWAP,
                .power = 0,
                .type = TYPE_PSYCHIC,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_IMPRISON] =
            {
                .effect = EFFECT_IMPRISON,
                .power = 0,
                .type = TYPE_PSYCHIC,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_REFRESH] =
            {
                .effect = EFFECT_REFRESH,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_GRUDGE] =
            {
                .effect = EFFECT_GRUDGE,
                .power = 0,
                .type = TYPE_GHOST,
                .accuracy = 100,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_SNATCH] =
            {
                .effect = EFFECT_SNATCH,
                .power = 0,
                .type = TYPE_DARK,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_DEPENDS,
                .priority = 4,
                .category = SPLIT_STATUS,
            },

        [MOVE_SECRET_POWER] =
            {
                .effect = EFFECT_SECRET_POWER,
                .power = 70,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_DIVE] =
            {
                .effect = EFFECT_SEMI_INVULNERABLE,
                .power = 60,
                .type = TYPE_WATER,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_ARM_THRUST] =
            {
                .effect = EFFECT_MULTI_HIT,
                .power = 15,
                .type = TYPE_FIGHTING,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_CAMOUFLAGE] =
            {
                .effect = EFFECT_CAMOUFLAGE,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_TAIL_GLOW] =
            {
                .effect = EFFECT_SPECIAL_ATTACK_UP_2,
                .power = 0,
                .type = TYPE_BUG,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_LUSTER_PURGE] =
            {
                .effect = EFFECT_SPECIAL_DEFENSE_DOWN_HIT,
                .power = 70,
                .type = TYPE_PSYCHIC,
                .accuracy = 100,
                .pp = 5,
                .secondaryEffectChance = 50,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_MIST_BALL] =
            {
                .effect = EFFECT_SPECIAL_ATTACK_DOWN_HIT,
                .power = 70,
                .type = TYPE_PSYCHIC,
                .accuracy = 100,
                .pp = 5,
                .secondaryEffectChance = 50,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_FEATHER_DANCE] =
            {
                .effect = EFFECT_ATTACK_DOWN_2,
                .power = 0,
                .type = TYPE_FLYING,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_TEETER_DANCE] =
            {
                .effect = EFFECT_TEETER_DANCE,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_FOES_AND_ALLY,
                .priority = 0,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_BLAZE_KICK] =
            {
                .effect = EFFECT_BLAZE_KICK,
                .power = 85,
                .type = TYPE_FIRE,
                .accuracy = 90,
                .pp = 10,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_MUD_SPORT] =
            {
                .effect = EFFECT_MUD_SPORT,
                .power = 0,
                .type = TYPE_GROUND,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_ICE_BALL] =
            {
                .effect = EFFECT_ROLLOUT,
                .power = 30,
                .type = TYPE_ICE,
                .accuracy = 90,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_NEEDLE_ARM] =
            {
                .effect = EFFECT_FLINCH_MINIMIZE_HIT,
                .power = 60,
                .type = TYPE_GRASS,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SLACK_OFF] =
            {
                .effect = EFFECT_RESTORE_HP,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_HYPER_VOICE] =
            {
                .effect = EFFECT_HIT,
                .power = 90,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_POISON_FANG] =
            {
                .effect = EFFECT_POISON_FANG,
                .power = 50,
                .type = TYPE_POISON,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_CRUSH_CLAW] =
            {
                .effect = EFFECT_DEFENSE_DOWN_HIT,
                .power = 75,
                .type = TYPE_NORMAL,
                .accuracy = 95,
                .pp = 10,
                .secondaryEffectChance = 50,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_BLAST_BURN] =
            {
                .effect = EFFECT_RECHARGE,
                .power = 150,
                .type = TYPE_FIRE,
                .accuracy = 90,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_HYDRO_CANNON] =
            {
                .effect = EFFECT_RECHARGE,
                .power = 150,
                .type = TYPE_WATER,
                .accuracy = 90,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_METEOR_MASH] =
            {
                .effect = EFFECT_ATTACK_UP_HIT,
                .power = 100,
                .type = TYPE_STEEL,
                .accuracy = 85,
                .pp = 10,
                .secondaryEffectChance = 20,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_ASTONISH] =
            {
                .effect = EFFECT_FLINCH_MINIMIZE_HIT,
                .power = 30,
                .type = TYPE_GHOST,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_WEATHER_BALL] =
            {
                .effect = EFFECT_WEATHER_BALL,
                .power = 50,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_AROMATHERAPY] =
            {
                .effect = EFFECT_HEAL_BELL,
                .power = 0,
                .type = TYPE_GRASS,
                .accuracy = 0,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_FAKE_TEARS] =
            {
                .effect = EFFECT_SPECIAL_DEFENSE_DOWN_2,
                .power = 0,
                .type = TYPE_DARK,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_AIR_CUTTER] =
            {
                .effect = EFFECT_HIGH_CRITICAL,
                .power = 55,
                .type = TYPE_FLYING,
                .accuracy = 95,
                .pp = 25,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_OVERHEAT] =
            {
                .effect = EFFECT_OVERHEAT,
                .power = 140,
                .type = TYPE_FIRE,
                .accuracy = 90,
                .pp = 5,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_ODOR_SLEUTH] =
            {
                .effect = EFFECT_FORESIGHT,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 40,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_ROCK_TOMB] =
            {
                .effect = EFFECT_SPEED_DOWN_HIT,
                .power = 50,
                .type = TYPE_ROCK,
                .accuracy = 80,
                .pp = 10,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SILVER_WIND] =
            {
                .effect = EFFECT_ALL_STATS_UP_HIT,
                .power = 60,
                .type = TYPE_BUG,
                .accuracy = 100,
                .pp = 5,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_METAL_SOUND] =
            {
                .effect = EFFECT_SPECIAL_DEFENSE_DOWN_2,
                .power = 0,
                .type = TYPE_STEEL,
                .accuracy = 85,
                .pp = 40,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
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
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
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
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
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
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_WATER_SPOUT] =
            {
                .effect = EFFECT_ERUPTION,
                .power = 150,
                .type = TYPE_WATER,
                .accuracy = 100,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_SIGNAL_BEAM] =
            {
                .effect = EFFECT_CONFUSE_HIT,
                .power = 75,
                .type = TYPE_BUG,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_SHADOW_PUNCH] =
            {
                .effect = EFFECT_ALWAYS_HIT,
                .power = 60,
                .type = TYPE_GHOST,
                .accuracy = 0,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_EXTRASENSORY] =
            {
                .effect = EFFECT_FLINCH_MINIMIZE_HIT,
                .power = 80,
                .type = TYPE_PSYCHIC,
                .accuracy = 100,
                .pp = 30,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_SKY_UPPERCUT] =
            {
                .effect = EFFECT_SKY_UPPERCUT,
                .power = 85,
                .type = TYPE_FIGHTING,
                .accuracy = 90,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SAND_TOMB] =
            {
                .effect = EFFECT_TRAP,
                .power = 15,
                .type = TYPE_GROUND,
                .accuracy = 70,
                .pp = 15,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SHEER_COLD] =
            {
                .effect = EFFECT_OHKO,
                .power = 1,
                .type = TYPE_ICE,
                .accuracy = 30,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_MUDDY_WATER] =
            {
                .effect = EFFECT_ACCURACY_DOWN_HIT,
                .power = 95,
                .type = TYPE_WATER,
                .accuracy = 85,
                .pp = 10,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_BOTH,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_BULLET_SEED] =
            {
                .effect = EFFECT_MULTI_HIT,
                .power = 10,
                .type = TYPE_GRASS,
                .accuracy = 100,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_AERIAL_ACE] =
            {
                .effect = EFFECT_ALWAYS_HIT,
                .power = 60,
                .type = TYPE_FLYING,
                .accuracy = 0,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_ICICLE_SPEAR] =
            {
                .effect = EFFECT_MULTI_HIT,
                .power = 10,
                .type = TYPE_ICE,
                .accuracy = 100,
                .pp = 30,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_IRON_DEFENSE] =
            {
                .effect = EFFECT_DEFENSE_UP_2,
                .power = 0,
                .type = TYPE_STEEL,
                .accuracy = 0,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_BLOCK] =
            {
                .effect = EFFECT_MEAN_LOOK,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .magicCoatAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_HOWL] =
            {
                .effect = EFFECT_ATTACK_UP,
                .power = 0,
                .type = TYPE_NORMAL,
                .accuracy = 0,
                .pp = 40,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_DRAGON_CLAW] =
            {
                .effect = EFFECT_HIT,
                .power = 80,
                .type = TYPE_DRAGON,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_FRENZY_PLANT] =
            {
                .effect = EFFECT_RECHARGE,
                .power = 150,
                .type = TYPE_GRASS,
                .accuracy = 90,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_BULK_UP] =
            {
                .effect = EFFECT_BULK_UP,
                .power = 0,
                .type = TYPE_FIGHTING,
                .accuracy = 0,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_BOUNCE] =
            {
                .effect = EFFECT_SEMI_INVULNERABLE,
                .power = 85,
                .type = TYPE_FLYING,
                .accuracy = 85,
                .pp = 5,
                .secondaryEffectChance = 30,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_MUD_SHOT] =
            {
                .effect = EFFECT_SPEED_DOWN_HIT,
                .power = 55,
                .type = TYPE_GROUND,
                .accuracy = 95,
                .pp = 15,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_POISON_TAIL] =
            {
                .effect = EFFECT_POISON_TAIL,
                .power = 50,
                .type = TYPE_POISON,
                .accuracy = 100,
                .pp = 25,
                .secondaryEffectChance = 10,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_COVET] =
            {
                .effect = EFFECT_THIEF,
                .power = 40,
                .type = TYPE_NORMAL,
                .accuracy = 100,
                .pp = 40,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .ignoresKingsRock = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_VOLT_TACKLE] =
            {
                .effect = EFFECT_DOUBLE_EDGE,
                .power = 120,
                .type = TYPE_ELECTRIC,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_MAGICAL_LEAF] =
            {
                .effect = EFFECT_ALWAYS_HIT,
                .power = 60,
                .type = TYPE_GRASS,
                .accuracy = 0,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_WATER_SPORT] =
            {
                .effect = EFFECT_WATER_SPORT,
                .power = 0,
                .type = TYPE_WATER,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .category = SPLIT_STATUS,
            },

        [MOVE_CALM_MIND] =
            {
                .effect = EFFECT_CALM_MIND,
                .power = 0,
                .type = TYPE_PSYCHIC,
                .accuracy = 0,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_LEAF_BLADE] =
            {
                .effect = EFFECT_HIGH_CRITICAL,
                .power = 70,
                .type = TYPE_GRASS,
                .accuracy = 100,
                .pp = 15,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .makesContact = TRUE,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_DRAGON_DANCE] =
            {
                .effect = EFFECT_DRAGON_DANCE,
                .power = 0,
                .type = TYPE_DRAGON,
                .accuracy = 0,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_USER,
                .priority = 0,
                .ignoresProtect = TRUE,
                .ignoresKingsRock = TRUE,
                .snatchAffected = TRUE,
                .category = SPLIT_STATUS,
            },

        [MOVE_ROCK_BLAST] =
            {
                .effect = EFFECT_MULTI_HIT,
                .power = 25,
                .type = TYPE_ROCK,
                .accuracy = 80,
                .pp = 10,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_PHYSICAL,
            },

        [MOVE_SHOCK_WAVE] =
            {
                .effect = EFFECT_ALWAYS_HIT,
                .power = 60,
                .type = TYPE_ELECTRIC,
                .accuracy = 0,
                .pp = 20,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_WATER_PULSE] =
            {
                .effect = EFFECT_CONFUSE_HIT,
                .power = 60,
                .type = TYPE_WATER,
                .accuracy = 100,
                .pp = 20,
                .secondaryEffectChance = 20,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_DOOM_DESIRE] =
            {
                .effect = EFFECT_FUTURE_SIGHT,
                .power = 120,
                .type = TYPE_STEEL,
                .accuracy = 85,
                .pp = 5,
                .secondaryEffectChance = 0,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .category = SPLIT_SPECIAL,
            },

        [MOVE_PSYCHO_BOOST] =
            {
                .effect = EFFECT_OVERHEAT,
                .power = 140,
                .type = TYPE_PSYCHIC,
                .accuracy = 90,
                .pp = 5,
                .secondaryEffectChance = 100,
                .target = MOVE_TARGET_SELECTED,
                .priority = 0,
                .mirrorMoveAffected = TRUE,
                .category = SPLIT_SPECIAL,
            },
};
