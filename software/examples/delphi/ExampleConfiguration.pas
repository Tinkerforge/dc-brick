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
  UID = 'ap8Mkxo2Dnm';

var
  e: TExample;

procedure TExample.Execute;
begin
  { Create IP connection to brickd }
  ipcon := TIPConnection.Create(HOST, PORT);

  { Create device object }
  dc := TBrickDC.Create(UID);

  { Add device to IP connection }
  ipcon.AddDevice(dc);
  { Don't use device before it is added to a connection }

  dc.SetPWMFrequency(10000); { Use PWM frequency of 10khz }
  dc.SetDriveMode(1); { Use 1 = Drive/Coast instead of 0 = Drive/Brake }

  dc.Enable;
  dc.SetAcceleration(5000); { Slow acceleration }
  dc.SetVelocity(32767); { Full speed }

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy;
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
