/*********************IMPORTANT DRAKVUF LICENSE TERMS***********************
 *                                                                         *
 * DRAKVUF (C) 2014-2022 Tamas K Lengyel.                                  *
 * Tamas K Lengyel is hereinafter referred to as the author.               *
 * This program is free software; you may redistribute and/or modify it    *
 * under the terms of the GNU General Public License as published by the   *
 * Free Software Foundation; Version 2 ("GPL"), BUT ONLY WITH ALL OF THE   *
 * CLARIFICATIONS AND EXCEPTIONS DESCRIBED HEREIN.  This guarantees your   *
 * right to use, modify, and redistribute this software under certain      *
 * conditions.  If you wish to embed DRAKVUF technology into proprietary   *
 * software, alternative licenses can be acquired from the author.         *
 *                                                                         *
 * Note that the GPL places important restrictions on "derivative works",  *
 * yet it does not provide a detailed definition of that term.  To avoid   *
 * misunderstandings, we interpret that term as broadly as copyright law   *
 * allows.  For example, we consider an application to constitute a        *
 * derivative work for the purpose of this license if it does any of the   *
 * following with any software or content covered by this license          *
 * ("Covered Software"):                                                   *
 *                                                                         *
 * o Integrates source code from Covered Software.                         *
 *                                                                         *
 * o Reads or includes copyrighted data files.                             *
 *                                                                         *
 * o Is designed specifically to execute Covered Software and parse the    *
 * results (as opposed to typical shell or execution-menu apps, which will *
 * execute anything you tell them to).                                     *
 *                                                                         *
 * o Includes Covered Software in a proprietary executable installer.  The *
 * installers produced by InstallShield are an example of this.  Including *
 * DRAKVUF with other software in compressed or archival form does not     *
 * trigger this provision, provided appropriate open source decompression  *
 * or de-archiving software is widely available for no charge.  For the    *
 * purposes of this license, an installer is considered to include Covered *
 * Software even if it actually retrieves a copy of Covered Software from  *
 * another source during runtime (such as by downloading it from the       *
 * Internet).                                                              *
 *                                                                         *
 * o Links (statically or dynamically) to a library which does any of the  *
 * above.                                                                  *
 *                                                                         *
 * o Executes a helper program, module, or script to do any of the above.  *
 *                                                                         *
 * This list is not exclusive, but is meant to clarify our interpretation  *
 * of derived works with some common examples.  Other people may interpret *
 * the plain GPL differently, so we consider this a special exception to   *
 * the GPL that we apply to Covered Software.  Works which meet any of     *
 * these conditions must conform to all of the terms of this license,      *
 * particularly including the GPL Section 3 requirements of providing      *
 * source code and allowing free redistribution of the work as a whole.    *
 *                                                                         *
 * Any redistribution of Covered Software, including any derived works,    *
 * must obey and carry forward all of the terms of this license, including *
 * obeying all GPL rules and restrictions.  For example, source code of    *
 * the whole work must be provided and free redistribution must be         *
 * allowed.  All GPL references to "this License", are to be treated as    *
 * including the terms and conditions of this license text as well.        *
 *                                                                         *
 * Because this license imposes special exceptions to the GPL, Covered     *
 * Work may not be combined (even as part of a larger work) with plain GPL *
 * software.  The terms, conditions, and exceptions of this license must   *
 * be included as well.  This license is incompatible with some other open *
 * source licenses as well.  In some cases we can relicense portions of    *
 * DRAKVUF or grant special permissions to use it in other open source     *
 * software.  Please contact tamas.k.lengyel@gmail.com with any such       *
 * requests.  Similarly, we don't incorporate incompatible open source     *
 * software into Covered Software without special permission from the      *
 * copyright holders.                                                      *
 *                                                                         *
 * If you have any questions about the licensing restrictions on using     *
 * DRAKVUF in other works, are happy to help.  As mentioned above,         *
 * alternative license can be requested from the author to integrate       *
 * DRAKVUF into proprietary applications and appliances.  Please email     *
 * tamas.k.lengyel@gmail.com for further information.                      *
 *                                                                         *
 * If you have received a written license agreement or contract for        *
 * Covered Software stating terms other than these, you may choose to use  *
 * and redistribute Covered Software under those terms instead of these.   *
 *                                                                         *
 * Source is provided to this software because we believe users have a     *
 * right to know exactly what a program is going to do before they run it. *
 * This also allows you to audit the software for security holes.          *
 *                                                                         *
 * Source code also allows you to port DRAKVUF to new platforms, fix bugs, *
 * and add new features.  You are highly encouraged to submit your changes *
 * on https://github.com/tklengyel/drakvuf, or by other methods.           *
 * By sending these changes, it is understood (unless you specify          *
 * otherwise) that you are offering unlimited, non-exclusive right to      *
 * reuse, modify, and relicense the code.  DRAKVUF will always be          *
 * available Open Source, but this is important because the inability to   *
 * relicense code has caused devastating problems for other Free Software  *
 * projects (such as KDE and NASM).                                        *
 * To specify special license conditions of your contributions, just say   *
 * so when you send them.                                                  *
 *                                                                         *
 * This program is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the DRAKVUF   *
 * license file for more details (it's in a COPYING file included with     *
 * DRAKVUF, and also available from                                        *
 * https://github.com/tklengyel/drakvuf/COPYING)                           *
 *                                                                         *
 ***************************************************************************/

