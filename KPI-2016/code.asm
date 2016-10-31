.586
.model flat, stdcall
includelib kernel32.lib
ExitProcess PROTO,
x:DWORD
WaitMsg PROTO
WriteString PROTO
Crlf PROTO

.data
L01 db 'Hello world !', 0
L02 db 'I am first programm', 0
.code
 main PROC
mov EDX, offset L01
invoke WriteString
invoke Crlf
mov EDX, offset L02
invoke WriteString
invoke Crlf
invoke WaitMsg
invoke ExitProcess, 0
main ENDP
end main