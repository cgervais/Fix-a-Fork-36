Fix-a-Fork (Carbon)
===================

About
-----

This is an unofficial fork of [Eric Helgeson's](https://github.com/erichelgeson) [Fix-a-Fork](https://tinkerdifferent.com/threads/fix-a-fork.3082/), originally written for System 6 and 7, updated for Mac OS 9.

Why?
----

I love Eric's utility but it looks really dated on Mac OS 9 and wanted to scratch an itch with some code renovation projects. My goal was to update the code and get it looking like a modern app for Classic Mac OS. This should run under MacOS 8.0+ with the most recent CarbonLib installed.

But, why Carbonize it?
----------------------

I dunno...why not? When I was a kid I did a lot of programming on classic Mac OS and pre-Carbon there were some things that were a giant pain. This fork is not tested on Mac OS X, so I have no idea if it'll work there. Eric's original version used a lot of System 6 idioms that are deprecated in later versions of Mac OS, so my goal was just to clean it up.

What's Changed
--------------

The initial check-in focused on getting the code to compile under [Retro68](https://github.com/autc04/Retro68), which required a number of changes and fixes:

1. Added missing header file includes to `main.h` and created `file-ext.h`
2. Added missing UPP definition to `AEInstallEventHandler()`
3. Added missing include for `stdbool.h`
4. Created `CMakeLists.txt` to facilitate building under Retro68
5. Created `build.bash` for quick compilation

Building
--------

* Download and compile [Retro68](https://github.com/autc04/Retro68) on your system (make sure to build all the things so you get Carbon)
* Modify `build.bash` to set `RETRO68_PATH` to your local copy of `Retro68-build/`
* Run `sh build.bash` to build

Right now, the script just builds a PowerPC-native version, but it'd be fairly easy to modify to build for 68K. The build script and `CMakeFiles.txt` were heavily inspired by [cy384](https://github.com/cy384)'s build system for [`SSHeven`](https://github.com/cy384/ssheven)

TODO
----

⬛️ Adopt NavigationServices API to replace old `SFPutFile()` API  
⬛️ Adopt Carbon and clean-up all the imports and Toolbox initiatlization code  
⬛️ Adopt the Carbon Event Manager to replace `WaitNextEvent()` calls  
⬛️ Modernize file system API usage  
⬛️ Update icons for Mac OS 8/9  
⬛️ Add a proper About box  
