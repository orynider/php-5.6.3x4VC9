Public Class frmSQLScriptGenerator
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
    Friend WithEvents btnRefreshList As System.Windows.Forms.Button
    Friend WithEvents btnShowScript As System.Windows.Forms.Button
    Friend WithEvents tcSybase As System.Windows.Forms.TabControl
    Friend WithEvents tpUserTable As System.Windows.Forms.TabPage
    Friend WithEvents tpTrigger As System.Windows.Forms.TabPage
    Friend WithEvents tpALL As System.Windows.Forms.TabPage
    Friend WithEvents xdwUserTable As xUtil.xDataWindow
    Friend WithEvents xdwStoredProcedure As xUtil.xDataWindow
    Friend WithEvents xdwView As xUtil.xDataWindow
    Friend WithEvents xdwTrigger As xUtil.xDataWindow
    Friend WithEvents xdwAll As xUtil.xDataWindow
    Friend WithEvents tpProcedure As System.Windows.Forms.TabPage
    Friend WithEvents tpOption As System.Windows.Forms.TabPage
    Friend WithEvents lblTableScripts As System.Windows.Forms.Label
    Friend WithEvents cbxTableDrop As System.Windows.Forms.CheckBox
    Friend WithEvents cmbObjectPermission As System.Windows.Forms.ComboBox
    Friend WithEvents cbxObjectPermission As System.Windows.Forms.CheckBox
    Friend WithEvents cbxOtherCreation As System.Windows.Forms.CheckBox
    Friend WithEvents cbxOtherDrop As System.Windows.Forms.CheckBox
    Friend WithEvents lblOtherScripts As System.Windows.Forms.Label
    Friend WithEvents cbxTableCheckConstraint As System.Windows.Forms.CheckBox
    Friend WithEvents cbxTableTrigger As System.Windows.Forms.CheckBox
    Friend WithEvents cbxTableIndex As System.Windows.Forms.CheckBox
    Friend WithEvents cbxTableCreation As System.Windows.Forms.CheckBox
    Friend WithEvents cbxTableKey As System.Windows.Forms.CheckBox
    Friend WithEvents cbxTableUniqueConstraint As System.Windows.Forms.CheckBox
    Friend WithEvents lblScriptInfo As System.Windows.Forms.Label
    Friend WithEvents cbxCreationMessage As System.Windows.Forms.CheckBox
    Friend WithEvents btnSaveScript As System.Windows.Forms.Button
    Friend WithEvents txtFilePath As System.Windows.Forms.TextBox
    Friend WithEvents btnGetFilePath As System.Windows.Forms.Button
    Friend WithEvents btnCopyScript As System.Windows.Forms.Button
    Friend WithEvents lblScriptGeneration As System.Windows.Forms.Label
    Friend WithEvents txtSearchKey As System.Windows.Forms.TextBox
    Friend WithEvents tpView As System.Windows.Forms.TabPage
    Friend WithEvents btnClear As System.Windows.Forms.Button
    Friend WithEvents fcTxtScript As FastColoredTextBoxNS.FastColoredTextBox
    Friend WithEvents btnSaveScripts As System.Windows.Forms.Button
    Friend WithEvents Label1 As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim XDataWindowSettings1 As xUtil.xDataWindowSettings = New xUtil.xDataWindowSettings()
        Dim XDataWindowSettings2 As xUtil.xDataWindowSettings = New xUtil.xDataWindowSettings()
        Dim XDataWindowSettings3 As xUtil.xDataWindowSettings = New xUtil.xDataWindowSettings()
        Dim XDataWindowSettings4 As xUtil.xDataWindowSettings = New xUtil.xDataWindowSettings()
        Dim XDataWindowSettings5 As xUtil.xDataWindowSettings = New xUtil.xDataWindowSettings()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(frmSQLScriptGenerator))
        Me.btnRefreshList = New System.Windows.Forms.Button()
        Me.btnShowScript = New System.Windows.Forms.Button()
        Me.tcSybase = New System.Windows.Forms.TabControl()
        Me.tpALL = New System.Windows.Forms.TabPage()
        Me.xdwAll = New xUtil.xDataWindow()
        Me.tpUserTable = New System.Windows.Forms.TabPage()
        Me.xdwUserTable = New xUtil.xDataWindow()
        Me.tpProcedure = New System.Windows.Forms.TabPage()
        Me.xdwStoredProcedure = New xUtil.xDataWindow()
        Me.tpView = New System.Windows.Forms.TabPage()
        Me.xdwView = New xUtil.xDataWindow()
        Me.tpTrigger = New System.Windows.Forms.TabPage()
        Me.xdwTrigger = New xUtil.xDataWindow()
        Me.tpOption = New System.Windows.Forms.TabPage()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.btnGetFilePath = New System.Windows.Forms.Button()
        Me.txtFilePath = New System.Windows.Forms.TextBox()
        Me.lblScriptGeneration = New System.Windows.Forms.Label()
        Me.cbxCreationMessage = New System.Windows.Forms.CheckBox()
        Me.cbxTableUniqueConstraint = New System.Windows.Forms.CheckBox()
        Me.cbxTableKey = New System.Windows.Forms.CheckBox()
        Me.cmbObjectPermission = New System.Windows.Forms.ComboBox()
        Me.cbxObjectPermission = New System.Windows.Forms.CheckBox()
        Me.cbxOtherCreation = New System.Windows.Forms.CheckBox()
        Me.cbxOtherDrop = New System.Windows.Forms.CheckBox()
        Me.lblOtherScripts = New System.Windows.Forms.Label()
        Me.cbxTableCheckConstraint = New System.Windows.Forms.CheckBox()
        Me.cbxTableTrigger = New System.Windows.Forms.CheckBox()
        Me.cbxTableIndex = New System.Windows.Forms.CheckBox()
        Me.cbxTableCreation = New System.Windows.Forms.CheckBox()
        Me.cbxTableDrop = New System.Windows.Forms.CheckBox()
        Me.lblTableScripts = New System.Windows.Forms.Label()
        Me.lblScriptInfo = New System.Windows.Forms.Label()
        Me.btnSaveScript = New System.Windows.Forms.Button()
        Me.btnCopyScript = New System.Windows.Forms.Button()
        Me.txtSearchKey = New System.Windows.Forms.TextBox()
        Me.btnClear = New System.Windows.Forms.Button()
        Me.fcTxtScript = New FastColoredTextBoxNS.FastColoredTextBox()
        Me.btnSaveScripts = New System.Windows.Forms.Button()
        Me.tcSybase.SuspendLayout()
        Me.tpALL.SuspendLayout()
        CType(Me.xdwAll, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.tpUserTable.SuspendLayout()
        CType(Me.xdwUserTable, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.tpProcedure.SuspendLayout()
        CType(Me.xdwStoredProcedure, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.tpView.SuspendLayout()
        CType(Me.xdwView, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.tpTrigger.SuspendLayout()
        CType(Me.xdwTrigger, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.tpOption.SuspendLayout()
        CType(Me.fcTxtScript, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'btnRefreshList
        '
        Me.btnRefreshList.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btnRefreshList.Location = New System.Drawing.Point(296, 7)
        Me.btnRefreshList.Name = "btnRefreshList"
        Me.btnRefreshList.Size = New System.Drawing.Size(72, 22)
        Me.btnRefreshList.TabIndex = 1
        Me.btnRefreshList.Text = "Refresh"
        '
        'btnShowScript
        '
        Me.btnShowScript.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btnShowScript.Location = New System.Drawing.Point(368, 7)
        Me.btnShowScript.Name = "btnShowScript"
        Me.btnShowScript.Size = New System.Drawing.Size(80, 22)
        Me.btnShowScript.TabIndex = 3
        Me.btnShowScript.Text = "Script >>"
        '
        'tcSybase
        '
        Me.tcSybase.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
                    Or System.Windows.Forms.AnchorStyles.Left), System.Windows.Forms.AnchorStyles)
        Me.tcSybase.Controls.Add(Me.tpALL)
        Me.tcSybase.Controls.Add(Me.tpUserTable)
        Me.tcSybase.Controls.Add(Me.tpProcedure)
        Me.tcSybase.Controls.Add(Me.tpView)
        Me.tcSybase.Controls.Add(Me.tpTrigger)
        Me.tcSybase.Controls.Add(Me.tpOption)
        Me.tcSybase.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.tcSybase.Location = New System.Drawing.Point(8, 58)
        Me.tcSybase.Name = "tcSybase"
        Me.tcSybase.SelectedIndex = 0
        Me.tcSybase.Size = New System.Drawing.Size(440, 544)
        Me.tcSybase.TabIndex = 4
        '
        'tpALL
        '
        Me.tpALL.Controls.Add(Me.xdwAll)
        Me.tpALL.Location = New System.Drawing.Point(4, 25)
        Me.tpALL.Name = "tpALL"
        Me.tpALL.Size = New System.Drawing.Size(432, 515)
        Me.tpALL.TabIndex = 4
        Me.tpALL.Text = "ALL"
        '
        'xdwAll
        '
        Me.xdwAll.AllowNavigation = False
        Me.xdwAll.AlternatingBackColor = System.Drawing.Color.Lavender
        Me.xdwAll.BackColor = System.Drawing.Color.WhiteSmoke
        Me.xdwAll.CaptionBackColor = System.Drawing.Color.Gray
        Me.xdwAll.CaptionForeColor = System.Drawing.Color.White
        Me.xdwAll.DataMember = ""
        Me.xdwAll.Dock = System.Windows.Forms.DockStyle.Fill
        Me.xdwAll.ForeColor = System.Drawing.Color.MidnightBlue
        Me.xdwAll.GridLineColor = System.Drawing.Color.Gainsboro
        Me.xdwAll.HeaderBackColor = System.Drawing.Color.MidnightBlue
        Me.xdwAll.HeaderForeColor = System.Drawing.Color.WhiteSmoke
        Me.xdwAll.Location = New System.Drawing.Point(0, 0)
        Me.xdwAll.Name = "xdwAll"
        Me.xdwAll.ReadOnly = True
        Me.xdwAll.RowHeaderWidth = 10
        Me.xdwAll.SelectionType = xUtil.xDataWindowSelectionType.ManualSelection
        XDataWindowSettings1.AlternatingBackColor = System.Drawing.Color.Lavender
        XDataWindowSettings1.BackColor = System.Drawing.Color.WhiteSmoke
        XDataWindowSettings1.CaptionInFocusBackColor = System.Drawing.Color.Yellow
        XDataWindowSettings1.CaptionInFocusForeColor = System.Drawing.Color.Blue
        XDataWindowSettings1.CaptionOutFocusBackColor = System.Drawing.Color.Gray
        XDataWindowSettings1.CaptionOutFocusForeColor = System.Drawing.Color.White
        XDataWindowSettings1.ForeColor = System.Drawing.Color.MidnightBlue
        XDataWindowSettings1.GridLineColor = System.Drawing.Color.Gainsboro
        XDataWindowSettings1.HeadeBackColor = System.Drawing.Color.MidnightBlue
        XDataWindowSettings1.HeaderForeColor = System.Drawing.Color.WhiteSmoke
        XDataWindowSettings1.RowHeaderVisible = True
        XDataWindowSettings1.RowHeaderWidth = 10
        Me.xdwAll.Settings = XDataWindowSettings1
        Me.xdwAll.Size = New System.Drawing.Size(432, 515)
        Me.xdwAll.TabIndex = 0
        '
        'tpUserTable
        '
        Me.tpUserTable.Controls.Add(Me.xdwUserTable)
        Me.tpUserTable.Location = New System.Drawing.Point(4, 25)
        Me.tpUserTable.Name = "tpUserTable"
        Me.tpUserTable.Size = New System.Drawing.Size(432, 515)
        Me.tpUserTable.TabIndex = 0
        Me.tpUserTable.Text = "User Tables"
        '
        'xdwUserTable
        '
        Me.xdwUserTable.AllowNavigation = False
        Me.xdwUserTable.AlternatingBackColor = System.Drawing.Color.Lavender
        Me.xdwUserTable.BackColor = System.Drawing.Color.WhiteSmoke
        Me.xdwUserTable.CaptionBackColor = System.Drawing.Color.Gray
        Me.xdwUserTable.CaptionForeColor = System.Drawing.Color.White
        Me.xdwUserTable.DataMember = ""
        Me.xdwUserTable.Dock = System.Windows.Forms.DockStyle.Fill
        Me.xdwUserTable.ForeColor = System.Drawing.Color.MidnightBlue
        Me.xdwUserTable.GridLineColor = System.Drawing.Color.Gainsboro
        Me.xdwUserTable.HeaderBackColor = System.Drawing.Color.MidnightBlue
        Me.xdwUserTable.HeaderForeColor = System.Drawing.Color.WhiteSmoke
        Me.xdwUserTable.Location = New System.Drawing.Point(0, 0)
        Me.xdwUserTable.Name = "xdwUserTable"
        Me.xdwUserTable.ReadOnly = True
        Me.xdwUserTable.RowHeaderWidth = 10
        Me.xdwUserTable.SelectionType = xUtil.xDataWindowSelectionType.ManualSelection
        XDataWindowSettings2.AlternatingBackColor = System.Drawing.Color.Lavender
        XDataWindowSettings2.BackColor = System.Drawing.Color.WhiteSmoke
        XDataWindowSettings2.CaptionInFocusBackColor = System.Drawing.Color.Yellow
        XDataWindowSettings2.CaptionInFocusForeColor = System.Drawing.Color.Blue
        XDataWindowSettings2.CaptionOutFocusBackColor = System.Drawing.Color.Gray
        XDataWindowSettings2.CaptionOutFocusForeColor = System.Drawing.Color.White
        XDataWindowSettings2.ForeColor = System.Drawing.Color.MidnightBlue
        XDataWindowSettings2.GridLineColor = System.Drawing.Color.Gainsboro
        XDataWindowSettings2.HeadeBackColor = System.Drawing.Color.MidnightBlue
        XDataWindowSettings2.HeaderForeColor = System.Drawing.Color.WhiteSmoke
        XDataWindowSettings2.RowHeaderVisible = True
        XDataWindowSettings2.RowHeaderWidth = 10
        Me.xdwUserTable.Settings = XDataWindowSettings2
        Me.xdwUserTable.Size = New System.Drawing.Size(432, 515)
        Me.xdwUserTable.TabIndex = 0
        '
        'tpProcedure
        '
        Me.tpProcedure.Controls.Add(Me.xdwStoredProcedure)
        Me.tpProcedure.Location = New System.Drawing.Point(4, 25)
        Me.tpProcedure.Name = "tpProcedure"
        Me.tpProcedure.Size = New System.Drawing.Size(432, 515)
        Me.tpProcedure.TabIndex = 1
        Me.tpProcedure.Text = "Procedures"
        '
        'xdwStoredProcedure
        '
        Me.xdwStoredProcedure.AllowNavigation = False
        Me.xdwStoredProcedure.AlternatingBackColor = System.Drawing.Color.Lavender
        Me.xdwStoredProcedure.BackColor = System.Drawing.Color.WhiteSmoke
        Me.xdwStoredProcedure.CaptionBackColor = System.Drawing.Color.Gray
        Me.xdwStoredProcedure.CaptionForeColor = System.Drawing.Color.White
        Me.xdwStoredProcedure.DataMember = ""
        Me.xdwStoredProcedure.Dock = System.Windows.Forms.DockStyle.Fill
        Me.xdwStoredProcedure.ForeColor = System.Drawing.Color.MidnightBlue
        Me.xdwStoredProcedure.GridLineColor = System.Drawing.Color.Gainsboro
        Me.xdwStoredProcedure.HeaderBackColor = System.Drawing.Color.MidnightBlue
        Me.xdwStoredProcedure.HeaderForeColor = System.Drawing.Color.WhiteSmoke
        Me.xdwStoredProcedure.Location = New System.Drawing.Point(0, 0)
        Me.xdwStoredProcedure.Name = "xdwStoredProcedure"
        Me.xdwStoredProcedure.ReadOnly = True
        Me.xdwStoredProcedure.RowHeaderWidth = 10
        Me.xdwStoredProcedure.SelectionType = xUtil.xDataWindowSelectionType.ManualSelection
        XDataWindowSettings3.AlternatingBackColor = System.Drawing.Color.Lavender
        XDataWindowSettings3.BackColor = System.Drawing.Color.WhiteSmoke
        XDataWindowSettings3.CaptionInFocusBackColor = System.Drawing.Color.Yellow
        XDataWindowSettings3.CaptionInFocusForeColor = System.Drawing.Color.Blue
        XDataWindowSettings3.CaptionOutFocusBackColor = System.Drawing.Color.Gray
        XDataWindowSettings3.CaptionOutFocusForeColor = System.Drawing.Color.White
        XDataWindowSettings3.ForeColor = System.Drawing.Color.MidnightBlue
        XDataWindowSettings3.GridLineColor = System.Drawing.Color.Gainsboro
        XDataWindowSettings3.HeadeBackColor = System.Drawing.Color.MidnightBlue
        XDataWindowSettings3.HeaderForeColor = System.Drawing.Color.WhiteSmoke
        XDataWindowSettings3.RowHeaderVisible = True
        XDataWindowSettings3.RowHeaderWidth = 10
        Me.xdwStoredProcedure.Settings = XDataWindowSettings3
        Me.xdwStoredProcedure.Size = New System.Drawing.Size(432, 515)
        Me.xdwStoredProcedure.TabIndex = 0
        '
        'tpView
        '
        Me.tpView.Controls.Add(Me.xdwView)
        Me.tpView.Location = New System.Drawing.Point(4, 25)
        Me.tpView.Name = "tpView"
        Me.tpView.Size = New System.Drawing.Size(432, 515)
        Me.tpView.TabIndex = 2
        Me.tpView.Text = "Views"
        '
        'xdwView
        '
        Me.xdwView.AllowNavigation = False
        Me.xdwView.AlternatingBackColor = System.Drawing.Color.Lavender
        Me.xdwView.BackColor = System.Drawing.Color.WhiteSmoke
        Me.xdwView.CaptionBackColor = System.Drawing.Color.Gray
        Me.xdwView.CaptionForeColor = System.Drawing.Color.White
        Me.xdwView.DataMember = ""
        Me.xdwView.Dock = System.Windows.Forms.DockStyle.Fill
        Me.xdwView.ForeColor = System.Drawing.Color.MidnightBlue
        Me.xdwView.GridLineColor = System.Drawing.Color.Gainsboro
        Me.xdwView.HeaderBackColor = System.Drawing.Color.MidnightBlue
        Me.xdwView.HeaderForeColor = System.Drawing.Color.WhiteSmoke
        Me.xdwView.Location = New System.Drawing.Point(0, 0)
        Me.xdwView.Name = "xdwView"
        Me.xdwView.ReadOnly = True
        Me.xdwView.RowHeaderWidth = 10
        Me.xdwView.SelectionType = xUtil.xDataWindowSelectionType.ManualSelection
        XDataWindowSettings4.AlternatingBackColor = System.Drawing.Color.Lavender
        XDataWindowSettings4.BackColor = System.Drawing.Color.WhiteSmoke
        XDataWindowSettings4.CaptionInFocusBackColor = System.Drawing.Color.Yellow
        XDataWindowSettings4.CaptionInFocusForeColor = System.Drawing.Color.Blue
        XDataWindowSettings4.CaptionOutFocusBackColor = System.Drawing.Color.Gray
        XDataWindowSettings4.CaptionOutFocusForeColor = System.Drawing.Color.White
        XDataWindowSettings4.ForeColor = System.Drawing.Color.MidnightBlue
        XDataWindowSettings4.GridLineColor = System.Drawing.Color.Gainsboro
        XDataWindowSettings4.HeadeBackColor = System.Drawing.Color.MidnightBlue
        XDataWindowSettings4.HeaderForeColor = System.Drawing.Color.WhiteSmoke
        XDataWindowSettings4.RowHeaderVisible = True
        XDataWindowSettings4.RowHeaderWidth = 10
        Me.xdwView.Settings = XDataWindowSettings4
        Me.xdwView.Size = New System.Drawing.Size(432, 515)
        Me.xdwView.TabIndex = 0
        '
        'tpTrigger
        '
        Me.tpTrigger.Controls.Add(Me.xdwTrigger)
        Me.tpTrigger.Location = New System.Drawing.Point(4, 25)
        Me.tpTrigger.Name = "tpTrigger"
        Me.tpTrigger.Size = New System.Drawing.Size(432, 515)
        Me.tpTrigger.TabIndex = 3
        Me.tpTrigger.Text = "Triggers"
        '
        'xdwTrigger
        '
        Me.xdwTrigger.AllowNavigation = False
        Me.xdwTrigger.AlternatingBackColor = System.Drawing.Color.Lavender
        Me.xdwTrigger.BackColor = System.Drawing.Color.WhiteSmoke
        Me.xdwTrigger.CaptionBackColor = System.Drawing.Color.Gray
        Me.xdwTrigger.CaptionForeColor = System.Drawing.Color.White
        Me.xdwTrigger.DataMember = ""
        Me.xdwTrigger.Dock = System.Windows.Forms.DockStyle.Fill
        Me.xdwTrigger.ForeColor = System.Drawing.Color.MidnightBlue
        Me.xdwTrigger.GridLineColor = System.Drawing.Color.Gainsboro
        Me.xdwTrigger.HeaderBackColor = System.Drawing.Color.MidnightBlue
        Me.xdwTrigger.HeaderForeColor = System.Drawing.Color.WhiteSmoke
        Me.xdwTrigger.Location = New System.Drawing.Point(0, 0)
        Me.xdwTrigger.Name = "xdwTrigger"
        Me.xdwTrigger.ReadOnly = True
        Me.xdwTrigger.RowHeaderWidth = 10
        Me.xdwTrigger.SelectionType = xUtil.xDataWindowSelectionType.ManualSelection
        XDataWindowSettings5.AlternatingBackColor = System.Drawing.Color.Lavender
        XDataWindowSettings5.BackColor = System.Drawing.Color.WhiteSmoke
        XDataWindowSettings5.CaptionInFocusBackColor = System.Drawing.Color.Yellow
        XDataWindowSettings5.CaptionInFocusForeColor = System.Drawing.Color.Blue
        XDataWindowSettings5.CaptionOutFocusBackColor = System.Drawing.Color.Gray
        XDataWindowSettings5.CaptionOutFocusForeColor = System.Drawing.Color.White
        XDataWindowSettings5.ForeColor = System.Drawing.Color.MidnightBlue
        XDataWindowSettings5.GridLineColor = System.Drawing.Color.Gainsboro
        XDataWindowSettings5.HeadeBackColor = System.Drawing.Color.MidnightBlue
        XDataWindowSettings5.HeaderForeColor = System.Drawing.Color.WhiteSmoke
        XDataWindowSettings5.RowHeaderVisible = True
        XDataWindowSettings5.RowHeaderWidth = 10
        Me.xdwTrigger.Settings = XDataWindowSettings5
        Me.xdwTrigger.Size = New System.Drawing.Size(432, 515)
        Me.xdwTrigger.TabIndex = 0
        '
        'tpOption
        '
        Me.tpOption.BackColor = System.Drawing.Color.FromArgb(CType(CType(192, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.tpOption.Controls.Add(Me.Label1)
        Me.tpOption.Controls.Add(Me.btnGetFilePath)
        Me.tpOption.Controls.Add(Me.txtFilePath)
        Me.tpOption.Controls.Add(Me.lblScriptGeneration)
        Me.tpOption.Controls.Add(Me.cbxCreationMessage)
        Me.tpOption.Controls.Add(Me.cbxTableUniqueConstraint)
        Me.tpOption.Controls.Add(Me.cbxTableKey)
        Me.tpOption.Controls.Add(Me.cmbObjectPermission)
        Me.tpOption.Controls.Add(Me.cbxObjectPermission)
        Me.tpOption.Controls.Add(Me.cbxOtherCreation)
        Me.tpOption.Controls.Add(Me.cbxOtherDrop)
        Me.tpOption.Controls.Add(Me.lblOtherScripts)
        Me.tpOption.Controls.Add(Me.cbxTableCheckConstraint)
        Me.tpOption.Controls.Add(Me.cbxTableTrigger)
        Me.tpOption.Controls.Add(Me.cbxTableIndex)
        Me.tpOption.Controls.Add(Me.cbxTableCreation)
        Me.tpOption.Controls.Add(Me.cbxTableDrop)
        Me.tpOption.Controls.Add(Me.lblTableScripts)
        Me.tpOption.Font = New System.Drawing.Font("Arial", 9.75!, CType((System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.FontStyle), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.tpOption.ForeColor = System.Drawing.Color.Navy
        Me.tpOption.Location = New System.Drawing.Point(4, 25)
        Me.tpOption.Name = "tpOption"
        Me.tpOption.Size = New System.Drawing.Size(432, 515)
        Me.tpOption.TabIndex = 5
        Me.tpOption.Text = "Options"
        '
        'Label1
        '
        Me.Label1.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.ForeColor = System.Drawing.Color.Red
        Me.Label1.Location = New System.Drawing.Point(40, 305)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(304, 14)
        Me.Label1.TabIndex = 31
        Me.Label1.Text = "(Leave it BLANK to follow database setting.)"
        '
        'btnGetFilePath
        '
        Me.btnGetFilePath.BackColor = System.Drawing.SystemColors.Control
        Me.btnGetFilePath.Location = New System.Drawing.Point(384, 388)
        Me.btnGetFilePath.Name = "btnGetFilePath"
        Me.btnGetFilePath.Size = New System.Drawing.Size(24, 21)
        Me.btnGetFilePath.TabIndex = 30
        Me.btnGetFilePath.Text = "..."
        Me.btnGetFilePath.UseVisualStyleBackColor = False
        '
        'txtFilePath
        '
        Me.txtFilePath.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtFilePath.Location = New System.Drawing.Point(24, 388)
        Me.txtFilePath.Name = "txtFilePath"
        Me.txtFilePath.ReadOnly = True
        Me.txtFilePath.Size = New System.Drawing.Size(352, 22)
        Me.txtFilePath.TabIndex = 29
        '
        'lblScriptGeneration
        '
        Me.lblScriptGeneration.Font = New System.Drawing.Font("Arial", 9.75!, CType((System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.FontStyle), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblScriptGeneration.ForeColor = System.Drawing.Color.FromArgb(CType(CType(0, Byte), Integer), CType(CType(0, Byte), Integer), CType(CType(192, Byte), Integer))
        Me.lblScriptGeneration.Location = New System.Drawing.Point(24, 367)
        Me.lblScriptGeneration.Name = "lblScriptGeneration"
        Me.lblScriptGeneration.Size = New System.Drawing.Size(336, 18)
        Me.lblScriptGeneration.TabIndex = 28
        Me.lblScriptGeneration.Text = "Script Generation"
        '
        'cbxCreationMessage
        '
        Me.cbxCreationMessage.Checked = True
        Me.cbxCreationMessage.CheckState = System.Windows.Forms.CheckState.Checked
        Me.cbxCreationMessage.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cbxCreationMessage.ForeColor = System.Drawing.Color.FromArgb(CType(CType(0, Byte), Integer), CType(CType(0, Byte), Integer), CType(CType(192, Byte), Integer))
        Me.cbxCreationMessage.Location = New System.Drawing.Point(24, 333)
        Me.cbxCreationMessage.Name = "cbxCreationMessage"
        Me.cbxCreationMessage.Size = New System.Drawing.Size(336, 21)
        Me.cbxCreationMessage.TabIndex = 27
        Me.cbxCreationMessage.Text = "Message for Object Creation"
        '
        'cbxTableUniqueConstraint
        '
        Me.cbxTableUniqueConstraint.Enabled = False
        Me.cbxTableUniqueConstraint.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cbxTableUniqueConstraint.ForeColor = System.Drawing.Color.Black
        Me.cbxTableUniqueConstraint.Location = New System.Drawing.Point(40, 139)
        Me.cbxTableUniqueConstraint.Name = "cbxTableUniqueConstraint"
        Me.cbxTableUniqueConstraint.Size = New System.Drawing.Size(328, 17)
        Me.cbxTableUniqueConstraint.TabIndex = 26
        Me.cbxTableUniqueConstraint.Text = "Table Unique Constraint"
        '
        'cbxTableKey
        '
        Me.cbxTableKey.Enabled = False
        Me.cbxTableKey.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cbxTableKey.ForeColor = System.Drawing.Color.Black
        Me.cbxTableKey.Location = New System.Drawing.Point(40, 159)
        Me.cbxTableKey.Name = "cbxTableKey"
        Me.cbxTableKey.Size = New System.Drawing.Size(328, 18)
        Me.cbxTableKey.TabIndex = 25
        Me.cbxTableKey.Text = "Primary/Foreign Key"
        '
        'cmbObjectPermission
        '
        Me.cmbObjectPermission.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmbObjectPermission.Location = New System.Drawing.Point(40, 284)
        Me.cmbObjectPermission.Name = "cmbObjectPermission"
        Me.cmbObjectPermission.Size = New System.Drawing.Size(344, 24)
        Me.cmbObjectPermission.TabIndex = 24
        '
        'cbxObjectPermission
        '
        Me.cbxObjectPermission.Checked = True
        Me.cbxObjectPermission.CheckState = System.Windows.Forms.CheckState.Checked
        Me.cbxObjectPermission.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cbxObjectPermission.ForeColor = System.Drawing.Color.FromArgb(CType(CType(0, Byte), Integer), CType(CType(0, Byte), Integer), CType(CType(192, Byte), Integer))
        Me.cbxObjectPermission.Location = New System.Drawing.Point(24, 257)
        Me.cbxObjectPermission.Name = "cbxObjectPermission"
        Me.cbxObjectPermission.Size = New System.Drawing.Size(336, 20)
        Me.cbxObjectPermission.TabIndex = 23
        Me.cbxObjectPermission.Text = "Set Object Permission"
        '
        'cbxOtherCreation
        '
        Me.cbxOtherCreation.Checked = True
        Me.cbxOtherCreation.CheckState = System.Windows.Forms.CheckState.Checked
        Me.cbxOtherCreation.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cbxOtherCreation.ForeColor = System.Drawing.Color.Black
        Me.cbxOtherCreation.Location = New System.Drawing.Point(40, 229)
        Me.cbxOtherCreation.Name = "cbxOtherCreation"
        Me.cbxOtherCreation.Size = New System.Drawing.Size(152, 17)
        Me.cbxOtherCreation.TabIndex = 22
        Me.cbxOtherCreation.Text = "Object Creation Script"
        '
        'cbxOtherDrop
        '
        Me.cbxOtherDrop.Checked = True
        Me.cbxOtherDrop.CheckState = System.Windows.Forms.CheckState.Checked
        Me.cbxOtherDrop.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cbxOtherDrop.ForeColor = System.Drawing.Color.Black
        Me.cbxOtherDrop.Location = New System.Drawing.Point(40, 208)
        Me.cbxOtherDrop.Name = "cbxOtherDrop"
        Me.cbxOtherDrop.Size = New System.Drawing.Size(152, 17)
        Me.cbxOtherDrop.TabIndex = 21
        Me.cbxOtherDrop.Text = "Drop Object"
        '
        'lblOtherScripts
        '
        Me.lblOtherScripts.Font = New System.Drawing.Font("Arial", 9.75!, CType((System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.FontStyle), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblOtherScripts.ForeColor = System.Drawing.Color.FromArgb(CType(CType(0, Byte), Integer), CType(CType(0, Byte), Integer), CType(CType(192, Byte), Integer))
        Me.lblOtherScripts.Location = New System.Drawing.Point(24, 187)
        Me.lblOtherScripts.Name = "lblOtherScripts"
        Me.lblOtherScripts.Size = New System.Drawing.Size(336, 18)
        Me.lblOtherScripts.TabIndex = 20
        Me.lblOtherScripts.Text = "Procedure/Trigger/View Scripts"
        '
        'cbxTableCheckConstraint
        '
        Me.cbxTableCheckConstraint.Enabled = False
        Me.cbxTableCheckConstraint.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cbxTableCheckConstraint.ForeColor = System.Drawing.Color.Black
        Me.cbxTableCheckConstraint.Location = New System.Drawing.Point(40, 118)
        Me.cbxTableCheckConstraint.Name = "cbxTableCheckConstraint"
        Me.cbxTableCheckConstraint.Size = New System.Drawing.Size(328, 17)
        Me.cbxTableCheckConstraint.TabIndex = 19
        Me.cbxTableCheckConstraint.Text = "Table Check Constraint"
        '
        'cbxTableTrigger
        '
        Me.cbxTableTrigger.Checked = True
        Me.cbxTableTrigger.CheckState = System.Windows.Forms.CheckState.Checked
        Me.cbxTableTrigger.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cbxTableTrigger.ForeColor = System.Drawing.Color.Black
        Me.cbxTableTrigger.Location = New System.Drawing.Point(40, 97)
        Me.cbxTableTrigger.Name = "cbxTableTrigger"
        Me.cbxTableTrigger.Size = New System.Drawing.Size(328, 17)
        Me.cbxTableTrigger.TabIndex = 18
        Me.cbxTableTrigger.Text = "Table Trigger"
        '
        'cbxTableIndex
        '
        Me.cbxTableIndex.Checked = True
        Me.cbxTableIndex.CheckState = System.Windows.Forms.CheckState.Checked
        Me.cbxTableIndex.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cbxTableIndex.ForeColor = System.Drawing.Color.Black
        Me.cbxTableIndex.Location = New System.Drawing.Point(40, 76)
        Me.cbxTableIndex.Name = "cbxTableIndex"
        Me.cbxTableIndex.Size = New System.Drawing.Size(328, 18)
        Me.cbxTableIndex.TabIndex = 17
        Me.cbxTableIndex.Text = "Table Index"
        '
        'cbxTableCreation
        '
        Me.cbxTableCreation.Checked = True
        Me.cbxTableCreation.CheckState = System.Windows.Forms.CheckState.Checked
        Me.cbxTableCreation.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cbxTableCreation.ForeColor = System.Drawing.Color.Black
        Me.cbxTableCreation.Location = New System.Drawing.Point(40, 55)
        Me.cbxTableCreation.Name = "cbxTableCreation"
        Me.cbxTableCreation.Size = New System.Drawing.Size(328, 18)
        Me.cbxTableCreation.TabIndex = 16
        Me.cbxTableCreation.Text = "Table Creation Script"
        '
        'cbxTableDrop
        '
        Me.cbxTableDrop.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cbxTableDrop.ForeColor = System.Drawing.Color.Red
        Me.cbxTableDrop.Location = New System.Drawing.Point(40, 35)
        Me.cbxTableDrop.Name = "cbxTableDrop"
        Me.cbxTableDrop.Size = New System.Drawing.Size(328, 17)
        Me.cbxTableDrop.TabIndex = 6
        Me.cbxTableDrop.Text = "Drop Table (DATA WILL BE REMOVED)"
        '
        'lblTableScripts
        '
        Me.lblTableScripts.Font = New System.Drawing.Font("Arial", 9.75!, CType((System.Drawing.FontStyle.Bold Or System.Drawing.FontStyle.Underline), System.Drawing.FontStyle), System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblTableScripts.ForeColor = System.Drawing.Color.FromArgb(CType(CType(0, Byte), Integer), CType(CType(0, Byte), Integer), CType(CType(192, Byte), Integer))
        Me.lblTableScripts.Location = New System.Drawing.Point(24, 14)
        Me.lblTableScripts.Name = "lblTableScripts"
        Me.lblTableScripts.Size = New System.Drawing.Size(336, 21)
        Me.lblTableScripts.TabIndex = 0
        Me.lblTableScripts.Text = "Table Scripts"
        '
        'lblScriptInfo
        '
        Me.lblScriptInfo.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.lblScriptInfo.BackColor = System.Drawing.Color.FromArgb(CType(CType(0, Byte), Integer), CType(CType(0, Byte), Integer), CType(CType(192, Byte), Integer))
        Me.lblScriptInfo.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.lblScriptInfo.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblScriptInfo.ForeColor = System.Drawing.Color.Yellow
        Me.lblScriptInfo.Location = New System.Drawing.Point(456, 7)
        Me.lblScriptInfo.Name = "lblScriptInfo"
        Me.lblScriptInfo.Size = New System.Drawing.Size(504, 24)
        Me.lblScriptInfo.TabIndex = 5
        Me.lblScriptInfo.Text = "No Script Selected"
        Me.lblScriptInfo.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
        '
        'btnSaveScript
        '
        Me.btnSaveScript.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnSaveScript.Enabled = False
        Me.btnSaveScript.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btnSaveScript.Location = New System.Drawing.Point(897, 6)
        Me.btnSaveScript.Name = "btnSaveScript"
        Me.btnSaveScript.Size = New System.Drawing.Size(63, 22)
        Me.btnSaveScript.TabIndex = 6
        Me.btnSaveScript.Text = "Save"
        '
        'btnCopyScript
        '
        Me.btnCopyScript.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnCopyScript.Enabled = False
        Me.btnCopyScript.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btnCopyScript.Location = New System.Drawing.Point(837, 6)
        Me.btnCopyScript.Name = "btnCopyScript"
        Me.btnCopyScript.Size = New System.Drawing.Size(63, 22)
        Me.btnCopyScript.TabIndex = 7
        Me.btnCopyScript.Text = "Copy"
        '
        'txtSearchKey
        '
        Me.txtSearchKey.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtSearchKey.Location = New System.Drawing.Point(16, 7)
        Me.txtSearchKey.Name = "txtSearchKey"
        Me.txtSearchKey.Size = New System.Drawing.Size(272, 22)
        Me.txtSearchKey.TabIndex = 8
        '
        'btnClear
        '
        Me.btnClear.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btnClear.Location = New System.Drawing.Point(296, 28)
        Me.btnClear.Name = "btnClear"
        Me.btnClear.Size = New System.Drawing.Size(72, 24)
        Me.btnClear.TabIndex = 9
        Me.btnClear.Text = "Clear"
        '
        'fcTxtScript
        '
        Me.fcTxtScript.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
                    Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.fcTxtScript.AutoScrollMinSize = New System.Drawing.Size(27, 14)
        Me.fcTxtScript.BackBrush = Nothing
        Me.fcTxtScript.BackColor = System.Drawing.Color.FromArgb(CType(CType(255, Byte), Integer), CType(CType(255, Byte), Integer), CType(CType(192, Byte), Integer))
        Me.fcTxtScript.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.fcTxtScript.CharHeight = 14
        Me.fcTxtScript.CharWidth = 8
        Me.fcTxtScript.CommentPrefix = "--"
        Me.fcTxtScript.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.fcTxtScript.DisabledColor = System.Drawing.Color.FromArgb(CType(CType(100, Byte), Integer), CType(CType(180, Byte), Integer), CType(CType(180, Byte), Integer), CType(CType(180, Byte), Integer))
        Me.fcTxtScript.IsReplaceMode = False
        Me.fcTxtScript.Language = FastColoredTextBoxNS.Language.SQL
        Me.fcTxtScript.LeftBracket = Global.Microsoft.VisualBasic.ChrW(40)
        Me.fcTxtScript.Location = New System.Drawing.Point(456, 28)
        Me.fcTxtScript.Name = "fcTxtScript"
        Me.fcTxtScript.Paddings = New System.Windows.Forms.Padding(0)
        Me.fcTxtScript.ReadOnly = True
        Me.fcTxtScript.RightBracket = Global.Microsoft.VisualBasic.ChrW(41)
        Me.fcTxtScript.SelectionColor = System.Drawing.Color.FromArgb(CType(CType(60, Byte), Integer), CType(CType(0, Byte), Integer), CType(CType(0, Byte), Integer), CType(CType(255, Byte), Integer))
        Me.fcTxtScript.Size = New System.Drawing.Size(504, 574)
        Me.fcTxtScript.TabIndex = 10
        Me.fcTxtScript.Zoom = 100
        '
        'btnSaveScripts
        '
        Me.btnSaveScripts.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btnSaveScripts.Location = New System.Drawing.Point(368, 28)
        Me.btnSaveScripts.Name = "btnSaveScripts"
        Me.btnSaveScripts.Size = New System.Drawing.Size(80, 24)
        Me.btnSaveScripts.TabIndex = 11
        Me.btnSaveScripts.Text = "Save"
        '
        'frmSQLScriptGenerator
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(972, 616)
        Me.Controls.Add(Me.btnSaveScripts)
        Me.Controls.Add(Me.fcTxtScript)
        Me.Controls.Add(Me.btnClear)
        Me.Controls.Add(Me.txtSearchKey)
        Me.Controls.Add(Me.btnCopyScript)
        Me.Controls.Add(Me.btnSaveScript)
        Me.Controls.Add(Me.lblScriptInfo)
        Me.Controls.Add(Me.tcSybase)
        Me.Controls.Add(Me.btnShowScript)
        Me.Controls.Add(Me.btnRefreshList)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.Name = "frmSQLScriptGenerator"
        Me.Text = "SQL Script Generator"
        Me.WindowState = System.Windows.Forms.FormWindowState.Maximized
        Me.tcSybase.ResumeLayout(False)
        Me.tpALL.ResumeLayout(False)
        CType(Me.xdwAll, System.ComponentModel.ISupportInitialize).EndInit()
        Me.tpUserTable.ResumeLayout(False)
        CType(Me.xdwUserTable, System.ComponentModel.ISupportInitialize).EndInit()
        Me.tpProcedure.ResumeLayout(False)
        CType(Me.xdwStoredProcedure, System.ComponentModel.ISupportInitialize).EndInit()
        Me.tpView.ResumeLayout(False)
        CType(Me.xdwView, System.ComponentModel.ISupportInitialize).EndInit()
        Me.tpTrigger.ResumeLayout(False)
        CType(Me.xdwTrigger, System.ComponentModel.ISupportInitialize).EndInit()
        Me.tpOption.ResumeLayout(False)
        Me.tpOption.PerformLayout()
        CType(Me.fcTxtScript, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

#End Region

    Private _ScriptObject As String = ""
    Private _dsALL As New DataSet
    Private _dvALL, _dvUserTable, _dvStoredProcedure, _dvView, _dvTrigger As DataView
    Private _bDataReady As Boolean = False

    Private Sub frmSQLScriptGenerator_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Dim sPath As String
        Me.Cursor = Cursors.WaitCursor
        sPath = oApplication.GetKey("Default", "File Path")
        If sPath > "" Then
            txtFilePath.Text = sPath
        Else
            txtFilePath.Text = System.IO.Directory.GetCurrentDirectory
        End If
        Me.GetAllTabs()
        Me.Cursor = Cursors.Arrow
    End Sub


    Private Function GetFullData() As Boolean
        Dim sSQL As String
        Dim oSybase As clsSybaseObjectInfo
        Dim j As Int16
        Dim sType As String
        Dim iSysstat, iSysstat2 As Integer

        If Not (Me._dsALL Is Nothing) Then
            Me._dsALL.Dispose()
        End If
        Me._dsALL = New DataSet

        '        sSQL = "SELECT *,x_ObjType='' FROM sysobjects ORDER BY name "
        sSQL = "SELECT name, id, uid, type, userstat, sysstat, indexdel, schemacnt, sysstat2, crdate, expdate, " _
               & "deltrig, instrig, updtrig, seltrig, ckfirst, cache, objspare, versionts, loginame, x_ObjType='' FROM sysobjects ORDER BY name "
        If oServer.ExecuteToDataset(sSQL, Me._dsALL) Then
            For j = 1 To Me._dsALL.Tables(0).Rows.Count
                sType = CType(Me._dsALL.Tables(0).Rows(j - 1)("type"), String).Trim.ToUpper
                iSysstat = CType(Me._dsALL.Tables(0).Rows(j - 1)("sysstat"), Integer)
                iSysstat2 = CType(Me._dsALL.Tables(0).Rows(j - 1)("sysstat2"), Integer)
                oSybase = New clsSybaseObjectInfo(sType, "", iSysstat, iSysstat2)
                Me._dsALL.Tables(0).Rows(j - 1)("x_ObjType") = oSybase.ObjShortTypeName
            Next
            Me._bDataReady = True
        Else
            Me._bDataReady = False
        End If
        Return Me._bDataReady
    End Function

    Private Sub GetDataWindow(ByRef xdwDisplay As xUtil.xDataWindow, ByRef dvData As DataView, ByVal sFilter As String)
        Dim dt As New System.Data.DataTable
        Dim drs() As System.Data.DataRow
        Dim dr As System.Data.DataRow

        If Me._bDataReady Then

            xdwDisplay.SuspendLayout()
            If sFilter > "" Then
                dt = Me._dsALL.Tables(0).Clone
                drs = Me._dsALL.Tables(0).Select(sFilter)
                For Each dr In drs
                    dt.ImportRow(dr)
                Next
            Else
                dt = Me._dsALL.Tables(0).Copy
            End If

            xdwDisplay.DataSource = dt
            xdwDisplay.Refresh()

            xdwDisplay.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
            xdwDisplay.SelectionType = xUtil.xDataWindowSelectionType.ManualSelection
            xdwDisplay.AllowNavigation = False

            'xdwDisplay.CreateCustomTableStyle(dvData.Table.TableName)
            xdwDisplay.CreateCustomTableStyle(dt.TableName)
            xdwDisplay.AddTextColumn("type", "", "", HorizontalAlignment.Left, 0)
            xdwDisplay.AddTextColumn("sysstat", "", "", HorizontalAlignment.Left, 0)
            xdwDisplay.AddTextColumn("sysstat2", "", "", HorizontalAlignment.Left, 0)
            xdwDisplay.AddTextColumn("name", "Object Name", "", HorizontalAlignment.Left, 200)
            xdwDisplay.AddTextColumn("x_ObjType", "Type", "", HorizontalAlignment.Left, 60)
            xdwDisplay.AddTextColumn("crdate", "Creation Date/Time", "yyyy-MM-dd hh:mm:ss", HorizontalAlignment.Left, 130)
            xdwDisplay.CloseTableStyle()
            xdwDisplay.ResetAfterRefresh()
            xdwDisplay.ResumeLayout()

        End If
    End Sub

    Private Sub btnRefreshList_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnRefreshList.Click
        GetAllTabs()
    End Sub

    Private Sub frmSQLScriptGenerator_Closed(ByVal sender As Object, ByVal e As System.EventArgs) Handles MyBase.Closed
        oApplication.CloseWindow("SQLScriptGenerator")
    End Sub

    Private Sub xdwUserTable_Navigate(ByVal sender As System.Object, ByVal ne As System.Windows.Forms.NavigateEventArgs)
        MsgBox("hi")
    End Sub

    Private Sub GetAllTabs()
        Me.Cursor = Cursors.WaitCursor
        If Me.GetFullData Then
            GetDataWindow(xdwAll, Me._dvALL, "")
            GetDataWindow(xdwUserTable, Me._dvUserTable, "(Type = 'U')")
            GetDataWindow(xdwStoredProcedure, Me._dvStoredProcedure, "(Type = 'P')")
            GetDataWindow(xdwView, Me._dvView, "(Type = 'V')")
            GetDataWindow(xdwTrigger, Me._dvTrigger, "(Type = 'TR')")
        End If
        Me.Cursor = Cursors.Arrow
    End Sub

    Private Sub btnShowScript_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnShowScript.Click
        Dim sObjType, sObjName As String
        Dim iSysStat, iSysStat2 As Integer
        Dim bObjValid As Boolean = False
        Dim oSybase As clsSybaseObjectInfo
        sObjType = ""
        sObjName = ""
        fcTxtScript.Text = ""
        Select Case tcSybase.SelectedTab.Name
            Case tpUserTable.Name
                bObjValid = GetObjectInfo(xdwUserTable, xdwUserTable.CurrentRowIndex, sObjType, sObjName, iSysStat, iSysStat2)
            Case tpProcedure.Name
                bObjValid = GetObjectInfo(xdwStoredProcedure, xdwStoredProcedure.CurrentRowIndex, sObjType, sObjName, iSysStat, iSysStat2)
            Case tpView.Name
                bObjValid = GetObjectInfo(xdwView, xdwView.CurrentRowIndex, sObjType, sObjName, iSysStat, iSysStat2)
            Case tpTrigger.Name
                bObjValid = GetObjectInfo(xdwTrigger, xdwTrigger.CurrentRowIndex, sObjType, sObjName, iSysStat, iSysStat2)
            Case tpALL.Name
                bObjValid = GetObjectInfo(xdwAll, xdwAll.CurrentRowIndex, sObjType, sObjName, iSysStat, iSysStat2)
            Case tpOption.Name
                Return
        End Select
        oSybase = New clsSybaseObjectInfo(sObjType, sObjName, iSysStat, iSysStat2)
        fcTxtScript.Text = ""
        If bObjValid Then
            lblScriptInfo.Text = oSybase.ObjDisplayName
            fcTxtScript.Text = GenScript(oSybase)
            _ScriptObject = oSybase.ObjName
            btnSaveScript.Enabled = True
            btnCopyScript.Enabled = True
        Else
            lblScriptInfo.Text = "No Script Selected"
            _ScriptObject = ""
            btnSaveScript.Enabled = False
            btnCopyScript.Enabled = False
        End If

    End Sub

    Private Function GenScript(ByVal oSybase As clsSybaseObjectInfo) As String
        Dim bDrop, bCreate As Boolean
        Dim sScript As String = ""

        Select Case oSybase.ObjClass
            Case SybaseObjClass.Table
                bDrop = cbxTableDrop.Checked
                bCreate = True  ' Table object is checked inside GenTableScript
            Case SybaseObjClass.Script
                bDrop = cbxOtherDrop.Checked
                bCreate = cbxOtherCreation.Checked
            Case SybaseObjClass.Unknown
                bDrop = False
                bCreate = False
        End Select
        If bDrop Then sScript &= GenDropObjectScript(oSybase)
        sScript &= GenCreateObjectScript(oSybase, bCreate)
        Return (sScript)
    End Function

    Private Function GenDropObjectScript(ByVal oSybase As clsSybaseObjectInfo) As String
        Dim sScript, sDrop As String
        sDrop = "DROP " & oSybase.SybObjName & " " & oSybase.ObjName
        sScript = "IF EXISTS (SELECT 0 FROM sysobjects WHERE id = object_id('" & oSybase.ObjName & "'))" & Chr(13) & Chr(10) & _
                  "BEGIN " & Chr(13) & Chr(10) & _
                  "    PRINT 'Drop Existing " & oSybase.ObjDisplayName & "'" & Chr(13) & Chr(10) & _
                  "    " & sDrop & Chr(13) & Chr(10) & _
                  "END " & Chr(13) & Chr(10) & _
                  "GO " & Chr(13) & Chr(10) & Chr(13) & Chr(10)
        Return sScript
    End Function

    Private Function GenCreateObjectScript(ByVal oSybase As clsSybaseObjectInfo, ByVal bCreate As Boolean) As String
        Dim sScript As String = ""

        Select Case oSybase.ObjType
            Case "U", "S"
                sScript = Me.GenTableScript(oSybase)
                sScript &= Me.GenObjectPermission(oSybase)
            Case "P"
                If bCreate Then sScript = Me.GenSyscommentScript(oSybase)
                sScript &= Me.GenObjectPermission(oSybase)
            Case "R"
                If bCreate Then sScript = Me.GenSyscommentScript(oSybase)
            Case "TR"
                If bCreate Then sScript = Me.GenSyscommentScript(oSybase)
            Case "V"
                If bCreate Then sScript = Me.GenSyscommentScript(oSybase)
                sScript &= Me.GenObjectPermission(oSybase)
        End Select

        Return sScript
    End Function

    Private Function GenTableScript(ByVal oSybase As clsSybaseObjectInfo) As String
        Dim sSQL As String
        Dim dsData As New System.Data.DataSet
        Dim sScript As String = ""
        Dim sColumn As String
        Dim iStatus As Integer
        Dim j As Integer
        Dim sType As String

        If cbxTableCreation.Checked Then
            sSQL = "SELECT colname=a.name, usertype=a.usertype, coltype=b.name, status=a.status, length=a.length, prec=a.prec, scale=a.scale " & _
                   "  FROM syscolumns a, systypes b " & _
                   " WHERE (a.id = object_id('" & oSybase.ObjName & "')) " & _
                   "   AND (a.usertype *= b.usertype) " & _
                   " ORDER BY a.colid "
            If Not oServer.ExecuteToDataset(sSQL, dsData) Then
                dsData.Dispose()
                Return ""
            End If


            sScript = GenMessage("CREATE TABLE " & oSybase.ObjName)

            sScript &= "CREATE TABLE " & oSybase.ObjName & "( " & Chr(13) & Chr(10)

            For j = 0 To dsData.Tables(0).Rows.Count - 1
                sColumn = "  " & CType(dsData.Tables(0).Rows(j)("colname"), String).PadRight(30) & "  "
                sType = CType(dsData.Tables(0).Rows(j)("coltype"), String).Trim

                Select Case sType.ToLower
                    Case "binary"
                        sType &= "(" & CType(dsData.Tables(0).Rows(j)("length"), Integer).ToString & ")"
                    Case "bit"
                    Case "char"
                        sType &= "(" & CType(dsData.Tables(0).Rows(j)("length"), Integer).ToString & ")"
                    Case "date"
                    Case "datetime"
                    Case "decimal"
                        sType &= "(" & CType(dsData.Tables(0).Rows(j)("prec"), Integer).ToString & "," & CType(dsData.Tables(0).Rows(j)("scale"), Integer).ToString & ")"
                    Case "float"
                    Case "image"
                    Case "int"
                    Case "money"
                    Case "nchar"
                        sType &= "(" & CType(dsData.Tables(0).Rows(j)("length"), Integer).ToString & ")"
                    Case "numeric"
                        sType &= "(" & CType(dsData.Tables(0).Rows(j)("prec"), Integer).ToString & "," & CType(dsData.Tables(0).Rows(j)("scale"), Integer).ToString & ")"
                    Case "nvarchar"
                        sType &= "(" & CType(dsData.Tables(0).Rows(j)("length"), Integer).ToString & ")"
                    Case "real"
                    Case "smalldatetime"
                    Case "smallint"
                    Case "smallmoney"
                    Case "sysname"
                        sType &= "(" & CType(dsData.Tables(0).Rows(j)("length"), Integer).ToString & ")"
                    Case "text"
                    Case "time"
                    Case "timestamp"
                    Case "tinyint"
                    Case "unichar"
                        sType &= "(" & CType(dsData.Tables(0).Rows(j)("length"), Integer).ToString & ")"
                    Case "univarchar"
                        sType &= "(" & CType(dsData.Tables(0).Rows(j)("length"), Integer).ToString & ")"
                    Case "varbinary"
                        sType &= "(" & CType(dsData.Tables(0).Rows(j)("length"), Integer).ToString & ")"
                    Case "varchar"
                        sType &= "(" & CType(dsData.Tables(0).Rows(j)("length"), Integer).ToString & ")"
                    Case Else
                End Select
                sColumn &= sType.PadRight(20) & "  "
                iStatus = CType(dsData.Tables(0).Rows(j)("status"), Integer)
                If ((iStatus & 8) = 8) Then
                    sColumn &= "NOT NULL"
                Else
                    sColumn &= "NULL"
                End If
                If j < dsData.Tables(0).Rows.Count - 1 Then sColumn &= ","
                sScript &= sColumn & Chr(13) & Chr(10)
            Next
            dsData.Dispose()
            sScript &= ")" & Chr(13) & Chr(10) & "GO " & Chr(13) & Chr(10) & Chr(13) & Chr(10)
        End If

        If cbxTableIndex.Checked Then
            sScript &= Me.GenTableIndex(oSybase)
        End If

        If cbxTableTrigger.Checked Then
            sScript &= Me.GenTableTrigger(oSybase)
        End If

        Return sScript
    End Function

    Private Function GenTableIndex(ByVal oSybase As clsSybaseObjectInfo) As String

        'Decimal Hex    Status
        '1       0x1    Abort current command or trigger if attempt to insert duplicate key
        '2       0x2    Unique index
        '4       0x4    Abort current command or trigger if attempt to insert duplicate row; always 0 for data-only-locked tables
        '16      0x10   Clustered index
        '64      0x40   Index allows duplicate rows, if an allpages-locked table; always 0 for data-only-locked tables()
        '128     0x80   Sorted object; not set for tables without clustered indexes or for text objects
        '512     0x200  sorted data option used in create index statement
        '2048    0x800  Index on primary key
        '32768   0x8000 Suspect index; index was created under another sort order

        Dim sScript As String = ""
        Dim sSQL As String
        Dim dsData As New System.Data.DataSet
        Dim dsIndex As System.Data.DataSet
        Dim j As Integer
        Dim sIndid As String
        Dim iStatus, iStatus2 As Integer
        Dim sIndex, sIndexType As String
        Dim iLoop, idx As Integer
        Dim sIdx As String
        Dim bIndexComplete As Boolean
        sSQL = "SELECT indid, name, status, status2 " & _
               "  FROM sysindexes " & _
               " WHERE (id = object_id('" & oSybase.ObjName & "')) " & _
               "   AND (indid > 0) " & _
               "   AND (indid < 255) " & _
               " ORDER BY indid "
        If Not oServer.ExecuteToDataset(sSQL, dsData) Then
            dsData.Dispose()
            Return ""
        End If
        sScript = ""
        For j = 0 To dsData.Tables(0).Rows.Count - 1
            iStatus = CType(dsData.Tables(0).Rows(j)("status"), Integer)
            iStatus2 = CType(dsData.Tables(0).Rows(j)("status2"), Integer)
            sIndexType = ""
            If ((iStatus And 2) = 2) Then sIndexType &= "UNIQUE "
            If ((iStatus And 16) = 16) Then
                sIndexType &= "CLUSTERED "
            Else
                sIndexType &= "NONCLUSTERED "
            End If

            sIndex = GenMessage("  CREATE " & sIndexType & " INDEX " & CType(dsData.Tables(0).Rows(j)("name"), String) & " ON " & oSybase.ObjName)
            sIndex &= "CREATE " & sIndexType & " INDEX " & CType(dsData.Tables(0).Rows(j)("name"), String) & " ON " & oSybase.ObjName & Chr(13) & Chr(10)
            sIndid = CType(dsData.Tables(0).Rows(j)("indid"), Integer).ToString
            sIndex &= "( "

            bIndexComplete = False
            iLoop = 0
            Do While Not bIndexComplete
                sSQL = "SELECT "
                For idx = 1 To 5
                    sIdx = ((iLoop * 5) + idx).ToString
                    If idx > 1 Then sSQL &= ", "
                    sSQL &= " col" & sIdx & " = index_col('" & oSybase.ObjName & "'," & sIndid & "," & sIdx & "), " & _
                            " ord" & sIdx & " = index_colorder('" & oSybase.ObjName & "'," & sIndid & "," & sIdx & ")"
                Next
                dsIndex = New System.Data.DataSet
                If Not oServer.ExecuteToDataset(sSQL, dsIndex) Then
                    dsIndex.Dispose()
                    dsData.Dispose()
                    Return ""
                End If
                Dim sColName, sColOrder As String
                For idx = 0 To 4
                    If dsIndex.Tables(0).Rows(0)(idx * 2) Is System.DBNull.Value Then
                        bIndexComplete = True
                        Exit For
                    Else
                        sColName = dsIndex.Tables(0).Rows(0)(idx * 2)
                        sColOrder = dsIndex.Tables(0).Rows(0)(idx * 2 + 1)
                        If (iLoop > 0) Or (idx > 0) Then sIndex &= ", "
                        sIndex &= sColName
                        If sColOrder = "DESC" Then sIndex &= " DESC"
                    End If
                Next
                iLoop += 1
            Loop
            sIndex &= " ) " & Chr(13) & Chr(10) & "GO " & Chr(13) & Chr(10) & Chr(13) & Chr(10)

            sScript &= sIndex
        Next


        Return sScript
    End Function

    Private Function GenTableTrigger(ByVal osybase As clsSybaseObjectInfo) As String
        Dim sScript As String = ""
        Dim sSQL As String
        Dim dsData As New System.Data.DataSet
        Dim iDelTrig, iInsTrig, iUpdTrig, iSelTrig As Integer
        sSQL = "SELECT deltrig, instrig, updtrig, seltrig FROM sysobjects WHERE id = object_id('" & osybase.ObjName & "')"
        If oServer.ExecuteToDataset(sSQL, dsData) Then
            If dsData.Tables(0).Rows.Count = 1 Then
                iDelTrig = CType(dsData.Tables(0).Rows(0)("deltrig"), Integer)
                If iDelTrig > 0 Then
                    sScript &= Me.GenSyscommentScript(iDelTrig)
                End If
                iInsTrig = CType(dsData.Tables(0).Rows(0)("instrig"), Integer)
                If (iInsTrig > 0) And (iInsTrig <> iDelTrig) Then
                    sScript &= Me.GenSyscommentScript(iInsTrig)
                End If
                iUpdTrig = CType(dsData.Tables(0).Rows(0)("updtrig"), Integer)
                If (iUpdTrig > 0) And (iUpdTrig <> iDelTrig) And (iUpdTrig <> iInsTrig) Then
                    sScript &= Me.GenSyscommentScript(iUpdTrig)
                End If
                iSelTrig = CType(dsData.Tables(0).Rows(0)("seltrig"), Integer)
                If (iSelTrig > 0) And (iSelTrig <> iDelTrig) And (iSelTrig <> iInsTrig) And (iSelTrig <> iUpdTrig) Then
                    sScript &= Me.GenSyscommentScript(iSelTrig)
                End If
            End If
        End If
        dsData.Dispose()
        Return sScript
    End Function

    Private Function GenMessage(ByVal sMessage As String) As String
        If Not cbxCreationMessage.Checked Then Return ""
        Return ("PRINT '" & sMessage & "'" & Chr(13) & Chr(10) & "GO " & Chr(13) & Chr(10))
    End Function

    Private Function GenSyscommentScript(ByVal id As Integer) As String
        Return Me.GenSyscommentScript("id = " & id.ToString)
    End Function

    Private Function GenSyscommentScript(ByVal osybase As clsSybaseObjectInfo) As String
        Return (Me.GenSyscommentScript("id =  object_id('" & osybase.ObjName & "') "))
    End Function

    Private Function GenSyscommentScript(ByVal sSQLwhere As String) As String
        Dim sSQL As String
        Dim dsData As New System.Data.DataSet
        Dim sScript As String = ""
        Dim j As Integer
        sSQLwhere = "(" & sSQLwhere.Trim & ") "
        sSQL = "SELECT colid2, colid,texttype, text " & _
               "  FROM syscomments " & _
               " WHERE " & sSQLwhere & _
               " ORDER BY colid2, colid "
        If Not oServer.ExecuteToDataset(sSQL, dsData) Then
            dsData.Dispose()
            Return ""
        End If

        sScript = ""
        For j = 0 To dsData.Tables(0).Rows.Count - 1
            sScript += CType(dsData.Tables(0).Rows(j)("text"), String).PadRight(255)
        Next
        ' Add chr(13) for script with chr(10) only for better display
        sScript = sScript.Replace(Chr(10), Chr(13) & Chr(10))
        ' Remove dummy chr(13) if any
        sScript = sScript.Replace(Chr(13) & Chr(13), Chr(13))

        sScript = sScript.Trim & Chr(13) & Chr(10) & "GO " & Chr(13) & Chr(10) & Chr(13) & Chr(10)
        dsData.Dispose()
        Return sScript
    End Function

    Private Function GenObjectPermission(ByVal oSybase As clsSybaseObjectInfo) As String
        Dim sScript As String = ""
        Dim sUser As String
        If Not cbxObjectPermission.Checked Then Return ""
        sUser = cmbObjectPermission.Text.Trim
        If sUser > "" Then
            sScript = Me.GenObjectPermission(oSybase, sUser)
        Else
            Dim sSQL As String
            Dim dsData As New System.Data.DataSet
            Dim j As Integer
            sSQL = "SELECT DISTINCT user_name=b.name   " & _
                   "  FROM sysprotects a, sysusers b   " & _
                   " WHERE (a.id = object_id('" & oSybase.ObjName & "')) " & _
                   "   AND (a.uid = b.uid) "
            If oServer.ExecuteToDataset(sSQL, dsData) Then
                For j = 0 To dsData.Tables(0).Rows.Count - 1
                    sUser = CType(dsData.Tables(0).Rows(j)("user_name"), String)
                    sScript &= Me.GenObjectPermission(oSybase, sUser)
                Next
            End If
            dsData.Dispose()

        End If

        Return sScript
    End Function


    Private Function GenObjectPermission(ByVal oSybase As clsSybaseObjectInfo, ByVal sUser As String) As String
        Dim sScript As String = ""
        Dim sPermission As String = ""
        If sUser = "" Then Return ""
        Select Case oSybase.ObjType
            Case "U", "V"
                sPermission = "ALL"
            Case "P"
                sPermission = "EXECUTE"
        End Select
        If sPermission > "" Then
            sScript = "GRANT " & sPermission & " ON " & oSybase.ObjName & " TO " & sUser
            sScript = Me.GenMessage(sScript) & sScript & Chr(13) & Chr(10) & "GO " & Chr(13) & Chr(10) & Chr(13) & Chr(10)
        End If
        Return sScript
    End Function

    Private Function GetObjectInfo(ByVal xdwData As xUtil.xDataWindow, ByVal iRow As Integer, ByRef sObjType As String, ByRef sObjName As String, ByRef iSysStat As Integer, ByRef iSysStat2 As Integer) As Boolean
        Dim rows As Integer
        If iRow < 0 Then Return False
        rows = CType(xdwData.DataSource, System.Data.DataTable).Rows.Count
        If (rows < 1) Or (iRow > rows) Then Return False
        sObjType = CType(xdwData(iRow, 0), String)
        iSysStat = CType(xdwData(iRow, 1), Integer)
        iSysStat2 = CType(xdwData(iRow, 2), Integer)
        sObjName = CType(xdwData(iRow, 3), String)
        Return True
    End Function

    Private Sub btnSaveScript_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnSaveScript.Click
        Dim sfd As New SaveFileDialog
        Dim sw As System.IO.StreamWriter
        Dim sFileName As String
        Try
            sfd.InitialDirectory = txtFilePath.Text
            sfd.FileName = _ScriptObject
            sfd.Filter = "SQL Script (*.SQL)|*.SQL|All files (*.*)|*.*"
            If (sfd.ShowDialog() = DialogResult.OK) Then
                sFileName = sfd.FileName
                sw = New System.IO.StreamWriter(sFileName)
                sw.Write(fcTxtScript.Text)
                sw.Close()
            End If

        Catch ex As Exception
            MsgBox(ex.Message)
        End Try
    End Sub

    Private Sub btnGetFilePath_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnGetFilePath.Click
        Dim fbd As New FolderBrowserDialog
        Try
            fbd.RootFolder = Environment.SpecialFolder.MyComputer
            fbd.SelectedPath = txtFilePath.Text
            If (fbd.ShowDialog() = DialogResult.OK) Then
                txtFilePath.Text = fbd.SelectedPath
            End If
        Catch ex As Exception
            MsgBox(ex.Message)
        End Try
        fbd.Dispose()
    End Sub

    Private Sub btnCopyScript_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnCopyScript.Click
        Clipboard.SetDataObject(fcTxtScript.Text)
    End Sub

    Private Sub txtFilePath_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtFilePath.TextChanged
        oApplication.SetKey("Default", "File Path", txtFilePath.Text)
    End Sub

    Private Sub txtSearchKey_KeyPress(ByVal sender As System.Object, ByVal e As System.Windows.Forms.KeyPressEventArgs) Handles txtSearchKey.KeyPress
        Dim iRow As Integer
        If e.KeyChar = Chr(13) Then
            Select Case tcSybase.SelectedTab.Name
                Case tpUserTable.Name
                    iRow = SearchObjName(xdwUserTable)
                Case tpProcedure.Name
                    iRow = SearchObjName(xdwStoredProcedure)
                Case tpView.Name
                    iRow = SearchObjName(xdwView)
                Case tpTrigger.Name
                    iRow = SearchObjName(xdwTrigger)
                Case tpALL.Name
                    iRow = SearchObjName(xdwAll)
            End Select
            ' Search the list for object
        End If
    End Sub

    Private Function SearchObjName(ByRef xdwData As xUtil.xDataWindow) As Integer
        Dim rows As Integer
        Dim idx, iReturn As Integer
        Dim sName As String = txtSearchKey.Text.Trim
        ' rows = CType(xdwData.DataSource, System.Data.DataView).Table.Rows.Count
        rows = CType(xdwData.DataSource, System.Data.DataTable).Rows.Count

        If rows < 1 Then Return -1
        iReturn = -1
        For idx = 0 To rows - 1
            If CType(xdwData(idx, 3), String) >= sName Then
                xdwData.JumpToRow(idx, False)
                If (CType(xdwData(idx, 3), String) = sName) Then xdwData.SelectRow(idx)
                iReturn = idx
                Exit For
            End If
        Next
        Return iReturn
    End Function


    Private Sub tcSybase_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles tcSybase.SelectedIndexChanged
        If tcSybase.SelectedTab.Name = "" Then Return
        If tcSybase.SelectedTab.Name = tpOption.Name Then
            btnShowScript.Enabled = False
            btnClear.Enabled = False
        Else
            btnShowScript.Enabled = True
            btnClear.Enabled = True
        End If
    End Sub

    Private Sub btnClear_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnClear.Click
        Select Case tcSybase.SelectedTab.Name
            Case tpUserTable.Name
                Me.ClearSelection(xdwUserTable)
            Case tpProcedure.Name
                Me.ClearSelection(xdwStoredProcedure)
            Case tpView.Name
                Me.ClearSelection(xdwView)
            Case tpTrigger.Name
                Me.ClearSelection(xdwTrigger)
            Case tpALL.Name
                Me.ClearSelection(xdwAll)
        End Select

    End Sub

    Private Sub ClearSelection(ByVal xData As xUtil.xDataWindow)
        If xData.IsEmpty Then Return
        xData.ClearSelection()
        xData.JumpToRow(xData.CurrentRowIndex)
    End Sub


    Private Sub btnSaveScripts_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnSaveScripts.Click
        Dim sfd As New SaveFileDialog
        Dim sw As System.IO.StreamWriter
        Dim sFileName As String
        Try
            Dim sObjType, sObjName As String
            Dim iSysStat, iSysStat2 As Integer
            Dim bObjValid As Boolean = False
            Dim oSybase As clsSybaseObjectInfo
            Dim xdw As xUtil.xDataWindow = Nothing
            sfd.InitialDirectory = txtFilePath.Text
            sfd.FileName = _ScriptObject
            sfd.Filter = "SQL Script (*.SQL)|*.SQL|All files (*.*)|*.*"
            If (sfd.ShowDialog() = DialogResult.OK) Then
                sFileName = sfd.FileName
                sw = New System.IO.StreamWriter(sFileName)

                Select Case tcSybase.SelectedTab.Name
                    Case tpUserTable.Name
                        xdw = xdwUserTable
                    Case tpProcedure.Name
                        xdw = xdwStoredProcedure
                    Case tpView.Name
                        xdw = xdwView
                    Case tpTrigger.Name
                        xdw = xdwTrigger
                    Case tpALL.Name
                        xdw = xdwAll
                    Case Else

                End Select

                If xdw Is Nothing Then Return

                If (xdw.RowsSelected > 0) Then
                    Dim idx As Integer
                    For idx = 0 To xdw.RowCount - 1
                        If xdw.IsSelected(idx) Then
                            sObjType = ""
                            sObjName = ""
                            iSysStat = 0
                            iSysStat2 = 0
                            If GetObjectInfo(xdw, idx, sObjType, sObjName, iSysStat, iSysStat2) Then
                                oSybase = New clsSybaseObjectInfo(sObjType, sObjName, iSysStat, iSysStat2)
                                sw.Write(GenScript(oSybase))
                            End If
                        End If
                    Next

                Else
                    sObjType = ""
                    sObjName = ""
                    iSysStat = 0
                    iSysStat2 = 0
                    If GetObjectInfo(xdw, xdw.CurrentRowIndex, sObjType, sObjName, iSysStat, iSysStat2) Then
                        oSybase = New clsSybaseObjectInfo(sObjType, sObjName, iSysStat, iSysStat2)
                        sw.Write(GenScript(oSybase))
                        sw.Write(fcTxtScript.Text)
                    End If
                End If
                sw.Close()
            End If

        Catch ex As Exception
            MsgBox(ex.Message)
        End Try

    End Sub
End Class
