Public Class frmCurrentProcess
    Inherits frmBase

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

    End Sub

    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Friend WithEvents PanTop As System.Windows.Forms.Panel
    Friend WithEvents PanCmd As System.Windows.Forms.Panel
    Friend WithEvents SpForm As System.Windows.Forms.Splitter
    Friend WithEvents xdwProcess As xUtil.xDataWindow
    Friend WithEvents btnRefresh As System.Windows.Forms.Button
    Friend WithEvents cbxShowSystemProcess As System.Windows.Forms.CheckBox
    Friend WithEvents TabControl1 As System.Windows.Forms.TabControl
    Friend WithEvents tpTableLock As System.Windows.Forms.TabPage
    Friend WithEvents xdwTableLock As xUtil.xDataWindow
    Friend WithEvents lblBlocker As System.Windows.Forms.Label
    Friend WithEvents cbxAutoRefresh As System.Windows.Forms.CheckBox
    Friend WithEvents tmrRefresh As System.Windows.Forms.Timer
    Friend WithEvents tbRefresh As System.Windows.Forms.TextBox
    Friend WithEvents lblRefresh As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Me.PanTop = New System.Windows.Forms.Panel
        Me.xdwProcess = New xUtil.xDataWindow
        Me.PanCmd = New System.Windows.Forms.Panel
        Me.lblRefresh = New System.Windows.Forms.Label
        Me.tbRefresh = New System.Windows.Forms.TextBox
        Me.cbxAutoRefresh = New System.Windows.Forms.CheckBox
        Me.lblBlocker = New System.Windows.Forms.Label
        Me.cbxShowSystemProcess = New System.Windows.Forms.CheckBox
        Me.btnRefresh = New System.Windows.Forms.Button
        Me.SpForm = New System.Windows.Forms.Splitter
        Me.TabControl1 = New System.Windows.Forms.TabControl
        Me.tpTableLock = New System.Windows.Forms.TabPage
        Me.xdwTableLock = New xUtil.xDataWindow
        Me.tmrRefresh = New System.Windows.Forms.Timer(Me.components)
        Me.PanTop.SuspendLayout()
        CType(Me.xdwProcess, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.PanCmd.SuspendLayout()
        Me.TabControl1.SuspendLayout()
        Me.tpTableLock.SuspendLayout()
        CType(Me.xdwTableLock, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'PanTop
        '
        Me.PanTop.Controls.Add(Me.xdwProcess)
        Me.PanTop.Controls.Add(Me.PanCmd)
        Me.PanTop.Dock = System.Windows.Forms.DockStyle.Top
        Me.PanTop.Location = New System.Drawing.Point(0, 0)
        Me.PanTop.Name = "PanTop"
        Me.PanTop.Size = New System.Drawing.Size(972, 432)
        Me.PanTop.TabIndex = 0
        '
        'xdwProcess
        '
        Me.xdwProcess.AllowNavigation = False
        Me.xdwProcess.AlternatingBackColor = System.Drawing.Color.Lavender
        Me.xdwProcess.BackColor = System.Drawing.Color.WhiteSmoke
        Me.xdwProcess.CaptionBackColor = System.Drawing.Color.Gray
        Me.xdwProcess.CaptionForeColor = System.Drawing.Color.White
        Me.xdwProcess.CaptionText = "  Current Process"
        Me.xdwProcess.DataMember = ""
        Me.xdwProcess.Dock = System.Windows.Forms.DockStyle.Fill
        Me.xdwProcess.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.xdwProcess.ForeColor = System.Drawing.Color.MidnightBlue
        Me.xdwProcess.GridLineColor = System.Drawing.Color.Gainsboro
        Me.xdwProcess.HeaderBackColor = System.Drawing.Color.MidnightBlue
        Me.xdwProcess.HeaderForeColor = System.Drawing.SystemColors.ControlText
        Me.xdwProcess.Location = New System.Drawing.Point(0, 32)
        Me.xdwProcess.Name = "xdwProcess"
        Me.xdwProcess.ReadOnly = True
        Me.xdwProcess.RowHeadersVisible = False
        Me.xdwProcess.RowHeaderWidth = 10
        Me.xdwProcess.SelectionType = xUtil.xDataWindowSelectionType.SingleSelection
        Me.xdwProcess.Size = New System.Drawing.Size(972, 400)
        Me.xdwProcess.TabIndex = 0
        '
        'PanCmd
        '
        Me.PanCmd.Controls.Add(Me.lblRefresh)
        Me.PanCmd.Controls.Add(Me.tbRefresh)
        Me.PanCmd.Controls.Add(Me.cbxAutoRefresh)
        Me.PanCmd.Controls.Add(Me.lblBlocker)
        Me.PanCmd.Controls.Add(Me.cbxShowSystemProcess)
        Me.PanCmd.Controls.Add(Me.btnRefresh)
        Me.PanCmd.Dock = System.Windows.Forms.DockStyle.Top
        Me.PanCmd.Location = New System.Drawing.Point(0, 0)
        Me.PanCmd.Name = "PanCmd"
        Me.PanCmd.Size = New System.Drawing.Size(972, 32)
        Me.PanCmd.TabIndex = 0
        '
        'lblRefresh
        '
        Me.lblRefresh.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblRefresh.Location = New System.Drawing.Point(352, 8)
        Me.lblRefresh.Name = "lblRefresh"
        Me.lblRefresh.Size = New System.Drawing.Size(64, 16)
        Me.lblRefresh.TabIndex = 6
        Me.lblRefresh.Text = "Seconds"
        '
        'tbRefresh
        '
        Me.tbRefresh.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.tbRefresh.Location = New System.Drawing.Point(304, 0)
        Me.tbRefresh.Name = "tbRefresh"
        Me.tbRefresh.Size = New System.Drawing.Size(48, 22)
        Me.tbRefresh.TabIndex = 5
        Me.tbRefresh.Text = "5"
        Me.tbRefresh.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'cbxAutoRefresh
        '
        Me.cbxAutoRefresh.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cbxAutoRefresh.Location = New System.Drawing.Point(192, 8)
        Me.cbxAutoRefresh.Name = "cbxAutoRefresh"
        Me.cbxAutoRefresh.Size = New System.Drawing.Size(112, 16)
        Me.cbxAutoRefresh.TabIndex = 4
        Me.cbxAutoRefresh.Text = "Auto-Refresh"
        '
        'lblBlocker
        '
        Me.lblBlocker.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.lblBlocker.BackColor = System.Drawing.Color.Red
        Me.lblBlocker.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblBlocker.ForeColor = System.Drawing.Color.Yellow
        Me.lblBlocker.Location = New System.Drawing.Point(752, 0)
        Me.lblBlocker.Name = "lblBlocker"
        Me.lblBlocker.RightToLeft = System.Windows.Forms.RightToLeft.Yes
        Me.lblBlocker.Size = New System.Drawing.Size(96, 32)
        Me.lblBlocker.TabIndex = 3
        Me.lblBlocker.Text = "Blocker Detected"
        Me.lblBlocker.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.lblBlocker.Visible = False
        '
        'cbxShowSystemProcess
        '
        Me.cbxShowSystemProcess.Dock = System.Windows.Forms.DockStyle.Left
        Me.cbxShowSystemProcess.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cbxShowSystemProcess.Location = New System.Drawing.Point(0, 0)
        Me.cbxShowSystemProcess.Name = "cbxShowSystemProcess"
        Me.cbxShowSystemProcess.Size = New System.Drawing.Size(184, 32)
        Me.cbxShowSystemProcess.TabIndex = 2
        Me.cbxShowSystemProcess.Text = "Show System Process"
        '
        'btnRefresh
        '
        Me.btnRefresh.Dock = System.Windows.Forms.DockStyle.Right
        Me.btnRefresh.Location = New System.Drawing.Point(852, 0)
        Me.btnRefresh.Name = "btnRefresh"
        Me.btnRefresh.RightToLeft = System.Windows.Forms.RightToLeft.Yes
        Me.btnRefresh.Size = New System.Drawing.Size(120, 32)
        Me.btnRefresh.TabIndex = 1
        Me.btnRefresh.Text = "&Refresh"
        '
        'SpForm
        '
        Me.SpForm.BackColor = System.Drawing.Color.Silver
        Me.SpForm.Dock = System.Windows.Forms.DockStyle.Top
        Me.SpForm.Location = New System.Drawing.Point(0, 432)
        Me.SpForm.Name = "SpForm"
        Me.SpForm.Size = New System.Drawing.Size(972, 8)
        Me.SpForm.TabIndex = 1
        Me.SpForm.TabStop = False
        '
        'TabControl1
        '
        Me.TabControl1.Controls.Add(Me.tpTableLock)
        Me.TabControl1.Dock = System.Windows.Forms.DockStyle.Fill
        Me.TabControl1.Location = New System.Drawing.Point(0, 440)
        Me.TabControl1.Name = "TabControl1"
        Me.TabControl1.SelectedIndex = 0
        Me.TabControl1.Size = New System.Drawing.Size(972, 176)
        Me.TabControl1.TabIndex = 2
        '
        'tpTableLock
        '
        Me.tpTableLock.Controls.Add(Me.xdwTableLock)
        Me.tpTableLock.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.tpTableLock.Location = New System.Drawing.Point(4, 21)
        Me.tpTableLock.Name = "tpTableLock"
        Me.tpTableLock.Size = New System.Drawing.Size(964, 151)
        Me.tpTableLock.TabIndex = 0
        Me.tpTableLock.Text = "Table Locking"
        '
        'xdwTableLock
        '
        Me.xdwTableLock.AllowNavigation = False
        Me.xdwTableLock.AlternatingBackColor = System.Drawing.Color.Lavender
        Me.xdwTableLock.BackColor = System.Drawing.Color.WhiteSmoke
        Me.xdwTableLock.CaptionBackColor = System.Drawing.Color.Gray
        Me.xdwTableLock.CaptionForeColor = System.Drawing.Color.White
        Me.xdwTableLock.CaptionText = "Table Locking Information"
        Me.xdwTableLock.DataMember = ""
        Me.xdwTableLock.Dock = System.Windows.Forms.DockStyle.Fill
        Me.xdwTableLock.ForeColor = System.Drawing.Color.MidnightBlue
        Me.xdwTableLock.GridLineColor = System.Drawing.Color.Gainsboro
        Me.xdwTableLock.HeaderBackColor = System.Drawing.Color.MidnightBlue
        Me.xdwTableLock.HeaderForeColor = System.Drawing.Color.WhiteSmoke
        Me.xdwTableLock.Location = New System.Drawing.Point(0, 0)
        Me.xdwTableLock.Name = "xdwTableLock"
        Me.xdwTableLock.ReadOnly = True
        Me.xdwTableLock.RowHeaderWidth = 10
        Me.xdwTableLock.SelectionType = xUtil.xDataWindowSelectionType.SingleSelection
        Me.xdwTableLock.Size = New System.Drawing.Size(964, 151)
        Me.xdwTableLock.TabIndex = 0
        '
        'tmrRefresh
        '
        Me.tmrRefresh.Interval = 5000
        '
        'frmCurrentProcess
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 15)
        Me.ClientSize = New System.Drawing.Size(972, 616)
        Me.Controls.Add(Me.TabControl1)
        Me.Controls.Add(Me.SpForm)
        Me.Controls.Add(Me.PanTop)
        Me.Name = "frmCurrentProcess"
        Me.Text = "Current Process"
        Me.WindowState = System.Windows.Forms.FormWindowState.Maximized
        Me.PanTop.ResumeLayout(False)
        CType(Me.xdwProcess, System.ComponentModel.ISupportInitialize).EndInit()
        Me.PanCmd.ResumeLayout(False)
        Me.TabControl1.ResumeLayout(False)
        Me.tpTableLock.ResumeLayout(False)
        CType(Me.xdwTableLock, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub frmCurrentProcess_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        GetProcess()
        GetTableLock()
        xdwProcess.Focus()
    End Sub

    Private Sub GetProcess()
        Dim sSQL As String
        Dim dsSQL As New DataSet
        sSQL = "SELECT dbname=db_name(a.dbid), " & _
                     " hostname=a.hostname, " & _
                     " spid=a.spid, " & _
                     " status=a.status, " & _
                     " loginname=convert(char(12), suser_name(a.suid)), " & _
                     " cmd=a.cmd, " & _
                     " by_host =b.hostname, " & _
                     " by_id   = a.blocked, " & _
                     " by_login=convert(char(12), suser_name(b.suid)), " & _
                     " by_cmd  =b.cmd, " & _
                     " also_by = b.blocked " & _
               "  FROM master..sysprocesses a, master..sysprocesses b " & _
               " WHERE (a.suid >= -32768 And a.suid <= 32767) " & _
                 " AND (a.spid >= 0 and a.spid <= 32767) " & _
                 " AND (a.blocked *= b.spid) "

        If Not cbxShowSystemProcess.Checked Then sSQL += " AND (suser_name(a.suid) IS NOT NULL) "

        If oServer.ExecuteToDataset(sSQL, dsSQL) Then

            Dim j As Int16

            lblBlocker.Visible = False

            ' Check for Blockers
            For j = 1 To dsSQL.Tables(0).Rows.Count
                If Not (dsSQL.Tables(0).Rows(j - 1)("by_host") Is System.DBNull.Value) Then
                    lblBlocker.Visible = True
                    Exit For
                End If
            Next

            'Reformat the data if necessary
            'For j = 1 To dsSQL.Tables(0).Rows.Count
            'Next

            xdwProcess.SuspendLayout()
            xdwProcess.DataSource = dsSQL.Tables(0)
            xdwProcess.Refresh()
            xdwProcess.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
            xdwProcess.AllowNavigation = False

            xdwProcess.CreateCustomTableStyle(dsSQL.Tables(0).TableName)
            xdwProcess.AddTextColumn("dbname", "DB name", "", HorizontalAlignment.Left, 80, AddressOf xdwFormatter)
            xdwProcess.AddTextColumn("hostname", "Host", "", HorizontalAlignment.Left, 100, AddressOf xdwFormatter)
            xdwProcess.AddTextColumn("spid", "spid", "", HorizontalAlignment.Right, 50, AddressOf xdwFormatter)
            xdwProcess.AddTextColumn("loginname", "loginname", "", HorizontalAlignment.Left, 100, AddressOf xdwFormatter)
            xdwProcess.AddTextColumn("status", "status", "", HorizontalAlignment.Left, 100, AddressOf xdwFormatter)
            xdwProcess.AddTextColumn("cmd", "Command", "", HorizontalAlignment.Left, 200, AddressOf xdwFormatter)
            xdwProcess.AddTextColumn("by_host", "Blocker", "", HorizontalAlignment.Left, 100)
            xdwProcess.AddTextColumn("by_id", "Blocker ID", "", HorizontalAlignment.Left, 60)
            xdwProcess.AddTextColumn("by_cmd", "Blocker Command", "", HorizontalAlignment.Left, 200)
            xdwProcess.CloseTableStyle()

            xdwProcess.ResetAfterRefresh()
            xdwProcess.Select()
            xdwProcess.ResumeLayout()

        End If
    End Sub

    Private Sub GetTableLock()
        Dim sSQL As String
        Dim dsSQL As New DataSet

        sSQL = "SELECT distinct a.hostname, l.spid, loginname=suser_name(a.suid), " & _
                    "  dbname=db_name(l.dbid), objectname=object_name(l.id,l.dbid), locktype = v1.name " & _
                " FROM master..syslocks l, master..spt_values v1, master..spt_values v2, " & _
                     " master..sysprocesses a " & _
               " WHERE l.type = v1.number " & _
                 " AND v1.type = 'L' " & _
                 " AND (l.context+2049) = v2.number " & _
                 " AND v2.type = 'L2' " & _
                 " AND a.spid = l.spid " & _
               " ORDER BY a.hostname, l.spid, suser_name(a.suid), db_name(l.dbid), object_name(l.id, l.dbid)"

        If oServer.ExecuteToDataset(sSQL, dsSQL) Then

            xdwTableLock.SuspendLayout()
            xdwTableLock.DataSource = dsSQL.Tables(0)
            xdwTableLock.Refresh()
            xdwTableLock.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
            xdwTableLock.AllowNavigation = False

            xdwTableLock.CreateCustomTableStyle(dsSQL.Tables(0).TableName)
            xdwTableLock.AddTextColumn("hostname", "Host", "", HorizontalAlignment.Left, 100)
            xdwTableLock.AddTextColumn("spid", "spid", "", HorizontalAlignment.Right, 50)
            xdwTableLock.AddTextColumn("loginname", "loginname", "", HorizontalAlignment.Left, 100)
            xdwTableLock.AddTextColumn("dbname", "DB name", "", HorizontalAlignment.Left, 80)
            xdwTableLock.AddTextColumn("objectname", "Object Nmae", "", HorizontalAlignment.Left, 250)
            xdwTableLock.AddTextColumn("locktype", "Lock Type", "", HorizontalAlignment.Left, 100)
            xdwTableLock.CloseTableStyle()

            xdwTableLock.ResetAfterRefresh()
            xdwTableLock.Select()
            xdwTableLock.ResumeLayout()

        End If
    End Sub

    Private Sub frmCurrentProcess_Closed(ByVal sender As Object, ByVal e As System.EventArgs) Handles MyBase.Closed
        oApplication.CloseWindow("CurrentProcess")
    End Sub


    Public Sub xdwFormatter(ByVal sender As Object, ByVal e As xUtil.xDataWindowHandlerEventArgs)

        Dim oBlocker As Object
        Dim bBlocked As Boolean

        If e.Row >= 0 Then
            Try
                ' Remember to change the Block ID column when the DataCrid is changed
                oBlocker = xdwProcess(e.Row, 7)
                If (oBlocker.GetType.ToString = "System.DBNull") Then
                    bBlocked = False
                Else
                    bBlocked = (CType(oBlocker, Integer) > 0)
                End If
            Catch ex As Exception
                bBlocked = False
            End Try
            If bBlocked Then
                If xdwProcess.IsSelected(e.Row) Then
                    e.ForeBrush = Brushes.Red
                Else
                    e.ForeBrush = Brushes.Yellow
                    e.BackBrush = Brushes.Red
                End If
            End If
        End If
    End Sub


    Private Sub btnRefresh_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnRefresh.Click
        GetProcess()
        GetTableLock()
        xdwProcess.Focus()
    End Sub


    Private Sub cbxShowSystemProcess_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cbxShowSystemProcess.CheckedChanged
        GetProcess()
        xdwProcess.Focus()
    End Sub

    Private Sub tmrRefresh_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles tmrRefresh.Tick
        GetProcess()
        GetTableLock()
        xdwProcess.Focus()
    End Sub

    Private Sub cbxAutoRefresh_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cbxAutoRefresh.CheckedChanged
        If Me.cbxAutoRefresh.Checked Then
            Me.tbRefresh.Enabled = False
            Me.tmrRefresh.Enabled = True
        Else
            Me.tbRefresh.Enabled = True
            Me.tmrRefresh.Enabled = False
        End If
    End Sub


    Private Sub tbRefresh_Validated(ByVal sender As Object, ByVal e As System.EventArgs) Handles tbRefresh.Validated
        Dim iSec As Integer
        If IsNumeric(Me.tbRefresh.Text) Then
            iSec = CType(Me.tbRefresh.Text, Integer)
            If iSec < 1 Then iSec = 5
        Else
            iSec = 5
        End If
        Me.tbRefresh.Text = CType(iSec, String)
        Me.tmrRefresh.Interval = iSec * 1000
    End Sub

    Private Sub tbRefresh_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles tbRefresh.TextChanged

    End Sub
End Class
