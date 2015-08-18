This repository contains the PLG book listings modified to compile under SDLv2.
My setup:

(1) Windows 10 and VisualStudio 2015CE - SDL2 has beenrecompiled under these environments. ( SDL/SDL_mixer/SDL_image )
    
(2) GNU/Linux Debian 8 with GCC 4.9/Clang4.3


The original work from John R. Hall was released under the GPLv2 so this modified will continue to use the same license.

I have removed most of the comments from the code because I think they were making the code unreadable. Anyway the code is selfexplanatory. I have only kept comments where the code intention is not obvious.

I am using emacs on both Windows and Linux. Similar to Casey's Muratori setup.

[Casey's Emacs setup] (https://youtu.be/hbmV1bnQ-i0?list=PLEMXAbCVnmY7om8VBMD-cIv5B-imU6GyF)

I have provided a make file in case you have GNU make installed or a simple make.bat that tries to replicate the same functionality. I prefer the latter under Windows.

LINUX NOTES:



WINDOWS NOTES:

In Windows I started with Visual Studio 2013CE and using 'cl' from the command line and batch files. Just moved to Visual Studio 2015CE.  

CL does not work correctly when executed within the git shell window (cmd). It is better to open another cmd and run from there.

For any reason the sound example ( 4-12 listing ) is not working on my Windows setup. The program compiles correctly but I has no sound. I spent a few hours trying to find the bug with no avail. I am giving up on this (sdl_sound.c). I rewrote the example using the SDL2_mixer library and now this is working OK ( sdl_sound_1.c ) 

Remember to set SDL_AUDIODRIVER=directsound




