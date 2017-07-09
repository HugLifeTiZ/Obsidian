--------------------------------------------------------------------
--  DOOM MONSTERS
--------------------------------------------------------------------
--
--  Copyright (C) 2006-2017 Andrew Apted
--  Copyright (C)      2011 Chris Pisarczyk
--
--  This program is free software; you can redistribute it and/or
--  modify it under the terms of the GNU General Public License
--  as published by the Free Software Foundation; either version 2
--  of the License, or (at your option) any later version.
--
--------------------------------------------------------------------

-- Usable keywords
-- ===============
--
-- id         : editor number used to place monster on the map
-- rank       : measure of "boss-ness", values < 3.0 are fodder
-- density    : how many to use, range is 0 to 99
--
-- health : hit points of monster
-- damage : total damage inflicted on player (on average)
-- attack : kind of attack (hitscan | missile | melee)
--
-- float  : true if monster floats (flies)
-- invis  : true if invisible (or partially)
--
-- weap_needed : weapons player must have to fight this monster
-- weap_min_damage : damage (per second) of player weapon required
-- weap_prefs : weapon preferences table (usage by player)
--
-- species    : name of species (default is monster itself)
-- disloyal   : can hurt a member of same species
-- infight_damage : damage inflicted on one (or more) other monsters
--
--
-- NOTES
-- =====
--
-- Some monsters (e.g. IMP) have both a close-range melee
-- attack and a longer range missile attack.  This is not
-- modelled, we just pick the one with the most damage.
--
-- Archvile attack is not a real hitscan, but for modelling
-- purposes that is a reasonable approximation.
--
-- Similarly the Pain Elemental attack is not a real missile
-- but actually a Lost Soul.  It spawns at least three (when
-- killed), and often more, hence the health is much higher.
--

