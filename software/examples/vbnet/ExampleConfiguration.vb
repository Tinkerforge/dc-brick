Imports System
Imports Tinkerforge

Module ExampleConfiguration
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XXYYZZ" ' Change XXYYZZ to the UID of your DC Brick

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim dc As New BrickDC(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        dc.SetDriveMode(BrickDC.DRIVE_MODE_DRIVE_COAST)
        dc.SetPWMFrequency(10000) ' Use PWM frequency of 10 kHz
        dc.SetAcceleration(4096) ' Slow acceleration (12.5 %/s)
        dc.SetVelocity(32767) ' Full speed forward (100 %)
        dc.Enable() ' Enable motor power

        Console.WriteLine("Press key to exit")
        Console.ReadLine()

        ' Stop motor before disabling motor power
        dc.SetAcceleration(16384) ' Fast decceleration (50 %/s) for stopping
        dc.SetVelocity(0) ' Request motor stop
        Thread.Sleep(2000) ' Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
        dc.Disable() ' Disable motor power

        ipcon.Disconnect()
    End Sub
End Module
