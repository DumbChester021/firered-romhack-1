@ commands

	.macro loadspritegfx tag:req
	.byte 0x0
	.2byte \tag
	.endm

	.macro unloadspritegfx tag:req
	.byte 0x1
	.2byte \tag
	.endm

.macro createsprite template:req, anim_battler:req, subpriority_offset:req, argv:vararg
	.byte 0x02
	.4byte \template
	.if \anim_battler == ANIM_TARGET
	.byte ANIMSPRITE_IS_TARGET | (\subpriority_offset & 0x7F)
	.else
	.byte (\subpriority_offset & 0x7F)
	.endif
	.byte (.Lsprite_\@_2 - .Lsprite_\@_1) / 2
.Lsprite_\@_1:
	.2byte \argv
.Lsprite_\@_2:
	.endm

	.macro createvisualtask addr:req, priority:req, argv:vararg
	.byte 0x03
	.4byte \addr
	.byte \priority
	.byte (.Lcreatetask_\@_2 - .Lcreatetask_\@_1) / 2
.Lcreatetask_\@_1:
	.2byte \argv
.Lcreatetask_\@_2:
	.endm

	.macro delay frames:req
	.byte 0x4
	.byte \frames
	.endm

	.macro waitforvisualfinish
	.byte 0x5
	.endm

	.macro nop
	.byte 0x6
	.endm

	.macro nop2
	.byte 0x7
	.endm

	.macro end
	.byte 0x8
	.endm

	.macro playse se:req
	.byte 0x9
	.2byte \se
	.endm

	.macro monbg battler:req
	.byte 0xa
	.byte \battler
	.endm

	.macro clearmonbg battler:req
	.byte 0xb
	.byte \battler
	.endm

	.macro setalpha eva:req, evb:req
	.byte 0x0C
	.2byte ((\evb) << 8) | (\eva)
	.endm

	.macro blendoff
	.byte 0xd
	.endm

	.macro call ptr:req
	.byte 0xe
	.4byte \ptr
	.endm

	.macro return
	.byte 0xf
	.endm

	.macro setarg argId:req, value:req
	.byte 0x10
	.byte \argId
	.2byte \value
	.endm

	.macro choosetwoturnanim ptr1:req, ptr2:req
	.byte 0x11
	.4byte \ptr1
	.4byte \ptr2
	.endm

	.macro jumpifmoveturn value:req, ptr:req
	.byte 0x12
	.byte \value
	.4byte \ptr
	.endm

	.macro goto ptr:req
	.byte 0x13
	.4byte \ptr
	.endm

	.macro fadetobg bg:req
	.byte 0x14
	.byte \bg
	.endm

	.macro restorebg
	.byte 0x15
	.endm

	.macro waitbgfadeout
	.byte 0x16
	.endm

	.macro waitbgfadein
	.byte 0x17
	.endm

	.macro changebg bg:req
	.byte 0x18
	.byte \bg
	.endm

	.macro playsewithpan se:req, pan:req
	.byte 0x19
	.2byte \se
	.byte \pan
	.endm

	.macro setpan pan:req
	.byte 0x1a
	.byte \pan
	.endm

	.macro panse se:req, currentPan:req, targetPan:req, incrementPan:req, delay:req
	.byte 0x1b
	.2byte \se
	.byte \currentPan
	.byte \targetPan
	.byte \incrementPan
	.byte \delay
	.endm

	.macro loopsewithpan se:req, pan:req, wait:req, times:req
	.byte 0x1c
	.2byte \se
	.byte \pan
	.byte \wait
	.byte \times
	.endm

	.macro waitplaysewithpan se:req, pan:req, wait:req
	.byte 0x1d
	.2byte \se
	.byte \pan
	.byte \wait
	.endm

	.macro setbldcnt bldcnt:req
	.byte 0x1e
	.2byte \bldcnt
	.endm

	.macro createsoundtask addr:req, argv:vararg
	.byte 0x1F
	.4byte \addr
	.byte (.Lcreatetask_1F_\@_2 - .Lcreatetask_1F_\@_1) / 2
