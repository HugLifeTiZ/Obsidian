----------------------------------------------------------------
--  MODULE: ZDoom Marines
----------------------------------------------------------------
--
--  Copyright (C) 2009 Enhas
--
--  This program is free software; you can redistribute it and/or
--  modify it under the terms of the GNU General Public License
--  as published by the Free Software Foundation; either version 2,
--  of the License, or (at your option) any later version.
--
--  This program is distributed in the hope that it will be useful,
--  but WITHOUT ANY WARRANTY; without even the implied warranty of
--  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--  GNU General Public License for more details.
--
----------------------------------------------------------------

ZDOOM_MARINE = { }

ZDOOM_MARINE.MONSTERS =
{
  -- None of these drop anything.

  -- The damage values below are not accurate,
  -- to keep too much health from spawning in the map.  May need more tweaking.

  -- Marines of all types (well, except the fist) are extremely dangerous,
  -- hence the low probabilities, low densities and nasty flag.
  -- We want them all to be rare.

  marine_fist =
  {
    id = 9101,
    r = 16,
    h = 56,
    prob = 1,
    health = 100,
    damage = 4,
    attack = "melee",
    nasty = true,
    density = 0.2,
  },

  marine_berserk =
  {
    id = 9102,
    r = 16,
    h = 56,
    prob = 6,
    health = 100,
    damage = 40,
    attack = "melee",
    nasty = true,
    density = 0.2,
  },

  marine_saw =
  {
    id = 9103,
    r = 16,
    h = 56,
    prob = 4,
    health = 100,
    damage = 15,
    attack = "melee",
    nasty = true,
    density = 0.2,
  },

  marine_pistol =
  {
    id = 9104,
    r = 16,
    h = 56,
    prob = 12,
    health = 100,
    damage = 8,
    attack = "hitscan",
    nasty = true,
    density = 0.5,
  },

  marine_shotty =
  {
    id = 9105,
    r = 16,
    h = 56,
    prob = 4,
    health = 100,
    damage = 10,
    attack = "hitscan",
    nasty = true,
    density = 0.4,
  },

  marine_ssg =
  {
    id = 9106,
    r = 16,
    h = 56,
    prob = 6,
    health = 100,
    damage = 65,
    attack = "hitscan",
    nasty = true,
    density = 0.3,
  },

  marine_chain =
  {
    id = 9107,
    r = 16,
    h = 56,
    prob = 6,
    health = 100,
    damage = 50,
    attack = "hitscan",
    nasty = true,
    density = 0.3,
  },

  marine_rocket =
  {
    id = 9108,
    r = 16,
    h = 56,
    prob = 4,
    crazy_prob = 10,
    health = 100,
    damage = 100,
    attack = "missile",
    nasty = true,
    density = 0.2,
  },

  marine_plasma =
  {
    id = 9109,
    r = 16,
    h = 56,
    prob = 4,
    crazy_prob = 6,
    health = 100,
    damage = 70,
    attack = "missile",
    nasty = true,
    density = 0.2,
  },

  marine_rail =
  {
    id = 9110,
    r = 16,
    h = 56,
    prob = 2,
    health = 100,
    damage = 100,
    attack = "hitscan",
    nasty = true,
    density = 0.1,
  },

  marine_bfg =
  {
    id = 9111,
    r = 16,
    h = 56,
    prob = 2,
    health = 100,
    damage = 100,
    attack = "missile",
    nasty = true,
    density = 0.1,
  },
}


ZDOOM_MARINE.CHOICES =
{
  "plenty", _("Plenty"),
  "scarce", _("Scarce"),
  "heaps",  _("Heaps"),
}

ZDOOM_MARINE.FACTORS =
{
  scarce = 0.4,
  plenty = 1.0,
  heaps  = 2.5,
}


