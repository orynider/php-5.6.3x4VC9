Option Explicit On

Imports Microsoft.Win32
Imports System.Security.Cryptography

Public Class frmLogin
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
    Friend WithEvents lblSrvProfile As System.Windows.Forms.Label
    Friend WithEvents txtHost As System.Windows.Forms.TextBox
    Friend WithEvents txtPort As System.Windows.Forms.TextBox
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents txtUserName As System.Windows.Forms.TextBox
    Friend WithEvents txtPassword As System.Windows.Forms.TextBox
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents btnConnect As System.Windows.Forms.Button
    Friend WithEvents btnClose As System.Windows.Forms.Button
    Friend WithEvents cmbServer As System.Windows.Forms.ComboBox
    Friend WithEvents rbNet As System.Windows.Forms.RadioButton
    Friend WithEvents cbxSavePassword As System.Windows.Forms.CheckBox
    Friend WithEvents txtDatabase As System.Windows.Forms.TextBox
    Friend WithEvents lblDatabase As System.Windows.Forms.Label
    Friend WithEvents cboCharSet As System.Windows.Forms.ComboBox
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents rbOLEDB As System.Windows.Forms.RadioButton
    Friend WithEvents btnReadINI As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(frmLogin))
        Me.cmbServer = New System.Windows.Forms.ComboBox()
        Me.lblSrvProfile = New System.Windows.Forms.Label()
        Me.txtHost = New System.Windows.Forms.TextBox()
        Me.txtPort = New System.Windows.Forms.TextBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.txtUserName = New System.Windows.Forms.TextBox()
        Me.txtPassword = New System.Windows.Forms.TextBox()
        Me.rbNet = New System.Windows.Forms.RadioButton()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.btnConnect = New System.Windows.Forms.Button()
        Me.btnClose = New System.Windows.Forms.Button()
        Me.cbxSavePassword = New System.Windows.Forms.CheckBox()
        Me.txtDatabase = New System.Windows.Forms.TextBox()
        Me.lblDatabase = New System.Windows.Forms.Label()
        Me.btnReadINI = New System.Windows.Forms.Button()
        Me.cboCharSet = New System.Windows.Forms.ComboBox()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.rbOLEDB = New System.Windows.Forms.RadioButton()
        Me.SuspendLayout()
        '
        'cmbServer
        '
        Me.cmbServer.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.cmbServer.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmbServer.Location = New System.Drawing.Point(128, 17)
        Me.cmbServer.Name = "cmbServer"
        Me.cmbServer.Size = New System.Drawing.Size(224, 24)
        Me.cmbServer.TabIndex = 0
        '
        'lblSrvProfile
        '
        Me.lblSrvProfile.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblSrvProfile.ForeColor = System.Drawing.Color.Navy
        Me.lblSrvProfile.Location = New System.Drawing.Point(12, 20)
        Me.lblSrvProfile.Name = "lblSrvProfile"
        Me.lblSrvProfile.Size = New System.Drawing.Size(96, 20)
        Me.lblSrvProfile.TabIndex = 1
        Me.lblSrvProfile.Text = "Server Name:"
        '
        'txtHost
        '
        Me.txtHost.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtHost.Location = New System.Drawing.Point(128, 47)
        Me.txtHost.Name = "txtHost"
        Me.txtHost.Size = New System.Drawing.Size(224, 22)
        Me.txtHost.TabIndex = 2
        '
        'txtPort
        '
        Me.txtPort.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtPort.Location = New System.Drawing.Point(358, 47)
        Me.txtPort.Name = "txtPort"
        Me.txtPort.Size = New System.Drawing.Size(80, 22)
        Me.txtPort.TabIndex = 3
        '
        'Label1
        '
        Me.Label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.ForeColor = System.Drawing.Color.Navy
        Me.Label1.Location = New System.Drawing.Point(12, 50)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(96, 14)
        Me.Label1.TabIndex = 4
        Me.Label1.Text = "Host, Port:"
        '
        'Label2
        '
        Me.Label2.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label2.ForeColor = System.Drawing.Color.Navy
        Me.Label2.Location = New System.Drawing.Point(12, 106)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(96, 14)
        Me.Label2.TabIndex = 5
        Me.Label2.Text = "User Name:"
        '
        'Label3
        '
        Me.Label3.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label3.ForeColor = System.Drawing.Color.Navy
        Me.Label3.Location = New System.Drawing.Point(12, 134)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(96, 14)
        Me.Label3.TabIndex = 6
        Me.Label3.Text = "Password:"
        '
        'txtUserName
        '
        Me.txtUserName.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtUserName.Location = New System.Drawing.Point(128, 103)
        Me.txtUserName.Name = "txtUserName"
        Me.txtUserName.Size = New System.Drawing.Size(310, 22)
        Me.txtUserName.TabIndex = 8
        '
        'txtPassword
        '
        Me.txtPassword.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtPassword.Location = New System.Drawing.Point(128, 131)
        Me.txtPassword.Name = "txtPassword"
        Me.txtPassword.PasswordChar = Global.Microsoft.VisualBasic.ChrW(42)
        Me.txtPassword.Size = New System.Drawing.Size(310, 22)
        Me.txtPassword.TabIndex = 9
        '
        'rbNet
        '
        Me.rbNet.Checked = True
        Me.rbNet.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.rbNet.Location = New System.Drawing.Point(128, 166)
        Me.rbNet.Name = "rbNet"
        Me.rbNet.Size = New System.Drawing.Size(104, 18)
        Me.rbNet.TabIndex = 11
        Me.rbNet.TabStop = True
        Me.rbNet.Text = ".Net Provider"
        '
        'Label4
        '
        Me.Label4.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label4.ForeColor = System.Drawing.Color.Navy
        Me.Label4.Location = New System.Drawing.Point(12, 167)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(96, 18)
        Me.Label4.TabIndex = 11
        Me.Label4.Text = "Connection:"
        '
        'btnConnect
        '
        Me.btnConnect.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btnConnect.Location = New System.Drawing.Point(213, 191)
        Me.btnConnect.Name = "btnConnect"
        Me.btnConnect.Size = New System.Drawing.Size(104, 41)
        Me.btnConnect.TabIndex = 13
        Me.btnConnect.Text = "Connect"
        '
        'btnClose
        '
        Me.btnClose.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btnClose.Location = New System.Drawing.Point(334, 190)
        Me.btnClose.Name = "btnClose"
        Me.btnClose.Size = New System.Drawing.Size(104, 41)
        Me.btnClose.TabIndex = 14
        Me.btnClose.Text = "Close"
        '
        'cbxSavePassword
        '
        Me.cbxSavePassword.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cbxSavePassword.ForeColor = System.Drawing.Color.Navy
        Me.cbxSavePassword.Location = New System.Drawing.Point(15, 200)
        Me.cbxSavePassword.Name = "cbxSavePassword"
        Me.cbxSavePassword.Size = New System.Drawing.Size(135, 23)
        Me.cbxSavePassword.TabIndex = 12
        Me.cbxSavePassword.Text = "Save Password"
        '
        'txtDatabase
        '
        Me.txtDatabase.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtDatabase.Location = New System.Drawing.Point(128, 75)
        Me.txtDatabase.Name = "txtDatabase"
        Me.txtDatabase.Size = New System.Drawing.Size(310, 22)
        Me.txtDatabase.TabIndex = 7
        '
        'lblDatabase
        '
        Me.lblDatabase.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDatabase.ForeColor = System.Drawing.Color.Navy
        Me.lblDatabase.Location = New System.Drawing.Point(12, 78)
        Me.lblDatabase.Name = "lblDatabase"
        Me.lblDatabase.Size = New System.Drawing.Size(96, 14)
        Me.lblDatabase.TabIndex = 16
        Me.lblDatabase.Text = "Database:"
        '
        'btnReadINI
        '
        Me.btnReadINI.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btnReadINI.Location = New System.Drawing.Point(358, 14)
        Me.btnReadINI.Name = "btnReadINI"
        Me.btnReadINI.Size = New System.Drawing.Size(80, 29)
        Me.btnReadINI.TabIndex = 17
        Me.btnReadINI.Text = "SQL.INI"
        '
        'cboCharSet
        '
        Me.cboCharSet.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboCharSet.FormattingEnabled = True
        Me.cboCharSet.Items.AddRange(New Object() {"", "cp850", "utf8", "iso_1"})
        Me.cboCharSet.Location = New System.Drawing.Point(358, 163)
        Me.cboCharSet.Name = "cboCharSet"
        Me.cboCharSet.Size = New System.Drawing.Size(80, 21)
        Me.cboCharSet.TabIndex = 18
        '
        'Label5
        '
        Me.Label5.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label5.ForeColor = System.Drawing.Color.Navy
        Me.Label5.Location = New System.Drawing.Point(273, 164)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(79, 18)
        Me.Label5.TabIndex = 19
        Me.Label5.Text = "CharSet:"
        '
        'rbOLEDB
        '
        Me.rbOLEDB.Enabled = False
        Me.rbOLEDB.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.rbOLEDB.Location = New System.Drawing.Point(12, -1)
        Me.rbOLEDB.Name = "rbOLEDB"
        Me.rbOLEDB.Size = New System.Drawing.Size(80, 18)
        Me.rbOLEDB.TabIndex = 10
        Me.rbOLEDB.Text = "OLE DB"
        Me.rbOLEDB.Visible = False
        '
        'frmLogin
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(445, 243)
        Me.ControlBox = False
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.cboCharSet)
        Me.Controls.Add(Me.btnReadINI)
        Me.Controls.Add(Me.lblDatabase)
        Me.Controls.Add(Me.txtDatabase)
        Me.Controls.Add(Me.cbxSavePassword)
        Me.Controls.Add(Me.btnClose)
        Me.Controls.Add(Me.btnConnect)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.rbNet)
        Me.Controls.Add(Me.rbOLEDB)
        Me.Controls.Add(Me.txtPassword)
        Me.Controls.Add(Me.txtUserName)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.txtPort)
        Me.Controls.Add(Me.txtHost)
        Me.Controls.Add(Me.lblSrvProfile)
        Me.Controls.Add(Me.cmbServer)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.KeyPreview = True
        Me.Name = "frmLogin"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "SybUtil.Net"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

