; Redefine only when the active window is a console window
; See http://stackoverflow.com/questions/131955/keyboard-shortcut-to-paste-clipboard-content-into-command-prompt-window-win-xp 
#IfWinActive ahk_class ConsoleWindowClass

; Close Command Window with Ctrl+w
$^w::
WinGetTitle sTitle
If (InStr(sTitle, "-")=0) { 
	Send EXIT{Enter}
} else {
	Send ^w
}

return 


; Ctrl+up / Down to scroll command window back and forward
^Up::
;^PgUp::
Send {WheelUp}
return

^Down::
;^PgDown::
Send {WheelDown}
return


; Paste in command window
;;^V::
; Spanish menu (Editar->Pegar, I suppose English version is the same, Edit->Paste)
;;Send !{Space}ep
;;return

#IfWinActive