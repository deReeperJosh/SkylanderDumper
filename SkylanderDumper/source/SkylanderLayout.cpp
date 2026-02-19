#include <SkylanderLayout.hpp>

#include <MainApplication.hpp>

extern MainApplication::Ref g_MainApplication;

static PadState pad;

const std::map<const std::pair<const u16, const u16>, const char*> s_listSkylanders = {
    {{0, 0x0000}, "Whirlwind"},
    {{0, 0x1801}, "Series 2 Whirlwind"},
    {{0, 0x1C02}, "Polar Whirlwind"},
    {{0, 0x2805}, "Horn Blast Whirlwind"},
    {{0, 0x3810}, "Eon's Elite Whirlwind"},
    {{1, 0x0000}, "Sonic Boom"},
    {{1, 0x1801}, "Series 2 Sonic Boom"},
    {{2, 0x0000}, "Warnado"},
    {{2, 0x2206}, "LightCore Warnado"},
    {{3, 0x0000}, "Lightning Rod"},
    {{3, 0x1801}, "Series 2 Lightning Rod"},
    {{4, 0x0000}, "Bash"},
    {{4, 0x1801}, "Series 2 Bash"},
    {{5, 0x0000}, "Terrafin"},
    {{5, 0x1801}, "Series 2 Terrafin"},
    {{5, 0x2805}, "Knockout Terrafin"},
    {{5, 0x3810}, "Eon's Elite Terrafin"},
    {{6, 0x0000}, "Dino Rang"},
    {{6, 0x4810}, "Eon's Elite Dino Rang"},
    {{7, 0x0000}, "Prism Break"},
    {{7, 0x1801}, "Series 2 Prism Break"},
    {{7, 0x2805}, "Hyper Beam Prism Break"},
    {{7, 0x1206}, "LightCore Prism Break"},
    {{8, 0x0000}, "Sunburn"},
    {{9, 0x0000}, "Eruptor"},
    {{9, 0x1801}, "Series 2 Eruptor"},
    {{9, 0x2C02}, "Volcanic Eruptor"},
    {{9, 0x2805}, "Lava Barf Eruptor"},
    {{9, 0x1206}, "LightCore Eruptor"},
    {{9, 0x3810}, "Eon's Elite Eruptor"},
    {{10, 0x0000}, "Ignitor"},
    {{10, 0x1801}, "Series 2 Ignitor"},
    {{10, 0x1C03}, "Legendary Ignitor"},
    {{11, 0x0000}, "Flameslinger"},
    {{11, 0x1801}, "Series 2 Flameslinger"},
    {{12, 0x0000}, "Zap"},
    {{12, 0x1801}, "Series 2 Zap"},
    {{13, 0x0000}, "Wham Shell"},
    {{13, 0x2206}, "LightCore Wham Shell"},
    {{14, 0x0000}, "Gill Grunt"},
    {{14, 0x1801}, "Series 2 Gill Grunt"},
    {{14, 0x2805}, "Anchors Away Gill Grunt"},
    {{14, 0x3805}, "Tidal Wave Gill Grunt"},
    {{14, 0x3810}, "Eon's Elite Gill Grunt"},
    {{15, 0x0000}, "Slam Bam"},
    {{15, 0x1801}, "Series 2 Slam Bam"},
    {{15, 0x1C03}, "Legendary Slam Bam"},
    {{15, 0x4810}, "Eon's Elite Slam Bam"},
    {{16, 0x0000}, "Spyro"},
    {{16, 0x1801}, "Series 2 Spyro"},
    {{16, 0x2C02}, "Dark Mega Ram Spyro"},
    {{16, 0x2805}, "Mega Ram Spyro"},
    {{16, 0x3810}, "Eon's Elite Spyro"},
    {{17, 0x0000}, "Voodood"},
    {{17, 0x4810}, "Eon's Elite Voodood"},
    {{18, 0x0000}, "Double Trouble"},
    {{18, 0x1801}, "Series 2 Double Trouble"},
    {{18, 0x1C02}, "Royal Double Trouble"},
    {{19, 0x0000}, "Trigger Happy"},
    {{19, 0x1801}, "Series 2 Trigger Happy"},
    {{19, 0x2C02}, "Springtime Trigger Happy"},
    {{19, 0x2805}, "Big Bang Trigger Happy"},
    {{19, 0x3810}, "Eon's Elite Trigger Happy"},
    {{20, 0x0000}, "Drobot"},
    {{20, 0x1801}, "Series 2 Drobot"},
    {{20, 0x1206}, "LightCore Drobot"},
    {{21, 0x0000}, "Drill Seargeant"},
    {{21, 0x1801}, "Series 2 Drill Seargeant"},
    {{22, 0x0000}, "Boomer"},
    {{22, 0x4810}, "Eon's Elite Boomer"},
    {{23, 0x0000}, "Wrecking Ball"},
    {{23, 0x1801}, "Series 2 Wrecking Ball"},
    {{24, 0x0000}, "Camo"},
    {{24, 0x2805}, "Thorn Horn Camo"},
    {{25, 0x0000}, "Zook"},
    {{25, 0x1801}, "Series 2 Zook"},
    {{25, 0x4810}, "Eon's Elite Zook"},
    {{26, 0x0000}, "Stealth Elf"},
    {{26, 0x1801}, "Series 2 Stealth Elf"},
    {{26, 0x2C02}, "Dark Stealth Elf"},
    {{26, 0x1C03}, "Legendary Stealth Elf"},
    {{26, 0x2805}, "Ninja Stealth Elf"},
    {{26, 0x3810}, "Eon's Elite Stealth Elf"},
    {{27, 0x0000}, "Stump Smash"},
    {{27, 0x1801}, "Series 2 Stump Smash"},
    {{28, 0x0000}, "Dark Spyro"},
    {{29, 0x0000}, "Hex"},
    {{29, 0x1801}, "Series 2 Hex"},
    {{29, 0x1206}, "LightCore Hex"},
    {{30, 0x0000}, "Chop Chop"},
    {{30, 0x1801}, "Series 2 Chop Chop"},
    {{30, 0x2805}, "Twin Blade Chop Chop"},
    {{30, 0x3810}, "Eon's Elite Chop Chop"},
    {{31, 0x0000}, "Ghost Roaster"},
    {{31, 0x4810}, "Eon's Elite Ghost Roaster"},
    {{32, 0x0000}, "Cynder"},
    {{32, 0x1801}, "Series 2 Cynder"},
    {{32, 0x2805}, "Phantom Cynder"},
    {{100, 0x0000}, "Jet Vac"},
    {{100, 0x1403}, "Legendary Jet Vac"},
    {{100, 0x2805}, "Turbo Jet Vac"},
    {{100, 0x3805}, "Full Blast Jet Vac"},
    {{100, 0x1206}, "LightCore Jet Vac"},
    {{101, 0x0000}, "Swarm"},
    {{102, 0x0000}, "Crusher"},
    {{102, 0x1602}, "Granite Crusher"},
    {{103, 0x0000}, "Flashwing"},
    {{103, 0x1402}, "Jade Flash Wing"},
    {{103, 0x2206}, "LightCore Flashwing"},
    {{104, 0x0000}, "Hot Head"},
    {{105, 0x0000}, "Hot Dog"},
    {{105, 0x1402}, "Molten Hot Dog"},
    {{105, 0x2805}, "Fire Bone Hot Dog"},
    {{106, 0x0000}, "Chill"},
    {{106, 0x1603}, "Legendary Chill"},
    {{106, 0x2805}, "Blizzard Chill"},
    {{106, 0x1206}, "LightCore Chill"},
    {{107, 0x0000}, "Thumpback"},
    {{108, 0x0000}, "Pop Fizz"},
    {{108, 0x1402}, "Punch Pop Fizz"},
    {{108, 0x3C02}, "Love Potion Pop Fizz"},
    {{108, 0x2805}, "Super Gulp Pop Fizz"},
    {{108, 0x3805}, "Fizzy Frenzy Pop Fizz"},
    {{108, 0x1206}, "LightCore Pop Fizz"},
    {{109, 0x0000}, "Ninjini"},
    {{109, 0x1602}, "Scarlet Ninjini"},
    {{110, 0x0000}, "Bouncer"},
    {{110, 0x1603}, "Legendary Bouncer"},
    {{111, 0x0000}, "Sprocket"},
    {{111, 0x2805}, "Heavy Duty Sprocket"},
    {{112, 0x0000}, "Tree Rex"},
    {{112, 0x1602}, "Gnarly Tree Rex"},
    {{113, 0x0000}, "Shroomboom"},
    {{113, 0x3805}, "Sure Shot Shroomboom"},
    {{113, 0x1206}, "LightCore Shroomboom"},
    {{114, 0x0000}, "Eye Brawl"},
    {{115, 0x0000}, "Fright Rider"},
    {{200, 0x0000}, "Anvil Rain"},
    {{201, 0x0000}, "Hidden Treasure"},
    {{201, 0x2000}, "Platinum Hidden Treasure"},
    {{202, 0x0000}, "Healing Elixir"},
    {{203, 0x0000}, "Ghost Pirate Swords"},
    {{204, 0x0000}, "Time Twist Hourglass"},
    {{205, 0x0000}, "Sky Iron Shield"},
    {{206, 0x0000}, "Winged Boots"},
    {{207, 0x0000}, "Sparx the Dragonfly"},
    {{208, 0x0000}, "Dragonfire Cannon"},
    {{208, 0x1602}, "Golden Dragonfire Cannon"},
    {{209, 0x0000}, "Scorpion Striker"},
    {{210, 0x3002}, "Biter's Bane"},
    {{210, 0x3008}, "Sorcerous Skull"},
    {{210, 0x300B}, "Axe of Illusion"},
    {{210, 0x300E}, "Arcane Hourglass"},
    {{210, 0x3012}, "Spell Slapper"},
    {{210, 0x3014}, "Rune Rocket"},
    {{211, 0x3001}, "Tidal Tiki"},
    {{211, 0x3002}, "Wet Walter"},
    {{211, 0x3006}, "Flood Flask"},
    {{211, 0x3406}, "Legendary Flood Flask"},
    {{211, 0x3007}, "Soaking Staff"},
    {{211, 0x300B}, "Aqua Axe"},
    {{211, 0x3016}, "Frost Helm"},
    {{212, 0x3003}, "Breezy Bird"},
    {{212, 0x3006}, "Drafty Decanter"},
    {{212, 0x300D}, "Tempest Timer"},
    {{212, 0x3010}, "Cloudy Cobra"},
    {{212, 0x3011}, "Storm Warning"},
    {{212, 0x3018}, "Cyclone Saber"},
    {{213, 0x3004}, "Spirit Sphere"},
    {{213, 0x3404}, "Legendary Spirit Sphere"},
    {{213, 0x3008}, "Spectral Skull"},
    {{213, 0x3408}, "Legendary Spectral Skull"},
    {{213, 0x300B}, "Haunted Hatchet"},
    {{213, 0x300C}, "Grim Gripper"},
    {{213, 0x3010}, "Spooky Snake"},
    {{213, 0x3017}, "Dream Piercer"},
    {{214, 0x3000}, "Tech Totem"},
    {{214, 0x3007}, "Automatic Angel"},
    {{214, 0x3009}, "Factory Flower"},
    {{214, 0x300C}, "Grabbing Gadget"},
    {{214, 0x3016}, "Makers Mana"},
    {{214, 0x301A}, "Topsy Techy"},
    {{215, 0x3005}, "Eternal Flame"},
    {{215, 0x3009}, "Fire Flower"},
    {{215, 0x3011}, "Scorching Stopper"},
    {{215, 0x3012}, "Searing Spinner"},
    {{215, 0x3017}, "Spark Spear"},
    {{215, 0x301B}, "Blazing Belch"},
    {{216, 0x3000}, "Banded Boulder"},
    {{216, 0x3003}, "Rock Hawk"},
    {{216, 0x300A}, "Slag Hammer"},
    {{216, 0x300E}, "Dust Of Time"},
    {{216, 0x3013}, "Spinning Sandstorm"},
    {{216, 0x301A}, "Rubble Trouble"},
    {{217, 0x3003}, "Oak Eagle"},
    {{217, 0x3005}, "Emerald Energy"},
    {{217, 0x300A}, "Weed Whacker"},
    {{217, 0x3010}, "Seed Serpent"},
    {{217, 0x3018}, "Jade Blade"},
    {{217, 0x301B}, "Shrub Shrieker"},
    {{218, 0x3000}, "Dark Dagger"},
    {{218, 0x3014}, "Shadow Spider"},
    {{218, 0x301A}, "Ghastly Grimace"},
    {{219, 0x3000}, "Shining Ship"},
    {{219, 0x300F}, "Heavenly Hawk"},
    {{219, 0x301B}, "Beam Scream"},
    {{220, 0x301E}, "Kaos Trap"},
    {{220, 0x351F}, "Ultimate Kaos Trap"},
    {{230, 0x0000}, "Hand of Fate"},
    {{230, 0x3403}, "Legendary Hand of Fate"},
    {{231, 0x0000}, "Piggy Bank"},
    {{232, 0x0000}, "Rocket Ram"},
    {{233, 0x0000}, "Tiki Speaky"},
    {{300, 0x0000}, "Dragon’s Peak"},
    {{301, 0x0000}, "Empire of Ice"},
    {{302, 0x0000}, "Pirate Seas"},
    {{303, 0x0000}, "Darklight Crypt"},
    {{304, 0x0000}, "Volcanic Vault"},
    {{305, 0x0000}, "Mirror of Mystery"},
    {{306, 0x0000}, "Nightmare Express"},
    {{307, 0x0000}, "Sunscraper Spire"},
    {{308, 0x0000}, "Midnight Museum"},
    {{404, 0x0000}, "Legendary Bash"},
    {{416, 0x0000}, "Legendary Spyro"},
    {{419, 0x0000}, "Legendary Trigger Happy"},
    {{430, 0x0000}, "Legendary Chop Chop"},
    {{450, 0x0000}, "Gusto"},
    {{451, 0x0000}, "Thunderbolt"},
    {{452, 0x0000}, "Fling Kong"},
    {{453, 0x0000}, "Blades"},
    {{453, 0x3403}, "Legendary Blades"},
    {{454, 0x0000}, "Wallop"},
    {{455, 0x0000}, "Head Rush"},
    {{455, 0x3402}, "Nitro Head Rush"},
    {{456, 0x0000}, "Fist Bump"},
    {{457, 0x0000}, "Rocky Roll"},
    {{458, 0x0000}, "Wildfire"},
    {{458, 0x3402}, "Dark Wildfire"},
    {{459, 0x0000}, "Ka Boom"},
    {{460, 0x0000}, "Trail Blazer"},
    {{461, 0x0000}, "Torch"},
    {{462, 0x3000}, "Snap Shot"},
    {{462, 0x3402}, "Dark Snap Shot"},
    {{463, 0x0000}, "Lob Star"},
    {{463, 0x3402}, "Winterfest Lob-Star"},
    {{464, 0x0000}, "Flip Wreck"},
    {{465, 0x0000}, "Echo"},
    {{466, 0x0000}, "Blastermind"},
    {{467, 0x0000}, "Enigma"},
    {{468, 0x0000}, "Deja Vu"},
    {{468, 0x3403}, "Legendary Deja Vu"},
    {{469, 0x0000}, "Cobra Candabra"},
    {{469, 0x3402}, "King Cobra Cadabra"},
    {{470, 0x0000}, "Jawbreaker"},
    {{470, 0x3403}, "Legendary Jawbreaker"},
    {{471, 0x0000}, "Gearshift"},
    {{472, 0x0000}, "Chopper"},
    {{473, 0x0000}, "Tread Head"},
    {{474, 0x0000}, "Bushwack"},
    {{474, 0x3403}, "Legendary Bushwack"},
    {{475, 0x0000}, "Tuff Luck"},
    {{476, 0x0000}, "Food Fight"},
    {{476, 0x3402}, "Dark Food Fight"},
    {{477, 0x0000}, "High Five"},
    {{478, 0x0000}, "Krypt King"},
    {{478, 0x3402}, "Nitro Krypt King"},
    {{479, 0x0000}, "Short Cut"},
    {{480, 0x0000}, "Bat Spin"},
    {{481, 0x0000}, "Funny Bone"},
    {{482, 0x0000}, "Knight Light"},
    {{483, 0x0000}, "Spotlight"},
    {{484, 0x0000}, "Knight Mare"},
    {{485, 0x0000}, "Blackout"},
    {{502, 0x0000}, "Bop"},
    {{505, 0x0000}, "Terrabite"},
    {{506, 0x0000}, "Breeze"},
    {{508, 0x0000}, "Pet Vac"},
    {{508, 0x3402}, "Power Punch Pet Vac"},
    {{507, 0x0000}, "Weeruptor"},
    {{507, 0x3402}, "Eggcellent Weeruptor"},
    {{509, 0x0000}, "Small Fry"},
    {{510, 0x0000}, "Drobit"},
    {{519, 0x0000}, "Trigger Snappy"},
    {{526, 0x0000}, "Whisper Elf"},
    {{540, 0x0000}, "Barkley"},
    {{540, 0x3402}, "Gnarly Barkley"},
    {{541, 0x0000}, "Thumpling"},
    {{514, 0x0000}, "Gill Runt"},
    {{542, 0x0000}, "Mini-Jini"},
    {{503, 0x0000}, "Spry"},
    {{504, 0x0000}, "Hijinx"},
    {{543, 0x0000}, "Eye Small"},
    {{601, 0x0000}, "King Pen"},
    {{602, 0x0000}, "Tri-Tip"},
    {{603, 0x0000}, "Chopscotch"},
    {{604, 0x0000}, "Boom Bloom"},
    {{605, 0x0000}, "Pit Boss"},
    {{606, 0x0000}, "Barbella"},
    {{607, 0x0000}, "Air Strike"},
    {{608, 0x0000}, "Ember"},
    {{609, 0x0000}, "Ambush"},
    {{610, 0x0000}, "Dr. Krankcase"},
    {{611, 0x0000}, "Hood Sickle"},
    {{612, 0x0000}, "Tae Kwon Crow"},
    {{613, 0x0000}, "Golden Queen"},
    {{614, 0x0000}, "Wolfgang"},
    {{615, 0x0000}, "Pain-Yatta"},
    {{616, 0x0000}, "Mysticat"},
    {{617, 0x0000}, "Starcast"},
    {{618, 0x0000}, "Buckshot"},
    {{619, 0x0000}, "Aurora"},
    {{620, 0x0000}, "Flare Wolf"},
    {{621, 0x0000}, "Chompy Mage"},
    {{622, 0x0000}, "Bad Juju"},
    {{623, 0x0000}, "Grave Clobber"},
    {{624, 0x0000}, "Blaster-Tron"},
    {{625, 0x0000}, "Ro-Bow"},
    {{626, 0x0000}, "Chain Reaction"},
    {{627, 0x0000}, "Kaos"},
    {{628, 0x0000}, "Wild Storm"},
    {{629, 0x0000}, "Tidepool"},
    {{630, 0x0000}, "Crash Bandicoot"},
    {{631, 0x0000}, "Dr. Neo Cortex"},
    {{1000, 0x0000}, "Boom Jet (Bottom)"},
    {{1001, 0x0000}, "Free Ranger (Bottom)"},
    {{1001, 0x2403}, "Legendary Free Ranger (Bottom)"},
    {{1002, 0x0000}, "Rubble Rouser (Bottom)"},
    {{1003, 0x0000}, "Doom Stone (Bottom)"},
    {{1004, 0x0000}, "Blast Zone (Bottom)"},
    {{1004, 0x2402}, "Dark Blast Zone (Bottom)"},
    {{1005, 0x0000}, "Fire Kraken (Bottom)"},
    {{1005, 0x2402}, "Jade Fire Kraken (Bottom)"},
    {{1006, 0x0000}, "Stink Bomb (Bottom)"},
    {{1007, 0x0000}, "Grilla Drilla (Bottom)"},
    {{1008, 0x0000}, "Hoot Loop (Bottom)"},
    {{1008, 0x2402}, "Enchanted Hoot Loop (Bottom)"},
    {{1009, 0x0000}, "Trap Shadow (Bottom)"},
    {{1010, 0x0000}, "Magna Charge (Bottom)"},
    {{1010, 0x2402}, "Nitro Magna Charge (Bottom)"},
    {{1011, 0x0000}, "Spy Rise (Bottom)"},
    {{1012, 0x0000}, "Night Shift (Bottom)"},
    {{1012, 0x2403}, "Legendary Night Shift (Bottom)"},
    {{1013, 0x0000}, "Rattle Shake (Bottom)"},
    {{1013, 0x2402}, "Quick Draw Rattle Shake (Bottom)"},
    {{1014, 0x0000}, "Freeze Blade (Bottom)"},
    {{1014, 0x2402}, "Nitro Freeze Blade (Bottom)"},
    {{1015, 0x0000}, "Wash Buckler (Bottom)"},
    {{1015, 0x2402}, "Dark Wash Buckler (Bottom)"},
    {{2000, 0x0000}, "Boom Jet (Top)"},
    {{2001, 0x0000}, "Free Ranger (Top)"},
    {{2001, 0x2403}, "Legendary Free Ranger (Top)"},
    {{2002, 0x0000}, "Rubble Rouser (Top)"},
    {{2003, 0x0000}, "Doom Stone (Top)"},
    {{2004, 0x0000}, "Blast Zone (Top)"},
    {{2004, 0x2402}, "Dark Blast Zone (Top)"},
    {{2005, 0x0000}, "Fire Kraken (Top)"},
    {{2005, 0x2402}, "Jade Fire Kraken (Top)"},
    {{2006, 0x0000}, "Stink Bomb (Top)"},
    {{2007, 0x0000}, "Grilla Drilla (Top)"},
    {{2008, 0x0000}, "Hoot Loop (Top)"},
    {{2008, 0x2402}, "Enchanted Hoot Loop (Top)"},
    {{2009, 0x0000}, "Trap Shadow (Top)"},
    {{2010, 0x0000}, "Magna Charge (Top)"},
    {{2010, 0x2402}, "Nitro Magna Charge (Top)"},
    {{2011, 0x0000}, "Spy Rise (Top)"},
    {{2012, 0x0000}, "Night Shift (Top)"},
    {{2012, 0x2403}, "Legendary Night Shift (Top)"},
    {{2013, 0x0000}, "Rattle Shake (Top)"},
    {{2013, 0x2402}, "Quick Draw Rattle Shake (Top)"},
    {{2014, 0x0000}, "Freeze Blade (Top)"},
    {{2014, 0x2402}, "Nitro Freeze Blade (Top)"},
    {{2015, 0x0000}, "Wash Buckler (Top)"},
    {{2015, 0x2402}, "Dark Wash Buckler (Top)"},
    {{3000, 0x0000}, "Scratch"},
    {{3001, 0x0000}, "Pop Thorn"},
    {{3002, 0x0000}, "Slobber Tooth"},
    {{3002, 0x2402}, "Dark Slobber Tooth"},
    {{3003, 0x0000}, "Scorp"},
    {{3004, 0x0000}, "Fryno"},
    {{3004, 0x3805}, "Hog Wild Fryno"},
    {{3005, 0x0000}, "Smolderdash"},
    {{3005, 0x2206}, "LightCore Smolderdash"},
    {{3006, 0x0000}, "Bumble Blast"},
    {{3006, 0x2402}, "Jolly Bumble Blast"},
    {{3006, 0x2206}, "LightCore Bumble Blast"},
    {{3007, 0x0000}, "Zoo Lou"},
    {{3007, 0x2403}, "Legendary Zoo Lou"},
    {{3008, 0x0000}, "Dune Bug"},
    {{3009, 0x0000}, "Star Strike"},
    {{3009, 0x2602}, "Enchanted Star Strike"},
    {{3009, 0x2206}, "LightCore Star Strike"},
    {{3010, 0x0000}, "Countdown"},
    {{3010, 0x2402}, "Kickoff Countdown"},
    {{3010, 0x2206}, "LightCore Countdown"},
    {{3011, 0x0000}, "Wind Up"},
    {{3011, 0x2404}, "Gear Head VVind Up"},
    {{3012, 0x0000}, "Roller Brawl"},
    {{3013, 0x0000}, "Grim Creeper"},
    {{3013, 0x2603}, "Legendary Grim Creeper"},
    {{3013, 0x2206}, "LightCore Grim Creeper"},
    {{3014, 0x0000}, "Rip Tide"},
    {{3015, 0x0000}, "Punk Shock"},
    {{3200, 0x0000}, "Battle Hammer"},
    {{3201, 0x0000}, "Sky Diamond"},
    {{3202, 0x0000}, "Platinum Sheep"},
    {{3203, 0x0000}, "Groove Machine"},
    {{3204, 0x0000}, "UFO Hat"},
    {{3300, 0x0000}, "Sheep Wreck Island"},
    {{3301, 0x0000}, "Tower of Time"},
    {{3302, 0x0000}, "Fiery Forge"},
    {{3303, 0x0000}, "Arkeyan Crossbow"},
    {{3220, 0x0000}, "Jet Stream"},
    {{3221, 0x0000}, "Tomb Buggy"},
    {{3222, 0x0000}, "Reef Ripper"},
    {{3223, 0x0000}, "Burn Cycle"},
    {{3224, 0x0000}, "Hot Streak"},
    {{3224, 0x4402}, "Dark Hot Streak"},
    {{3224, 0x4004}, "E3 Hot Streak"},
    {{3224, 0x441E}, "Golden Hot Streak"},
    {{3225, 0x0000}, "Shark Tank"},
    {{3226, 0x0000}, "Thump Truck"},
    {{3227, 0x0000}, "Crypt Crusher"},
    {{3228, 0x0000}, "Stealth Stinger"},
    {{3228, 0x4402}, "Nitro Stealth Stinger"},
    {{3231, 0x0000}, "Dive Bomber"},
    {{3231, 0x4402}, "Spring Ahead Dive Bomber"},
    {{3232, 0x0000}, "Sky Slicer"},
    {{3233, 0x0000}, "Clown Cruiser (Nintendo Only)"},
    {{3233, 0x4402}, "Dark Clown Cruiser (Nintendo Only)"},
    {{3234, 0x0000}, "Gold Rusher"},
    {{3234, 0x4402}, "Power Blue Gold Rusher"},
    {{3235, 0x0000}, "Shield Striker"},
    {{3236, 0x0000}, "Sun Runner"},
    {{3236, 0x4403}, "Legendary Sun Runner"},
    {{3237, 0x0000}, "Sea Shadow"},
    {{3237, 0x4402}, "Dark Sea Shadow"},
    {{3238, 0x0000}, "Splatter Splasher"},
    {{3238, 0x4402}, "Power Blue Splatter Splasher"},
    {{3239, 0x0000}, "Soda Skimmer"},
    {{3239, 0x4402}, "Nitro Soda Skimmer"},
    {{3240, 0x0000}, "Barrel Blaster (Nintendo Only)"},
    {{3240, 0x4402}, "Dark Barrel Blaster (Nintendo Only)"},
    {{3241, 0x0000}, "Buzz Wing"},
    {{3400, 0x0000}, "Fiesta"},
    {{3400, 0x4515}, "Frightful Fiesta"},
    {{3401, 0x0000}, "High Volt"},
    {{3402, 0x0000}, "Splat"},
    {{3402, 0x4502}, "Power Blue Splat"},
    {{3406, 0x0000}, "Stormblade"},
    {{3411, 0x0000}, "Smash Hit"},
    {{3411, 0x4502}, "Steel Plated Smash Hit"},
    {{3412, 0x0000}, "Spitfire"},
    {{3412, 0x4502}, "Dark Spitfire"},
    {{3413, 0x0000}, "Hurricane Jet Vac"},
    {{3413, 0x4503}, "Legendary Hurricane Jet Vac"},
    {{3414, 0x0000}, "Double Dare Trigger Happy"},
    {{3414, 0x4502}, "Power Blue Double Dare Trigger Happy"},
    {{3415, 0x0000}, "Super Shot Stealth Elf"},
    {{3415, 0x4502}, "Dark Super Shot Stealth Elf"},
    {{3416, 0x0000}, "Shark Shooter Terrafin"},
    {{3417, 0x0000}, "Bone Bash Roller Brawl"},
    {{3417, 0x4503}, "Legendary Bone Bash Roller Brawl"},
    {{3420, 0x0000}, "Big Bubble Pop Fizz"},
    {{3420, 0x450E}, "Birthday Bash Big Bubble Pop Fizz"},
    {{3421, 0x0000}, "Lava Lance Eruptor"},
    {{3422, 0x0000}, "Deep Dive Gill Grunt"},
    {{3423, 0x0000}, "Turbo Charge Donkey Kong (Nintendo Only)"},
    {{3423, 0x4502}, "Dark Turbo Charge Donkey Kong (Nintendo Only)"},
    {{3424, 0x0000}, "Hammer Slam Bowser (Nintendo Only)"},
    {{3424, 0x4502}, "Dark Hammer Slam Bowser (Nintendo Only)"},
    {{3425, 0x0000}, "Dive-Clops"},
    {{3425, 0x450E}, "Missile-Tow Dive-Clops"},
    {{3426, 0x0000}, "Astroblast"},
    {{3426, 0x4503}, "Legendary Astroblast"},
    {{3427, 0x0000}, "Nightfall"},
    {{3428, 0x0000}, "Thrillipede"},
    {{3428, 0x450D}, "Eggcited Thrillipede"},
    {{3500, 0x0000}, "Sky Trophy"},
    {{3501, 0x0000}, "Land Trophy"},
    {{3502, 0x0000}, "Sea Trophy"},
    {{3503, 0x0000}, "Kaos Trophy"},
};

