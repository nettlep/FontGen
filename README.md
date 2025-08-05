# Legacy Code Resurrection Project

This file is part of a glorious rescue mission: migrating ancient code from the dusty vaults of the internet to the shiny halls of GitHub.

This code has been preserved as faithfully as possible, warts and all. All code contained herein is original code written by Paul Nettle unless otherwise noted.

---

## Original description

FontGen is a font generation tool (from TrueType fonts) for applications that must render their own fonts (includes full source).

FontGen creates fonts that include the antialiasing information, so that 3D/2D graphics applications can render beautiful characters to the screen.

---

## Original Readme.txt

    -------------------------------------------------------------------------------
     _____                 _ __  __        _        _
    |  __ \               | |  \/  |      | |      | |
    | |__) | ___  __ _  __| | \  / | ___  | |___  __ |_
    |  _  / / _ \/ _` |/ _` | |\/| |/ _ \ | __\ \/ / __|
    | | \ \|  __/ (_| | (_| | |  | |  __/_| |_ >  <| |_
    |_|  \_\\___|\__,_|\__,_|_|  |_|\___(_)\__/_/\_\\__|
                                                                  
    -------------------------------------------------------------------------------

    Originally released under a custom license.
    This historical re-release is provided under the MIT License.
    See the LICENSE file in the repo root for details.

    https://github.com/nettlep

    -------------------------------------------------------------------------------
    Originally created on 12/18/2000 by Paul Nettle

    Copyright 2000, Fluid Studios, Inc., all rights reserved.
    -------------------------------------------------------------------------------

    The latest version of this package can be found at:

          http://www.FluidStudios.com/publications.html

    The Fluid Studios Font Generation Tool (FontGen) generates font files (*.f) for
    use in applications that must render their own fonts. For an example on using
    these font files and rendering them to a frame buffer, see the font class
    source code that is included in the usage_example.zip file that came with this
    package. If you want a better example (a running program with source that uses
    this font system) then download the collision detection demo from:

          http://www.FluidStudios.com/publications.html

    This tool grabs the rendered font from Windows and creates a bitmap of the
    rendered font, which includes an alpha channel. This alpha channel can be used
    for generating text that overlays well on any background of any color, because
    it is to be blended in with the background, not overlaied on top.

    Note, in order for this to work, Windows must be set to "Smooth edges of screen
    fonts". On my Windows2000 box, this is under "effects" of the display
    properties dialog. Note that this is only necessary to be set when running this
    font generation tool, not when rendering the fonts, because it's your job to
    create the font rendering code to work however you like. :)

    Also note that the complete font placement and with is also stored. This means
    that, when properly rendered, the characters of a string all appear properly
    spaced out (kerned) and aligned with one another.

    The format of the font file is very simple. There are 256 characters stored in
    the file, and each character is stored in the following format:

      4 bytes   byteWidth    -- Width of the font (in bytes)
      4 bytes   byteHeight   -- Height of the font (in bytes)
      4 bytes   xOffset      -- X character placement offset (in pixels)
      4 bytes   yOffset      -- Y character placement offset (in pixels)
      4 bytes   screenWidth  -- Width of the font (in screen coordinates)
      4 bytes   screenHeight -- Height of the font (in screen coordinates)
     ?? bytes   fontData     -- Array of byteWidth by byteHeight pixels

            [All integer values are stored in Intel format]

    The byte width & height of each character is so that you may read the character
    from the file, but also so that you know how big the character is in memory.
    These dimensions have nothing to do with character placement, aligntment or
    kerning.

    The remaining values are for pixel placement, alignment and kerning.

    The X & Y offsets are used for pixel placement & alignment. When rendering a
    character, you'll need some reference point for where to render, such as "draw
    the letter Q at [187,224]". If you were to draw a string of letters starting
    at that point, the letters would each have a different baseline. This means
    that each letter is actually positioned at a different offset above or below
    the given input coordinate. The same is true for the horizontal dimension. In
    order to correctly place and align your characters, add the X & Y offsets to
    your input coordinate. For example, given the input coordinate of [187,224] and
    an X/Y offset of [-3,-8], the upper-left corner of the character would be at
    [184,216]. You would then begin rendering the entire character (byteWidth by
    byteHeight) at that new location.

    The screen width & height define the character extents (see CDC::GetTextExtent
    in the Microsoft MFC documentation). Use these values to determine how wide
    a character is (in pixels), so that you can render them with proper kerning, or
    to calculate the total dimensions of a string of characters.

    The pixels are stored as alpha values. A value of 0 means the pixel is
    completely transparent, and a value of 255 means that the pixel is completely
    opaque. These are mono-color fonts, so no color information is stored in the
    file, it's whatever color you decide to draw it in.

    -------------------------------------------------------------------------------
    ReadMe.txt - End of file
    -------------------------------------------------------------------------------

---

## What's in here?

This repository includes:

- Original source code with minimal modifications  
- Historical comments and design choices, preserved for posterity  
- A fresh coat of licensing and documentation (hello `LICENSE` and `README.md`!)  
- Possibly some delightful quirks from a bygone programming era

---

## License

The code is now released under the [MIT License](LICENSE), unless stated otherwise. You are free to use, modify, and redistribute it.

Note: Original copyright notices from the author have been retained for historical context.

---

## Disclaimer

> This code is **vintage**. That means:
> 
> - Expect odd formatting, outdated conventions, and maybe even some nostalgia.
> - It might not compile or run without some TLC.
> - There's zero warranty, and it may bite. You’ve been warned.

---

## Why preserve this?

Because history matters. This code is a snapshot of how things were done back then—and in some cases, how they’re still done today. Think of it as open source time travel.

Happy coding!

— Paul
