Imports Sybase.Data.AseClient
Imports System.Data.OleDb


Public Class oServer

    Enum ConnectionType
        OLEDB = 0
        NetPorvider = 1
        ODBC = 2
    End Enum

    Shared _Connected As Boolean = False
    Shared _ConnString As String = ""
    Shared _ConnType As ConnectionType = ConnectionType.NetPorvider
    Shared _ConnASE As AseConnection
    Shared _ConnOLEDB As OleDbConnection
    Shared _ServerName As String
    Shared _Database As String
    Shared _UserName As String
    Shared _CharSet As String = "cp850"

    Shared ReadOnly Property Database() As String
        Get
            Return _Database
        End Get
    End Property

    Shared ReadOnly Property IsConnected() As Boolean
        Get
            Return _Connected
        End Get
    End Property

    Shared ReadOnly Property ConnectionInfo() As String
        Get
            Return _ServerName & "(" & _Database & ") : " & _UserName
        End Get
    End Property

    Shared Function Connect(ByVal sServerName As String, ByVal oConnType As ConnectionType, ByVal sHost As String, ByVal sPort As String, ByVal sUserName As String, ByVal sPassword As String, ByVal sDatabase As String, ByVal sCharSet As String) As Boolean

        Dim sConnString As String = ""
        If _Connected Then

        End If
        _Connected = False

        Try
            Select Case oConnType
                Case ConnectionType.OLEDB

                    sConnString = "Provider='Sybase ASE OLE DB Provider';" & _
                            "Server Name='" & sHost & "';" & _
                            "Server Port Address='" & sPort & "';" & _
                            "Initial Catalog='" & sDatabase & "';" & _
                            "User ID='" & sUserName & "';" & _
                            "Password='" & sPassword & "'"

                    _ConnOLEDB = New OleDb.OleDbConnection(sConnString)
                    _ConnOLEDB.Open()
                    _Connected = True

                Case ConnectionType.NetPorvider

                    sConnString = "Data Source='" & sHost & "';" & _
                                  "Port='" & sPort & "';" & _
                                  "UID='" & sUserName & "';" & _
                                  "PWD='" & sPassword & "';" & _
                                  "Database='" & sDatabase & "';"
                    If (sCharSet > "") Then sConnString = sConnString & "CharSet='" & sCharSet & "'"

                    _ConnASE = New AseConnection(sConnString)

                    _ConnASE.Open()
                    _Connected = True

                Case ConnectionType.ODBC
                    Return False
            End Select
        Catch ex As Exception
            MsgBox("Connection Failed" & Chr(13) & Chr(10) & Chr(13) & Chr(10) & sConnString & Chr(13) & Chr(10) & Chr(13) & Chr(10) & ex.Message, MsgBoxStyle.Exclamation, "Connection Failed")
            Return False
        End Try

        If _Connected Then
            _ConnString = sConnString
            _ConnType = oConnType
            _ServerName = sServerName
            _Database = sDatabase
            _UserName = sUserName
        End If

        Return True

    End Function

    Shared Function Disconnect() As Boolean
        If Not _Connected Then Return True
        Try

            Select Case _ConnType
                Case ConnectionType.NetPorvider
                    _ConnASE.Close()
                    _ConnASE.Dispose()
                Case ConnectionType.OLEDB
                    _ConnOLEDB.Close()
                    _ConnOLEDB.Dispose()
            End Select

        Catch ex As Exception

        End Try

        _Connected = False
        Return True
    End Function


    Shared Function ExecuteToDataset(ByVal sSQL As String, ByRef dsSQL As DataSet) As Boolean
        If sSQL > "" Then
            Try
                Select Case _ConnType
                    Case ConnectionType.NetPorvider
                        Dim daSQL As New Sybase.Data.AseClient.AseDataAdapter(sSQL, _ConnASE)
                        daSQL.Fill(dsSQL)
                        Return True
                    Case ConnectionType.OLEDB
                        Dim daSQL As New System.Data.OleDb.OleDbDataAdapter(sSQL, _ConnOLEDB)
                        daSQL.Fill(dsSQL)
                        Return True
                End Select

            Catch ex As Exception
                MsgBox(ex.Message, MsgBoxStyle.Exclamation, "Error in ExecuteToDataset")
            End Try
        End If
        Return False

    End Function

    Shared Function ExecuteToString(ByVal sSQL As String) As String
        Dim sReturn As String
        If sSQL > "" Then
            Try
                Select Case _ConnType
                    Case ConnectionType.NetPorvider
                        Dim cmd As Sybase.Data.AseClient.AseCommand
                        Dim reader As Sybase.Data.AseClient.AseDataReader
                        cmd = New AseCommand(sSQL, _ConnASE)
                        reader = cmd.ExecuteReader
                        reader.Read()
                        sReturn = reader.GetString(0)
                        reader.Close()
                        reader.Dispose()
                        cmd.Dispose()
                        Return sReturn
                    Case ConnectionType.OLEDB
                        Dim cmd As OleDb.OleDbCommand
                        Dim reader As OleDb.OleDbDataReader
                        cmd = New OleDbCommand(sSQL, _ConnOLEDB)
                        reader = cmd.ExecuteReader
                        reader.Read()
                        sReturn = reader.GetString(0)
                        reader.Close()
                        cmd.Dispose()
                        Return sReturn
                End Select

            Catch ex As Exception
                MsgBox(ex.Message, MsgBoxStyle.Exclamation, "Error in ExecuteToString")
            End Try
        End If
        Return ""

    End Function

    Shared Function ExecuteNonQuery(ByVal sSQL As String) As Integer
        Dim iReturn As Integer = 0
        If sSQL > "" Then
            Try
                Select Case _ConnType
                    Case ConnectionType.NetPorvider
                        Dim cmd As Sybase.Data.AseClient.AseCommand
                        cmd = New AseCommand(sSQL, _ConnASE)
                        iReturn = cmd.ExecuteNonQuery()
                        cmd.Dispose()
                        Return iReturn
                    Case ConnectionType.OLEDB
                        Dim cmd As OleDb.OleDbCommand
                        cmd = New OleDbCommand(sSQL, _ConnOLEDB)
                        iReturn = cmd.ExecuteNonQuery()
                        cmd.Dispose()
                        Return iReturn
                End Select

            Catch ex As Exception
                MsgBox(ex.Message, MsgBoxStyle.Exclamation, "Error in ExecuteNonQuery")
                Return -2
            End Try
        End If
        Return 0

    End Function

End Class


