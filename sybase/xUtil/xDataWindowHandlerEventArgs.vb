
Public Delegate Sub xDataWindowHandler(ByVal sender As Object, ByVal e As xUtil.xDataWindowHandlerEventArgs)

Public Class xDataWindowHandlerEventArgs
    Inherits EventArgs

    Private _row As Integer
    Private _col As Integer
    Private _data As Object
    Private _TextFont As System.Drawing.Font
    Private _BackBrush As System.Drawing.Brush
    Private _ForeBrush As System.Drawing.Brush
    Private _CallBaseClass As Boolean

    Public ReadOnly Property Row() As Integer
        Get
            Return _row
        End Get
    End Property

    Public ReadOnly Property Col() As Integer
        Get
            Return _col
        End Get
    End Property

    Public ReadOnly Property Data() As Object
        Get
            Return _data
        End Get
    End Property

    Public Property CallBaseClass() As Boolean
        Get
            Return _CallBaseClass
        End Get
        Set(ByVal Value As Boolean)
            _CallBaseClass = Value
        End Set
    End Property

    Public Property TextFont() As System.Drawing.Font
        Get
            Return (_TextFont)
        End Get
        Set(ByVal Value As System.Drawing.Font)
            _TextFont = Value
        End Set
    End Property

    Public Property BackBrush() As System.Drawing.Brush
        Get
            Return _BackBrush
        End Get
        Set(ByVal Value As System.Drawing.Brush)
            _BackBrush = Value
        End Set
    End Property

    Public Property ForeBrush() As System.Drawing.Brush
        Get
            Return _ForeBrush
        End Get
        Set(ByVal Value As System.Drawing.Brush)
            _ForeBrush = Value
        End Set
    End Property

    Public Sub New(ByVal row As Integer, ByVal col As Integer, ByVal data As Object)
        _row = row
        _col = col
        _data = data
        _TextFont = Nothing
        _BackBrush = Nothing
        _ForeBrush = Nothing
        _CallBaseClass = True
    End Sub

End Class
