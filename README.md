Cave Story NX
=============

**Cave Story NX** is a nostalgic side-action adventure game to jump and shoot,
using the modified NXEngine-evo engine[1].

NXEngine-evo is a somewhat updated/refactored version of NXEngine[2].

[1] https://github.com/nxengine/nxengine-evo

[2] http://nxengine.sourceforge.net

**Game History:**
-----------------

You control a little amnesiac who runs around helping out these rabbit-ish
creatures called Mimigas while trying to find your way out of the giant cave
inside the floating island which makes up the game's setting.

You can expand your health meter by collecting Life Capsules, while you can get
stronger by collecting energy to boost your firearms output. 

Each weapon can be built up to the maximum level (3) fairly quickly,
but taking damage will drain energy from its experience meter,
sometimes causing it to level down. 

Given how quickly they power up this only tends to be an issue during
boss fights, and even then there´s usually plenty of opportunities for
collecting more weapon energy.

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
-----------
> The Cave Story NX project is distributed under the terms of the BSD-2-Clause
> license that can be found in the [LICENSE](LICENSE) file. 
> We encourage new contributors to distribute files under this license.
>
> The NXEngine/NXEngine-evo is distributed under the terms
> of the [GNU General Public License version 3 or later](src/LICENSE.GPLv3),
> as it contains code made available under various GPL-compliant licenses.
> We encourage new contributors to distribute files under this license.

* Copyright (c) 2004 **Game data developed by Studio Pixel**
* Copyright (c) 2010-2016 **NXEngine by Caitlin Shaw**
* Copyright (c) 2015-2018 **Engine upgraded/refactored by NXEngine-evo**
* Copyright (c) 2018 Individual work by Carlos Donizete Froes [a.k.a coringao]
