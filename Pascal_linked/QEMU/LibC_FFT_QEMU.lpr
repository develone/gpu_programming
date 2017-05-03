program LibC_FFT_QEMU;

{$mode objfpc}{$H+}
//QEMUVersatilePB,PlatformQemuVpb,VersatilePB,
uses
 QEMUVersatilePB, {<-- Change this to suit which model you have!!}
 GlobalConfig,
 GlobalConst,
 GlobalTypes,
 Platform,
 PlatformQemuVpb,
 VersatilePB,
 Console,
 SysUtils,  { TimeToStr & Time }
 { needed by bitmap }
 GraphicsConsole, {Include the GraphicsConsole unit so we can create a graphics window}
 BMPcomn,         {Include the BMPcomn unit from the fpc-image package to give the Bitmap headers}
 Classes,
 { needed by bitmap }
 { needed to use ultibo-tftp  }
 //uTFTP,
 Winsock2,
 { needed to use ultibo-tftp  }
 { needed for telnet }
      Shell,
     ShellFilesystem,
     ShellUpdate,
     RemoteShell,
  { needed for telnet }

 Syscalls;

{$linklib fft}
{$linklib libm}
 
procedure fft_pas; cdecl; external 'libfft' name 'fft_pas';

 

var
 Handle:THandle;
 Handle1:THandle;
 {Handle2:THandle;}
 Window:TWindowHandle;
 Window1:TWindowHandle;
 //Handle3:THandle;

 IPAddress : string;
 X:LongWord;
 Y:LongWord;
 Width:LongWord;
 Height:LongWord;









procedure Msg (Sender : TObject; s : string);

begin

  ConsoleWindowWriteLn (Handle1, s);

end;



//procedure WaitForSDDrive;

//begin

  //while not DirectoryExists ('C:\') do sleep (500);

//end;

 

begin

 //ConsoleWindowWriteLn (Handle1, 'TFTP Demo.');
 // wait for IP address and SD Card to be initialised.
 //WaitForSDDrive;
 //IPAddress := WaitForIPComplete;
 {Wait a few seconds for all initialization (like filesystem and network) to be done}
 Sleep(3000);

 {Create a graphics window to display our bitmap, let's use the new CONSOLE_POSITION_FULLSCREEN option}
 Window:=GraphicsWindowCreate(ConsoleDeviceGetDefault,CONSOLE_POSITION_BOTTOMLEFT);
 Window1:=GraphicsWindowCreate(ConsoleDeviceGetDefault,CONSOLE_POSITION_BOTTOMRIGHT);
 {Call our bitmap drawing function and pass the name of our bitmap file on the SD card,
  we also pass the handle for our graphics console window and the X and Y locations to
  draw the bitmap.

  What happens if the bitmap is bigger than the window? It will be trimmed to fit, try it
  yourself and see}

 Handle:=ConsoleWindowCreate(ConsoleDeviceGetDefault,CONSOLE_POSITION_TOPLEFT,True);
 Handle1:=ConsoleWindowCreate(ConsoleDeviceGetDefault,CONSOLE_POSITION_TOPRIGHT,True);
 {Handle2:=ConsoleWindowCreate(ConsoleDeviceGetDefault,CONSOLE_POSITION_BOTTOMLEFT,True);}
 //Handle3:=ConsoleWindowCreate(ConsoleDeviceGetDefault,CONSOLE_POSITION_BOTTOMRIGHT,True);
 //ConsoleWindowWriteLn(Handle1, 'writing top right handle1');
 {ConsoleWindowWriteLn(Handle2, 'writing bottom left handle2');}
 //ConsoleWindowWriteLn(Handle3, 'writing bottom right handle3');
 ConsoleWindowWriteLn(Handle, TimeToStr(Time));

 fft_pas;
 
 
 //ConsoleWindowWriteLn (Handle1, 'Local Address ' + IPAddress);
 //SetOnMsg (@Msg);
 ConsoleWindowWriteLn(Handle, TimeToStr(Time));
 

 //ThreadHalt(0);
end.

