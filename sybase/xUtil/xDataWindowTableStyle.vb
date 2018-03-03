Public Class xDataWindowTableStyle
    Inherits System.Windows.Forms.DataGridTableStyle

    Public Sub New(ByVal sMappingName As String, ByVal oDefault As xUtil.xDataWindowSettings)
        MyBase.New()
        Me.MappingName = sMappingName
        Me.AlternatingBackColor = oDefault.AlternatingBackColor
        Me.BackColor = oDefault.BackColor
        Me.ForeColor = oDefault.ForeColor
        Me.GridLineColor = oDefault.GridLineColor
        Me.HeaderBackColor = oDefault.HeadeBackColor
        Me.HeaderForeColor = oDefault.HeaderForeColor
        Me.RowHeadersVisible = oDefault.RowHeaderVisible
        Me.RowHeaderWidth = oDefault.RowHeaderWidth
        Me.ReadOnly = True
    End Sub
End Class