SkylanderLayout::SkylanderLayout() : Layout::Layout()
{
  // Create the TextBlock instance with the text we want
  this->skylanderText = pu::ui::elm::TextBlock::New(300, 300, "Press x to Scan a Skylander");
  this->fileText = pu::ui::elm::TextBlock::New(300, 400, "");
  this->progressBar =
      pu::ui::elm::ProgressBar::New(20, 500, pu::ui::render::ScreenWidth - 40, 50, 16);
  // Add the instance to the layout. IMPORTANT! this MUST be done for them to be used, having them
  // as members is not enough (just a simple way to keep them)
  this->Add(this->skylanderText);
  this->Add(this->fileText);
  this->Add(this->progressBar);

  this->SetOnInput([&](const u64 keys_down, const u64 keys_up, const u64 keys_held,
                       const pu::ui::TouchPoint touch_pos) {
    // If + is pressed, exit application
    if (keys_down & HidNpadButton_Plus)
    {
      g_MainApplication->Close();
    }
    else if (keys_down & HidNpadButton_X)
    {
      this->fileText->SetText("");
      auto rc = ProcessSkylander();
      if (R_SUCCEEDED(rc))
      {
        this->progressBar->SetProgress(0);
        this->skylanderText->SetText("Press x to Scan a Skylander");
        this->fileText->SetText("");
      }
    }
    else if (keys_down & HidNpadButton_B)
    {
      g_MainApplication->LoadLayout(g_MainApplication->GetMainLayout());
      this->progressBar->SetProgress(0);
      this->skylanderText->SetText("Press x to Scan a Skylander");
      this->fileText->SetText("");
    }
  });
}

