Public Class xDataWindowSettings
    Private _CaptionInFocusBackColor As System.Drawing.Color
    Private _CaptionInFocusForeColor As System.Drawing.Color
    Private _CaptionOutFocusBackColor As System.Drawing.Color
    Private _CaptionOutFocusForeColor As System.Drawing.Color
    Private _AlternatingBackColor As System.Drawing.Color
    Private _BackColor As System.Drawing.Color
    Private _ForeColor As System.Drawing.Color
    Private _GridLineColor As System.Drawing.Color
    Private _HeaderBackColor As System.Drawing.Color
    Private _HeaderForeColor As System.Drawing.Color
    Private _RowHeadersVisible As Boolean
    Private _RowHeaderWidth As Integer

    Public Property CaptionInFocusBackColor() As System.Drawing.Color
        Get
            Return _CaptionInFocusBackColor
        End Get
        Set(ByVal Value As System.Drawing.Color)
            _CaptionInFocusBackColor = Value
        End Set
    End Property
    Public Property CaptionInFocusForeColor() As System.Drawing.Color
        Get
            Return _CaptionInFocusForeColor
        End Get
        Set(ByVal Value As System.Drawing.Color)
            _CaptionInFocusForeColor = Value
        End Set
    End Property
    Public Property CaptionOutFocusBackColor() As System.Drawing.Color
        Get
            Return _CaptionOutFocusBackColor
        End Get
        Set(ByVal Value As System.Drawing.Color)
            _CaptionOutFocusBackColor = Value
        End Set
    End Property
    Public Property CaptionOutFocusForeColor() As System.Drawing.Color
        Get
            Return _CaptionOutFocusForeColor
        End Get
        Set(ByVal Value As System.Drawing.Color)
            _CaptionOutFocusForeColor = Value
        End Set
    End Property
    Public Property AlternatingBackColor() As System.Drawing.Color
        Get
            Return _AlternatingBackColor
        End Get
        Set(ByVal Value As System.Drawing.Color)
            _AlternatingBackColor = Value
        End Set
    End Property
    Public Property BackColor() As System.Drawing.Color
        Get
            Return _BackColor
        End Get
        Set(ByVal Value As System.Drawing.Color)
            _BackColor = Value
        End Set
    End Property
    Public Property ForeColor() As System.Drawing.Color
        Get
            Return _ForeColor
        End Get
        Set(ByVal Value As System.Drawing.Color)
            _ForeColor = Value
        End Set
    End Property
    Public Property GridLineColor() As System.Drawing.Color
        Get
            Return _GridLineColor
        End Get
        Set(ByVal Value As System.Drawing.Color)
            _GridLineColor = Value
        End Set
    End Property
    Public Property HeadeBackColor() As System.Drawing.Color
        Get
            Return _HeaderBackColor
        End Get
        Set(ByVal Value As System.Drawing.Color)
            _HeaderBackColor = Value
        End Set
    End Property
    Public Property HeaderForeColor() As System.Drawing.Color
        Get
            Return _HeaderForeColor
        End Get
        Set(ByVal Value As System.Drawing.Color)
            _HeaderForeColor = Value
        End Set
    End Property
    Public Property RowHeaderVisible() As Boolean
        Get
            Return _RowHeadersVisible
        End Get
        Set(ByVal Value As Boolean)
            _RowHeadersVisible = Value
        End Set
    End Property
    Public Property RowHeaderWidth() As Integer
        Get
            Return _RowHeaderWidth
        End Get
        Set(ByVal Value As Integer)
            _RowHeaderWidth = Value
        End Set
    End Property


    Public Sub New()
        ' Set Default Setting for xDataWindow
        _CaptionInFocusBackColor = System.Drawing.Color.Yellow
        _CaptionInFocusForeColor = System.Drawing.Color.Blue
        _CaptionOutFocusBackColor = System.Drawing.Color.Gray
        _CaptionOutFocusForeColor = System.Drawing.Color.White
        _AlternatingBackColor = System.Drawing.Color.Lavender
        _BackColor = System.Drawing.Color.WhiteSmoke
        _ForeColor = System.Drawing.Color.MidnightBlue
        _GridLineColor = System.Drawing.Color.Gainsboro
        _HeaderBackColor = System.Drawing.Color.MidnightBlue
        _HeaderForeColor = System.Drawing.Color.WhiteSmoke
        _RowHeadersVisible = True
        _RowHeaderWidth = 10
    End Sub

End Class
