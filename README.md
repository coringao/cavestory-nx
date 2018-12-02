Cave Story NX
=============

**Cave Story NX** is a nostalgic side-action adventure game to jump and shoot,
using the modified NXEngine-evo[1] engine.

NXEngine-evo is a somewhat updated/refactored version of NXEngine[2].

> This engine is being rewritten particularly for the game data contained
> in this project.

[1] https://github.com/nxengine/nxengine-evo

[2] http://nxengine.sourceforge.net

**Game History:**
-----------------

The story revolves around a character who mysteriously awakens inside
a cave with no memory or recollection of how he got there.

It turns out that the cave is actually the interior of a large floating island
that is populated by rabbit-like creatures.

The cave also hides a very powerful and magical artifact known
as the Demon Crown that is being sought by an army of robots.

It is up to the players to guide the protagonist through the various levels of
the cave fighting back the robots in order to obtain the artifact.

**Game Play and Features**
--------------------------

Cave Story is a Japanese freeware side-scrolling platform game that can be
played with either the keyboard or a gamepad. Players will solve puzzles
and fight enemies on each map while trying to collect weapons and items to
help him along the way.

Includes some RPG elements with more than three dozen different items
that can be found and stored in the player's inventory for later use.

Players won't get tired of fighting the same monsters over and over again
simply because there are so many different monsters in game and there always
seems to be something new to tackle where each representing a unique set of
challenges that the player must overcome to defeat.

**Development**
---------------

The game Cave Story[1] was released in 2004 and made available in the freeware
version after more than five years in development by Daisuke Amaya otherwise
known by the stage name "Pixel", who designed and coded the game by himself.

Since the release 'Pixel' has developed a number of other platforms,
retro style games through his company Studio Pixel[2].

It has been translated into English by Aeon Genesis Translations[3].

[1] https://www.cavestory.org

[2] https://studiopixel.sakura.ne.jp

[3] https://agtp.romhack.net

**Installation dependency:**
----------------------------

On Debian/Ubuntu/GNU/Linux you can get all necessary packages by typing:

    # apt install cmake libpng-dev libsdl2-dev libsdl2-mixer-dev

When all these dependencies are installed to start compiling the game.
To create the archive binary, do it from the source directory.

**Creating directory and accessing:**

    $ mkdir -p build && cd build

**Starting to build:**

    $ cmake ..

**Starting compilation:**

    $ make

**Running the game:**

    $ ../cavestory-nx

**Removing the build directory and the binary:**

    $ rm -rf build cavestory-nx

**Licenses**
------------

> The **Cave Story NX** project is distributed under the terms of
> the BSD-2-Clause license that can be found in the [LICENSE](LICENSE) file. 
> We encourage new contributors to distribute files under this license.
>
> The **NXEngine/NXEngine-evo** is distributed under the terms
> of the [GNU General Public License version 3 or later](src/LICENSE.GPLv3),
> as it contains code made available under various GPL-compliant licenses.
> We encourage new contributors to distribute files under this license.
>
> **Game data developed by Daisuke Amaya and property of Studio Pixel**
> has been identified as free from known restrictions under the copyright law,
> including all related rights and neighbors. You can copy, modify, distribute
> and perform the work, even for commercial purposes, all without
> asking permission. https://creativecommons.org/publicdomain/mark/1.0

* Copyright (c) 2004 **Game data developed by Studio Pixel**
* Copyright (c) 2005 **Aeon Genesis Translations**
* Copyright (c) 2010-2016 **NXEngine by Caitlin Shaw**
* Copyright (c) 2015-2018 **Engine upgraded/refactored by NXEngine-evo**
* Copyright (c) 2018 Individual work by Carlos Donizete Froes [a.k.a coringao]
