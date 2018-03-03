Public Class frmTest
    Inherits SybUtil.frmBase

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
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents xdwProcess As xUtil.xDataWindow
    Friend WithEvents Button2 As System.Windows.Forms.Button
    Friend WithEvents Button3 As System.Windows.Forms.Button
    Friend WithEvents Button4 As System.Windows.Forms.Button
    Friend WithEvents xdwTest As xUtil.xDataWindow
    Friend WithEvents btnNewData As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.xdwProcess = New xUtil.xDataWindow
        Me.Button1 = New System.Windows.Forms.Button
        Me.Button2 = New System.Windows.Forms.Button
        Me.Button3 = New System.Windows.Forms.Button
        Me.Button4 = New System.Windows.Forms.Button
        Me.xdwTest = New xUtil.xDataWindow
        Me.btnNewData = New System.Windows.Forms.Button
        CType(Me.xdwProcess, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.xdwTest, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'xdwProcess
        '
        Me.xdwProcess.AllowNavigation = False
        Me.xdwProcess.AlternatingBackColor = System.Drawing.Color.Lavender
        Me.xdwProcess.BackColor = System.Drawing.Color.WhiteSmoke
        Me.xdwProcess.CaptionBackColor = System.Drawing.Color.Gray
        Me.xdwProcess.CaptionForeColor = System.Drawing.Color.White
        Me.xdwProcess.CaptionText = "Dummy"
        Me.xdwProcess.DataMember = ""
        Me.xdwProcess.ForeColor = System.Drawing.Color.MidnightBlue
        Me.xdwProcess.GridLineColor = System.Drawing.Color.Gainsboro
        Me.xdwProcess.HeaderBackColor = System.Drawing.Color.MidnightBlue
        Me.xdwProcess.HeaderForeColor = System.Drawing.SystemColors.ControlText
        Me.xdwProcess.Location = New System.Drawing.Point(24, 16)
        Me.xdwProcess.Name = "xdwProcess"
        Me.xdwProcess.ReadOnly = True
        Me.xdwProcess.RowHeaderWidth = 10
        Me.xdwProcess.SelectionType = xUtil.xDataWindowSelectionType.SingleSelection
        Me.xdwProcess.Size = New System.Drawing.Size(720, 248)
        Me.xdwProcess.TabIndex = 0
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(640, 272)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(104, 32)
        Me.Button1.TabIndex = 1
        Me.Button1.Text = "Refresh"
        '
        'Button2
        '
        Me.Button2.Location = New System.Drawing.Point(496, 272)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(104, 32)
        Me.Button2.TabIndex = 2
        Me.Button2.Text = "Multi-Selection"
        '
        'Button3
        '
        Me.Button3.Location = New System.Drawing.Point(344, 272)
        Me.Button3.Name = "Button3"
        Me.Button3.Size = New System.Drawing.Size(120, 32)
        Me.Button3.TabIndex = 3
        Me.Button3.Text = "Single-Selection"
        '
        'Button4
        '
        Me.Button4.Location = New System.Drawing.Point(192, 272)
        Me.Button4.Name = "Button4"
        Me.Button4.Size = New System.Drawing.Size(128, 32)
        Me.Button4.TabIndex = 4
        Me.Button4.Text = "Manual-Selection"
        '
        'xdwTest
        '
        Me.xdwTest.AllowNavigation = False
        Me.xdwTest.AlternatingBackColor = System.Drawing.Color.Lavender
        Me.xdwTest.BackColor = System.Drawing.Color.WhiteSmoke
        Me.xdwTest.CaptionBackColor = System.Drawing.Color.Gray
        Me.xdwTest.CaptionForeColor = System.Drawing.Color.White
        Me.xdwTest.DataMember = ""
        Me.xdwTest.ForeColor = System.Drawing.Color.MidnightBlue
        Me.xdwTest.GridLineColor = System.Drawing.Color.Gainsboro
        Me.xdwTest.HeaderBackColor = System.Drawing.Color.MidnightBlue
        Me.xdwTest.HeaderForeColor = System.Drawing.Color.WhiteSmoke
        Me.xdwTest.Location = New System.Drawing.Point(24, 312)
        Me.xdwTest.Name = "xdwTest"
        Me.xdwTest.ReadOnly = True
        Me.xdwTest.RowHeaderWidth = 10
        Me.xdwTest.SelectionType = xUtil.xDataWindowSelectionType.MultiSelection
        Me.xdwTest.Size = New System.Drawing.Size(440, 216)
        Me.xdwTest.TabIndex = 5
        '
        'btnNewData
        '
        Me.btnNewData.Location = New System.Drawing.Point(480, 312)
        Me.btnNewData.Name = "btnNewData"
        Me.btnNewData.Size = New System.Drawing.Size(96, 32)
        Me.btnNewData.TabIndex = 6
        Me.btnNewData.Text = "New Data"
        '
        'frmTest
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 15)
        Me.ClientSize = New System.Drawing.Size(768, 542)
        Me.Controls.Add(Me.btnNewData)
        Me.Controls.Add(Me.xdwTest)
        Me.Controls.Add(Me.Button4)
        Me.Controls.Add(Me.Button3)
        Me.Controls.Add(Me.Button2)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.xdwProcess)
        Me.Name = "frmTest"
        CType(Me.xdwProcess, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.xdwTest, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        GetProcess()
    End Sub

    Private Sub XDataWindow1_Navigate(ByVal sender As System.Object, ByVal ne As System.Windows.Forms.NavigateEventArgs)

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

        If oServer.ExecuteToDataset(sSQL, dsSQL) Then

            'Reformat the data if necessary
            'For j = 1 To dsSQL.Tables(0).Rows.Count
            'Next

            xdwProcess.SuspendLayout()
            xdwProcess.DataSource = dsSQL.Tables(0)
            xdwProcess.Refresh()
            xdwProcess.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))

            xdwProcess.AllowNavigation = False


            ' ------ New Method to Set TableStyle

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

            ' ------ New Method to Set TableStyle


            ' ****** Original Method - Begin

            'dgTS = New DataGridTableStyle
            'dgTS.MappingName = dsSQL.Tables(0).TableName
            'dgTS.AlternatingBackColor = System.Drawing.Color.Lavender
            'dgTS.BackColor = System.Drawing.Color.WhiteSmoke
            'dgTS.ForeColor = System.Drawing.Color.MidnightBlue
            'dgTS.GridLineColor = System.Drawing.Color.Gainsboro
            'dgTS.HeaderBackColor = System.Drawing.Color.MidnightBlue
            'dgTS.HeaderForeColor = System.Drawing.Color.WhiteSmoke
            'dgTS.ReadOnly = True

            '' Display column for name
            'oServer.DgAddTBC(dgTS, "dbname", "DB Name", "", HorizontalAlignment.Left, 80, AddressOf xdwFormatterX)
            'oServer.DgAddTBC(dgTS, "hostname", "Host", "", HorizontalAlignment.Left, 100, AddressOf xdwFormatterX)
            'oServer.DgAddTBC(dgTS, "spid", "spid", "", HorizontalAlignment.Right, 50, AddressOf xdwFormatterX)
            'oServer.DgAddTBC(dgTS, "loginname", "loginname", "", HorizontalAlignment.Left, 100, AddressOf xdwFormatterX)
            'oServer.DgAddTBC(dgTS, "status", "status", "", HorizontalAlignment.Left, 100, AddressOf xdwFormatterX)
            'oServer.DgAddTBC(dgTS, "cmd", "Command", "", HorizontalAlignment.Left, 200, AddressOf xdwFormatterX)
            'oServer.DgAddTBC(dgTS, "by_host", "Blocker", "", HorizontalAlignment.Left, 100)
            'oServer.DgAddTBC(dgTS, "by_id", "Blocker ID", "", HorizontalAlignment.Left, 60)
            'oServer.DgAddTBC(dgTS, "by_cmd", "Blocker Command", "", HorizontalAlignment.Left, 200)

            'xdwProcess.TableStyles.Clear()
            'xdwProcess.TableStyles.Add(dgTS)

            ' ****** Original Method - End

            xdwProcess.ResetAfterRefresh()
            xdwProcess.Select()
            xdwProcess.ResumeLayout()

        End If
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


    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        xdwProcess.SelectionType = xUtil.xDataWindowSelectionType.MultiSelection
    End Sub

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        xdwProcess.SelectionType = xUtil.xDataWindowSelectionType.SingleSelection
    End Sub

    Private Sub Button4_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button4.Click
        xdwProcess.SelectionType = xUtil.xDataWindowSelectionType.ManualSelection
    End Sub

    Private Sub btnNewData_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnNewData.Click
        xdwTest.CreateCustomTableStyle("Testing")
        xdwTest.AddTextColumn("dbname", "DB name", "", HorizontalAlignment.Left, 80)
        xdwTest.AddTextColumn("hostname", "Host", "", HorizontalAlignment.Left, 100)
        xdwTest.AddTextColumn("spid", "spid", "", HorizontalAlignment.Right, 50)
        xdwTest.AddTextColumn("loginname", "loginname", "", HorizontalAlignment.Left, 100)
        xdwTest.AddTextColumn("status", "status", "", HorizontalAlignment.Left, 100)
        xdwTest.AddTextColumn("cmd", "Command", "", HorizontalAlignment.Left, 200)
        xdwTest.AddTextColumn("by_host", "Blocker", "", HorizontalAlignment.Left, 100)
        xdwTest.AddTextColumn("by_id", "Blocker ID", "", HorizontalAlignment.Left, 60)
        xdwTest.AddTextColumn("by_cmd", "Blocker Command", "", HorizontalAlignment.Left, 200)
        xdwTest.CloseTableStyle()
    End Sub
End Class