// Indefinitely wait for an event to be signaled
// Break when + is pressed, or if the application should quit (in this case, return value will be
// non-zero)
Result SkylanderLayout::EventWaitLoop(Event* event)
{
  Result rc = 1;
  while (appletMainLoop())
  {
    rc = eventWait(event, 0);
    padUpdate(&pad);
    if (R_SUCCEEDED(rc) || (padGetButtonsDown(&pad) & HidNpadButton_Plus))
      break;
  }
  return rc;
}

// Print raw data as hexadecimal numbers.
std::string SkylanderLayout::PrintHex(void* buf, size_t size)
{
  std::stringstream ss;
  for (size_t i = 0; i < size; i++)
  {
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(((u8*)buf)[i]);
  }
  return ss.str();
}

u16 SkylanderLayout::Swap16(u16 data)
{
  return (data >> 8) | (data << 8);
}

u32 SkylanderLayout::Swap32(u32 data)
{
  return (Swap16(data) << 16) | Swap16(data >> 16);
}

u64 SkylanderLayout::Swap64(u64 data)
{
  return ((u64)Swap32(data) << 32) | Swap32(data >> 32);
}

// CRC-64 algorithm that is limited to 48 bits every iteration
u64 SkylanderLayout::ComputeCRC48(u8 data[5])
{
  const u64 polynomial = 0x42f0e1eba9ea3693;
  const u64 initial_register_value = 2ULL * 2ULL * 3ULL * 1103ULL * 12868356821ULL;

  const u64 msb = 0x800000000000;

  u64 crc = initial_register_value;
  for (size_t i = 0; i < 5; ++i)
  {
    crc ^= (((u64)data[i]) << 40);
    for (size_t j = 0; j < 8; ++j)
    {
      if (crc & msb)
      {
        crc = (crc << 1) ^ polynomial;
      }
      else
      {
        crc <<= 1;
      }
    }
  }
  return crc & 0x0000FFFFFFFFFFFF;
}