function ZDOOM_MARINE.setup(self)

  module_param_up(self)

  local factor = ZDOOM_MARINE.FACTORS[PARAM["zdoom_marine_qty"]]

  for name,_ in pairs(ZDOOM_MARINE.MONSTERS) do
    local M = GAME.MONSTERS[name]

    if M and factor then
      M.prob = M.prob * factor
      M.crazy_prob = (M.crazy_prob or M.prob) * factor
    end
  end

  if not PARAM.doom2_weapons then
    GAME.MONSTERS["marine_ssg"] = nil
  end

end


-- Monster / Weapon prefs may go here eventually

OB_MODULES["zdoom_marines"] =
{
  label = _("ZDoom Marines"),

  game = "doomish",

  engine = "zdoom",

  tables =
  {
    ZDOOM_MARINE
  },

  hooks =
  {
    setup = ZDOOM_MARINE.setup
  },

  options =
  {
    {
      name = "zdoom_marine_qty",
      label = _("Default Quantity"),
      choices = ZDOOM_MARINE.CHOICES,
      randomize_group = "monsters"
    },
  },
}


----------------------------------------------------------------


ZDOOM_MARINE.CTL_CHOICES =
{
  "default", _("DEFAULT"),
  "none",    _("None at all"),
  "scarce",  _("Scarce"),
  "less",    _("Less"),
  "plenty",  _("Plenty"),
  "more",    _("More"),
  "heaps",   _("Heaps"),
  "insane",  _("INSANE"),
}

-- these probabilities are lower than in the Monster Control module
-- because these dudes really pack a punch.

ZDOOM_MARINE.CTL_PROBS =
{
  none   = 0,
  scarce = 1,
  less   = 4,
  plenty = 20,
  more   = 70,
  heaps  = 200,
  insane = 1000,
}


function ZDOOM_MARINE.control_setup(self)

  module_param_up(self)

  for _,opt in pairs(self.options) do

    local M = GAME.MONSTERS[opt.name]

    if M and opt.value ~= "default" then
      local prob = ZDOOM_MARINE.CTL_PROBS[opt.value]

      M.prob = prob
      M.crazy_prob = prob

      if prob >  50 then M.density = 0.5 end
      if prob > 150 then M.density = 1.0 end
    end
  end -- for opt
end


OB_MODULES["zdoom_marine_control"] =
{
  label = _("ZDoom Marines : Control"),

  module = "zdoom_marines",
  hooks =
  {
    setup = ZDOOM_MARINE.control_setup
  },

  options =
  {
    { name = "marine_fist", label="Fist Marine",        choices=ZDOOM_MARINE.CTL_CHOICES, randomize_group = "monsters" },
    { name = "marine_berserk", label="Berserk Marine",     choices=ZDOOM_MARINE.CTL_CHOICES, randomize_group = "monsters" },
    { name = "marine_saw", label="Chainsaw Marine",    choices=ZDOOM_MARINE.CTL_CHOICES, randomize_group = "monsters" },
    { name = "marine_pistol", label="Pistol Marine",      choices=ZDOOM_MARINE.CTL_CHOICES, randomize_group = "monsters" },
    { name = "marine_shotty", label="Shotgun Marine",     choices=ZDOOM_MARINE.CTL_CHOICES, randomize_group = "monsters" },
    { name = "marine_ssg", label="SSG Marine",         choices=ZDOOM_MARINE.CTL_CHOICES, randomize_group = "monsters" },
    { name = "marine_chain", label="Chaingun Marine",    choices=ZDOOM_MARINE.CTL_CHOICES, randomize_group = "monsters" },
    { name = "marine_rocket", label="Rocket Marine",      choices=ZDOOM_MARINE.CTL_CHOICES, randomize_group = "monsters" },
    { name = "marine_plasma", label="Plasma Marine",      choices=ZDOOM_MARINE.CTL_CHOICES, randomize_group = "monsters" },
    { name = "marine_rail", label="Railgun Marine",     choices=ZDOOM_MARINE.CTL_CHOICES, randomize_group = "monsters" },
    { name = "marine_bfg", label="BFG Marine",         choices=ZDOOM_MARINE.CTL_CHOICES, randomize_group = "monsters" },
  },
}

