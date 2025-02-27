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

#ifndef FILEDELETE_PRIVATE_H
#define FILEDELETE_PRIVATE_H

#include "../plugin_utils.h"

#define FILE_DISPOSITION_INFORMATION 13
#define FILE_DELETE_ON_CLOSE 0x1000

enum offset
{
    FILE_OBJECT_TYPE,
    FILE_OBJECT_FLAGS,
    FILE_OBJECT_FILENAME,
    FILE_OBJECT_SECTIONOBJECTPOINTER,
    SECTIONOBJECTPOINTER_DATASECTIONOBJECT,
    SECTIONOBJECTPOINTER_SHAREDCACHEMAP,
    SECTIONOBJECTPOINTER_IMAGESECTIONOBJECT,
    CONTROL_AREA_SEGMENT,
    SEGMENT_CONTROLAREA,
    SEGMENT_SIZEOFSEGMENT,
    SEGMENT_TOTALNUMBEROFPTES,
    SUBSECTION_NEXTSUBSECTION,
    SUBSECTION_SUBSECTIONBASE,
    SUBSECTION_PTESINSUBSECTION,
    SUBSECTION_CONTROLAREA,
    SUBSECTION_STARTINGSECTOR,
    OBJECT_HEADER_BODY,
    OBJECT_HEADER_HANDLE_COUNT,
    __OFFSET_MAX
};

struct createfile_ret_info
{
    vmi_pid_t pid;
    uint32_t tid;
    uint64_t rsp;

    addr_t handle;

    fileextractor* f;
};

enum file_object_flags
{
    FO_FILE_OPEN                    = 0x00000001,
    FO_SYNCHRONOUS_IO               = 0x00000002,
    FO_ALERTABLE_IO                 = 0x00000004,
    FO_NO_INTERMEDIATE_BUFFERING    = 0x00000008,
    FO_WRITE_THROUGH                = 0x00000010,
    FO_SEQUENTIAL_ONLY              = 0x00000020,
    FO_CACHE_SUPPORTED              = 0x00000040,
    FO_NAMED_PIPE                   = 0x00000080,
    FO_STREAM_FILE                  = 0x00000100,
    FO_MAILSLOT                     = 0x00000200,
    FO_GENERATE_AUDIT_ON_CLOSE      = 0x00000400,
    FO_DIRECT_DEVICE_OPEN           = 0x00000800,
    FO_FILE_MODIFIED                = 0x00001000,
    FO_FILE_SIZE_CHANGED            = 0x00002000,
    FO_CLEANUP_COMPLETE             = 0x00004000,
    FO_TEMPORARY_FILE               = 0x00008000,
    FO_DELETE_ON_CLOSE              = 0x00010000,
    FO_OPENED_CASE_SENSITIVE        = 0x00020000,
    FO_HANDLE_CREATED               = 0x00040000,
    FO_FILE_FAST_IO_READ            = 0x00080000,
    FO_RANDOM_ACCESS                = 0x00100000,
    FO_FILE_OPEN_CANCELLED          = 0x00200000,
    FO_VOLUME_OPEN                  = 0x00400000,
    FO_REMOTE_ORIGIN                = 0x01000000,
    FO_DISALLOW_EXCLUSIVE           = 0x02000000,
    FO_SKIP_SET_EVENT               = 0x04000000,
    FO_SKIP_SET_FAST_IO             = 0x08000000,
    FO_INDIRECT_WAIT_OBJECT         = 0x10000000,
    FO_SECTION_MINSTORE_TREATMENT   = 0x20000000,
};

static const char* offset_names[__OFFSET_MAX][2] =
{
    [FILE_OBJECT_TYPE] = {"_FILE_OBJECT", "Type"},
    [FILE_OBJECT_FLAGS] = {"_FILE_OBJECT", "Flags"},
    [FILE_OBJECT_FILENAME] = {"_FILE_OBJECT", "FileName"},
    [FILE_OBJECT_SECTIONOBJECTPOINTER] = {"_FILE_OBJECT", "SectionObjectPointer"},
    [SECTIONOBJECTPOINTER_DATASECTIONOBJECT] = {"_SECTION_OBJECT_POINTERS", "DataSectionObject"},
    [SECTIONOBJECTPOINTER_SHAREDCACHEMAP] = {"_SECTION_OBJECT_POINTERS", "SharedCacheMap"},
    [SECTIONOBJECTPOINTER_IMAGESECTIONOBJECT] = {"_SECTION_OBJECT_POINTERS", "ImageSectionObject"},
    [CONTROL_AREA_SEGMENT] = {"_CONTROL_AREA", "Segment"},
    [SEGMENT_CONTROLAREA] = {"_SEGMENT", "ControlArea"},
    [SEGMENT_SIZEOFSEGMENT] = {"_SEGMENT", "SizeOfSegment"},
    [SEGMENT_TOTALNUMBEROFPTES] = {"_SEGMENT", "TotalNumberOfPtes"},
    [SUBSECTION_NEXTSUBSECTION] = {"_SUBSECTION", "NextSubsection"},
    [SUBSECTION_SUBSECTIONBASE] = {"_SUBSECTION", "SubsectionBase"},
    [SUBSECTION_PTESINSUBSECTION] = {"_SUBSECTION", "PtesInSubsection"},
    [SUBSECTION_CONTROLAREA] = {"_SUBSECTION", "ControlArea"},
    [SUBSECTION_STARTINGSECTOR] = {"_SUBSECTION", "StartingSector"},
    [OBJECT_HEADER_BODY] = { "_OBJECT_HEADER", "Body" },
    [OBJECT_HEADER_HANDLE_COUNT] = { "_OBJECT_HEADER", "HandleCount" },
};