.Lcreatetask_1F_\@_1:
	.2byte \argv
.Lcreatetask_1F_\@_2:
	.endm

	.macro waitsound
	.byte 0x20
	.endm

	.macro jumpargeq argId:req, value:req, ptr:req
	.byte 0x21
	.byte \argId
	.2byte \value
	.4byte \ptr
	.endm

	.macro monbg_static battler:req
	.byte 0x22
	.byte \battler
	.endm

	.macro clearmonbg_static battler:req
	.byte 0x23
	.byte \battler
	.endm

	.macro jumpifcontest ptr:req
	.byte 0x24
	.4byte \ptr
	.endm

	.macro fadetobgfromset bgOpponent:req, bgPlayer:req, bgContest:req
	.byte 0x25
	.byte \bgOpponent
	.byte \bgPlayer
	.byte \bgContest
	.endm

	.macro panse_adjustnone se:req, currentPan:req, targetPan:req, incrementPan:req, delay:req
	.byte 0x26
	.2byte \se
	.byte \currentPan
	.byte \targetPan
	.byte \incrementPan
	.byte \delay
	.endm

	.macro panse_adjustall se:req, currentPan:req, targetPan:req, incrementPan:req, delay:req
	.byte 0x27
	.2byte \se
	.byte \currentPan
	.byte \targetPan
	.byte \incrementPan
	.byte \delay
	.endm

	.macro splitbgprio battler:req
	.byte 0x28
	.byte \battler
	.endm

	.macro splitbgprio_all
	.byte 0x29
	.endm

	.macro splitbgprio_foes battler:req
	.byte 0x2a
	.byte \battler
	.endm

	.macro invisible battler:req
	.byte 0x2b
	.byte \battler
	.endm

	.macro visible battler:req
	.byte 0x2c
	.byte \battler
	.endm

	.macro teamattack_moveback battler:req
	.byte 0x2d
	.byte \battler
	.endm

	.macro teamattack_movefwd battler:req
	.byte 0x2e
	.byte \battler
	.endm

	.macro stopsound
	.byte 0x2f
	.endm

	.macro createvisualtaskontargets task:req, priority:req, battlerargindex:req, argv:vararg
	.byte 0x30
	.4byte \task
	.byte \priority
	.byte \battlerargindex
	.byte (.Ltask_\@_2 - .Ltask_\@_1) / 2
.Ltask_\@_1:
	.2byte \argv
.Ltask_\@_2:
	.endm

	.macro createspriteontargets template:req, anim_battler:req, subpriority_offset:req, battlerargindex:req, argv:vararg
	.byte 0x31
	.4byte \template
	.if \anim_battler == ANIM_TARGET
	.byte 0x80 | (\subpriority_offset & 0x7F)
	.else
	.byte (\subpriority_offset & 0x7F)
	.endif
	.byte \battlerargindex
	.byte (.Lsprite_\@_2 - .Lsprite_\@_1) / 2
.Lsprite_\@_1:
	.2byte \argv
.Lsprite_\@_2:
	.endm

	.macro createspriteontargets_onpos template:req, anim_battler:req, subpriority_offset:req, battlerargindex:req, argv:vararg
	.byte 0x32
	.4byte \template
	.if \anim_battler == ANIM_TARGET
	.byte 0x80 | (\subpriority_offset & 0x7F)
	.else
	.byte (\subpriority_offset & 0x7F)
	.endif
	.byte \battlerargindex
	.byte (.Lsprite_\@_2 - .Lsprite_\@_1) / 2
.Lsprite_\@_1:
	.2byte \argv
.Lsprite_\@_2:
	.endm

	.macro jumpifmovetypeequal type:req, jumpInstr:req
	.byte 0x33
	.byte \type
	.4byte \jumpInstr
	.endm

	.macro createdragondartsprite anim_battler:req, subpriority_offset:req, argv:vararg
	.byte 0x34
	.if \anim_battler == ANIM_TARGET
	.byte ANIMSPRITE_IS_TARGET | (\subpriority_offset & 0x7F)
	.else
	.byte (\subpriority_offset & 0x7F)
	.endif
	.byte (.Lsprite_\@_2 - .Lsprite_\@_1) / 2
