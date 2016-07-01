Imports System
Imports Tinkerforge

Module ExampleCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XXYYZZ" ' Change XXYYZZ to the UID of your DC Brick

    ' Use velocity reached callback to swing back and forth
    ' between full speed forward and full speed backward
    Sub VelocityReachedCB(ByVal sender As BrickDC, ByVal velocity As Short)
        If velocity = 32767 Then
            Console.WriteLine("Velocity: Full speed forward, now turning backward")
            sender.SetVelocity(-32767)
        Else If velocity = -32767 Then
            Console.WriteLine("Velocity: Full speed backward, now turning forward")
            sender.SetVelocity(32767)
        Else
            ' Can only happen if another program sets velocity
            Console.WriteLine("Error")
        End If
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim dc As New BrickDC(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' The acceleration has to be smaller or equal to the maximum
        ' acceleration of the DC motor, otherwise the velocity reached
        ' callback will be called too early
        dc.SetAcceleration(5000) ' Slow acceleration
        dc.SetVelocity(32767) ' Full speed forward

        ' Register velocity reached callback to subroutine VelocityReachedCB
        AddHandler dc.VelocityReached, AddressOf VelocityReachedCB

        ' Enable motor power
        dc.Enable()

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        dc.Disable() ' Disable motor power
        ipcon.Disconnect()
    End Sub
End Module
