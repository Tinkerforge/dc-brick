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
  UID = 'ap8Mkxo2Dnm'; { Change to your UID }

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

  dc.SetPWMFrequency(10000); { Use PWM frequency of 10kHz }
  dc.SetDriveMode(1); { Use 1 = Drive/Coast instead of 0 = Drive/Brake }

  dc.Enable;
  dc.SetAcceleration(5000); { Slow acceleration }
  dc.SetVelocity(32767); { Full speed }

  WriteLn('Press key to exit');
  ReadLn;
  dc.Disable;
  ipcon.Destroy; { Calls ipcon.Disconnect internally }
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