.Lsprite_\@_1:
	.2byte \argv
.Lsprite_\@_2:
	.endm

@ useful macros
	.macro jumpreteq value:req, ptr:req
	jumpargeq ARG_RET_ID, \value, \ptr
	.endm
	
	.macro jumprettrue ptr:req
	jumpreteq TRUE, \ptr
	.endm
	
	.macro jumpretfalse ptr:req
	jumpreteq FALSE, \ptr
	.endm

	.macro jumpifdoublebattle ptr:req
	createvisualtask AnimTask_IsDoubleBattle, 0
	jumprettrue \ptr
	.endm

@ createsprite wrappers
	.macro simple_palette_blend unused_anim_battler=ANIM_ATTACKER, unused_subpriority_offset=2, selector:req, delay:req, initial_blend_y:req, target_blend_y:req, color:req
	createsprite gSimplePaletteBlendSpriteTemplate, \unused_anim_battler, \unused_subpriority_offset, \selector, \delay, \initial_blend_y, \target_blend_y, \color
	.endm

	.macro create_basic_hitsplat_sprite anim_battler:req, subpriority_offset:req, x:req, y:req, relative_to:req, animation:req
	createsprite gBasicHitSplatSpriteTemplate, \anim_battler, \subpriority_offset, \x, \y, \relative_to, \animation
	.endm

	.macro create_random_pos_hitsplat_sprite anim_battler:req, subpriority_offset:req, relative_to:req, animation
	.ifnb \animation
	createsprite gRandomPosHitSplatSpriteTemplate, \anim_battler, \subpriority_offset, \relative_to, \animation
	.else
	createsprite gRandomPosHitSplatSpriteTemplate, \anim_battler, \subpriority_offset, \relative_to, -1
	.endif
	.endm

	.macro complex_palette_blend unused_anim_battler=ANIM_ATTACKER, unused_subpriority_offset=2, selector:req, delay:req, num_blends:req, color1:req, blend_y1:req, color2:req, blend_y2:req
	createsprite gComplexPaletteBlendSpriteTemplate, \unused_anim_battler, \unused_subpriority_offset, \selector, \delay, \num_blends, \color1, \blend_y1, \color2, \blend_y2
	.endm

	.macro blend_color_cycle priority=2, selector:req, delay:req, num_blends:req, initial_blend_y:req, target_blend_y:req, color:req
	createvisualtask AnimTask_BlendColorCycle, \priority, \selector, \delay, \num_blends, \initial_blend_y, \target_blend_y, \color
	.endm

	.macro create_sharp_teeth_sprite anim_battler:req, subpriority_offset:req, x:req, y:req, animation:req, x_velocity:req, y_velocity:req, half_duration:req
	createsprite gSharpTeethSpriteTemplate, \anim_battler, \subpriority_offset, \x, \y, \animation, 256 * \x_velocity, 256 * \y_velocity, \half_duration
	.endm

	.macro create_twister_leaf_sprite anim_battler:req, subpriority_offset:req, duration:req, distance_y:req, wave_period:req, wave_amplitude:req, speed_up_on_frame:req
	createsprite gTwisterLeafSpriteTemplate, \anim_battler, \subpriority_offset, \duration, \distance_y, \wave_period, \wave_amplitude, \speed_up_on_frame
	.endm

	.macro create_flashing_hitsplat_sprite anim_battler:req, subpriority_offset:req, x:req, y:req, relative_to:req, animation:req
	createsprite gFlashingHitSplatSpriteTemplate, \anim_battler, \subpriority_offset, \x, \y, \relative_to, \animation
	.endm

	.macro create_cross_impact_sprite anim_battler:req, subpriority_offset:req, x:req, y:req, relative_to:req, duration:req
	createsprite gCrossImpactSpriteTemplate, \anim_battler, \subpriority_offset, \x, \y, \relative_to, \duration
	.endm
