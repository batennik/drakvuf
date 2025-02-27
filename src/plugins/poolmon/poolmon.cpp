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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <inttypes.h>
#include <dirent.h>
#include <err.h>
#include <ctype.h>

#include "plugins/plugins.h"
#include "plugins/output_format.h"

#include "private.h"
#include "poolmon.h"

static GTree* pooltag_build_tree()
{
    GTree* pooltags = g_tree_new((GCompareFunc) strcmp);

    uint32_t i = 0;
    for (; i < TAG_COUNT; i++)
    {
        g_tree_insert(pooltags, (gpointer) tags[i].tag,
            (gpointer) &tags[i]);
    }

    return pooltags;
}

static event_response_t cb(drakvuf_t drakvuf, drakvuf_trap_info_t* info)
{
    poolmon* p = (poolmon*)info->trap->data;
    page_mode_t pm = drakvuf_get_page_mode(drakvuf);
    reg_t pool_type = 0;
    reg_t size = 0;
    char tag[5] = { [0 ... 4] = '\0' };
    struct pooltag* s = NULL;
    const char* pool_type_str;

    ACCESS_CONTEXT(ctx);
    ctx.translate_mechanism = VMI_TM_PROCESS_DTB;
    ctx.dtb = info->regs->cr3;

    if (pm == VMI_PM_IA32E)
    {
        pool_type = info->regs->rcx;
        size = info->regs->rdx;
        memcpy(tag, &info->regs->r8, sizeof(uint32_t));
    }
    else
    {
        auto vmi = vmi_lock_guard(drakvuf);
        uint32_t _tag;

        ctx.addr = info->regs->rsp+12;
        if ( VMI_FAILURE == vmi_read_32(vmi, &ctx, &_tag) )
            return 0;

        memcpy(tag, &_tag, sizeof(uint32_t));

        ctx.addr = info->regs->rsp+8;
        if ( VMI_FAILURE == vmi_read_32(vmi, &ctx, (uint32_t*)&size) )
            return 0;

        ctx.addr = info->regs->rsp+4;
        if ( VMI_FAILURE == vmi_read_32(vmi, &ctx, (uint32_t*)&pool_type) )
            return 0;
    }

    s = (struct pooltag*)g_tree_lookup(p->pooltag_tree, tag);

    pool_type_str = pool_type<MaxPoolType ? pool_types[pool_type] : "unknown_pool_type";

    std::optional<fmt::Rstr<decltype(s->source)>> source;
    std::optional<fmt::Rstr<decltype(s->description)>> description;
    if (s)
    {
        source = fmt::Rstr(s->source);
        description = fmt::Rstr(s->description);
    }

    // Remove non-ascii characters from tag
    for (size_t i = 0; i < sizeof(tag); ++i)
    {
        if (!isascii(tag[i]))
            tag[i] = '?';
    }

    fmt::print(p->format, "poolmon", drakvuf, info,
        keyval("VCPU", fmt::Nval(info->vcpu)),
        keyval("CR3", fmt::Nval(info->regs->cr3)),
        keyval("Tag", fmt::Qstr(tag)),
        keyval("Type", fmt::Qstr(pool_type_str)),
        keyval("Size", fmt::Nval(size)),
        keyval("Source", source),
        keyval("Description", description)
    );

    return 0;
}

/*void pool_tracker_free(vmi_instance_t vmi, vmi_event_t *event) {
    // TODO: 32-bit inputs are on the stack
    reg_t rcx, rdx;
    drakvuf_t *drakvuf = event->data;

    vmi_get_vcpureg(vmi, &rcx, RCX, event->vcpu_id);
    vmi_get_vcpureg(vmi, &rdx, RDX, event->vcpu_id);

    char ctag[5] = { [0 ... 4] = '\0' };
    memcpy(ctag, &rdx, 4);

    PRINT(drakvuf, HEAPFREE_STRING, rcx, ctag);
}*/

/* ----------------------------------------------------- */

poolmon::poolmon(drakvuf_t drakvuf, output_format_t output)
{
    this->pooltag_tree = pooltag_build_tree();

    this->trap.breakpoint.lookup_type = LOOKUP_KERNEL;
    this->trap.breakpoint.addr_type = ADDR_SYMBOL;
    this->trap.breakpoint.symbol = "ExAllocatePoolWithTag";
    this->trap.name = "ExAllocatePoolWithTag";
    this->trap.type = BREAKPOINT;
    this->trap.cb = cb;
    this->trap.data = (void*)this;
    this->trap.ttl = drakvuf_get_limited_traps_ttl(drakvuf);
    this->trap.ah_cb = nullptr;
    this->format = output;

    if ( !drakvuf_add_trap(drakvuf, &this->trap) )
        throw -1;
}

poolmon::~poolmon()
{
    if (this->pooltag_tree)
        g_tree_destroy(this->pooltag_tree);
}

bool poolmon::stop_impl()
{
    return true;
}