DOOM.MONSTERS =
{
  zombie =
  {
    id = 3004
    r = 20
    h = 56 
    rank = 0.5
    prob = 50
    health = 20
    damage = 1.2
    attack = "hitscan"
    give = { {ammo="bullet",count=5} }
    density = 1.5
    room_size = "small"
    disloyal = true
    trap_factor = 0.01
    infight_damage = 1.9
  }

  shooter =
  {
    id = 9
    r = 20
    h = 56 
    rank = 1.5
    prob = 90
    health = 30
    damage = 3.0
    attack = "hitscan"
    density = 1.0
    give = { {weapon="shotty"}, {ammo="shell",count=4} }
    weap_needed = { shotty=true }
    species = "zombie"
    room_size = "small"
    disloyal = true
    trap_factor = 2.0
    infight_damage = 6.1
  }

  imp =
  {
    id = 3001
    r = 20
    h = 56 
    rank = 1.0
    prob = 140
    health = 60
    damage = 1.3
    attack = "missile"
    density = 1.0
    room_size = "small"
    trap_factor = 0.3
    infight_damage = 4.0
  }

  skull =
  {
    id = 3006
    r = 16
    h = 56 
    rank = 1.5
    prob = 25
    health = 100
    damage = 1.7
    attack = "melee"
    density = 0.5
    float = true
    weap_prefs = { launch=0.3 }
    room_size = "small"
    disloyal = true
    trap_factor = 0.2
    infight_damage = 2.1
  }

  demon =
  {
    id = 3002
    r = 30
    h = 56 
    rank = 2.2
    prob = 50
    health = 150
    damage = 0.4
    attack = "melee"
    density = 0.85
    weap_min_damage = 40
    weap_prefs = { launch=0.3 }
    room_size = "any"
    infight_damage = 3.5
  }

  spectre =
  {
    id = 58
    r = 30
    h = 56 
    rank = 2.8
    replaces = "demon"
    replace_prob = 35
    crazy_prob = 25
    health = 150
    damage = 1.0
    attack = "melee"
    density = 0.5
    invis = true
    outdoor_factor = 3.0
    weap_min_damage = 40
    weap_prefs = { launch=0.1 }
    species = "demon"
    room_size = "any"
    trap_factor = 0.3
    infight_damage = 2.5
  }

  caco =
  {
    id = 3005
    r = 31
    h = 56 
    rank = 3.8
    prob = 30
    health = 400
    damage = 4.0
    attack = "missile"
    density = 0.6
    weap_min_damage = 40
    float = true
    room_size = "large"
    trap_factor = 0.5
    infight_damage = 21
  }


  ---| BOSSES |---

  baron =
  {
    id = 3003
    r = 24
    h = 64 
    rank = 6.6
    boss_type = "minor"
    boss_prob = 50
    prob = 6.4
    crazy_prob = 20
    health = 1000
    damage = 7.5
    attack = "missile"
    density = 0.3
    weap_min_damage = 88
    room_size = "medium"
    infight_damage = 40
  }

  Cyberdemon =
  {
    id = 16
    r = 40
    h = 110
    rank = 9.9
    boss_type = "tough"
    boss_prob = 50
    prob = 1.6
    crazy_prob = 10
    health = 4000
    damage = 125
    attack = "missile"
    density = 0.1
    weap_min_damage = 150
    weap_prefs = { bfg=10.0 }
    room_size = "medium"
    infight_damage = 1600
  }

  Spiderdemon =
  {
    id = 7
    r = 128
    h = 100
    rank = 9.6
    boss_type = "tough"
    boss_prob = 15
    boss_limit = 1 -- because they infight
    prob = 1.0
    crazy_prob = 10
    health = 3000
    damage = 100
    attack = "hitscan"
    density = 0.1
    weap_min_damage = 200
    weap_prefs = { bfg=10.0 }
    room_size = "large"
    infight_damage = 700
    boss_replacement = "Cyberdemon"
  }


  ---== Doom II only ==---

  gunner =
  {
    id = 65
    r = 20
    h = 56 
    rank = 3.5
    prob = 60
    health = 70
    damage = 5.5
    attack = "hitscan"
    give = { {weapon="chain"}, {ammo="bullet",count=10} }
    weap_needed = { chain=true }
    weap_min_damage = 50
    density = 0.75
    species = "zombie"
    room_size = "large"
    disloyal = true
    trap_factor = 2.4
    infight_damage = 25
  }

  revenant =
  {
    id = 66
    r = 20
    h = 64 
    rank = 4.9
    prob = 28
    health = 300
    damage = 8.5
    attack = "missile"
    weap_min_damage = 60
    density = 0.6
    room_size = "any"
    trap_factor = 3.6
    infight_damage = 20
  }

  knight =
  {
    id = 69
    r = 24
    h = 64 
    rank = 4.9
    prob = 26
    health = 500
    damage = 4.0
    attack = "missile"
    weap_min_damage = 50
    density = 0.75
    species = "baron"
    room_size = "medium"
    infight_damage = 36
  }

  mancubus =
  {
    id = 67
    r = 48
    h = 64 
    rank = 5.5
    prob = 20
    health = 600
    damage = 8.0
    attack = "missile"
    density = 0.32
    weap_min_damage = 88
    room_size = "large"
    infight_damage = 70
  }

  arach =
  {
    id = 68
    r = 64
    h = 64 
    rank = 5.5
    prob = 12
    health = 500
    damage = 10.7
    attack = "missile"
    weap_min_damage = 60
    density = 0.5
    room_size = "medium"
    infight_damage = 62
    boss_replacement = "revenant"
  }

  vile =
  {
    id = 64
    r = 20
    h = 56 
    rank = 7.9
    boss_type = "nasty"
    boss_prob = 50
    prob = 5
    crazy_prob = 15
    health = 700
    damage = 25
    attack = "hitscan"
    density = 0.15
    room_size = "medium"
    weap_min_damage = 120
    nasty = true
    infight_damage = 18
  }

  pain =
  {
    id = 71
    r = 31
    h = 56 
    rank = 6.3
    boss_type = "nasty"
    boss_prob = 15
    prob = 10
    crazy_prob = 15
    health = 900  -- 400 + 5 skulls
    damage = 14.5 -- about 5 skulls
    attack = "missile"
    density = 0.1
    float = true
    weap_min_damage = 100
    weap_prefs = { launch=0.1 }
    room_size = "large"
    cage_factor = 0  -- never put in cages
    infight_damage = 4.5 -- guess
  }

  -- NOTE: this is not normally added to levels
  ss_nazi =
  {
    id = 84
    r = 20
    h = 56 
    rank = 2.2
    prob = 0
    health = 50
    damage = 2.8
    attack = "hitscan"
    give = { {ammo="bullet",count=5} }
    density = 1.5
    infight_damage = 6.0
  }
}

