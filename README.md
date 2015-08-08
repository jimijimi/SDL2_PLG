This repository will contain the PLG book listings modified to compile under SDLv2. The original work from John R. Hall was released under the GPLv2 so the modified code presented here will continue to use the same license.

I have noticed that it is not possible to compile with cl from the git shell command line. It is safer to open another shell for this task.

I have removed most of the comments from the code because they were making the code unreadable. Anyway the code is selfexplanatory. I have only kept comments where the code intentions is not obvious.

I am using emacs on both Windows and Linux. Similar to Casey's Muratori setup.

[Casey's Emacs setup] (https://youtu.be/hbmV1bnQ-i0?list=PLEMXAbCVnmY7om8VBMD-cIv5B-imU6GyF)


LINUX NOTES:
make is my preferred build system. 


WINDOWS NOTES:
In Windows I have Visual Studio 2013 CE but I am using cl from the command line. 
I have provided a make file in case you have GNU make installed or a simple make.bat that tries to replicate the same functionality. I prefer the latter under windows.







