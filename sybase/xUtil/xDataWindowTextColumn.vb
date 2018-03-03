Public Class xDataWindowTextColumn
    Inherits System.Windows.Forms.DataGridTextBoxColumn

    Public Event FormatDataCell As xUtil.xDataWindowHandler

    Protected Overrides Sub Abort(ByVal rowNum As Integer)
        ' No Edit -> No Abort
    End Sub

    Protected Overrides Function Commit(ByVal dataSource As System.Windows.Forms.CurrencyManager, ByVal rowNum As Integer) As Boolean
        ' No Edit -> No Commit
        Return True
    End Function

    Protected Overloads Overrides Sub Edit(ByVal source As System.Windows.Forms.CurrencyManager, ByVal rowNum As Integer, ByVal bounds As System.Drawing.Rectangle, ByVal [readOnly] As Boolean, ByVal instantText As String, ByVal cellIsVisible As Boolean)
        ' Disable Editing
    End Sub

    Protected Overrides Function GetMinimumHeight() As Integer
        Return MyBase.GetMinimumHeight()
    End Function

    Protected Overrides Function GetPreferredHeight(ByVal g As System.Drawing.Graphics, ByVal value As Object) As Integer
        Return MyBase.GetPreferredHeight(g, value)
    End Function

    Protected Overrides Function GetPreferredSize(ByVal g As System.Drawing.Graphics, ByVal value As Object) As System.Drawing.Size
        Return MyBase.GetPreferredSize(g, value)
    End Function

    Protected Overloads Overrides Sub Paint(ByVal g As System.Drawing.Graphics, ByVal bounds As System.Drawing.Rectangle, ByVal source As System.Windows.Forms.CurrencyManager, ByVal rowNum As Integer)
        MyBase.Paint(g, bounds, source, rowNum)
    End Sub

    Protected Overloads Overrides Sub Paint(ByVal g As System.Drawing.Graphics, ByVal bounds As System.Drawing.Rectangle, ByVal source As System.Windows.Forms.CurrencyManager, ByVal rowNum As Integer, ByVal alignToRight As Boolean)
        MyBase.Paint(g, bounds, source, rowNum, alignToRight)
    End Sub

    Protected Overloads Overrides Sub Paint(ByVal g As System.Drawing.Graphics, ByVal bounds As System.Drawing.Rectangle, ByVal [source] As System.Windows.Forms.CurrencyManager, ByVal rowNum As Integer, ByVal backBrush As System.Drawing.Brush, ByVal foreBrush As System.Drawing.Brush, ByVal alignToRight As Boolean)
        Dim e As xDataWindowHandlerEventArgs = Nothing
        Dim col As Integer = Me.DataGridTableStyle.GridColumnStyles.IndexOf(Me)

        e = New xDataWindowHandlerEventArgs(rowNum, col, Me.GetColumnValueAtRow([source], rowNum))
        RaiseEvent FormatDataCell(Me, e)
        If Not (e.BackBrush Is Nothing) Then
            backBrush = e.BackBrush
        End If
        If Not (e.ForeBrush Is Nothing) Then
            foreBrush = e.ForeBrush
        End If
        MyBase.Paint(g, bounds, [source], rowNum, backBrush, foreBrush, alignToRight)
    End Sub
End Class
