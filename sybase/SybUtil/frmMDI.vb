Public Class frmMDI
    Inherits System.Windows.Forms.Form

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
    Friend WithEvents mnuMDI As System.Windows.Forms.MainMenu
    Friend WithEvents mnuFile As System.Windows.Forms.MenuItem
    Friend WithEvents mnuExit As System.Windows.Forms.MenuItem
    Friend WithEvents mnuDisconnect As System.Windows.Forms.MenuItem
    Friend WithEvents MenuItem1 As System.Windows.Forms.MenuItem
    Friend WithEvents mnuUtilities As System.Windows.Forms.MenuItem
    Friend WithEvents mnuISQL As System.Windows.Forms.MenuItem
    Friend WithEvents mnuSQLScriptGenerator As System.Windows.Forms.MenuItem
    Friend WithEvents mnuServerInformation As System.Windows.Forms.MenuItem
    Friend WithEvents mnuUserProfile As System.Windows.Forms.MenuItem
    Friend WithEvents MenuItem3 As System.Windows.Forms.MenuItem
    Friend WithEvents mnuUserStatus As System.Windows.Forms.MenuItem
    Friend WithEvents mnuCurrentProcess As System.Windows.Forms.MenuItem
    Friend WithEvents tbMDI As System.Windows.Forms.ToolBar
    Friend WithEvents tbbCurrentProcess As System.Windows.Forms.ToolBarButton
    Friend WithEvents tbbInteractiveSQL As System.Windows.Forms.ToolBarButton
    Friend WithEvents tbbSQLGeneration As System.Windows.Forms.ToolBarButton
    Friend WithEvents ilButton As System.Windows.Forms.ImageList
    Friend WithEvents tbbSeperator01 As System.Windows.Forms.ToolBarButton
    Friend WithEvents tbbSeperator02 As System.Windows.Forms.ToolBarButton
    Friend WithEvents tbbExit As System.Windows.Forms.ToolBarButton
    Friend WithEvents tbbDisconnect As System.Windows.Forms.ToolBarButton
    Friend WithEvents tbbSeperator00 As System.Windows.Forms.ToolBarButton
    Friend WithEvents mnuChangeDatabase As System.Windows.Forms.MenuItem
    Friend WithEvents cmbDatabase As System.Windows.Forms.ComboBox
    Friend WithEvents tbbSeperator03 As System.Windows.Forms.ToolBarButton
    Friend WithEvents tbbTest As System.Windows.Forms.ToolBarButton
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(frmMDI))
        Me.mnuMDI = New System.Windows.Forms.MainMenu(Me.components)
        Me.mnuFile = New System.Windows.Forms.MenuItem()
        Me.mnuChangeDatabase = New System.Windows.Forms.MenuItem()
        Me.mnuDisconnect = New System.Windows.Forms.MenuItem()
        Me.MenuItem1 = New System.Windows.Forms.MenuItem()
        Me.mnuExit = New System.Windows.Forms.MenuItem()
        Me.mnuServerInformation = New System.Windows.Forms.MenuItem()
        Me.mnuUserProfile = New System.Windows.Forms.MenuItem()
        Me.MenuItem3 = New System.Windows.Forms.MenuItem()
        Me.mnuUserStatus = New System.Windows.Forms.MenuItem()
        Me.mnuCurrentProcess = New System.Windows.Forms.MenuItem()
        Me.mnuUtilities = New System.Windows.Forms.MenuItem()
        Me.mnuISQL = New System.Windows.Forms.MenuItem()
        Me.mnuSQLScriptGenerator = New System.Windows.Forms.MenuItem()
        Me.tbMDI = New System.Windows.Forms.ToolBar()
        Me.tbbSeperator00 = New System.Windows.Forms.ToolBarButton()
        Me.tbbExit = New System.Windows.Forms.ToolBarButton()
        Me.tbbDisconnect = New System.Windows.Forms.ToolBarButton()
        Me.tbbSeperator01 = New System.Windows.Forms.ToolBarButton()
        Me.tbbCurrentProcess = New System.Windows.Forms.ToolBarButton()
        Me.tbbSeperator02 = New System.Windows.Forms.ToolBarButton()
        Me.tbbInteractiveSQL = New System.Windows.Forms.ToolBarButton()
        Me.tbbSQLGeneration = New System.Windows.Forms.ToolBarButton()
        Me.tbbSeperator03 = New System.Windows.Forms.ToolBarButton()
        Me.tbbTest = New System.Windows.Forms.ToolBarButton()
        Me.ilButton = New System.Windows.Forms.ImageList(Me.components)
        Me.cmbDatabase = New System.Windows.Forms.ComboBox()
        Me.SuspendLayout()
        '
        'mnuMDI
        '
        Me.mnuMDI.MenuItems.AddRange(New System.Windows.Forms.MenuItem() {Me.mnuFile, Me.mnuServerInformation, Me.mnuUtilities})
        '
        'mnuFile
        '
        Me.mnuFile.Index = 0
        Me.mnuFile.MenuItems.AddRange(New System.Windows.Forms.MenuItem() {Me.mnuChangeDatabase, Me.mnuDisconnect, Me.MenuItem1, Me.mnuExit})
        Me.mnuFile.Text = "&File"
        '
        'mnuChangeDatabase
        '
        Me.mnuChangeDatabase.Index = 0
        Me.mnuChangeDatabase.Text = "&Change Database"
        '
        'mnuDisconnect
        '
        Me.mnuDisconnect.Index = 1
        Me.mnuDisconnect.Shortcut = System.Windows.Forms.Shortcut.F11
        Me.mnuDisconnect.Text = "&Disconnect"
        '
        'MenuItem1
        '
        Me.MenuItem1.Index = 2
        Me.MenuItem1.Text = "-"
        '
        'mnuExit
        '
        Me.mnuExit.Index = 3
        Me.mnuExit.Shortcut = System.Windows.Forms.Shortcut.F12
        Me.mnuExit.Text = "E&xit"
        '
        'mnuServerInformation
        '
        Me.mnuServerInformation.Index = 1
        Me.mnuServerInformation.MenuItems.AddRange(New System.Windows.Forms.MenuItem() {Me.mnuUserProfile, Me.MenuItem3, Me.mnuUserStatus, Me.mnuCurrentProcess})
        Me.mnuServerInformation.Text = "Server &Information"
        '
        'mnuUserProfile
        '
        Me.mnuUserProfile.Index = 0
        Me.mnuUserProfile.Text = "&User Profile"
        '
        'MenuItem3
        '
        Me.MenuItem3.Index = 1
        Me.MenuItem3.Text = "-"
        '
        'mnuUserStatus
        '
        Me.mnuUserStatus.Index = 2
        Me.mnuUserStatus.Text = "&Server Status"
        '
        'mnuCurrentProcess
        '
        Me.mnuCurrentProcess.Index = 3
        Me.mnuCurrentProcess.Shortcut = System.Windows.Forms.Shortcut.F7
        Me.mnuCurrentProcess.Text = "Current &Process"
        '
        'mnuUtilities
        '
        Me.mnuUtilities.Index = 2
        Me.mnuUtilities.MenuItems.AddRange(New System.Windows.Forms.MenuItem() {Me.mnuISQL, Me.mnuSQLScriptGenerator})
        Me.mnuUtilities.Text = "&Utilities"
        '
        'mnuISQL
        '
        Me.mnuISQL.Index = 0
        Me.mnuISQL.Shortcut = System.Windows.Forms.Shortcut.F9
        Me.mnuISQL.Text = "&Interactive SQL"
        '
        'mnuSQLScriptGenerator
        '
        Me.mnuSQLScriptGenerator.Index = 1
        Me.mnuSQLScriptGenerator.Shortcut = System.Windows.Forms.Shortcut.F10
        Me.mnuSQLScriptGenerator.Text = "SQL Script &Generator"
        '
        'tbMDI
        '
        Me.tbMDI.Buttons.AddRange(New System.Windows.Forms.ToolBarButton() {Me.tbbSeperator00, Me.tbbExit, Me.tbbDisconnect, Me.tbbSeperator01, Me.tbbCurrentProcess, Me.tbbSeperator02, Me.tbbInteractiveSQL, Me.tbbSQLGeneration, Me.tbbSeperator03, Me.tbbTest})
        Me.tbMDI.ButtonSize = New System.Drawing.Size(24, 24)
        Me.tbMDI.DropDownArrows = True
        Me.tbMDI.ImageList = Me.ilButton
        Me.tbMDI.Location = New System.Drawing.Point(0, 0)
        Me.tbMDI.Name = "tbMDI"
        Me.tbMDI.ShowToolTips = True
        Me.tbMDI.Size = New System.Drawing.Size(1016, 36)
        Me.tbMDI.TabIndex = 1
        '
        'tbbSeperator00
        '
        Me.tbbSeperator00.Name = "tbbSeperator00"
        Me.tbbSeperator00.Style = System.Windows.Forms.ToolBarButtonStyle.Separator
        '
        'tbbExit
        '
        Me.tbbExit.ImageIndex = 0
        Me.tbbExit.Name = "tbbExit"
        Me.tbbExit.Tag = "EXIT"
        Me.tbbExit.ToolTipText = "Exit"
        '
        'tbbDisconnect
        '
        Me.tbbDisconnect.ImageIndex = 1
        Me.tbbDisconnect.Name = "tbbDisconnect"
        Me.tbbDisconnect.Tag = "DISCONNECT"
        Me.tbbDisconnect.ToolTipText = "Disconnect"
        '
        'tbbSeperator01
        '
        Me.tbbSeperator01.Name = "tbbSeperator01"
        Me.tbbSeperator01.Style = System.Windows.Forms.ToolBarButtonStyle.Separator
        '
        'tbbCurrentProcess
        '
        Me.tbbCurrentProcess.ImageIndex = 2
        Me.tbbCurrentProcess.Name = "tbbCurrentProcess"
        Me.tbbCurrentProcess.Tag = "PROCESS"
        Me.tbbCurrentProcess.ToolTipText = "Current Process"
        '
        'tbbSeperator02
        '
        Me.tbbSeperator02.Name = "tbbSeperator02"
        Me.tbbSeperator02.Style = System.Windows.Forms.ToolBarButtonStyle.Separator
        '
        'tbbInteractiveSQL
        '
        Me.tbbInteractiveSQL.ImageIndex = 3
        Me.tbbInteractiveSQL.Name = "tbbInteractiveSQL"
        Me.tbbInteractiveSQL.Tag = "ISQL"
        Me.tbbInteractiveSQL.ToolTipText = "Interactive SQL"
        '
        'tbbSQLGeneration
        '
        Me.tbbSQLGeneration.ImageIndex = 4
        Me.tbbSQLGeneration.Name = "tbbSQLGeneration"
        Me.tbbSQLGeneration.Tag = "SQLGENERATION"
        Me.tbbSQLGeneration.ToolTipText = "SQL Script Generator"
        '
        'tbbSeperator03
        '
        Me.tbbSeperator03.Name = "tbbSeperator03"
        Me.tbbSeperator03.Style = System.Windows.Forms.ToolBarButtonStyle.Separator
        '
        'tbbTest
        '
        Me.tbbTest.Name = "tbbTest"
        Me.tbbTest.Tag = "TEST"
        Me.tbbTest.Text = "Test"
        Me.tbbTest.Visible = False
        '
        'ilButton
        '
        Me.ilButton.ImageStream = CType(resources.GetObject("ilButton.ImageStream"), System.Windows.Forms.ImageListStreamer)
        Me.ilButton.TransparentColor = System.Drawing.Color.Transparent
        Me.ilButton.Images.SetKeyName(0, "")
        Me.ilButton.Images.SetKeyName(1, "")
        Me.ilButton.Images.SetKeyName(2, "")
        Me.ilButton.Images.SetKeyName(3, "")
        Me.ilButton.Images.SetKeyName(4, "")
        '
        'cmbDatabase
        '
        Me.cmbDatabase.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cmbDatabase.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmbDatabase.Location = New System.Drawing.Point(248, 7)
        Me.cmbDatabase.Name = "cmbDatabase"
        Me.cmbDatabase.Size = New System.Drawing.Size(160, 24)
        Me.cmbDatabase.Sorted = True
        Me.cmbDatabase.TabIndex = 3
        Me.cmbDatabase.Visible = False
        '
        'frmMDI
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(1016, 645)
        Me.Controls.Add(Me.cmbDatabase)
        Me.Controls.Add(Me.tbMDI)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.IsMdiContainer = True
        Me.Menu = Me.mnuMDI
        Me.Name = "frmMDI"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "SybUtil"
        Me.WindowState = System.Windows.Forms.FormWindowState.Maximized
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

