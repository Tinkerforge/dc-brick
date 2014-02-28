Imports Tinkerforge

Module ExampleCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "6eS9CJ" ' Change to your UID

    ' Use velocity reached callback to swing back and forth between
    ' full speed forward and full speed backward
    Sub ReachedCB(ByVal sender As BrickDC, ByVal velocity As Short)
        If velocity = 32767 Then
            System.Console.WriteLine("Velocity: Full Speed forward, turning backward")
            sender.SetVelocity(-32767)
        Else If velocity = -32767 Then
            System.Console.WriteLine("Velocity: Full Speed backward, turning forward")
            sender.SetVelocity(32767)
        Else
            ' Can only happen if another program sets velocity
            System.Console.WriteLine("Error")
        End If
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim dc As New BrickDC(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Register "velocity reached callback" to ReachedCB
        ' ReachedCB will be called every time a velocity set with
        ' SetVelocity is reached
        AddHandler dc.VelocityReached, AddressOf ReachedCB

        dc.Enable()
        ' The acceleration has to be smaller or equal to the maximum acceleration
        ' of the DC motor, otherwise ReachedCB will be called too early
        dc.SetAcceleration(5000) ' Slow acceleration
        dc.SetVelocity(32767) ' Full speed forward

        System.Console.WriteLine("Press key to exit")
        System.Console.ReadKey()
        ipcon.Disconnect()
    End Sub
End Module
