object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 441
  ClientWidth = 624
  Color = clDarkgray
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesigned
  TextHeight = 15
  object Edit1: TEdit
    Left = 72
    Top = 96
    Width = 121
    Height = 33
    TabOrder = 0
    Text = 'Input'
  end
  object CheckBox1: TCheckBox
    Left = 72
    Top = 184
    Width = 153
    Height = 33
    Caption = 'Write Signal for register'
    TabOrder = 1
  end
  object CheckBox2: TCheckBox
    Left = 72
    Top = 232
    Width = 153
    Height = 33
    Caption = 'Read Signal for register'
    TabOrder = 2
    OnClick = CheckBox2Click
  end
end
