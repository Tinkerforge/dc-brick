program ExampleConfiguration;

{$ifdef MSWINDOWS}{$apptype CONSOLE}{$endif}
{$ifdef FPC}{$mode OBJFPC}{$H+}{$endif}

uses
  SysUtils, IPConnection, BrickDC;

type
  TExample = class
  private
    ipcon: TIPConnection;
    dc: TBrickDC;
  public
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = 'XXYYZZ'; { Change XXYYZZ to the UID of your DC Brick }

var
  e: TExample;

procedure TExample.Execute;
begin
  { Create IP connection }
  ipcon := TIPConnection.Create;

  { Create device object }
  dc := TBrickDC.Create(UID, ipcon);

  { Connect to brickd }
  ipcon.Connect(HOST, PORT);
  { Don't use device before ipcon is connected }

  dc.SetDriveMode(BRICK_DC_DRIVE_MODE_DRIVE_COAST);
  dc.SetPWMFrequency(10000); { Use PWM frequency of 10 kHz }
  dc.SetAcceleration(4096); { Slow acceleration (12.5 %/s) }
  dc.SetVelocity(32767); { Full speed forward (100 %) }
  dc.Enable; { Enable motor power }

  WriteLn('Press key to exit');
  ReadLn;

  { Stop motor before disabling motor power }
  dc.SetAcceleration(16384); { Fast decceleration (50 %/s) for stopping }
  dc.SetVelocity(0); { Request motor stop }
  Sleep(2000); { Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s }
  dc.Disable; { Disable motor power }

  ipcon.Destroy; { Calls ipcon.Disconnect internally }
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
