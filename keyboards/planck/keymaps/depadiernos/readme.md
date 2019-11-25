# depadiernos's Planck keymap

This keymap is primarily based on smt's Planck keymap.

Notable differences from the default are:

- **[Mod-Tap](https://github.com/jackhumbert/qmk_firmware/wiki#fun-with-modifier-keys) keys**

    - `Enter/Shift`

        I use both the left and right shift keys when I type. When I want to modify a key with shift, I hold shift with the hand opposite the one typing the key. In the default keymap, Enter is where shift would be on a standard keyboard layout. Oh, muscle memory.

- **"Lower" and "Raise" layers are the same**

    I prefer to have symbols and numbers on both "raise" and "lower" layers.

- **Removed Colemak/Dvorak/Plover layer**

    I don't intend to use these layouts, so I removed from my keymap.


## Qwerty

```
,-----------------------------------------------------------------------------------.
| Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
|------+------+------+------+------+-------------+------+------+------+------+------|
| Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
|------+------+------+------+------+------|------+------+------+------+------+------|
| Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Ctrl | Alt  | GUI  |   `  |Lower | Bksp |Space |Raise | Left | Down |  Up  |Right |
`-----------------------------------------------------------------------------------'
```

## Lower/Raise

Lower and Raise is the same: numbers, symbols, and media controls.

```
,-----------------------------------------------------------------------------------.
|      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | PRSC |
|------+------+------+------+------+-------------+------+------+------+------+------|
|      |      |      |      |      |      |   _  |   ?  |   +  |   {  |   }  |      |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      |      |      |      |      |      |   -  |   /  |   =  |   [  |   ]  |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |  DEL |      |      | Next | Vol- | Vol+ | Play |
`-----------------------------------------------------------------------------------'
```

## Adjust (Lower + Raise)

Utility and Function layer. Function keys and keys to adjust the audio/music and backlight settings, or put the Planck into bootloader mode.

```
,-----------------------------------------------------------------------------------.
|      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |      |      |      | Reset|
|------+------+------+------+------+-------------+------+------+------+------+------|
|      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|Aud on|Audoff|AGnorm|AGswap|      |
|------+------+------+------+------+------+------+------+------+------+------+------|
|Brite |      |      |      |      |             |      | Home |PageDn|PageUp| End  |
`-----------------------------------------------------------------------------------'
```
  