static const flags_str_t fo_flags_map =
{
    REGISTER_FLAG(FO_FILE_OPEN),
    REGISTER_FLAG(FO_SYNCHRONOUS_IO),
    REGISTER_FLAG(FO_ALERTABLE_IO),
    REGISTER_FLAG(FO_NO_INTERMEDIATE_BUFFERING),
    REGISTER_FLAG(FO_WRITE_THROUGH),
    REGISTER_FLAG(FO_SEQUENTIAL_ONLY),
    REGISTER_FLAG(FO_CACHE_SUPPORTED),
    REGISTER_FLAG(FO_NAMED_PIPE),
    REGISTER_FLAG(FO_STREAM_FILE),
    REGISTER_FLAG(FO_MAILSLOT),
    REGISTER_FLAG(FO_GENERATE_AUDIT_ON_CLOSE),
    REGISTER_FLAG(FO_DIRECT_DEVICE_OPEN),
    REGISTER_FLAG(FO_FILE_MODIFIED),
    REGISTER_FLAG(FO_FILE_SIZE_CHANGED),
    REGISTER_FLAG(FO_CLEANUP_COMPLETE),
    REGISTER_FLAG(FO_TEMPORARY_FILE),
    REGISTER_FLAG(FO_DELETE_ON_CLOSE),
    REGISTER_FLAG(FO_OPENED_CASE_SENSITIVE),
    REGISTER_FLAG(FO_HANDLE_CREATED),
    REGISTER_FLAG(FO_FILE_FAST_IO_READ),
    REGISTER_FLAG(FO_RANDOM_ACCESS),
    REGISTER_FLAG(FO_FILE_OPEN_CANCELLED),
    REGISTER_FLAG(FO_VOLUME_OPEN),
    REGISTER_FLAG(FO_REMOTE_ORIGIN),
    REGISTER_FLAG(FO_DISALLOW_EXCLUSIVE),
    REGISTER_FLAG(FO_SKIP_SET_EVENT),
    REGISTER_FLAG(FO_SKIP_SET_FAST_IO),
    REGISTER_FLAG(FO_INDIRECT_WAIT_OBJECT),
    REGISTER_FLAG(FO_SECTION_MINSTORE_TREATMENT),
};

struct task_t
{
    enum class stage_t
    {
        pending,
        queryvolumeinfo,
        queryinfo,
        createsection,
        mapview,
        allocate_pool,
        unmapview,
        close_handle,
        memcpy,
        finished,
    };

    struct return_ctx
    {
        vmi_pid_t ret_pid{0};
        addr_t    ret_rsp{0};
        uint32_t  ret_tid{0};
        x86_registers_t regs;
    };

    enum class task_reason
    {
        write,
        del,
        invalid,
    };

    handle_t handle;
    std::string filename;
    const task_reason reason{task_reason::invalid};
    stage_t stage{stage_t::pending};

    return_ctx target;
    addr_t target_process_base{0};

    const addr_t file_obj{0};
    uint64_t fo_flags{0};
    uint64_t file_size{0};
    uint64_t file_offset{0};
    uint64_t bytes_to_read{0};
    handle_t section_handle{0};
    addr_t view_base{0};

    int idx{0};

    union
    {
        struct
        {
            addr_t out{0};
        } queryvolumeinfo;

        struct
        {
            addr_t out;
        } queryinfo{0};

        struct
        {
            addr_t handle{0};
        } createsection;

        struct
        {
            addr_t base{0};
            addr_t size{0};
        } mapview;

        struct
        {
            size_t bytes_read{0};
            addr_t out{0};
            addr_t io_status_block{0};
        } readfile;
    };

    addr_t pool;

    task_t(handle_t handle_,
        std::string filename_,
        task_reason reason_,
        addr_t file_obj_)
        : handle(handle_)
        , filename(filename_)
        , reason(reason_)
        , file_obj(file_obj_)
    {}
};

struct createfile_result_t : public PluginResult
{
    createfile_result_t()
        : PluginResult(),
          handle()
    {
    }

    addr_t handle;
};

struct IO_STATUS_BLOCK_32
{
    uint32_t status;
    uint32_t info;
} __attribute__((packed));

struct IO_STATUS_BLOCK_64
{
    uint64_t status;
    uint64_t info;
} __attribute__((packed));

constexpr static uint32_t STATUS_SUCCESS = 0;
constexpr static uint32_t STATUS_PENDING = 0x103;
constexpr static uint32_t STATUS_END_OF_FILE = 0xC0000011;

struct _LARGE_INTEGER
{
    uint64_t QuadPart;
} __attribute__((packed));

// NOTE The size of structure should be 0x18
#define FileStandardInformation 5
struct FILE_STANDARD_INFORMATION
{
    uint64_t allocation_size;
    uint64_t end_of_file;
    uint32_t number_of_links;
    uint8_t  delete_pending;
    uint8_t  directory;
    uint16_t  dummy;
} __attribute__((packed));

#define FileFsDeviceInformation 4
struct FILE_FS_DEVICE_INFORMATION
{
    uint32_t device_type;
    uint32_t characteristics;
} __attribute__((packed));

// TODO Move into "task_t" as "MAX_READ_BYTES"
static const uint64_t BYTES_TO_READ = 0x10000;

#endif // FILEDELETE_PRIVATE_H
