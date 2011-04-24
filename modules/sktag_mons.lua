----------------------------------------------------------------
--  MODULE: Skulltag Monsters and Items
----------------------------------------------------------------
--
--  Copyright (C)      2009 Andrew Apted
--  Copyright (C) 2009-2010 Chris Pisarczyk
--  Copyright (C) 2009-2010 Enhas
--
--  This program is free software; you can redistribute it and/or
--  modify it under the terms of the GNU General Public License
--  as published by the Free Software Foundation; either version 2
--  of the License, or (at your option) any later version.
--
--  This program is distributed in the hope that it will be useful,
--  but WITHOUT ANY WARRANTY; without even the implied warranty of
--  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--  GNU General Public License for more details.
--
----------------------------------------------------------------

SKTAG_MONS = { }

SKTAG_MONS.MONSTERS =
{
  darkimp =
  {
    level = 1
    prob = 55
    health = 120
    damage = 30
    attack = "missile"
    density = 0.7
  }

  superguy =
  {
    level = 3
    prob = 33
    health = 120
    damage = 65
    attack = "hitscan"
    give = { {weapon="super"}, {ammo="shell",count=4} }
    density = 0.5
  }

  bldemon =
  {
    level = 3
    prob = 20
    health = 300
    damage = 25
    attack = "melee"
    density = 0.5
  }

  cacolant =
  {
    level = 5
    prob = 25
    crazy_prob = 10
    health = 800
    damage = 55
    attack = "missile"
    density = 0.4
    float = true
  }

  hectebus =
  {
    level = 7
    prob = 10
    skip_prob = 100
    health = 1200
    damage = 120
    attack = "missile"
    density = 0.2
    never_promote = true
  }

  abaddon =
  {
    level = 7
    prob = 15
    health = 1200
    damage = 65
    attack = "missile"
    density = 0.2
    float = true
  }

  belphegor =
  {
    level = 8
    prob = 10
    health = 1500
    damage = 80
    attack = "missile"
    density = 0.2
  }
}


SKTAG_MONS.WEAPONS =
{
  minigun =
  {
    pref = 85
    add_prob = 20
    start_prob = 10
    rate = 15
    damage = 10
    attack = "hitscan"
    ammo = "bullet"
    per = 1
    give = { {ammo="bullet",count=20} }
  }

  glaunch =
  {
    pref = 50
    add_prob = 15
    start_prob = 8
    rate = 1.7
    damage = 80
    attack = "missile"
    splash = { 50,20,5 }
    ammo = "rocket"
    per = 1
    give = { {ammo="rocket",count=2} }
  }

  railgun =
  {
    pref = 20
    add_prob = 10
    start_prob = 5
    rarity = 3
    rate = 3.0
    damage = 200
    attack = "hitscan"
    ammo = "cell"
    per = 10
    give = { {ammo="cell",count=40} }
  }

  bfg10k =
  {
    pref = 15
    add_prob = 5
    start_prob = 1
    rarity = 4
    rate = 6.0
    damage = 160
    attack = "missile"
    splash = {60,45,30,30,20,10}
    ammo = "cell"
    per = 5
    give = { {ammo="cell",count=40} }
  }
}


SKTAG_MONS.PICKUPS =
{
  max_potion =
  {
    prob = 1
    cluster = { 1,2 }
    give = { {health=1} }
  }

  max_helmet =
  {
    prob = 1
    armor = true
    cluster = { 1,2 }
    give = { {health=1} }
  }

  red_armor =
  {
    prob = 2
    armor = true
    big_item = true
    give = { {health=90} }
  }
}


SKTAG_MONS.CHOICES =
{
  "some",   "Some",
  "few",    "Few",
  "heaps",  "Heaps",
}

SKTAG_MONS.FACTORS =
{
  few   = 0.2
  some  = 1.0
  heaps = 5.0
}


function SKTAG_MONS.setup(self)
  if not PARAM.doom2_monsters then
    GAME.MONSTERS["hectebus"] = nil
    GAME.MONSTERS["superguy"].give = nil
  end

  -- apply the 'Default Monsters' choice
  local factor = SKTAG_MONS.FACTORS[self.options.def_mon.value]

  for name,_ in pairs(SKTAG_MONS.MONSTERS) do
    local M = GAME.MONSTERS[name]
    if M and factor then
      M.prob = M.prob * factor
      M.crazy_prob = (M.crazy_prob or M.prob) * factor
    end
  end

  -- apply the 'Default Weapons' choice
  factor = SKTAG_MONS.FACTORS[self.options.def_weap.value]

  for name,_ in pairs(SKTAG_MONS.WEAPONS) do
    local W = GAME.WEAPONS[name]
    if W and factor then
      W.add_prob   = math.max(4, W.add_prob)   * factor
      W.start_prob = math.max(4, W.start_prob) * factor
    end
  end