#End Region

    Private Sub frmLogin_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Me.Text = oApplication.FullName
        oApplication.SetKey("", "Version", "aplha")
        If oApplication.GetKey("", "First Execute") = "" Then oApplication.SetKey("", "First Execute", Now().ToString)
        oApplication.SetKey("", "Last Execute", Now().ToString)

        oServer.Disconnect()

        LoadServerList()

    End Sub

    Private Sub LoadServerList()
        Dim sConnection() As String
        Dim idx As Integer

        sConnection = oApplication.GetSubKeyNames("Connections")

        cmbServer.Items.Clear()
        For idx = 0 To sConnection.Length - 1
            cmbServer.Items.Add(sConnection(idx))
        Next
        GetProfile("Default", True)

    End Sub

    Private Sub GetProfile(ByVal sSubKey As String, ByVal bUpdateServer As Boolean)
        If bUpdateServer Then cmbServer.Text = oApplication.GetKey(sSubKey, "Server Name").ToUpper
        txtHost.Text = oApplication.GetKey(sSubKey, "Host")
        txtPort.Text = oApplication.GetKey(sSubKey, "Port")
        txtDatabase.Text = oApplication.GetKey(sSubKey, "Database")
        txtUserName.Text = oApplication.GetKey(sSubKey, "User Name")
        Dim encryptPwd As String = oApplication.GetKey(sSubKey, "Password")
        If (encryptPwd > "") Then
            txtPassword.Text = AESCrypter.AES_Decrypt(encryptPwd)
            cbxSavePassword.Checked = True
        Else
            txtPassword.Text = ""
            cbxSavePassword.Checked = False
        End If
        If oApplication.GetKey(sSubKey, "Connection Type") = "OLE DB" Then
            rbOLEDB.Checked = True
            rbNet.Checked = False
        Else
            rbOLEDB.Checked = False
            rbNet.Checked = True
        End If
        cboCharSet.Text = oApplication.GetKey(sSubKey, "CharSet")
        If (cboCharSet.Text = "") Then cboCharSet.Text = "cp850"

    End Sub

    Private Sub SaveProfile(ByVal sSubKey As String)
        oApplication.SetKey(sSubKey, "Server Name", cmbServer.Text.ToUpper)
        oApplication.SetKey(sSubKey, "Host", txtHost.Text)
        oApplication.SetKey(sSubKey, "Port", txtPort.Text)
        oApplication.SetKey(sSubKey, "Database", txtDatabase.Text)
        oApplication.SetKey(sSubKey, "User Name", txtUserName.Text)
        If cbxSavePassword.Checked Then
            Dim encryptPwd As String = AESCrypter.AES_Encrypt(txtPassword.Text)
            oApplication.SetKey(sSubKey, "Password", encryptPwd)
        Else
            oApplication.SetKey(sSubKey, "Password", "")
        End If
        If rbOLEDB.Checked Then
            oApplication.SetKey(sSubKey, "Connection Type", "OLE DB")
        Else
            oApplication.SetKey(sSubKey, "Connection Type", ".Net Provider")
        End If
        oApplication.SetKey(sSubKey, "CharSet", cboCharSet.Text)
    End Sub

    Private Sub SaveProfile(ByVal sSubKey As String, ByVal sServerName As String, ByVal sHost As String, ByVal sPort As String)
        oApplication.SetKey(sSubKey, "Server Name", sServerName.Trim.ToUpper)
        oApplication.SetKey(sSubKey, "Host", sHost.Trim)
        oApplication.SetKey(sSubKey, "Port", sPort.Trim)
    End Sub

    Private Sub btnClose_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnClose.Click
        Me.Close()
    End Sub

    Private Sub btnConnect_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnConnect.Click
        Me.LoginServer()
    End Sub

    Private Function LoginServer() As Boolean
        Dim connType As oServer.ConnectionType
        If rbOLEDB.Checked Then
            connType = oServer.ConnectionType.OLEDB
        Else
            connType = oServer.ConnectionType.NetPorvider
        End If
        Try
            If oServer.Connect(cmbServer.Text, connType, txtHost.Text, txtPort.Text, txtUserName.Text, txtPassword.Text, txtDatabase.Text, cboCharSet.Text) Then
                'If cbxSavePassword.Checked Then
                Me.SaveProfile("Connections\\" & cmbServer.Text)
                Me.SaveProfile("Default")
                'End If
                Me.Close()
                Return False
            Else
                Return False
            End If
        Catch ex As Exception
            MsgBox(ex.Message)
            Return False
        End Try
    End Function

    Private Sub frmLogin_Closing(ByVal sender As Object, ByVal e As System.ComponentModel.CancelEventArgs) Handles MyBase.Closing
        If Not oServer.IsConnected Then oApplication.StopAndQuit()
    End Sub



    Private Sub cmbServer_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmbServer.SelectedIndexChanged
        SetProfile()
        txtPassword.Focus()
    End Sub

    Private Sub cmbServer_TextChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles cmbServer.TextChanged
        SetProfile()
    End Sub

    Private Sub SetProfile()
        Dim sSubKey As String = "Connections\\" & cmbServer.Text
        If cmbServer.Text > "" Then
            If oApplication.GetKey(sSubKey, "Server Name").ToUpper = cmbServer.Text.ToUpper Then
                GetProfile(sSubKey, False)
            End If
        End If
    End Sub

    Private Sub frmLogin_KeyPress(ByVal sender As Object, ByVal e As System.Windows.Forms.KeyPressEventArgs) Handles MyBase.KeyPress
        If e.KeyChar = Chr(Keys.Enter) Then
            LoginServer()
            e.Handled = True
        End If
    End Sub

    Private Sub cmbServer_KeyPress(ByVal sender As Object, ByVal e As System.Windows.Forms.KeyPressEventArgs) Handles cmbServer.KeyPress
        ' Special case, don't why it cannot be captured by forms KeyPress in the combo field.
        If e.KeyChar = Chr(Keys.Enter) Then
            LoginServer()
            e.Handled = True
        End If
    End Sub

    Private Sub btnReadINI_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnReadINI.Click
        Dim ofd As New OpenFileDialog
        Dim sFileName As String
        Try
            ofd.InitialDirectory = "C:\Sybase\INI"
            ofd.FileName = "SQL.INI"
            ofd.Filter = "INI File (*.INI)|*.INI|All files (*.*)|*.*"
            If (ofd.ShowDialog() = DialogResult.OK) Then
                sFileName = ofd.FileName
                Me.ReadINI(sFileName)
                LoadServerList()
                ' GetProfile("Default", True)
            End If
        Catch ex As Exception
            MsgBox(ex.Message)
        End Try
    End Sub

    Private Sub ReadINI(ByVal sFileName As String)
        Dim sr As System.IO.StreamReader
        Dim sLine, sData As String
        Dim sServerName, sIP, sPort As String
        Dim bContinue As Boolean
        Dim nP1, nP2 As Integer
        Try
            sr = New System.IO.StreamReader(sFileName)
            sLine = Nothing
            Do
                If Not (sLine Is Nothing) Then
                    sData = sLine.Trim
                    If sData.StartsWith("[") And sData.EndsWith("]") Then
                        sServerName = sData.Substring(1, sData.Length - 2).ToUpper
                        bContinue = True
                        Do
                            sLine = sr.ReadLine
                            If sLine Is Nothing Then
                                bContinue = False
                            Else
                                sLine = sLine.Trim.ToLower
                                If sLine.StartsWith("query=") Then
                                    nP1 = sLine.IndexOf(",")
                                    nP2 = sLine.LastIndexOf(",")
                                    If nP1 <> nP2 Then
                                        sIP = sLine.Substring(nP1 + 1, (nP2 - nP1 - 1))
                                        sPort = sLine.Substring(nP2 + 1)
                                        If Not IsNumeric(sPort) Then
                                            MsgBox(sServerName & ":" & sIP & "," & sPort)
                                        Else
                                            Me.SaveProfile("Connections\\" & sServerName, sServerName, sIP, sPort)
                                        End If
                                    End If
                                    sLine = sr.ReadLine
                                    bContinue = False
                                ElseIf sLine.StartsWith("[") And sLine.EndsWith("]") Then
                                    bContinue = False
                                End If
                            End If


                        Loop While bContinue
                    Else
                        sLine = sr.ReadLine
                    End If
                Else
                    sLine = sr.ReadLine
                End If
            Loop Until sLine Is Nothing
            sr.Close()
        Catch ex As Exception
            MsgBox(ex.Message)
        End Try
    End Sub

End Class