u64 SkylanderLayout::CalculateKeyA(u8 sector, u8 nuid[4])
{
  if (sector == 0)
  {
    return 73ULL * 2017ULL * 560381651ULL;
  }

  u8 data[5] = {nuid[0], nuid[1], nuid[2], nuid[3], sector};

  u64 big_endian_crc = ComputeCRC48(data);
  u64 little_endian_crc = Swap64(big_endian_crc) >> 16;

  return little_endian_crc;
}

u8 SkylanderLayout::GetSectorFromBlock(u8 block)
{
  float block_float = block;
  return floor(block_float / 4);
}

NfcMifareReadBlockParameter SkylanderLayout::GenerateMifareParam(u8 block, u8 nuid[4])
{
  NfcMifareReadBlockParameter param;
  param.sector_number = block;
  NfcSectorKey key;
  key.mifare_command = NfcMifareCommand_AuthA;
  key.unknown = 1;
  u64 keyA = CalculateKeyA(GetSectorFromBlock(block), nuid);
  for (u32 j = 0; j < 6; j++)
  {
    u8 byte = (keyA >> (j * 8)) & 0xFF;
    key.sector_key[(5 - j)] = byte;
  }
  param.sector_key = key;
  return param;
}

Result SkylanderLayout::ProcessSkylander()
{
  Result rc = 0;

  // Get the handle of the first controller with NFC capabilities.
  NfcDeviceHandle handle = {0};
  if (R_SUCCEEDED(rc))
  {
    s32 device_count;
    rc = nfcMfListDevices(&device_count, &handle, 1);

    if (R_FAILED(rc))
      return rc;
  }

  if (R_SUCCEEDED(rc))
  {
    u32 npadId;
    rc = nfcMfGetNpadId(&handle, &npadId);

    if (R_FAILED(rc))
      return rc;
  }

  // Get the activation event. This is signaled when a tag is detected.
  Event activate_event = {0};
  if (R_FAILED(nfcMfAttachActivateEvent(&handle, &activate_event)))
  {
    eventClose(&activate_event);

    return rc;
  }

  // Get the deactivation event. This is signaled when a tag is removed.
  Event deactivate_event = {0};
  if (R_FAILED(nfcMfAttachDeactivateEvent(&handle, &deactivate_event)))
  {
    eventClose(&deactivate_event);
    eventClose(&activate_event);

    return rc;
  }

  NfcState state = NfcState_NonInitialized;
  if (R_SUCCEEDED(rc))
  {
    rc = nfcMfGetState(&state);

    if (R_SUCCEEDED(rc) && state == NfcState_NonInitialized)
    {
      this->skylanderText->SetText("Bad NFC State: " + std::to_string(state));
      g_MainApplication->CallForRender();
      rc = -1;
    }
  }

  NfcMifareDeviceState device_state = NfcMifareDeviceState_Initialized;
  if (R_SUCCEEDED(rc))
  {
    rc = nfcMfGetDeviceState(&handle, &device_state);

    if (R_SUCCEEDED(rc) && device_state > NfcMifareDeviceState_TagFound)
    {
      this->skylanderText->SetText("Bad NFC Device State: " + std::to_string(device_state));
      g_MainApplication->CallForRender();
      rc = -1;
    }
  }

  if (R_FAILED(rc))
  {
    eventClose(&deactivate_event);
    eventClose(&activate_event);

    return rc;
  }

  // Start the detection of tags.
  rc = nfcMfStartDetection(&handle);
  if (R_SUCCEEDED(rc))
  {
    this->skylanderText->SetText("Scanning for a tag...");
    g_MainApplication->CallForRender();
  }

  // Wait until a tag is detected.
  // You could also wait until nfcGetDeviceState returns NfcDeviceState_TagFound.
  if (R_SUCCEEDED(rc))
  {
    rc = EventWaitLoop(&activate_event);

    if (R_SUCCEEDED(rc))
    {
      this->skylanderText->SetText(
          "A tag was detected, please do not remove it from the NFC spot.");
      g_MainApplication->CallForRender();
    }
  }

  // Retrieve the tag info data, which contains the protocol, type and uuid.
  NfcTagInfo tag_info = {0};
  if (R_SUCCEEDED(rc))
    rc = nfcMfGetTagInfo(&handle, &tag_info);

  u8 skylander_data[0x40 * 0x10];
  bool read = true;

  if (R_SUCCEEDED(rc) && tag_info.tag_type == NfcTagType_Mifare)
  {
    const u8 num_blocks = 4;
    u8 nuid[4] = {tag_info.uid.uid[0], tag_info.uid.uid[1], tag_info.uid.uid[2],
                  tag_info.uid.uid[3]};
    for (u8 i = 0; i < 16; i++)
    {
      NfcMifareReadBlockParameter params[num_blocks];
      NfcMifareReadBlockData response[num_blocks];
      for (u8 j = 0; j < num_blocks; j++)
      {
        params[j] = GenerateMifareParam((i * 4) + j, nuid);
      }
      rc = nfcMfReadMifare(&handle, response, params, num_blocks);
      if (R_FAILED(rc))
      {
        this->skylanderText->SetText("Error reading sector " + std::to_string(i));
        this->fileText->SetText("Press X to try again.");
        this->progressBar->SetProgress(0);
        g_MainApplication->CallForRender();
        read = false;
        break;
      }
      else
      {
        this->progressBar->SetProgress(this->progressBar->GetProgress() + 1);
        g_MainApplication->CallForRender();
        // printf("Sector %u data:\n", i);
        for (u8 j = 0; j < num_blocks; j++)
        {
          //   PrintHex(response[j].data, sizeof(response[j].data));
          memcpy(&skylander_data[i * 0x40 + j * 0x10], response[j].data, sizeof(response[j].data));
          if ((j + 1) % 4 == 0)
          {
            memcpy(&skylander_data[i * 0x40 + j * 0x10], params[j].sector_key.sector_key, sizeof(params[j].sector_key.sector_key));
          }
        }
      }
    }

    std::string fileName = "mifare/skylander_data.bin";

    if (read)
    {
      u16 m_sky_id = skylander_data[0x11];
      u16 m_sky_var = skylander_data[0x1D];
      m_sky_id <<= 8;
      m_sky_var <<= 8;
      m_sky_id |= skylander_data[0x10];
      m_sky_var |= skylander_data[0x1C];
      std::pair<u16, u16> id = {m_sky_id, m_sky_var};
      if (const auto it = s_listSkylanders.find(id); it != s_listSkylanders.end())
      {
        auto found = it->second;
        fileName = "mifare/" + std::string(found) + ".bin";
      }
      else
      {
        m_sky_var = 0;
        id = std::make_pair(m_sky_id, m_sky_var);
        if (const auto it = s_listSkylanders.find(id); it != s_listSkylanders.end())
        {
          auto found = it->second;
          fileName = "mifare/" + std::string(found) + ".bin";
        }
      }
      FILE* file = fopen(fileName.c_str(), "wb");
      if (file)
      {
        fwrite(skylander_data, 1, sizeof(skylander_data), file);
        fclose(file);
        this->fileText->SetText("Skylander data written to " + fileName);
        g_MainApplication->CallForRender();
      }
      else
      {
        this->fileText->SetText("Failed to open file for writing: " + fileName);
        g_MainApplication->CallForRender();
      }
    }
  }

  // Wait until the tag is removed.
  // You could also wait until nfcGetDeviceState returns NfcDeviceState_TagRemoved.
  if (R_SUCCEEDED(rc))
  {
    this->skylanderText->SetText("You can now remove the tag.");
    g_MainApplication->CallForRender();
    EventWaitLoop(&deactivate_event);
  }

  // Stop the detection of tags.
  nfcMfStopDetection(&handle);

  // Cleanup.
  eventClose(&deactivate_event);
  eventClose(&activate_event);

  return rc;
}