#End Region

    Dim _wSQLExecute As frmSQLExecute
    Dim _wSQLScriptGenerator As frmSQLScriptGenerator

    Private Sub frmMDI_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Me.Text = oApplication.FullName & " [" & oServer.ConnectionInfo & "]"
        Dim sSQL As String
        Dim dsData As New System.Data.DataSet
        Dim j As Integer
        sSQL = "SELECT name FROM master..sysdatabases ORDER BY name "
        If oServer.ExecuteToDataset(sSQL, dsData) Then
            For j = 0 To dsData.Tables(0).Rows.Count - 1
                cmbDatabase.Items.Add(CType(dsData.Tables(0).Rows(j)("name"), String))
            Next
        End If
        dsData.Dispose()
        cmbDatabase.Text = oServer.Database
    End Sub

    Private Sub mnuDisconnect_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuDisconnect.Click
        oApplication.CloseAllWindows()
        Me.Close()
    End Sub

    Private Sub mnuExit_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuExit.Click
        oApplication.StopAndQuit()
        Me.Close()
    End Sub

    Private Sub mnuUserProfile_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuUserProfile.Click
        oApplication.OpenWindow("UserProfile")
    End Sub

    Private Sub mnuISQL_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuISQL.Click
        oApplication.OpenWindow("SQLExecute")
    End Sub

    Private Sub mnuSQLScriptGenerator_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuSQLScriptGenerator.Click
        oApplication.OpenWindow("SQLScriptGenerator")
    End Sub

    Private Sub mnuCurrentProcess_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles mnuCurrentProcess.Click
        oApplication.OpenWindow("CurrentProcess")
    End Sub

    Private Sub tbMDI_ButtonClick(ByVal sender As System.Object, ByVal e As System.Windows.Forms.ToolBarButtonClickEventArgs) Handles tbMDI.ButtonClick
        Select Case tbMDI.Buttons(tbMDI.Buttons.IndexOf(e.Button)).Tag.ToString
            Case "EXIT"
                oApplication.StopAndQuit()
                Me.Close()
            Case "DISCONNECT"
                oApplication.CloseAllWindows()
                Me.Close()
            Case "PROCESS"
                oApplication.OpenWindow("CurrentProcess")
            Case "ISQL"
                oApplication.OpenWindow("SQLExecute")
            Case "SQLGENERATION"
                oApplication.OpenWindow("SQLScriptGenerator")
            Case "TEST"
                oApplication.OpenWindow("TEST")
        End Select
    End Sub

    Private Sub frmMDI_Closed(ByVal sender As Object, ByVal e As System.EventArgs) Handles MyBase.Closed
        oApplication.CloseAllWindows()
    End Sub

    Private Sub cmbDatabase_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmbDatabase.SelectedIndexChanged
        If cmbDatabase.Text <> oServer.Database Then
            MsgBox("Sorry, change database not yet available")
            cmbDatabase.Text = oServer.Database
        End If
    End Sub

End Class
