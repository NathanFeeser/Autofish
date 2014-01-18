Autofish
========

Qt Creator C++ Autofish for FFXIV

This is the C++ code for a GUI application which reads memory locations to detect when an even has occurred.

It retrieves a value at a particular address and determines how to proceed. This usually means sending input via the sendInput() function using VK keycodes from here:  http://www.kbdedit.com/manual/low_level_vk_list.html

This is very much a work in progress as I have stopped playing the game. The hard work is done (finding the memory location of a certain variable for this particular version of the game). I will mention that you must find the variable that is changing to denote the current fishing status. There is a status code for having a bite, reeling in, waiitng to cast, not yet fishing, and waiting for a bite. You must look for a 2-level pointer.