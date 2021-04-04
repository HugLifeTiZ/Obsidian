HARMONY = { }

----------------------------------------------------------------
gui.import("params")
gui.import("entities")
gui.import("monsters")
gui.import("pickups")
gui.import("weapons")
gui.import("shapes")
gui.import("materials")
gui.import("themes")
gui.import("levels")
gui.import("resources")
----------------------------------------------------------------

UNFINISHED["harmony"] =
{
	label = _("Harmony"),
	priority = 29,
	
	format = "doom",
	sub_format = "harmony",
	
	game_dir = "harmony",
	iwad_name = "harm1.wad",
	
	tables =
	{
		HARMONY
	},
	
	hooks =
	{
		setup = HARMONY.setup,
		get_levels = HARMONY.get_levels,
		all_done = HARMONY.all_done
	},
}