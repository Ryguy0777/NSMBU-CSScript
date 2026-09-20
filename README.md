# NSMBU-CSScript

## Overview
A small [RedCore](https://github.com/Zenith-Team/RedCore) module that allows the scripts used for several events on the World Map to be loaded from an external file.
You may use RoadrunnerWMC's [Cobra](https://github.com/RoadrunnerWMC/Cobra) to create `.wmsc` files for use with this module.
All credit for the original code goes to the Zenith-Team, as this code was originally part of [Tsuru](https://github.com/Zenith-Team/Tsuru), I have only ported their code to RedCore.
A bundle is provided for those who wish to apply the patch on top of other mods, or as a package if a mod creator wishes to incorporate it into their mod directly.

## Setup Guide
### For Modders
- Download the **`bundle`** from the [latest release](https://github.com/Ryguy0777/NSMBU-CSScript/releases/latest) and extract it to your mod folder, merging the `code` folder into your project.
    - The `rules.txt` doesn't matter as long as the `version = 8` in your own.
- Running on console: Use the [Telkin](https://github.com/Zenith-Team/Telkin) aroma plugin to load your whole mod.
    - Place the `code` folders in `sd:/wiiu/telkin/TITLEID/` where `TITLEID` is the [title ID](https://wiiubrew.org/wiki/Title_database#00050000:_Game_Application_Titles) of your game's region (without dashes).
- Running on Cemu: Load and distribute your mod as a GraphicPack by placing it in Cemu's `graphicPacks` folder and activating it in the game's settings.
- Generate a `scripts.wmsc` file with Cobra, making sure that the file is for NSMBU v1.3.0. Place this file into the `Common/course_select/` folder.

### Compiling
Install [Tachyon](https://github.com/Zenith-Team/Tachyon) (requires [Node.js](https://nodejs.org/) v24+)
```yml
npm i -g --allow-remote=root https://github.com/Zenith-Team/Tachyon/releases/latest/download/tachyon.tgz
```
Build and run the project for your region (example with `US`)
```rb
tachyon pm install
tachyon compile US
tachyon launch US
```
