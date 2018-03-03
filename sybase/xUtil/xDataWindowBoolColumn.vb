Public Class xDataWindowBoolColumn
    Inherits System.Windows.Forms.DataGridBoolColumn
    Public Event FormatDataCell As xUtil.xDataWindowHandler

    Protected Overrides Sub Abort(ByVal rowNum As Integer)
        ' No Edit -> No Abort
    End Sub

    Protected Overrides Function Commit(ByVal dataSource As System.Windows.Forms.CurrencyManager, ByVal rowNum As Integer) As Boolean
        ' No Edit -> No Commit
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

    Protected Overloads Overrides Sub Paint(ByVal g As System.Drawing.Graphics, ByVal bounds As System.Drawing.Rectangle, ByVal [source] As System.Windows.Forms.CurrencyManager, ByVal rowNum As Integer, ByVal backBrush As System.Drawing.Brush, ByVal foreBrush As System.Drawing.Brush, ByVal alignToRight As Boolean)
        Dim e As xDataWindowHandlerEventArgs = Nothing
        Dim col As Integer = Me.DataGridTableStyle.GridColumnStyles.IndexOf(Me)

        e = New xDataWindowHandlerEventArgs(rowNum, col, Me.GetColumnValueAtRow([source], rowNum))
        RaiseEvent FormatDataCell(Me, e)
        If Not (e.BackBrush Is Nothing) Then backBrush = e.BackBrush
        If Not (e.ForeBrush Is Nothing) Then foreBrush = e.ForeBrush
        'if TextFont set, then must call drawstring
        If Not (e.TextFont Is Nothing) Then
            g.FillRectangle(backBrush, bounds)
            Try
                Dim charWidth As Integer = CType(Fix(Math.Ceiling(g.MeasureString("c", e.TextFont, 20, StringFormat.GenericTypographic).Width)), Integer)

                Dim s As String = Me.GetColumnValueAtRow([source], rowNum).ToString()
                Dim maxChars As Integer = CType(Math.Min(s.Length, bounds.Width / charWidth), Integer)

                Try
                    g.DrawString(s.Substring(0, maxChars), e.TextFont, foreBrush, bounds.X, bounds.Y + 2)
                Catch ex As Exception
                    ' Should check why the error occured
                    Console.WriteLine(ex.Message.ToString())
                End Try
            Catch 'empty catch
            End Try
            e.CallBaseClass = False
        End If
        If e.CallBaseClass Then
            MyBase.Paint(g, bounds, [source], rowNum, backBrush, foreBrush, alignToRight)
        End If
        If Not (e Is Nothing) Then
            If Not (e.BackBrush Is Nothing) Then e.BackBrush.Dispose()
            If Not (e.ForeBrush Is Nothing) Then e.ForeBrush.Dispose()
            If Not (e.TextFont Is Nothing) Then e.TextFont.Dispose()
        End If

    End Sub
End Class
