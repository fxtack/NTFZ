/*++

    The MIT License (MIT)

    Copyright (c) 2023 Fxtack

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

Module Name:

    FileGuardCore.c

Abstract:

    Definition of communication with user-mode application.

Environment:

    Kernel mode.

--*/

#include "FileGuardCore.h"
#include "Communication.h"

/*-------------------------------------------------------------
    Core control communication routines.
-------------------------------------------------------------*/

NTSTATUS FgCoreControlPortConnectCallback(
    _In_ PFLT_PORT AdminPort,
    _In_ PVOID CorePortCookie,
    _In_reads_bytes_(ContextBytes) PVOID ConnectionContext,
    _In_ ULONG ContextBytes,
    _Flt_ConnectionCookie_Outptr_ PVOID* ConnectionCookie
    )
/*++

Routine Description

    Communication connection callback routine.
    This is called when user-mode connects to the server port.

Arguments

    ClientPort        - This is the client connection port that will be used to send messages from the filter
                      
    ServerPortCookie  - Unused

    ConnectionContext - The connection context passed from the user. This is to recognize which type
                        connection the user is trying to connect.

    SizeofContext     - The size of the connection context.

    ConnectionCookie  - Propagation of the connection context to disconnection callback.

Return Value

    STATUS_SUCCESS                - to accept the connection
    STATUS_INSUFFICIENT_RESOURCES - if memory is not enough
    STATUS_INVALID_PARAMETER_3    - Connection context is not valid.

--*/
{
    PAGED_CODE();

    UNREFERENCED_PARAMETER(AdminPort);
    UNREFERENCED_PARAMETER(CorePortCookie);
    UNREFERENCED_PARAMETER(ConnectionContext);
    UNREFERENCED_PARAMETER(ContextBytes);
    UNREFERENCED_PARAMETER(ConnectionCookie);

    FLT_ASSERT(Globals.ControlClientPort == NULL);

    Globals.ControlClientPort = AdminPort;

    DbgPrint("CannotCore!%s: Communicate port connected.\n", __FUNCTION__);

    return STATUS_SUCCESS;
}

VOID FgCoreControlPortDisconnectCallback(
    _In_opt_ PVOID ConnectionCookie
    ) 
/*++

Routine Description

    Communication disconnection callback routine.
    This is called when user-mode disconnects the server port.

Arguments

    ConnectionCookie - The cookie set in connect notify callback. It is connection context.

Return Value

    None

--*/
{
    PAGED_CODE();

    UNREFERENCED_PARAMETER(ConnectionCookie);

    FLT_ASSERT(Globals.ControlClientPort != NULL);

    FltCloseClientPort(Globals.Filter, &Globals.ControlClientPort);

    DbgPrint("CannotCore!%s: Communicate port disconnected.\n", __FUNCTION__);
}

NTSTATUS
FgCoreControlMessageNotifyCallback(
    _In_opt_ PVOID ConnectionCookie,
    _In_reads_bytes_opt_(InputBytes) PVOID Input,
    _In_ ULONG InputBytes,
    _Out_writes_bytes_to_opt_(OutputBytes, *ReturnSize) PVOID Output,
    _In_ ULONG OutputBytes,
    _Out_ PULONG ReturnSize
    ) 
{
    UNREFERENCED_PARAMETER(ConnectionCookie);
    UNREFERENCED_PARAMETER(Input);
    UNREFERENCED_PARAMETER(InputBytes);
    UNREFERENCED_PARAMETER(Output);
    UNREFERENCED_PARAMETER(OutputBytes);
    UNREFERENCED_PARAMETER(ReturnSize);

    return STATUS_NOT_IMPLEMENTED;
}

/*-------------------------------------------------------------
    Monitor communication routines.
-------------------------------------------------------------*/

NTSTATUS
FgMonitorPortConnectCallback(
    _In_ PFLT_PORT ClientPort,
    _In_ PVOID CorePortCookie,
    _In_reads_bytes_(ContextBytes) PVOID ConnectionContext,
    _In_ ULONG ContextBytes,
    _Flt_ConnectionCookie_Outptr_ PVOID* ConnectionCookie
    )
{
    UNREFERENCED_PARAMETER(ClientPort);
    UNREFERENCED_PARAMETER(CorePortCookie);
    UNREFERENCED_PARAMETER(ConnectionContext);
    UNREFERENCED_PARAMETER(ContextBytes);
    UNREFERENCED_PARAMETER(ConnectionCookie);

    return STATUS_NOT_IMPLEMENTED;
}

VOID
FgMonitorPortDisconnectCallback(
    _In_opt_ PVOID ConnectionCookie
    ) 
{
    UNREFERENCED_PARAMETER(ConnectionCookie);
}