end


OB_MODULES["sktag_mons"] =
{
  label = "Skulltag : Monsters and Items"

  for_games = { doom1=1, doom2=1 }
  for_modes = { sp=1, coop=1 }
  for_engines = { skulltag=1 }

  tables =
  {
    SKULLTAG
  }

  hooks =
  {
    setup = SKTAG_MONS.setup
  }

  options =
  {
    def_mon =
    {
      label = "Default Monsters", choices = SKTAG_MONS.CHOICES
    }

    def_weap =
    {
      label = "Default Weapons", choices = SKTAG_MONS.CHOICES
    }
  }
}


----------------------------------------------------------------


SKTAG_MONS.CONTROL_CHOICES =
{
  "default", "DEFAULT",
  "none",    "None at all",
  "scarce",  "Scarce",
  "less",    "Less",
  "plenty",  "Plenty",
  "more",    "More",
  "heaps",   "Heaps",
  "insane",  "INSANE",
}

SKTAG_MONS.CONTROL_PROBS =
{
  none   = 0
  scarce = 2
  less   = 10
  plenty = 50
  more   = 120
  heaps  = 300
  insane = 1200
}


function SKTAG_MONS.mon_control_setup(self)
  for name,opt in pairs(self.options) do
    local M = GAME.MONSTERS[name]

    if M and opt.value != "default" then
      local prob = SKTAG_MONS.CONTROL_PROBS[opt.value]

      M.prob = prob
      M.crazy_prob = prob

      if prob >  80 then M.density = 1.0 ; M.skip_prob = 30 end
      if prob > 180 then M.skip_prob = 0 end
    end
  end -- for opt
end


OB_MODULES["sktag_mon_control"] =
{
  label = "Skulltag Monsters : Fine Control"

  for_modules = { sktag_mons=1 }

  hooks =
  {
    setup = SKTAG_MONS.mon_control_setup
  }

  options =
  {
    darkimp   = { label="Dark Imp",          choices=SKTAG_MONS.CONTROL_CHOICES }
    bldemon   = { label="Blood Demon",       choices=SKTAG_MONS.CONTROL_CHOICES }
    cacolant  = { label="Cacolantern",       choices=SKTAG_MONS.CONTROL_CHOICES }
    hectebus  = { label="Hectebus",          choices=SKTAG_MONS.CONTROL_CHOICES }
    abaddon   = { label="Abaddon",           choices=SKTAG_MONS.CONTROL_CHOICES }

    superguy  = { label="Super Shotgun Guy", choices=SKTAG_MONS.CONTROL_CHOICES }
    belphegor = { label="Belphegor",         choices=SKTAG_MONS.CONTROL_CHOICES }
  }
}


----------------------------------------------------------------


function SKTAG_MONS.weap_control_setup(self)
  for name,opt in pairs(self.options) do
    local W = GAME.WEAPONS[name]

    if W and opt.value != "default" then
      local prob = SKTAG_MONS.CONTROL_PROBS[opt.value]

      W.start_prob = prob
      W.add_prob   = prob

      -- adjust usage preference as well
      if W.pref and prob > 0 then
        W.pref = W.pref * ((prob / 50) ^ 0.6)
      end
      
      -- allow it to appear as often as the user wants
      W.rarity = nil
    end
  end -- for opt
end


OB_MODULES["sktag_weap_control"] =
{
  label = "Skulltag Weapons : Fine Control"

  for_modules = { sktag_mons=1 }

  hooks =
  {
    setup = SKTAG_MONS.weap_control_setup
  }

  options =
  {
    minigun  = { label="Minigun",          choices=SKTAG_MONS.CONTROL_CHOICES }
    glaunch  = { label="Grenade Launcher", choices=SKTAG_MONS.CONTROL_CHOICES }
    railgun  = { label="Railgun",          choices=SKTAG_MONS.CONTROL_CHOICES }
    bfg10k   = { label="BFG10K",           choices=SKTAG_MONS.CONTROL_CHOICES }
  }
}

