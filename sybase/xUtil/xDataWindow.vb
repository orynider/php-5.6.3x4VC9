Public Enum xDataWindowSelectionType
    SingleSelection = 1 ' Default Selection Type (but not set)
    MultiSelection = 2
    ManualSelection = 3
End Enum

Public Class xDataWindow
    Inherits System.Windows.Forms.DataGrid

    Private _SelectionType As xUtil.xDataWindowSelectionType
    Private _RowsSelected As Integer = 0
    Private _LastHitRow As Integer = -1
    Private _dgTS As xUtil.xDataWindowTableStyle
    Private _Setting As New xUtil.xDataWindowSettings

    Public Property SelectionType() As xUtil.xDataWindowSelectionType
        Get
            Return _SelectionType
        End Get
        Set(ByVal Value As xUtil.xDataWindowSelectionType)
            _SelectionType = Value
        End Set
    End Property
    Public Property Settings() As xUtil.xDataWindowSettings
        Get
            Return _Setting
        End Get
        Set(ByVal Value As xUtil.xDataWindowSettings)
            _Setting = Value
            Me.ApplySetting()
        End Set
    End Property
    Public ReadOnly Property IsValid() As Boolean
        Get
            If Me.DataSource Is Nothing Then
                Return False
            Else
                Return (Me.DataSource.GetType.ToString = "System.Data.DataTable")
            End If
        End Get
    End Property
    Public ReadOnly Property RowCount() As Integer
        Get
            If Me.IsValid Then
                Return CType(Me.DataSource, System.Data.DataTable).Rows.Count
            Else
                Return 0
            End If
        End Get
    End Property
    Public ReadOnly Property RowsSelected() As Integer
        Get
            Return _RowsSelected
        End Get
    End Property
    Public ReadOnly Property IsEmpty() As Boolean
        Get
            Return (Me.RowCount < 1)
        End Get
    End Property
    Public ReadOnly Property IsNotEmpty() As Boolean
        Get
            Return (Me.RowCount > 0)
        End Get
    End Property

    Public Sub New()
        MyBase.New()
        Me.ApplySetting()
        _SelectionType = xDataWindowSelectionType.SingleSelection
        Me.ReadOnly = True
        Me.AllowNavigation = False
    End Sub

    Private Sub ApplySetting()
        Me.CaptionBackColor = _Setting.CaptionOutFocusBackColor
        Me.CaptionForeColor = _Setting.CaptionOutFocusForeColor
        Me.AlternatingBackColor = _Setting.AlternatingBackColor
        Me.BackColor = _Setting.BackColor
        Me.ForeColor = _Setting.ForeColor
        Me.GridLineColor = _Setting.GridLineColor
        Me.HeaderBackColor = _Setting.HeadeBackColor
        Me.HeaderForeColor = _Setting.HeaderForeColor
        Me.RowHeadersVisible = _Setting.RowHeaderVisible
        Me.RowHeaderWidth = _Setting.RowHeaderWidth
    End Sub

    Private Shared Sub xDataWindowDefaultColumnHandler(ByVal sender As Object, ByVal e As xUtil.xDataWindowHandlerEventArgs)
        ' Dummy handler
    End Sub

    Public Function CreateCustomTableStyle(ByVal sMappingName As String) As xUtil.xDataWindowTableStyle
        Return Me.CreateCustomTableStyle(sMappingName, True)
    End Function

    Public Function CreateCustomTableStyle(ByVal sMappingName As String, ByVal bUseDefault As Boolean) As xUtil.xDataWindowTableStyle
        If Not (_dgTS Is Nothing) Then _dgTS.Dispose()
        _dgTS = New xUtil.xDataWindowTableStyle(sMappingName, _Setting)
        Return _dgTS
    End Function

    Public Sub AddTextColumn(ByVal sMapName As String, ByVal sHeader As String, ByVal sFormat As String, ByVal sAlignment As HorizontalAlignment, ByVal iWidth As Integer)
        Me.AddTextColumn(sMapName, sHeader, sFormat, sAlignment, iWidth, AddressOf xDataWindow.xDataWindowDefaultColumnHandler)
    End Sub

    Public Sub AddTextColumn(ByVal sMapName As String, ByVal sHeader As String, ByVal sFormat As String, ByVal sAlignment As HorizontalAlignment, ByVal iWidth As Integer, ByRef [xHandler] As xUtil.xDataWindowHandler)
        Dim xdwTBC As New xUtil.xDataWindowTextColumn

        If (_dgTS Is Nothing) Then Me.CreateCustomTableStyle("", True)
        xdwTBC.MappingName = sMapName
        xdwTBC.HeaderText = sHeader
        If sFormat > "" Then xdwTBC.Format = sFormat
        xdwTBC.Alignment = sAlignment
        xdwTBC.Width = iWidth
        AddHandler xdwTBC.FormatDataCell, xHandler

        _dgTS.GridColumnStyles.Add(xdwTBC)
    End Sub

    Public Function CloseTableStyle() As Boolean
        If _dgTS Is Nothing Then Return False
        Me.TableStyles.Clear()
        Me.TableStyles.Add(_dgTS)
        Me.ResetAfterRefresh()
        Return True
    End Function

    Protected Overrides Sub OnGotFocus(ByVal e As System.EventArgs)
        Me.CaptionBackColor = _Setting.CaptionInFocusBackColor
        Me.CaptionForeColor = _Setting.CaptionInFocusForeColor
    End Sub

    Protected Overrides Sub OnLostFocus(ByVal e As System.EventArgs)
        Me.CaptionBackColor = _Setting.CaptionOutFocusBackColor
        Me.CaptionForeColor = _Setting.CaptionOutFocusForeColor
    End Sub

    Public Sub ClearSelection()
        Me.ResetSelection()
        _RowsSelected = 0
    End Sub

    Public Sub SelectRow(ByVal row As Integer)
        If Me.IsSelected(row) Then Return
        Try
            Me.Select(row)
        Catch ex As Exception
            MsgBox(ex.Message.ToString)
        End Try
        _RowsSelected += 1
    End Sub

    Public Sub UnSelectRow(ByVal row As Integer)
        If Not Me.IsSelected(row) Then Return
        Me.UnSelect(row)
        _RowsSelected -= 1
    End Sub

    Public Sub ResetAfterRefresh()
        Me.ClearSelection()
        If Not Me.IsEmpty Then
            If Not (_SelectionType = xUtil.xDataWindowSelectionType.ManualSelection) Then
                Me.SelectRow(0)
            End If
            Me.CurrentRowIndex = 0
            _LastHitRow = 0
        Else
            _LastHitRow = -1
        End If
    End Sub

    Public Function AdjustedRow(ByVal row As Integer) As Integer
        If (Me.IsEmpty) Then Return -1
        If (row < 0) Then Return 0
        If row > Me.RowCount - 1 Then Return Me.RowCount - 1
        Return row
    End Function

    Public Sub JumpToRow(ByVal row As Integer)
        Me.HitRow(row, 0, True)
    End Sub

    Public Sub JumpToRow(ByVal row As Integer, ByVal bAutoSelect As Boolean)
        Me.HitRow(row, 0, bautoselect)
    End Sub

    Private Sub HitRow(ByVal row As Integer, ByVal keyModifier As System.Windows.Forms.Keys)
        Me.HitRow(row, keyModifier, True)
    End Sub

    Private Sub HitRow(ByVal row As Integer, ByVal keyModifier As System.Windows.Forms.Keys, ByVal bAutoSelect As Boolean)

        If Me.IsEmpty Then Return

        Dim bControl, bShift As Boolean
        Dim idx, iStep As Integer
        bControl = ((keyModifier And Keys.Control) = Keys.Control)
        bShift = ((keyModifier And Keys.Shift) = Keys.Shift)
        row = Me.AdjustedRow(row)

        Select Case _SelectionType

            Case xDataWindowSelectionType.SingleSelection
                ' Only one row is selected at a time, so just clear and reselect
                Me.ClearSelection()
                Me.SelectRow(row)

            Case xDataWindowSelectionType.MultiSelection
                If (Not bControl) Then
                    Me.ClearSelection()
                End If
                If bShift Then
                    If _LastHitRow > row Then
                        iStep = -1
                    Else
                        iStep = 1
                    End If
                    For idx = _LastHitRow To row Step iStep
                        Me.SelectRow(idx)
                    Next
                Else
                    Me.SelectRow(row)
                End If

            Case xDataWindowSelectionType.ManualSelection
                If bShift Then
                    If _LastHitRow > row Then
                        iStep = -1
                    Else
                        iStep = 1
                    End If
                    For idx = _LastHitRow To row Step iStep
                        Me.SelectRow(idx)
                    Next
                Else
                    If bAutoSelect Then
                        If Me.IsSelected(row) Then
                            Me.UnSelectRow(row)
                        Else
                            Me.SelectRow(row)
                        End If
                    End If
                End If

        End Select
        Me.CurrentRowIndex = row
        _LastHitRow = row

    End Sub

    Public Overrides Sub Refresh()
        MyBase.Refresh()
        Me.ResetAfterRefresh()
    End Sub

    Protected Overrides Sub OnMouseDown(ByVal e As System.Windows.Forms.MouseEventArgs)
        Dim hTest As System.Windows.Forms.DataGrid.HitTestInfo
        hTest = Me.HitTest(e.X, e.Y)
        If (hTest.Row < 0) Then
            Select Case hTest.Type
                Case DataGrid.HitTestType.ColumnHeader
                    ' Sorting should be done in OnMouseUp Event, Call OnMouseDown here just for safe
                    MyBase.OnMouseDown(e)
                Case DataGrid.HitTestType.ColumnResize
                    MyBase.OnMouseDown(e)
                Case Else ' Just make all the reset resume normal
                    MyBase.OnMouseDown(e)
            End Select
        Else
            HitRow(hTest.Row, Control.ModifierKeys)
        End If
    End Sub

    Protected Overrides Sub OnMouseUp(ByVal e As System.Windows.Forms.MouseEventArgs)
        MyBase.OnMouseUp(e)
        Dim hTest As System.Windows.Forms.DataGrid.HitTestInfo
        hTest = Me.HitTest(e.X, e.Y)
        If (hTest.Row < 0) Then
            Select Case hTest.Type
                Case DataGrid.HitTestType.ColumnHeader
                    ' Call MyBase.OnMouseUp for data sorting
                    MyBase.OnMouseUp(e)
                    Me.ClearSelection()
                    If Not Me.IsEmpty Then
                        Me.CurrentRowIndex = 0
                        SelectRow(0)
                    End If
                Case DataGrid.HitTestType.ColumnResize
                    MyBase.OnMouseUp(e)
                Case Else ' Just make all the reset resume normal
                    MyBase.OnMouseUp(e)
            End Select
        End If
    End Sub

    Protected Overrides Function ProcessCmdKey(ByRef msg As System.Windows.Forms.Message, ByVal keyData As System.Windows.Forms.Keys) As Boolean
        Dim rows As Integer = CType(Me.DataSource, System.Data.DataTable).Rows.Count
        Dim realKey As System.Windows.Forms.Keys
        Dim newRow As Integer

        realKey = CType((CType(keyData, Integer) And 255), System.windows.forms.Keys)

        Select Case realKey


            Case Keys.A
                If ((keyData And Keys.Control) = Keys.Control) Then
                    If Me.SelectionType = xDataWindowSelectionType.MultiSelection Or Me.SelectionType = xDataWindowSelectionType.ManualSelection Then
                        'Ctrl-A Select ALL rows
                        Return MyBase.ProcessCmdKey(msg, keyData)
                    End If
                End If
            Case Keys.Enter, Keys.Space
                Me.HitRow(Me.CurrentRowIndex, Keys.Control, True)
                Return True

            Case Keys.Up, Keys.Subtract
                newRow = Me.CurrentRowIndex - 1
                Me.HitRow(newRow, keyData, False)
                Return True

            Case Keys.Down, Keys.Add
                newRow = Me.CurrentRowIndex + 1
                Me.HitRow(newRow, keyData, False)
                Return True

            Case Keys.PageUp
                newRow = Me.CurrentRowIndex - Me.VisibleRowCount
                Me.HitRow(newRow, keyData, False)
                Return True

            Case Keys.PageDown
                newRow = Me.CurrentRowIndex + Me.VisibleRowCount
                Me.HitRow(newRow, keyData, False)
                Return True

            Case Keys.Left
                ' Horizontal move
                Return True

            Case Keys.Right
                ' Horizontal move
                Return True

            Case Keys.Home
                Me.HitRow(0, 0, False)
                Return True

            Case Keys.End
                Me.HitRow(Me.RowCount - 1, 0, False)
                Return True

            Case Keys.Tab
                ' Next / Previous Control
                'Dim ctl As System.Windows.Forms.Control
                'ctl = Me.GetNextControl(Me.Parent, Not ((keyData And Keys.Shift) = Keys.Shift))
                'ctl.Select()
                Return True

                'Disable The following Keys also
            Case Keys.Escape, Keys.BrowserBack, Keys.Delete, Keys.F2, Keys.NumPad0
                Return True




        End Select
        Return MyBase.ProcessCmdKey(msg, keyData)
    End Function


End Class
