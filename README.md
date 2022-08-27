# ExOverlay

ExOverlay is an "empty" Direct3D9 & ImGui external overlay for any game that you plan to hack externally, it also has precoded classes for: **Offsets**, 
**Addresses**, **Cheat features**, **Memory hack**, **Process handling**. 

There is code for a small health hack for ULTRAKILL as an example...

<p align="center">
  <img src="https://user-images.githubusercontent.com/87567996/186927945-a5b1cd8b-2202-4d62-aed9-b53015bf88ce.png" width="700">
</p>

The ExOverlay will open only if the target process is found as you can see from the fisrt lines of **WinMain(...)**

    41 procId = proc->GetProcId(L"ULTRAKILL.exe");
    42 
    43 if (procId)
    44 {...}
    
So if you just want the overlay you should delete these lines... and compile for 64 and Release

    procId = proc->GetProcId(L"ULTRAKILL.exe");

      if (procId)
      {
        // Get Handle to target Process
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

        // Proc base address
        addr->moduleBase = (uintptr_t)proc->GetModuleBaseAddress64(procId);

        addr->unityPlayer = (uintptr_t)proc->GetDllModule(L"UnityPlayer.dll", procId);
      }
      else
      {
        option->exit = true;
      }

# Credits

Guided Hacking
