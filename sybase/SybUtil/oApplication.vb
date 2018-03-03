Imports Microsoft.Win32

' Version Update
'   - alpha         : First aplha released version
'   - alpha (0.0.1) 
'       + Remove the hidden Windows (frmTest) from menu
'       + SQLGen: Change to retrieve ALL objects by default in SQL Generation
'   - alpha (0.0.2) 
'       + Add application icon (using the old version SybUtil icon)
'       + SQLGen: Enhance the logic for data retrival using dataview, use dataset copy to speed up the retrival
'                 **** This part should be enhanced using dataview (still have technical problem in using dataview)
'       + SQLGen: Set the default tab to ALL, and retrieve all tabs at start
'   - alpha (0.0.3) 
'       + SQLExec: Bug Fix - In .Net Provider, if the last result set has no rows, it will not be displayed
'                            (Not yet have any solution)
'   - alpha (0.0.4) 
'       + SQLGen: Bug Fix - Allow non-sa user to retrieve data from sysobjects (do not use SELECT *)
'
'   - alpha (0.0.5) 
'       + Login: Bug Fix     - Read SQL.INI even if query= is not the first setting
'                Enhancement - Retrieve the server list after reading SQL.INI
'       + oApplication - User My Settings
'


Public Class oApplication
    'Shared _Name As String = "SybUtil.Net"
    'Shared _Version As String = "alpha 0.0.5"
    'Shared _RegKey As String = "Software\\Super169\\SybUtil"
    Shared _Stopped As Boolean = False

    Shared ReadOnly Property Name() As String
        Get
            Return My.Settings.AppName
        End Get
    End Property

    Shared ReadOnly Property Version() As String
        Get
            Return My.Settings.Version
        End Get
    End Property

    Shared ReadOnly Property FullName() As String
        Get
            Return My.Settings.AppName & " (v" & My.Application.Info.Version.ToString() & ")"
        End Get
    End Property

    Shared ReadOnly Property RegKey() As String
        Get
            Return My.Settings.RegKey
        End Get
    End Property

    Shared ReadOnly Property IsStopped() As Boolean
        Get
            Return _Stopped
        End Get
    End Property

    Shared Sub StartApplication()

    End Sub

    Shared Sub CloseApplication()
        oServer.Disconnect()
    End Sub

    Shared Sub StopAndQuit()
        _Stopped = True
    End Sub

    Private Shared Function GetRegKey(ByVal sSubkey As String) As RegistryKey
        Return GetRegKey(sSubkey, False)
    End Function

    Private Shared Function GetRegKey(ByVal sSubkey As String, ByVal bAutoCreate As Boolean) As RegistryKey
        Dim sKeyName As String
        Dim regKey As RegistryKey

        If sSubkey > "" Then
            sKeyName = My.Settings.RegKey & "\\" & sSubkey
        Else
            sKeyName = My.Settings.RegKey
        End If

        regKey = Registry.CurrentUser.OpenSubKey(sKeyName, True)
        If regKey Is Nothing Then
            If bAutoCreate Then
                regKey = Registry.CurrentUser.CreateSubKey(sKeyName)
            End If
        End If

        Return regKey
    End Function

    Shared Function GetKey(ByVal sSubKey As String, ByVal sName As String) As String
        Return GetKey(sSubKey, sName, "", False)
    End Function
    Shared Function GetKey(ByVal sSubKey As String, ByVal sName As String, ByVal bAutoCreate As Boolean) As String
        Return GetKey(sSubKey, sName, "", bAutoCreate)
    End Function

    Shared Function GetKey(ByVal sSubKey As String, ByVal sName As String, ByVal sDefault As String) As String
        Return GetKey(sSubKey, sName, sDefault, False)
    End Function

    Shared Function GetKey(ByVal sSubKey As String, ByVal sName As String, ByVal sDefault As String, ByVal bAutoCreate As Boolean) As String
        Dim regKey As RegistryKey
        regKey = GetRegKey(sSubKey, bAutoCreate)
        If regKey Is Nothing Then
            Return sDefault
        Else
            Return regKey.GetValue(sName, sDefault)
        End If
    End Function

    Shared Sub SetKey(ByVal sSubKey As String, ByVal sName As String, ByVal sValue As String)
        GetRegKey(sSubKey, True).SetValue(sName, sValue)
    End Sub

    Shared Function GetSubKeyNames(ByVal sSubKey As String) As String()
        Return GetSubKeyNames(sSubKey, True)
    End Function

    Shared Function GetSubKeyNames(ByVal sSubKey As String, ByVal bAutoCreate As Boolean) As String()
        Dim regKey As RegistryKey
        regKey = GetRegKey(sSubKey, bAutoCreate)
        If regKey Is Nothing Then
            Dim sReturn() As String
            sReturn = Nothing
            Return sReturn
        Else
            Return regKey.GetSubKeyNames
        End If
    End Function

    Shared _wMain As frmMDI
    Shared _wCurrentProcess As frmCurrentProcess
    Shared _wSQLExecute As frmSQLExecute
    Shared _wSQLScriptGenerator As frmSQLScriptGenerator
    Shared _wTest As frmBase


    Shared Sub OpenWindow(ByVal asWinName As String)
        Select Case asWinName
            Case "Main"
                _wMain = New frmMDI
                _wMain.ShowDialog()
                _wMain.Dispose()

            Case "CurrentProcess"
                If _wCurrentProcess Is Nothing Then
                    _wCurrentProcess = New frmCurrentProcess
                    _wCurrentProcess.MdiParent = _wMain
                End If
                _wCurrentProcess.Show()
                _wCurrentProcess.BringToFront()

            Case "SQLExecute"
                If _wSQLExecute Is Nothing Then
                    _wSQLExecute = New frmSQLExecute
                    _wSQLExecute.MdiParent = _wMain
                End If
                _wSQLExecute.Show()
                _wSQLExecute.BringToFront()

            Case "SQLScriptGenerator"
                If _wSQLScriptGenerator Is Nothing Then
                    _wSQLScriptGenerator = New frmSQLScriptGenerator
                    _wSQLScriptGenerator.MdiParent = _wMain
                End If
                _wSQLScriptGenerator.Show()
                _wSQLScriptGenerator.BringToFront()

                'Case "TEST"
                '    If _wTest Is Nothing Then
                '        _wTest = New frmTest
                '        _wtest.MdiParent = _wMain
                '    End If
                '    _wtest.Show()
                '    _wtest.BringToFront()
        End Select
    End Sub

    Shared Sub CloseWindow(ByVal asWinName As String)
        Select Case asWinName
            Case "Main"

            Case "CurrentProcess"
                _wCurrentProcess.Dispose()
                _wCurrentProcess = Nothing

            Case "SQLExecute"
                _wSQLExecute.Dispose()
                _wSQLExecute = Nothing

            Case "SQLScriptGenerator"
                _wSQLScriptGenerator.Dispose()
                _wSQLScriptGenerator = Nothing
        End Select
    End Sub

    Shared Sub CloseAllWindows()
        If Not (_wCurrentProcess Is Nothing) Then
            _wCurrentProcess.Close()
        End If
        If Not (_wSQLExecute Is Nothing) Then
            _wSQLExecute.Close()
        End If
        If Not (_wSQLScriptGenerator Is Nothing) Then
            _wSQLScriptGenerator.Close()
        End If
    End Sub

End Class
