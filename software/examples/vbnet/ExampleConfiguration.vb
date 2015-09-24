Imports System
Imports Tinkerforge

Module ExampleConfiguration
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XXYYZZ" ' Change to your UID

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim dc As New BrickDC(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        dc.SetDriveMode(BrickDC.DRIVE_MODE_DRIVE_COAST)
        dc.SetPWMFrequency(10000) ' Use PWM frequency of 10kHz
        dc.SetAcceleration(5000) ' Slow acceleration
        dc.SetVelocity(32767) ' Full speed forward
        dc.Enable() ' Enable motor power

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        dc.Disable() ' Disable motor power
        ipcon.Disconnect()
    End Sub
End Module
