Imports Tinkerforge

Module ExampleConfiguration
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "6eS9CJ" ' Change to your UID

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim dc As New BrickDC(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        dc.SetPWMFrequency(10000) ' Use PWM frequency of 10kHz
        dc.SetDriveMode(1) ' Use 1 = Drive/Coast instead of 0 = Drive/Brake

        dc.Enable()
        dc.SetAcceleration(5000) ' Slow acceleration
        dc.SetVelocity(32767) ' Full speed forward

        System.Console.WriteLine("Press key to exit")
        System.Console.ReadKey()
        dc.Disable()
        ipcon.Disconnect()
    End Sub
End Module
