Module modMain

    Sub main()
        oApplication.StartApplication()
        Dim _wLogin As frmLogin
        Do
            _wLogin = New frmLogin
            _wLogin.ShowDialog()
            _wLogin.Dispose()
            If oApplication.IsStopped Then Exit Do

            oApplication.OpenWindow("Main")

            oServer.Disconnect()

        Loop Until oApplication.IsStopped()

        oApplication.CloseApplication()
    End Sub
End Module
