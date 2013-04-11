program ExampleCallback;

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
    procedure ReachedCB(sender: TBrickDC; const velocity: smallint);
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = 'ap8Mkxo2Dnm'; { Change to your UID }

var
  e: TExample;

{ Use velocity reached callback to swing back and forth }
procedure TExample.ReachedCB(sender: TBrickDC; const velocity: smallint);
begin
  if (velocity = 32767) then begin
    WriteLn('Velocity: Full Speed forward, turning backward');
    sender.SetVelocity(-32767);
  end
  else if (velocity = -32767) then begin
    WriteLn('Velocity: Full Speed backward, turning forward');
    sender.SetVelocity(32767);
  end
  else begin
    WriteLn('Error'); { Can only happen if another program sets velocity }
  end;
end;

procedure TExample.Execute;
begin
  { Create IP connection }
  ipcon := TIPConnection.Create;

  { Create device object }
  dc := TBrickDC.Create(UID, ipcon);

  { Connect to brickd }
  ipcon.Connect(HOST, PORT);
  { Don't use device before ipcon is connected }

  { Register "velocity reached callback" to procedure ReachedCB.
    ReachedCB will be called every time a velocity set with
    SetVelocity is reached }
  dc.OnVelocityReached := {$ifdef FPC}@{$endif}ReachedCB;

  dc.Enable;

  { The acceleration has to be smaller or equal to the maximum acceleration
    of the dc motor, otherwise ReachedCB will be called too early }
  dc.SetAcceleration(5000); { Slow acceleration }
  dc.SetVelocity(32767); { Full speed forward }

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy; { Calls ipcon.Disconnect internally }
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
