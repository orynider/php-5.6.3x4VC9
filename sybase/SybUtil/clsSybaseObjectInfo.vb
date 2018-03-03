Public Enum SybaseObjClass
    Unknown = 0
    Table = 1
    Script = 2
End Enum

Public Class clsSybaseObjectInfo
    Dim _Type As String
    Dim _Name As String
    Dim _Class As SybaseObjClass
    Dim _FullTypeName As String
    Dim _ShortTypeName As String
    Dim _SybObjName As String

    Public Property ObjType() As String
        Get
            Return _Type
        End Get
        Set(ByVal Value As String)
            _Type = Value
        End Set
    End Property

    Public Property ObjName() As String
        Get
            Return _Name
        End Get
        Set(ByVal Value As String)
            _Name = Value
        End Set
    End Property

    Public Property ObjClass() As SybaseObjClass
        Get
            Return _Class
        End Get
        Set(ByVal Value As SybaseObjClass)
            _Class = Value
        End Set
    End Property

    Public Property ObjFullTypeName() As String
        Get
            Return _FullTypeName
        End Get
        Set(ByVal Value As String)
            _FullTypeName = Value
        End Set
    End Property

    Public Property ObjShortTypeName() As String
        Get
            Return _ShortTypeName
        End Get
        Set(ByVal Value As String)
            _ShortTypeName = Value
        End Set
    End Property

    Public Property SybObjName() As String
        Get
            Return _SybObjName
        End Get
        Set(ByVal Value As String)
            _SybObjName = Value
        End Set
    End Property

    Public ReadOnly Property ObjDisplayName() As String
        Get
            Return _FullTypeName & ": " & _Name
        End Get
    End Property

    Public Sub New(ByVal sObjType As String, ByVal sObjName As String, ByVal iSysStat As Integer, ByVal iSysStat2 As Integer)
        _Type = sObjType.Trim.ToUpper
        _Name = sObjName
        Select Case _Type
            Case "D"
                _Class = SybaseObjClass.Script
                _FullTypeName = "Default"
                _ShortTypeName = "Default"
                _SybObjName = "DEFAULT"
            Case "F"
                _Class = SybaseObjClass.Script
                _FullTypeName = "SQLJ Function"
                _ShortTypeName = "SQLJ Fx"
                _SybObjName = ""
            Case "L"
                _Class = SybaseObjClass.Script
                _FullTypeName = "Log"
                _ShortTypeName = "Log"
                _SybObjName = ""
            Case "P"
                _Class = SybaseObjClass.Script
                If (iSysStat2 And 33554432) = 33554432 Then
                    _FullTypeName = "SQLJ Stored Procedure"
                    _ShortTypeName = "SQLJ SProc"
                    _SybObjName = ""
                Else
                    _FullTypeName = "Stored Procedure"
                    _ShortTypeName = "Sproc"
                    _SybObjName = "PROCEDURE"
                End If
            Case "R"
                _Class = SybaseObjClass.Script
                _FullTypeName = "Rule"
                _ShortTypeName = "Rule"
                _SybObjName = ""
            Case "RI"
                _Class = SybaseObjClass.Script
                _FullTypeName = "Referential Constraint"
                _ShortTypeName = "Ref.Constraint"
                _SybObjName = ""
            Case "S"
                _Class = SybaseObjClass.Table
                _FullTypeName = "System Table"
                _ShortTypeName = "SysTable"
                _SybObjName = "TABLE"
            Case "TR"
                _Class = SybaseObjClass.Script
                _FullTypeName = "Trigger"
                _ShortTypeName = "Trigger"
                _SybObjName = "TRIGGER"
            Case "U"
                _Class = SybaseObjClass.Table
                If (iSysStat2 And 2048) = 2048 Then
                    _FullTypeName = "Proxy Table"
                    _ShortTypeName = "ProxyTbl"
                    _SybObjName = ""
                Else
                    _FullTypeName = "User Table"
                    _ShortTypeName = "Table"
                    _SybObjName = "TABLE"
                End If
            Case "V"
                _Class = SybaseObjClass.Script
                _FullTypeName = "View"
                _ShortTypeName = "View"
                _SybObjName = "VIEW"
            Case "XP"
                _Class = SybaseObjClass.Script
                _FullTypeName = "Extended Stored Procedure"
                _ShortTypeName = "Ex.Sproc"
                _SybObjName = ""
            Case Else
                _Class = SybaseObjClass.Unknown
                _FullTypeName = sObjType
                _ShortTypeName = sObjType
                _SybObjName = ""
        End Select

    End Sub
End Class