#include <libdrakvuf/libdrakvuf.h>
#include <libvmi/libvmi.h>

#include "plugins/hook_helpers.h"
#include "plugins/output_format.h"
#include "ptracemon.h"
#include "private.h"

using namespace ptracemon_ns;

event_response_t ptracemon::ptrace_cb(drakvuf_t drakvuf, drakvuf_trap_info_t* info)
{
    auto vmi = vmi_lock_guard(drakvuf);
    addr_t pt_regs = drakvuf_get_function_argument(drakvuf, info, 1);

    uint64_t request;
    if (VMI_FAILURE == vmi_read_64_va(vmi, pt_regs + this->offsets[PT_REGS_RDI], 0, &request))
    {
        PRINT_DEBUG("[PTRACEMON] Failed to get rdi from pt_regs\n");
        return VMI_EVENT_RESPONSE_NONE;
    }
    auto request_str = ptrace_request_to_str((ptrace_request_t)request);

    uint64_t pid;
    if (VMI_FAILURE == vmi_read_64_va(vmi, pt_regs + this->offsets[PT_REGS_RSI], 0, &pid))
    {
        PRINT_DEBUG("[PTRACEMON] Failed to get rsi from pt_regs\n");
        return VMI_EVENT_RESPONSE_NONE;
    }

    addr_t target_process_base, dtb;
    if (!drakvuf_get_process_by_pid(drakvuf, (vmi_pid_t)pid, &target_process_base, &dtb))
    {
        PRINT_DEBUG("[PTRACEMON] Failed to get target process\n");
        return VMI_EVENT_RESPONSE_NONE;
    }

    proc_data_t target_process_data;
    if (!drakvuf_get_process_data(drakvuf, target_process_base, &target_process_data))
    {
        PRINT_DEBUG("[PTRACEMON] Probably process already died\n");
        return VMI_EVENT_RESPONSE_NONE;
    }

    fmt::print(this->m_output_format, "ptracemon", drakvuf, info,
        keyval("Type", fmt::Rstr(request_str)),
        keyval("TargetPID", fmt::Nval(target_process_data.pid)),
        keyval("TargetProcessName", fmt::Estr(target_process_data.name))
    );

    g_free(const_cast<char*>(target_process_data.name));

    return VMI_EVENT_RESPONSE_NONE;
}

ptracemon::ptracemon(drakvuf_t drakvuf, output_format_t output) : pluginex(drakvuf, output)
{
    if (!drakvuf_get_kernel_struct_members_array_rva(drakvuf, pt_regs_offsets_name, this->offsets.size(), this->offsets.data()))
    {
        PRINT_DEBUG("[PTRACEMON] Failed to get offsets\n");
        return;
    }

    syshook = createSyscallHook("__x64_sys_ptrace", &ptracemon::ptrace_cb, "ptrace");
    if (nullptr == syshook)
    {
        PRINT_DEBUG("[PTRACEMON] Method __x64_sys_ptrace not found\n");
        return;
    }
}