PetalburgWoods_MapObjects:: @ 838C14C
	object_event 1, MAP_OBJ_GFX_CUTTABLE_TREE, 0, 19, 0, 10, 0, 3, 1, 0, 0, 0, 0, 0, 0, CuttableTreeScript, 17, 0, 0
	object_event 2, MAP_OBJ_GFX_CUTTABLE_TREE, 0, 19, 0, 11, 0, 3, 1, 0, 0, 0, 0, 0, 0, CuttableTreeScript, 18, 0, 0
	object_event 3, 241, 0, 26, 0, 17, 0, 3, 10, 0, 0, 0, 0, 0, 0, 0x0, 725, 0, 0
	object_event 4, MAP_OBJ_GFX_MAN_2, 0, 26, 0, 20, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0x0, 724, 0, 0
	object_event 5, MAP_OBJ_GFX_ITEM_BALL, 0, 45, 0, 7, 0, 3, 8, 0, 0, 0, 0, 0, 0, PetalburgWoods_EventScript_1B175F, 1056, 0, 0
	object_event 6, MAP_OBJ_GFX_ITEM_BALL, 0, 35, 0, 20, 0, 3, 8, 0, 0, 0, 0, 0, 0, PetalburgWoods_EventScript_1B1752, 1055, 0, 0
	object_event 7, MAP_OBJ_GFX_ITEM_BALL, 0, 4, 0, 8, 0, 3, 1, 0, 0, 0, 0, 0, 0, PetalburgWoods_EventScript_1B176C, 1058, 0, 0
	object_event 8, MAP_OBJ_GFX_BOY_2, 0, 15, 0, 19, 0, 3, 3, 33, 0, 0, 0, 0, 0, PetalburgWoods_EventScript_15CECA, 0, 0, 0
	object_event 9, MAP_OBJ_GFX_BUG_CATCHER, 0, 7, 0, 32, 0, 3, 22, 0, 0, 1, 0, 3, 0, PetalburgWoods_EventScript_15CF27, 0, 0, 0
	object_event 10, MAP_OBJ_GFX_BUG_CATCHER, 0, 4, 0, 14, 0, 3, 20, 0, 0, 1, 0, 3, 0, PetalburgWoods_EventScript_15CF3E, 0, 0, 0
	object_event 11, MAP_OBJ_GFX_BOY_3, 0, 30, 0, 34, 0, 3, 2, 18, 0, 0, 0, 0, 0, PetalburgWoods_EventScript_15CED3, 0, 0, 0
	object_event 12, MAP_OBJ_GFX_ITEM_BALL, 0, 4, 0, 26, 0, 3, 1, 17, 0, 0, 0, 0, 0, PetalburgWoods_EventScript_1B1779, 1117, 0, 0
	object_event 13, MAP_OBJ_GFX_GIRL_2, 0, 33, 0, 5, 0, 3, 1, 17, 0, 0, 0, 0, 0, PetalburgWoods_EventScript_15CEDC, 0, 0, 0

PetalburgWoods_MapWarps:: @ 838C284
	warp_def 14, 5, 0, 2, Route104
	warp_def 15, 5, 0, 3, Route104
	warp_def 16, 38, 0, 4, Route104
	warp_def 17, 38, 0, 5, Route104
	warp_def 36, 38, 0, 6, Route104
	warp_def 37, 38, 0, 7, Route104

PetalburgWoods_MapCoordEvents:: @ 838C2B4
	coord_event 26, 23, 3, 0, 0x4098, 0, 0, PetalburgWoods_EventScript_15CCA8
	coord_event 27, 23, 3, 0, 0x4098, 0, 0, PetalburgWoods_EventScript_15CD42

PetalburgWoods_MapBGEvents:: @ 838C2D4
	bg_event 14, 32, 3, 0, 0, PetalburgWoods_EventScript_15CF15
	bg_event 39, 35, 3, 7, 0, ITEM_POTION, 58, 0
	bg_event 26, 6, 3, 7, 0, ITEM_TINY_MUSHROOM, 59, 0
	bg_event 40, 29, 3, 7, 0, ITEM_TINY_MUSHROOM, 60, 0
	bg_event 4, 19, 3, 7, 0, ITEM_POKE_BALL, 61, 0
	bg_event 11, 8, 3, 0, 0, PetalburgWoods_EventScript_15CF1E

PetalburgWoods_MapEvents:: @ 838C31C
	map_events PetalburgWoods_MapObjects, PetalburgWoods_MapWarps, PetalburgWoods_MapCoordEvents, PetalburgWoods_MapBGEvents
